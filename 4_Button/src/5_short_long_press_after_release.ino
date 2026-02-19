#define BUTTON_PIN 14
#define LED_PIN    4
#define BUZZER_PIN 5

const unsigned long LONG_PRESS_MS = 5000;
const unsigned long ACTION_MS     = 2000;

int  lastButtonState = HIGH;
unsigned long pressStartTime = 0;
bool isPressed = false;

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
    pressStartTime = millis();
  }

  
  if (isPressed && !pressedNow) {
    isPressed = false;
    unsigned long pressDuration = millis() - pressStartTime;

    if (pressDuration < LONG_PRESS_MS) {
      
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      delay(ACTION_MS);
      digitalWrite(LED_PIN, LOW);
    } else {
      
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(ACTION_MS);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  lastButtonState = reading;
}
