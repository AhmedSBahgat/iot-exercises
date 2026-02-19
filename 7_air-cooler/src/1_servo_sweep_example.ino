#include <Servo.h>

#define SERVO_PIN 5

Servo myservo;
int pos = 0;

void setup() {
  myservo.attach(SERVO_PIN);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}
