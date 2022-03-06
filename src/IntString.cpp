#include "IntString.h"

String boolToString(bool flag){
  if (flag) {
    return String("true");
  } else {
    return String("false");
  }
}

bool strToBool(String buff, bool flag){
  if (flag) {
    if (buff.equalsIgnoreCase("true")) {
      return true;
    } else {
      return false;
    }
  } else {
    if (buff.equalsIgnoreCase("false")) {
      return false;
    } else {
      return true;
    }
  }
}

bool checkBoolStr(String buff) {
  if (strToBool(buff, true)) return true;
  if (!strToBool(buff, false)) return true;
  return false;
}

int64_t calcDecVal(char *str,int length) {
  int64_t rst=0;
  for (int i=0;i<length;i++) {
    rst=rst*10;
    switch(str[i]) {
      case '1':rst=rst+1;break;
      case '2':rst=rst+2;break;
      case '3':rst=rst+3;break;
      case '4':rst=rst+4;break;
      case '5':rst=rst+5;break;
      case '6':rst=rst+6;break;
      case '7':rst=rst+7;break;
      case '8':rst=rst+8;break;
      case '9':rst=rst+9;break;
    }
  }
  return rst;
}

int64_t calcHexVal(char *str,int length) {
  int64_t rst=0;
  for (int i=0;i<length;i++) {
    rst=rst*16;
    switch(str[i]) {
      case '1':rst=rst+1;break;
      case '2':rst=rst+2;break;
      case '3':rst=rst+3;break;
      case '4':rst=rst+4;break;
      case '5':rst=rst+5;break;
      case '6':rst=rst+6;break;
      case '7':rst=rst+7;break;
      case '8':rst=rst+8;break;
      case '9':rst=rst+9;break;
      case 'a':rst=rst+10;break;
      case 'A':rst=rst+10;break;
      case 'b':rst=rst+11;break;
      case 'B':rst=rst+11;break;
      case 'c':rst=rst+12;break;
      case 'C':rst=rst+12;break;
      case 'd':rst=rst+13;break;
      case 'D':rst=rst+13;break;
      case 'e':rst=rst+14;break;
      case 'E':rst=rst+14;break;
      case 'f':rst=rst+15;break;
      case 'F':rst=rst+15;break;
    }
  }
  return rst;
}

int64_t calcBinVal(char *str,int length) {
  int64_t rst=0;
  for (int i=0;i<length;i++) {
    rst=rst*2;
    if (str[i]=='1') rst=rst+1;
  }
  return rst;
}

int64_t calcOctVal(char *str,int length) {
  int64_t rst=0;
  for (int i=0;i<length;i++) {
    rst=rst*8;
    switch(str[i]) {
      case '1':rst=rst+1;break;
      case '2':rst=rst+2;break;
      case '3':rst=rst+3;break;
      case '4':rst=rst+4;break;
      case '5':rst=rst+5;break;
      case '6':rst=rst+6;break;
      case '7':rst=rst+7;break;
    }
  }
  return rst;
}

