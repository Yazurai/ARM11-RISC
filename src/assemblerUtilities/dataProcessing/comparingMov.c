#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../assemblerUtilities.h"
#include "../../database/mnemonics.h"
#include "../../database/masks.h"

void comparingMov(FILE *writeFile, char *args, enum mnemonic type) {
    //Extract the arguments from the instruction
    char *r = strtok(args, " r,");
    uint8_t rV = strtol(r, NULL, 0);
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

    //Set the appropriate opcode depending on the mnemonic
    switch (type) {
        case CMP:
            encoded |= 0xa << DP_MASK_OPCODE_OFFSET;
            break;
        case TEQ:
            encoded |= 0x9 << DP_MASK_OPCODE_OFFSET;
            break;
        case TST:
            encoded |= 0x8 << DP_MASK_OPCODE_OFFSET;
            break;
        case MOV:
            encoded |= 0xd << DP_MASK_OPCODE_OFFSET;
            break;
    }

    encoded |= 0xe0000000; //condition
    if (type != MOV) {
        encoded |= 0x1 << DP_MASK_SET_OFFSET; //set cond
        encoded |= rV << DP_MASK_RN; //rn
    } else {
        encoded |= rV << DP_MASK_RD; //rd
    }


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
