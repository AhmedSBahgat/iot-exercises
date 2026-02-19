#define BUTTON_PIN 14  

int buttonState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  Serial.println(buttonState);        
  delay(100);
}
