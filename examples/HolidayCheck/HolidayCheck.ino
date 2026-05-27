/*
  PersianDate Example - Convert fixed Gregorian date to Persian and check holiday
  This example uses PersianDate library v2.1.0
*/

#include <PersianDate.h>

// تابع کمکی برای دریافت نام مناسبت بر اساس تاریخ شمسی
String getHolidayName(int year, int month, int day) {
  // تعطیلات رسمی ثابت (مطابق با تعاریف کتابخانه)
  if (month == 1 && day >= 1 && day <= 4) return "عید نوروز";
  if (month == 1 && day == 12) return "روز جمهوری اسلامی";
  if (month == 1 && day == 13) return "روز طبیعت (سیزده بدر)";
  if (month == 2 && day == 1) return "روز جهانی کارگر";
  if (month == 3 && day == 14) return "رحلت امام خمینی";
  if (month == 3 && day == 15) return "قیام ۱۵ خرداد";
  if (month == 11 && day == 22) return "پیروزی انقلاب اسلامی";
  
  // جمعه‌ها را جداگانه بررسی می‌کنیم (نیاز به محاسبه روز هفته دارد)
  // اما این تابع فقط برای تعطیلات ثابت است، جمعه را بعداً در main چک می‌کنیم.
  return "";
}

void setup() {
  Serial.begin(9600);
  delay(1000); // برای اطمینان از شروع سریال
  
  PersianDate pd;
  
  int gy = 2026;
  int gm = 5;
  int gd = 27;
  
  // تنظیم و تبدیل به شمسی
  pd.setGregorianDate(gy, gm, gd);
  pd.convertGregorianToPersian();
  
  // دریافت تاریخ شمسی
  int jy = pd.getPersianYear();
  int jm = pd.getPersianMonth();
  int jd = pd.getPersianDay();
  
  // چاپ نتایج
  Serial.println("=================================");
  Serial.println("تبدیل تاریخ میلادی به شمسی");
  Serial.print("تاریخ میلادی: ");
  Serial.print(gy); Serial.print("/"); Serial.print(gm); Serial.print("/"); Serial.println(gd);
  
  Serial.print("تاریخ شمسی (عددی): ");
  Serial.println(pd.getPersianDateString());
  
  Serial.print("تاریخ شمسی با نام ماه: ");
  Serial.println(pd.getPersianDateStringWithNames());
  
  Serial.print("روز هفته: ");
  Serial.println(pd.getPersianWeekdayName(gy, gm, gd));
  
  // بررسی تعطیلی
  bool holiday = pd.isHoliday(); // با تاریخ شمسی جاری (همان jy, jm, jd)
  if (holiday) {
    Serial.print("وضعیت: ** تعطیل رسمی ** ");
    String hName = getHolidayName(jy, jm, jd);
    if (hName != "") {
      Serial.print("(" + hName + ")");
    } else {
      // اگر جمعه باشد، مناسبت خاصی ندارد
      String weekday = pd.getPersianWeekdayName(gy, gm, gd);
      if (weekday == "جمعه") {
        Serial.print("(جمعه)");
      }
    }
    Serial.println();
  } else {
    Serial.println("وضعیت: ** غیر تعطیل ** (روز کاری)");
  }
  
  Serial.println("=================================");
}

void loop() {
  // هیچ کاری انجام نمی‌دهد
}
