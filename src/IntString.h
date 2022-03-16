#include "Arduino.h"
#include <string.h>

#define CONV_ERROR_FORMAT -1
#define CONV_SUCCESS       1
#define CONV_DATA_DEC      0
#define CONV_DATA_HEX      1
#define CONV_DATA_BIN      2
#define CONV_DATA_OCT      3

#define UPPER_LIMIT_INT8    127
#define LOWER_LIMIT_INT8   -128
#define UPPER_LIMIT_UINT8   255
#define LOWER_LIMIT_UINT8   0
#define UPPER_LIMIT_INT16   32767
#define LOWER_LIMIT_INT16  -32768
#define UPPER_LIMIT_UINT16  65535
#define LOWER_LIMIT_UINT16  0
#define UPPER_LIMIT_INT32   2147483647
#define LOWER_LIMIT_INT32  -2147483648
#define UPPER_LIMIT_UINT32  4294967295
#define LOWER_LIMIT_UINT32  0

#define UPPER_LIMIT_INT64   9223372036854775807LL
#define LOWER_LIMIT_INT64  -9223372036854775808LL
#define CONV_THRESH_INT64   9223372036854775808LL

#define UPPER_LIMIT_UINT64  18446744073709551615ULL
#define LOWER_LIMIT_UINT64  0
#define UPPER_LIMIT_UINT64_DIV_BIN 9223372036854775807ULL
#define UPPER_LIMIT_UINT64_DIV_OCT 2305843009213693951ULL
#define UPPER_LIMIT_UINT64_DIV_HEX 1152921504606846975ULL
#define UPPER_LIMIT_UINT64_DIV_DEC 1844674407370955161ULL
#define UPPER_LIMIT_UINT64_MINUS_1 18446744073709551614ULL
#define UPPER_LIMIT_UINT64_MINUS_2 18446744073709551613ULL
#define UPPER_LIMIT_UINT64_MINUS_3 18446744073709551612ULL
#define UPPER_LIMIT_UINT64_MINUS_4 18446744073709551611ULL
#define UPPER_LIMIT_UINT64_MINUS_5 18446744073709551610ULL
#define UPPER_LIMIT_UINT64_MINUS_6 18446744073709551609ULL
#define UPPER_LIMIT_UINT64_MINUS_7 18446744073709551608ULL
#define UPPER_LIMIT_UINT64_MINUS_8 18446744073709551607ULL
#define UPPER_LIMIT_UINT64_MINUS_9 18446744073709551606ULL
#define UPPER_LIMIT_UINT64_MINUS_A 18446744073709551605ULL
#define UPPER_LIMIT_UINT64_MINUS_B 18446744073709551604ULL
#define UPPER_LIMIT_UINT64_MINUS_C 18446744073709551603ULL
#define UPPER_LIMIT_UINT64_MINUS_D 18446744073709551602ULL
#define UPPER_LIMIT_UINT64_MINUS_E 18446744073709551601ULL
#define UPPER_LIMIT_UINT64_MINUS_F 18446744073709551600ULL

extern String   boolToString(bool flag);
extern bool     strToBool(String buff, bool flag=true);
extern bool     checkBoolStr(String buff);
extern int8_t   strToInt8(String str);
extern uint8_t  strToUint8(String str);
extern int16_t  strToInt16(String str);
extern uint16_t strToUint16(String str);
extern int32_t  strToInt32(String str);
extern uint32_t strToUint32(String str);
extern int64_t strToInt64(String str);
extern uint64_t strToUint64(String str);

extern String int32ToStr(int32_t val, uint8_t type=DEC, bool header=true);
extern String uint32ToStr(uint32_t val, uint8_t type=DEC, bool header=true);
extern String int8ToStr(int8_t val, uint8_t type=DEC, bool header=true);
extern String uint8ToStr(uint8_t val, uint8_t type=DEC, bool header=true);
extern String int16ToStr(int16_t val, uint8_t type=DEC, bool header=true);
extern String uint16ToStr(uint16_t val, uint8_t type=DEC, bool header=true);
extern String int64ToStr(int64_t val, uint8_t type=DEC, bool header=true);
extern String uint64ToStr(uint64_t val, uint8_t type=DEC, bool header=true);


extern bool isOctDigit(char a);
//extern int64_t  calcOctVal(char *str,int length);
//extern uint64_t calcDec64Val(char *target,int len);
//extern uint64_t calcHex64Val(char *target,int len);
//extern uint64_t calcOct64Val(char *target,int len);
//extern uint64_t calcBin64Val(char *target,int len);
