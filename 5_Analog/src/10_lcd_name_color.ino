#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 0;
const int colorG = 128;
const int colorB = 255;

void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);

  lcd.setCursor(0, 0);
  lcd.print("Ahmed Bahgat");   
}

void loop() {
  
  lcd.setCursor(0, 1);
  lcd.print("Time ");
  lcd.print(millis() / 1000);
  delay(200);
}
