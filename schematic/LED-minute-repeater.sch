EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:switches
LIBS:leds
LIBS:ws2812b
LIBS:maxim
LIBS:zoncon-cache
LIBS:LED-minute-repeater-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SW_Push SW3
U 1 1 58D2CAE0
P 3550 3550
F 0 "SW3" H 3600 3650 50  0000 L CNN
F 1 "Minute" V 3550 3800 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_EVQPE1" H 3550 3750 50  0001 C CNN
F 3 "" H 3550 3750 50  0001 C CNN
	1    3550 3550
	0    1    1    0   
$EndComp
$Comp
L ATTINY85-20PU U1
U 1 1 58D2E7B1
P 5150 1500
F 0 "U1" H 4000 1900 50  0000 C CNN
F 1 "ATTiny85" H 6150 1100 50  0000 C CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 6150 1500 50  0001 C CIN
F 3 "" H 5150 1500 50  0001 C CNN
	1    5150 1500
	1    0    0    -1  
$EndComp
$Comp
L R_PHOTO R2
U 1 1 58D2E89F
P 2250 2300
F 0 "R2" H 2300 2350 50  0000 L CNN
F 1 "PHOTO CELL" H 2300 2300 50  0000 L TNN
F 2 "Opto-Devices:Resistor_LDR_4.9x4.2_RM2.54" V 2300 2050 50  0001 L CNN
F 3 "" H 2250 2250 50  0001 C CNN
	1    2250 2300
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 58D2E967
P 2250 2600
F 0 "R3" V 2330 2600 50  0000 C CNN
F 1 "R_ADC" V 2150 2600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2180 2600 50  0001 C CNN
F 3 "" H 2250 2600 50  0001 C CNN
	1    2250 2600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR01
U 1 1 58D30225
P 6500 1250
F 0 "#PWR01" H 6500 1100 50  0001 C CNN
F 1 "+3.3V" H 6500 1390 50  0000 C CNN
F 2 "" H 6500 1250 50  0001 C CNN
F 3 "" H 6500 1250 50  0001 C CNN
	1    6500 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 58D30248
P 6500 1750
F 0 "#PWR02" H 6500 1500 50  0001 C CNN
F 1 "GND" H 6500 1600 50  0000 C CNN
F 2 "" H 6500 1750 50  0001 C CNN
F 3 "" H 6500 1750 50  0001 C CNN
	1    6500 1750
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW2
U 1 1 58D30269
P 3150 3550
F 0 "SW2" H 3200 3650 50  0000 L CNN
F 1 "Hour" V 3300 3450 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_EVQPE1" H 3150 3750 50  0001 C CNN
F 3 "" H 3150 3750 50  0001 C CNN
	1    3150 3550
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 58D3092A
P 3150 3000
F 0 "R4" V 3230 3000 50  0000 C CNN
F 1 "10K" V 3150 3000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3080 3000 50  0001 C CNN
F 3 "" H 3150 3000 50  0001 C CNN
	1    3150 3000
	1    0    0    -1  
$EndComp
$Comp
L DS3231 U2
U 1 1 58D3F29A
P 8700 3150
F 0 "U2" H 8600 3625 50  0000 R CNN
F 1 "DS3231" H 9150 2750 50  0000 R CNN
F 2 "Housings_SOIC:SOIC-16W_7.5x10.3mm_Pitch1.27mm" H 8750 2750 50  0001 L CNN
F 3 "" H 8970 3400 50  0001 C CNN
	1    8700 3150
	1    0    0    -1  
