#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WM;

#include <HTTPClient.h>

#include "hangul.h"

#define W_SSID "test1234"
#define W_PW "10101010"

void setup() {
  Serial.begin(115200);
  delay(100);

  WM.addAP(W_SSID,W_PW);

  Serial.println();
  Serial.println("Waiting Wifi.");

  while(WM.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  tft.begin();
  Serial.println("TFT STARTED");
  tft.fillScreen(TFT_BLACK);
}

void loop() {
    if(WM.run() == WL_CONNECTED) {
      HTTPClient http;

      http.begin("https://raw.githubusercontent.com/suyasuyazzang/smartMirror/main/codes/SMchecker/todaySM.txt");

      int httpCode = http.GET();

      if(httpCode > 0){
        Serial.print("GET CODE:"); Serial.println(httpCode);
        String payload = http.getString();
        Serial.println(payload);
        tft.fillScreen(TFT_BLACK);
        printHangul(&payload, 10, 10, TFT_WHITE, &tft);
      }else{
        Serial.println("Fail...");
      }
    }
    delay(3600000);
}
