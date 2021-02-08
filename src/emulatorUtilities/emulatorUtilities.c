#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "../database/messages.h"
#include "../emulate.h"
#include "initialize.h"
#include "../database/masks.h"

//Gets a word(32 bits) from a given address in the memory
uint32_t getMemoryWord(uint32_t address, bool isReverse) {
    assert(address / 8 <= HIGHEST_WORD_ADDRESS); //is the address point to an appropriate memory address
    uint32_t word = 0;
    if (!isReverse) {
        for (int j = 0; j < 4; j++) {
            word |= ram[address + j] << 8 * (3 - j);
        }
    } else {
        for (int j = 0; j < 4; j++) {
            word |= ram[address + j] << 8 * (j);
        }
    }
    return word;
}

//Checks whether the current condition is true with the current CPSR
bool checkCond(void) {
    uint8_t conditional = decodedInstr >> 28;
    bool condHolds = false;
    switch (conditional) {
        case 0: //eq - equal
            condHolds = zFlag;
            break;
        case 1: //ne - not equal
            condHolds = !zFlag;
            break;
        case 10: //ge - greater or equal
            condHolds = nFlag == vFlag;
            break;
        case 11: //lt - less than
            condHolds = nFlag != vFlag;
            break;
        case 12: //gt - greater than
            condHolds = !zFlag && (nFlag == vFlag);
            break;
        case 13: //le - less than or equal
            condHolds = zFlag && (nFlag != vFlag);
            break;
        case 14: //al - always
            condHolds = true;
            break;
        default:
            printf(MSG_ERR_INVALID_CONDITION, decodedInstr);
            break;
    }
    return condHolds;
}

//Converts the CPSR bool flags to a 32bit integer (Option: could have it the other way around
// Perhaps find a way to make this more concise (maybe macros?)or both simultaneously)
int32_t getCPSR(void) {
    int32_t cpsr = 0;
    cpsr = cpsr | nFlag;
    cpsr <<= 1;
    cpsr = cpsr | zFlag;
    cpsr <<= 1;
    cpsr = cpsr | cFlag;
    cpsr <<= 1;
    cpsr = cpsr | vFlag;
    cpsr <<= 28;

    return cpsr;
}

//Extracts the value from the last 12 bits of the decoded instruction and optionally sets a carryout
uint32_t extractShiftedRegister(bool *carryout) {
    //reads in the arguments from the decoded instruction
    uint8_t sAmount = 0x1f & (decodedInstr >> SR_MASK_AMOUNT_OFFSET);
    uint8_t sType = 0x3 & (decodedInstr >> SR_MASK_TYPE_OFFSET);
    uint32_t rValue = gRegisters[0xf & decodedInstr];
    bool carryOut = false;
    uint32_t result = 0;

    //Because if sAmount == 0 it will mess with 32 shifting, could move it in to case 3
    if (sAmount != 0) {
        switch (sType) {
            case 0: //Logical left shift
                carryOut = 0x1 & (rValue >> (32 - sAmount));
                result = rValue << sAmount;
                break;
            case 1: //Logical right shift
                carryOut = 0x1 & (rValue >> (sAmount - 1));
                result = rValue >> sAmount;
                break;
            case 2: //Arithmetic right shift
                carryOut = 0x1 & (rValue >> (sAmount - 1));
                result = (int32_t) rValue >> sAmount;
                break;
            case 3: //Rotate right
                carryOut = 0x1 & (rValue >> (sAmount - 1));
                result = rValue >> sAmount | rValue << (32 - sAmount);
                break;
            default:
                break;
        }
        if (carryout != NULL) {
            *carryout = carryOut;
        }
    } else {
        result = rValue;
    }
    return result;
}
