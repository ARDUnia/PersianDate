#include <PersianDate.h>

PersianDate pd;

void setup() {
  Serial.begin(9600);
  
  // Set a Persian (Jalali) date
  pd.setPersianDate(1405, 2, 30);  // 30 Ordibehesht 1405
  
  // Convert to Gregorian
  pd.convertPersianToGregorian();
  
  Serial.println("=== Persian to Gregorian ===");
  Serial.print("Persian date: 1405/02/30");
  Serial.print(" -> Gregorian date: ");
  Serial.println(pd.getGregorianDateString());
}

void loop() { }