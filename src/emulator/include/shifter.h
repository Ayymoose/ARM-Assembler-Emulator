#ifndef SHIFTER_H
#define SHIFTER_H

#include "cpu.h"
#include <stdint.h>

typedef enum {
    LSL = 0,
    LSR = 1,
    ARS = 2,
    RR = 3
} shift_type;

/* Shifter signatures */

uint32_t log_left_shift(uint32_t num, uint32_t shift, bool set_flags, ARM11 *cpu);

uint32_t log_right_shift(uint32_t num, uint32_t shift, bool set_flags, ARM11 *cpu);

uint32_t arith_right_shift(int32_t num, uint32_t shift, bool set_flags, ARM11 *cpu);

int32_t arith_left_shift(int32_t num, uint32_t shift);

uint32_t rotate_right(uint32_t num, uint32_t shift, bool set_flags, ARM11 *cpu);

uint32_t shifter_reg(uint32_t operand2, ARM11 *cpu, bool set_flags);

uint32_t shifter_imm(uint32_t operand2, ARM11 *cpu, bool set_flags);

#endif
