#define POT_PIN 34  
void setup() {
  Serial.begin(115200);
}

void loop() {
  int value = analogRead(POT_PIN);  
  Serial.print("Pot value: ");
  Serial.println(value);
  delay(100);
}
