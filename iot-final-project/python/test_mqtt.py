import paho.mqtt.client as mqtt
import time

def on_connect(client, userdata, flags, reason_code, properties=None):
    print(f"Connected! reason_code={reason_code}")

def on_disconnect(client, userdata, flags, reason_code, properties=None):
    print(f"Disconnected! reason_code={reason_code}")

print("Testing broker.emqx.io...")
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.connect("broker.emqx.io", 1883, 60)
client.loop_start()
time.sleep(5)
print("Done.")
client.loop_stop()