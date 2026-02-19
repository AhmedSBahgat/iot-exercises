#define LED_PIN 4  

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  
  delay(500);                   

  digitalWrite(LED_PIN, LOW);   
  delay(2000);                  
}
