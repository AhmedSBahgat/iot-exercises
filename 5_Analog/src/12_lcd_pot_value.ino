#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

#define POT_PIN 34

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 255);
  lcd.setCursor(0, 0);
  lcd.print("Pot value:");
}

void loop() {
  int value = analogRead(POT_PIN);   

  lcd.setCursor(0, 1);
  lcd.print("        ");             
  lcd.setCursor(0, 1);
  lcd.print(value);

  delay(100);
}
