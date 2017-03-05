#include <limits.h>


#define BAUD 9600
#define HOUR_BUTTON 2
#define MINUTE_BUTTON 3

 
void print_time(bool overwrite) {
    int h = fake_rtc_hours();
    int m = fake_rtc_mins();
    int s = fake_rtc_secs();
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


void setup()  {
    Serial.begin(BAUD);

    pinMode(HOUR_BUTTON, INPUT_PULLUP);
    pinMode(MINUTE_BUTTON, INPUT_PULLUP);
}


void loop() {
    print_time(true);

    if (digitalRead(MINUTE_BUTTON) == LOW) {
        fake_rtc_advance(0, 1);
    }
    if (digitalRead(HOUR_BUTTON) == LOW) {
        fake_rtc_advance(1, 0);
    }
    delay(250);
}
