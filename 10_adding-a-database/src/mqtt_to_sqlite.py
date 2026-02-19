import sqlite3
import time
from datetime import datetime

import paho.mqtt.client as mqtt

BROKER = "test.mosquitto.org"
PORT = 1883
TOPIC = "iot_yourname_sensor"   

DB_FILE = "sensor_data.db"


def init_db():
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute(
        """
        CREATE TABLE IF NOT EXISTS readings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ts TEXT NOT NULL,
            value INTEGER NOT NULL
        )
        """
    )
    conn.commit()
    conn.close()


def save_reading(value: int):
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute(
        "INSERT INTO readings (ts, value) VALUES (?, ?)",
        (datetime.utcnow().isoformat(), int(value)),
    )
    conn.commit()
    conn.close()


def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker with result code", rc)
    client.subscribe(TOPIC)
    print("Subscribed to", TOPIC)


def on_message(client, userdata, msg):
    payload = msg.payload.decode().strip()
    print(f"Received on {msg.topic}: {payload}")
    try:
        value = int(payload)
        save_reading(value)
        print("Saved to DB.")
    except ValueError:
        print("Payload is not an int, skipping.")


def main():
    init_db()

    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(BROKER, PORT, 60)
    client.loop_start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("Stopping...")
    finally:
        client.loop_stop()
        client.disconnect()


if __name__ == "__main__":
    main()
