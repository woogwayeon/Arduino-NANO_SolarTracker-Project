import json
from firebase_admin import credentials, initialize_app
from firebase_admin import db

with open("D:/2025HC_seoyeon/[Ko-Jin-hyung]Arduino_Project/Firebase_Python_Private_Key/solartracker-1a0a9-firebase-adminsdk-fbsvc-f0db2633c8.json", encoding="utf-8") as f:
    key_dict = json.load(f)

cred = credentials.Certificate(key_dict)
initialize_app(cred, {
    "databaseURL": "https://solartracker-1a0a9-default-rtdb.firebaseio.com/"
})

'''
    set() : 쓰기 (WRITE) -> 그런데 강력한 쓰기라서 잘 안씀
    get() : 읽기 (READ)
    update() : 쓰기, 업데이트 (Write, Update)
    delete() : 삭제 (Delete)

'''

'''
ref = db.reference("users/user1")
ref.update({
    "name" : "테스트테스트",
    "age": 26
})

ref = db.reference("users/user2")
ref.update({
    "name" : "나는서연",
    "age": 26
})

# 여러 경로 동시에 수정
ref = db.reference("/")
ref.update({
    "users/user1/age": 27,
    "users/user2": { "name": "곰곰 아몬드 두유", "age": 28 }
})

ref = db.reference('users/-OaOC9oJYBlbrSPID4ol')
ref.delete()

'''

ref = db.reference("users/admin")
ref.update({
    "ID":"admin01",
    "PW":"0000",
    "name" : "서연",
    "age": 26,
    "phoneNum":"010-5244-0835",
    "gender":"F",
})

ref = db.reference("users/user1")
ref.update({
    "ID":"admin02",
    "PW":"0000",
    "name" : "바닐라코",
    "age": 13,
    "phoneNum":"010-0000-1234",
    "gender":"M",
})

ref = db.reference("users/user2")
ref.update({
    "ID":"admin03",
    "PW":"0000",
    "age": 22,
    "phoneNum":"010-3333-1234",
    "gender":"M",
})