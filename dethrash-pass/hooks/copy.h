//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#ifndef __COPY_H__
#define __COPY_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//
// This will be decided at compile time for matrix operations, so we can
// define it here without loss of fidelity in our results.
//
#define L1_BLK_SIZE     64  // affects the stride for copying
#define FLT_PER_BLOCK   (L1_BLK_SIZE / sizeof(float))
#define A_OFFSET        0
#define B_OFFSET        1
#define C_OFFSET        2
#define NUM_OPERANDS    3

//
// Function prototypes.
//
float* hooks_copy_inputs(float* A, float* B, int size);
void hooks_copy_output(float* unaligned, float* C, int size);
inline float* hooks_align(float* unaligned);

#endif
