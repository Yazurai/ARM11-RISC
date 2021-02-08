#ifndef ARM11_06_EMULATORUTILITIES_H
#define ARM11_06_EMULATORUTILITIES_H

uint32_t getMemoryWord(uint32_t address, bool isReverse);

bool checkCond(void);

int32_t getCPSR(void);

uint32_t extractShiftedRegister(bool *carryout);

#endif //ARM11_06_EMULATORUTILITIES_H
