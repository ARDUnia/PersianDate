/*
  PersianDate.h - Library for Gregorian to Persian (Jalali) date conversion and vice versa.
  Version 2.1.0
  Author: Hamidreza Milaninia (ARDUnia Agency)
  This library is independent of RTClib and can convert both ways.
*/

#ifndef PersianDate_h
#define PersianDate_h

#include "Arduino.h"

struct Date {
  int year;
  int month;
  int day;
};

class PersianDate {
public:
  PersianDate();

  void setGregorianDate(int year, int month, int day);
  void setPersianDate(int year, int month, int day);

  void convertGregorianToPersian();
  void convertPersianToGregorian();

  int getGregorianYear();
  int getGregorianMonth();
  int getGregorianDay();
  int getPersianYear();
  int getPersianMonth();
  int getPersianDay();

  String getGregorianDateString();
  String getPersianDateString();
  String getPersianDateStringWithNames();
  String getFullPersianDateString();

  // Holiday functions
  bool isHoliday();                          // non-static
  static bool isHoliday(int year, int month, int day); // static

  // Static conversion functions
  static Date gregorianToPersian(int gy, int gm, int gd);
  static Date persianToGregorian(int jy, int jm, int jd);
  static String getPersianMonthName(int month);
  static String getShortPersianMonthName(int month);
  static String getPersianWeekdayName(int year, int month, int day);
  static String getShortPersianWeekdayName(int year, int month, int day);
  static bool isPersianLeapYear(int jy);
  static bool isGregorianLeapYear(int gy);

private:
  int _gy, _gm, _gd;
  int _jy, _jm, _jd;

  static const char* _persianMonthNames[12];
  static const char* _shortPersianMonthNames[12];
  static const char* _persianWeekdayNames[7];
  static const char* _shortPersianWeekdayNames[7];

  void _clear();

  // Helper static functions (declared here)
  static long _gregorianToJdn(int y, int m, int d);
  static int _getWeekdayIndex(int year, int month, int day);
  static bool _isFixedHoliday(int month, int day);
};

#endif