$EndComp
Text GLabel 3800 1650 0    60   Output ~ 0
PWR_CTRL
Text GLabel 3800 1750 0    60   Input ~ 0
BUTTON/RST
Text GLabel 2650 2450 2    60   Output ~ 0
PCELL
Text GLabel 2250 2000 0    60   Input ~ 0
PWR_CTRL
Text GLabel 5000 2500 0    60   Input ~ 0
PWR_CTRL
Text GLabel 3800 1350 0    60   Output ~ 0
LED_SIG
Text GLabel 3800 1250 0    60   Output ~ 0
RTC_SDA
Text GLabel 3800 1450 0    60   Output ~ 0
RTC_SCL
Text GLabel 3800 1550 0    60   Input ~ 0
PCELL
Text GLabel 5800 2600 0    60   Input ~ 0
LED_SIG
$Comp
L Battery BT1
U 1 1 58D43E82
P 8600 1450
F 0 "BT1" H 8700 1550 50  0000 L CNN
F 1 "Battery" H 8700 1450 50  0000 L CNN
F 2 "clock-ws2812-schematic-v2:BatteryHolder_3xAAA_Keystone_2479" V 8600 1510 50  0001 C CNN
F 3 "" V 8600 1510 50  0001 C CNN
	1    8600 1450
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR03
U 1 1 58D43F45
P 7250 1400
F 0 "#PWR03" H 7250 1250 50  0001 C CNN
F 1 "+3.3V" H 7250 1540 50  0000 C CNN
F 2 "" H 7250 1400 50  0001 C CNN
F 3 "" H 7250 1400 50  0001 C CNN
	1    7250 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 58D43F71
P 8600 1750
F 0 "#PWR04" H 8600 1500 50  0001 C CNN
F 1 "GND" H 8600 1600 50  0000 C CNN
F 2 "" H 8600 1750 50  0001 C CNN
F 3 "" H 8600 1750 50  0001 C CNN
	1    8600 1750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR05
U 1 1 58D440B9
P 9450 3350
F 0 "#PWR05" H 9450 3200 50  0001 C CNN
F 1 "+3.3V" H 9450 3490 50  0000 C CNN
F 2 "" H 9450 3350 50  0001 C CNN
F 3 "" H 9450 3350 50  0001 C CNN
	1    9450 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 58D440E5
P 8700 3650
F 0 "#PWR06" H 8700 3400 50  0001 C CNN
F 1 "GND" H 8700 3500 50  0000 C CNN
F 2 "" H 8700 3650 50  0001 C CNN
F 3 "" H 8700 3650 50  0001 C CNN
	1    8700 3650
	1    0    0    -1  
$EndComp
Text GLabel 7700 3150 0    60   Input ~ 0
RTC_SDA
Text GLabel 7700 3050 0    60   Input ~ 0
RTC_SCL
$Comp
L R R6
U 1 1 58D44279
P 3550 3000
F 0 "R6" V 3630 3000 50  0000 C CNN
F 1 "5K" V 3550 3000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3480 3000 50  0001 C CNN
F 3 "" H 3550 3000 50  0001 C CNN
	1    3550 3000
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 58D44783
P 3550 2450
F 0 "R5" V 3630 2450 50  0000 C CNN
F 1 "2K" V 3550 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3480 2450 50  0001 C CNN
F 3 "" H 3550 2450 50  0001 C CNN
	1    3550 2450
	1    0    0    -1  
$EndComp
Text GLabel 3700 2700 2    60   Output ~ 0
BUTTON/RST
$Comp
L GND #PWR07
U 1 1 58D489BB
P 3350 3950
F 0 "#PWR07" H 3350 3700 50  0001 C CNN
F 1 "GND" H 3350 3800 50  0000 C CNN
F 2 "" H 3350 3950 50  0001 C CNN
F 3 "" H 3350 3950 50  0001 C CNN
	1    3350 3950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR08
U 1 1 58D5C31A
P 3550 2300
F 0 "#PWR08" H 3550 2150 50  0001 C CNN
F 1 "+3.3V" H 3550 2440 50  0000 C CNN
F 2 "" H 3550 2300 50  0001 C CNN
F 3 "" H 3550 2300 50  0001 C CNN
	1    3550 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 58D780CE
P 2250 2900
F 0 "#PWR09" H 2250 2650 50  0001 C CNN
F 1 "GND" H 2250 2750 50  0000 C CNN
F 2 "" H 2250 2900 50  0001 C CNN
F 3 "" H 2250 2900 50  0001 C CNN
	1    2250 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 58D782F4