int ShortStringToInt64(String valString, int64_t *result) {
  int startPos=0;
  bool minus=false;
  int len=valString.length();
  //char *charArray=valString.c_str();
  const char *work=valString.c_str();
  char *charArray=(char*)work;

  if (charArray[0]=='-') {
    startPos=1;
    minus=true;
  }
  if (charArray[0]=='+') {
    startPos=1;
  }
  int kind=CONV_DATA_DEC; // CONV_DATA_DEC: dec, CONV_DATA_HEX: hex, CONV_DATA_BIN: bin, CONV_DATA_OCT: oct
  if (startPos != (len-1)) {
    if ((charArray[startPos]=='0') && (charArray[startPos+1]=='x')) {kind=CONV_DATA_HEX;startPos+=2;}
    if ((charArray[startPos]=='0') && (charArray[startPos+1]=='X')) {kind=CONV_DATA_HEX;startPos+=2;}
    if ((charArray[startPos]=='0') && (charArray[startPos+1]=='b')) {kind=CONV_DATA_BIN;startPos+=2;}
    if ((charArray[startPos]=='0') && (charArray[startPos+1]=='B')) {kind=CONV_DATA_BIN;startPos+=2;}
    if ((charArray[startPos]=='0') && (charArray[startPos+1]=='o')) {kind=CONV_DATA_OCT;startPos+=2;}
    if ((charArray[startPos]=='0') && (charArray[startPos+1]=='O')) {kind=CONV_DATA_OCT;startPos+=2;}
  }
  bool header=true;
  bool error=false;
  for (int i=startPos; i< len; i++) {
    if ((!isHexadecimalDigit(charArray[i])) && (kind==1)) error=true;
    if ((!isDigit(charArray[i])) && (kind==0)) error=true;
    if ((charArray[i]!='0') && (charArray[i]!='1') && (kind==2)) error=true;
    if ((charArray[i]!='0') && (header)) header=false;
    if ((charArray[i]=='0') && (header)) startPos++;
  }
  if (startPos==len) {
    (*result) = 0;
    return CONV_SUCCESS;
  }
  uint64_t tmp=0;
  switch(kind) {
    case CONV_DATA_DEC:{
      tmp=calcDecVal(charArray+startPos, len-startPos);
      if (minus) tmp=tmp*(-1);
    };break;
    case CONV_DATA_HEX:{
      tmp=calcHexVal(charArray+startPos, len-startPos);
      if (minus) tmp=tmp*(-1);
    };break;
    case CONV_DATA_BIN:{
      tmp=calcBinVal(charArray+startPos, len-startPos);
      if (minus) tmp=tmp*(-1);
    };break;
    case CONV_DATA_OCT:{
      tmp=calcOctVal(charArray+startPos, len-startPos);
      if (minus) tmp=tmp*(-1);
    };break;
  }
  (*result)=tmp;
  return CONV_SUCCESS;
}

int8_t strToInt8(String str) {
  int64_t val;
  int rst = ShortStringToInt64(str, &val);
  if (rst!=CONV_SUCCESS) return 0;
  if (val > UPPER_LIMIT_INT8) return UPPER_LIMIT_INT8;
  if (val < LOWER_LIMIT_INT8) return LOWER_LIMIT_INT8;
  return (int8_t) val;
}

uint8_t strToUint8(String str) {
  int64_t val;
  int rst = ShortStringToInt64(str, &val);
  if (rst!=CONV_SUCCESS) return 0;
  if (val > UPPER_LIMIT_UINT8) return UPPER_LIMIT_UINT8;
  if (val < LOWER_LIMIT_UINT8) return LOWER_LIMIT_UINT8;
  return (uint8_t) val;
}

int16_t strToInt16(String str) {
  int64_t val;
  int rst = ShortStringToInt64(str, &val);
  if (rst!=CONV_SUCCESS) return 0;
  if (val > UPPER_LIMIT_INT16) return UPPER_LIMIT_INT16;
  if (val < LOWER_LIMIT_INT16) return LOWER_LIMIT_INT16;
  return (int16_t) val;
}

uint16_t strToUint16(String str) {
  int64_t val;
  int rst = ShortStringToInt64(str, &val);
  if (rst!=CONV_SUCCESS) return 0;
  if (val > UPPER_LIMIT_UINT16) return UPPER_LIMIT_UINT16;
  if (val < LOWER_LIMIT_UINT16) return LOWER_LIMIT_UINT16;
  return (uint16_t) val;
}

int32_t strToInt32(String str) {
  int64_t val;
  int rst = ShortStringToInt64(str, &val);
  if (rst!=CONV_SUCCESS) return 0;
  if (val > UPPER_LIMIT_INT32) return UPPER_LIMIT_INT32;
  if (val < LOWER_LIMIT_INT32) return LOWER_LIMIT_INT32;
  return (int32_t) val;
}

uint32_t strToUint32(String str) {
  int64_t val;
  int rst = ShortStringToInt64(str, &val);
  if (rst!=CONV_SUCCESS) return 0;
  if (val > UPPER_LIMIT_UINT32) return UPPER_LIMIT_UINT32;
  if (val < LOWER_LIMIT_UINT32) return LOWER_LIMIT_UINT32;
  return (uint32_t) val;
}
