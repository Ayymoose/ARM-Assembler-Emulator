/*
 *
 * Purpose: The ARM11 processor
 *
 */

#include "header/processor.h"

/* Initialises the ARM11 processor  */
ARM11* initialiseProcessor() {

  /* Allocate memory for the processor */
  ARM11 *arm11 = (ARM11*) calloc(sizeof(ARM11), 1);

  /* Allocate 64KB of memory and clear */
  arm11->memory = (uint8_t*) calloc(MEMORY_SIZE, sizeof(uint32_t));

  /* Allocate memory for the CPSR register */
  arm11->cpsr = (CPSR*) calloc(sizeof(CPSR), 1);

  return arm11;
}

/* Frees the memory allocated by an ARM11 processor */
void freeProcessor(ARM11 *arm11) {

  /* Free the CPSR register first otherwise we will have a memory leak */
  free(arm11->cpsr);

  /* Now the 64KB of memory */
  free(arm11->memory);

  /* Finally the processor */
  free(arm11);

}
