#include <iostream>
#include "PersianDate.h"

static int failures = 0;

void expectDate(
    const char* label,
    Date actual,
    int year,
    int month,
    int day) {

  if (actual.year != year ||
      actual.month != month ||
      actual.day != day) {

    std::cerr << "FAIL: " << label << " expected "
              << year << "/" << month << "/" << day
              << " but got "
              << actual.year << "/"
              << actual.month << "/"
              << actual.day << std::endl;

    failures++;
  }
}

void expectBool(
    const char* label,
    bool actual,
    bool expected) {

  if (actual != expected) {
    std::cerr << "FAIL: " << label
              << " expected " << expected
              << " but got " << actual
              << std::endl;

    failures++;
  }
}

int main() {
  // Gregorian to Persian
  expectDate(
      "2024-03-20",
      PersianDate::gregorianToPersian(2024, 3, 20),
      1403, 1, 1);

  expectDate(
      "2025-03-20",
      PersianDate::gregorianToPersian(2025, 3, 20),
      1403, 12, 30);

  expectDate(
      "2026-03-21",
      PersianDate::gregorianToPersian(2026, 3, 21),
      1405, 1, 1);

  expectDate(
      "2026-05-20",
      PersianDate::gregorianToPersian(2026, 5, 20),
      1405, 2, 30);

  // Persian to Gregorian
  expectDate(
      "1403-01-01",
      PersianDate::persianToGregorian(1403, 1, 1),
      2024, 3, 20);

  expectDate(
      "1403-12-30",
      PersianDate::persianToGregorian(1403, 12, 30),
      2025, 3, 20);

  expectDate(
      "1405-01-01",
      PersianDate::persianToGregorian(1405, 1, 1),
      2026, 3, 21);

  expectDate(
      "1405-11-22",
      PersianDate::persianToGregorian(1405, 11, 22),
      2027, 2, 11);

  // Persian leap years
  expectBool(
      "1399 is leap",
      PersianDate::isPersianLeapYear(1399),
      true);

  expectBool(
      "1400 is not leap",
      PersianDate::isPersianLeapYear(1400),
      false);

  expectBool(
      "1403 is leap",
      PersianDate::isPersianLeapYear(1403),
      true);

  expectBool(
      "1404 is not leap",
      PersianDate::isPersianLeapYear(1404),
      false);

  // Holiday detection
  expectBool(
      "Nowruz is holiday",
      PersianDate::isHoliday(1405, 1, 1),
      true);

  expectBool(
      "1405-06-27 is Friday",
      PersianDate::isHoliday(1405, 6, 27),
      true);

  expectBool(
      "1405-06-26 is Thursday",
      PersianDate::isHoliday(1405, 6, 26),
      false);

  if (failures != 0) {
    std::cerr << failures
              << " test(s) failed."
              << std::endl;
    return 1;
  }

  std::cout
      << "All PersianDate tests passed."
      << std::endl;

  return 0;
}
