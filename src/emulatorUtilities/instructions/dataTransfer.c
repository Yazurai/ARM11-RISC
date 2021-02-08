#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../database/messages.h"
#include "../../emulate.h"
#include "../../database/masks.h"
#include "emulatorInstructions.h"
#include "../emulatorUtilities.h"
#include "../initialize.h"

//Executes a single data transfer instruction
void dataTransfer(void) {
    if (checkCond()) {
        //Extracts the arguments of the instruction
        bool immOp = 0x1 & (decodedInstr >> DT_MASK_IMM_OFFSET);
        bool prePost = 0x1 & (decodedInstr >> DT_MASK_INDEXING_OFFSET);
        bool up = 0x1 & (decodedInstr >> DT_MASK_UP_OFFSET);
        bool load = 0x1 & (decodedInstr >> DT_MASK_LS_OFFSET);
        uint8_t rn = 0xf & (decodedInstr >> DT_MASK_RN_OFFSET);
        uint8_t rd = 0xf & (decodedInstr >> DT_MASK_RD_OFFSET);
        uint32_t offset = 0;
        uint32_t address = 0;

        //Extract the offset from the instruction depending on the immediate bit(i)
        offset = immOp ? extractShiftedRegister(NULL) : 0x3ff & decodedInstr;

        //Depending on the pre-post bit(p), and the up bit(u), add/substract the offset
        if (prePost) {
            address = up ? (gRegisters[rn] + offset) : gRegisters[rn] - offset;
        } else {
            address = gRegisters[rn];
            gRegisters[rn] = up ? gRegisters[rn] + offset : gRegisters[rn] - offset;
        }

        //depending on load/save bit, execute the load/save
        if (address > MEMORY_SIZE) {
            printf( "Error: Out of bounds memory access at address 0x%x\n", address);
        } else {
            if (load) {
                gRegisters[rd] = getMemoryWord(address, false);
            } else {
                for (int i = 0; i < 4; i++) {
                    ram[address + i] = 0xff & (gRegisters[rd] >> (i * 8));
                }
            }
        }
    }
}
