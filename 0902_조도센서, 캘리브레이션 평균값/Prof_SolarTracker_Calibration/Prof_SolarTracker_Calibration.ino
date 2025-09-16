int cds_1 = A0;
int cds_2 = A1;
int cds_3 = A2;
int cds_4 = A3;

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
  // put your main code here, to run repeatedly:

}
