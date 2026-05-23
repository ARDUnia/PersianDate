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
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (isGregorianLeapYear(gy)) daysInMonth[1] = 29;
  int doy = gd;
  for (int i = 0; i < gm - 1; i++) doy += daysInMonth[i];

  bool gregLeap = isGregorianLeapYear(gy);
  int threshold = gregLeap ? 81 : 80;

  int jy;
  if (doy < threshold) jy = gy - 622;
  else jy = gy - 621;

  int jalaliDayOfYear;
  if (doy >= threshold) {
    jalaliDayOfYear = doy - threshold + 1;
  } else {
    int prevYear = gy - 1;
    int prevYearDays = isGregorianLeapYear(prevYear) ? 366 : 365;
    jalaliDayOfYear = doy + (prevYearDays - threshold + 1);
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
  return {jy, 12, 30};
}

// تبدیل شمسی به میلادی با استفاده از الگوریتم معکوس
Date PersianDate::persianToGregorian(int jy, int jm, int jd) {
  int monthDays[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
  if (isPersianLeapYear(jy)) monthDays[11] = 30;
  int jalaliDayOfYear = jd;
  for (int i = 0; i < jm - 1; i++) jalaliDayOfYear += monthDays[i];
  
  int candidates[2] = {jy + 621, jy + 622};
  for (int idx = 0; idx < 2; idx++) {
    int gy = candidates[idx];
    bool gregLeap = isGregorianLeapYear(gy);
    int threshold = gregLeap ? 81 : 80;
    int doy = jalaliDayOfYear + threshold - 1;
    
    int maxDays = gregLeap ? 366 : 365;
    if (doy < 1 || doy > maxDays) continue;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (gregLeap) daysInMonth[1] = 29;
    int gm = 0, gd = doy;
    for (int i = 0; i < 12; i++) {
      if (gd <= daysInMonth[i]) {
        gm = i + 1;
        break;
      }
      gd -= daysInMonth[i];
    }
    
    Date check = gregorianToPersian(gy, gm, gd);
    if (check.year == jy && check.month == jm && check.day == jd) {
      return {gy, gm, gd};
    }
  }
  return {0, 0, 0};
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

// محاسبه روز هفته با الگوریتم زلر (خروجی فارسی)
String PersianDate::getPersianWeekdayName(int year, int month, int day) {
  int y = year, m = month, d = day;
  if (m < 3) {
    y--;
    m += 12;
  }
  int K = y % 100;
  int J = y / 100;
  int h = (d + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
  // h: 0=شنبه, 1=یکشنبه, 2=دوشنبه, 3=سه‌شنبه, 4=چهارشنبه, 5=پنجشنبه, 6=جمعه
  if (h >= 0 && h <= 6) return String(_persianWeekdayNames[h]);
  return "";
}

String PersianDate::getShortPersianWeekdayName(int year, int month, int day) {
  int y = year, m = month, d = day;
  if (m < 3) {
    y--;
    m += 12;
  }
  int K = y % 100;
  int J = y / 100;
  int h = (d + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
  if (h >= 0 && h <= 6) return String(_shortPersianWeekdayNames[h]);
  return "";
}

bool PersianDate::isPersianLeapYear(int jy) {
  if (jy < 1372) return (jy % 4 == 2);
  else return (jy % 4 == 1);
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