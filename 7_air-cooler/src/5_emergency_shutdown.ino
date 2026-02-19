#include <Servo.h>

#define SERVO_PIN   5
#define TEMP_PIN    35
#define RELAY_PIN   4
#define TOUCH_PIN   14   

Servo myservo;

volatile bool emergencyTriggered = false;

float convertToCelsius(int raw) {
  return map(raw, 0, 4095, 0, 50);   
}

void IRAM_ATTR emergencyISR() {
  emergencyTriggered = true;
}

void setup() {
  Serial.begin(115200);
  myservo.attach(SERVO_PIN);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  pinMode(TOUCH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TOUCH_PIN), emergencyISR, RISING);

  Serial.println("System running. Touch sensor to trigger EMERGENCY STOP.");
}

void loop() {
  if (emergencyTriggered) {
    digitalWrite(RELAY_PIN, LOW);
    myservo.write(0);
    Serial.println("EMERGENCY STOP! System halted.");
    while (true) {
      delay(1000);
    }
  }

  int raw = analogRead(TEMP_PIN);
  float tempC = convertToCelsius(raw);

  int angle = map((int)tempC, 0, 50, 0, 180);
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;

  myservo.write(angle);

  bool hot = (tempC > 28.0);
  digitalWrite(RELAY_PIN, hot ? HIGH : LOW);

  Serial.print("TempC: ");
  Serial.print(tempC);
  Serial.print("  Angle: ");
  Serial.print(angle);
  Serial.print("  Relay: ");
  Serial.println(hot ? "ON" : "OFF");

  delay(500);
}
