/*
**
** Purpose: This file contains the branch instruction implementation
**
*/

#include "header/branch.h"
#include "header/shifter.h"

/* Performs a branch instruction */
void branch(instruction *instr, ARM11 *arm)	{
	uint32_t offset = instr->offset;
	int32_t shiftedOffset = arithLeftShift(offset, 2);
	arm->pc += shiftedOffset;
}
