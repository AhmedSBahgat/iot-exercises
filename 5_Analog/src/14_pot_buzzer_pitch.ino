#define POT_PIN    34
#define BUZZER_PIN 18

const int BUZZER_CHANNEL = 1;

const int MIN_FREQ = 200;   
const int MAX_FREQ = 2000;  

void setup() {
  Serial.begin(115200);

  ledcSetup(BUZZER_CHANNEL, 1000, 10);  
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
}

void loop() {
  int potValue = analogRead(POT_PIN);                
  int freq = map(potValue, 0, 4095, MIN_FREQ, MAX_FREQ);

  ledcWriteTone(BUZZER_CHANNEL, freq);

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  freq: ");
  Serial.println(freq);

  delay(20);
}
