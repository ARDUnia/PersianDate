# PersianDate for Arduino

**Version:** 2.0  

**Author:** Hamidreza Milaninia (ARDUnia Agency)  
**Contact:** milaninia.h@gmail.com  

A complete, lightweight, and **independent** library for converting Gregorian (Miladi) dates to Persian (Jalali/Shamsi) dates and **vice versa**. No external dependencies (does not require RTClib).

---

## ✨ Features

- ✅ Convert **Gregorian → Persian (Jalali)**
- ✅ Convert **Persian (Jalali) → Gregorian**
- ✅ Static functions (no object instance needed)
- ✅ Persian month names (full & short)
- ✅ Persian weekday names (Saturday to Friday)
- ✅ Leap year detection (both calendars)
- ✅ Multiple output formats
- ✅ No external dependencies (only Arduino.h)
- ✅ Lightweight and fast

---

## 📦 Installation

### Arduino Library Manager (recommended)
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search for **"PersianDate"**
4. Click **Install**

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
  Serial.println(pd.getPersianDateString()); // 1405/02/30
  
  // Persian to Gregorian
  pd.setPersianDate(1405, 2, 30);
  pd.convertPersianToGregorian();
  Serial.println(pd.getGregorianDateString()); // 2026/05/20
}

void loop() {}
