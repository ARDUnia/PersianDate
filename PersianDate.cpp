#include "PersianDate.h"
#include <Arduino.h>

// ========== جداول نام‌های ماه‌های شمسی (فارسی) ==========
const char* PersianDate::_persianMonthNames[12] = {
  "فروردین", "اردیبهشت", "خرداد", "تیر", "مرداد", "شهریور",
  "مهر", "آبان", "آذر", "دی", "بهمن", "اسفند"
};

const char* PersianDate::_shortPersianMonthNames[12] = {
  "فر", "ار", "خر", "تی", "مر", "شه",
  "مه", "آبا", "آذ", "دی", "به", "اس"
};

// ========== جداول نام‌های روزهای هفته (فارسی) ==========
const char* PersianDate::_persianWeekdayNames[7] = {
  "شنبه", "یکشنبه", "دوشنبه", "سه‌شنبه", "چهارشنبه", "پنجشنبه", "جمعه"
};

const char* PersianDate::_shortPersianWeekdayNames[7] = {
  "ش", "ی", "د", "س", "چ", "پ", "ج"
};

// ========== تعطیلات رسمی ثابت (ماه, روز) ==========
static const byte FIXED_HOLIDAYS[][2] = {
  {1,1},{1,2},{1,3},{1,4},{1,12},{1,13},  // فروردین
  {2,1},                                   // اردیبهشت
  {3,14},{3,15},                           // خرداد
  {11,22}                                  // بهمن
};
static const byte NUM_FIXED_HOLIDAYS = sizeof(FIXED_HOLIDAYS) / sizeof(FIXED_HOLIDAYS[0]);

// ========== سازنده ==========
PersianDate::PersianDate() {
  _clear();
}

void PersianDate::_clear() {
  _gy = 2000; _gm = 1; _gd = 1;
  _jy = 1378; _jm = 10; _jd = 11;
}

// ========== تنظیم تاریخ ==========
void PersianDate::setGregorianDate(int year, int month, int day) {
  _gy = year; _gm = month; _gd = day;
}

void PersianDate::setPersianDate(int year, int month, int day) {
  _jy = year; _jm = month; _jd = day;
}

// ========== تبدیل میلادی به شمسی (غیراستاتیک) ==========
void PersianDate::convertGregorianToPersian() {
  Date result = gregorianToPersian(_gy, _gm, _gd);
  _jy = result.year;
  _jm = result.month;
  _jd = result.day;
}

// ========== تبدیل شمسی به میلادی (غیراستاتیک) ==========
void PersianDate::convertPersianToGregorian() {
  Date result = persianToGregorian(_jy, _jm, _jd);
  _gy = result.year;
  _gm = result.month;
  _gd = result.day;
}

// ========== توابع استاتیک عمومی ==========

