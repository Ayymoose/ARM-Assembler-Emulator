#ifndef MEMORY_H
#define MEMORY_H

#include "cpu.h"
#include <stdint.h>

/* General bits */
#define BITS_IN_BYTE 8
#define BYTE_MASK 0x000000FF /* Mask for extracting bytes */

/* Prints the contents of all registers */ 
void dump_registers(ARM11 *cpu);

/* Prints the contents of all non-zero memory locations */
void dump_memory(ARM11 *cpu);

/* Gets the bits from a 32-bit word from startBit to endBit */
uint32_t get_bits(uint32_t instruction,uint32_t start_bit,uint32_t end_bit);

/* Creates a mask from startBit to endBit of a 32-bit integer */
uint32_t create_mask(uint32_t start_bit,uint32_t end_bit);

/* Reads a 32-bit word (4 bytes) from a memory address */
uint32_t read_word(uint8_t *memory);

/* Write a 32-bit word (4 bytes) to a memory address */
void write_word(uint8_t *memory, uint32_t value);

/* Changes the endianess of a 32-bit word (big->little , little->big */
uint32_t swap_endianness(uint32_t number);

/* Loads the binary file into memory and returns a 8-bit pointer to the memory */
bool load_binary(const char *file_name,uint8_t *memory);

#endif
