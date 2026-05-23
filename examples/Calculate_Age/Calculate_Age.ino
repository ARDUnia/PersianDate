#include <PersianDate.h>

PersianDate pd;

int calculateAge(int birthYear, int birthMonth, int birthDay, int currentYear, int currentMonth, int currentDay) {
  int age = currentYear - birthYear;
  if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
    age--;
  }
  return age;
}

void setup() {
  Serial.begin(9600);
  
  // Birth date: 1360/05/15 (Persian)
  // Today: 1405/02/30 (Persian)
  int age = calculateAge(1360, 10, 10, 1405, 2, 30);
  Serial.print("Your age: ");
  Serial.print(age);
  Serial.println(" years");
}

void loop() { }
