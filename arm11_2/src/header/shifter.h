#ifndef SHIFTER_H
#define SHIFTER_H

#include "processor.h"

/* Shifter signartures */

uint32_t logLeftShift(uint32_t num, uint32_t shift, bool setFlags, ARM11 *arm11Ptr);

uint32_t logRightShift(uint32_t num, uint32_t shift, bool setFlags, ARM11 *arm11Ptr);

uint32_t arithRightShift(int32_t num, uint32_t shift, bool setFlags, ARM11 *arm11Ptr);

int32_t arithLeftShift(int32_t num, uint32_t shift);

uint32_t rotRight(uint32_t num, uint32_t shift, bool setFlags, ARM11 *arm11Ptr);

uint32_t shifterReg(uint32_t operand2, ARM11 *arm11Ptr, bool setFlags);

uint32_t shifterImm(uint32_t operand2, ARM11 *arm11Ptr, bool setFlags);

#endif
