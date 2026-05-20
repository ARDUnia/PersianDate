# PersianDate for Arduino

**Version:** 1.1.0  
**Author:** Hamidreza Milaninia (ARDUnia Agency)  
**Contact:** milaninia.h@gmail.com  

A lightweight, verified algorithm to convert Gregorian calendar dates to Persian (Jalali/Shamsi) dates.  
This library is optimized for Arduino (Uno, Nano, Mega, etc.) and works with RTClib DateTime objects.

## Features
- Convert Gregorian date to Jalali date (year, month, day)
- Get month name (full or short) in Persian (Latin transcription)
- Get weekday name (full or short) starting from Saturday
- Output formatted strings: `YYYY/MM/DD`, `DD MonthName YYYY`, `Weekday DD MonthName YYYY`
- Compatible with RTClib

## Installation
1. Download the ZIP from GitHub or Library Manager (search "PersianDate").
2. Install required dependency: **RTClib** by Adafruit.
3. Include the library in your sketch: `#include <PersianDate.h>`.

## Usage Example
```cpp
#include <Wire.h>
#include <RTClib.h>
#include <PersianDate.h>

RTC_DS1307 rtc;
PersianDate pd;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  // Set a known date (or use rtc.now())
  pd.setGregorianDate(2026, 5, 20);
  pd.convert();
  Serial.println(pd.getPersianDateString()); // prints "30 Ordibehesht 1405"
}

void loop() {}