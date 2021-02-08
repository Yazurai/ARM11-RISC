#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "encodingFunctions.h"
#include "assemblerUtilities.h"
#include "../database/messages.h"
#include "../database/mnemonics.h"
#include "../assemble.h"

//Writes a 32 bit number(bin) to the binary file and handles errors
void write(FILE *writeFile, uint32_t word) {
    fwrite(&word, sizeof(word), 1, writeFile);
    if (ferror(writeFile)) {
        printf(MSG_ERR_FILE_WRITE);
    }
}

//WARNING: encoding functions require very precise argument formatting and do very little to no error checking themselves
//This function calls the appropriate encoding function depending on the given mnemonic
void encode(enum mnemonic instrCode, FILE *writeFile, char *args) {
    //Here we use the values of enum mnemonic as a bit mask
    args = strtok(args, "\r\n");
    if ((RESULTCOMPUTE & instrCode) == instrCode) {
        resultCompute(writeFile, args, instrCode);
    }
    if ((COMPARINGMOV & instrCode) == instrCode) {
        comparingMov(writeFile, args, instrCode);
    }
    if ((MULTIPLY & instrCode) == instrCode) {
        multiply(writeFile, args, instrCode);
    }
    if ((DATATRANSFER & instrCode) == instrCode) {
        transfer(writeFile, args, instrCode);
    }
    if ((BRANCH & instrCode) == instrCode) {
        branch(writeFile, args, instrCode);
    }
    if ((LSL & instrCode) == instrCode) {
        lsl(writeFile, args);
    }
    if ((ANDEQ & instrCode) == instrCode) {
        andeq(writeFile);
    }
}

//Does a passthrough of the two passthrough system.
//Pre: all labels are a single word
//Pre: none of the labels are an instruction mnemonic
void passThrough(FILE *readFile, FILE *writeFile, bool isFirstPass) {
    pc = 8;

    char currLine[512]; //Holds the current line we're inspecting
    char *currCode; //Holds the mnemonic of the current instruction line
    uint32_t currAddress = 0; //Holds the address of the current word

    while (fgets(currLine, 512, readFile) != NULL) { //Read in line by line until eof
        if (ferror(readFile)) {
            printf(MSG_ERR_FILE_READ);
            exit(EXIT_FAILURE);
        }
        bool isInstruction = false;
        currCode = strtok(currLine, ": "); //Get the first word
        for (int i = 0; i < MNEMONIC_COUNT; ++i) { //get and check whether the first part is a mnemonic
            if ((strcmp(mnemonicsTable[i], currCode) == 0)) { //Check against the array of mnemonics
                if (!isFirstPass) { //We only need to encode when we're on the second pass through
                    char *args = strtok(NULL, "");
                    encode(mnemonicsEnumTable[i], writeFile, args);
                }
                isInstruction = true;
                break;
            }
        }

        if (!isInstruction) {
            if (isFirstPass) {
                tableAdd(&symbolTable, currCode, currAddress); //If it's a label (not instruction) add it to the map table
            }
        } else {
            currAddress += 4; //Otherwise it's a valid instruction and we need to increase the "pc" address
            pc += 4; //We update the pc to properly display the 8 bit offset (was initialized to 8)
        }
    }

    constantAddress = currAddress; //Store the latest word address, this is where the constants addresses start
}
