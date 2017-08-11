#include <stdbool.h>
#include "include/shifter.h"
#include "include/memory.h"

/* Performs left shift on number by specified amount */
uint32_t log_left_shift(uint32_t num, uint32_t shift, bool set_flags, ARM11 *cpu) {
  if (set_flags) {
    /* Get the discarded bit */
    cpu->cpsr->C = get_bits(num, 31 - shift, 31 - shift);
  }
  return num << shift;
}

/* Performs right shift on number by specified amount */
uint32_t log_right_shift(uint32_t num, uint32_t shift, bool set_flags, ARM11 *cpu) {
  if (set_flags) {
    /* Get the discarded bit */
    cpu->cpsr->C = get_bits(num, shift - 1, shift - 1);
  }
  return num >> shift;
}

/* Performs right shift on number by specified amount preserving the sign */

uint32_t arith_right_shift(int32_t num, uint32_t shift, bool set_flags, ARM11 *cpu) {
  return log_right_shift(num,shift,set_flags,cpu);
}

/* Performs left shift on number by specified amount and preserves the sign */
int32_t arith_left_shift(int32_t num, uint32_t shift) {
  return num << shift;
}

/* Performs right shift on number by specified amount,
 * least significant bits rotated round to most significant positions*/
uint32_t rotate_right(uint32_t num, uint32_t shift, bool set_flags, ARM11 *cpu) {
  if (shift == 0) {
    return num;
  }
  if (set_flags) {
    cpu->cpsr->C = get_bits(num, shift - 1, shift - 1);
  }
  uint32_t end_bits = get_bits(num, 0, shift - 1);
  end_bits <<= (32 - shift); /* 32 ? */
  return end_bits | log_right_shift(num, shift, set_flags, cpu);
}

/* Shifts, treating operand2 as register */
uint32_t shifter_reg(uint32_t operand2, ARM11 *cpu, bool set_flags) {
  reg32 rm = get_bits(operand2, 0, 3);
  uint32_t shift_amount;
  shift_type shift_type;
  if (get_bits(operand2, 4, 4) == 0) {
    /* Shift by a constant amount */
    shift_amount = get_bits(operand2, 7, 11);
    shift_type = get_bits(operand2, 5, 6);
  } else {
    /* Shift by a register */
    shift_amount = get_bits(cpu->gpr[get_bits(operand2, 8, 11)], 0,7);
    shift_type = get_bits(operand2, 5, 6);
  }
    switch (shift_type) {
    case LSL:
      return log_left_shift(cpu->gpr[rm], shift_amount, set_flags, cpu);
    case LSR:
      return log_right_shift(cpu->gpr[rm], shift_amount, set_flags, cpu);
    case ARS:
      return arith_right_shift(cpu->gpr[rm], shift_amount, set_flags,cpu);
    case RR:
      return rotate_right(cpu->gpr[rm], shift_amount, set_flags, cpu);
    default:
      return operand2;
    }
}

/* Shifts, treating operand2 as immediate constant */
uint32_t shifter_imm(uint32_t operand2, ARM11 *cpu, bool set_flags) {
  uint32_t val = get_bits(operand2, 0, 7);
  uint32_t rotate_amount = get_bits(operand2, 8, 11);
  return rotate_right(val, 2 * rotate_amount, set_flags, cpu);
}
