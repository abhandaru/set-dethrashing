//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "matrix_mul.h"


void matrix_mul(float *sq_matrix_1, float *sq_matrix_2,
    float *sq_matrix_result, unsigned int sq_dimension) {
  for (unsigned int i = 0; i < sq_dimension; i++) {
    for (unsigned int j = 0; j < sq_dimension; j++) {
      float sum = 0.0f;
      for(unsigned int k = 0; k < sq_dimension; k++) {
        sum += sq_matrix_1[i*sq_dimension + k] * sq_matrix_2[k*sq_dimension + j];
      }
      sq_matrix_result[i*sq_dimension + j] = sum;
    }
  }
}
