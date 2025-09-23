#include <Servo.h> // 서보라이브러리

/* 서보 객체와 초기각도(90도, 중간위치) 설정 */
Servo servoX;
Servo servoY;

int posX = 90;
int posY = 90;

int sensorMin_A0 = 0, sensorMax_A0 = 1023;
int sensorMin_A1 = 0, sensorMax_A1 = 1023;
int sensorMin_A2 = 0, sensorMax_A2 = 1023;
int sensorMin_A3 = 0, sensorMax_A3 = 1023;

// 핀
int cds_1 = A0; // 왼쪽 아래
int cds_2 = A1; // 오른쪽 아래
int cds_3 = A2; // 왼쪽 위
int cds_4 = A3; // 오른쪽 위

// 오차값
int cds_1_max = 988;
int cds_1_min = 709;

int cds_2_max = 981;
int cds_2_min = 586;

int cds_3_max = 1006;
int cds_3_min = 573;

int cds_4_max = 809;
int cds_4_min = 641;

// 센서 읽기 함수
int get_cds_1() { return analogRead(cds_1); }
int get_cds_2() { return analogRead(cds_2); }
int get_cds_3() { return analogRead(cds_3); }
int get_cds_4() { return analogRead(cds_4); }

void setup() 
{
  Serial.begin(9600);

  servoX.attach(9);
  servoY.attach(10);

  servoX.write(posX);
  servoY.write(posY);

  // 캘리브레이션 부분 제거
}

void loop() {
  int raw_A0 = get_cds_1();
  int raw_A1 = get_cds_2();
  int raw_A2 = get_cds_3();
  int raw_A3 = get_cds_4();

  int cal_A0 = map(constrain(raw_A0, sensorMin_A0, sensorMax_A0), sensorMin_A0, sensorMax_A0, 0, 100);
  int cal_A1 = map(constrain(raw_A1, sensorMin_A1, sensorMax_A1), sensorMin_A1, sensorMax_A1, 0, 100);
  int cal_A2 = map(constrain(raw_A2, sensorMin_A2, sensorMax_A2), sensorMin_A2, sensorMax_A2, 0, 100);
  int cal_A3 = map(constrain(raw_A3, sensorMin_A3, sensorMax_A3), sensorMin_A3, sensorMax_A3, 0, 100);

  int left   = (cal_A0 + cal_A2) / 2; // 왼쪽: A0(왼쪽 아래) + A2(왼쪽 위)
  int right  = (cal_A1 + cal_A3) / 2; // 오른쪽: A1(오른쪽 아래) + A3(오른쪽 위)
  int top    = (cal_A2 + cal_A3) / 2; // 위쪽: A2 + A3
  int bottom = (cal_A0 + cal_A1) / 2; // 아래쪽: A0 + A1

  int moveX = 0, moveY = 0;
  int stepVal = 5;

  // --- 추가된 부분: 일정 각도 범위에서 멈추기 ---
  int thresholdX = 3; // X축 목표 범위
  int thresholdY = 3; // Y축 목표 범위
  // --------------------------------------------

  if(abs(left - right) > thresholdX)
  {
    if(left < right) { posX -= stepVal; moveX = stepVal; }
    else { posX += stepVal; moveX = stepVal; }
  }

  if(abs(top - bottom) > thresholdY) 
  {
    if(top > bottom) { posY += stepVal; moveY = stepVal; } // 위가 더 밝으면 올림
    else { posY -= stepVal; moveY = stepVal; }
  }

  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  servoX.write(posX);
  servoY.write(posY);

  Serial.print("A0:"); Serial.print(cal_A0); // 왼쪽 아래
  Serial.print(" A1:"); Serial.print(cal_A1); // 오른쪽 아래
  Serial.print(" A2:"); Serial.print(cal_A2); // 왼쪽 위
  Serial.print(" A3:"); Serial.print(cal_A3); // 오른쪽 위
  Serial.print("     ");
  Serial.print(" X:"); Serial.print(posX);
  Serial.print(" Y:"); Serial.print(posY);

  Serial.print("     ");
  if(moveX==0 && moveY==0) Serial.print(" NoMove");
  else 
  {
    if(left < right) 
    {
      Serial.print(" Left");  
    }
    else
    {
      Serial.print(" Right");             
    }

    if(top > bottom)
    { 
      Serial.print(" Down"); 
    }
    else
    { 
      Serial.print(" Up");
    }
  }
  Serial.println();

  delay(100);
}
