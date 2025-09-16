#include <Servo.h>

Servo servoY; // 위-아래 (세로)
Servo servoX; // 왼쪽-오른쪽 (가로)

int posX = 90; // 초기 가로 위치
int posY = 45; // 초기 세로 위치 (0~90 범위)

void setup() 
{
  servoY.attach(9);  // 세로 서보 연결 핀
  servoX.attach(10); // 가로 서보 연결 핀

  servoY.write(posY);
  servoX.write(posX);
}

void loop() {
  // 예시: 날개 좌우 자동 스윙 (0~180도)
  for(posX = 0; posX <= 180; posX += 1) 
  {
    servoX.write(posX);
    delay(15);
  }
  for(posX = 180; posX >= 0; posX -= 1) 
  {
    servoX.write(posX);
    delay(15);
  }

  // 예시: 날개 위아래 작은 움직임 (0~90도)
  for(posY = 0; posY <= 90; posY += 1) 
  {
    servoY.write(posY);
    delay(20);
  }
  for(posY = 90; posY >= 0; posY -= 1) 
  {
    servoY.write(posY);
    delay(20);
  }
}
