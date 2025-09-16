#include <Servo.h>

Servo servoX;
Servo servoY;

int cds_1 = A0;
int cds_2 = A1;
int cds_3 = A2;
int cds_4 = A3;

int cds_1_min = 0, cds_1_max = 1023;  
int cds_2_min = 0, cds_2_max = 1023;  
int cds_3_min = 0, cds_3_max = 1023;  
int cds_4_min = 0, cds_4_max = 1023;  

int posX = 90;
int posY = 90;

void setup()
{
  servoX.attach(9);   // X축 서보
  servoY.attach(10);  // Y축 서보

  servoX.write(posX);
  servoY.write(posY);

  Serial.begin(9600);
}

// --- 센서값 읽기 함수 ---
int get_cds_1()
{
  int val = analogRead(cds_1);
  int res = map(val, cds_1_min - 10, cds_1_max + 10, 0, 100);
  return res;
}

int get_cds_2()
{
  int val = analogRead(cds_2);
  int res = map(val, cds_2_min - 10, cds_2_max + 10, 0, 100);
  return res;
}

int get_cds_3()
{
  int val = analogRead(cds_3);
  int res = map(val, cds_3_min - 10, cds_3_max + 10, 0, 100);
  return res;
}

int get_cds_4()
{
  int val = analogRead(cds_4);
  int res = map(val, cds_4_min - 10, cds_4_max + 10, 0, 100);
  return res;
}

void loop()
{
  int cds1 = get_cds_1();
  int cds2 = get_cds_2();
  int cds3 = get_cds_3();
  int cds4 = get_cds_4();

  int avgTop = (cds1 + cds2) / 2;
  int avgBottom = (cds3 + cds4) / 2;
  int avgLeft = (cds1 + cds3) / 2;
  int avgRight = (cds2 + cds4) / 2;

  int tolerance = 2;

  // --- Y축 제어 ---
  if (abs(avgTop - avgBottom) > tolerance) {
    if (avgTop > avgBottom) posY++;
    else posY--;
  }

  // --- X축 제어 ---
  if (abs(avgLeft - avgRight) > tolerance) {
    if (avgLeft > avgRight) posX++;
    else posX--;
  }

  // --- 안전 범위 제한 (0~180도) ---
  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  // --- 서보 제어 ---
  servoX.write(posX);
  servoY.write(posY);

  // 디버깅 출력
  Serial.print("cds1: "); Serial.print(cds1);
  Serial.print("  cds2: "); Serial.print(cds2);
  Serial.print("  cds3: "); Serial.print(cds3);
  Serial.print("  cds4: "); Serial.print(cds4);
  Serial.print("  posX: "); Serial.print(posX);
  Serial.print("  posY: "); Serial.println(posY);

  delay(100);
}
