#include <stdio.h>
#include <stdlib.h>

/* This can introduce a nasty exit bug if not wrapped in an if statement */
#define error(message,...) fprintf(stderr,"[ERROR] (%s:%d) " message "\n", __FILE__, __LINE__,__VA_ARGS__); exit(EXIT_FAILURE)

#define warning(message,...) fprintf(stderr,"[WARNING] (%s:%d) " message "\n", __FILE__, __LINE__,__VA_ARGS__)

/* Taken from https://stackoverflow.com/questions/1898153/how-to-determine-if-memory-is-aligned-testing-for-alignment-not-aligning */
//#define is_aligned(POINTER, BYTE_COUNT) \
    (((uintptr_t)(const void *)(POINTER)) % (BYTE_COUNT) == 0)
