int seconds = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Seconds (0–9): ");
  Serial.println(seconds);

  seconds = seconds + 1;

  if (seconds >= 10) {
    seconds = 0;  
  }

  delay(1000);
}
