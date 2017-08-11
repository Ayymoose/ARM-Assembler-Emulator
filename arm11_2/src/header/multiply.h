#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "processor.h"

/* Multiply. */
void multiply(instruction *instr, ARM11 *arm);

/* Multiply without accumulate. */
void multiplyWithoutAccumulate(instruction *instr, ARM11 *arm);

/* Multiply with accumulate. */
void multiplyWithAccumulate(instruction *instr, ARM11 *arm);

#endif
