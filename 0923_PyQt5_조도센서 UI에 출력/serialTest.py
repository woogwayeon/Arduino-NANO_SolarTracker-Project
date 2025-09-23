import serial
import time

# 아두이노 포트 확인 (Windows: COM3, COM4... / Mac: /dev/tty.usbmodem... / Linux: /dev/ttyUSB0 등)
arduino = serial.Serial(port='COM4', baudrate=9600, timeout=1)
time.sleep(2)  # 아두이노 리셋 대기 시간

# 아두이노에 데이터 보내기
arduino.write(b'Hello Arduino!\n')

while True:
    # 아두이노에서 들어오는 데이터 읽기
    if arduino.in_waiting > 0:
        data = arduino.readline().decode().strip()
        print(f"Arduino says: {data}")
