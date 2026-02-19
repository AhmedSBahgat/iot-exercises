#define LED_PIN 4

String bitmask = "10101010";        
const unsigned long BIT_DURATION = 200;  

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Enter bitmask like 10101010 and press Enter.");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    bool valid = true;
    if (input.length() > 0) {
      for (unsigned int i = 0; i < input.length(); i++) {
        char c = input[i];
        if (c != '0' && c != '1') {
          valid = false;
          break;
        }
      }
      if (valid) {
        bitmask = input;
        Serial.print("New pattern: ");
        Serial.println(bitmask);
      } else {
        Serial.println("Invalid pattern, use only 0 and 1.");
      }
    }
  }

  for (unsigned int i = 0; i < bitmask.length(); i++) {
    char c = bitmask[i];
    if (c == '1') {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    delay(BIT_DURATION);
  }
}
