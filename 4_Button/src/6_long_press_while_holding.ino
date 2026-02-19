#define BUTTON_PIN 14
#define LED_PIN    4
#define BUZZER_PIN 5

const unsigned long LONG_PRESS_MS = 5000;

bool isPressed           = false;
bool longActionTriggered = false;
unsigned long pressStartTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);
  bool pressedNow = (reading == LOW);

  if (!isPressed && pressedNow) {
   
    isPressed = true;
    longActionTriggered = false;
    pressStartTime = millis();
    digitalWrite(LED_PIN, HIGH);   
  }

  if (isPressed && pressedNow) {

    if (!longActionTriggered && (millis() - pressStartTime >= LONG_PRESS_MS)) {
      longActionTriggered = true;
      digitalWrite(BUZZER_PIN, HIGH);  
    }
  }

  if (isPressed && !pressedNow) {
  
    isPressed = false;
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW); 
  }
}
