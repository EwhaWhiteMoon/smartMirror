```c
TFT_eSprite spr = TFT_eSprite(&tft); // spr 스프라이트 객체를 tft 객체 포인터로 초기화
//까지 setup 밖에서

spr.setColorDepth(8); //색 깊이 설정, 설정 안 하면 16임

spr.createSprite(Width, Height); //크기 정해서 스프라이트 생성
spr.pushRotated(Angle, Color); //Angle 만큼 회전해서 push, Color은 투명으로 취급
spr.setPivot(x, y);     // 스프라이트의 피벗 지정

```