Date PersianDate::gregorianToPersian(int gy, int gm, int gd) {
  if (!_isValidGregorianDate(gy, gm, gd)) return {0, 0, 0};

  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (isGregorianLeapYear(gy)) daysInMonth[1] = 29;
  int doy = gd;
  for (int i = 0; i < gm - 1; i++) doy += daysInMonth[i];

  int threshold = _farvardinStartDayOfYear(gy);

  int jy;
  if (doy < threshold) jy = gy - 622;
  else jy = gy - 621;

  int jalaliDayOfYear;
  if (doy >= threshold) {
    jalaliDayOfYear = doy - threshold + 1;
  } else {
    int prevYear = gy - 1;
    int previousThreshold = _farvardinStartDayOfYear(prevYear);
    jalaliDayOfYear = doy + _daysInGregorianYear(prevYear)
                           - previousThreshold + 1;
  }

  int monthDays[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
  if (isPersianLeapYear(jy)) monthDays[11] = 30;

  int remain = jalaliDayOfYear;
  for (int i = 0; i < 12; i++) {
    if (remain <= monthDays[i]) {
      return {jy, i + 1, remain};
    }
    remain -= monthDays[i];
  }
  return {0, 0, 0};
}

Date PersianDate::persianToGregorian(int jy, int jm, int jd) {
  if (!_isValidPersianDate(jy, jm, jd)) return {0, 0, 0};

  int monthDays[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
  if (isPersianLeapYear(jy)) monthDays[11] = 30;
  int jalaliDayOfYear = jd;
  for (int i = 0; i < jm - 1; i++) jalaliDayOfYear += monthDays[i];

  int gy = jy + 621;
  int doy = jalaliDayOfYear + _farvardinStartDayOfYear(gy) - 1;

  if (doy > _daysInGregorianYear(gy)) {
    doy -= _daysInGregorianYear(gy);
    gy++;
  }

  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (isGregorianLeapYear(gy)) daysInMonth[1] = 29;

  int gm = 1;
  while (gm <= 12 && doy > daysInMonth[gm - 1]) {
    doy -= daysInMonth[gm - 1];
    gm++;
  }

  if (gm > 12) return {0, 0, 0};
  return {gy, gm, doy};
}

int PersianDate::_daysInGregorianYear(int year) {
  return isGregorianLeapYear(year) ? 366 : 365;
}

// The Milaninia day-of-year method uses 2024-03-20 (1403-01-01) as an
// anchor and moves between years using the exact lengths of both calendars.
int PersianDate::_farvardinStartDayOfYear(int gregorianYear) {
  const int anchorGregorianYear = 2024;
  int threshold = 80;  // 2024-03-20 in a Gregorian leap year

  if (gregorianYear > anchorGregorianYear) {
    for (int year = anchorGregorianYear + 1; year <= gregorianYear; year++) {
      int previousPersianYear = year - 622;
      threshold += (isPersianLeapYear(previousPersianYear) ? 366 : 365)
                 - _daysInGregorianYear(year - 1);
    }
  } else if (gregorianYear < anchorGregorianYear) {
    for (int year = anchorGregorianYear; year > gregorianYear; year--) {
      int previousPersianYear = year - 622;
      threshold -= (isPersianLeapYear(previousPersianYear) ? 366 : 365)
                 - _daysInGregorianYear(year - 1);
    }
  }

  return threshold;
}

bool PersianDate::_isValidGregorianDate(int year, int month, int day) {
  if (year < 2000 || year > 2100 || month < 1 || month > 12 || day < 1) {
    return false;
  }
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (isGregorianLeapYear(year)) daysInMonth[1] = 29;
  return day <= daysInMonth[month - 1];
}

bool PersianDate::_isValidPersianDate(int year, int month, int day) {
  if (year < 1378 || year > 1479 || month < 1 || month > 12 || day < 1) {
    return false;
  }
  int maxDay = month <= 6 ? 31
             : month <= 11 ? 30
             : isPersianLeapYear(year) ? 30 : 29;
  return day <= maxDay;
}

// ========== محاسبه JDN (برای روز هفته) ==========
long PersianDate::_gregorianToJdn(int y, int m, int d) {
  int a = (14 - m) / 12;
  long yy = y + 4800 - a;
  int mm = m + 12 * a - 3;
  return d + (153 * mm + 2) / 5 + 365 * yy + yy / 4 - yy / 100 + yy / 400 - 32045;
}

// ========== محاسبه اندیس روز هفته (0=شنبه تا 6=جمعه) با JDN ==========
int PersianDate::_getWeekdayIndex(int year, int month, int day) {
  long jdn = _gregorianToJdn(year, month, day);
  // 1 Jan 2000 = 2451545 JDN = Saturday
  int w = (jdn + 2) % 7; // 0=Saturday, 1=Sunday, ..., 6=Friday
  return w;
}

String PersianDate::getPersianWeekdayName(int year, int month, int day) {
  int idx = _getWeekdayIndex(year, month, day);
  if (idx >= 0 && idx <= 6) return String(_persianWeekdayNames[idx]);
  return "";
}

String PersianDate::getShortPersianWeekdayName(int year, int month, int day) {
  int idx = _getWeekdayIndex(year, month, day);
  if (idx >= 0 && idx <= 6) return String(_shortPersianWeekdayNames[idx]);
  return "";
}

// ========== توابع جانبی استاتیک ==========
String PersianDate::getPersianMonthName(int month) {
  if (month >= 1 && month <= 12) return String(_persianMonthNames[month - 1]);
  return "";
}

String PersianDate::getShortPersianMonthName(int month) {
  if (month >= 1 && month <= 12) return String(_shortPersianMonthNames[month - 1]);
  return "";
}

bool PersianDate::_isFixedHoliday(int month, int day) {
  for (byte i = 0; i < NUM_FIXED_HOLIDAYS; i++) {
    if (FIXED_HOLIDAYS[i][0] == month && FIXED_HOLIDAYS[i][1] == day) {
      return true;
    }
  }
  return false;
}

bool PersianDate::isHoliday(int year, int month, int day) {
  if (!_isValidPersianDate(year, month, day)) return false;
  Date gregorian = persianToGregorian(year, month, day);
  String wd = getPersianWeekdayName(
      gregorian.year, gregorian.month, gregorian.day);
  if (wd == "جمعه") return true;
  if (_isFixedHoliday(month, day)) return true;
  return false;
}

bool PersianDate::isHoliday() {
  return isHoliday(_jy, _jm, _jd);
}

bool PersianDate::isPersianLeapYear(int jy) {
  int remainder = jy % 33;
  if (remainder < 0) remainder += 33;
  return remainder == 1 || remainder == 5 || remainder == 9 ||
         remainder == 13 || remainder == 17 || remainder == 22 ||
         remainder == 26 || remainder == 30;
}

bool PersianDate::isGregorianLeapYear(int gy) {
  return (gy % 4 == 0 && (gy % 100 != 0 || gy % 400 == 0));
}

// ========== توابع دریافت (غیراستاتیک) ==========
int PersianDate::getGregorianYear() { return _gy; }
int PersianDate::getGregorianMonth() { return _gm; }
int PersianDate::getGregorianDay() { return _gd; }
int PersianDate::getPersianYear() { return _jy; }
int PersianDate::getPersianMonth() { return _jm; }
int PersianDate::getPersianDay() { return _jd; }

String PersianDate::getGregorianDateString() {
  char buf[12];
  sprintf(buf, "%04d/%02d/%02d", _gy, _gm, _gd);
  return String(buf);
}

String PersianDate::getPersianDateString() {
  char buf[12];
  sprintf(buf, "%04d/%02d/%02d", _jy, _jm, _jd);
  return String(buf);
}

String PersianDate::getPersianDateStringWithNames() {
  char buf[30];
  sprintf(buf, "%d %s %04d", _jd, getPersianMonthName(_jm).c_str(), _jy);
  return String(buf);
}

String PersianDate::getFullPersianDateString() {
  char buf[50];
  sprintf(buf, "%s %d %s %04d", 
          getPersianWeekdayName(_gy, _gm, _gd).c_str(), 
          _jd, 
          getPersianMonthName(_jm).c_str(), 
          _jy);
  return String(buf);
}
