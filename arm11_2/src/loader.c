/*
 **
 ** Purpose: Loading binary files and initialising data.
 **
 */

#include <stdio.h>

#include "header/loader.h"
#include "header/bitmanipulation.h"
#include "header/processor.h"
#include "header/instruction.h"

#define FILE_ERROR -1  /* Status code for file related operations */

/* Returns the type of an instruction depending on the bits set or not set */
instructionType getType(uint32_t instructionWord) {

  uint8_t branch = getBits(instructionWord, BRANCH_BIT, BRANCH_BIT);
  uint8_t singleDataTransfer = getBits(instructionWord,
  SINGLE_DATA_TRANSFER_BIT, SINGLE_DATA_TRANSFER_BIT);
  uint8_t dataProcessing = getBits(instructionWord, DATA_PROCESSING_BIT,
  DATA_PROCESSING_BIT);
  uint8_t multiply = getBits(instructionWord, MULTIPLY_BIT_START,
  MULTIPLY_BIT_END);

  /* Certain bits can only be set depending on some flags
   * So we check for that
   */

  if (branch == 1) {
    return BRANCH_INSTR;
  } else if (singleDataTransfer == 1) {
    return SINGLE_DATA_TRANSFER_INSTR;
  } else if (dataProcessing == 1) {
    return DATA_PROCESSING_INSTR;
  } else {
    if (multiply == MULTIPLY_BITS) {
      return MULTIPLY_INSTR;
    } else {
      return DATA_PROCESSING_INSTR;
    }
  }
}


/* Loads the binary file into memory */
void loadBinary(const char *fileName, uint8_t *memory) {

  FILE* file;

  /* Catch the failed file opening error */
  if ((file = fopen(fileName, "r")) == NULL) {
    perror(fileName);
    exit(FILE_ERROR);
  } else {

    /* Read one element of size MEMORY_SIZE into our buffer */
    size_t bytesRead = 0;
    size_t totalBytesRead = 0;

    /* The file read loop */
    while (totalBytesRead < MEMORY_SIZE) {
      bytesRead = fread(memory, 1, MEMORY_SIZE, file);
      if (bytesRead == 0) {
        break;
      }
      totalBytesRead += bytesRead;
    }

    /* If we tried to read a file greater than 64KB which is unsupported */
    if (totalBytesRead >= MEMORY_SIZE) {
      fprintf(stderr, "File sizes greater than %uKB are not supported.\n",
      MEMORY_SIZE >> KILO_POWER);
      exit(FILE_ERROR);
    } else {
      fclose(file);
    }
  }
}
