/*
 *
 * Purpose: This is the main file that contains the emulator
 * Usage: emulate path/to/binary
 *
 */

#include <stdio.h>

#include "header/processor.h"
#include "header/pipeline.h"
#include "header/auxiliary.h"
#include "header/loader.h"

#define EXPECTED_ARGUMENTS 1 /* Expected number of arguments passed in should be 1*/
#define ARGUMENT_ERROR -1 /* Error code for invalid number of arguments passed in */

int main(int argc, char **argv) {
  ARM11 *arm11;
  switch (argc) {
  case (EXPECTED_ARGUMENTS + 1):
    arm11 = initialiseProcessor();
    loadBinary(argv[1], arm11->memory);
    pipeline(arm11);
    printRegisters(arm11);
    printMemory(arm11);
    freeProcessor(arm11);
    break;
  default:
    fprintf(stderr,
        "Expecting only 1 argument which is the binary file but received %d.\n",
        argc - 1);
    exit(ARGUMENT_ERROR);
  }
  return EXIT_SUCCESS;
}
