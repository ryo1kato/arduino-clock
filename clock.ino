#include <Adafruit_NeoPixel.h>
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <TinyWireM.h>
#include "TinyRTClib.h"
#include "Narcoleptic.h"


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


#define delay Narcoleptic.delay

///////////////////////////////////////////////////////////////////////////////
//
// Other Configurations
//

#define NUMPIXELS           (1)
#define BAUD             (9600)
#define BLINK_HZ            (4)
#define BRIGHTNESS_BASE    ( 4U) //minimum brightness, PWM 1~255
#define PHOTOCELL_MIN      (50U) //Set LED to min/max intencity if photocell ...
#define PHOTOCELL_MAX     (700U) //...reading is below or above these values
#define BRIGHTNESS_MAX    (255U)


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
#endif //DEBUG_TX_PIN


#ifdef PWRCTL_PIN
unsigned int pwrctl_users=0;
void setup_power() {
    pinMode(PWRCTL_PIN, OUTPUT);
    digitalWrite(PWRCTL_PIN, LOW);
}
void power_enable () {
    if ( pwrctl_users <= 0 ) {
        digitalWrite(PWRCTL_PIN, HIGH);
    }
    pwrctl_users++;
}
void power_disable () {
    pwrctl_users--;
    if ( pwrctl_users <= 0 ) {
        digitalWrite(PWRCTL_PIN, LOW);
    }
}
#else // let them disappear
#   define setup_power()
#   define power_enable()
#   define power_disable()
#endif


RTC_DS3231 rtc;
void setup_rtc() {
    TinyWireM.begin();
    power_enable();
    rtc.begin();
    if (rtc.lostPower()) {
        rtc.adjust(DateTime((__DATE__), (__TIME__)));
    }
    power_disable();
}


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);

void setup_neopixel () {
    pinMode(NEOPIXEL_PIN, OUTPUT);
    // Walk through colors as a simple initial test
    power_enable();
    pixels.begin();
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    delay(300);
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
    delay(300);
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.show();
    delay(300);
    pixels.clear();
    pixels.show();
    power_disable();
}



#ifdef CONFIG_SERIAL_OUTPUT
void setup_serial() {
    Serial.begin(BAUD);
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

unsigned char brightness()
{
#ifdef PHOTOCELL_PIN
    power_enable();
    unsigned int reading = analogRead(PHOTOCELL_PIN);
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
    Serial.print("ADC value: ");
    Serial.println(reading);
    Serial.print("Brightness: ");
    Serial.println(brightness);
#endif
    return brightness;
#else
    return BRIGHTNESS_MAX/4;
#endif
}


void blink(unsigned char r, unsigned char g, unsigned char b, int count, int hz=BLINK_HZ)
{
    for (int i = 0; i < count; i++) {
        power_enable();
        pixels.setPixelColor(0, pixels.Color(r, g, b));
        pixels.setPixelColor(1, pixels.Color(r, g, b));
        pixels.show();
        delay(1000/hz);
        pixels.clear();
        pixels.show();
        power_disable();
        delay(1000/hz);
    }
}


void blink_time() {
    power_enable();
    DateTime now = rtc.now();
    power_disable();
    uint8_t h = now.hour();
    uint8_t m = now.minute();

    int br = brightness();
    // once -> 0, twice -> 3, tri -> 6, quad -> 9 o'clock
    blink(br/2, br/2, br/2, (h%12) / 3 + 1);
    delay(1000/BLINK_HZ);

    //hour
    blink(br, 0, 0, (h%12) % 3);
    delay(1000/BLINK_HZ);

    //ten minutes
    blink(0, br, 0, m / 10 );
    delay(2*1000/BLINK_HZ);

    //last digit of minutes
    blink(0, 0, br, m % 10, BLINK_HZ*2);
    delay(2*1000/BLINK_HZ);
}


int readButtons() {
    unsigned int reading = analogRead(BUTTONS_PIN);
    if (reading > 900) {
        return 0;  // 2K ohm pullup
    }
    else if (reading > 770) {
        return 1;  //10K ohm button
    }
    else if (reading > 660) {
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
    setup_serial();
    setup_power();
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

    delay(2000);
}

;
