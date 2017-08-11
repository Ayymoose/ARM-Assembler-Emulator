#ifndef PIPELINE_H
#define PIPELINE_H

#include <stdint.h>
#include "processor.h"

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

/* Fetches a 32-bit instruction from memory */
uint32_t fetch(ARM11 *arm);

/* Decodes a 32-bit instruction */
instruction* decode(uint32_t fetched);

/* Executes a 32-bit instruction */
bool execute(instruction *decoded, ARM11 *arm);

/* Checks the condition of ... */
bool checkCondition(uint32_t cond, ARM11 *arm);

/* The three stage pipeline */
void pipeline(ARM11 *arm);

#endif
