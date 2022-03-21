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

bool isOctDigit(char a) {
  switch(a) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
      return true;
  }
  return false;
}

int ShortStringToInt64(String valString, int64_t *result) {
  int startPos=0;
  bool minus=false;
  int len=valString.length();
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
    if ((!isHexadecimalDigit(charArray[i])) && (kind==CONV_DATA_HEX)) error=true;
    if ((!isDigit(charArray[i])) && (kind==CONV_DATA_DEC)) error=true;
    if ((charArray[i]!='0') && (charArray[i]!='1') && (kind==CONV_DATA_BIN)) error=true;
    if ((!isOctDigit(charArray[i])) && (kind==CONV_DATA_OCT)) error=true;
    if ((charArray[i]!='0') && (header)) header=false;
    if ((charArray[i]=='0') && (header)) startPos++;
  }
  if (error) return CONV_ERROR_FORMAT;
  if (startPos==len) {
    (*result) = 0;
    return CONV_SUCCESS;
  }
  int64_t tmp=0;
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

String int32ToStr(int32_t val, uint8_t type, bool header) {
  if (LOWER_LIMIT_INT32==val) {
    switch(type) {
      case DEC:return "-2147483648";
      case HEX:return "-0x80000000";
      case OCT:return "-0o20000000000";
      case BIN:return "-0b10000000000000000000000000000000";
    }
  }
  bool minus=false;
  int32_t tmp;
  String rst;
  if (val <0) {
    if (header) {
      rst="-";
    } else {
      rst="";
    }
    tmp=(-1)*val;
  } else {
    rst="";
    tmp=val;
  }
  uint8_t div;
  switch(type){
    case DEC:div=10;break;
    case HEX:{
      div=16;
      if (header) rst=rst+"0x";
      break;
    }
    case BIN:{
      div=2;
      if (header) rst=rst+"0b";
      break;
    }
    case OCT:{
      div=8;
      if (header) rst=rst+"0o";
      break;
    }
    default: return "";
  }
  uint8_t mod=0;
  String work="";
  while (tmp >= div) {
    mod=tmp%div;
    switch(mod){
      case  0:work="0"+work;break;
      case  1:work="1"+work;break;
      case  2:work="2"+work;break;
      case  3:work="3"+work;break;
      case  4:work="4"+work;break;
      case  5:work="5"+work;break;
      case  6:work="6"+work;break;
      case  7:work="7"+work;break;
      case  8:work="8"+work;break;
      case  9:work="9"+work;break;
      case 10:work="A"+work;break;
      case 11:work="B"+work;break;
      case 12:work="C"+work;break;
      case 13:work="D"+work;break;
      case 14:work="E"+work;break;
      case 15:work="F"+work;break;
    }
    tmp=(tmp-mod)/div;
  };
  switch(tmp){
    case  0:work="0"+work;break;
    case  1:work="1"+work;break;
    case  2:work="2"+work;break;
    case  3:work="3"+work;break;
    case  4:work="4"+work;break;
    case  5:work="5"+work;break;
    case  6:work="6"+work;break;
    case  7:work="7"+work;break;
    case  8:work="8"+work;break;
    case  9:work="9"+work;break;
    case 10:work="A"+work;break;
    case 11:work="B"+work;break;
    case 12:work="C"+work;break;
    case 13:work="D"+work;break;
    case 14:work="E"+work;break;
    case 15:work="F"+work;break;
  }
  rst=rst+work;
  return rst;
}

String uint32ToStr(uint32_t val, uint8_t type, bool header) {
  return uint64ToStr( val,  type,  header);
}

String int8ToStr(int8_t val, uint8_t type, bool header) {
  //return int32ToStr( val,  type,  header);
  return int64ToStr( val,  type,  header);
}

String uint8ToStr(uint8_t val, uint8_t type, bool header) {
  //return uint32ToStr( val,  type,  header);
  return uint64ToStr( val,  type,  header);
}

String int16ToStr(int16_t val, uint8_t type, bool header) {
  //return int32ToStr( val,  type,  header);
  return int64ToStr( val,  type,  header);
}

String uint16ToStr(uint16_t val, uint8_t type, bool header) {
  //return uint32ToStr( val,  type,  header);
  return uint64ToStr( val,  type,  header);
}

