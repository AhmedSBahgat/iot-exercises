#define LIGHT_PIN 34
#define LED_PIN    4

int sensorMin = 4095;
int sensorMax = 0;
bool calibrated = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Calibrating light sensor for 5 seconds...");
}

void loop() {
  unsigned long t = millis();
  int sensorValue = analogRead(LIGHT_PIN);

  if (t <= 5000) {
    
    if (sensorValue > sensorMax) sensorMax = sensorValue;
    if (sensorValue < sensorMin) sensorMin = sensorValue;

    if (t % 500 == 0) {  
      Serial.print("Calib value: ");
      Serial.println(sensorValue);
    }
  } else {
    if (!calibrated) {
      calibrated = true;
      Serial.print("Calibration done. Min = ");
      Serial.print(sensorMin);
      Serial.print(", Max = ");
      Serial.println(sensorMax);
    }

    int threshold = sensorMin + (sensorMax - sensorMin) / 4;
    bool dark = (sensorValue < threshold);

    digitalWrite(LED_PIN, dark ? HIGH : LOW);

    Serial.print("Light: ");
    Serial.print(sensorValue);
    Serial.print("  threshold: ");
    Serial.print(threshold);
    Serial.print("  dark: ");
    Serial.println(dark ? "YES" : "NO");

    delay(100);
  }
}
