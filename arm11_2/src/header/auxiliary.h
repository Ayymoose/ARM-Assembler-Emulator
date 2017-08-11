#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <stdint.h>
#include "processor.h"

/* Prints the contents of all registers */ 
void printRegisters(ARM11 *arm11);

/* Prints the contents of all non-zero memory locations */
void printMemory(ARM11 *arm11);

#endif
