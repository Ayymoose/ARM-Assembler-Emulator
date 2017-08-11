#include <stdio.h>
#include "include/cpu.h"
#include "include/memory.h"

/* Usage: ./emulate binary_file */

int main(int argc, char **argv) {
  ARM11 *arm11;
  switch (argc) {
  case 2:
    arm11 = init_cpu();
    if (load_binary(argv[1], arm11->memory)) {
        pipeline_init(arm11);
        dump_registers(arm11);
        dump_memory(arm11);    
    }
    free_cpu(arm11);
    break;
  default:
    fprintf(stderr,"Expecting only 1 argument which is the binary file but received %d.\n",argc - 1);
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
