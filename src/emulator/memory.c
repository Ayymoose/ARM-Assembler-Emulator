#include <stdio.h>
#include "include/cpu.h"
#include "include/memory.h"
#include "include/debug.h"
#include <assert.h>

/* Prints the contents of all registers */
void dump_registers(ARM11 *arm11) {
  printf("Registers:\n");

  /* General Purpose Registers */
  for (int i=0; i<GPR_REGISTERS; i++) {
    printf("$%-3d: %10d (0x%08x)\n",i,arm11->gpr[i],arm11->gpr[i]);
  }

  /* Program Counter */
  printf("PC  :   %8d (0x%08x)\n",arm11->pc,arm11->pc);

  /* Display the CPSR register as a combination of shifted flags */
  uint32_t cpsr
      = (uint32_t)(arm11->cpsr->N << 31)
      | (uint32_t)(arm11->cpsr->Z << 30)
      | (uint32_t)(arm11->cpsr->C << 29)
      | (uint32_t)(arm11->cpsr->V << 28);

  printf("CPSR: %10d (0x%08x)\n",cpsr,cpsr);
}

/* Prints the contents of all non-zero memory locations */
void dump_memory(ARM11 *arm11) {
  printf("Non-zero memory:\n");
  for (int i=0; i<MEMORY_SIZE; i+=sizeof(uint32_t)) {
    if (read_word(arm11->memory+i) != 0) {
      printf("0x%08x: 0x%08x\n",
      (uint32_t)(i*sizeof(uint8_t)),
       swap_endianness(read_word(arm11->memory+i)));
    }
  }
}


/* Loads the binary file into memory */
bool load_binary(const char *file_name, uint8_t *memory) {
  FILE* file;
  /* Catch the failed file opening error */
  if ((file = fopen(file_name, "r")) == NULL) {
    fprintf(stderr,"Unable to open file '%s'\n",file_name); 
    return false;
  } else {
    /* Read one element of size MEMORY_SIZE into our buffer */
    size_t bytes_read = 0;
    size_t total_bytes_read = 0;

    /* The file read loop */
    while (total_bytes_read < MEMORY_SIZE) {
      bytes_read = fread(memory, 1, MEMORY_SIZE, file);
      if (bytes_read == 0) {
        break;
      }
      total_bytes_read += bytes_read;
    }

    /* If we tried to read a file greater than 64KB which is unsupported */
    if (total_bytes_read >= MEMORY_SIZE) {
      fprintf(stderr,"File sizes greater than %uKB are not supported.\n",MEMORY_SIZE >> KILO_POWER);
      fclose(file);
      return false;
    }
  }
  fclose(file);
  return true;
}


/* Creates a mask from start_bit to end_bit of a 32-bit integer */
/* 00000000 00000000 00000000 00000000*/
/* 00000000 00000000 00000000 00000010*/

uint32_t create_mask(uint32_t start_bit,uint32_t end_bit) {
  // 0 <= start_bit, end_bit <= 31
  // 2^E - 2^(S-1)
  // 2^n = 1 << n
  assert(start_bit >=0 && start_bit <= 31 && end_bit >=0 && end_bit <=31);
  return (end_bit-start_bit == 31 ? 0xFFFFFFFF : ((1 << ((end_bit-start_bit)+1))-1) << start_bit);
}

/* Gets the bits from a 32-bit word from startBit to endBit */
uint32_t get_bits(uint32_t word, uint32_t start_bit,uint32_t end_bit) {
  return (word & create_mask(start_bit, end_bit)) >> start_bit;
}

/* Reads a 32-bit word (4 bytes) from a memory address */
uint32_t read_word(uint8_t *memory) {
  return (memory[0]
      | (memory[1] << (BITS_IN_BYTE))
      | (memory[2] << (BITS_IN_BYTE * 2))
      | (memory[3] << (BITS_IN_BYTE * 3)));
}

/* Write a 32-bit word (4 bytes) to a memory address */
void write_word(uint8_t *memory, uint32_t word) {
  memory[0] = word & BYTE_MASK;
  memory[1] = (word >> BITS_IN_BYTE) & BYTE_MASK;
  memory[2] = (word >> (BITS_IN_BYTE * 2)) & BYTE_MASK;
  memory[3] = (word >> (BITS_IN_BYTE * 3)) & BYTE_MASK;
}

/* Changes the endianess of a 32-bit word (big->little , little->big */
uint32_t swap_endianness(uint32_t word) {
  return ((word & (BYTE_MASK << (BITS_IN_BYTE * 3))) >> (BITS_IN_BYTE * 3))
      | ((word & (BYTE_MASK << (BITS_IN_BYTE * 2))) >> BITS_IN_BYTE)
      | ((word & (BYTE_MASK << BITS_IN_BYTE)) << BITS_IN_BYTE)
      | ((word & BYTE_MASK) << (BITS_IN_BYTE * 3));
}
