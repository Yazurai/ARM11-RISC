cmake_minimum_required(VERSION 3.13)
project(arm11_06 C)
set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(src/assemblerUtilities)
include_directories(src/database)
include_directories(src/emulatorUtilities)
include_directories(src/emulatorUtilities/instructions)
include_directories(src/tableUtilities)

add_executable(assemble
        src/assemblerUtilities/branch/branch.c
        src/assemblerUtilities/dataProcessing/comparingMov.c
        src/assemblerUtilities/dataProcessing/resultCompute.c
        src/assemblerUtilities/dataTransfer/dataTransfer.c
        src/assemblerUtilities/multiply/multiply.c
        src/assemblerUtilities/special/andeq.c
        src/assemblerUtilities/special/lsl.c
        src/assemblerUtilities/assemblerUtilities.c
        src/assemblerUtilities/assemblerUtilities.h
        src/assemblerUtilities/encodingFunctions.h
        src/database/masks.h
        src/database/messages.h
        src/database/mnemonics.h
        src/tableUtilities/symbolTable.c
        src/tableUtilities/symbolTable.h
        src/assemble.c
        src/assemble.h
        )

add_executable(emulate
        src/emulatorUtilities/instructions/branch.c
        src/emulatorUtilities/instructions/dataProcessing.c
        src/emulatorUtilities/instructions/dataTransfer.c
        src/emulatorUtilities/instructions/emulatorInstructions.h
        src/emulatorUtilities/instructions/finish.c
        src/emulatorUtilities/instructions/multiply.c
        src/emulatorUtilities/emulatorUtilities.c
        src/emulatorUtilities/emulatorUtilities.h
        src/emulatorUtilities/initialize.c
        src/emulatorUtilities/initialize.h
        src/database/masks.h
        src/database/messages.h
        src/database/mnemonics.h
        src/tableUtilities/symbolTable.c
        src/tableUtilities/symbolTable.h
        src/emulate.c
        src/emulate.h
        )
