/*
 **
 ** Purpose: The instruction implementations of the ARM emulator.
 **
 */

#include "header/processor.h"
#include "header/instruction.h"
#include "header/shifter.h"
#include "header/bitmanipulation.h"

/* Check if oparand2 is register or constant*/
bool checkOpReg(instruction *instr) {
  return (instr->I == 0);
}

/* Check if CPSR flags need to be set */
bool checkSetFlags(instruction *instr) {
  return instr->S == 1;
}

/* Rn AND operand2 */
uint32_t and(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = arm11->gpr[instr->rn]
        & shifterReg(instr->operand2, arm11, checkSetFlags(instr));
  } else {
    result = arm11->gpr[instr->rn]
        & shifterImm(instr->operand2, arm11, checkSetFlags(instr));
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
  return result;
}

/* Rn EOR(XOR) operand2 */
uint32_t eor(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = arm11->gpr[instr->rn]
        ^ shifterReg(instr->operand2, arm11, checkSetFlags(instr));
  } else {
    result = arm11->gpr[instr->rn]
        ^ shifterImm(instr->operand2, arm11, checkSetFlags(instr));
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
  return result;
}

/* Rn SUB operand2 */
uint32_t sub(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = arm11->gpr[instr->rn] - shifterReg(instr->operand2, arm11, false);
  } else {
    result = arm11->gpr[instr->rn] - shifterImm(instr->operand2, arm11, false);
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    arm11->cpsr->C = (result <= createMask(0, 31));
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
  return result;
}

/* operand2 - Rn */
uint32_t rsb(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = shifterReg(instr->operand2, arm11, false) - arm11->gpr[instr->rn];
  } else {
    result = shifterImm(instr->operand2, arm11, false) - arm11->gpr[instr->rn];
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    arm11->cpsr->C = (result <= createMask(0, 31));
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
  return result;
}

/* Rn + operand2 */
uint32_t add(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = arm11->gpr[instr->rn] + shifterReg(instr->operand2, arm11, false);
  } else {
    result = arm11->gpr[instr->rn] + shifterImm(instr->operand2, arm11, false);
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    arm11->cpsr->C = (result > createMask(0, 31));
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
  return result;
}

/* Same as and() but result not written */
void tst(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = arm11->gpr[instr->rn]
        & shifterReg(instr->operand2, arm11, checkSetFlags(instr));
  } else {
    result = arm11->gpr[instr->rn]
        & shifterImm(instr->operand2, arm11, checkSetFlags(instr));
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
}

/* Same as eor() but result not written */
void teq(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = arm11->gpr[instr->rn]
        ^ shifterReg(instr->operand2, arm11, checkSetFlags(instr));
  } else {
    result = arm11->gpr[instr->rn]
        ^ shifterImm(instr->operand2, arm11, checkSetFlags(instr));
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
}

/* Same as sub() but result not written */
void cmp(instruction *instr, ARM11 *arm11) {
  uint64_t result; /* UINT 64 !!!*/
  if (checkOpReg(instr)) {
    result = arm11->gpr[instr->rn] - shifterReg(instr->operand2, arm11, false);
  } else {
    result = arm11->gpr[instr->rn] - shifterImm(instr->operand2, arm11, false);
  }
  uint32_t operand2 = (
      checkOpReg(instr) ?
          shifterReg(instr->operand2, arm11, false) :
          shifterImm(instr->operand2, arm11, false));
  arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
  arm11->cpsr->C = !(operand2 > arm11->gpr[instr->rn]);
  if (result == 0) {
    arm11->cpsr->Z = 1;
  }
}

/* Rn OR operand2 */
uint32_t orr(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = arm11->gpr[instr->rn]
        | shifterReg(instr->operand2, arm11, checkSetFlags(instr));
  } else {
    result = arm11->gpr[instr->rn]
        | shifterImm(instr->operand2, arm11, checkSetFlags(instr));
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
  return result;
}

/* mov Rd,operand2 */
uint32_t mov(instruction *instr, ARM11 *arm11) {
  uint32_t result;
  if (checkOpReg(instr)) {
    result = shifterReg(instr->operand2, arm11, checkSetFlags(instr));
  } else {
    result = shifterImm(instr->operand2, arm11, checkSetFlags(instr));
  }
  if (checkSetFlags(instr)) {
    arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
    if (result == 0) {
      arm11->cpsr->Z = 1;
    }
  }
  return result;
}
