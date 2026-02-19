#define BUTTON_PIN  12   
#define DATA_PIN    14  

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW);
}

void loop() {
  int button = digitalRead(BUTTON_PIN);    
  bool pressed = (button == LOW);

  digitalWrite(DATA_PIN, pressed ? HIGH : LOW);

  delay(10);
}
