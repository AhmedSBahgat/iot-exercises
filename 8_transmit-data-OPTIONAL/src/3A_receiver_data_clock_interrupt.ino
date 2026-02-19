#include <Arduino.h>

#define DATA_PIN   14   
#define CLOCK_PIN  27   

volatile byte receivedByte = 0;
volatile int bitCount = 0;
volatile bool frameComplete = false;

void IRAM_ATTR clockISR() {
  if (frameComplete) {
    return;  
  }

  int bit = digitalRead(DATA_PIN);  

  
  receivedByte = (receivedByte << 1) | (bit ? 1 : 0);
  bitCount++;

  if (bitCount >= 8) {
    frameComplete = true;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), clockISR, RISING);

  Serial.println("Receiver ready. Waiting for 8 bits...");
}

void loop() {
  if (frameComplete) {
    noInterrupts();
    byte value = receivedByte;
    int bits = bitCount;
    receivedByte = 0;
    bitCount = 0;
    frameComplete = false;
    interrupts();

    Serial.print("Received ");
    Serial.print(bits);
    Serial.print(" bits: 0b");

    for (int i = 7; i >= 0; i--) {
      Serial.print((value & (1 << i)) ? '1' : '0');
    }
    Serial.print("  (decimal ");
    Serial.print(value);
    Serial.println(")");

    Serial.println("Waiting for next frame...");
  }
}
