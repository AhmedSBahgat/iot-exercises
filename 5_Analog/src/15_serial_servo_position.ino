#include <Servo.h>  

#define SERVO_PIN 5

Servo myservo;

String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(115200);
  myservo.attach(SERVO_PIN);
  Serial.println("Send angle 0-180 followed by Enter");
}

void loop() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') {
      if (inputString.length() > 0) {
        stringComplete = true;
      }
    } else {
      inputString += c;
    }
  }

  if (stringComplete) {
    int angle = inputString.toInt();    
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    myservo.write(angle);
    Serial.print("Moving to ");
    Serial.println(angle);

    inputString = "";
    stringComplete = false;
  }
}