String uint64ToStr(uint64_t val, uint8_t type, bool header) {
  uint64_t tmp=val;
  String rst="";
  uint8_t div;
  switch(type){
    case DEC:div=10;break;
    case HEX:{
      div=16;
      if (header) rst=rst+"0x";
      break;
    }
    case BIN:{
      div=2;
      if (header) rst=rst+"0b";
      break;
    }
    case OCT:{
      div=8;
      if (header) rst=rst+"0o";
      break;
    }
    default: return "";
  }
  uint8_t mod=0;
  String work="";
  while (tmp >= div) {
    mod=tmp%div;
    switch(mod){
      case  0:work="0"+work;break;
      case  1:work="1"+work;break;
      case  2:work="2"+work;break;
      case  3:work="3"+work;break;
      case  4:work="4"+work;break;
      case  5:work="5"+work;break;
      case  6:work="6"+work;break;
      case  7:work="7"+work;break;
      case  8:work="8"+work;break;
      case  9:work="9"+work;break;
      case 10:work="A"+work;break;
      case 11:work="B"+work;break;
      case 12:work="C"+work;break;
      case 13:work="D"+work;break;
      case 14:work="E"+work;break;
      case 15:work="F"+work;break;
    }
    tmp=(tmp-mod)/div;
  };
  switch(tmp){
    case  0:work="0"+work;break;
    case  1:work="1"+work;break;
    case  2:work="2"+work;break;
    case  3:work="3"+work;break;
    case  4:work="4"+work;break;
    case  5:work="5"+work;break;
    case  6:work="6"+work;break;
    case  7:work="7"+work;break;
    case  8:work="8"+work;break;
    case  9:work="9"+work;break;
    case 10:work="A"+work;break;
    case 11:work="B"+work;break;
    case 12:work="C"+work;break;
    case 13:work="D"+work;break;
    case 14:work="E"+work;break;
    case 15:work="F"+work;break;
  }
  rst=rst+work;
  return rst;
}

uint64_t calcDec64Val(char *target,int len) {
  uint64_t tmp=0;
  for (int i=0;i < len ; i++) {
    if (tmp > UPPER_LIMIT_UINT64_DIV_DEC) return UPPER_LIMIT_UINT64;
    tmp=tmp*10;
    switch(target[i]){
      case '0': {
        tmp=tmp+0;
        break;
      }
      case '1': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_1) return UPPER_LIMIT_UINT64;
        tmp=tmp+1;
        break;
      }
      case '2': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_2) return UPPER_LIMIT_UINT64;
        tmp=tmp+2;
        break;
      }
      case '3': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_3) return UPPER_LIMIT_UINT64;
        tmp=tmp+3;
        break;
      }
      case '4': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_4) return UPPER_LIMIT_UINT64;
        tmp=tmp+4;
        break;
      }
      case '5': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_5) return UPPER_LIMIT_UINT64;
        tmp=tmp+5;
        break;
      }
      case '6': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_6) return UPPER_LIMIT_UINT64;
        tmp=tmp+6;
        break;
      }
      case '7': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_7) return UPPER_LIMIT_UINT64;
        tmp=tmp+7;
        break;
      }
      case '8': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_8) return UPPER_LIMIT_UINT64;
        tmp=tmp+8;
        break;
      }
      case '9': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_9) return UPPER_LIMIT_UINT64;
        tmp=tmp+9;
        break;
      }
    }
  }
  return tmp;
}

