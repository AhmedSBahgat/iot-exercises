#include <WiFi.h>              
#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int port = 1883;


const char topic[] = "iot_yourname_hello";

#define LED_PIN 4

void onMqttMessage(int messageSize);

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

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
  Serial.print("Message on topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("' length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  String payload = "";
  while (mqttClient.available()) {
    char c = (char)mqttClient.read();
    Serial.print(c);
    payload += c;
  }
  Serial.println();

  static bool ledOn = false;
  ledOn = !ledOn;
  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);

  Serial.println();
}
