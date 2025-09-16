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

  int val_20[4] = {0, 0, 0, 0};   
  int val_40[4] = {0, 0, 0, 0};   
  int temp[4][50] = {{0,},};

  for(int l=0; l<2; l++)
  {
    Serial.println("Ready for Chacking 10sec...");
    for(int i=0; i<10; i++)
    {
      Serial.print(10-i); 
      Serial.print("  ");
      delay(1000);
    }
    Serial.println("");

    for(int i=0; i<50; i++)
    {
      temp[0][i] = analogRead(cds_1);
      temp[1][i] = analogRead(cds_2);
      temp[2][i] = analogRead(cds_3);
      temp[3][i] = analogRead(cds_4);
      delay(20); 
    }

    for(int k=0; k<25; k++)
    {
      for(int i=0; i<(49-k); i++)
      {
        for(int j=0; j<4; j++)
        {
          if(temp[j][i] > temp[j][i+1])
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
        Serial.print("["); Serial.print(i); Serial.print("] : "); 
        Serial.print(val_20[i]); 
        Serial.print("  //  ");
      }
      else 
      {
        val_40[i] = temp[i][25];
        Serial.print("val_40 CdS"); 
        Serial.print("["); Serial.print(i); Serial.print("] : "); 
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

  int left   = (cal_A0 + cal_A2) / 2; // 왼쪽: A0(왼쪽 아래) + A2(왼쪽 위)
  int right  = (cal_A1 + cal_A3) / 2; // 오른쪽: A1(오른쪽 아래) + A3(오른쪽 위)
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
