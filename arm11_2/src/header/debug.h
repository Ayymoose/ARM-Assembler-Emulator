#ifndef DEBUG_H
#define DEBUG_H

/*
**
** Purpose: Contaings the prototypes for all debugging functions
**
*/

#include <stdint.h>

#include "loader.h"
#include "pipeline.h"
#include "processor.h"
#include "bitmanipulation.h"

#define DEBUG

//
void loadBinaryDebug(const char *fileName,uint32_t *memory);

//
ARM11* initialiseDebug();

//
uint32_t fetchDebug(ARM11 *arm);

//
instruction* decodeDebug(uint32_t fetched);

#ifdef DEBUG
  #define loadBinary(fileName,memory) (loadBinaryDebug(fileName,memory))
  #define initialise() (initialiseDebug())
  #define fetch(arm) (fetchDebug(arm))
  #define decode(fetched) (decodeDebug(fetched))
#else
  #define loadBinary(fileName,memory) (loadBinary(fileName,memory))
  #define initialise() (initialise())
  #define fetch(arm) (fetch(arm))
  #define decode(fetched) (decode(fetched))
#endif // DEBUG








#endif // DEBUG_H
