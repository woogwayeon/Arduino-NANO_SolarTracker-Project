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
int solarPin = A6; // 태양광 전기 센서

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

// 평균 계산용 버퍼
#define N_AVG 10
float solarBuf[N_AVG] = {0};
int solarIndex = 0;

void setup() 
{
  Serial.begin(9600);

  servoX.attach(9);
  servoY.attach(10);

  servoX.write(posX);
  servoY.write(posY);
}

void loop() {
  int raw_A0 = get_cds_1();
  int raw_A1 = get_cds_2();
  int raw_A2 = get_cds_3();
  int raw_A3 = get_cds_4();
  int raw_A6 = analogRead(solarPin); // 태양광 전기 센서 읽기

  int cal_A0 = map(constrain(raw_A0, sensorMin_A0, sensorMax_A0), sensorMin_A0, sensorMax_A0, 0, 100);
  int cal_A1 = map(constrain(raw_A1, sensorMin_A1, sensorMax_A1), sensorMin_A1, sensorMax_A1, 0, 100);
  int cal_A2 = map(constrain(raw_A2, sensorMin_A2, sensorMax_A2), sensorMin_A2, sensorMax_A2, 0, 100);
  int cal_A3 = map(constrain(raw_A3, sensorMin_A3, sensorMax_A3), sensorMin_A3, sensorMax_A3, 0, 100);

  int left   = (cal_A0 + cal_A2) / 2; // 왼쪽: A0 + A2
  int right  = (cal_A1 + cal_A3) / 2; // 오른쪽: A1 + A3
  int top    = (cal_A2 + cal_A3) / 2; // 위쪽: A2 + A3
  int bottom = (cal_A0 + cal_A1) / 2; // 아래쪽: A0 + A1

  int moveX = 0, moveY = 0;
  int stepVal = 5;

  if(abs(left - right) > 5)
  {
    if(left < right) { posX -= stepVal; moveX = stepVal; }
    else { posX += stepVal; moveX = stepVal; }
  }

  if(abs(top - bottom) > 5) 
  {
    if(top > bottom) { posY += stepVal; moveY = stepVal; } // 위가 더 밝으면 올림
    else { posY -= stepVal; moveY = stepVal; }
  }

  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  servoX.write(posX);
  servoY.write(posY);

  // 기존 volt_A6 계산 그대로
  float volt_A6 = map(raw_A6, 0, 1023, 0, 2500);

  // 평균 계산용 배열에 저장
  solarBuf[solarIndex] = volt_A6;
  solarIndex = (solarIndex + 1) % N_AVG;

  // 최근 N_AVG개 평균 계산
  float volt_A6_avg = 0;
  for(int i = 0; i < N_AVG; i++) volt_A6_avg += solarBuf[i];
  volt_A6_avg /= N_AVG;

  // 시리얼 출력
  Serial.print("A0%"); Serial.print(cal_A0);
  Serial.print("%A1%"); Serial.print(cal_A1);
  Serial.print("%A2%"); Serial.print(cal_A2);
  Serial.print("%A3%"); Serial.print(cal_A3);
  Serial.print("%");
  Serial.print("     ");
  Serial.print(" X:"); Serial.print(posX);
  Serial.print(" Y:"); Serial.print(posY);

  Serial.print("     ");
  if(moveX == 0 && moveY == 0) Serial.print(" NoMove");
  else 
  {
    if(left < right) Serial.print(" Left");  
    else Serial.print(" Right");             

    if(top > bottom) Serial.print(" Down"); 
    else Serial.print(" Up");
  }

  // 평균값 출력 (원래 계산식 유지)
  Serial.print("  %Volt%"); 
  Serial.print(volt_A6_avg / 100); // 0~5V 변환
  Serial.print("V%");

  Serial.println();

  delay(100);
}
