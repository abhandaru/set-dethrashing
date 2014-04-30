//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "copy.h"

// Returns unaligned interleaved region.
float* hooks_copy_inputs(float* A, float* B) {
  return NULL;
}


void hooks_copy_output(float* unaligned, float* C) {
  float* inter = (float*) hooks_align(unaligned);
  return;
}


inline float* hooks_align(float* unaligned) {
  return NULL;
}
