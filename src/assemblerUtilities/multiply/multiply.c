#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../assemblerUtilities.h"
#include "../../database/mnemonics.h"
#include "../../database/masks.h"

void multiply(FILE *writeFile, char *args, enum mnemonic type) {
    //Extract the arguments of the multiply instruction
    char *rd = strtok(args, " r,");
    uint8_t rdV = strtol(rd, NULL, 0);
    char *rm = strtok(NULL, " r,");
    uint8_t rmV = strtol(rm, NULL, 0);
    char *rs = strtok(NULL, " r,");
    uint8_t rsV = strtol(rs, NULL, 0);
    char *rn = strtok(NULL, " r,");
    uint8_t rnV;

    //If the type is mla, than we need the accumulator and set it accordingly, otherwise just move on
    uint32_t encoded = 0;
    if (type == MLA) {
        rnV = strtol(rn, NULL, 0);
        encoded |= rnV << DP_MASK_RN; //rn
        encoded |= 0x1 << M_MASK_ACC_OFFSET; //acc bit
    }

    //Using bit OR and bit shifting, we build up the encoded binary code (in the form of an uint32)
    encoded |= 0xe << COND_OFFSET; //condition
    encoded |= rdV << M_MASK_RD; //rd
    encoded |= rsV << M_MASK_RS; //rs
    encoded |= M_CODE_MASK; //the 1001 code
    encoded |= rmV; //rm

    //Then we write this to the binary file
    write(writeFile, encoded);
}
