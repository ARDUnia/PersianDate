#include <PersianDate.h>

PersianDate pd;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Here you could read current time from RTC or compile time
  // For demo, use a fixed date
  pd.setGregorianDate(2026, 5, 20);
  pd.convertGregorianToPersian();
  
  Serial.print("\r");
  Serial.print(pd.getFullPersianDateString());
  delay(1000);
}