#include <Servo.h>

#define POT_PIN   34
#define SERVO_PIN 5

Servo myservo;

void setup() {
  Serial.begin(115200);
  myservo.attach(SERVO_PIN);
}

void loop() {
  int potValue = analogRead(POT_PIN);           
  int angle = map(potValue, 0, 4095, 0, 180);   

  myservo.write(angle);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Angle: ");
  Serial.println(angle);

  delay(30);
}
