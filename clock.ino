#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/common.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

#include <EEPROM.h>
#include <TinyWireM.h>
#include "TinyRTClib.h"
#include "Narcoleptic.h"

#define EEPROM_VOID       123U


///////////////////////////////////////////////////////////////////////////////
//
// Pin Assign
//

// ATTiny85 Analog pins
#define PB2_ANALOG  (1)
#define PB3_ANALOG  (3)
#define PB4_ANALOG  (2)
#define PB5_ANALOG  (0)
#define A0 (5)
#define A1 (2)
#define A2 (4)
#define A3 (3)


// PB0 is SDA for i2c
#define NEOPIXEL_PIN       (1)
// PB2 is SCL for i2c
#define PHOTOCELL_PIN      PB3_ANALOG
#define PWRCTL_PIN         (4)
//#define DEBUG_TX_PIN       (4)
#define BUTTONS_PIN        PB5_ANALOG  // A0 = PB5 = RST


void msleep (uint32_t msecs) {
    Narcoleptic.delay(msecs);
}


///////////////////////////////////////////////////////////////////////////////
//
// Other Configurations
//

#define NUMPIXELS           (1)
#define BAUD             (9600)
#define BLINK_HZ            (3)
#define BRIGHTNESS_BASE    ( 4U) //minimum brightness, PWM 1~255
#define PHOTOCELL_MIN      (50U) //Set LED to min/max intencity if photocell ...
#define PHOTOCELL_MAX     (700U) //...reading is below or above these values
#define BRIGHTNESS_MAX    (128U)

void blink(unsigned char r, unsigned char g, unsigned char b, int count, int hz=BLINK_HZ);

///////////////////////////////////////////////////////////////////////////////
#ifdef NEOPIXEL_PIN
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Initialization Codes
//

#ifdef DEBUG_TX_PIN
#define CONFIG_SERIAL_OUTPUT
// See http://forum.arduino.cc/index.php?topic=112013.0
#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial mySerial(DEBUG_TX_PIN);
#define Serial mySerial  //Avoid conflict with the standard ATTinyCore's TinySoftwareSerial
#define debug(fmt, ...) Serial.print(fmt, ##__VA_ARGS__)
#define debugln(fmt, ...) Serial.println(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...) /* disappear */
#define debugln(fmt, ...) /* disappear */
#endif //DEBUG_TX_PIN

void setup_powersave () {
    MCUCR |= _BV(BODS) | _BV(BODSE);  //turn off the brown-out detector
    ADCSRA &= ~_BV(ADEN); // disable adc
    ACSR |= _BV(ACD);     //disable the analog comparator
    PRR = bit(PRTIM1);
}


#ifdef PWRCTL_PIN
unsigned int pwrctl_users = 0U;
void setup_powerctl() {
    pinMode(PWRCTL_PIN, OUTPUT);
    digitalWrite(PWRCTL_PIN, LOW);
}
void power_enable () {
    digitalWrite(PWRCTL_PIN, HIGH);
    delay(1);
}
void power_disable () {
    digitalWrite(PWRCTL_PIN, LOW);
}
#else // let them disappear
#   define setup_powerctl()
#   define power_enable()
#   define power_disable()
#endif


RTC_DS3231 rtc;
void setup_rtc() {
    power_enable();
    TinyWireM.begin();
    rtc.begin();
    if (rtc.lostPower()) {
        debug("RTC power lost. Loading from EEPROM: ");
        DateTime saved_time = clock_load();
        debug(saved_time.hour()); debug(":");
        debug(saved_time.minute()); debug(":");
        debugln(saved_time.second());
        rtc.adjust( saved_time );
        delay(200);
        blink(100, 0, 0, 3, 10);
        delay(200);
    } else {
        delay(200);
        blink(0, 100, 0, 3, 10);
        delay(200);
    }
    power_disable();
}



void setup_neopixel () {
#ifdef NEOPIXEL_PIN
    pinMode(NEOPIXEL_PIN, OUTPUT);
    // Walk through colors as a simple initial test
    power_enable();
    pixels.begin();
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    msleep(300);
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
    msleep(300);
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.show();
    msleep(300);
    pixels.clear();
    pixels.show();
    power_disable();
#endif
}



#ifdef CONFIG_SERIAL_OUTPUT
void setup_serial() {
    Serial.begin(BAUD);
    Serial.println("")
    Serial.println("LED Minute Repeater Clock v0.1")
}
void print_time(bool overwrite = false) {
    power_enable();
    DateTime now = rtc.now();
    power_disable();

    unsigned int y = now.year();
    unsigned int M = now.month();
    unsigned int D = now.day();
    unsigned int h = now.hour();
    unsigned int m = now.minute();
    unsigned int s = now.second();
    if (overwrite) {
        Serial.print("      \r");
    }
    Serial.print(y, DEC);
    Serial.print('-');
    if ( M < 10 ) { Serial.print("0"); }
    Serial.print(M, DEC);
    Serial.print('-');
    if ( D < 10 ) { Serial.print("0"); }
    Serial.print(D, DEC);
    Serial.print(" ");
    Serial.print(h);
    Serial.print(":");
    if ( m < 10 ) { Serial.print("0"); }
    Serial.print(m);
    Serial.print(".");
    if ( s < 10 ) { Serial.print("0"); }
    Serial.print(s);
    if (!overwrite) {
        Serial.println("");
    }


}
#else
#define setup_serial()
#define print_time()
#endif

