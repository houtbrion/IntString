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

extern String   boolToString(bool flag);
extern bool     strToBool(String buff, bool flag=true);
extern bool     checkBoolStr(String buff);
extern int8_t   strToInt8(String str);
extern uint8_t  strToUint8(String str);
extern int16_t  strToInt16(String str);
extern uint16_t strToUint16(String str);
extern int32_t  strToInt32(String str);
extern uint32_t strToUint32(String str);
extern int64_t calcOctVal(char *str,int length);

