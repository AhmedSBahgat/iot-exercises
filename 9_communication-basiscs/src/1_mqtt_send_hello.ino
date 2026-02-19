#include <WiFi.h>              // for ESP32
#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int port = 1883;

const char topic[] = "iot_yourname_hello";

const long interval = 8000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }

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

    Serial.print("Sending 'Hello World!' to topic: ");
    Serial.println(topic);

    mqttClient.beginMessage(topic);
    mqttClient.print("Hello World!");
    mqttClient.endMessage();
  }
}
