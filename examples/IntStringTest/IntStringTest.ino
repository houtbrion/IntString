
#define DEBUG
#include <IntString.h>
#include <Int64String.h>

#define ARRAY_SIZE_INT8   24
#define ARRAY_SIZE_UINT8  24
#define ARRAY_SIZE_INT16  24
#define ARRAY_SIZE_UINT16 24
#define ARRAY_SIZE_INT32  24
#define ARRAY_SIZE_UINT32 24

#define ARRAY_SIZE_BOOL   10

String strInt8[]   = { "+0127", "+0128", "+127", "127",
                       "-0127", "-0128", "-129", "-128",
                       "+0x07f", "+0x080", "+0x7f", "0x7e",
                       "-0x07f", "-0x080", "-0x81", "-0x80",
                       "+0b01111111", "+0B010000000", "+0b1111111", "0b1111111",
                       "-0B01111111", "-0b010000000", "-0b10000001", "-0b10000000" };
String strUint8[]  = { "+0255", "+0256", "+255", "255",
                       "-0", "-1", "1", "0",
                       "+0x0ff", "+0x0100", "+0xff", "0xff",
                       "-0x000", "-0x01", "-0x0", "0x0",
                       "+0B011111111", "+0b0100000000", "+0b11111111", "0b11111111",
                       "-0b000", "-0b01", "-0b0", "0b0" };
String strInt16[]  = { "+032767", "+032768", "+32767", "32767",
                       "-032767", "-032768", "-032769", "-32768",
                       "+0x07fff", "+0x08000", "+0x7fff", "0x7ffe",
                       "-0x07fff", "-0x08000", "-0x8001", "-0x8000",
                       "+0b0111111111111111", "+0B01000000000000000", "+0b111111111111111", "0b111111111111111",
                       "-0B0111111111111111", "-0b01000000000000000", "-0b1000000000000001", "-0b1000000000000000" };
String strUint16[] = { "+065535", "+065536", "+65535", "65535",
                       "-0", "-1", "1", "0",
                       "+0x0ffff", "+0x010000", "+0xffff", "0xffff",
                       "-0x000", "-0x01", "-0x0", "0x0",
                       "+0B01111111111111111", "+0b010000000000000000", "+0b1111111111111111", "0b1111111111111111",
                       "-0b000", "-0b01", "-0b0", "0b0" };
String strInt32[]  = { "+02147483647", "+02147483648", "+2147483647", "2147483647",
                       "-02147483647", "-02147483648", "-02147483649", "-2147483648",
                       "+0x07FFFFFFF", "+0x080000000", "+0x7FFFFFFF", "0x7FFFFFFe",
                       "-0x07FFFFFFF", "-0x080000000", "-0x80000001", "-0x80000000",
                       "+0b01111111111111111111111111111111", "+0B010000000000000000000000000000000", "+0b1111111111111111111111111111111", "0b1111111111111111111111111111111",
                       "-0B01111111111111111111111111111111", "-0b010000000000000000000000000000000", "-0b10000000000000000000000000000001", "-0b10000000000000000000000000000000" };
String strUint32[] = { "+04294967295", "+04294967296", "+4294967295", "4294967295",
                       "-04294967295", "-04294967296", "-04294967297", "-4294967296",
                       "+0x0FFFFFFFF", "+0x0100000000", "+0xFFFFFFFF", "0xFFFFFFFE",
                       "-0x0FFFFFFFF", "-0x0100000000", "-0x100000001", "-0x100000000",
                       "+0b011111111111111111111111111111111", "+0B0100000000000000000000000000000000", "+0b11111111111111111111111111111111", "0b11111111111111111111111111111111",
                       "-0B011111111111111111111111111111111", "-0b0100000000000000000000000000000000", "-0b100000000000000000000000000000001", "-0b100000000000000000000000000000000" };
String strBool[]   = { "True", "true", "truE", "TRUE", "false", "False", "faLse", "FALSE", "foo", "bar" };


