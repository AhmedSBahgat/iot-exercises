#define LED_PIN  4
#define PWM_CH   0
#define PWM_FREQ 5000
#define PWM_RES  8     

void setup() {
  Serial.begin(115200);
  ledcSetup(PWM_CH, PWM_FREQ, PWM_RES);
  ledcAttachPin(LED_PIN, PWM_CH);
}

void loop() {
  ledcWrite(PWM_CH, 255);   
  Serial.println("ON");
  delay(1000);            

  ledcWrite(PWM_CH, 0);    
  Serial.println("OFF");
  delay(1000);              
}