P 5050 2950
F 0 "#PWR010" H 5050 2700 50  0001 C CNN
F 1 "GND" H 5050 2800 50  0000 C CNN
F 2 "" H 5050 2950 50  0001 C CNN
F 3 "" H 5050 2950 50  0001 C CNN
	1    5050 2950
	1    0    0    -1  
$EndComp
Text GLabel 8700 2550 1    60   Input ~ 0
PWR_CTRL
$Comp
L CONN_01X03_FEMALE J2
U 1 1 58EA8B21
P 5500 4250
F 0 "J2" H 5500 4550 50  0000 C CNN
F 1 "WS2812B_OUT" V 5700 4200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 5500 4450 50  0001 C CNN
F 3 "" H 5500 4450 50  0001 C CNN
	1    5500 4250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 58EA8B7D
P 5400 4050
F 0 "#PWR011" H 5400 3900 50  0001 C CNN
F 1 "+3.3V" H 5250 4150 50  0000 C CNN
F 2 "" H 5400 4050 50  0001 C CNN
F 3 "" H 5400 4050 50  0001 C CNN
	1    5400 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 58EA8BAC
P 5400 4450
F 0 "#PWR012" H 5400 4200 50  0001 C CNN
F 1 "GND" H 5400 4300 50  0000 C CNN
F 2 "" H 5400 4450 50  0001 C CNN
F 3 "" H 5400 4450 50  0001 C CNN
	1    5400 4450
	1    0    0    -1  
$EndComp
Text GLabel 5800 2900 0    60   Output ~ 0
LED_SIG_OUT
Text GLabel 5400 4250 0    60   Input ~ 0
LED_SIG_OUT
$Comp
L CONN_02X03 J1
U 1 1 58EAB70F
P 2250 1350
F 0 "J1" H 2250 1550 50  0000 C CNN
F 1 "ICSP" H 2250 1150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 2250 150 50  0001 C CNN
F 3 "" H 2250 150 50  0001 C CNN
	1    2250 1350
	1    0    0    -1  
$EndComp
Text GLabel 2000 1450 0    60   Output ~ 0
BUTTON/RST
$Comp
L GND #PWR013
U 1 1 58EAE3FB
P 2500 1450
F 0 "#PWR013" H 2500 1200 50  0001 C CNN
F 1 "GND" H 2500 1300 50  0000 C CNN
F 2 "" H 2500 1450 50  0001 C CNN
F 3 "" H 2500 1450 50  0001 C CNN
	1    2500 1450
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR014
U 1 1 58EAE461
P 2500 1250
F 0 "#PWR014" H 2500 1100 50  0001 C CNN
F 1 "+3.3V" H 2500 1390 50  0000 C CNN
F 2 "" H 2500 1250 50  0001 C CNN
F 3 "" H 2500 1250 50  0001 C CNN
	1    2500 1250
	1    0    0    -1  
$EndComp
Text GLabel 2500 1350 2    60   Output ~ 0
RTC_SDA
Text GLabel 2000 1250 0    60   Output ~ 0
LED_SIG
Text GLabel 2000 1350 0    60   Output ~ 0
RTC_SCL
NoConn ~ 8200 3350
NoConn ~ 9200 3050
NoConn ~ 9200 3150
$Comp
L MCP1700T-3002E/TT U3
U 1 1 58ECF1D1
P 7700 1500
F 0 "U3" H 7600 1350 50  0000 C CNN
F 1 "MCP1700T" H 7700 1750 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT89-3_Housing_Handsoldering" H 7700 1600 50  0001 C CNN
F 3 "" H 7700 1600 50  0001 C CNN
	1    7700 1500
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR015
U 1 1 58ED04AD
P 8600 1250
F 0 "#PWR015" H 8600 1100 50  0001 C CNN
F 1 "+5V" H 8700 1350 50  0000 C CNN
F 2 "" H 8600 1250 50  0001 C CNN
F 3 "" H 8600 1250 50  0001 C CNN
	1    8600 1250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG016
