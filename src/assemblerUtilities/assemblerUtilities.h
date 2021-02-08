#ifndef ARM11_06_ASSEMBLERUTILITIES_H
#define ARM11_06_ASSEMBLERUTILITIES_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//Writes a 32 bit number(bin) to the binary file and handles errors
void write(FILE *writeFile, uint32_t word);

//Performs one of the pass cycles of the two-pass through strategy depending on the isFirstPass bool
void passThrough(FILE *readFile, FILE *writeFile, bool isFirstPass);

#endif //ARM11_06_ASSEMBLERUTILITIES_H
