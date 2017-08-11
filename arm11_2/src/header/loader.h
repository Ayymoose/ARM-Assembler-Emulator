#ifndef LOADER_H
#define LOADER_H

#include <stdint.h>
//#include "structure.h"


/* Instruction bits */
#define BRANCH_BIT 27                /* BRANCH instruction bit 27 */
#define SINGLE_DATA_TRANSFER_BIT 26  /* SINGLE_DATA_TRANSFER instruction bit 26 */ /* Exceeds 80 chars */
#define DATA_PROCESSING_BIT 25       /* DATA_PROCESSING instruction bit 25 */
/* Multiply */
#define MULTIPLY_BIT_START 4
#define MULTIPLY_BIT_END 7
#define MULTIPLY_BITS 9              /* bin(1001) = dec(9) for MULTIPLY */

/* Loads the binary file into memory and returns a 8-bit pointer to the memory */
void loadBinary(const char *fileName,uint8_t *memory);

#endif
