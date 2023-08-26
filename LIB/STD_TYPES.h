#pragma once

typedef unsigned char       uint8;
typedef signed char         sint8;
typedef unsigned short      uint16;
typedef signed short        sint16;
typedef unsigned int        uint32;
typedef signed int          sint32;
typedef unsigned long long  uint64;
typedef signed long long    sint64;

typedef unsigned char       bool;
#define true                (1)
#define false               (0)

/* Bit manipulation macros */
#define SET_BIT(reg, bit)     ((reg) |= (1U << (bit)))
#define CLEAR_BIT(reg, bit)   ((reg) &= ~(1U << (bit)))
#define TOGGLE_BIT(reg, bit)  ((reg) ^= (1U << (bit)))
#define GET_BIT(reg, bit)     (((reg) >> (bit)) & 1U)

/* Maximum and minimum values for fixed-width types */
#define INT8_MIN      (-128)
#define INT8_MAX       127
#define UINT8_MAX      255
#define INT16_MIN     (-32768)
#define INT16_MAX      32767
#define UINT16_MAX     65535
#define INT32_MIN     (-2147483647 - 1)
#define INT32_MAX      2147483647
#define UINT32_MAX     4294967295U
#define INT64_MIN     (-9223372036854775807LL - 1)
#define INT64_MAX      9223372036854775807LL
#define UINT64_MAX     18446744073709551615ULL

/* Macro to calculate the number of elements in an array */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

