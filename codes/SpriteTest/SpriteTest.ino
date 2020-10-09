#include <TFT_eSPI.h>

#define WIDTH  128
#define HEIGHT 128

TFT_eSPI tft = TFT_eSPI(); //tft 개체 선언

TFT_eSprite spr = TFT_eSprite(&tft); // spr 스프라이트 객체를 tft 객체 포인터로 초기화

int n = 0;

void setup() {
  Serial.begin(250000);
  Serial.println();

  tft.init(); //tft 객체 초기화

  spr.createSprite(WIDTH, HEIGHT); //크기 정해서 스프라이트 생성

  tft.fillScreen(TFT_BLACK); //화면 검게 초기화
  spr.fillSprite(TFT_BLUE);

  int xw = tft.width()/2;   // xw, yh is middle of screen
  int yh = tft.height()/2;
  
  spr.setPivot(xw,yh);
}

void loop() {  
  spr.pushRotated(n+=10, TFT_GREEN);
  if(n == 360) n = 0;
  delay(100);
  tft.fillScreen(TFT_BLACK);
}
