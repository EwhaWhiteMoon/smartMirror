#sourceFileName = input("입력 파일 이름을 입력하세요...")
#outFileName = input("출력 파일 이름을 입력하세요...")

sourceFileName = "H04.FNT"
outFileName = "fontSet2.h"
logFileName = "log.txt"

def reverseByte(b):
    return int(f'{b:08b}'[::-1],base=2)

fontSource = open(sourceFileName, 'rb')

fontOut = open(outFileName, 'w',encoding = 'utf8')
log = open(logFileName, 'w',encoding = 'utf8')

syl = ['초성', '중성', '종성']
sylCnt = [20, 22, 28]

initStr = "PROGMEM const unsigned char glyphs[3][8][28][32] = {\n"
fontOut.write(initStr)

for i in range(0,8*20 + 4*22 + 4*28): # 초성 8벌, 중성 4벌, 종성 4벌
    #               0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
    # 초성 20자 : 공백 ㄱ ㄲ ㄴ ㄷ ㄸ ㄹ ㅁ ㅂ ㅃ ㅅ ㅆ ㅇ ㅈ ㅉ ㅊ ㅋ ㅌ ㅍ ㅎ
    # 중성 22자 : 공백 ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅗ ㅘ ㅙ ㅚ ㅛ ㅜ ㅝ ㅞ ㅟ ㅠ ㅡ ㅢ ㅣ
    # 종성 28자 : 공백 ㄱ ㄲ ㄳ ㄴ ㄵ ㄶ ㄷ ㄹ ㄺ ㄻ ㄼ ㄽ ㄾ ㄿ ㅀ ㅁ ㅂ ㅃ ㅅ ㅆ ㅇ ㅈ ㅊ ㅋ ㅌ ㅍ ㅎ
    # ─────┬────┬──────────┬────────────────────────────┐
    #   ※  │ 벌 │ 받침유무 │ 결합                       │
    # 초성 │ 1  │  없음    │ ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅣ │
    #      │ 2  │  없음    │ ㅗ ㅛ ㅡ                   │
    #      │ 3  │  없음    │ ㅜ ㅠ                      │
    #      │ 4  │  없음    │ ㅘ ㅙ ㅚ ㅢ                │
    #      │ 5  │  없음    │ ㅝ ㅞ ㅟ                   │
    #      │ 6  │  있음    │ ㅏ ㅐ ㅑ ㅒ ㅓ ㅔ ㅕ ㅖ ㅣ │
    #      │ 7  │  있음    │ ㅗ ㅛ ㅜ ㅠ ㅡ             │
    #      │ 8  │  있음    │ ㅘ ㅙ ㅚ ㅢ ㅝ ㅞ ㅟ       │
    # ─────┼────┼──────────┼────────────────────────────┤
    # 중성 │ 1  │  없음    │ ㄱ ㅋ                      │
    #      │ 2  │  없음    │ ㄱ ㅋ 이외                 │
    #      │ 3  │  있음    │ ㄱ ㅋ                      │
    #      │ 4  │  있음    │ ㄱ ㅋ 이외                 │
    # ─────┼────┼──────────┼────────────────────────────┤
    # 종성 │ 1  │  있음    │ ㅏ ㅑ ㅘ                   │
    #      │ 2  │  있음    │ ㅓ ㅕ ㅚ ㅝ ㅟ ㅢ ㅣ       │
    #      │ 3  │  있음    │ ㅐ ㅒ ㅔ ㅖ ㅙ ㅞ          │
    #      │ 4  │  있음    │ ㅗ ㅛ ㅜ ㅠ ㅡ             │
    # ─────┴────┴──────────┴────────────────────────────┘

    #출력 파일 목표: char형 배열 glyphs를 만드는 코드. 
    #PROGMEM const unsigned char glyphs[초성 : 0, 중성 : 1, 종성: 2][벌 수 - 1][번째 수(최대 28)][data]
    
    # 0~159 초성, 160~247 중성, 248~359 종성

    if(i < 160): 
        sylType = 0
        lotType = int(i / 20)
        order = i % 20
    elif(i < 248): 
        sylType = 1
        lotType = int((i - 160) / 22)
        order = (i - 160) % 22
    else: 
        sylType = 2
        lotType = int((i - 248) / 28)
        order = (i - 248) % 28


    curFontData = fontSource.read(32) # 한글은 16 * 16 크기의 glyph를 가짐.
    
    log.write(f'-{syl[sylType]},{lotType + 1} 벌,{order} 번째 문자.--------------\n')
    for j, b in enumerate([curFontData[p] * 256 + curFontData[p + 1] for p in range(0, 32, 2)]):
        log.write(f'0x{curFontData[j*2]:02x} 0x{curFontData[j*2 + 1]:02x} : ' + f'{b:016b}\n'.replace('0','□ ').replace('1','■ '))


    if(i == 0 or i == 160 or i == 248): fontOut.write(f'\u007b // {syl[sylType]} 시작\n')

    if(order == 0): fontOut.write(f'    \u007b // {syl[sylType]} {lotType + 1} 벌 시작\n')

    fontOut.write('        {')
    for j in curFontData:
        fontOut.write(f'0x{reverseByte(j):02x},')
    fontOut.write(f'\u007d, //{syl[sylType]},{lotType + 1} 벌,{order} 번째 문자.\n')

    if(i == 159 or i == 247 or i == 359): fontOut.write(f'    \u007d,//{syl[sylType]} 끝\n')

    if(order == sylCnt[sylType] - 1): fontOut.write('},\n')

fontOut.write('};')