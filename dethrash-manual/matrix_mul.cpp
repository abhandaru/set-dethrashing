//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "matrix_mul.h"

using std::cout;
using std::endl;


void matrix_mul(float *A, float *B, float *C, unsigned int size) {

  //
  // This is where we rearrange the memory.
  //

  int length = size * size;
  // Allocate memory padded to block size.
  int mem_size = length * NUM_OPERANDS * sizeof(float) + L1_BLK_SIZE;
  float* unaligned_mem = (float *) malloc(mem_size);
  float* interleaved = (float*) block_align(unaligned_mem);
  // Load inputs A and B into the interleaved data format.
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

  //
  // Do operation on interleaved memory.
  //

  for (unsigned int i = 0; i < size; i++) {
    for (unsigned int j = 0; j < size; j++) {
      float sum = 0.0f;
      for(unsigned int k = 0; k < size; k++) {
        int a_index = i * size + k;
        int b_index = k * size + j;
        float Aik = interleaved[inverse_index(a_index, A_OFFSET)];
        float Bkj = interleaved[inverse_index(b_index, B_OFFSET)];
        sum += Aik * Bkj;
      }
      int c_index = i * size + j;
      interleaved[inverse_index(c_index, C_OFFSET)] = sum;
    }
  }

  //
  // Copy back into the result matrix
  //
  int baseC = C_OFFSET;
  for (int i = 0; i < length; i++) {
    if (i > 0 && i % FLT_PER_BLOCK == 0) {
      baseC += NUM_OPERANDS;
    }
    C[i] = interleaved[baseC * FLT_PER_BLOCK + i % FLT_PER_BLOCK];
  }
}


//
// Align the memory address to the next block.
//
inline float* block_align(float* address) {
  return (float *)((uint64_t)(address) & (~L1_BLK_SIZE + 1));
}


//
// Compute the address into the interleaved data format.
//
inline int inverse_index(int index, int offset) {
  return (index / FLT_PER_BLOCK) * NUM_OPERANDS * FLT_PER_BLOCK
    + (index % FLT_PER_BLOCK)
    + (offset * FLT_PER_BLOCK);
}


