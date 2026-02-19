#define DATA_PIN  14   
#define LED_PIN    4   

void setup() {
  Serial.begin(115200);
  pinMode(DATA_PIN, INPUT);     
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int data = digitalRead(DATA_PIN);   

 
  digitalWrite(LED_PIN, data ? HIGH : LOW);

  delay(10);
}
