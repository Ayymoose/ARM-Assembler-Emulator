/*
 *
 * Purpose: Shifter function implementations
 *
 */

#include <stdbool.h>

#include "header/shifter.h"
#include "header/bitmanipulation.h"

/* Performs left shift on number by specified amount */
uint32_t logLeftShift(uint32_t num, uint32_t shift, bool setFlags,
    ARM11 *arm11) {
  if (setFlags) {
    uint32_t discardedBit = getBits(num, (32 - shift), (32 - shift));
    arm11->cpsr->C = discardedBit;
  }
  return num << shift;
}

/* Performs right shift on number by specified amount */
uint32_t logRightShift(uint32_t num, uint32_t shift, bool setFlags,
    ARM11 *arm11) {
  if (setFlags) {
    uint32_t discardedBit = getBits(num, (shift - 1), (shift - 1));
    arm11->cpsr->C = discardedBit;
  }
  return num >> shift;
}

/* Performs right shift on number by specified amount preserving the sign */

uint32_t arithRightShift(int32_t num, uint32_t shift, bool setFlags,
    ARM11 *arm11) {
  if (setFlags) {
    uint32_t discardedBit = getBits(num, (shift - 1), (shift - 1));
    arm11->cpsr->C = discardedBit;
  }
  return num >> shift;
}

/* Performs left shift on number by specified amount and preserves the sign */
int32_t arithLeftShift(int32_t num, uint32_t shift) {
  return num << shift;
}

/* Performs right shift on number by specified amount,
 * least significant bits rotated round to most significant positions*/
uint32_t rotRight(uint32_t num, uint32_t shift, bool setFlags, ARM11 *arm11) {
  if (setFlags) {
    uint32_t discardedBit = getBits(num, (shift - 1), (shift - 1));
    arm11->cpsr->C = discardedBit;
  }
  if (shift == 0) {
    return num;
  }
  uint32_t endBits = getBits(num, 0, shift - 1);
  endBits <<= (32 - shift);
  return endBits | (logRightShift(num, shift, setFlags, arm11));
}

/* Shifts, treating operand2 as register */
uint32_t shifterReg(uint32_t operand2, ARM11 *arm11, bool setFlags) {
  reg32 reg = getBits(operand2, 0, 3);
  if (getBits(operand2, 4, 4) == 0) {
    uint32_t shiftAmount = getBits(operand2, 7, 11);
    uint32_t shiftType = getBits(operand2, 5, 6);
    switch (shiftType) {
    case 0:
      return logLeftShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
    case 1:
      return logRightShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
    case 2:
      return arithRightShift(arm11->gpr[reg], shiftAmount, setFlags,
          arm11);
    case 3:
      return rotRight(arm11->gpr[reg], shiftAmount, setFlags, arm11);
    default:
      return operand2;
    }
  } else {
    uint32_t shiftAmount = getBits(arm11->gpr[getBits(operand2, 8, 11)], 0,
        7);
    uint32_t shiftType = getBits(operand2, 5, 6);
    switch (shiftType) {
    case 0:
      return logLeftShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
    case 1:
      return logRightShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
    case 2:
      return arithRightShift(arm11->gpr[reg], shiftAmount, setFlags,
          arm11);
    case 3:
      return rotRight(arm11->gpr[reg], shiftAmount, setFlags, arm11);
    default:
      return operand2;
    }
  }
  return operand2;
}

/* Shifts, treating operand2 as immediate constant */
uint32_t shifterImm(uint32_t operand2, ARM11 *arm11, bool setFlags) {
  uint32_t val = getBits(operand2, 0, 7);
  uint32_t rotAmount = getBits(operand2, 8, 11);
  return rotRight(val, 2 * rotAmount, setFlags, arm11);
}
