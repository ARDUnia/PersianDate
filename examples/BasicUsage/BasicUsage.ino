#include <PersianDate.h>

PersianDate pd;

void setup() {
  Serial.begin(9600);
  
  // ========== تبدیل میلادی به شمسی ==========
  pd.setGregorianDate(2026, 5, 20);
  pd.convertGregorianToPersian();
  
  Serial.println("=== Gregorian to Persian ===");
  Serial.print("Input (Gregorian): "); Serial.println(pd.getGregorianDateString());
  Serial.print("Output (Persian): "); Serial.println(pd.getPersianDateString());
  Serial.print("With names: "); Serial.println(pd.getPersianDateStringWithNames());
  Serial.print("Full: "); Serial.println(pd.getFullPersianDateString());
  
  // ========== تبدیل شمسی به میلادی ==========
  pd.setPersianDate(1405, 2, 30);
  pd.convertPersianToGregorian();
  
  Serial.println("\n=== Persian to Gregorian ===");
  Serial.print("Input (Persian): 1405/02/30");
  Serial.print("Output (Gregorian): "); Serial.println(pd.getGregorianDateString());
  
  // ========== استفاده مستقیم از توابع استاتیک ==========
  Date result = PersianDate::gregorianToPersian(2026, 5, 20);
  Serial.println("\n=== Static function ===");
  Serial.print("2026/5/20 -> Persian: ");
  Serial.print(result.year); Serial.print("/"); Serial.print(result.month); Serial.print("/"); Serial.println(result.day);
}

void loop() {}