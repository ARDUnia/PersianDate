#include <PersianDate.h>

void setup() {
  Serial.begin(9600);
  
  // Weekday for May 20, 2026
  String weekday = PersianDate::getPersianWeekdayName(2026, 5, 20);
  Serial.print("May 20, 2026 is a ");
  Serial.print(weekday);
  Serial.println(".");
  
  // Short weekday name
  String shortWeekday = PersianDate::getShortPersianWeekdayName(2026, 5, 20);
  Serial.print("Short name: ");
  Serial.println(shortWeekday);
}

void loop() { }
