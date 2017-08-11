#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define GPR_REGISTERS 13  /* The number of General Purpose Registers */
#define MEMORY_SIZE 65536 /* 64KB = 64 * 2^10 bytes */
#define KILO_POWER 10     /* 2^10 is the number of bytes in a KB */
#define PC 15             /* Program counter is register 15 */

/* Hack - We interpret this value as an uninitialised instruction */
#define UNDEFINED 0x7FFFFFFF 

//cond
#define COND_BIT_START 28
#define COND_BIT_END 31
//offset
#define OFFSET_BIT_START 0
#define OFFSET_BIT_END 23
//Flags
//A
#define A_BIT 21
//S
#define S_BIT 20
//I
#define I_BIT 25
//P
#define P_BIT 24
//U
#define U_BIT 23
//L
#define L_BIT 20

//Registers
//Rd - Multiply
#define RD_BIT_START_M 16
#define RD_BIT_END_M 19
//Rd - Single Data Transfer
#define RD_BIT_START_SDT 12
#define RD_BIT_END_SDT 15
//Rd - Data Processing
#define RD_BIT_START_DP 12
#define RD_BIT_END_DP 15
//Rn - Multiply
#define RN_BIT_START_M 12
#define RN_BIT_END_M 15
//Rn - Single Data Transfer
#define RN_BIT_START_SDT 16
#define RN_BIT_END_SDT 19
//Rn - Data Processing
#define RN_BIT_START_DP 16
#define RN_BIT_END_DP 19
//Rs - Multiply
#define RS_BIT_START_M 8
#define RS_BIT_END_M 11
//Rm - Multiply
#define RM_BIT_START_M 0
#define RM_BIT_END_M 3
//
//opcode
#define OPCODE_BIT_START 21
#define OPCODE_BIT_END 24
//offset - Branch
#define OFFSET_BIT_START_B 0
#define OFFSET_BIT_END_B 23
//offset - Single Data Transfer
#define OFFSET_BIT_START_SDT 0
#define OFFSET_BIT_END_SDT 11
//operand2
#define OPERAND2_BIT_START 0
#define OPERAND2_BIT_END 11

typedef uint32_t reg32; /* 32-bit registers NUMBERS (not values) */
typedef bool flag; /* Boolean flags */

/* The instruction struct */
/* DO NOT CHANGE THESE BIT FIELDS! */
typedef struct {
  reg32 rn;              /* Register n (Source register) */
  reg32 rd;              /* Register d (Destination register)   */
  reg32 rs;              /* Rs? */
  reg32 rm;              /* Rm? */
  flag I :1;             /* Immediate flag  */
  flag P :1;             /* Pre/Post indexing flag  */
  flag U :1;             /* Up flag */
  flag L :1;             /* Load/Store flag */
  flag S :1;             /* Set-condition flag  */
  flag A :1;             /* Accumulate flag */
  uint32_t cond :4;      /* 4-bit condition code    */
  uint32_t opcode :4;    /* 4-bit opcode    */
  uint32_t operand2 :12; /* 12-bit operand for operation    */
  int32_t offset :24;    /* Offset 24-bits*//* CHANGED FROM UINT32_T to INT32_T */
  uint32_t id;
} instruction;

/* CPSR register flags struct */

typedef struct {
  flag N;   /* Negative flag */
  flag Z;   /* Zero flag */
  flag C;   /* Carry flag */
  flag V;   /* Overflow flag */
} CPSR;

/* ARM1176JZF-S processor struct */
typedef struct {
  reg32 gpr[GPR_REGISTERS]; /* Registers 0 to 11 are GPR (General Purpose Registers) */
  reg32 pc;                 /* Register 15 - The program counter */
  CPSR *cpsr;               /* Register 16 - CPRS register */
  uint8_t *memory;          /* Pointer to 64KB of memory */
} ARM11;


/* Initialises the ARM11 processor; allocating 64KB of memory and clearing all registers */
ARM11* init_cpu();

/* Frees the memory allocated by an ARM11 processor */
void free_cpu(ARM11 *cpu);

/* Fetches a 32-bit instruction from memory */
uint32_t fetch(ARM11 *cpu);

/* Decodes a 32-bit instruction */
void decode(uint32_t fetched, instruction *decoded);

/* Executes a 32-bit instruction */
bool execute(instruction *instr, ARM11 *cpu);

/* Checks the condition of ... */
bool check_condition(uint32_t cond, ARM11 *cpu);

/* Start the three stage pipeline */
void pipeline_init(ARM11 *cpu);


void decode_data_processing(uint32_t fetched,instruction *decoded);
void decode_multiply(uint32_t fetched,instruction *decoded);
void decode_single_data_transfer(uint32_t fetched,instruction *decoded);
void decode_branch(uint32_t fetched,instruction *decoded);

#endif