uint64_t calcHex64Val(char *target,int len) {
  uint64_t tmp=0;
  for (int i=0;i < len ; i++) {
    if (tmp > UPPER_LIMIT_UINT64_DIV_HEX) return UPPER_LIMIT_UINT64;
    tmp=tmp*16;
    switch(target[i]){
      case '0': {
        tmp=tmp+0;
        break;
      }
      case '1': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_1) return UPPER_LIMIT_UINT64;
        tmp=tmp+1;
        break;
      }
      case '2': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_2) return UPPER_LIMIT_UINT64;
        tmp=tmp+2;
        break;
      }
      case '3': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_3) return UPPER_LIMIT_UINT64;
        tmp=tmp+3;
        break;
      }
      case '4': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_4) return UPPER_LIMIT_UINT64;
        tmp=tmp+4;
        break;
      }
      case '5': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_5) return UPPER_LIMIT_UINT64;
        tmp=tmp+5;
        break;
      }
      case '6': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_6) return UPPER_LIMIT_UINT64;
        tmp=tmp+6;
        break;
      }
      case '7': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_7) return UPPER_LIMIT_UINT64;
        tmp=tmp+7;
        break;
      }
      case '8': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_8) return UPPER_LIMIT_UINT64;
        tmp=tmp+8;
        break;
      }
      case '9': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_9) return UPPER_LIMIT_UINT64;
        tmp=tmp+9;
        break;
      }
      case 'a': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_A) return UPPER_LIMIT_UINT64;
        tmp=tmp+10;
        break;
      }
      case 'A': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_A) return UPPER_LIMIT_UINT64;
        tmp=tmp+10;
        break;
      }
      case 'b': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_B) return UPPER_LIMIT_UINT64;
        tmp=tmp+11;
        break;
      }
      case 'B': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_B) return UPPER_LIMIT_UINT64;
        tmp=tmp+11;
        break;
      }
      case 'c': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_C) return UPPER_LIMIT_UINT64;
        tmp=tmp+12;
        break;
      }
      case 'C': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_C) return UPPER_LIMIT_UINT64;
        tmp=tmp+12;
        break;
      }
      case 'd': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_D) return UPPER_LIMIT_UINT64;
        tmp=tmp+13;
        break;
      }
      case 'D': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_D) return UPPER_LIMIT_UINT64;
        tmp=tmp+13;
        break;
      }
      case 'e': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_E) return UPPER_LIMIT_UINT64;
        tmp=tmp+14;
        break;
      }
      case 'E': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_E) return UPPER_LIMIT_UINT64;
        tmp=tmp+14;
        break;
      }
      case 'f': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_F) return UPPER_LIMIT_UINT64;
        tmp=tmp+15;
        break;
      }
      case 'F': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_F) return UPPER_LIMIT_UINT64;
        tmp=tmp+15;
        break;
      }
    }
  }
  return tmp;
}

uint64_t calcOct64Val(char *target,int len) {
  uint64_t tmp=0;
  for (int i=0;i < len ; i++) {
    if (tmp > UPPER_LIMIT_UINT64_DIV_OCT) return UPPER_LIMIT_UINT64;
    tmp=tmp*8;
    switch(target[i]){
      case '0': {
        tmp=tmp+0;
        break;
      }
      case '1': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_1) return UPPER_LIMIT_UINT64;
        tmp=tmp+1;
        break;
      }
      case '2': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_2) return UPPER_LIMIT_UINT64;
        tmp=tmp+2;
        break;
      }
      case '3': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_3) return UPPER_LIMIT_UINT64;
        tmp=tmp+3;
        break;
      }
      case '4': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_4) return UPPER_LIMIT_UINT64;
        tmp=tmp+4;
        break;
      }
      case '5': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_5) return UPPER_LIMIT_UINT64;
        tmp=tmp+5;
        break;
      }
      case '6': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_6) return UPPER_LIMIT_UINT64;
        tmp=tmp+6;
        break;
      }
      case '7': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_7) return UPPER_LIMIT_UINT64;
        tmp=tmp+7;
        break;
      }
    }
  }
  return tmp;
}

uint64_t calcBin64Val(char *target,int len) {
  uint64_t tmp=0;
  for (int i=0;i < len ; i++) {
    if (tmp > UPPER_LIMIT_UINT64_DIV_BIN) return UPPER_LIMIT_UINT64;
    tmp=tmp*2;
    switch(target[i]){
      case '0': {
        tmp=tmp+0;
        break;
      }
      case '1': {
        if (tmp > UPPER_LIMIT_UINT64_MINUS_1) return UPPER_LIMIT_UINT64;
        tmp=tmp+1;
        break;
      }
    }
  }
  return tmp;
}

