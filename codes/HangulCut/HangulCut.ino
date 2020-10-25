#include "hangul.h"

void setup() {
  Serial.begin(115200);
  Serial.println();
}

void loop() {
  if (Serial.available()) {
    String inStr = Serial.readString();
    
    char inChar[128];
    inStr.toCharArray(inChar, inStr.length());

    int uniStr[128] = {0};
    int uniStrLen = utf8toUni(inChar, inStr.length(), uniStr);

    for (int i = 0; i < uniStrLen; i++) {
      int curChar = uniStr[i];
      if(isHangul(curChar)){
        int d[3];
        cutHangul(curChar, d);
        Serial.print("초성: "); Serial.println(d[0]);
        Serial.print("중성: "); Serial.println(d[1]);
        Serial.print("종성: "); Serial.println(d[2]);
      }else{
        Serial.print("한글이 아닙니다.");
      }
    }
  }
}
