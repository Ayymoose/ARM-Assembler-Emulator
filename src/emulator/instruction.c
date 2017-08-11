#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "include/cpu.h"
#include "include/instruction.h"
#include "include/shifter.h"
#include "include/memory.h"
#include "include/debug.h"

static uint32_t (*f_data_processing[14])(instruction *instr, ARM11 *cpu) = {and,eor,sub,rsb,add,NULL,NULL,NULL,NULL,NULL,NULL,NULL,orr,mov};
static void (*f_test[3])(instruction *instr, ARM11 *cpu) = {tst,teq,cmp};


/* Returns the type of an instruction depending on the bits set or not set */
instruction_type get_instruction_type(uint32_t instruction_word) {

  uint8_t branch = get_bits(instruction_word, BRANCH_BIT, BRANCH_BIT);
  uint8_t single_data_transfer = get_bits(instruction_word, SINGLE_DATA_TRANSFER_BIT, SINGLE_DATA_TRANSFER_BIT);
  uint8_t data_processing = get_bits(instruction_word, DATA_PROCESSING_BIT,DATA_PROCESSING_BIT);
  uint8_t multiply = get_bits(instruction_word, MULTIPLY_BIT_START,MULTIPLY_BIT_END);

  /* Certain bits can only be set depending on some flags
   * So we check for that
   */

  if (branch == 1) {
    return BRANCH;
  } else if (single_data_transfer == 1) {
    return SINGLE_DATA_TRANSFER;
  } else if (data_processing == 1) {
    return DATA_PROCESSING;
  } else {
    if (multiply == MULTIPLY_BITS) {
      return MULTIPLY;
    } else {
      return DATA_PROCESSING;
    }
  }
}

/* Check if operand2 is register or constant*/
static bool check_op_reg(instruction *instr) {
  return (instr->I == 0);
}

/* Check if CPSR flags need to be set */
static bool check_set_flags(instruction *instr) {
  return instr->S == 1;
}

/* Rn AND operand2 */
uint32_t and(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = cpu->gpr[instr->rn] & shifter_reg(instr->operand2, cpu, check_set_flags(instr));
  } else {
    result = cpu->gpr[instr->rn] & shifter_imm(instr->operand2, cpu, check_set_flags(instr));
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->Z = (result == 0);
  }
  return result;
}

/* Rn EOR(XOR) operand2 */
uint32_t eor(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = cpu->gpr[instr->rn] ^ shifter_reg(instr->operand2, cpu, check_set_flags(instr));
  } else {
    result = cpu->gpr[instr->rn] ^ shifter_imm(instr->operand2, cpu, check_set_flags(instr));
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->Z = (result == 0);
  }
  return result;
}

/* Rn SUB operand2 */
uint32_t sub(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = cpu->gpr[instr->rn] - shifter_reg(instr->operand2, cpu, false);
  } else {
    result = cpu->gpr[instr->rn] - shifter_imm(instr->operand2, cpu, false);
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->C = (result <= create_mask(0, 31));
    cpu->cpsr->Z = (result == 0);
  }
  return result;
}

/* operand2 - Rn */
uint32_t rsb(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = shifter_reg(instr->operand2, cpu, false) - cpu->gpr[instr->rn];
  } else {
    result = shifter_imm(instr->operand2, cpu, false) - cpu->gpr[instr->rn];
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->C = (result <= create_mask(0, 31));
    cpu->cpsr->Z = (result == 0);
  }
  return result;
}

/* Rn + operand2 */
uint32_t add(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = cpu->gpr[instr->rn] + shifter_reg(instr->operand2, cpu, false);
  } else {
    result = cpu->gpr[instr->rn] + shifter_imm(instr->operand2, cpu, false);
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->C = (result > create_mask(0, 31));
    cpu->cpsr->Z = (result == 0);
  }
  return result;
}

/* Same as and() but result not written */
void tst(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = cpu->gpr[instr->rn] & shifter_reg(instr->operand2, cpu, check_set_flags(instr));
  } else {
    result = cpu->gpr[instr->rn] & shifter_imm(instr->operand2, cpu, check_set_flags(instr));
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->Z = (result == 0);
  }
}

/* Same as eor() but result not written */
void teq(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = cpu->gpr[instr->rn] ^ shifter_reg(instr->operand2, cpu, check_set_flags(instr));
  } else {
    result = cpu->gpr[instr->rn] ^ shifter_imm(instr->operand2, cpu, check_set_flags(instr));
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->Z = (result == 0);
  }
}

/* Same as sub() but result not written */
void cmp(instruction *instr, ARM11 *cpu) {
  int64_t result; /* UINT 64 !!!*/ /* Changed to int64_t*/
  if (check_op_reg(instr)) {
    result = cpu->gpr[instr->rn] - shifter_reg(instr->operand2, cpu, false);
  } else {
    result = cpu->gpr[instr->rn] - shifter_imm(instr->operand2, cpu, false);
  }
  uint32_t operand2 = (check_op_reg(instr) ? shifter_reg(instr->operand2, cpu, false) : shifter_imm(instr->operand2, cpu, false));
  cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
  cpu->cpsr->C = !(operand2 > cpu->gpr[instr->rn]);
  cpu->cpsr->Z = (result == 0);
}

