#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

#define POT_PIN     34
#define BUTTON_PIN  14

int lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setRGB(255, 255, 0);
  lcd.clear();
}

void loop() {
  int potValue = analogRead(POT_PIN);           
  int col = map(potValue, 0, 4095, 0, 15);      
  int row = 0;                                  

  int buttonState = digitalRead(BUTTON_PIN);

 
  if (lastButtonState == HIGH && buttonState == LOW) {
    lcd.setCursor(col, row);
    lcd.print("*");
  }

  lastButtonState = buttonState;
  delay(30);
}
