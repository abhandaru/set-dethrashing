//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "copy.h"

// Returns unaligned interleaved region.
float* hooks_copy_inputs(float* A, float* B, int size) {
  int length = size * size;
  int mem_size = length * NUM_OPERANDS * sizeof(float) + L1_BLK_SIZE;
  float* unaligned = (float *) malloc(mem_size);
  float* interleaved = (float*) hooks_align(unaligned);

  int baseA = A_OFFSET;
  int baseB = B_OFFSET;
  for (int i = 0; i < length; i++) {
    if (i > 0 && i % FLT_PER_BLOCK == 0) {
      baseA += NUM_OPERANDS;
      baseB += NUM_OPERANDS;
    }
    interleaved[baseA * FLT_PER_BLOCK + i % FLT_PER_BLOCK] = A[i];
    interleaved[baseB * FLT_PER_BLOCK + i % FLT_PER_BLOCK] = B[i];
  }

  return unaligned;
}


void hooks_copy_output(float* unaligned, float* C, int size) {
  float* inter = (float*) hooks_align(unaligned);
  int length = size * size;
  int baseC = C_OFFSET;
  for (int i = 0; i < length; i++) {
    if (i > 0 && i % FLT_PER_BLOCK == 0) {
      baseC += NUM_OPERANDS;
    }
    C[i] = inter[baseC * FLT_PER_BLOCK + i % FLT_PER_BLOCK];
  }
  free(unaligned);
  return;
}


inline float* hooks_align(float* unaligned) {
  return (float *)((uint64_t)(unaligned) & (~L1_BLK_SIZE + 1));
}


void hooks_print(int i) {
  printf("load i=%d\n", i);
}