U 1 1 58ED04EB
P 8450 1250
F 0 "#FLG016" H 8450 1325 50  0001 C CNN
F 1 "PWR_FLAG" H 8300 1400 50  0000 C CNN
F 2 "" H 8450 1250 50  0001 C CNN
F 3 "" H 8450 1250 50  0001 C CNN
	1    8450 1250
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 58ED07EF
P 8150 1500
F 0 "C2" H 8175 1600 50  0000 L CNN
F 1 "1uF" H 8175 1400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8188 1350 50  0001 C CNN
F 3 "" H 8150 1500 50  0001 C CNN
	1    8150 1500
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 58ED0902
P 7250 1550
F 0 "C1" H 7275 1650 50  0000 L CNN
F 1 "1uF" H 7050 1450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7288 1400 50  0001 C CNN
F 3 "" H 7250 1550 50  0001 C CNN
	1    7250 1550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 J3
U 1 1 58ED0D5F
P 7150 4100
F 0 "J3" H 7150 4350 50  0000 C CNN
F 1 "I2C" V 7250 4100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 7150 4100 50  0001 C CNN
F 3 "" H 7150 4100 50  0001 C CNN
	1    7150 4100
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 58ED13A3
P 8050 2800
F 0 "R7" H 8100 2650 50  0000 C CNN
F 1 "SCL_PUP" V 8150 2850 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7980 2800 50  0001 C CNN
F 3 "" H 8050 2800 50  0001 C CNN
	1    8050 2800
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 58ED13F2
P 7850 2800
F 0 "R1" H 7900 2650 50  0000 C CNN
F 1 "SDA_PUP" V 7750 2800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7780 2800 50  0001 C CNN
F 3 "" H 7850 2800 50  0001 C CNN
	1    7850 2800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR017
U 1 1 58ED14C7
P 7850 2650
F 0 "#PWR017" H 7850 2500 50  0001 C CNN
F 1 "+3.3V" H 7800 2800 50  0000 C CNN
F 2 "" H 7850 2650 50  0001 C CNN
F 3 "" H 7850 2650 50  0001 C CNN
	1    7850 2650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR018
U 1 1 58ED150B
P 8050 2650
F 0 "#PWR018" H 8050 2500 50  0001 C CNN
F 1 "+3.3V" H 8050 2790 50  0000 C CNN
F 2 "" H 8050 2650 50  0001 C CNN
F 3 "" H 8050 2650 50  0001 C CNN
	1    8050 2650
	1    0    0    -1  
$EndComp
Text GLabel 6950 4150 0    60   Input ~ 0
RTC_SDA
Text GLabel 6950 4050 0    60   Input ~ 0
RTC_SCL
$Comp
L GND #PWR019
U 1 1 58ED193C
P 6950 4250
F 0 "#PWR019" H 6950 4000 50  0001 C CNN
F 1 "GND" H 6950 4100 50  0000 C CNN
F 2 "" H 6950 4250 50  0001 C CNN
F 3 "" H 6950 4250 50  0001 C CNN
	1    6950 4250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR020
U 1 1 58ED19A6
P 6950 3950
F 0 "#PWR020" H 6950 3800 50  0001 C CNN
F 1 "+3.3V" H 6900 4100 50  0000 C CNN
F 2 "" H 6950 3950 50  0001 C CNN
F 3 "" H 6950 3950 50  0001 C CNN
	1    6950 3950
	1    0    0    -1  
$EndComp
$Comp
L WS2812 LED1
U 1 1 58ED93FE
P 5800 2600
F 0 "LED1" H 6200 2700 60  0000 C CNN
F 1 "WS2812" H 6200 2200 60  0000 C CNN
F 2 "WS2812:WS2812-8mm" H 6200 2400 60  0001 C CNN
F 3 "" H 6200 2400 60  0000 C CNN
	1    5800 2600
	1    0    0    -1  
