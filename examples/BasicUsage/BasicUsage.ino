/*
  BasicUsage.ino - Example for PersianDate library
  This sketch shows how to convert a Gregorian date to Persian (Jalali) date.
  by: Hamidreza Milaninia (ARDUnia)
*/

#include <Wire.h>
#include <RTClib.h>
#include <PersianDate.h>

RTC_DS1307 rtc;
PersianDate pd;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("RTC not found! Using compile time.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Example 1: using explicit date
  pd.setGregorianDate(2026, 5, 20);
  pd.convert();
  Serial.println("=== Explicit date 2026/5/20 ===");
  Serial.print("Jalali date (YYYY/MM/DD): "); Serial.println(pd.getDateString());
  Serial.print("Persian date string: "); Serial.println(pd.getPersianDateString());
  Serial.print("Full Persian date: "); Serial.println(pd.getFullPersianDateString());
  Serial.print("Month name: "); Serial.println(pd.getMonthName());
  Serial.print("Weekday: "); Serial.println(pd.getDayOfWeekName());

  // Example 2: using RTC now
  DateTime now = rtc.now();
  pd.setGregorianDate(now);
  pd.convert();
  Serial.println("\n=== Current RTC time ===");
  Serial.print("Gregorian: "); Serial.print(now.year()); Serial.print("/"); Serial.print(now.month()); Serial.print("/"); Serial.println(now.day());
  Serial.print("Jalali: "); Serial.println(pd.getPersianDateString());
}

void loop() {
  // nothing
}