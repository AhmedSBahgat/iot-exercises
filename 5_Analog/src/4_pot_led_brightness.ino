#define POT_PIN 34
#define LED_PIN 4   

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int potValue = analogRead(POT_PIN);    
  int pwmValue = map(potValue, 0, 4095, 0, 255);

  ledcAttachPin(LED_PIN, 0);              
  ledcSetup(0, 5000, 8);                  
  ledcWrite(0, pwmValue);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  PWM: ");
  Serial.println(pwmValue);

  delay(30);
}