/* Rn OR operand2 */
uint32_t orr(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = cpu->gpr[instr->rn] | shifter_reg(instr->operand2, cpu, check_set_flags(instr));
  } else {
    result = cpu->gpr[instr->rn] | shifter_imm(instr->operand2, cpu, check_set_flags(instr));
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->Z = (result == 0);
  }
  return result;
}

/* mov Rd,operand2 */
uint32_t mov(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (check_op_reg(instr)) {
    result = shifter_reg(instr->operand2, cpu, check_set_flags(instr));
  } else {
    result = shifter_imm(instr->operand2, cpu, check_set_flags(instr));
  }
  if (check_set_flags(instr)) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->Z = (result == 0);
  }
  return result;
}

/* Multiply. */
void execute_multiply(instruction *instr, ARM11 *cpu) {
  uint32_t result;
  if (instr->A == 0) {
    /* Multiply without accumulate */
    result = cpu->gpr[instr->rm] * cpu->gpr[instr->rs];
  } else {
    /* Multiply with accumulate */
    result = (cpu->gpr[instr->rm] * cpu->gpr[instr->rs]) + cpu->gpr[instr->rn];
  }
  cpu->gpr[instr->rd] = result;
  if (instr->S == 1) {
    cpu->cpsr->N = get_bits(result, N_BIT, N_BIT);
    cpu->cpsr->Z = (result == 0);
  }
}

/* Performs a data processing instruction */
void execute_data_processing(instruction *instr, ARM11 *cpu) {
    if (instr->opcode >= TST && instr->opcode <= CMP) {
       f_test[instr->opcode % 8](instr,cpu);
    } else {
       cpu->gpr[instr->rd] = f_data_processing[instr->opcode](instr,cpu);
    }
}

/* Check if we accessed a GPIO pin */
static void gpio_memory_access(ARM11 *cpu,instruction *instr, uint32_t address) {
    switch (address) {
        case GPIO_0_9: printf("One GPIO pin from 0 to 9 has been accessed\n");  break;
        case GPIO_10_19: printf("One GPIO pin from 10 to 19 has been accessed\n"); break;
        case GPIO_20_29: printf("One GPIO pin from 20 to 29 has been accessed\n"); break;
        case GPIO_SET: printf("PIN ON\n"); break;
        case GPIO_CLEAR: printf("PIN OFF\n"); break;
        default: warning("Memory access within GPIO memory mapped IO: %u",address); break;
    }
    if (instr->L == 1) {
        cpu->gpr[instr->rd] = address;
    }
}

/* Execute a load or store instruction */
static void ldr_or_str(ARM11 *cpu, instruction *instr, uint32_t address) {
    if (address < MEMORY_SIZE) {
        // Is it a load instruction?
        if (instr->L == 1) {
           cpu->gpr[instr->rd] = read_word(cpu->memory + address);
        } else {
           // Otherwise it's a store instruction
           write_word(cpu->memory + address, cpu->gpr[instr->rd]);
        }
    } else if (address >= GPIO_0_9 && address <= GPIO_CLEAR) {
        gpio_memory_access(cpu,instr,address);
    } else {
        printf("Error: Out of bounds memory access at address 0x%08x\n",address);
    }
}

/* Pre or post indexing */
static uint32_t pre_or_post(ARM11 *cpu, instruction *instr, int32_t offset) {
    uint32_t address;
    if (instr->U == 1) {
        address = (instr->rn == PC ? (cpu->pc + offset) : (cpu->gpr[instr->rn] + offset));
    } else {
        address = (instr->rn == PC ? (cpu->pc - offset) : (cpu->gpr[instr->rn] - offset));
    }
    if (instr->P == 0) {
        if (instr->U == 1) {
            cpu->gpr[instr->rn] += offset;
        } else {
            cpu->gpr[instr->rn] -= offset;
        }
    }
    return address;
}

/* Single data transfer instruction */
void execute_single_data_transfer(instruction *instr, ARM11 *cpu) {
  /* If the immediate flag is set then the offset is a shifted register
    otherwise if it is NOT set then it is interpreted as an unsigned 12-bit immediate offset
  */
  uint32_t address = cpu->gpr[instr->rn];
  int32_t offset;
  if (instr->I == 1) {
    offset = shifter_reg(instr->offset, cpu, false);
  } else {
    offset = instr->offset;
  }
  /* If pre-indexing is set, offset is added/subtracted to the base register
     before transferring the data 
  */
  if (instr->P == 1) {
     /* For the purpose of this exercise (according to the spec) 
        Pre-indexing does NOT change the contents of the base register
     */
    address = pre_or_post(cpu,instr,offset);
    ldr_or_str(cpu,instr,address);
  } else {
    /* Post-indexing is set: offset is added/subtracted after transferring 
       the data
    */    
    ldr_or_str(cpu,instr,address);
    address = pre_or_post(cpu,instr,offset);
  }
}

/* Performs a branch instruction */
void execute_branch(instruction *instr, ARM11 *cpu)	{
	cpu->pc += arith_left_shift(instr->offset, 2);
}

