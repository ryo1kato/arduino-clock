## Arduino Blink "minute repeater" Clock (ATtiny85 version)

A clock with blinking LED indicating the time of day. &nbsp;
LED version of a [repeater](https://en.wikipedia.org/wiki/Repeater_%28horology%29)
You can tell a time in the dark, from distance, w/o glasses. &nbsp;
Useful if you're myopic and don't have glasses or smartphone within reach of your hand when you're in the bed (like me, with my two kids blocking my both sides). &nbsp;
LED brightness is automatically adjusted with light sensor (CdS photo cell)
The design uses AVR ATtiny85 micro controller and DS3231 RTC chip with "smart" RGB LED WS2812B.



## Telling Time
* Blinking in white: base hour of 0, 3, 6, or 9 o'clock.
    - once        : 0 o'clock
    - twice       : 3 o'clock
    - three times : 6 o'clock
    - four times  : 9 o'clock

* Blinking in <span style='color: #00AA00'>**green**</span>: add one or two hours to the above base hour.
    - example: blinking in white for three times, and then twice in green indicates 8 o'clock (8am or 8pm)

* Blinking in <span style='color: red'>**red**</span>: 10 minutes per blink.
    - example: blinking in red for four times: 40 minutes

* Blinking in <span style='color: blue'>**blue**</span>(fast): one minute per blink.

The clock blinks in white -> green -> blue -> blue, skipping some of the colors, for example, skipping red if the time is 10:02 (in which case it blinks in whilte three times, in green once, skips green, and in blue twice)

After completing this cycle, clock sleeps about 3 seconds and start a new cycle.


### Adjusting Time
Long press *Hour* and/or *Minute* button until they start blinking slowly in max brightness.

* Long press *Hour* button : advance time by 60 minutes (blinks in green)
* Long press *Minute* button : advance time by one minutes (blinks in blue)
* Long press **both** buttons : advance time by ten minutes (blinks in red)

You need to keep the buttons pressed and wait for an time indicating cycle to complete, until it starts blinking slowly and brightly.



### Build of Materials
* PCB
    - SMD (rev 0.5.1) [OSH Park](https://oshpark.com/shared_projects/CKZP3omf)
    - THT (rev 0.2) [OSH Park](https://oshpark.com/shared_projects/mC1U04Ox)
* BOM: [bom.txt](schematic/bom.txt)



### Port Assignment
* RST (GPIO #5) - Hour & Minute Buttons (using ADC above 2.2v reset threshold)
* GPIO #0       -  I2C SDA to RTC
* GPIO #1       -  Smart LED NeoPixel WS2812B
* GPIO #2       -  I2C SCL to RTC
* GPIO #3       -  Photo Cell
* GPIO #4       -  Power Control for LED, RTC, Photo Cell

