#include <EEPROM.h>

#define BAUD 9600
#define HOUR_BUTTON   2
#define MINUTE_BUTTON 3

#define HOUR_LED           10
#define MINUTE_LED          9
#define BLINK_HZ            4

#define BRIGHTNESS_STEPS    5  //two to the power of STEPS
#define HOUR_BRIGHTNESS     1U //minimum brightness, PWM 1~255
#define MINUTE_BRIGHTNESS   4U
#define PHOTOCELL_PIN       0U
#define PHOTOCELL_MIN      15U //Set LED to min/max intencity if photocell
#define PHOTOCELL_MAX     200U //reading is below or above these values
#define BRIGHTNESS_MAX    255U

#define EEPROM_INDIRECT    10
#define EEPROM_ROTATE_FREQ 10
#define EEPROM_VOID        123U



unsigned int eeprom_current_slot () {
    for (unsigned int i=0; i < EEPROM.length() ; i++) {
        if ( EEPROM.read(i) < EEPROM_VOID ) {
            return i;
        }
    }
    return 0;
}

void clock_load() {
    unsigned int offset = eeprom_current_slot();
    unsigned char h = EEPROM.read(offset + 0);
    unsigned char m = EEPROM.read(offset + 1);
    unsigned char s = EEPROM.read(offset + 2);
    fake_rtc_set(h, m, s);
}

void clock_save() {
    int h = fake_rtc_hours();
    int m = fake_rtc_mins();
    int s = fake_rtc_secs();

    /* clear current slot */
    unsigned int offset = eeprom_current_slot();
    EEPROM.write(offset + 0, EEPROM_VOID);
    EEPROM.write(offset + 1, EEPROM_VOID);
    EEPROM.write(offset + 2, EEPROM_VOID);

    offset += 3;
    if (offset + 3 >= EEPROM.length() ) {
        offset = 0;
    }

    Serial.print(" Saving to EEPROM: ");
    Serial.print(h);    Serial.print(":");
    Serial.print(m);    Serial.print(":");
    Serial.print(s);
    Serial.print(" offset: ");
    Serial.print(offset);
    Serial.print("\r\n");

    EEPROM.write(offset + 0, h);
    EEPROM.write(offset + 1, m);
    EEPROM.write(offset + 2, s);
}

void print_time(bool overwrite = true) {
    unsigned int h = fake_rtc_hours();
    unsigned int m = fake_rtc_mins();
    unsigned int s = fake_rtc_secs();
    if (overwrite) {
        Serial.print("      \r");
    }
    Serial.print(h);
    Serial.print(":");
    if ( m < 10 ) {
        Serial.print("0");
    }
    Serial.print(m);
    Serial.print(".");
    if ( s < 10 ) {
        Serial.print("0");
    }
    Serial.print(s);
    if (!overwrite) {
        Serial.print("\r\n");
    }
}

unsigned char brightness(unsigned char led_base)
{
    unsigned int reading = analogRead(PHOTOCELL_PIN);
    unsigned int led_max = led_base << BRIGHTNESS_STEPS;
    unsigned char brightness;
    if ( reading < PHOTOCELL_MIN ) {
        brightness = led_base;
    } else {
        brightness = led_base + (led_max - led_base)
                    * (reading - PHOTOCELL_MIN)/(PHOTOCELL_MAX - PHOTOCELL_MIN);
    }
    if (brightness >= BRIGHTNESS_MAX ) {
        brightness = BRIGHTNESS_MAX;
    }
    return brightness;
}

void blink(bool hour, bool minute, int count, int hz=BLINK_HZ)
{

    for (int i = 0; i < count; i++) {
        if (hour)   analogWrite(HOUR_LED, brightness(HOUR_BRIGHTNESS));
        if (minute) analogWrite(MINUTE_LED, brightness(MINUTE_BRIGHTNESS));
        delay(1000/hz);
        analogWrite(HOUR_LED, 0);
        analogWrite(MINUTE_LED, 0);
        delay(1000/hz);
    }
}

void blink_time() {
    unsigned int h = fake_rtc_hours();
    unsigned int m = fake_rtc_mins();

    // once -> 0, twice -> 3, tri -> 6, quad -> 9 o'clock
    blink(true,   true, (h%12) / 3 + 1);
    blink(true,  false, (h%12) % 3);
    delay(1000/BLINK_HZ);
    blink(false,  true, m / 10 );
    delay(2*1000/BLINK_HZ);
}

void setup() {
    Serial.begin(BAUD);
    clock_load();
    pinMode(HOUR_BUTTON, INPUT_PULLUP);
    pinMode(MINUTE_BUTTON, INPUT_PULLUP);
    pinMode(HOUR_LED, OUTPUT);
    pinMode(MINUTE_LED, OUTPUT);
    digitalWrite(HOUR_LED, HIGH);
    digitalWrite(MINUTE_LED, HIGH);
    delay(100);
    digitalWrite(HOUR_LED, LOW);
    digitalWrite(MINUTE_LED, LOW);
}

#define H_BTN_PRESSED  (digitalRead(HOUR_BUTTON) == LOW)
#define M_BTN_PRESSED  (digitalRead(MINUTE_BUTTON) == LOW)

void loop() {
    static unsigned int last_save_min;
    print_time();
    blink_time();

    /* Save current time to EEPROM every minute.
       Since we wear-level the write, for 1K size,
       we have over 60 years before wear-out the EEPROM.
            100000 / 24 / 60 * (1000/3) / 365 = 62.9
     */
    if ( last_save_min != fake_rtc_mins() ) {
        clock_save();
        last_save_min = fake_rtc_mins();
    }

    while ( H_BTN_PRESSED || M_BTN_PRESSED ) {
        if (H_BTN_PRESSED && M_BTN_PRESSED ) {
            blink(true, true, 1, 2);
            fake_rtc_advance(0, 10);
        }
        else if (H_BTN_PRESSED) {
            blink(true, false, 1, 2);
            fake_rtc_advance(1, 0);
        }
        else if (M_BTN_PRESSED) {
            blink(false, true, 1, 2);
            fake_rtc_advance(0, 1);
        }
        print_time();
    }
    delay(3000);
}
;
