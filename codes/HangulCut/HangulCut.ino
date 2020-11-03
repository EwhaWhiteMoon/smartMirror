#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#include "hangul.h"
#include "fontSet.h"

unsigned char cho[] =  {0,0,0,0,0,0,0,0,0,1,3,3,3,1,2,4,4,4,2,1,3,0};
unsigned char cho2[] = {0,5,5,5,5,5,5,5,5,6,7,7,7,6,6,7,7,7,6,6,7,5};
unsigned char jong[] = {0,0,2,0,2,1,2,1,2,3,0,2,1,3,3,1,2,1,3,3,1,1};
void setup() {
  Serial.begin(115200);
  Serial.println();

  tft.begin();
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  if (Serial.available()) {
    String inStr = Serial.readString();
    
    char inChar[128];
    inStr.toCharArray(inChar, inStr.length());

    int uniStr[128] = {0};
    int uniStrLen = utf8toUni(inChar, inStr.length(), uniStr);
        
    tft.fillScreen(TFT_BLACK);

    for (int i = 0; i < uniStrLen; i++) {
      int curChar = uniStr[i];
      Serial.println(curChar);
      if(isHangul(curChar)){
        int d[3];
        cutHangul(curChar, d);
        Serial.print("초성: "); Serial.println(d[0]++);
        Serial.print("중성: "); Serial.println(d[1]++);
        Serial.print("종성: "); Serial.println(d[2]);

        int b[3] = {0, 0, 0};

        if(d[2] == 0){
          b[0] = cho[d[1]];
          if(d[0] == 1 || d[0] == 24) b[1] = 0;
          else b[1] = 1;
        }else{
          b[0] = cho2[d[1]];
          if(d[0] == 1 || d[0] == 24) b[1] = 2;
          else b[1] = 3;
          b[2] = jong[d[1]];
        }
        
        tft.drawXBitmap(10 + i * 17, 10, glyphs[0][b[0]][d[0]], 16, 16, TFT_WHITE);
        tft.drawXBitmap(10 + i * 17, 10, glyphs[1][b[1]][d[1]], 16, 16, TFT_WHITE);
        tft.drawXBitmap(10 + i * 17, 10, glyphs[2][b[2]][d[2]], 16, 16, TFT_WHITE);
      }else{
        Serial.println("한글이 아닙니다.");
      }
    }
  }
}
