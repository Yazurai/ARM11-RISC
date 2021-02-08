#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../database/messages.h"
#include "../../emulate.h"
#include "../../database/masks.h"
#include "emulatorInstructions.h"
#include "../emulatorUtilities.h"

//Executes the data processing instruction
void dataProcessing(void) {
    if (checkCond()) {
        //Extracts the arguments of the instruction
        bool immOp = 0x1 & (decodedInstr >> DP_MASK_IMM_OFFSET);
        uint8_t opCode = 0xf & (decodedInstr >> DP_MASK_OPCODE_OFFSET);
        bool setCond = 0x1 & (decodedInstr >> DP_MASK_SET_OFFSET);
        uint8_t rn = 0xf & (decodedInstr >> DP_MASK_RN);
        uint8_t rd = 0xf & (decodedInstr >> DP_MASK_RD);
        uint32_t op2 = 0;
        uint32_t result = 0;
        bool carryOut = false;

        //Reads in the second operand depending on the value of the immediate operand(i)
        if (immOp) {
            uint8_t rotAmount = (0xf & (decodedInstr >> DP_IMM_OP_OFFSET)) * 2;
            op2 = 0xff & decodedInstr;

            //To avoid bit shifting by 32
            if (rotAmount != 0) {
                op2 = (op2 >> rotAmount) | (op2 << (32 - rotAmount));
            }
        } else {
            op2 = extractShiftedRegister(&carryOut);
        }

        //Executes the actual operations and sets the appropriate carryout depending on the op
        switch (opCode) {
            case 0: // And
                result = gRegisters[rn] & op2;
                break;
            case 1: // Exclusive or
                result = gRegisters[rn] ^ op2;
                break;
            case 2: // Subtraction
                result = gRegisters[rn] - op2;
                carryOut = op2 <= gRegisters[rn];
                break;
            case 3: // Reverse subtraction
                result = op2 - gRegisters[rn];
                carryOut = op2 <= gRegisters[rn];
                break;
            case 4: // Addition
                result = gRegisters[rn] + op2;
                carryOut = result < op2;
                break;
            case 8: // Test and
                result = gRegisters[rn] & op2;
                break;
            case 9: // Test exclusive or
                result = gRegisters[rn] ^ op2;
                break;
            case 10: // Test subtraction
                result = gRegisters[rn] - op2;
                carryOut = op2 <= gRegisters[rn];
                break;
            case 12: // Or
                result = gRegisters[rn] | op2;
                break;
            case 13: // Move
                result = op2;
                break;
            default:
                printf(MSG_ERR_INVALID_OPCODE, decodedInstr);
                break;
        }

        //Write the result for the appropriate operations
        switch (opCode) {
            case 8: // Test and
            case 9: // Test exclusive or
            case 10: // Test subtraction
                break;
            default:
                gRegisters[rd] = result;
                break;
        }

        //If the cond bit is set, then update the cpsr accordingly
        if (setCond) {
            cFlag = carryOut;
            zFlag = result == 0;
            nFlag = 0x1 & (result >> 31);
        }
    }
}
