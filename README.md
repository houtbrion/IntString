# IntString

ファイルの読み取りや通信プロトコルの処理では，文字列となった数字を解析する必要があります．その際に数字の列を読み取り，整数に変換して内容を判断することは珍しくありません．Arduinoでは，Stringクラスに``long toInt()``というメンバ関数があり，longの出力をする関数はすでにありますが，正負の符号の判定，16進数，2進数の解析機能はありません．

また，CPUアーキテクチャの違いによる整数型の差が出るもの面倒だったため，``int8``や``uint32_t``のようにbit数指定の整数型に変換する関数群に加えて，boolを取り扱う関数を用意しました．

動作を確認した機種は以下の通り．
|CPUアーキ|機種|
|---|---|
|AVR|Mega2560|
|SAMD|MKR WiFi 1010|
|ESP32|ESP32 Dev Kit|

ESP8266やSAM(Due)での動作確認はしていません．

## 文字列→整数変換機能

### 変換対象の文字列フォーマット
本ライブラリで，解釈可能な数字のフォーマットは以下のとおりです．

| 種類 | フォーマット(正規表現で記載) |
|---|---|
|  2進数 |``[+\|-]0b[0\|1]+``|
|  8進数 |``[+\|-]0o[0-7]+``  |
| 10進数 |``[+\|-][0-9]+``  |
| 16進数 |``[+\|-]0x[0-9,a,A,b,B,c,C,d,D,e,E,f,F]+`` |

上の表を見てわかる通り，記号と数字の間など全ての場所に空白が存在してはいけません．また，値を示す部分の冒頭が0で始まっていても大丈夫です．冒頭の``0``の連続は無視します．このフォーマットは通常のCやC++のものとは異なります(8進数と0で始まる10進整数の両方をサポートするため)．

### 変換用関数
文字列を整数に変換する関数は``intXX_t strToIntXX(String)``もしくは``intXX_t strToUintXX(String)``の形式になっており，``XX``はbit数になっています．

``int8_t``は``-128``から``127``の範囲の値となります．解析対象の文字列の値がこの範囲より大きい場合は``127``を返します．値が範囲より小さい場合は``-128``を返す動作をします．なお，文字列のうち，記号を示す部分以外に不正な文字が含まれていると，``0``を返します．

現状実装している関数は以下の通りです(8から64bitの符号ありなし両方)．
- ``int8_t   strToInt8(String str)``
- ``uint8_t  strToUint8(String str)``
- ``int16_t  strToInt16(String str)``
- ``uint16_t strToUint16(String str)``
- ``int32_t  strToInt32(String str)``
- ``uint32_t strToUint32(String str)``
- ``int64_t strToInt64(String str)``
- ``uint64_t strToUint64(String str)``

## 数値→文字列変換機能

- ``String int32ToStr(int32_t val, uint8_t type=DEC, bool header=true)``
- ``String uint32ToStr(uint32_t val, uint8_t type=DEC, bool header=true)``
- ``String int8ToStr(int8_t val, uint8_t type=DEC, bool header=true)``
- ``String uint8ToStr(uint8_t val, uint8_t type=DEC, bool header=true)``
- ``tring int16ToStr(int16_t val, uint8_t type=DEC, bool header=true)``
- ``String uint16ToStr(uint16_t val, uint8_t type=DEC, bool header=true)``
- ``String int64ToStr(int64_t val, uint8_t type=DEC, bool header=true)``
- ``String uint64ToStr(uint64_t val, uint8_t type=DEC, bool header=true)``

第2引数``type``の値で以下のフォーマットのうちの1つの出力形式を取ります．
| 引数``type``の値 | フォーマット(正規表現で記載) |
|---|---|
| BIN |``[+\|-]0b[0\|1]+``|
| OCT |``[+\|-]0o[0-7]+`` |
| DEC |``[+\|-][0-9]+``   |
| HEX |``[+\|-]0x[0-9,a,A,b,B,c,C,d,D,e,E,f,F]+`` |

第3引数``header``は真偽値を取り，``+``，``-``や``0x``などを出力に含めるか否かを切り替えます．

## 数値関係機能
Arduino標準ライブラリでは，16進数，10進数を判定する機能はありますが，8進数を判定する機能はないのでそれを用意しています．
- ``bool isOctDigit(char a)``

## 真偽値関連機能

真偽値については以下のような機能を実装してます．

###  ``String boolToString(bool flag)``
真偽値を``true``や``false``という文字列に変換します．


### ``bool strToBool(String buff, bool bool flag=true)``
文字列``buff``が``true``もしくは``false``であるか否かを判定します．この際，``flag``で指定した値と一致しているか否かを基準にするため，以下のような動作になります．


| flagの値 | buffの値 |返り値|
|---|---|---|
|``true``|``True``|``true``|
| ``true`` | ``foo``| ``false``|
|``false`` | ``bar``| ``true``|
|``false``|``FaLse``|``false``|

つまり，``flag``は``true``と``false``のどちらを厳密に解釈するかを示すものになります．


### ``bool checkBoolStr(String buff)``
引数に不正な値(``true``，``false``いずれでもない文字列)を与えた場合に``strToBool()``の動作がわかりにくくなるため，不正な値が否かを判定する関数も実装しています．

この関数が``true``を返す場合のみ，引数``buff``は``true``や``false``を示す文字列になっています．


## 将来課題
全般的にメモリをたくさん使う．特に，``intxxToStr()``がメモリを多用する作りになっているので，それを削減する．

