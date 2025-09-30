import serial
import time

def parse_line(line: str):
    """
    아두이노 시리얼 문자열을 파싱해서 딕셔너리로 변환
    예시 입력:
    "A0%73%A1%72%A2%78%A3%83%      X:110 Y:180      Left Down"
    """
    result = {}

    # 1) % 단위로 자르기
    parts = [p for p in line.split('%') if p.strip() != ""]

    # 2) A0, A1 ... 센서값 추출 (짝수=이름, 홀수=값)
    for i in range(0, len(parts) - 1, 2):
        if parts[i].startswith("A"):
            key = parts[i]
            try:
                value = int(parts[i + 1])
                result[key] = value
            except ValueError:
                continue

    # 3) 마지막 문자열에서 X, Y, 위치 정보 추출
    last_part = parts[-1].strip()
    tokens = last_part.split()

    for token in tokens:
        if token.startswith("X:"):
            result["X"] = int(token.replace("X:", ""))
        elif token.startswith("Y:"):
            result["Y"] = int(token.replace("Y:", ""))

    # X:, Y:가 아닌 부분은 pos로 저장
    others = [t for t in tokens if not t.startswith(("X:", "Y:"))]
    if others:
        result["pos"] = " ".join(others)

    return result


def main():
    # 아두이노 포트 설정 (환경에 맞게 수정하세요)
    arduino = serial.Serial(port='COM4', baudrate=9600, timeout=1)
    time.sleep(2)  # 아두이노 자동 리셋 대기

    print("시리얼 통신 시작...")

    while True:
        if arduino.in_waiting > 0:
            line = arduino.readline().decode('utf-8', errors='ignore').strip()
            if line:  # 빈 줄이 아닐 경우
                data = parse_line(line)
                print(data)


if __name__ == "__main__":
    main()
