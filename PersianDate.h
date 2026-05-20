/*
  PersianDate.h - Library for Gregorian to Persian (Jalali) date conversion.
  Version 1.1.0
  Author: Hamidreza Milaninia (ARDUnia Agency) <milaninia.h@gmail.com>
  Algorithm provided by Hamidreza Milaninia.
  Released into the public domain or under MIT License (see LICENSE file).
*/

#ifndef PersianDate_h
#define PersianDate_h

#include "Arduino.h"
#include <RTClib.h>

class PersianDate {
public:
    PersianDate();
    void setGregorianDate(int year, int month, int day);
    void setGregorianDate(const DateTime& dt);
    void convert();

    int getYear();
    int getMonth();
    int getDay();
    String getMonthName();
    String getShortMonthName();
    int getDayOfWeek();      // 1=Saturday ... 7=Friday
    String getDayOfWeekName();
    String getShortDayOfWeekName();
    String getDateString();            // YYYY/MM/DD
    String getPersianDateString();     // DD MonthName YYYY
    String getFullPersianDateString(); // Weekday DD MonthName YYYY

private:
    int _gy, _gm, _gd;
    int _jy, _jm, _jd;
    int _dayOfWeek;
    bool _converted;

    static const char* _monthNames[12];
    static const char* _shortMonthNames[12];
    static const char* _dayNames[7];
    static const char* _shortDayNames[7];

    // Internal conversion helpers
    bool _isGregorianLeap(int year);
    int _getDayOfYear(int year, int month, int day);
    bool _isJalaliLeap(int jy);
    void _gregorianToJalali(int gy, int gm, int gd, int &jy, int &jm, int &jd);
    void _calculateDayOfWeek();
};

#endif