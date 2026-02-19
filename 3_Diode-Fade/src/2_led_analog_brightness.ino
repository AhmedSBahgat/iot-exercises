#define LED_PIN    4
#define PWM_CH     0
#define PWM_FREQ   5000
#define PWM_RES    8     

void setup() {
  Serial.begin(115200);
  ledcSetup(PWM_CH, PWM_FREQ, PWM_RES);
  ledcAttachPin(LED_PIN, PWM_CH);
}

void loop() {

  ledcWrite(PWM_CH, 128);
  Serial.println("Brightness: 128 (half)");
  delay(2000);

 
  ledcWrite(PWM_CH, 255);
  Serial.println("Brightness: 255 (max)");
  delay(2000);

  
  ledcWrite(PWM_CH, 0);
  Serial.println("Brightness: 0 (off)");
  delay(2000);
}
