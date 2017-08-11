#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "cpu.h"

/* N flag of the CPSR register */
#define N_BIT 31

/* Instruction bits */
#define BRANCH_BIT 27                /* BRANCH instruction bit 27 */
#define SINGLE_DATA_TRANSFER_BIT 26  /* SINGLE_DATA_TRANSFER instruction bit 26 */ /* Exceeds 80 chars */
#define DATA_PROCESSING_BIT 25       /* DATA_PROCESSING instruction bit 25 */

/* Multiply */
#define MULTIPLY_BIT_START 4
#define MULTIPLY_BIT_END 7
#define MULTIPLY_BITS 9              /* bin(1001) = dec(9) for MULTIPLY */


/* GPIO access memory addresses */
/* Memory mapped IO -> Any access to these addresses turns on pin XX-XX */

#define GPIO_20_29 0x20200008
#define GPIO_10_19 0x20200004
#define GPIO_0_9 0x20200000
#define GPIO_SET 0x2020001C
#define GPIO_CLEAR 0x20200028

/* enum for instruction types */
typedef enum {
  DATA_PROCESSING = 0,
  MULTIPLY = 1,
  SINGLE_DATA_TRANSFER = 2,
  BRANCH = 3
} instruction_type;

/* enum for opcodes */
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

/* Returns the type of an instruction */
instruction_type get_instruction_type(uint32_t instruction);

/*Rn AND operand2*/
uint32_t and(instruction *instr, ARM11 *cpu);

/*Rn EOR operand2*/
uint32_t eor(instruction *instr, ARM11 *cpu);

/*Rn SUB operand2*/
uint32_t sub(instruction *instr, ARM11 *cpu);

/*operand2 - Rn*/
uint32_t rsb(instruction *instr, ARM11 *cpu);

/*Rn + operand2*/
uint32_t add(instruction *instr, ARM11 *cpu);

/*Same as and() but result not written*/
void tst(instruction *instr, ARM11 *cpu);

/*Same as eor() but result not written*/
void teq(instruction *instr, ARM11 *cpu);

/*Same as sub() but result not written*/
void cmp(instruction *instr, ARM11 *cpu);

/*Rn OR operand2*/
uint32_t orr(instruction *instr, ARM11 *cpu);

/*mov Rd,operand2 */
uint32_t mov(instruction *instr, ARM11 *cpu);

/****************************************************************/

void execute_multiply(instruction *instr, ARM11 *cpu);
void execute_single_data_transfer(instruction *instr, ARM11 *cpu);
void execute_data_processing(instruction *instr, ARM11 *cpu);
void execute_branch(instruction *instr, ARM11 *cpu);

/****************************************************************/

#endif
