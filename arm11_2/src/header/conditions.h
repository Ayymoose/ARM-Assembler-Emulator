#ifndef CONDITIONS_H
#define CONDITIONS_H

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

bool eq(ARM11 *arm11);

bool ne(ARM11 *arm11);

bool ge(ARM11 *arm11);

bool lt(ARM11 *arm11);

bool gt(ARM11 *arm11);

bool le(ARM11 *arm11);

bool al(ARM11 *arm11);

#endif


