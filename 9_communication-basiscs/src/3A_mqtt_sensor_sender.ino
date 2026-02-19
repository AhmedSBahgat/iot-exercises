#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int port = 1883;

const char topic[] = "iot_yourname_sensor";

// sensor pin
#define POT_PIN 34

const long interval = 3000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }

  pinMode(POT_PIN, INPUT);

  Serial.print("Connecting to SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nWiFi connected.");

  Serial.print("Connecting to MQTT broker: ");
  Serial.println(broker);
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed, error = ");
    Serial.println(mqttClient.connectError());
    while (1) ;
  }
  Serial.println("MQTT connected.");
}

void loop() {
  mqttClient.poll();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int value = analogRead(POT_PIN);  
    Serial.print("Sending sensor value: ");
    Serial.println(value);

    mqttClient.beginMessage(topic);
    mqttClient.print(value);
    mqttClient.endMessage();
  }
}
