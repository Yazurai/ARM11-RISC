#ifndef ARM11_06_EMULATE_H
#define ARM11_06_EMULATE_H

#include <stdint.h>
#include <stdbool.h>
#include "database/messages.h"
#include "database/mnemonics.h"
#include "assemblerUtilities/assemblerUtilities.h"

#define NO_OF_REGISTERS 16
#define PC gRegisters[15]

extern uint8_t *ram; //memory (make it to pointer)
extern uint32_t gRegisters[NO_OF_REGISTERS]; //general purpose registers, 4 bytes/register
extern bool nFlag, zFlag, cFlag, vFlag; //top 4 bits of CPSR

extern bool hasFetched; //hasFetched holds whether there's already a fetched instruction and fetchedInstr holds that
extern uint32_t fetchedInstr;

extern bool hasDecoded; //hasDecoded holds whether there's already a decoded instruction and decodedInstr holds that
extern uint32_t decodedInstr;
extern enum mnemonic decodedCode;

bool canFinish; //Holds whether we ran into an all zero instruction or not

#endif //ARM11_06_EMULATE_H
