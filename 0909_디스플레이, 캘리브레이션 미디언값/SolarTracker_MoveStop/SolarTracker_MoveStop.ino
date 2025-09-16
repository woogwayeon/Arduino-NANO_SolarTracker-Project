#include <Servo.h>

Servo servoX;
Servo servoY;
int posX = 90;
int posY = 90;

int sensorMin_A0 = 0, sensorMax_A0 = 1023;
int sensorMin_A1 = 0, sensorMax_A1 = 1023;
int sensorMin_A2 = 0, sensorMax_A2 = 1023;
int sensorMin_A3 = 0, sensorMax_A3 = 1023;

// 핀?
int cds_1 = A0;
int cds_2 = A1;
int cds_3 = A2;
int cds_4 = A3;

// 오차값
int cds_1_max = 988;
int cds_1_min = 709;

int cds_2_max = 981;
int cds_2_min = 586;

int cds_3_max = 1006;
int cds_3_min = 573;

int cds_4_max = 809;
int cds_4_min = 641;

// 센서 읽기 함수 : 각각 최대 최소값을 균일하게 매핑해줄거에요
int get_cds_1()
{
  int val = analogRead(cds_1);
  int res = map(val, cds_1_min - 10, cds_1_max + 10, 0, 1000);
  return val;
}

int get_cds_2()
{
  int val = analogRead(cds_2);
  int res = map(val, cds_2_min - 10, cds_2_max + 10, 0, 1000);
  return val;
}

int get_cds_3()
{
  int val = analogRead(cds_3);
  int res = map(val, cds_3_min - 10, cds_3_max + 10, 0, 1000);
  return val;
}

int get_cds_4()
{
  int val = analogRead(cds_4);
  int res = map(val, cds_4_min - 10, cds_4_max + 10, 0, 1000);
  return val;
}

void setup() 
{
  Serial.begin(9600);

  // 각도마다 4개니까 두개 만듦
  int val_20[4] = {0, 0, 0, 0};
  int val_40[4] = {0, 0, 0, 0};

  // 임시배열 50
  int temp[4][50] = {{0,},}; // C++문법, 0으로 다 초기화



  // 중간값 구하기2. 버블 정렬
  for(int l=0; l<2; l++) // 4. 전체 for문 (2번 구해야 해서)
  {
    Serial.println("Ready for Chacking 10sec...");
    for(int i=0; i<10; i++)
    {
      Serial.print(10-i);
      Serial.print("  ");
      delay(1000);
    }
    Serial.println("");

    // 중간값 구하기1. : 50개 정도
    for(int i=0; i<50; i++)
    {
      temp[0][i] = analogRead(cds_1);
      temp[1][i] = analogRead(cds_2);
      temp[2][i] = analogRead(cds_3);
      temp[3][i] = analogRead(cds_4);
      delay(20);
    }

    for(int k=0; k<25; k++) // 3. 중간값이니까 25, 26 이렇게 되면 된다
    {
      for(int i=0; i<(49-k); i++) // 1. 49번씩 비교해야함 n-1
      {
        for(int j=0; j<4; j++) // 2. 조도센서 4개
        {
          if(temp[j][i] > temp[j][i+1])   // 여기서 j로 고쳐야 함
          {
            int temp_c = temp[j][i];
            temp[j][i] = temp[j][i+1];
            temp[j][i+1] = temp_c; 
          }
        }
      }
    }

    for(int i=0; i<4; i++)
    {
      Serial.print("  ");
      if(l == 0) 
      {
        val_20[i] = temp[i][25];
        Serial.print("val_20 CdS");
        Serial.print("[");
        Serial.print(i);
        Serial.print("] : ");
        Serial.print(val_20[i]);
        Serial.print("  //  ");
      }
      else 
      {
        val_40[i] = temp[i][25];
        Serial.print("val_40 CdS");
        Serial.print("[");
        Serial.print(i);
        Serial.print("] : ");
        Serial.print(val_40[i]);
        Serial.print("  //  ");
      }
    }
    Serial.println("");
  }
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

  int left   = (cal_A0 + cal_A3) / 2;
  int right  = (cal_A1 + cal_A2) / 2;
  int top    = (cal_A2 + cal_A3) / 2;
  int bottom = (cal_A0 + cal_A1) / 2;

  int tolerance = 5;
  int moveX = 0, moveY = 0;

  if(abs(left - right) > tolerance) 
  {
    if(left < right)
    { 
      posX -= 1; moveX = -1; 
    }
    else 
    { 
      posX += 1; moveX = 1; 
    }
  }

  if(abs(top - bottom) > tolerance) 
  {
    if(top < bottom)
    { 
      posY += 1; moveY = 1; 
    }
    else 
    { 
      posY -= 1; moveY = -1; 
    }
  }

  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  servoX.write(posX);
  servoY.write(posY);

  Serial.print("A0:"); Serial.print(cal_A0);
  Serial.print(" A1:"); Serial.print(cal_A1);
  Serial.print(" A2:"); Serial.print(cal_A2);
  Serial.print(" A3:"); Serial.print(cal_A3);
  Serial.print(" X:"); Serial.print(posX);
  Serial.print(" Y:"); Serial.print(posY);

  if(moveX==0 && moveY==0) Serial.print(" NoMove");
  else 
  {
    if(moveX==-1) Serial.print(" Left-1");
    else if(moveX==1) Serial.print(" Right+1");
    
    if(moveY==-1) Serial.print(" Down-1");
    else if(moveY==1) Serial.print(" Up+1");
  }
  Serial.println();

  delay(100);
}
