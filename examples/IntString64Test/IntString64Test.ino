
#define DEBUG
#include <IntString.h>
#include <Int64String.h>

#define ARRAY_SIZE_INT64 60


String strInt64[]={
"9223372036854775806", "9223372036854775807", "9223372036854775808", "9223372036854775809", "000", 
"+9223372036854775806", "+9223372036854775807", "+9223372036854775808", "+9223372036854775809", "+000", 
"-9223372036854775806", "-9223372036854775807", "-9223372036854775808", "-9223372036854775809", "-000", 

"0x7FFFFFFFFFFFFFFE", "0x7FFFFFFFFFFFFFFF", "0x8000000000000000", "0x8000000000000001", "0x000", 
"+0x7FFFFFFFFFFFFFFE", "+0x7FFFFFFFFFFFFFFF", "+0x8000000000000000", "+0x8000000000000001", "+0x000", 
"-0x7FFFFFFFFFFFFFFE", "-0x7FFFFFFFFFFFFFFF", "-0x8000000000000000", "-0x8000000000000001", "-0x000", 

"0o777777777777777777776", "0o777777777777777777777", "0o1000000000000000000000", "0o1000000000000000000001", "0o000", 
"+0o777777777777777777776", "+0o777777777777777777777", "+0o1000000000000000000000", "+0o1000000000000000000001", "+0o000", 
"-0o777777777777777777776", "-0o777777777777777777777", "-0o1000000000000000000000", "-0o1000000000000000000001", "-0o000", 

"0b111111111111111111111111111111111111111111111111111111111111110", "0b111111111111111111111111111111111111111111111111111111111111111", "0b1000000000000000000000000000000000000000000000000000000000000000", "0b1000000000000000000000000000000000000000000000000000000000000001", "0b000", 
"+0b111111111111111111111111111111111111111111111111111111111111110", "+0b111111111111111111111111111111111111111111111111111111111111111", "+0b1000000000000000000000000000000000000000000000000000000000000000", "+0b1000000000000000000000000000000000000000000000000000000000000001", "+0b000", 
"-0b111111111111111111111111111111111111111111111111111111111111110", "-0b111111111111111111111111111111111111111111111111111111111111111", "-0b1000000000000000000000000000000000000000000000000000000000000000", "-0b1000000000000000000000000000000000000000000000000000000000000001", "-0b000"
};



void setup() {
  Serial.begin(9600);
  delay(5000);
  int64_t tmp=0;

  Serial.println("============= int64_t (min:-9223372036854775808, max:9223372036854775807) ==========");
  for (int i=0;i<ARRAY_SIZE_INT64;i++) {
    int64_t result=strToInt64(strInt64[i]);
    Serial.print("string = ");Serial.print(strInt64[i]);
    Serial.print(" , result = ");Serial.println(int64String(result));
    Serial.print("   DEC string = ");Serial.println(int64ToStr(result,DEC,true));
    Serial.print("   HEX string = ");Serial.println(int64ToStr(result,HEX,true));
    Serial.print("   OCT string = ");Serial.println(int64ToStr(result,OCT,true));
    Serial.print("   BIN string = ");Serial.println(int64ToStr(result,BIN,true));
  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
}
