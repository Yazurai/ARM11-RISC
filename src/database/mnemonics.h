#ifndef ARM11_06_MNEMONICS_H
#define ARM11_06_MNEMONICS_H

#include <stdbool.h>
#include <stdint.h>

#define MNEMONIC_COUNT 23

enum mnemonic {
    ADD = 0x1,
    SUB = 0x2,
    RSB = 0x4,
    AND = 0x8,
    EOR = 0x10,
    ORR = 0x20,
    MOV = 0x40,
    TST = 0x80,
    TEQ = 0x100,
    CMP = 0x200,
    MUL = 0x400,
    MLA = 0x800,
    LDR = 0x1000,
    STR = 0x2000,
    BEQ = 0x4000,
    BNE = 0x8000,
    BGE = 0x10000,
    BLT = 0x20000,
    BGT = 0x40000,
    BLE = 0x80000,
    B = 0x100000,
    LSL = 0x200000,
    ANDEQ = 0x400000,
    DATAPROCESS = ADD | SUB | RSB | AND | EOR | ORR | MOV | TST | TEQ | CMP,
    RESULTCOMPUTE = ADD | SUB | RSB | AND | EOR | ORR,
    COMPARINGMOV = TST | TEQ | CMP | MOV,
    MULTIPLY = MUL | MLA,
    DATATRANSFER = LDR | STR,
    BRANCH = BEQ | BNE | BGE | BLT | BGT | BLE | B,
    SPECIAL = LSL | ANDEQ,
    INVALID = 0
};

static char mnemonicsTable[23][6] =
        {
                "add", "sub", "rsb", "and", "eor", "orr", "mov", "tst", "teq", "cmp", "mul", "mla", "ldr",
                "str", "beq", "bne", "bge", "blt", "bgt", "ble", "b", "lsl", "andeq"
        };

static enum mnemonic mnemonicsEnumTable[] =
        {
                ADD, SUB, RSB, AND, EOR, ORR, MOV, TST, TEQ, CMP, MUL, MLA, LDR, STR, BEQ, BNE, BGE, BLT, BGT,
                BLE, B, LSL, ANDEQ
        };

static uint32_t mnemonicsFunctionTable[] =
        {
                3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 4, 3, 2,
                2, 1, 1, 1, 1, 1, 1, 1, 2, 3
        };
#endif //ARM11_06_MNEMONICS_H
