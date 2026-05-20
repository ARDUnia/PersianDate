/*
  PersianDate.cpp - Implementation of PersianDate library.
  Version 1.1.0
  Author: Hamidreza Milaninia (ARDUnia Agency)
  Algorithm by Hamidreza Milaninia.
*/

#include "PersianDate.h"

const char* PersianDate::_monthNames[12] = {
    "Farvardin", "Ordibehesht", "Khordad", "Tir", "Mordad", "Shahrivar",
    "Mehr", "Aban", "Azar", "Dey", "Bahman", "Esfand"
};
const char* PersianDate::_shortMonthNames[12] = {
    "Far", "Ord", "Kho", "Tir", "Mor", "Sha",
    "Meh", "Aba", "Aza", "Dey", "Bah", "Esf"
};
const char* PersianDate::_dayNames[7] = {
    "Saturday", "Sunday", "Monday", "Tuesday",
    "Wednesday", "Thursday", "Friday"
};
const char* PersianDate::_shortDayNames[7] = {
    "Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"
};

PersianDate::PersianDate() {
    _gy = 2000; _gm = 1; _gd = 1;
    _jy = 0; _jm = 0; _jd = 0;
    _dayOfWeek = 0;
    _converted = false;
}

void PersianDate::setGregorianDate(int year, int month, int day) {
    _gy = year; _gm = month; _gd = day;
    _converted = false;
}
void PersianDate::setGregorianDate(const DateTime& dt) {
    _gy = dt.year(); _gm = dt.month(); _gd = dt.day();
    _converted = false;
}

bool PersianDate::_isGregorianLeap(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int PersianDate::_getDayOfYear(int year, int month, int day) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (_isGregorianLeap(year)) daysInMonth[1] = 29;
    int doy = 0;
    for (int i = 0; i < month - 1; i++) doy += daysInMonth[i];
    doy += day;
    return doy;
}

bool PersianDate::_isJalaliLeap(int jy) {
    if (jy < 1372) return (jy % 4 == 2);
    else return (jy % 4 == 1);
}

void PersianDate::_gregorianToJalali(int gy, int gm, int gd, int &jy, int &jm, int &jd) {
    int doy = _getDayOfYear(gy, gm, gd);
    bool gregLeap = _isGregorianLeap(gy);
    int threshold = gregLeap ? 81 : 80;   // First day of Farvardin = March 21 (day 80) or 81 in leap

    // Year calculation (Milaninia algorithm)
    if (doy < threshold) jy = gy - 622;
    else jy = gy - 621;

    // Day-of-year in Jalali calendar
    int jalaliDayOfYear;
    if (doy >= threshold) {
        jalaliDayOfYear = doy - threshold + 1;
    } else {
        int prevYear = gy - 1;
        int prevYearDays = _isGregorianLeap(prevYear) ? 366 : 365;
        jalaliDayOfYear = doy + (prevYearDays - threshold + 1);
    }

    // Month days for Jalali
    int monthDays[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
    if (_isJalaliLeap(jy)) monthDays[11] = 30;   // Esfand 30 days in leap

    int remain = jalaliDayOfYear;
    for (int i = 0; i < 12; i++) {
        if (remain <= monthDays[i]) {
            jm = i + 1;
            jd = remain;
            return;
        }
        remain -= monthDays[i];
    }
    // fallback (should never reach)
    jm = 12; jd = 30;
}

void PersianDate::_calculateDayOfWeek() {
    // Using Gregorian to JDN formula (only for weekday)
    int y = _gy, m = _gm, d = _gd;
    if (m < 3) {
        y--;
        m += 12;
    }
    int a = y / 100;
    int b = a / 4;
    int c = 2 - a + b;
    int e = (36525 * (y + 4716)) / 100;
    int f = (306 * (m + 1)) / 10;
    long jdn = c + d + e + f - 1524;
    // 1 Jan 2000 = 2451545 JDN = Saturday (day 1 in our calendar)
    int w = (jdn + 2) % 7; // 0=Saturday, 6=Friday
    _dayOfWeek = w + 1;    // 1=Sat ... 7=Fri
}

void PersianDate::convert() {
    if (_converted) return;
    _gregorianToJalali(_gy, _gm, _gd, _jy, _jm, _jd);
    _calculateDayOfWeek();
    _converted = true;
}

int PersianDate::getYear() { if (!_converted) convert(); return _jy; }
int PersianDate::getMonth() { if (!_converted) convert(); return _jm; }
int PersianDate::getDay() { if (!_converted) convert(); return _jd; }

String PersianDate::getMonthName() {
    if (!_converted) convert();
    if (_jm >= 1 && _jm <= 12) return String(_monthNames[_jm-1]);
    return "";
}
String PersianDate::getShortMonthName() {
    if (!_converted) convert();
    if (_jm >= 1 && _jm <= 12) return String(_shortMonthNames[_jm-1]);
    return "";
}
int PersianDate::getDayOfWeek() { if (!_converted) convert(); return _dayOfWeek; }
String PersianDate::getDayOfWeekName() {
    if (!_converted) convert();
    if (_dayOfWeek >= 1 && _dayOfWeek <= 7) return String(_dayNames[_dayOfWeek-1]);
    return "";
}
String PersianDate::getShortDayOfWeekName() {
    if (!_converted) convert();
    if (_dayOfWeek >= 1 && _dayOfWeek <= 7) return String(_shortDayNames[_dayOfWeek-1]);
    return "";
}
String PersianDate::getDateString() {
    if (!_converted) convert();
    char buf[12];
    sprintf(buf, "%04d/%02d/%02d", _jy, _jm, _jd);
    return String(buf);
}
String PersianDate::getPersianDateString() {
    if (!_converted) convert();
    char buf[30];
    sprintf(buf, "%d %s %04d", _jd, getMonthName().c_str(), _jy);
    return String(buf);
}
String PersianDate::getFullPersianDateString() {
    if (!_converted) convert();
    char buf[50];
    sprintf(buf, "%s %d %s %04d", getDayOfWeekName().c_str(), _jd, getMonthName().c_str(), _jy);
    return String(buf);
}