uint64_t strToUint64(String valString){
  int startPos=0;
  bool minus=false;
  int len=valString.length();
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
    if ((!isHexadecimalDigit(charArray[i])) && (kind==CONV_DATA_HEX)) error=true;
    if ((!isDigit(charArray[i])) && (kind==CONV_DATA_DEC)) error=true;
    if ((charArray[i]!='0') && (charArray[i]!='1') && (kind==CONV_DATA_BIN)) error=true;
    if ((!isOctDigit(charArray[i])) && (kind==CONV_DATA_OCT)) error=true;
    if ((charArray[i]!='0') && (header)) header=false;
    if ((charArray[i]=='0') && (header)) startPos++;
  }
  if ((error) || (startPos==len)) return 0;

  uint64_t result=0;
  switch(kind) {
    case CONV_DATA_DEC:{
      result=calcDec64Val(charArray+startPos, len-startPos);
      if (minus) return 0;
    };break;
    case CONV_DATA_HEX:{
      result=calcHex64Val(charArray+startPos, len-startPos);
      if (minus) return 0;
    };break;
    case CONV_DATA_BIN:{
      result=calcBin64Val(charArray+startPos, len-startPos);
      if (minus) return 0;
    };break;
    case CONV_DATA_OCT:{
      result=calcOct64Val(charArray+startPos, len-startPos);
      if (minus) return 0;
    };break;
  }
  return result;
}


int64_t strToInt64(String valString){
  int startPos=0;
  bool minus=false;
  int len=valString.length();
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
    if ((!isHexadecimalDigit(charArray[i])) && (kind==CONV_DATA_HEX)) error=true;
    if ((!isDigit(charArray[i])) && (kind==CONV_DATA_DEC)) error=true;
    if ((charArray[i]!='0') && (charArray[i]!='1') && (kind==CONV_DATA_BIN)) error=true;
    if ((!isOctDigit(charArray[i])) && (kind==CONV_DATA_OCT)) error=true;
    if ((charArray[i]!='0') && (header)) header=false;
    if ((charArray[i]=='0') && (header)) startPos++;
  }
  if ((error) || (startPos==len)) return 0;
  int64_t result=0;
  uint64_t conv=0;
  switch(kind) {
    case CONV_DATA_DEC:{
      conv=calcDec64Val(charArray+startPos, len-startPos);
      if (minus) {
        if (conv > CONV_THRESH_INT64) conv = CONV_THRESH_INT64;
        result=(int64_t) (conv)*(-1);
      } else {
        if (conv > UPPER_LIMIT_INT64) conv = UPPER_LIMIT_INT64;
        result=(int64_t) conv;
      }
    };break;
    case CONV_DATA_HEX:{
      conv=calcHex64Val(charArray+startPos, len-startPos);
      if (minus) {
        if (conv > CONV_THRESH_INT64) conv = CONV_THRESH_INT64;
        result=(int64_t) (conv)*(-1);
      } else {
        if (conv > UPPER_LIMIT_INT64) conv = UPPER_LIMIT_INT64;
        result=(int64_t) conv;
      }
    };break;
    case CONV_DATA_BIN:{
      conv=calcBin64Val(charArray+startPos, len-startPos);
      if (minus) {
        if (conv > CONV_THRESH_INT64) conv = CONV_THRESH_INT64;
        result=(int64_t) (conv)*(-1);
      } else {
        if (conv > UPPER_LIMIT_INT64) conv = UPPER_LIMIT_INT64;
        result=(int64_t) conv;
      }
    };break;
    case CONV_DATA_OCT:{
      conv=calcOct64Val(charArray+startPos, len-startPos);
      if (minus) {
        if (conv > CONV_THRESH_INT64) conv = CONV_THRESH_INT64;
        result=(int64_t) (conv)*(-1);
      } else {
        if (conv > UPPER_LIMIT_INT64) conv = UPPER_LIMIT_INT64;
        result=(int64_t) conv;
      }
    };break;
  }
  return result;
}

