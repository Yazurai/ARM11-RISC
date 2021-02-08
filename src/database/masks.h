#ifndef ARM11_06_MASKS_H
#define ARM11_06_MASKS_H

//The masks themselves
/*#define ONE_BIT 0x1
#define TWO_BITS 0x3
#define FOUR_BITS 0xf*/

#define COND_OFFSET 28

//The masks for identifying the different instructions
#define DP_MASK 0x00000010
#define M_MASK 0x00000010
#define DT_MASK 0x04000000
#define B_MASK 0x08000000
#define B_ENCODE_MASK 0x0a000000

//The mask offsets for the shifted register function
#define SR_MASK_AMOUNT_OFFSET  7
#define SR_MASK_TYPE_OFFSET 5

//The mask offsets for the data transfer function
#define DT_MASK_IMM_OFFSET 25
#define DT_MASK_INDEXING_OFFSET 24
#define DT_MASK_UP_OFFSET 23
#define DT_MASK_LS_OFFSET 20
#define DT_MASK_RN_OFFSET 16
#define DT_MASK_RD_OFFSET 12

//The mask offsets for the multiply function
#define M_MASK_ACC_OFFSET 21
#define M_MASK_SET_OFFSET  20
#define M_MASK_RD 16
#define M_MASK_RN 12
#define M_MASK_RS 8

//The mask offsets for the data processing function
#define DP_MASK_IMM_OFFSET 25
#define DP_MASK_OPCODE_OFFSET 21
#define DP_MASK_SET_OFFSET 20
#define DP_MASK_RN 16
#define DP_MASK_RD 12
#define DP_IMM_OP_OFFSET 8

//lsl masks
#define LSL_MASK 0xe1a01000

//multiply masks
#define M_CODE_MASK 0x00000090

#endif //ARM11_06_MASKS_H
