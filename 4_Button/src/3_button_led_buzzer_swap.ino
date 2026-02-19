#define BUTTON_PIN 14
#define LED_PIN    4
#define BUZZER_PIN 5   

int buttonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);      
  bool pressed = (buttonState == LOW);

  if (pressed) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
  }

  delay(20);
}
