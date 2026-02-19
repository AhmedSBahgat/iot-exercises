#define LED_PIN 4  

const unsigned long ON_TIME  = 500;   
const unsigned long OFF_TIME = 2000;  

bool ledOn = false;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long interval = ledOn ? ON_TIME : OFF_TIME;

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
  }

}
