#include <PersianDate.h>

void setup() {
  Serial.begin(9600);
  
  // Direct Gregorian to Persian using static function
  Date result = PersianDate::gregorianToPersian(2026, 5, 20);
  Serial.print("Persian date: 1405/");
  Serial.print(result.month);
  Serial.print("/");
  Serial.println(result.day);
  
  // Direct Persian to Gregorian
  Date miladi = PersianDate::persianToGregorian(1405, 2, 30);
  Serial.print("Gregorian date: 2026/");
  Serial.print(miladi.month);
  Serial.print("/");
  Serial.println(miladi.day);
  
  // Get Persian month name
  Serial.print("Second month name: ");
  Serial.println(PersianDate::getPersianMonthName(2));
  
  // Check if a Persian year is leap
  Serial.print("Is year 1404 a leap year? ");
  Serial.println(PersianDate::isPersianLeapYear(1404) ? "Yes" : "No");
}

void loop() { }