int analogReadPS(uint8_t pin) {

    ACSR &= ~ _BV(ACD);     // Enablethe analog comparator
    bitClear(PRR, PRADC);   // power up ADC
    ADCSRA |= _BV(ADEN);

    unsigned int reading = analogRead(pin);

    ADCSRA &= ~_BV(ADEN);
    bitSet(PRR, PRADC);     // power down ADC
    ACSR |= _BV(ACD);       //Disable the analog comparator
    return reading;
}

unsigned char brightness()
{
#ifdef PHOTOCELL_PIN
    power_enable();
    unsigned int reading = analogReadPS(PHOTOCELL_PIN);
    unsigned char brightness;
    if ( reading < PHOTOCELL_MIN ) {
        brightness = BRIGHTNESS_BASE;
    } else {
        brightness = BRIGHTNESS_BASE + (BRIGHTNESS_MAX - BRIGHTNESS_BASE)
                    * (reading - PHOTOCELL_MIN)/(PHOTOCELL_MAX - PHOTOCELL_MIN);
    }
    if (brightness >= BRIGHTNESS_MAX ) {
        brightness = BRIGHTNESS_MAX;
    }
    power_disable();
#ifdef CONFIG_SERIAL_OUTPUT
    Serial.print("    ADC value: ");
    Serial.println(reading);
    Serial.print("    Brightness: ");
    Serial.println(brightness);
#endif
    return brightness;
#else
    return BRIGHTNESS_MAX/4;
#endif
}


// Poor man's wear-leveling
unsigned int eeprom_current_slot () {
    for (unsigned int i=0; i < EEPROM.length() ; i++) {
        if ( EEPROM.read(i) < EEPROM_VOID ) {
            return i;
        }
    }
    return 0;
}

void clock_save(uint8_t h, uint8_t m, uint8_t s) {
    /* clear current slot */
    unsigned int offset = eeprom_current_slot();
    EEPROM.write(offset + 0, EEPROM_VOID);
    EEPROM.write(offset + 1, EEPROM_VOID);
    EEPROM.write(offset + 2, EEPROM_VOID);

    offset += 3;
    if (offset + 3 >= EEPROM.length() ) {
        offset = 0;
    }

    EEPROM.write(offset + 0, h);
    EEPROM.write(offset + 1, m);
    EEPROM.write(offset + 2, s);
}

DateTime clock_load() {
    unsigned int offset = eeprom_current_slot();
    unsigned char h = EEPROM.read(offset + 0);
    unsigned char m = EEPROM.read(offset + 1);
    unsigned char s = EEPROM.read(offset + 2);
    return DateTime(2000, 1, 1, h, m, s);
}


void blink(unsigned char r, unsigned char g, unsigned char b, int count, int hz=BLINK_HZ)
{
    for (int i = 0; i < count; i++) {
        power_enable();
        pixels.setPixelColor(0, pixels.Color(g, r, b));
        pixels.setPixelColor(1, pixels.Color(g, r, b));
        pixels.show();
        msleep(1000/hz/2);
        pixels.clear();
        pixels.show();
        power_disable();
        msleep(1000/hz);
    }
}


int last_save_min = 0;
void blink_time() {
    power_enable();
    DateTime now = rtc.now();
    power_disable();
    uint8_t h = now.hour();
    uint8_t m = now.minute();
    uint8_t s = now.second();

    int br = brightness();
    // once -> 0, twice -> 3, tri -> 6, quad -> 9 o'clock
    blink(br, br, br, (h%12) / 3 + 1);
    msleep(1000/BLINK_HZ);

    //hour
    blink(0, br, 0, (h%12) % 3);
    msleep(1000/BLINK_HZ);

    //ten minutes
    blink(br, 0, 0, m / 10 );
    msleep(2*1000/BLINK_HZ);

    //last digit of minutes
    blink(0, 0, br, m % 10, BLINK_HZ*2);
    msleep(2*1000/BLINK_HZ);

    if (last_save_min != m) {
        clock_save(h, m, s);
        last_save_min = m;
    }

}


int readButtons() {
    unsigned int reading = analogReadPS(BUTTONS_PIN);
    debug("    Button ADC: ");
    debugln(reading);
    if (reading > 950) {
        return 0;  // 2K ohm pullup
    }
    else if (reading > 800) {
        return 1;  //10K ohm button
    }
    else if (reading > 700) {
        return 2;  // 5k ohm button
    }
    else {
        return 3;  // both 10k and 5k ohm, composite resistance =
    }
}

bool buttonHour(unsigned int buttonStatus) {
    return ( (buttonStatus & 0x01) > 0 );
}
bool buttonMinute(unsigned int buttonStatus) {
    return ( (buttonStatus & 0x02) > 0 );
}

void advanceRtcMinutes(int minutes) {
    power_enable();
    DateTime now = rtc.now();
    DateTime adj = DateTime( now.unixtime() + (minutes*60) );
    rtc.adjust( adj );
    power_disable();
}


void setup() {
    setup_powersave();
    setup_serial();
    setup_powerctl();
    setup_neopixel();
    setup_rtc();
}


void loop() {
    print_time();
    blink_time();

    int btn = readButtons();
    while ( btn > 0 ) {
        if ( buttonHour(btn) && buttonMinute(btn) ) {
            blink(0, BRIGHTNESS_MAX, 0, 1, 2);
            advanceRtcMinutes(10);
        }
        else if ( buttonHour(btn) ) {
            blink(BRIGHTNESS_MAX, 0, 0, 1, 2);
            advanceRtcMinutes(60);
        }
        else if ( buttonMinute(btn) ) {
            blink(0, 0, BRIGHTNESS_MAX, 1, 2);
            advanceRtcMinutes(1);
        }
        print_time();
        btn = readButtons();
    }

    msleep(2000);
}

;
