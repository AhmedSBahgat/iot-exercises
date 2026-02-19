#include <Servo.h>

#define SERVO_PIN 5
#define TEMP_PIN  35

Servo myservo;

float convertToCelsius(int raw) {
 
  return map(raw, 0, 4095, 0, 50);
}

void setup() {
  Serial.begin(115200);
  myservo.attach(SERVO_PIN);
}

void loop() {
  int raw = analogRead(TEMP_PIN);
  float tempC = convertToCelsius(raw);

 
  int angle = map((int)tempC, 0, 50, 0, 180);
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;

  myservo.write(angle);

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("  TempC: ");
  Serial.print(tempC);
  Serial.print("  Angle: ");
  Serial.println(angle);

  delay(500);
}
