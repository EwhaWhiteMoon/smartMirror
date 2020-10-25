int utf8toUni(const char* inStr, int length, int* uniStr) {
  int cur = 0;

  for (int i = 0; i < length; i++) {

    if ((inStr[i] & 0x80) != 0x80) { //맨 앞 바이트가 1이 아니면
      uniStr[cur] = inStr[i]; //7비트를 사용하므로 그대로 옮김

    } else if ((inStr[i] & 0xE0) == 0xC0) { //맨 앞 바이트가 110이면
      /*            첫 바이트의 뒤쪽 5칸 마스크  6칸 밀고  다음 바이트의 뒤쪽 6칸 마스크 */
      uniStr[cur] = ((int)(inStr[i] & 0x1F)) << 6 + ((int)(inStr[i + 1] & 0x3F));
      i++; //다음 바이트까지 썼으니까...

    } else if ((inStr[i] & 0xF0) == 0xE0) { //맨 앞 바이트가 1110이면
      /*            첫 바이트의 뒤쪽 4칸 마스크  12칸 밀고  다음 바이트의 뒤쪽 6칸 마스크 6칸 밀고 또 다음 바이트의 뒤쪽 6칸 마스크*/
      uniStr[cur] = (((int)(inStr[i] & 0x0F)) << 12) + (((int)(inStr[i + 1] & 0x3F)) << 6) + ((int)(inStr[i + 2] & 0x3F));
      i += 2; //두 바이트 썼으니까...

    } else {
      uniStr[cur] = 0xFFFF; //버그!!!!!!!
    }

    cur++; //커서 한 칸 옮김
  }
  return cur--;
}

int isHangul(int uniChar){
  return 0xAC00 <= uniChar && uniChar <= 0xD7A3;
}

int cutHangul(int uniChar, int * d) {
  if (isHangul(uniChar)) { //한글 범위 내의 글자라면
    int c = uniChar - 0xAC00; //일단 0xAC00을 빼고...

    d[0] = c / (21 * 28); //초성
    d[1] = (c - (d[0] * 21 * 28)) / 28; //중성
    d[2] = c - (d[0] * 21 * 28) - d[1] * 28; //종성

    return 0;
  }else{ //한글 범위가 아니면 -1을 반환
    return -1;
  }
}