#ifndef _SLIOT_CORE_BIT_OPS_
#define _SLIOT_CORE_BIT_OPS_

#include "Arduino.h"
extern const uint8_t sliot_bit_reverse[16];

#define SLIOT_BIT_OP_8B_4L(val) \
          ((val) & 0xF)
#define SLIOT_BIT_OP_8B_4H(val) \
          (((val)>>4) & 0xF)
#define SLIOT_BIT_OP_16B_8L(val) \
          ((val) & 0xFF)
#define SLIOT_BIT_OP_16B_8H(val) \
          (((val)>>8) & 0xFF)
#define SLIOT_BIT_OP_32B_16L(val) \
          ((val) & 0xFFFF)
#define SLIOT_BIT_OP_32B_16H(val) \
          (((val)>>16) & 0xFFFF)


#define SLIOT_BIT_OP_REVERSE_4BIT(val) \
          (sliot_bit_reverse[val & 0xF])
#define SLIOT_BIT_OP_REVERSE_8BIT(val) \
          ( SLIOT_BIT_OP_REVERSE_4BIT(SLIOT_BIT_OP_8B_4L(val)) << 4 | SLIOT_BIT_OP_REVERSE_4BIT(SLIOT_BIT_OP_8B_4H(val)) )
#define SLIOT_BIT_OP_REVERSE_16BIT(val) \
          ( SLIOT_BIT_OP_REVERSE_8BIT(SLIOT_BIT_OP_16B_8L(val)) << 8 | SLIOT_BIT_OP_REVERSE_8BIT(SLIOT_BIT_OP_16B_8H(val)) )
#define SLIOT_BIT_OP_REVERSE_32BIT(val) \
          ( SLIOT_BIT_OP_REVERSE_16BIT(SLIOT_BIT_OP_32B_16L(val)) << 16 | SLIOT_BIT_OP_REVERSE_8BIT(SLIOT_BIT_OP_32B_16H(val)) )

#define SLIOT_BIT_OP_REVERSE_OCTET_16B(val) \
          ( (SLIOT_BIT_OP_16B_8L(val) << 8) | SLIOT_BIT_OP_16B_8H(val) )

#define SLIOT_BIT_OP_REVERSE_OCTET_32B(val) \
          ( (SLIOT_BIT_OP_REVERSE_OCTET_16B(SLIOT_BIT_OP_32B_16L(val)) << 16) | SLIOT_BIT_OP_REVERSE_OCTET_16B(SLIOT_BIT_OP_32B_16H(val)) )

#endif //_SLIOT_CORE_BIT_OPS_