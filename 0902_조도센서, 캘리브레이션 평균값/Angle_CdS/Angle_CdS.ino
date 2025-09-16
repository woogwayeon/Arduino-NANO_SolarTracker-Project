#include <Servo.h>
#define POS_SIZE 4

Servo servoX;   // 좌우 움직임
Servo servoY;   // 상하 움직임

int posX = 90;  // 초기 각도 (가운데)
int posY = 90;

// 센서 최소/최대값 (캘리브레이션용)
int sensorMin_A0, sensorMax_A0;
int sensorMin_A1, sensorMax_A1;
int sensorMin_A2, sensorMax_A2;
int sensorMin_A3, sensorMax_A3;

void setup() {
  Serial.begin(9600);
  Serial.println("start");

  servoX.attach(9);    // X축 서보모터 핀
  servoY.attach(10);   // Y축 서보모터 핀

  servoX.write(posX);
  servoY.write(posY);

  // --- 캘리브레이션 (20번 읽어서 평균값 계산) ---
  long sum_A0 = 0;
  long sum_A1 = 0; 
  long sum_A2 = 0; 
  long sum_A3 = 0;


  for (int i = 0; i < 20; i++) 
  {
    sum_A0 += analogRead(A0);
    sum_A1 += analogRead(A1);
    sum_A2 += analogRead(A2);
    sum_A3 += analogRead(A3);
    delay(50);
  }

  int avg_A0 = sum_A0 / 20;
  int avg_A1 = sum_A1 / 20;
  int avg_A2 = sum_A2 / 20;
  int avg_A3 = sum_A3 / 20;

  // 센서 범위 설정 (±200 여유)
  // A0 센서 평균값 = 800 -> ±200 범위 = 600~1000
  sensorMin_A0 = avg_A0 - 200;  
  sensorMax_A0 = avg_A0 + 200;
  
  sensorMin_A1 = avg_A1 - 200;  
  sensorMax_A1 = avg_A1 + 200;
 
  sensorMin_A2 = avg_A2 - 200;  
  sensorMax_A2 = avg_A2 + 200;
  
  sensorMin_A3 = avg_A3 - 200;  
  sensorMax_A3 = avg_A3 + 200;
}

void loop() {
  // --- 센서 값 읽기 ---
  int raw_A0 = analogRead(A0);
  int raw_A1 = analogRead(A1);
  int raw_A2 = analogRead(A2);
  int raw_A3 = analogRead(A3);

  // --- 센서값 보정 (0~100 범위) ---
  int cal_A0 = map(constrain(raw_A0, sensorMin_A0, sensorMax_A0), sensorMin_A0, sensorMax_A0, 0, 100);
  int cal_A1 = map(constrain(raw_A1, sensorMin_A1, sensorMax_A1), sensorMin_A1, sensorMax_A1, 0, 100);
  int cal_A2 = map(constrain(raw_A2, sensorMin_A2, sensorMax_A2), sensorMin_A2, sensorMax_A2, 0, 100);
  int cal_A3 = map(constrain(raw_A3, sensorMin_A3, sensorMax_A3), sensorMin_A3, sensorMax_A3, 0, 100);

  // --- 좌우/상하 평균 ---
  int left   = (cal_A0 + cal_A3) / 2;
  int right  = (cal_A1 + cal_A2) / 2;
  int top    = (cal_A2 + cal_A3) / 2;
  int bottom = (cal_A0 + cal_A1) / 2;

  // --- 민감도 (값 차이가 이 이상이면 움직임) ---
  int tolerance = 5;

  // --- 이동 방향 기록 ---
  int moveX = 0;
  int moveY = 0;

  // --- X축 제어 ---
  if (abs(left - right) > tolerance) 
  {
    if (left < right) 
    { 
      posX -= 1; 
      moveX = -1; 
    } 
    else 
    { 
      posX += 1; 
      moveX = 1; 
    }
  }

  // --- Y축 제어 ---
  if (abs(top - bottom) > tolerance) 
  {
    if (top < bottom) 
    { 
      posY += 1; 
      moveY = 1; 
    } 
    else 
    { 
      posY -= 1; 
      moveY = -1; 
    }
  }

  // --- 안전 범위 제한 (0~180도) ---
  // 서보모터가 물리적으로 회전할 수 있는 최대 범위가 0 ~ 180도
  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  // --- 모터 이동 ---
  servoX.write(posX);
  servoY.write(posY);

  // --- 출력 ---
  Serial.print("A0:"); Serial.print(cal_A0);
  Serial.print("     A1:"); Serial.print(cal_A1);
  Serial.print("     A2:"); Serial.print(cal_A2);
  Serial.print("     A3:"); Serial.print(cal_A3);

  Serial.print("  |   X:"); Serial.print(posX);
  Serial.print("    Y:"); Serial.print(posY);

  Serial.print("  | ");
  if (moveX == 0 && moveY == 0) 
  {
    Serial.print("NoMove");
  } 
  else 
  {
    if (moveX == -1) Serial.print("Left-1 ");
    else if (moveX == 1) Serial.print("Right+1 ");
    if (moveY == -1) Serial.print("Down-1 ");
    else if (moveY == 1) Serial.print("Up+1 ");
  }
  Serial.println();

  delay(100);
}
