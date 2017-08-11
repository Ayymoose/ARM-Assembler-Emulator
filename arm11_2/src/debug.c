/*
**
** Purpose: Contaings the prototypes for all debugging functions
**
*/


#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "header/debug.h"
#include "header/processor.h"
#include "header/instruction.h"

/* FUNCTION DECLARATIONS */

/* Loads the binary file into memory */
void loadBinaryDebug(const char *fileName,uint32_t *memory) {
  FILE* file = fopen(fileName,"r");
  printf("loadBinaryDebug()\n");
  printf("---------------\n");
  printf("File name:\t%s\n",fileName);
  assert(file != NULL);

  /* Read one element of size MEMORY_SIZE into our buffer */
  uint32_t bytesRead = fread(memory,1,MEMORY_SIZE,file);
  printf("Bytes read into memory:\t%u\n",bytesRead);
  printf("---------------\n");
  fclose(file);
}

/* Initialises the ARM11 processor; allocating 64KB of memory and clearing all registers */
ARM11* initialiseDebug() {

  printf("initialiseDebug()\n");
  printf("-----------------\n");
  printf("Allocating memory for ARM11 processor\n");
  ARM11 *arm11Ptr = (ARM11*)malloc(sizeof(ARM11));
  assert(arm11Ptr != NULL);
  printf("Allocated %u bytes of memory\n",sizeof(ARM11));

  /* Allocate 64KB of memory (*sizeof(uint8_t) because memory is byte addressable) and clear */
  printf("Allocating memory for ARM11->memory\n");
  arm11Ptr->memory = calloc(MEMORY_SIZE * sizeof(uint8_t),sizeof(uint32_t));
  assert(arm11Ptr->memory != NULL);
  printf("Allocated %u bytes of memory for ARM11->memory\n",MEMORY_SIZE * sizeof(uint8_t) * sizeof(uint32_t));
  printf("Allocating memory for ARM11->cpsr\n");
  arm11Ptr->cpsr = calloc(sizeof(CPSR),sizeof(bool));
  assert(arm11Ptr->cpsr != NULL);
  printf("Allocated %u bytes of memory for ARM11->cpsr\n",sizeof(CPSR) * sizeof(bool));
  printf("-----------------\n");

  /* Clear all registers */
  //arm11Ptr->r13 = 0;
  //arm11Ptr->r14 = 0;
  arm11Ptr->pc = 0;
  //arm11Ptr->alu = 0;
  for (int i=0; i<GPR_REGISTERS; i++) {
    arm11Ptr->gpr[i] = 0;
  }
  arm11Ptr->cpsr->N = 0;
  arm11Ptr->cpsr->Z = 0;
  arm11Ptr->cpsr->C = 0;
  arm11Ptr->cpsr->V = 0;

  return arm11Ptr;
}

//
instruction* decodeDebug(uint32_t fetched) {
  /* Must malloc() memory for these structures */

  printf("decodeDebug()\n");
  printf("-------------\n");
  /* Must call free() when done! */

  printf("Allocating memory for instruction\n");
  instruction *type = (instruction*)malloc(sizeof(instruction));
  assert(type != NULL);
  printf("Allocating %u bytes for *type\n",sizeof(instruction));

  type->id = fetched;

  printf("Fetched instruction is a ");

  switch (getType(fetched)) {
  case BRANCH_INSTR:
    printf("BRANCH Instruction\n");
    type->cond = getBits(fetched, 28, 31);
    type->offset = getBits(fetched, 0, 23);

    break;
  case MULTIPLY_INSTR:
    printf("MULTIPLY Instruction\n");
    type->cond = getBits(fetched, 28, 31);
    type->A = getBits(fetched, 21, 21);
    type->S = getBits(fetched, 20, 20);
    type->rd = getBits(fetched, 16, 19);
    type->rn = getBits(fetched, 12, 15);
    type->rs = getBits(fetched,8, 11);
    type->rm = getBits(fetched,0, 3);
    break;
  case DATA_PROCESSING_INSTR:
    printf("DATA_PROCESSING Instruction\n");
    type->cond = getBits(fetched, 28, 31);
    type->I = getBits(fetched, 25, 25);
    type->opcode = getBits(fetched, 21, 24);
    type->rn = getBits(fetched,16, 19);
    type->rd = getBits(fetched,12, 15);
    type->operand2 = getBits(fetched, 0, 11);
    break;
  case SINGLE_DATA_TRANSFER_INSTR:
    printf("SINGLE_DATA_TRANSFER Instruction\n");
    type->cond = getBits(fetched, 28, 31);
    type->I = getBits(fetched, 25, 25);
    type->P = getBits(fetched, 24, 24);
    type->U = getBits(fetched, 23, 23);
    type->L = getBits(fetched, 20, 20);
    type->rn = getBits(fetched, 16, 19);
    type->rd = getBits(fetched, 12, 15);
    type->offset = getBits(fetched, 0, 11);
    break;
  }


  return type;
}

