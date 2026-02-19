#define SOUND_PIN 35

const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
long total = 0;
int averageValue = 0;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  total = total - readings[readIndex];

  int newValue = analogRead(SOUND_PIN);
  readings[readIndex] = newValue;

  total = total + readings[readIndex];

  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  averageValue = total / numReadings;

  Serial.print("raw:");
  Serial.print(newValue);
  Serial.print(" avg:");
  Serial.println(averageValue);

  delay(20);
}
