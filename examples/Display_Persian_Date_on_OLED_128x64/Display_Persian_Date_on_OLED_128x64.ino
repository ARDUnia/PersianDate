#include <Wire.h>
#include <U8g2lib.h>
#include <PersianDate.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0);
PersianDate pd;

void setup() {
  oled.begin();
  pd.setGregorianDate(2026, 5, 20);
  pd.convertGregorianToPersian();
}

void loop() {
  oled.clearBuffer();
  oled.setFont(u8g2_font_10x20_tn);
  
  String dateStr = pd.getPersianDateStringWithNames();
  int16_t x = (128 - oled.getStrWidth(dateStr.c_str())) / 2;
  int16_t y = 32;
  
  oled.drawStr(x, y, dateStr.c_str());
  oled.sendBuffer();
  delay(1000);
}