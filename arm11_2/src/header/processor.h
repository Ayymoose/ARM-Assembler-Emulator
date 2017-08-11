#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define GPR_REGISTERS 13  /* The number of General Purpose Registers */
#define MEMORY_SIZE 65536 /* 64KB = 64 * 2^10 bytes */
#define KILO_POWER 10     /* 2^10 is the number of bytes in a KB */

typedef uint32_t reg32; /* 32-bit registers */
typedef bool flag; /* Boolean flags */

/* The instruction struct */
/* DO NOT CHANGE THESE BIT FIELDS! */
typedef struct {
  reg32 rn; /*Register n (Source register) */
  reg32 rd; /*Register d (Destination register)*/
  reg32 rs; /*Rs?*/
  reg32 rm; /*Rm?*/
  flag I :1; /*Immediate flag*/
  flag P :1; /*Pre/Post indexing flag*/
  flag U :1; /*Up flag*/
  flag L :1; /*Load/Store flag*/
  flag S :1; /*Set-condition flag*/
  flag A :1; /*Accumulate flag*/
  uint32_t cond :4; /*4-bit condition code*/
  uint32_t opcode :4; /*4-bit opcode*/
  uint32_t operand2 :12; /*12-bit operand for operation*/
  int32_t offset :24; /*Offset 24-bits*//* CHANGED FROM UINT32_T to INT32_T*/
  uint32_t id;
} instruction;

/* CPSR flags struct */

typedef struct {
  flag N; /* Negative flag */
  flag Z; /* Zero flag */
  flag C; /* Carry flag */
  flag V; /* Overflow flag */
} CPSR;

/* ARM1176JZF-S processor struct */
typedef struct {
  reg32 gpr[GPR_REGISTERS]; /* Registers 0 to 11 are gpr (General Purpose Registers) */
  reg32 pc; /* Register 15 - The program counter */
  CPSR *cpsr; /* Register 16 - CPRS register */
  uint8_t *memory; /* Pointer to 64KB of memory */
} ARM11;

#endif

/* Initialises the ARM11 processor; allocating 64KB of memory and clearing all registers */
ARM11* initialiseProcessor();

/* Frees the memory allocated by an ARM11 processor */
void freeProcessor(ARM11 *arm11);
