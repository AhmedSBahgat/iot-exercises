#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int port = 1883;

const char topic[] = "iot_yourname_sensor";

void onMqttMessage(int messageSize);

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }

  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);
  lcd.setCursor(0, 0);
  lcd.print("Sensor value:");

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

  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  mqttClient.subscribe(topic);
}

void loop() {
  mqttClient.poll();
}

void onMqttMessage(int messageSize) {
  String payload = "";
  while (mqttClient.available()) {
    char c = (char)mqttClient.read();
    payload += c;
  }

  int value = payload.toInt();

  Serial.print("Received sensor: ");
  Serial.println(value);

  lcd.setCursor(0, 1);
  lcd.print("        ");
  lcd.setCursor(0, 1);
  lcd.print(value);
}
