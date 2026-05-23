#include <PersianDate.h>

PersianDate pd;

void setup() {
  Serial.begin(9600);
  
  // Set a custom Gregorian date
  pd.setGregorianDate(2026, 05, 24);
  
  // Convert to Persian (Jalali)
  pd.convertGregorianToPersian();
  
  // Display results
  Serial.println("=== Gregorian to Persian ===");
  Serial.print("Gregorian date: ");
  Serial.println(pd.getGregorianDateString());
  Serial.print("Persian date (numeric): ");
  Serial.println(pd.getPersianDateString());
  Serial.print("Persian date with month name: ");
  Serial.println(pd.getPersianDateStringWithNames());
  Serial.print("Full Persian date with weekday: ");
  Serial.println(pd.getFullPersianDateString());
}

void loop() { }