$EndComp
Text Notes 8150 7650 0    60   ~ 0
2017-04-29
Text Notes 7350 7500 0    60   ~ 0
LED Minute Repeater Clock (ATtiny85)
Text Notes 10550 7650 0    60   ~ 0
0.2
Text Notes 7000 6750 0    40   ~ 0
[Rev 0.2]\n  - Fixed MCP1700 pin assign (Vin <-> Vout)\n  - Fixed DS3231 pin assign (SCL <-> SDA)
$Comp
L C C4
U 1 1 59052A27
P 9450 3500
F 0 "C4" H 9475 3600 50  0000 L CNN
F 1 "0.1uF" H 9475 3400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9488 3350 50  0001 C CNN
F 3 "" H 9450 3500 50  0001 C CNN
	1    9450 3500
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 59052ACC
P 9750 3500
F 0 "C5" H 9775 3600 50  0000 L CNN
F 1 "0.1uF" H 9775 3400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9788 3350 50  0001 C CNN
F 3 "" H 9750 3500 50  0001 C CNN
	1    9750 3500
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 59054059
P 6500 1500
F 0 "C6" H 6525 1600 50  0000 L CNN
F 1 "0.1uF" H 6525 1400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6538 1350 50  0001 C CNN
F 3 "" H 6500 1500 50  0001 C CNN
	1    6500 1500
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 590540B2
P 5200 2650
F 0 "C3" H 5225 2750 50  0000 L CNN
F 1 "0.1uF (LED)" H 5225 2550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5238 2500 50  0001 C CNN
F 3 "" H 5200 2650 50  0001 C CNN
	1    5200 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 2450 2650 2450
Connection ~ 2250 2450
Wire Wire Line
	3550 2600 3550 2850
Wire Wire Line
	3550 2850 3150 2850
Wire Wire Line
	3550 2700 3700 2700
Connection ~ 3550 2700
Wire Wire Line
	3550 3150 3550 3350
Wire Wire Line
	3150 3150 3150 3350
Wire Wire Line
	3150 3750 3150 3950
Wire Wire Line
	3150 3950 3550 3950
Wire Wire Line
	3550 3950 3550 3750
Wire Wire Line
	2250 2000 2250 2150
Wire Wire Line
	2250 2750 2250 2900
Connection ~ 3350 3950
Wire Wire Line
	7250 1700 8600 1700
Wire Wire Line
	8000 1250 8600 1250
Wire Wire Line
	8000 1250 8000 1400
Wire Wire Line
	8150 1250 8150 1350
Connection ~ 8150 1250
Wire Wire Line
	8150 1700 8150 1650
Connection ~ 8150 1700
Connection ~ 7700 1700
Wire Wire Line
	7250 1400 7400 1400
Connection ~ 7250 1400
Wire Wire Line
	7700 3050 8200 3050
Wire Wire Line
	7700 3150 8200 3150
Wire Wire Line
	7850 2950 7850 3150
Connection ~ 7850 3150
Wire Wire Line
	8050 2950 8050 3050
Connection ~ 8050 3050
Wire Wire Line
	8600 1650 8600 1750
Connection ~ 8600 1700
Wire Wire Line
	5050 2950 5050 2800
Connection ~ 6500 1750
Connection ~ 8000 1400
Connection ~ 8450 1250
Wire Wire Line
	5350 2500 5350 2700
Wire Wire Line
	5350 2700 5800 2700
Wire Wire Line
	8700 3650 9750 3650
Connection ~ 9450 3650
Wire Wire Line
	9200 3350 9450 3350
Wire Wire Line
	8700 2550 8700 2650
Wire Wire Line
	8700 2650 9750 2650
Wire Wire Line
	9750 2650 9750 3350
Connection ~ 6500 1250
Connection ~ 9450 3350
Connection ~ 8700 3650
Connection ~ 8700 2650
Wire Wire Line
	6500 1250 6500 1350
Wire Wire Line
	6500 1650 6500 1750
Connection ~ 5200 2800
Wire Wire Line
	5050 2800 5800 2800
Wire Wire Line
	5000 2500 5350 2500
Connection ~ 5200 2500
$EndSCHEMATC
