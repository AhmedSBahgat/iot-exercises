#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

#define TOUCH_PIN  T0   // or digital input pin

unsigned long counter = 0;
int lastTouchState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_PIN, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);
  lcd.setCursor(0, 0);
  lcd.print("Touch count:");
}

void loop() {
  int state = digitalRead(TOUCH_PIN);       

  if (lastTouchState == HIGH && state == LOW) {
    counter++;
    lcd.setCursor(0, 1);
    lcd.print("        ");                  
    lcd.setCursor(0, 1);
    lcd.print(counter);
  }

  lastTouchState = state;
  delay(20);
}
