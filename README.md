# ARM11-RISC
An assembler and emulator for an RISC ARM11 processor architecture written in C.

## The assembler
The project bases off of a family of Reduced Instruction Set Computer (RISC) based computer processors. The instruction set is a subset of the ARM instruction set architecture. The project has two parts, an emulator and assembler. The emulator simulates the execution of an ARM binary file on a Raspberry Pi (ARM1176JZF-S 700 MHz processor). The assembler translates an ARM assembly source file into a binary file that can subsequently be executed by the emulator.

## The emulator
The emulator reads in ARM binary object code (i.e. compiled assembly code) from a binary file whose filename is specified as the sole argument on the command line. The object code consists of a number of 32-bit ‘words’. The emulator memory i byte addressable and has a capacity of 64KB (i.e. 216 = 65536 bytes) which means that all addresses can be accommodated in 16 bits. Once the binary file has been loaded, the emulator then runs the program contained within it by simulating the execution of each instruction in turn, starting with the instruction at location 0, which is the initial value of the program counter (PC) register

The ARM system has 17, 32-bit registers. Registers 0 - 12 are general purpose, registers 13 and 14 are ignored by the emulator. The PC is register 15, and the CPSR is register 16.

The emulator will deviate from standard ARM and interpret an all-0 instruction (andeq r0, r0, r0) as the signal that the emulator should terminate.

The emulator supports four of the ARM instructions

- Data processing
- Multiply
- Single data transfer
- Brach instruction

![Available ARM instructions](https://github.com/Yazurai/ARM11-RISC/blob/master/documentation/table.png?raw=true)

## The full specification can be [found here](https://tbkhoa.web.elte.hu/projects/arm-specification.pdf)

# Usage

```shell
>assemble factorial

>emulate factorial
Registers:
$0  :        120 (0x00000078)
$1  :          0 (0x00000000)
$2  :        120 (0x00000078)
$3  :        256 (0x00000100)
$4  :          0 (0x00000000)
$5  :          0 (0x00000000)
$6  :          0 (0x00000000)
$7  :          0 (0x00000000)
$8  :          0 (0x00000000)
$9  :          0 (0x00000000)
$10 :          0 (0x00000000)
$11 :          0 (0x00000000)
$12 :          0 (0x00000000)
PC  :         44 (0x0000002c)
CPSR: 1610612736 (0x60000000)
Non-zero memory:
0x00000000: 0x0100a0e3
0x00000004: 0x0510a0e3
0x00000008: 0x910002e0
0x0000000c: 0x0200a0e1
0x00000010: 0x011041e2
0x00000014: 0x000051e3
0x00000018: 0xfaffff1a
0x0000001c: 0x013ca0e3
0x00000020: 0x002083e5
0x00000100: 0x78000000
```


