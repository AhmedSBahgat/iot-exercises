#define BUTTON_PIN  12
#define DATA_PIN    14

const unsigned long BIT_TIME_MS = 500;  

byte pattern = 0b10101010;

bool lastPressed = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  bool pressed = (buttonState == LOW);

  if (!lastPressed && pressed) {
    Serial.println("Sending pattern...");

    for (byte mask = 0b10000000; mask != 0; mask >>= 1) {
      if (pattern & mask) {
        digitalWrite(DATA_PIN, HIGH);
      } else {
        digitalWrite(DATA_PIN, LOW);
      }

      delay(BIT_TIME_MS);
    }

    digitalWrite(DATA_PIN, LOW);
    Serial.println("Done.");
  }

  lastPressed = pressed;
}
