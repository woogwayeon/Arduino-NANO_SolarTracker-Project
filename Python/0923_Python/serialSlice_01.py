import serial

# 시리얼 포트 설정 (Windows: COM4, Linux: /dev/ttyUSB0, Mac: /dev/tty.usbmodemxxx)
arduino = serial.Serial(port='COM4', baudrate=9600, timeout=1)

while True:
    if arduino.in_waiting > 0:
        line = arduino.readline().decode('utf-8').strip()
        print("Raw:", line)

        # % 기준으로 분리
        parts = line.split('%')
        # 빈 문자열 제거
        parts = [p for p in parts if p != ""]

        print("Split parts:", parts)

        # 예: 센서 값만 추출 (A0, A1, A2, A3)
        sensor_values = []
        for p in parts:
            if p.startswith("A"):
                sensor_values.append(p)
        
        print("Sensor values:", sensor_values)
