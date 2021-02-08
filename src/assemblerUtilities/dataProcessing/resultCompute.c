#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../assemblerUtilities.h"
#include "../../database/masks.h"
#include "../../database/mnemonics.h"

void resultCompute(FILE *writeFile, char *args, enum mnemonic type) {
    //Extract the arguments from the instruction
    char *rd = strtok(args, " r,");
    uint8_t rdV = strtol(rd, NULL, 0);
    char *rn = strtok(NULL, " r,");
    uint8_t rnV = strtol(rn, NULL, 0);
    char *op2s = strtok(NULL, ", ");
    bool imm = (op2s[0] == '#') ? true : false;
    uint32_t op2 = strtol(strtok(op2s, "r#"), NULL, 0);
    uint32_t encoded = 0; //This holds the final binary instruction in uint32 format

    int8_t shift = -1;  //will store which shift can be used (if any, if not then stays -1)
    uint8_t shifted = 0; //will store the value of the already shifted value

    if (imm) {
        uint32_t op2rot = op2; //will be used to temporarily check a rotational mutation of op2

        for (int i = 0; i < 32; i += 2) {
            if (i != 0) {
                op2rot = (op2 >> (32 - i)) | (op2 << i); //Get the next rotational mutation
            }
            if ((0xff & op2rot) == op2rot) { //See if it can be fitted into the first 8 bits
                shift = i;
                shifted = op2rot;
                break;
            }
        }
    }


    //set the opcode depending on the mnemonic
    switch (type) {
        case AND: //nothing to do here, but left it in for readability
            break;
        case EOR:
            encoded |= 0x1 << DP_MASK_OPCODE_OFFSET;
            break;
        case SUB:
            encoded |= 0x2 << DP_MASK_OPCODE_OFFSET;
            break;
        case RSB:
            encoded |= 0x3 << DP_MASK_OPCODE_OFFSET;
            break;
        case ADD:
            encoded |= 0x4 << DP_MASK_OPCODE_OFFSET;
            break;
        case ORR:
            encoded |= 0xc << DP_MASK_OPCODE_OFFSET;
            break;
    }

    //Build up the universal part of the instruction binary code
    encoded |= 0xe << COND_OFFSET; //condition
    encoded |= rnV << DP_MASK_RN; //rn
    encoded |= rdV << DP_MASK_RD; //rd

    if (imm) {
        //If the operand can be expressed via a rotation, then fill in the rest of the detail with the universal parts of the instruction
        if (shift != -1) {
            encoded |= 0x1 << DP_MASK_IMM_OFFSET; //imm op
            encoded |= (shift / 2) << 8; //shift amount
            encoded |= shifted; //shift value
        } else {
            printf("Numeric constant is invalid\n");
        }
    } else {
        encoded |= op2; //Register number
    }

    //Write the instruction to the binary file
    write(writeFile, encoded);
}
