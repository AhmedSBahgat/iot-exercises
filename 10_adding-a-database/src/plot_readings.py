import sqlite3
from datetime import datetime

import matplotlib.pyplot as plt

DB_FILE = "sensor_data.db"


def load_readings():
    conn = sqlite3.connect(DB_FILE)
    cur = conn.cursor()
    cur.execute("SELECT ts, value FROM readings ORDER BY id ASC")
    rows = cur.fetchall()
    conn.close()

    times = [datetime.fromisoformat(ts) for ts, _ in rows]
    values = [v for _, v in rows]
    return times, values


def main():
    times, values = load_readings()
    if not times:
        print("No data in database yet.")
        return

    plt.figure(figsize=(8, 4))
    plt.plot(times, values, marker="o")
    plt.xlabel("Time")
    plt.ylabel("Sensor value")
    plt.title("Sensor readings over time")
    plt.grid(True)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
