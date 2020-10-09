# smartMirror
	ESP32 개발 보드와 TFT LCD를 사용한 소형 스마트 거울 개발입니다.
## 참조 링크
1. 부품 구매처
	1. [2.2인치 SPI TFT LCD 모듈 ILI9341](http://item.gmarket.co.kr/Item?goodscode=1467256245)
	2. <details>
    		<summary>핀 맵 이미지</summary>

		<img src= https://raw.githubusercontent.com/suyasuyazzang/smartMirror/main/images/ESP32-Pinout.png>

	</details>  
	
	3. [NodeMcu ESP32 Development Board BLE+WIFI](http://parts-parts.co.kr/product/detail.html?product_no=793&cate_no=163&display_group=1)
2. [아두이노 IDE에서 개발환경 만들기](https://deneb21.tistory.com/590)
3. [TFT_eSPI 라이브러리](https://github.com/Bodmer/TFT_eSPI)
4. [외국 예제](https://arduino-er.blogspot.com/2020/06/esp32-devkitc-28inch-240x320-spi-tft.html)
## TODO
#### 2020.10.8
- 한글 폰트를 생성해 출력해 봤으나, 크기가 너무 작고, 늘릴 수 없음(용량이 더 필요할 듯). 한글 조합형 출력을 시도해 봐야겠다.  
#### 2020.10.9
- 어라? 이거 원래 있는 폰트가 투명 배경을 지원하면, 겹쳐 쓰는 거로 만들 수 있지 않을까??????
- 한글 자소 분리 완성! 스프라이트 기능도 사용법을 연구하고 있다.
