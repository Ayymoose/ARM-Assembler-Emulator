#ifndef BITMANIPULATION_H
#define BITMANIPULATION_H

#include <stdint.h>

/* General bits */
#define BITS_IN_BYTE 8
#define BYTE_MASK 0x000000FF /* Mask for extracting bytes */

/* Gets the bits from a 32-bit word from startBit to endBit */
uint32_t getBits(uint32_t instructionWord,uint32_t startBit,uint32_t endBit);

/* Creates a mask from startBit to endBit of a 32-bit integer */
uint32_t createMask(uint32_t startBit,uint32_t endBit);

/* Reads a 32-bit word (4 bytes) from a memory address */
uint32_t readWord(uint8_t *memory);

/* Write a 32-bit word (4 bytes) to a memory address */
void writeWord(uint8_t *memory, uint32_t value);

/* Changes the endianess of a 32-bit word (big->little , little->big */
uint32_t changeEndianess(uint32_t number);

#endif
