#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

int i = 0;
char str[256] = "";

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000);

  display.clearDisplay(); // Clear the buffer
  //testdrawchar();  // Draw characters of the default font
    
  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);


}

void loop() {

  if (Serial.available()) 
  {
    char data = Serial.read();
    Serial.print(data);

    if (data != '\n') 
    {
      str[i++] = data;
      str[i] = '\0';  // 문자열 종료 문자
    }

    if (data == '\n') 
    {
      display.clearDisplay();
      display.setTextSize(2);       // 글자 크기 조절 가능
      display.setTextColor(WHITE);
      display.setCursor(0,0);       // 출력 시작 위치
      display.println(str);         // 한 글자씩이 아니라 전체 문자열 출력
      display.display();
      delay(100);      
                
      i = 0;                        
      str[0] = '\0';  // 줄 바뀌면 초기화
    }

    
  }

}