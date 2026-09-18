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
  Serial.println(pd.getGregorianDateString()); // 2027/02/11
}

void loop() {}
```

---

## 📚 Function Reference (v2.1.2)

### 🏗️ Constructor and Setup

| Function                             | Description                      |
| ------------------------------------ | -------------------------------- |
| `PersianDate()`                      | Creates a new PersianDate object |
| `setGregorianDate(year, month, day)` | Sets the Gregorian date          |
| `setPersianDate(year, month, day)`   | Sets the Persian date            |

### 🔄 Conversion Methods

| Function                      | Description                                   |
| ----------------------------- | --------------------------------------------- |
| `convertGregorianToPersian()` | Converts the stored Gregorian date to Persian |
| `convertPersianToGregorian()` | Converts the stored Persian date to Gregorian |

### 📤 Date Getters

| Function              | Returns         |
| --------------------- | --------------- |
| `getGregorianYear()`  | Gregorian year  |
| `getGregorianMonth()` | Gregorian month |
| `getGregorianDay()`   | Gregorian day   |
| `getPersianYear()`    | Persian year    |
| `getPersianMonth()`   | Persian month   |
| `getPersianDay()`     | Persian day     |

### 📝 Formatted Outputs

| Function                          | Example output           |
| --------------------------------- | ------------------------ |
| `getGregorianDateString()`        | `2026/05/20`             |
| `getPersianDateString()`          | `1405/02/30`             |
| `getPersianDateStringWithNames()` | `30 Ordibehesht 1405`    |
| `getFullPersianDateString()`      | Persian weekday and date |

### 🛡️ Holiday Detection

| Function                      | Description                                                       |
| ----------------------------- | ----------------------------------------------------------------- |
| `isHoliday()`                 | Checks whether the Persian date stored in the object is a holiday |
| `isHoliday(year, month, day)` | Checks whether the specified Persian date is a holiday            |

Recognized holidays include:

* Every Friday
* Farvardin 1–4: Nowruz
* Farvardin 12: Islamic Republic Day
* Farvardin 13: Nature Day
* Ordibehesht 1: Workers' Day
* Khordad 14
* Khordad 15
* Bahman 22: Iranian Revolution Victory Day

Movable Islamic lunar holidays are not included because they require lunar calendar calculations.

### 🧰 Static Functions

| Function                                       | Description                                                       |
| ---------------------------------------------- | ----------------------------------------------------------------- |
| `gregorianToPersian(gy, gm, gd)`               | Converts a Gregorian date and returns a `Date`                    |
| `persianToGregorian(jy, jm, jd)`               | Converts a Persian date and returns a `Date`                      |
| `getPersianMonthName(month)`                   | Returns the full Persian month name                               |
| `getShortPersianMonthName(month)`              | Returns the abbreviated Persian month name                        |
| `getPersianWeekdayName(year, month, day)`      | Returns the Persian weekday name for a Gregorian date             |
| `getShortPersianWeekdayName(year, month, day)` | Returns the abbreviated Persian weekday name for a Gregorian date |
| `isPersianLeapYear(jy)`                        | Checks whether a Persian year is a leap year                      |
| `isGregorianLeapYear(gy)`                      | Checks whether a Gregorian year is a leap year                    |

Invalid conversion inputs return a `Date` containing `0, 0, 0`.

### 📐 Date Structure

```cpp
struct Date {
  int year;
  int month;
  int day;
};
```

---

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

## 📚 Project Documentation

* [Changelog](CHANGELOG.md)
* [Contributing Guidelines](CONTRIBUTING.md)
* [Security Policy](SECURITY.md)

## 📄 License

This library is released under the MIT License. See [LICENSE.txt](LICENSE.txt) for details.

## 👤 Author

**Hamidreza Milaninia**
ARDUnia Agency
[milaninia.h@gmail.com](mailto:milaninia.h@gmail.com)
[Personal Website](https://hrmnia.com/)

## 🤝 Contributing

Bug reports, test cases, documentation improvements, and pull requests are welcome. Please read the [Contributing Guidelines](CONTRIBUTING.md) before submitting a change.

## ⭐ Support

If you find PersianDate useful, please consider giving the repository a star.
