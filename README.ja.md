## Arduino Blink "minute repeater" Clock (ATtiny85 version)

### 概要
光の点滅で時刻を知らせる時計で, 視力の悪い人が暗闇で眼鏡なしでも読める時計として便利です。
光センサーによって、環境光にあわせた丁度よい輝度に調整します。
[リピーター時計](https://ja.wikipedia.org/wiki/%E3%83%AA%E3%83%94%E3%83%BC%E3%82%BF%E3%83%BC_(%E6%99%82%E8%A8%88))の光バージョンです。


### 時刻の読み方
色と点滅回数で以下のとおり時刻を表します。

* 白色で点滅する回数で0, 3, 6, 9時のいずれかを表します。
    - 1 回 → 0 時
    - 2 回 → 3 時
    - 3 回 → 6 時
    - 4 回 → 9 時

* 緑の点滅する回数を 0, 3, 6, 9 に足します。
    - 例:  白で3回点滅し、更に緑で2回点滅  → 8時(または20時)を表します

* 赤の点滅 → 回数かける 10 分が現在時刻の分の部分です。
    - 例:  赤く4回点滅 → 40分を表します

* 青の素早い点滅 → 0 ~ 9 分を表します。



### 時刻の設定方法
HourまたはMinuteボタンを押し続けると、押している間、時間を進めます。進めた時間・分の回数分だけLEDが点滅します。通常の時刻表示の点滅よりもゆっくり, 明るく点滅します。

* 「Hour」を長押し → 時間を60分進めます。(緑で点滅)
* 「Minute」を長押し  → 1分進めます。(青く点滅)
* ボタンを両方同時に長押し → 10分づつ進めます。(赤く点滅)

なお、ボタンは時刻設定の点滅(ゆっくりな点滅)が始まるまで押し続けてください。
(時刻表示の点滅の途中にボタンを押したばあい、時刻表示が全部完了するまで設定モードに入りません。)



### 必要な部品
* 基板
    - 表面実装版 (rev 0.5.1) [OSH Park](https://oshpark.com/shared_projects/CKZP3omf)
    - スルーホール (rev 0.2) [OSH Park](https://oshpark.com/shared_projects/mC1U04Ox)
* 部品リスト: [bom.txt](schematic/bom.txt) を参照して下さい。

### ポートの割当
* RST (GPIO #5) - Hour & Minute Buttons (using ADC above 2.2v reset threshold)
* GPIO #0       -  I2C SDA to RTC
* GPIO #1       -  Smart LED NeoPixel WS2812B
* GPIO #2       -  I2C SCL to RTC
* GPIO #3       -  Photo Cell
* GPIO #4       -  Power Control for LED, RTC, Photo Cell









