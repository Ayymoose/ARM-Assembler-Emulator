#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include "processor.h"

typedef enum {
  AND = 0,
  EOR = 1,
  SUB = 2,
  RSB = 3,
  ADD = 4,
  TST = 8,
  TEQ = 9,
  CMP = 10,
  ORR = 12,
  MOV = 13,
} opcode;

/* Perform data processing on the instruction */
void dataProcessing(instruction *instr, ARM11 *arm11);

#endif 
