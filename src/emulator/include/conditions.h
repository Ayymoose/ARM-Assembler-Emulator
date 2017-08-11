#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "cpu.h"

typedef enum {
  EQUAL = 0,
  NOT_EQUAL = 1,
  GREATER_OR_EQUAL = 10,
  LESS_THAN = 11,
  GREATER_THAN = 12,
  LESS_THAN_OR_EQUAL = 13,
  ALWAYS = 14,
} condition;

/* Conditions to be checked */

bool eq(ARM11 *cpu);

bool ne(ARM11 *cpu);

bool ge(ARM11 *cpu);

bool lt(ARM11 *cpu);

bool gt(ARM11 *cpu);

bool le(ARM11 *cpu);

bool al(ARM11 *cpu);

#endif


