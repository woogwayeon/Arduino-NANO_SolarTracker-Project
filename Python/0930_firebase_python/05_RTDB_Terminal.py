import json
import time
from firebase_admin import credentials, initialize_app
from firebase_admin import db

with open("D:/2025HC_seoyeon/[Ko-Jin-hyung]Arduino_Project/Firebase_Python_Private_Key/solartracker-1a0a9-firebase-adminsdk-fbsvc-f0db2633c8.json", encoding="utf-8") as f:
    key_dict = json.load(f)

cred = credentials.Certificate(key_dict)
initialize_app(cred, {
    "databaseURL": "https://solartracker-1a0a9-default-rtdb.firebaseio.com/"
})

ref = db.reference("users")

def on_event(event: db.Event):
    # event.event_type : put 또는 patch
    # event.path : 바뀐 경로
    # event.data : 변경된 데이터
    print(f"[{event.event_type}] path = {event.path} data = {event.data}")

regist = ref.listen(on_event)

try:
    while True:
        time.sleep(60)
        
except KeyboardInterrupt:
    regist.close()
    print("Listener closed")