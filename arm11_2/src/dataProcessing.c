/*
 *
 * Purpose: Data processing instruction
 *
 */

#include "header/shifter.h"
#include "header/instruction.h"
#include "header/dataProcessing.h"

/* Performs a data processing instruction */
void dataProcessing(instruction *instr, ARM11 *arm11) {
  switch (instr->opcode) {
  case AND:
    arm11->gpr[instr->rd] = and(instr, arm11);
    break;
  case EOR:
    arm11->gpr[instr->rd] = eor(instr, arm11);
    break;
  case SUB:
    arm11->gpr[instr->rd] = sub(instr, arm11);
    break;
  case RSB:
    arm11->gpr[instr->rd] = rsb(instr, arm11);
    break;
  case ADD:
    arm11->gpr[instr->rd] = add(instr, arm11);
    break;
  case TST:
    tst(instr, arm11);
    break;
  case TEQ:
    teq(instr, arm11);
    break;
  case CMP:
    cmp(instr, arm11);
    break;
  case ORR:
    arm11->gpr[instr->rd] = orr(instr, arm11);
    break;
  case MOV:
    arm11->gpr[instr->rd] = mov(instr, arm11);
  }
}
