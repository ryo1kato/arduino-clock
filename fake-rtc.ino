unsigned long int rtc_ms = 0;
#define DAYSEC (24UL*3600UL)

// a 24H-wrap second counter to handle
// 32bit overflow (49.7days) for millis()
unsigned long int seconds() {
    static unsigned long last_millis = 0;
    unsigned long new_millis = millis();
    rtc_ms += new_millis - last_millis;
    last_millis = new_millis;

    if ( rtc_ms > DAYSEC*1000 ) {
        // assuming this function to be called at least once a day
        rtc_ms %= DAYSEC*1000 ;
    }
    return rtc_ms/1000;
}

void fake_rtc_set(int h, int m, int s)
{
    rtc_ms = 1000UL * h * m * s;
}

void fake_rtc_advance(unsigned long h, unsigned long m)
{
    rtc_ms += m *   60UL*1000UL;
    rtc_ms += h * 3600UL*1000UL;
}

unsigned int fake_rtc_hours()
{
    return (seconds() / 3600UL) % 24UL;
}

unsigned int fake_rtc_mins()
{
    return (seconds()/60UL) % 60UL;
}

unsigned fake_rtc_secs()
{
    return seconds() % 60UL;
}

