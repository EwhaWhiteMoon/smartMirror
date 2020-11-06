#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#include "hangul.h"

String testStr = String("테스트 문자열\n");

void setup() {
  Serial.begin(115200);
  Serial.println();

  tft.begin();
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  if (Serial.available()) {
    String inStr = Serial.readString();


    tft.fillScreen(TFT_BLACK);

    printHangul(&inStr, 10, 40, TFT_WHITE, &tft);
    printHangul(&testStr, 10, 80, TFT_BLUE, &tft);
  }
}
