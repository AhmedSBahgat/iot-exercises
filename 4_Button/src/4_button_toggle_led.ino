#define BUTTON_PIN 14
#define LED_PIN    4

bool ledState        = false;
int  lastButtonState = HIGH;    
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_MS = 50;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > DEBOUNCE_MS) {
    if (lastButtonState == HIGH && reading == LOW) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    }
  }

  lastButtonState = reading;
}
