
#define DEBUG
#include <IntString.h>

#define ARRAY_SIZE_FLOAT 16

String strFloat[ARRAY_SIZE_FLOAT]={
"1234567890.0987654321",
"12345678900987654321",
"0.12345678900987654321",

"12345678900987654321.",
"123456.78900987.654321",
"123456.7890.0987.654321",

".12345678900987654321",

"0001234567890.0987654321",
"00012345678900987654321",
"0000.12345678900987654321",

"+0001234567890.0987654321",
"+00012345678900987654321",
"+0000.12345678900987654321",

"-0001234567890.0987654321",
"-00012345678900987654321",
"-0000.12345678900987654321"

};




void setup() {
  Serial.begin(9600);
  delay(5000);

  Serial.println("============= float (min:-2147483648, max:2147483647) ==========");
  for (int i=0;i<ARRAY_SIZE_FLOAT;i++) {
    Serial.print("data = ");Serial.print(strFloat[i]);
    float result=floatToStr(strFloat[i],DECIMAL_POINT_PERIOD);
    Serial.print(" , result = ");Serial.println(String(result));
    Serial.println("");
  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
}
