#include <TFT_eSPI.h>
#include "fontSet2.h"

unsigned char cho[] =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1, 2, 4, 4, 4, 2, 1, 3, 0};
unsigned char cho2[] = {0, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 5};
unsigned char jong[] = {0, 0, 2, 0, 2, 1, 2, 1, 2, 3, 0, 2, 1, 3, 3, 1, 2, 1, 3, 3, 1, 1};

int utf8toUni(const char* inStr, int length, int* uniStr) {
  int cur = 0;

  for (int i = 0; i < length; i++) {
    if (inStr[i] < 0x80) { //맨 앞 바이트가 1이 아니면
      uniStr[cur] = (int)inStr[i]; //7비트를 사용하므로 그대로 옮김

    } else if ((inStr[i] & 0xE0) == 0xC0) { //맨 앞 바이트가 110이면
      uniStr[cur] = (int)(((int)(inStr[i] & 0x1F)) << 6 | (inStr[i + 1] & 0x3F));
      i++; //다음 바이트까지 썼으니까...

    } else if ((inStr[i] & 0xF0) == 0xE0) { //맨 앞 바이트가 1110이면
      uniStr[cur] = (int)(((int)(inStr[i] & 0x0F)) << 12 | (inStr[i + 1] & 0x3F) << 6 | (inStr[i + 2] & 0x3F));
      i += 2; //두 바이트 썼으니까...
    } else {
      uniStr[cur] = 0xFFFF; //버그!!!!!!!
    }

    cur++; //커서 한 칸 옮김
  }
  return cur--;
}

int isHangul(int uniChar) {
  return 0xAC00 <= uniChar && uniChar <= 0xD7A3;
}

int cutHangul(int uniChar, int * d) {
  if (isHangul(uniChar)) { //한글 범위 내의 글자라면
    int c = uniChar - 0xAC00; //일단 0xAC00을 빼고...

    d[0] = (c / (21 * 28)); //초성
    d[1] = ((c - (d[0] * 21 * 28)) / 28); //중성
    d[2] = (c - (d[0] * 21 * 28) - d[1] * 28); //종성

    d[0]++;
    d[1]++;

    return 0;
  } else { //한글 범위가 아니면 -1을 반환
    return -1;
  }
}

int printHangulChar(int* d, int x, int y, uint16_t color, TFT_eSPI* tft) {

  int b[3] = {0, 0, 0};

  if (d[2] == 0) {
    b[0] = cho[d[1]];
    if (d[0] == 1 || d[0] == 24) b[1] = 0;
    else b[1] = 1;
  } else {
    b[0] = cho2[d[1]];
    if (d[0] == 1 || d[0] == 24) b[1] = 2;
    else b[1] = 3;
    b[2] = jong[d[1]];
  }

  tft->drawXBitmap(x, y, glyphs[0][b[0]][d[0]], 16, 16, color);
  tft->drawXBitmap(x, y, glyphs[1][b[1]][d[1]], 16, 16, color);
  tft->drawXBitmap(x, y, glyphs[2][b[2]][d[2]], 16, 16, color);
}

int printHangul(String* inStr, int x, int y, uint16_t color, TFT_eSPI* tft) {

  char tempChar[256];
  inStr->toCharArray(tempChar, inStr->length());

  int uniStr[256] = {0};
  int uniStrLen = utf8toUni(tempChar, inStr->length(), uniStr);

  int curx = x;

  for (int i = 0; i < uniStrLen; i++) {
    int curChar = uniStr[i];
    if( curx > 210 || y > 300) continue;
    if(curChar == 10){
      y += 20;
      curx = x;
    }else if (isHangul(curChar)) {
      int d[3];
      cutHangul(curChar, d);
      printHangulChar(d, curx, y, color, tft);
      curx += 17;
    } else {
      tft->setTextColor(color, TFT_BLACK);
      tft->drawChar(curChar, curx, y, 2);
      curx += 8;
    }
  }
}
