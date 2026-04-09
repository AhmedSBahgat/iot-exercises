import json
import sqlite3
import threading
import time
from datetime import datetime, timezone

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import paho.mqtt.client as mqtt

# ── Configuration ─────────────────────────────────────────
BROKER       = "broker.emqx.io"
PORT         = 1883
TOPIC_SCORE  = "ahmedbahgat_reaction_score"
TOPIC_STATUS = "ahmedbahgat_reaction_status"
DB_FILE      = "D:/Centria 2025-2026/IOT/iot-final-project/reaction_scores.db"

# ── Database ──────────────────────────────────────────────
def init_db(clear=False):
    conn = sqlite3.connect(DB_FILE)
    if clear:
        conn.execute("DROP TABLE IF EXISTS scores")
    conn.execute("""
        CREATE TABLE IF NOT EXISTS scores (
            id          INTEGER PRIMARY KEY AUTOINCREMENT,
            ts          TEXT    NOT NULL,
            round_num   INTEGER NOT NULL,
            reaction_ms INTEGER NOT NULL
        )
    """)
    conn.commit()
    conn.close()

def save_score(round_num, reaction_ms):
    conn = sqlite3.connect(DB_FILE)
    conn.execute(
        "INSERT INTO scores (ts, round_num, reaction_ms) VALUES (?,?,?)",
        (datetime.now(timezone.utc).isoformat(), round_num, reaction_ms),
    )
    conn.commit()
    conn.close()

def load_scores():
    conn = sqlite3.connect(DB_FILE)
    cur  = conn.execute(
        "SELECT round_num, reaction_ms FROM scores ORDER BY id ASC"
    )
    rows = cur.fetchall()
    conn.close()
    return rows

def load_stats():
    conn = sqlite3.connect(DB_FILE)
    cur  = conn.execute(
        "SELECT MIN(reaction_ms), MAX(reaction_ms), AVG(reaction_ms) FROM scores"
    )
    row = cur.fetchone()
    conn.close()
    if row[0] is None:
        return None
    return row

# ── MQTT ──────────────────────────────────────────────────
def on_connect(client, userdata, flags, reason_code, properties=None):
    print(f"on_connect called! reason_code={reason_code}")
    if str(reason_code) in ["0", "Success"]:
        print("Connected to MQTT broker.")
        client.subscribe(TOPIC_SCORE)
        client.subscribe(TOPIC_STATUS)
        print(f"Listening on:\n  {TOPIC_SCORE}\n  {TOPIC_STATUS}\n")
    else:
        print(f"MQTT connection failed: {reason_code}")

def on_message(client, userdata, msg):
    topic   = msg.topic
    payload = msg.payload.decode().strip()

    if topic == TOPIC_SCORE:
        try:
            data        = json.loads(payload)
            round_num   = int(data["round"])
            reaction_ms = int(data["reaction_ms"])
            save_score(round_num, reaction_ms)

            if   reaction_ms < 200: rating = "AMAZING"
            elif reaction_ms < 350: rating = "GOOD"
            elif reaction_ms < 500: rating = "OK"
            else:                   rating = "SLOW"

            print(f"[Round {round_num}] {reaction_ms} ms → {rating}")
        except Exception as e:
            print(f"Error: {e}")

    elif topic == TOPIC_STATUS:
        labels = {
            "waiting":     "Waiting for LED...",
            "led_on":      "LED ON - player reacting!",
            "false_start": "FALSE START!",
            "ready":       "Game ready.",
        }
        print(f"Status: {labels.get(payload, payload)}")

def start_mqtt():
    print("MQTT thread running...")
    try:
        client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
        client.on_connect = on_connect
        client.on_message = on_message
        print(f"Connecting to {BROKER}:{PORT}...")
        client.connect(BROKER, PORT, 60)
        client.loop_start()
        print("Loop started, waiting for connection...")
        time.sleep(5)
        print("Connection attempt done.")
        while True:
            time.sleep(1)
    except Exception as e:
        print(f"MQTT error: {e}")

# ── Live chart ────────────────────────────────────────────
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(13, 5))
fig.suptitle("Reaction Time Game - Live Scoreboard",
             fontsize=14, fontweight="bold")

def animate(_):
    rows = load_scores()

    ax1.clear()
    ax2.clear()

    if not rows or len(rows) < 1:
        ax1.set_title("Waiting for scores...")
        ax2.set_title("Waiting for scores...")
        ax1.set_xlabel("Round")
        ax2.set_xlabel("Round")
        plt.tight_layout()
        fig.canvas.draw()
        fig.canvas.flush_events()
        return

    rounds = [r[0] for r in rows]
    times  = [r[1] for r in rows]
    stats  = load_stats()
    if stats is None:
        return

    best  = stats[0]
    worst = stats[1]
    avg   = stats[2]

    colors = ["gold"      if t == best  else
              "tomato"    if t == worst else
              "steelblue" for t in times]

    # Bar chart
    ax1.bar(rounds, times, color=colors, edgecolor="white")
    ax1.axhline(avg,  color="red",  linestyle="--",
                label=f"Avg: {avg:.0f} ms")
    ax1.axhline(best, color="gold", linestyle="--",
                label=f"Best: {best} ms")
    ax1.set_xlabel("Round")
    ax1.set_ylabel("Reaction time (ms)")
    ax1.set_title("Score per round  (gold=best  red=worst)")
    ax1.legend(fontsize=9)
    ax1.grid(axis="y", alpha=0.4)
    ax1.set_xticks(rounds)

    # Line chart
    ax2.plot(rounds, times, marker="o", color="steelblue",
             linewidth=2, markersize=6)
    ax2.axhline(avg, color="red", linestyle="--",
                label=f"Avg: {avg:.0f} ms")
    ax2.fill_between(rounds, times, avg,
                     where=[t < avg for t in times],
                     alpha=0.15, color="green", label="Below avg")
    ax2.fill_between(rounds, times, avg,
                     where=[t >= avg for t in times],
                     alpha=0.15, color="red", label="Above avg")
    ax2.set_xlabel("Round")
    ax2.set_ylabel("Reaction time (ms)")
    ax2.set_title(f"Trend | Best: {best} ms | Rounds: {len(rounds)}")
    ax2.legend(fontsize=9)
    ax2.grid(True, alpha=0.4)
    ax2.set_xticks(rounds)

    plt.tight_layout()
    fig.canvas.draw()
    fig.canvas.flush_events()

# ── Main ──────────────────────────────────────────────────
if __name__ == "__main__":
    init_db(clear=True)
    print("=" * 45)
    print("  Reaction Time Game Monitor")
    print("=" * 45)

    t = threading.Thread(target=start_mqtt, daemon=True)
    t.start()

    ani = animation.FuncAnimation(
        fig, animate,
        interval=2000,
        cache_frame_data=False,
        repeat=True
    )
    plt.show(block=True)