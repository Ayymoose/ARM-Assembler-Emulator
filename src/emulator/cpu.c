#include "include/cpu.h"
#include "include/memory.h"
#include "include/conditions.h"
#include "include/instruction.h"
#include "include/debug.h"

/* Function pointer array for conditions - Triggers seg fault on non-existing condition */
static bool (*f_check_condition[15])(ARM11 *cpu) = {eq,ne,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,ge,lt,gt,le,al};
static void (*f_execute[4])(instruction *decoded, ARM11 *cpu) = {execute_data_processing,execute_multiply,execute_single_data_transfer,execute_branch};
static void (*f_decode[4])(uint32_t fetched,instruction *decoded) = {decode_data_processing,decode_multiply,decode_single_data_transfer,decode_branch};

/* Initialises the ARM11 processor  */
ARM11* init_cpu() {

  /* Allocate memory for the processor */
  ARM11 *cpu = malloc(sizeof(ARM11));
  if (!cpu) {
    error("malloc() fail %p",(void*)cpu);
  }

  /* Allocate 64KB of memory and clear */
  cpu->memory = calloc(MEMORY_SIZE, sizeof(uint32_t));
  if (!cpu->memory) {
    error("calloc() fail %p",cpu->memory);
  }
  /* Allocate memory for the CPSR register */
  /* MUST be 0 on initialisation */
  cpu->cpsr = calloc(1,sizeof(CPSR));
  if (!cpu->cpsr) {
    error("calloc() fail %p",(void*)cpu->cpsr);
  }
  return cpu;
}

/* Frees the memory allocated by an ARM11 processor */
void free_cpu(ARM11 *cpu) {
  /* Free the CPSR register first otherwise we will have a memory leak */
  free(cpu->cpsr);
  /* Now the 64KB of memory */
  free(cpu->memory);
  /* Finally the processor */
  free(cpu);
}

/* The three-stage pipeline */
void pipeline_init(ARM11 *cpu) {
       
  uint32_t fetched = UNDEFINED; 
  instruction *decoded = calloc(1,sizeof(instruction));
  if (!decoded) {
    error("calloc() fail %p",(void*)decoded);
  }
  decoded->id = UNDEFINED;

  //Keep filling the pipeline
  for (;;) {

    // If we have a instruction that is decoded
    if (decoded->id != UNDEFINED) {

      // If we've reached the halt instruction
      if (decoded->id == 0) {
        // And there is one decoded instruction left to execute
        if (decoded) {
          // Execute it
          execute(decoded, cpu);
        }
        // Then break
        break;
      }

      // Execute the decoded instruction
      bool is_executed = execute(decoded, cpu);

      // If the instruction is a branch that has been executed 
      if (get_instruction_type(decoded->id) == BRANCH && is_executed) {
        // Do nothing
        fetched = decoded->id = UNDEFINED;
      }
    }
    // If we have a fetched instruction then decode it
    if (fetched != UNDEFINED) {
        decode(fetched,decoded);
    }

    // Fetch a 32-bit instruction
    fetched = fetch(cpu);
    
  }
    free(decoded);
}

/* Fetches a 32-bit instruction from memory */
uint32_t fetch(ARM11 *cpu) {
  /* Since memory is stored as bytes; read 4 bytes*/
  uint32_t next_instruction = read_word(cpu->memory + cpu->pc);
  cpu->pc += sizeof(uint32_t);
  return next_instruction;
}

void decode_branch(uint32_t fetched,instruction *decoded) {
    decoded->offset = get_bits(fetched, OFFSET_BIT_START_B, OFFSET_BIT_END_B);
}

void decode_multiply(uint32_t fetched,instruction *decoded) {
    decoded->A = get_bits(fetched, A_BIT, A_BIT);
    decoded->S = get_bits(fetched, S_BIT, S_BIT);
    decoded->rd = get_bits(fetched, RD_BIT_START_M, RD_BIT_END_M);
    decoded->rn = get_bits(fetched, RN_BIT_START_M, RN_BIT_END_M);
    decoded->rs = get_bits(fetched, RS_BIT_START_M, RS_BIT_END_M);
    decoded->rm = get_bits(fetched, RM_BIT_START_M, RM_BIT_END_M);
}

void decode_data_processing(uint32_t fetched,instruction *decoded) {
    decoded->I = get_bits(fetched, I_BIT, I_BIT);
    decoded->S = get_bits(fetched, S_BIT, S_BIT);
    decoded->opcode = get_bits(fetched, OPCODE_BIT_START, OPCODE_BIT_END);
    decoded->rn = get_bits(fetched, RN_BIT_START_DP, RN_BIT_END_DP);
    decoded->rd = get_bits(fetched, RD_BIT_START_DP, RD_BIT_END_DP);
    decoded->operand2 = get_bits(fetched, OPERAND2_BIT_START, OPERAND2_BIT_END);
}

void decode_single_data_transfer(uint32_t fetched,instruction *decoded) {
    decoded->I = get_bits(fetched, I_BIT, I_BIT);
    decoded->P = get_bits(fetched, P_BIT, P_BIT);
    decoded->U = get_bits(fetched, U_BIT, U_BIT);
    decoded->L = get_bits(fetched, L_BIT, L_BIT);
    decoded->rn = get_bits(fetched, RN_BIT_START_SDT, RN_BIT_END_SDT);
    decoded->rd = get_bits(fetched, RD_BIT_START_SDT, RD_BIT_END_SDT);
    decoded->offset = get_bits(fetched, OFFSET_BIT_START_SDT, OFFSET_BIT_END_SDT);
}

/* Decodes a 32-bit instruction */
void decode(uint32_t fetched, instruction *decoded) {
  decoded->id = fetched;
  decoded->cond = get_bits(fetched, COND_BIT_START, COND_BIT_END);
  f_decode[get_instruction_type(fetched)](fetched,decoded);
}

/* Executes an instruction */
bool execute(instruction *decoded, ARM11 *cpu) {
  uint32_t condition = decoded->cond;
  if (check_condition(condition, cpu)) {
    f_execute[get_instruction_type(decoded->id)](decoded,cpu);
    return true;
  }
  return false;
}

/* Checks the condition */
bool check_condition(uint32_t cond, ARM11 *cpu) {
    return f_check_condition[cond](cpu);
}
