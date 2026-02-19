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
  
  for (int brightness = 0; brightness <= 255; brightness++) {
    ledcWrite(PWM_CH, brightness);
    delay(8); 
  }

  for (int brightness = 255; brightness >= 0; brightness--) {
    ledcWrite(PWM_CH, brightness);
    delay(8);   
  }
}
