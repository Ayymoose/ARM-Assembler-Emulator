/*
**
** Purpose: This file contains all bit manipulation functions 
**
*/

#include "header/bitmanipulation.h"

/* Creates a mask from startBit to endBit of a 32-bit integer */
uint32_t createMask(uint32_t startBit,uint32_t endBit) {
  return (2 << endBit) - (startBit > 0 ? (2 << (startBit - 1)) : 1);
}

/* Gets the bits from a 32-bit word from startBit to endBit */
uint32_t getBits(uint32_t word,uint32_t startBit,uint32_t endBit) {
  return (word & createMask(startBit, endBit)) >> startBit;
}

/* Reads a 32-bit word (4 bytes) from a memory address */
uint32_t readWord(uint8_t *memory) {
  return (memory[0]
      | (memory[1] << (BITS_IN_BYTE))
      | (memory[2] << (BITS_IN_BYTE * 2))
      | (memory[3] << (BITS_IN_BYTE * 3)));
}

/* Write a 32-bit word (4 bytes) to a memory address */
void writeWord(uint8_t *memory, uint32_t word) {
  memory[0] = word & BYTE_MASK;
  memory[1] = (word >> BITS_IN_BYTE) & BYTE_MASK;
  memory[2] = (word >> (BITS_IN_BYTE * 2)) & BYTE_MASK;
  memory[3] = (word >> (BITS_IN_BYTE * 3)) & BYTE_MASK;
}

/* Changes the endianess of a 32-bit word (big->little , little->big */
uint32_t changeEndianess(uint32_t word) {
  return ((word & (BYTE_MASK << (BITS_IN_BYTE * 3))) >> (BITS_IN_BYTE * 3))
      | ((word & (BYTE_MASK << (BITS_IN_BYTE * 2))) >> BITS_IN_BYTE)
      | ((word & (BYTE_MASK << BITS_IN_BYTE)) << BITS_IN_BYTE)
      | ((word & BYTE_MASK) << (BITS_IN_BYTE * 3));
}
