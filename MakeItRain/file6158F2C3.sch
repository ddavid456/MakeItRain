EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 10 10
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
L Connector:Screw_Terminal_01x02 J3
U 1 1 61497C21
P 1600 1800
F 0 "J3" H 1680 1792 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 1680 1701 50  0000 L CNN
F 2 "" H 1600 1800 50  0001 C CNN
F 3 "~" H 1600 1800 50  0001 C CNN
	1    1600 1800
	-1   0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:IRF9Z34NPBF Q17
U 1 1 61498C00
P 2450 2100
F 0 "Q17" H 2880 2246 50  0000 L CNN
F 1 "IRF9Z34NPBF" H 2880 2155 50  0000 L CNN
F 2 "TO254P469X1042X1967-3P" H 2900 2050 50  0001 L CNN
F 3 "https://www.infineon.com/dgdl/irf9z34npbf.pdf?fileId=5546d462533600a40153561220af1ddd" H 2900 1950 50  0001 L CNN
F 4 "MOSFET MOSFT PCh -55V -17A 100mOhm 23.3nC" H 2900 1850 50  0001 L CNN "Description"
F 5 "4.69" H 2900 1750 50  0001 L CNN "Height"
F 6 "942-IRF9Z34NPBF" H 2900 1650 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Infineon-IR/IRF9Z34NPBF?qs=9%252BKlkBgLFf16a%2FvlD%252BMCtQ%3D%3D" H 2900 1550 50  0001 L CNN "Mouser Price/Stock"
F 8 "Infineon" H 2900 1450 50  0001 L CNN "Manufacturer_Name"
F 9 "IRF9Z34NPBF" H 2900 1350 50  0001 L CNN "Manufacturer_Part_Number"
	1    2450 2100
	0    1    -1   0   
$EndComp
Wire Wire Line
	2250 1800 1800 1800
$Comp
L power:GND #PWR025
U 1 1 6149AD72
P 1800 2150
F 0 "#PWR025" H 1800 1900 50  0001 C CNN
F 1 "GND" H 1805 1977 50  0000 C CNN
F 2 "" H 1800 2150 50  0001 C CNN
F 3 "" H 1800 2150 50  0001 C CNN
	1    1800 2150
	1    0    0    -1  
$EndComp
$Comp
L power:+VDC #PWR027
U 1 1 6149B3DD
P 5700 1600
F 0 "#PWR027" H 5700 1500 50  0001 C CNN
F 1 "+VDC" H 5700 1875 50  0000 C CNN
F 2 "" H 5700 1600 50  0001 C CNN
F 3 "" H 5700 1600 50  0001 C CNN
	1    5700 1600
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:TL071CP IC2
U 1 1 6149EB86
P 5650 2450
F 0 "IC2" H 6450 2715 50  0000 C CNN
F 1 "TL071CP" H 6450 2624 50  0000 C CNN
F 2 "DIP794W53P254L959H508Q8N" H 7100 2550 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071a.pdf" H 7100 2450 50  0001 L CNN
F 4 "Low-Noise JFET-Input General-Purpose Operational Amplifier" H 7100 2350 50  0001 L CNN "Description"
F 5 "5.08" H 7100 2250 50  0001 L CNN "Height"
F 6 "595-TL071CP" H 7100 2150 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Texas-Instruments/TL071CP/?qs=3FVjRv9mUZ%2FN1XJT5coqUQ%3D%3D" H 7100 2050 50  0001 L CNN "Mouser Price/Stock"
F 8 "Texas Instruments" H 7100 1950 50  0001 L CNN "Manufacturer_Name"
F 9 "TL071CP" H 7100 1850 50  0001 L CNN "Manufacturer_Part_Number"
	1    5650 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R25
U 1 1 614A1F25
P 2450 2350
F 0 "R25" H 2520 2396 50  0000 L CNN
F 1 "R" H 2520 2305 50  0000 L CNN
F 2 "" V 2380 2350 50  0001 C CNN
F 3 "~" H 2450 2350 50  0001 C CNN
	1    2450 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 614A2763
P 2450 2650
F 0 "#PWR026" H 2450 2400 50  0001 C CNN
F 1 "GND" H 2455 2477 50  0000 C CNN
F 2 "" H 2450 2650 50  0001 C CNN
F 3 "" H 2450 2650 50  0001 C CNN
	1    2450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2200 2450 2100
Wire Wire Line
	2450 2500 2450 2650
Wire Wire Line
	1800 2150 1800 1900
$Comp
L SamacSys_Parts:LM2597MX-5.0_NOPB IC1
U 1 1 614A2E08
P 3650 3900
F 0 "IC1" H 4800 4165 50  0000 C CNN
F 1 "LM2597MX-5.0_NOPB" H 4800 4074 50  0000 C CNN
F 2 "SOIC127P600X175-8N" H 5800 4000 50  0001 L CNN
F 3 "http://www.ti.com/lit/gpn/LM2597" H 5800 3900 50  0001 L CNN
F 4 "SIMPLE SWITCHER Power Converter 150 kHz 0.5A Step-Down Voltage Regulator" H 5800 3800 50  0001 L CNN "Description"
F 5 "1.75" H 5800 3700 50  0001 L CNN "Height"
F 6 "926-LM2597MX50NOPB" H 5800 3600 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=926-LM2597MX50NOPB" H 5800 3500 50  0001 L CNN "Mouser Price/Stock"
F 8 "Texas Instruments" H 5800 3400 50  0001 L CNN "Manufacturer_Name"
F 9 "LM2597MX-5.0/NOPB" H 5800 3300 50  0001 L CNN "Manufacturer_Part_Number"
	1    3650 3900
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:178.6165.0001 U1
U 1 1 614AAA6C
P 2850 1200
F 0 "U1" H 3250 1465 50  0000 C CNN
F 1 "178.6165.0001" H 3250 1374 50  0000 C CNN
F 2 "17861650001" H 3500 1300 50  0001 L CNN
F 3 "" H 3500 1200 50  0001 L CNN
F 4 "FLR PCB FUSE HOLDER FOR ATO STYLE BLADE FUSE RATED 58V" H 3500 1100 50  0001 L CNN "Description"
F 5 "17.5" H 3500 1000 50  0001 L CNN "Height"
F 6 "576-178.6165.0001" H 3500 900 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Littelfuse/17861650001?qs=CSLd874fYV1KI1oBGU5EQg%3D%3D" H 3500 800 50  0001 L CNN "Mouser Price/Stock"
F 8 "LITTELFUSE" H 3500 700 50  0001 L CNN "Manufacturer_Name"
F 9 "178.6165.0001" H 3500 600 50  0001 L CNN "Manufacturer_Part_Number"
	1    2850 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1300 2850 1200
Wire Wire Line
	3650 1300 3650 1200
Wire Wire Line
	3650 1200 3650 850 
Wire Wire Line
	2850 850  2850 1200
Connection ~ 3650 1200
Connection ~ 2850 1200
Wire Wire Line
	2850 1400 2850 1500
Wire Wire Line
	2850 1500 2850 1800
Wire Wire Line
	2850 1800 3650 1800
Wire Wire Line
	3650 1800 3650 1500
Connection ~ 2850 1500
Wire Wire Line
	3650 1500 3650 1400
Connection ~ 3650 1500
Connection ~ 2850 1800
Wire Wire Line
	2850 850  3650 850 
Text HLabel 7750 2450 2    50   Input ~ 0
BatteryVoltage
$EndSCHEMATC