String int64ToStr(int64_t val, uint8_t type, bool header) {
  if (LOWER_LIMIT_INT64==val) {
    switch(type) {
      case DEC:return "-9223372036854775808";
      case HEX:return "-0x8000000000000000";
      case OCT:return "-0o1000000000000000000000";
      case BIN:return "-0b1000000000000000000000000000000000000000000000000000000000000000";
    }
  }
  bool minus=false;
  int64_t tmp;
  String rst;
  if (val <0) {
    if (header) {
      rst="-";
    } else {
      rst="";
    }
    tmp=(-1)*val;
  } else {
    rst="";
    tmp=val;
  }
  uint8_t div;
  switch(type){
    case DEC:div=10;break;
    case HEX:{
      div=16;
      if (header) rst=rst+"0x";
      break;
    }
    case BIN:{
      div=2;
      if (header) rst=rst+"0b";
      break;
    }
    case OCT:{
      div=8;
      if (header) rst=rst+"0o";
      break;
    }
    default: return "";
  }
  uint8_t mod=0;
  String work="";
  while (tmp >= div) {
    mod=tmp%div;
    switch(mod){
      case  0:work="0"+work;break;
      case  1:work="1"+work;break;
      case  2:work="2"+work;break;
      case  3:work="3"+work;break;
      case  4:work="4"+work;break;
      case  5:work="5"+work;break;
      case  6:work="6"+work;break;
      case  7:work="7"+work;break;
      case  8:work="8"+work;break;
      case  9:work="9"+work;break;
      case 10:work="A"+work;break;
      case 11:work="B"+work;break;
      case 12:work="C"+work;break;
      case 13:work="D"+work;break;
      case 14:work="E"+work;break;
      case 15:work="F"+work;break;
    }
    tmp=(tmp-mod)/div;
  };
  switch(tmp){
    case  0:work="0"+work;break;
    case  1:work="1"+work;break;
    case  2:work="2"+work;break;
    case  3:work="3"+work;break;
    case  4:work="4"+work;break;
    case  5:work="5"+work;break;
    case  6:work="6"+work;break;
    case  7:work="7"+work;break;
    case  8:work="8"+work;break;
    case  9:work="9"+work;break;
    case 10:work="A"+work;break;
    case 11:work="B"+work;break;
    case 12:work="C"+work;break;
    case 13:work="D"+work;break;
    case 14:work="E"+work;break;
    case 15:work="F"+work;break;
  }
  rst=rst+work;
  return rst;
}

/*
 * 小数点のチェック
 * int checkDecimalPoint(String str, uint8_t type)
 *
 * 返り値 - 正:小数点の位置    0:点はなし    負:フォーマットエラー
 *
 */

int checkDecimalPoint(String str, uint8_t type) {
  int first, last;
  if (type==DECIMAL_POINT_PERIOD) {
    first=str.indexOf('.');
    last=str.lastIndexOf('.');
  } else if (type==DECIMAL_POINT_COMMA) {
    first=str.indexOf(',');
    last=str.lastIndexOf(',');
  } else {
    return -1;
  }
  if (first == 0) return -1;
  if (first < 0) return 0;
  if (first == last) return first;
  return -1;
}

float floatToStr(String str, uint8_t type) {
  int intStartPos=0;
  bool minus=false;
  int len=str.length();
  const char *work=str.c_str();
  char *charArray=(char*)work;

  if (charArray[0]=='-') {
    intStartPos=1;
    minus=true;
  }
  if (charArray[0]=='+') {
    intStartPos=1;
  }

  char decPointChar;
  switch(type) {
    case DECIMAL_POINT_PERIOD : decPointChar='.';break;
    case DECIMAL_POINT_COMMA  : decPointChar=',';break;
    default: return 0;
  }
  bool error=false;
  bool header=true;
  for (int i=intStartPos; i< len; i++) {
    if ((!isDigit(charArray[i])) && (decPointChar!=charArray[i])) error=true;
    if ((charArray[i]!='0') && (header)) header=false;
    if ((charArray[i]=='0') && (header)) intStartPos++;
  }
  if ((error) || (intStartPos==len)) return 0;
  int decStartPos=-1;
  int decEndPos=-1;
  int intEndPos=-1;
  int decPoint=checkDecimalPoint(str, type);
  if (decPoint < 0) return 0;
  if (decPoint==len) return 0;
  if (decPoint==0) {
    intEndPos=len;
  } else {
    intEndPos=decPoint;
    decStartPos=decPoint+1;
    decEndPos=len;
    if (decStartPos >= decEndPos) return 0;
  }
  uint64_t intVal=calcDec64Val( charArray + intStartPos , intEndPos - intStartPos );
  uint64_t decVal=0;
  if (decStartPos!=-1) decVal=calcDec64Val( charArray+decStartPos, decEndPos - decStartPos);
  if (intVal>UPPER_LIMIT_INT32) intVal=UPPER_LIMIT_INT32;
  float result=(float) decVal;
  for (int i=0; i< ( decEndPos - decStartPos) ; i++) {
    result=result/10;
  }
  result=result+(float) intVal;
  if (minus) {
    result=result*(-1);
  }
  return result;
}
