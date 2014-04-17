//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#ifndef __MATRIX_MUL_H__
#define __MATRIX_MUL_H__

#include <cstdint>
#include <cstdlib>
#include <iostream>

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
void matrix_mul(float *A, float *B, float *C, unsigned int size);
inline float* block_align(float* address);
inline int inverse_index(int index, int offset);

#endif
