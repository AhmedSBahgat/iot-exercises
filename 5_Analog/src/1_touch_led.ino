#define TOUCH_PIN  T0   
#define LED_PIN    4

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int touchValue = digitalRead(TOUCH_PIN);  
  bool touched = (touchValue == LOW);

  digitalWrite(LED_PIN, touched ? HIGH : LOW);

  Serial.print("Touch value: ");
  Serial.println(touchValue);

  delay(50);
}
