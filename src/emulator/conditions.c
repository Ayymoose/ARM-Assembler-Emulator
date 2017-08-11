#include "include/cpu.h"

bool eq(ARM11 *cpu) {
  return cpu->cpsr->Z == 1;
}

bool ne(ARM11 *cpu) {
  return cpu->cpsr->Z == 0;
}

bool ge(ARM11 *cpu) {
  return cpu->cpsr->N == cpu->cpsr->V;
}

bool lt(ARM11 *cpu) {
  return cpu->cpsr->Z != cpu->cpsr->V;
}

bool gt(ARM11 *cpu) {
  return cpu->cpsr->Z == 0 && (cpu->cpsr->N == cpu->cpsr->V);
}

bool le(ARM11 *cpu) {
  return cpu->cpsr->Z == 1 && (cpu->cpsr->N != cpu->cpsr->V);
}

bool al(ARM11 *cpu) {
  return true;
}
