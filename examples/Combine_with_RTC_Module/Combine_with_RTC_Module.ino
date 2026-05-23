#include <Wire.h>
#include <RTClib.h>
#include <PersianDate.h>

RTC_DS3231 rtc;
PersianDate pd;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  
  // Assume RTC holds Gregorian time
  DateTime now = rtc.now();
  
  pd.setGregorianDate(now.year(), now.month(), now.day());
  pd.convertGregorianToPersian();
  
  Serial.print("Today in Persian calendar: ");
  Serial.println(pd.getFullPersianDateString());
}

void loop() { }