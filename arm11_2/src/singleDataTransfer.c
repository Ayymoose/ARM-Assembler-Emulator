/*
 *
 * Purpose: Single data transfer instructions
 *
 */
#include <stdio.h>
#include <stdbool.h>

#include "header/shifter.h"
#include "header/loader.h"
#include "header/bitmanipulation.h"
#include "header/singleDataTransfer.h"

#define PC 15 /* Program counter is register 15 */

/* Loads data from a memory address to a register */
void ldr(instruction *instr, ARM11 *arm) {
  uint32_t memoryAddress;
  if (instr->U == 1) {
    memoryAddress = (
        instr->rn == PC ?
            (arm->pc + instr->offset) : (arm->gpr[instr->rn] + instr->offset));
  } else {
    memoryAddress = (
        instr->rn == PC ?
            (arm->pc - instr->offset) : (arm->gpr[instr->rn] - instr->offset));
  }
  /* Check that access is valid */
  if (memoryAddress < MEMORY_SIZE) {
    /* Read 4-bytes from memory + memoryAddress */
    arm->gpr[instr->rd] = readWord(arm->memory + memoryAddress);
  } else {
    printf("Error: Out of bounds memory access at address 0x%08x\n",
        memoryAddress);
  }
}

/* Stores data from a register to another register */
void str(instruction *instr, ARM11 *arm) {
  uint32_t memoryAddress;
  if (instr->U == 1) {
    memoryAddress = (
        instr->rn == PC ?
            (arm->pc + instr->offset) : (arm->gpr[instr->rn] + instr->offset));
  } else {
    memoryAddress = (
        instr->rn == PC ?
            (arm->pc - instr->offset) : (arm->gpr[instr->rn] - instr->offset));
  }
  /* Write 4 bytes to memory */
  writeWord(arm->memory + memoryAddress, arm->gpr[instr->rd]);
}

/* Single data transfer instruction */
void singleDataTransfer(instruction *instr, ARM11 *arm11) {

  // I - FLAG CHECK i.e 2nd bullet point.
  if (instr->I == 1) {
    instr->offset = shifterReg(instr->offset, arm11, false);
  }

  // P - FLAG CHECK i.e 3rd bullet point.
  // if P == 1 then just transfer without arithmetic operations.
  if (instr->P == 1) {
    // if L == 1 then load
    if (instr->L == 1) {
      ldr(instr, arm11);
    } else {
      str(instr, arm11);
    }
    // else if P == 0
  } else {
    // if L == 1 then load
    if (instr->L == 1) {
      ldr(instr, arm11);
      // and then if U == 1 then add
      if (instr->U == 1) {
        arm11->gpr[instr->rn] += instr->offset;
      } else {	// else if U == 0 u subtract
        arm11->gpr[instr->rn] -= instr->offset;
      }
    } else {
      // if L == 0 then store function is called
      str(instr, arm11);
      if (instr->U == 1) {
        // and after this transfer, if U == 1 then addition is done
        arm11->gpr[instr->rn] += instr->offset;
      } else {
        // else subtraction follows.
        arm11->gpr[instr->rn] -= instr->offset;
      }
    }
  }
}
