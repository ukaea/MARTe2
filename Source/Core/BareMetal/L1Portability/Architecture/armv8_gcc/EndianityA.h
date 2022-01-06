/**
 * @file EndianityA.h
 * @brief Header file for module EndianityA
 * @date 18/01/2022
 * @author Colin Hogben
 *
 * @details This header file contains the declaration of the module EndianityA
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef ENDIANITYA_H_
#define ENDIANITYA_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Module declaration                               */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

namespace MARTe{

namespace Endianity {

// Use GCC built-in functions

inline void Swap32(volatile void *x) {
    uint32 *xx = (uint32 *) x;
    *xx = __builtin_bswap32(*xx);
}

inline void Swap32(volatile void *x,
                   uint32 sizer) {
    register uint32 *xx = (uint32 *) x;
    for (uint32 i = 0; i < sizer; i++) {
        register uint32 temp = *xx;
        *xx = __builtin_bswap32(temp);
        xx++;
    }
}

inline void MemCopySwap32(volatile void *dest,
                          volatile const void *src,
                          uint32 sizer) {
    register uint32 *s = (uint32 *) src;
    register uint32 *d = (uint32 *) dest;
    for (uint32 i = 0; i < sizer; i++) {
        uint32 temp = *s;
        *d = __builtin_bswap32(temp);
        d++;
        s++;
    }
}

inline void Swap16(volatile void *x) {
    uint16 *xx = (uint16 *) x;
    uint16 temp = *xx;
    *xx = __builtin_bswap16(temp);
}

inline void Swap16(volatile void *x,
                   uint32 sizer) {
    uint16 *xx = (uint16 *) x;
    for (uint32 i = 0; i < sizer; i++) {
	uint16 temp = *xx;
	*xx = __builtin_bswap16(temp);
        xx++;
    }
}

inline void MemCopySwap16(volatile void *dest,
                          volatile const void *src,
                          uint32 sizer) {
    uint16 *s = (uint16 *) src;
    uint16 *d = (uint16 *) dest;
    for (uint32 i = 0; i < sizer; i++) {
	uint16 temp = *s;
	*d = __builtin_bswap16(temp);
        s++;
        d++;
    }
}

inline void Swap64(volatile void *x) {
    uint64 *xx = (uint64 *) x;
    uint64 temp = *xx;
    *xx = __builtin_bswap64(temp);
}

inline void MemCopySwap64(volatile void *dest,
                          volatile const void *src,
                          uint32 sizer) {
    uint64 *s = (uint64 *) src;
    uint64 *d = (uint64 *) dest;
    for (uint32 i = 0; i < sizer; i++) {
	uint64 temp = *s;
	*d = __builtin_bswap64(temp);
        d++;
        s++;
    }
}

inline void FromBigEndian(volatile float64 &x) {
    Swap64(&x);
}

inline void FromBigEndian(volatile float32 &x) {
    Swap32(&x);
}

inline void FromBigEndian(volatile uint64 &x) {
    Swap64(&x);
}

inline void FromBigEndian(volatile uint32 &x) {
    Swap32(&x);
}

inline void FromBigEndian(volatile uint16 &x) {
    Swap16(&x);
}

inline void FromBigEndian(volatile int64 &x) {
    Swap64(&x);
}

inline void FromBigEndian(volatile int32 &x) {
    Swap32(&x);
}

inline void FromBigEndian(volatile int16 &x) {
    Swap16(&x);
}

inline void FromLittleEndian(volatile float64 &x) {
}

inline void FromLittleEndian(volatile float32 &x) {
}

inline void FromLittleEndian(volatile uint64 &x) {
}

inline void FromLittleEndian(volatile uint32 &x) {
}

inline void FromLittleEndian(volatile uint16 &x) {
}

inline void FromLittleEndian(volatile int64 &x) {
}

inline void FromLittleEndian(volatile int32 &x) {
}

inline void FromLittleEndian(volatile int16 &x) {
}

inline void ToBigEndian(volatile float64 &x) {
    Swap64(&x);
}

inline void ToBigEndian(volatile float32 &x) {
    Swap32(&x);
}

inline void ToBigEndian(volatile uint64 &x) {
    Swap64(&x);
}

inline void ToBigEndian(volatile uint32 &x) {
    Swap32(&x);
}

inline void ToBigEndian(volatile uint16 &x) {
    Swap16(&x);
}

inline void ToBigEndian(volatile int64 &x) {
    Swap64(&x);
}

inline void ToBigEndian(volatile int32 &x) {
    Swap32(&x);
}

inline void ToBigEndian(volatile int16 &x) {
    Swap16(&x);
}

inline void ToLittleEndian(volatile float64 &x) {
}

inline void ToLittleEndian(volatile float32 &x) {
}

inline void ToLittleEndian(volatile uint64 &x) {
}

inline void ToLittleEndian(volatile uint32 &x) {
}

inline void ToLittleEndian(volatile uint16 &x) {
}

inline void ToLittleEndian(volatile int64 &x) {
}

inline void ToLittleEndian(volatile int32 &x) {
}

inline void ToLittleEndian(volatile int16 &x) {
}

inline void MemCopyFromBigEndian(float64 *dest,
                                 const float64 *src,
                                 uint32 size) {
    MemCopySwap64(dest, src, size);
}

inline void MemCopyFromBigEndian(uint64 *dest,
                                 const uint64 *src,
                                 uint32 size) {
    MemCopySwap64(dest, src, size);
}

inline void MemCopyFromBigEndian(int64 *dest,
                                 const int64 *src,
                                 uint32 size) {
    MemCopySwap64(dest, src, size);
}

inline void MemCopyFromBigEndian(float32 *dest,
                                 const float32 *src,
                                 uint32 size) {
    MemCopySwap32(dest, src, size);
}

inline void MemCopyFromBigEndian(uint32 *dest,
                                 const uint32 *src,
                                 uint32 size) {
    MemCopySwap32(dest, src, size);
}

inline void MemCopyFromBigEndian(uint16 *dest,
                                 const uint16 *src,
                                 uint32 size) {
    MemCopySwap16(dest, src, size);
}

inline void MemCopyFromBigEndian(int32 *dest,
                                 const int32 *src,
                                 uint32 size) {
    MemCopySwap32(dest, src, size);
}

inline void MemCopyFromBigEndian(int16 *dest,
                                 const int16 *src,
                                 uint32 size) {
    MemCopySwap16(dest, src, size);
}

inline void MemCopyFromLittleEndian(float64 *dest,
                                    const float64 *src,
                                    uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyFromLittleEndian(uint64 *dest,
                                    const uint64 *src,
                                    uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyFromLittleEndian(int64 *dest,
                                    const int64 *src,
                                    uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyFromLittleEndian(float32 *dest,
                                    const float32 *src,
                                    uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyFromLittleEndian(uint32 *dest,
                                    const uint32 *src,
                                    uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyFromLittleEndian(uint16 *dest,
                                    const uint16 *src,
                                    uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyFromLittleEndian(int32 *dest,
                                    const int32 *src,
                                    uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyFromLittleEndian(int16 *dest,
                                    const int16 *src,
                                    uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyToBigEndian(float64 *dest,
                               const float64 *src,
                               uint32 size) {
    MemCopySwap64(dest, src, size);
}

inline void MemCopyToBigEndian(uint64 *dest,
                               const uint64 *src,
                               uint32 size) {
    MemCopySwap64(dest, src, size);
}

inline void MemCopyToBigEndian(int64 *dest,
                               const int64 *src,
                               uint32 size) {
    MemCopySwap64(dest, src, size);
}

inline void MemCopyToBigEndian(float32 *dest,
                               const float32 *src,
                               uint32 size) {
    MemCopySwap32(dest, src, size);
}

inline void MemCopyToBigEndian(uint32 *dest,
                               const uint32 *src,
                               uint32 size) {
    MemCopySwap32(dest, src, size);
}

inline void MemCopyToBigEndian(uint16 *dest,
                               const uint16 *src,
                               uint32 size) {
    MemCopySwap16(dest, src, size);
}

inline void MemCopyToBigEndian(int32 *dest,
                               const int32 *src,
                               uint32 size) {
    MemCopySwap32(dest, src, size);
}

inline void MemCopyToBigEndian(int16 *dest,
                               const int16 *src,
                               uint32 size) {
    MemCopySwap16(dest, src, size);
}

inline void MemCopyToLittleEndian(float64 *dest,
                                  const float64 *src,
                                  uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyToLittleEndian(uint64 *dest,
                                  const uint64 *src,
                                  uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyToLittleEndian(int64 *dest,
                                  const int64 *src,
                                  uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyToLittleEndian(float32 *dest,
                                  const float32 *src,
                                  uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyToLittleEndian(uint32 *dest,
                                  const uint32 *src,
                                  uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyToLittleEndian(uint16 *dest,
                                  const uint16 *src,
                                  uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyToLittleEndian(int32 *dest,
                                  const int32 *src,
                                  uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

inline void MemCopyToLittleEndian(int16 *dest,
                                  const int16 *src,
                                  uint32 size) {
    for (uint32 i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

}
}
#endif /* ENDIANITYA_H_ */

