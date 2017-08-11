#ifndef INSTRUCTION_H
#define INSTRUCTION_H

/* Here lies the strange bug; we can't remove INSTR without some error! */
typedef enum {
  DATA_PROCESSING_INSTR,
  MULTIPLY_INSTR,
  SINGLE_DATA_TRANSFER_INSTR,
  BRANCH_INSTR
} instructionType;

/* Returns the type of an instruction */
instructionType getType(uint32_t instructionWord);

/* N flag of the CPSR register */
#define N_BIT 31

/*Rn AND operand2*/
uint32_t and(instruction *instr, ARM11 *arm11);

/*Rn EOR operand2*/
uint32_t eor(instruction *instr, ARM11 *arm11);

/*Rn SUB operand2*/
uint32_t sub(instruction *instr, ARM11 *arm11);

/*operand2 - Rn*/
uint32_t rsb(instruction *instr, ARM11 *arm11);

/*Rn + operand2*/
uint32_t add(instruction *instr, ARM11 *arm11);

/*Same as and() but result not written*/
void tst(instruction *instr, ARM11 *arm11);

/*Same as eor() but result not written*/
void teq(instruction *instr, ARM11 *arm11);

/*Same as sub() but result not written*/
void cmp(instruction *instr, ARM11 *arm11);

/*Rn OR operand2*/
uint32_t orr(instruction *instr, ARM11 *arm11);

/*mov Rd,operand2 */
uint32_t mov(instruction *instr, ARM11 *arm11);

#endif
