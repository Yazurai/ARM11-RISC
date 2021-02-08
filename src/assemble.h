#ifndef ARM11_06_ASSEMBLE_H
#define ARM11_06_ASSEMBLE_H

#include <stdint.h>
#include "tableUtilities/symbolTable.h"

extern uint32_t constantAddress;
extern uint32_t pc;
extern struct symbolTableStruct symbolTable;

extern uint32_t constantList[];
extern uint32_t constantCount;

#endif //ARM11_06_ASSEMBLE_H
