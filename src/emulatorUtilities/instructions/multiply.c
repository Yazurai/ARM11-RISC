#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../database/messages.h"
#include "../../emulate.h"
#include "../../database/masks.h"
#include "emulatorInstructions.h"
#include "../emulatorUtilities.h"

//Executes the multiply instruction
void multiply(void) {
    if (checkCond()) {
        //Reads in the operands of the instruction
        bool acc = 0x1 & (decodedInstr >> M_MASK_ACC_OFFSET);
        bool setCond = 0x1 & (decodedInstr >> M_MASK_SET_OFFSET);
        uint8_t rd = 0xf & (decodedInstr >> M_MASK_RD);
        uint8_t rn = 0xf & (decodedInstr >> M_MASK_RN);
        uint8_t rs = 0xf & (decodedInstr >> M_MASK_RS);
        uint8_t rm = 0xf & decodedInstr;
        uint64_t fullResult = 0; //holds the real result of the multiplication
        uint32_t truncResult = 0; // holds the truncated/least 32 bits

        //Executes the instruction depending on the accumulator bit(acc) and then takes the least 32 bits of it and writes it
        fullResult = acc ? (gRegisters[rm] * gRegisters[rs] + gRegisters[rn]) : (gRegisters[rm] * gRegisters[rs]);
        truncResult = (uint32_t) (0xffffffff & fullResult);
        gRegisters[rd] = truncResult;

        //If the cond bit is set, then update the cpsr accordingly
        if (setCond) {
            nFlag = 0x1 & (truncResult >> 31);
            zFlag = truncResult == 0;
        }
    }
}

