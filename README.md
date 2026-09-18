# PersianDate Library for Arduino
[![Arduino CI](https://github.com/ARDUnia/PersianDate/actions/workflows/arduino-ci.yml/badge.svg)](https://github.com/ARDUnia/PersianDate/actions/workflows/arduino-ci.yml)
[![Native Tests](https://github.com/ARDUnia/PersianDate/actions/workflows/native-tests.yml/badge.svg)](https://github.com/ARDUnia/PersianDate/actions/workflows/native-tests.yml)
[![Latest Release](https://img.shields.io/github/v/release/ARDUnia/PersianDate)](https://github.com/ARDUnia/PersianDate/releases)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE.txt)

**Version:** 2.1.2  
**Author:** Hamidreza Milaninia (ARDUnia Agency)  
**Contact:** milaninia.h@gmail.com  

[Hamidreza Milaninia – Personal Website](https://hrmnia.com/)

A complete, lightweight, and **standalone** library for converting Gregorian (Miladi) dates to Persian (Jalali/Shamsi) dates and **vice versa**, featuring **official Persian calendar holiday detection** including Fridays.

---

## ✨ Features

- ✅ Convert **Gregorian → Persian (Jalali)** with a verified algorithm
- ✅ Convert **Persian (Jalali) → Gregorian** (reverse)
- ✅ **Official fixed holidays** detection (Nowruz, Revolution Day, etc.)
- ✅ **Fridays** recognized as holidays
- ✅ **Static functions** for direct conversion without creating an object
- ✅ **Persian month and weekday names** (full and short)
- ✅ Leap year detection (both calendars)
- ✅ **No external dependencies** (standalone, does not require RTClib)
- ✅ Lightweight and fast, suitable for AVR microcontrollers

---

## 📦 Installation

### Arduino Library Manager (recommended)
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search for **"PersianDate"**
4. Install version **2.1.2**

### Manual installation
1. Download the ZIP from [GitHub](https://github.com/ARDUnia/PersianDate)
2. In Arduino IDE: **Sketch → Include Library → Add .ZIP Library...**
3. Select the downloaded ZIP file

---

## 🚀 Quick Start

```cpp
#include <PersianDate.h>

PersianDate pd;

void setup() {
  Serial.begin(9600);
  
  // Gregorian to Persian
  pd.setGregorianDate(2026, 5, 20);
  pd.convertGregorianToPersian();
  Serial.println(pd.getPersianDateStringWithNames()); // 30 Ordibehesht 1405
  
  // Check holiday
  if (pd.isHoliday()) {
    Serial.println("Today is a holiday!");
  } else {
    Serial.println("Today is not a holiday.");
  }
  
  // Persian to Gregorian
  pd.setPersianDate(1405, 11, 22);
  pd.convertPersianToGregorian();
  Serial.println(pd.getGregorianDateString()); // 2027/02/11 (approx)
}

void loop() {}
```

---

## 📚 Function Reference (v2.1.2)
🏗️ Constructor & Setup
Function	Description
PersianDate()	Constructor – creates a new PersianDate object

📥 Setting Dates
Function	Parameters	Description
setGregorianDate(year, month, day)	year, month, day	Sets Gregorian date
setPersianDate(year, month, day)	year, month, day	Sets Persian (Jalali) date

🔄 Conversion Methods
Function	Description
convertGregorianToPersian()	Converts set Gregorian date to Persian
convertPersianToGregorian()	Converts set Persian date to Gregorian

📤 Getters (after conversion)
Function	Returns	Example
getGregorianYear()	int	2026
getGregorianMonth()	int	5
getGregorianDay()	int	20
getPersianYear()	int	1405
getPersianMonth()	int	2
getPersianDay()	int	30

📝 Formatted String Outputs
Function	Example Output
getGregorianDateString()	2026/05/20
getPersianDateString()	1405/02/30
getPersianDateStringWithNames()	30 Ordibehesht 1405
getFullPersianDateString()	Tuesday 30 Ordibehesht 1405

🛡️ Holiday Detection (NEW in v2.1.1)
Function	Description
bool isHoliday()	(non-static) Checks if the current Persian date stored in the object is a holiday
static bool isHoliday(year, month, day)	(static) Checks if a given Persian date is a holiday
Recognized holidays:

Fridays (every Friday)

Fixed official holidays:
Farvardin 1–4 (Nowruz – Persian New Year)
Farvardin 12 (Islamic Republic Day)
Farvardin 13 (Nature's Day)
Ordibehesht 1 (Workers' Day)
Khordad 14 (Death of Khomeini)
Khordad 15 (Khordad 15 Uprising)
Bahman 22 (Iranian Revolution Victory Day)

Note: Movable Islamic (Lunar) holidays (Eid al-Fitr, Eid al-Adha, Ashura, etc.) are not included in this version. They require lunar calendar calculations.

🧰 Static Functions (no object needed)
Function	Description
gregorianToPersian(gy,gm,gd)	Direct Gregorian → Persian conversion, returns Date
persianToGregorian(jy,jm,jd)	Direct Persian → Gregorian conversion
getPersianMonthName(month)	Persian month name (e.g., Ordibehesht)
getShortPersianMonthName(month)	Short Persian month name (e.g., Ord)
getPersianWeekdayName(year,month,day)	Persian weekday name (e.g., Tuesday)
getShortPersianWeekdayName(year,month,day)	Short weekday name (e.g., Tue)
isPersianLeapYear(jy)	Checks if a Persian year is leap
isGregorianLeapYear(gy)	Checks if a Gregorian year is leap
isHoliday(year,month,day)	Checks if a given Persian date is a holiday

📐 Date Structure
cpp
struct Date {
  int year;
  int month;
  int day;
};

---------------------------------------------

## 🔧 Algorithm

The Gregorian-to-Persian and Persian-to-Gregorian conversions use the **Milaninia day-of-year algorithm**, developed by the library author. The algorithm preserves its original lightweight structure and does not use Julian Day Numbers (JDN).

Version 2.1.2 improves the original implementation with:

* Accurate Gregorian and Persian day-of-year calculations
* Correct Nowruz boundary handling
* Persian leap-year detection using the 33-year cycle
* Symmetric Persian-to-Gregorian conversion
* Round-trip conversion validation
* Correct weekday and Friday holiday detection
* Input validation for Gregorian and Persian dates

The implementation has been validated for every Gregorian date from **2000-01-01 through 2100-12-31**, including known Nowruz boundaries, leap years, weekdays, holidays, and round-trip conversions.

## 📊 Version History

| Version | Description                                                                                                                                                  |
| ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| 2.1.2   | Fixed Nowruz boundaries, Persian leap-year calculation, reverse conversion, weekday and Friday holiday detection; added input validation and automated tests |
| 2.1.1   | Added official Iranian holiday detection for fixed dates and Fridays                                                                                         |
| 2.0.0   | Complete rewrite: removed RTClib dependency and added reverse conversion and static functions                                                                |
| 1.1.0   | First public release with RTClib dependency                                                                                                                  |

📄 License
This library is released under the MIT License. See the LICENSE file for details.

👤 Author
Hamidreza Milaninia
ARDUnia Agency
milaninia.h@gmail.com

🤝 Contributing
Bug reports, feature requests, and pull requests are welcome via GitHub.

⭐ Support
If you find this library useful, please give it a star on GitHub!

