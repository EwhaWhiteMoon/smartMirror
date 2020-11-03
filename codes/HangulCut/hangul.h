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

    } else if ((inStr[i] & 0xF8) == 0xF0){
      uniStr[cur] = 0xFFFF; //이 범위 문자가 들어오면 처리 못하니까 일단 임시로...
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
