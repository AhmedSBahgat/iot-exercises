int seconds = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Seconds since start: ");
  Serial.println(seconds);

  seconds = seconds + 1;  
  delay(1000);            
}