void setup() {
  Serial.begin(9600);
  delay(5000);
  uint32_t tmp=0;

  Serial.println("============= int8_t (min:-128, max:127) ==========");
  for (int i=0;i<ARRAY_SIZE_INT8;i++) {
    int8_t result=strToInt8(strInt8[i]);
    Serial.print("string = ");Serial.print(strInt8[i]);
    Serial.print(" , result = ");Serial.println(String(result));
    Serial.print("   DEC string = ");Serial.println(int8ToStr(result,DEC,true));
    Serial.print("   HEX string = ");Serial.println(int8ToStr(result,HEX,true));
    Serial.print("   OCT string = ");Serial.println(int8ToStr(result,OCT,true));
    Serial.print("   BIN string = ");Serial.println(int8ToStr(result,BIN,true));
  }
  tmp=strToInt8("0");
  Serial.print("string = ");Serial.print("0");
  Serial.print(" , tmp = ");Serial.println(String(tmp));
  Serial.print("   DEC tmp = ");Serial.println(int8ToStr(tmp,DEC,true));
  Serial.print("   HEX tmp = ");Serial.println(int8ToStr(tmp,HEX,true));
  Serial.print("   OCT tmp = ");Serial.println(int8ToStr(tmp,OCT,true));
  Serial.print("   BIN tmp = ");Serial.println(int8ToStr(tmp,BIN,true));
  Serial.println("");
  Serial.println("============= uint8_t (min:0, max:255) ==========");
  for (int i=0;i<ARRAY_SIZE_UINT8;i++) {
    uint8_t result=strToUint8(strUint8[i]);
    Serial.print("string = ");Serial.print(strUint8[i]);
    Serial.print(" , result = ");Serial.println(String(result));
    Serial.print("   DEC string = ");Serial.println(uint8ToStr(result,DEC,true));
    Serial.print("   HEX string = ");Serial.println(uint8ToStr(result,HEX,true));
    Serial.print("   OCT string = ");Serial.println(uint8ToStr(result,OCT,true));
    Serial.print("   BIN string = ");Serial.println(uint8ToStr(result,BIN,true));
  }
  tmp=strToUint8("0");
  Serial.print("string = ");Serial.print("0");
  Serial.print(" , tmp = ");Serial.println(String(tmp));
  Serial.print("   DEC tmp = ");Serial.println(uint8ToStr(tmp,DEC,true));
  Serial.print("   HEX tmp = ");Serial.println(uint8ToStr(tmp,HEX,true));
  Serial.print("   OCT tmp = ");Serial.println(uint8ToStr(tmp,OCT,true));
  Serial.print("   BIN tmp = ");Serial.println(uint8ToStr(tmp,BIN,true));
  Serial.println("");
  Serial.println("============= int16_t (min:-32768, max:32767) ==========");
  for (int i=0;i<ARRAY_SIZE_INT16;i++) {
    int16_t result=strToInt16(strInt16[i]);
    Serial.print("string = ");Serial.print(strInt16[i]);
    Serial.print(" , result = ");Serial.println(String(result));
    Serial.print("   DEC string = ");Serial.println(int16ToStr(result,DEC,true));
    Serial.print("   HEX string = ");Serial.println(int16ToStr(result,HEX,true));
    Serial.print("   OCT string = ");Serial.println(int16ToStr(result,OCT,true));
    Serial.print("   BIN string = ");Serial.println(int16ToStr(result,BIN,true));
  }
  tmp=strToInt16("0");
  Serial.print("string = ");Serial.print("0");
  Serial.print(" , tmp = ");Serial.println(String(tmp));
  Serial.print("   DEC tmp = ");Serial.println(int16ToStr(tmp,DEC,true));
  Serial.print("   HEX tmp = ");Serial.println(int16ToStr(tmp,HEX,true));
  Serial.print("   OCT tmp = ");Serial.println(int16ToStr(tmp,OCT,true));
  Serial.print("   BIN tmp = ");Serial.println(int16ToStr(tmp,BIN,true));
  Serial.println("");
  Serial.println("============= uint16_t (min:0, max:65535) ==========");
  for (int i=0;i<ARRAY_SIZE_UINT16;i++) {
    uint16_t result=strToUint16(strUint16[i]);
    Serial.print("string = ");Serial.print(strUint16[i]);
    Serial.print(" , result = ");Serial.println(String(result));
    Serial.print("   DEC string = ");Serial.println(uint16ToStr(result,DEC,true));
    Serial.print("   HEX string = ");Serial.println(uint16ToStr(result,HEX,true));
    Serial.print("   OCT string = ");Serial.println(uint16ToStr(result,OCT,true));
    Serial.print("   BIN string = ");Serial.println(uint16ToStr(result,BIN,true));
  }
  tmp=strToUint16("0");
  Serial.print("string = ");Serial.print("0");
  Serial.print(" , tmp = ");Serial.println(String(tmp));
  Serial.print("   DEC tmp = ");Serial.println(uint16ToStr(tmp,DEC,true));
  Serial.print("   HEX tmp = ");Serial.println(uint16ToStr(tmp,HEX,true));
  Serial.print("   OCT tmp = ");Serial.println(uint16ToStr(tmp,OCT,true));
  Serial.print("   BIN tmp = ");Serial.println(uint16ToStr(tmp,BIN,true));
  Serial.println("");
  Serial.println("============= int32_t (min:-2147483648, max:2147483647) ==========");
  for (int i=0;i<ARRAY_SIZE_INT32;i++) {
    int32_t result=strToInt32(strInt32[i]);
    Serial.print("string = ");Serial.print(strInt32[i]);
    Serial.print(" , result = ");Serial.println(String(result));
    Serial.print("   DEC string = ");Serial.println(int32ToStr(result,DEC,true));
    Serial.print("   HEX string = ");Serial.println(int32ToStr(result,HEX,true));
    Serial.print("   OCT string = ");Serial.println(int32ToStr(result,OCT,true));
    Serial.print("   BIN string = ");Serial.println(int32ToStr(result,BIN,true));
  }
  tmp=strToInt32("0");
  Serial.print("string = ");Serial.print("0");
  Serial.print(" , tmp = ");Serial.println(String(tmp));
  Serial.print("   DEC tmp = ");Serial.println(int32ToStr(tmp,DEC,true));
  Serial.print("   HEX tmp = ");Serial.println(int32ToStr(tmp,HEX,true));
  Serial.print("   OCT tmp = ");Serial.println(int32ToStr(tmp,OCT,true));
  Serial.print("   BIN tmp = ");Serial.println(int32ToStr(tmp,BIN,true));
  Serial.println("");
  Serial.println("============= uint32_t (min:0, max:4294967295) ==========");
  for (int i=0;i<ARRAY_SIZE_UINT32;i++) {
    uint32_t result=strToUint32(strUint32[i]);
    Serial.print("string = ");Serial.print(strUint32[i]);
    Serial.print(" , result = ");Serial.println(String(result));
    Serial.print("   DEC string = ");Serial.println(uint32ToStr(result,DEC,true));
    Serial.print("   HEX string = ");Serial.println(uint32ToStr(result,HEX,true));
    Serial.print("   OCT string = ");Serial.println(uint32ToStr(result,OCT,true));
    Serial.print("   BIN string = ");Serial.println(uint32ToStr(result,BIN,true));
  }
  tmp=strToUint32("0");
  Serial.print("string = ");Serial.print("0");
  Serial.print(" , tmp = ");Serial.println(String(tmp));
  Serial.print("   DEC tmp = ");Serial.println(uint32ToStr(tmp,DEC,true));
  Serial.print("   HEX tmp = ");Serial.println(uint32ToStr(tmp,HEX,true));
  Serial.print("   OCT tmp = ");Serial.println(uint32ToStr(tmp,OCT,true));
  Serial.print("   BIN tmp = ");Serial.println(uint32ToStr(tmp,BIN,true));
  Serial.println("");
  Serial.println("============= bool (true, false) ==========");
  for (int i=0;i<ARRAY_SIZE_BOOL;i++) {
    bool result0=strToBool(strBool[i], true);
    bool result1=strToBool(strBool[i], false);
    bool flag=checkBoolStr(strBool[i]);
    Serial.print("string = ");Serial.print(strBool[i]);
    Serial.print(" , result0 = ");Serial.print(boolToString(result0));
    Serial.print(" , result1 = ");Serial.print(boolToString(result1));
    Serial.print(" , check = ");Serial.println(boolToString(flag));
  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
}
