#define POT_PIN 34
#define LED_PIN 4

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int value = analogRead(POT_PIN);  
  int threshold = 4095 / 2;

  bool ledOn = (value > threshold);
  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);

  Serial.print("Pot: ");
  Serial.print(value);
  Serial.print(" -> LED ");
  Serial.println(ledOn ? "ON" : "OFF");

  delay(50);
}
