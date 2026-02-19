#define LED_PIN 4

int incomingByte = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();      
    digitalWrite(LED_PIN, HIGH);      
  } else {
    digitalWrite(LED_PIN, LOW);        
  }
}
