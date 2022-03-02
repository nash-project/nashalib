#pragma once

#define ENDIANESS__BIG_ENDIAN__ 0
#define ENDIANESS__LITTLE_ENDIAN__ 1
#define ENDIANESS__UNKNOWN_ENDIAN 2

#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
    defined(__BIG_ENDIAN__) || \
    defined(__ARMEB__) || \
    defined(__THUMBEB__) || \
    defined(__AARCH64EB__) || \
    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
    #define __ENDIANESS__ ENDIANESS__BIG_ENDIAN__

#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__) || \
    defined(__ARMEL__) || \
    defined(__THUMBEL__) || \
    defined(__AARCH64EL__) || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
    #define __ENDIANESS__ ENDIANESS__LITTLE_ENDIAN__
#else
#define __ENDIANESS__ ENDIANESS__UNKNOWN_ENDIAN
#endif

