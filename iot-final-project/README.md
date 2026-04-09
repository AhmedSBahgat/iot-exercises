# Reaction Time Game – IoT Final Project

## Overview
A reaction time game built with ESP32, MQTT communication, Python monitoring app,
SQLite database and live matplotlib visualization.

The ESP32 lights an LED at a random moment. The player presses a button as fast
as possible. The reaction time is measured in milliseconds, sent over WiFi via MQTT,
stored in a database, and displayed on a live chart.

---

## Project Structure
iot-final-project/
├── esp32/
│ ├── src/
│ │ ├── main.ino # ESP32 game logic
│ │ └── arduino_secrets.h # WiFi credentials (not committed)
│ ├── platformio.ini # PlatformIO configuration
│ ├── diagram.json # Wokwi circuit diagram
│ └── wokwi.toml # Wokwi simulator config
├── python/
│ ├── game_monitor.py # MQTT subscriber + database + live chart
│ └── requirements.txt # Python dependencies
└── README.md

---

## How It Works
ESP32 (Wokwi Simulator)
→ Button pressed → reaction time measured in ms
→ Published via WiFi to MQTT broker
↓
MQTT Broker (broker.emqx.io)
↓
Python App (PC)
→ Receives score
→ Saves to SQLite database
→ Updates live bar + line chart

---

## Scoring Criteria Met

| Criteria | Points | Implementation |
|----------|--------|----------------|
| Sensor + Actuator | 10 | Button (input) + LED (output) |
| Communication | 30 | ESP32 ↔ Python via MQTT over WiFi |
| Database + Visualization | 50 | SQLite stores scores + matplotlib live chart |

**Total: 50 points**

---

## Hardware (Simulated in Wokwi)

| Component | Pin |
|-----------|-----|
| ESP32 Dev Module | – |
| Built-in LED | GPIO 2 |
| Push button | GPIO 14 → GND |

---

## Game Rules

- ESP32 waits a **random 2–5 seconds** before LED turns on
- Player presses button as fast as possible when LED turns on
- Reaction time is measured in **milliseconds**
- **False start** (pressing before LED) → LED flashes 3 times → round restarts
- Game auto-resets after each round

## Reaction Time Ratings

| Time | Rating |
|------|--------|
| < 200 ms | AMAZING |
| < 350 ms | GOOD |
| < 500 ms | OK |
| ≥ 500 ms | SLOW |

---

## Setup and Running

### ESP32 (Wokwi Simulator)

1. Install [PlatformIO](https://platformio.org/) in VS Code
2. Install [Wokwi VS Code extension](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode)
3. Edit `esp32/src/arduino_secrets.h`:
```cpp
#define SECRET_SSID "Wokwi-GUEST"
#define SECRET_PASS ""
```
4. Build firmware:
```bash
cd esp32
pio run
```
5. Start simulator:
   - Press `F1` → **Wokwi: Start Simulator**

### Python Monitor

1. Install dependencies:
```bash
cd python
pip install -r requirements.txt
```
2. Run the monitor:
```bash
python game_monitor.py
```

---

## MQTT Topics

| Topic | Description |
|-------|-------------|
| `ahmedbahgat_reaction_score` | JSON score: `{"round": 1, "reaction_ms": 287}` |
| `ahmedbahgat_reaction_status` | Game status: `waiting / led_on / false_start / ready` |

---

## Database

**File:** `reaction_scores.db` (SQLite)

**Table:** `scores`

| Column | Type | Description |
|--------|------|-------------|
| id | INTEGER | Auto increment |
| ts | TEXT | UTC timestamp |
| round_num | INTEGER | Round number |
| reaction_ms | INTEGER | Reaction time in ms |

---

## Live Chart

The Python app shows a **live updating chart** with two panels:

- **Left – Bar chart:** reaction time per round
  - Gold bar = best score
  - Red bar = worst score
  - Dashed lines = average and best

- **Right – Line chart:** performance trend over time
  - Green area = faster than average
  - Red area = slower than average

Chart updates automatically every **2 seconds**.

---

## Technologies Used

| Technology | Purpose |
|-----------|---------|
| ESP32 | Microcontroller running the game |
| Arduino C++ | ESP32 programming language |
| PlatformIO | Build and compile tool |
| Wokwi | Hardware simulator |
| WiFi | ESP32 internet connection |
| MQTT | IoT messaging protocol |
| broker.emqx.io | Free public MQTT broker |
| Python 3 | Monitoring application |
| paho-mqtt | MQTT client library |
| SQLite | Lightweight database |
| matplotlib | Live chart visualization |
| GitHub | Version control |

---

## Real World Use Cases

- **Sports training** – track athlete reaction speed improvement
- **Medical testing** – screen patients for slow reflexes
- **Driver safety** – measure reaction time before driving
- **Gaming / esports** – benchmark and improve reaction speed
- **Research** – study effects of fatigue or caffeine on reaction time

---

## Author

**Ahmed Bahgat**
Centria University of Applied Sciences
Internet of Things – 2025/2026

## Repository

[github.com/AhmedSBahgat/iot-exercises](https://github.com/AhmedSBahgat/iot-exercises/tree/main/final_project)
