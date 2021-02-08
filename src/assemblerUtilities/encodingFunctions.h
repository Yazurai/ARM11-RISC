#ifndef ARM11_06_ENCODINGFUNCTIONS_H
#define ARM11_06_ENCODINGFUNCTIONS_H

#include <stdio.h>
#include "../database/mnemonics.h"

void resultCompute(FILE *writeFile, char *args, enum mnemonic type);

void comparingMov(FILE *writeFile, char *args, enum mnemonic type);

void multiply(FILE *writeFile, char *args, enum mnemonic type);

void transfer(FILE *writeFile, char *args, enum mnemonic transferType);

void branch(FILE *writeFile, char *args, enum mnemonic type);

void lsl(FILE *writeFile, char *args);

void andeq(FILE *writeFile);

#endif //ARM11_06_ENCODINGFUNCTIONS_H
