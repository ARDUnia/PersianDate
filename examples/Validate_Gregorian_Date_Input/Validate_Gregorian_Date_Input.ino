#include <PersianDate.h>

bool isValidGregorian(int y, int m, int d) {
  if (y < 1 || m < 1 || m > 12 || d < 1) return false;
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (PersianDate::isGregorianLeapYear(y)) daysInMonth[1] = 29;
  return d <= daysInMonth[m - 1];
}

void setup() {
  Serial.begin(9600);
  
  if (isValidGregorian(2026, 02, 29)) {
    Serial.println("Date is valid");
  } else {
    Serial.println("Date is invalid");  // 2026 is not leap, so Feb 29 is invalid
  }
}

void loop() { }
