import json
from firebase_admin import credentials, initialize_app
from firebase_admin import db

with open("D:/2025HC_seoyeon/[Ko-Jin-hyung]Arduino_Project/Firebase_Python_Private_Key/solartracker-1a0a9-firebase-adminsdk-fbsvc-f0db2633c8.json", encoding="utf-8") as f:
    key_dict = json.load(f)

cred = credentials.Certificate(key_dict)
initialize_app(cred, {
    "databaseURL": "https://solartracker-1a0a9-default-rtdb.firebaseio.com/"
})

ref = db.reference('users')
ref.set({  # 전체를 덮어쓰기
    'user1': {
        'name': 'Alice',
        'age': 25
    },
    'user2': {
        'name': 'Bob',
        'age': 30
    }
})

ref = db.reference('users')
new_user_ref = ref.push({
    'name': 'Charlie',
    'age': 28
})
print("새로운 키:", new_user_ref.key)

ref = db.reference('users')
users = ref.get()
print(users)

ref = db.reference('users/user1/name')
name = ref.get()
print("user1의 이름:", name)

ref = db.reference('users/user1')
ref.update({
    'age': 26
})

ref = db.reference('users/user2')
ref.delete()
