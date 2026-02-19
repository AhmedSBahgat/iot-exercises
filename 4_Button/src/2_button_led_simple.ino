#define BUTTON_PIN 14   
#define LED_PIN    4   

int buttonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);   

  bool ledOn = (buttonState == LOW);
  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);

  delay(20);
}
