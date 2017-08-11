/*
 *
 * Purpose: The multiply instruction implementation
 *
 */

#include "header/multiply.h"
#include "header/instruction.h"
#include "header/bitmanipulation.h"

/* Multiply. */
void multiply(instruction *instr, ARM11 *arm) {
  if (instr->A == 0) {
    multiplyWithoutAccumulate(instr, arm);
  } else {
    multiplyWithAccumulate(instr, arm);
  }
}

/* Multiply without accumulate. */
void multiplyWithoutAccumulate(instruction *instr, ARM11 *arm) {
  uint32_t result = arm->gpr[instr->rm] * arm->gpr[instr->rs];
  arm->gpr[instr->rd] = result;
  if (instr->S == 1) {
    arm->cpsr->N = getBits(result, N_BIT, N_BIT);
    if (result == 0) {
      arm->cpsr->Z = 1;
    }
  }
}

/* Multiply with accumulate. */
void multiplyWithAccumulate(instruction *instr, ARM11 *arm) {
  uint32_t result = (arm->gpr[instr->rm] * arm->gpr[instr->rs])
      + arm->gpr[instr->rn];
  arm->gpr[instr->rd] = result;
  if (instr->S == 1) {
    arm->cpsr->N = getBits(result, N_BIT, N_BIT);
    if (result == 0) {
      arm->cpsr->Z = 1;
    }
  }
}
