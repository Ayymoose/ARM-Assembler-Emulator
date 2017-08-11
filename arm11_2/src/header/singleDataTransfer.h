#ifndef SINGLE_DATA_TRANSFER_H
#define SINGLE_DATA_TRANSFER_H

#include "processor.h"

/* Single Data Transfer signatures */

void ldr(instruction *instr, ARM11 *arm);

void str(instruction *instr, ARM11 *arm);

void singleDataTransfer(instruction *instr, ARM11 *registers);

#endif
