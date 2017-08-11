/*
 *  Purpose: Boolean instructions of cond
 */

#include "header/processor.h"

bool eq(ARM11 *arm11) {
  return arm11->cpsr->Z == 1;
}

bool ne(ARM11 *arm11) {
  return arm11->cpsr->Z == 0;
}

bool ge(ARM11 *arm11) {
  return arm11->cpsr->N == arm11->cpsr->V;
}

bool lt(ARM11 *arm11) {
  return arm11->cpsr->Z != arm11->cpsr->V;
}

bool gt(ARM11 *arm11) {
  return arm11->cpsr->Z == 0 && (arm11->cpsr->N == arm11->cpsr->V);
}

bool le(ARM11 *arm11) {
  return arm11->cpsr->Z == 1 && (arm11->cpsr->N != arm11->cpsr->V);
}

bool al(ARM11 *arm11) {
  return true;
}
