#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"

// ── Pins ──────────────────────────────────────────────────
#define LED_PIN     2
#define BUTTON_PIN  14

// ── MQTT ──────────────────────────────────────────────────
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[]      = "broker.emqx.io";
int        port          = 1883;
const char topicScore[]  = "ahmedbahgat_reaction_score";
const char topicStatus[] = "ahmedbahgat_reaction_status";

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// ── Game state ────────────────────────────────────────────
enum GameState { WAITING, LED_ON, COOLDOWN };
GameState state = WAITING;

unsigned long waitUntil   = 0;
unsigned long ledOnTime   = 0;
int           roundNumber = 0;
bool          lastButton  = HIGH;

// ── WiFi ──────────────────────────────────────────────────
void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {
    Serial.print(".");
    delay(500);
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("WiFi connected. IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi FAILED");
  }
}

// ── MQTT ──────────────────────────────────────────────────
void connectMQTT() {
  Serial.print("Connecting to MQTT");
  while (!mqttClient.connect(broker, port)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("MQTT connected.");
}

// ── Publish ───────────────────────────────────────────────
void publishScore(unsigned long reactionMs) {
  roundNumber++;
  String payload = "{\"round\":"       + String(roundNumber) +
                   ",\"reaction_ms\":" + String(reactionMs)  +
                   "}";
  mqttClient.beginMessage(topicScore);
  mqttClient.print(payload);
  mqttClient.endMessage();
  Serial.print("Published: ");
  Serial.println(payload);
}

void publishStatus(const char* msg) {
  mqttClient.beginMessage(topicStatus);
  mqttClient.print(msg);
  mqttClient.endMessage();
}

// ── New round ─────────────────────────────────────────────
void startNewRound() {
  digitalWrite(LED_PIN, LOW);
  unsigned long waitMs = random(2000, 5001);
  waitUntil = millis() + waitMs;
  state = WAITING;
  Serial.print("Round ");
  Serial.print(roundNumber + 1);
  Serial.println(": Wait for LED...");
  publishStatus("waiting");
}

// ── Setup ─────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  pinMode(LED_PIN,    OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);

  connectWiFi();
  connectMQTT();

  Serial.println("=== Reaction Time Game Ready ===");
  publishStatus("ready");
  startNewRound();
}

// ── Loop ──────────────────────────────────────────────────
void loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.poll();

  bool currentButton = digitalRead(BUTTON_PIN);
  bool justPressed   = (lastButton == HIGH && currentButton == LOW);
  lastButton = currentButton;

  switch (state) {

    case WAITING:
      if (justPressed) {
        Serial.println("FALSE START! Penalty.");
        publishStatus("false_start");
        for (int i = 0; i < 3; i++) {
          digitalWrite(LED_PIN, HIGH); delay(100);
          digitalWrite(LED_PIN, LOW);  delay(100);
        }
        delay(500);
        startNewRound();
      } else if (millis() >= waitUntil) {
        digitalWrite(LED_PIN, HIGH);
        ledOnTime = millis();
        state = LED_ON;
        Serial.println("LED ON — press now!");
        publishStatus("led_on");
      }
      break;

    case LED_ON:
      if (justPressed) {
        unsigned long reactionMs = millis() - ledOnTime;
        digitalWrite(LED_PIN, LOW);

        Serial.print("Reaction: ");
        Serial.print(reactionMs);
        Serial.print(" ms → ");
        if      (reactionMs < 200) Serial.println("AMAZING!");
        else if (reactionMs < 350) Serial.println("GOOD!");
        else if (reactionMs < 500) Serial.println("OK");
        else                       Serial.println("SLOW");

        publishScore(reactionMs);
        state = COOLDOWN;
        delay(2000);
        startNewRound();
      }
      break;

    case COOLDOWN:
      break;
  }
}