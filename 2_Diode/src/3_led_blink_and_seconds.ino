#define LED_PIN 4

const unsigned long ON_TIME      = 500;  
const unsigned long OFF_TIME     = 2000;  
const unsigned long PRINT_PERIOD = 1000;  

bool ledOn = false;
unsigned long previousLedMillis   = 0;
unsigned long previousPrintMillis = 0;
unsigned long secondsSinceStart   = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting 2_Diode task 3");
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  unsigned long ledInterval = ledOn ? ON_TIME : OFF_TIME;
  if (currentMillis - previousLedMillis >= ledInterval) {
    previousLedMillis = currentMillis;
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
  }

  if (currentMillis - previousPrintMillis >= PRINT_PERIOD) {
    previousPrintMillis = currentMillis;
    secondsSinceStart++;
    Serial.print("Running for ");
    Serial.print(secondsSinceStart);
    Serial.println(" seconds");
  }
}
