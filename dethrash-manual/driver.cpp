//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "driver.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
  // Configuration.
  Config config(argc, argv);

  // Allocate initial space for matrices.
  float* matrixA = (float*) malloc(N * N * sizeof(float));
  float* matrixB = (float*) malloc(N * N * sizeof(float));
  float* matrixC = (float*) malloc(N * N * sizeof(float));

  // Generate random input matrices.
  Generator::random(matrixA, N, N);
  Generator::random(matrixB, N, N);
  matrix_mul(matrixA, matrixB, matrixC, N);

  // Print out the results.
  if (config.mode == CORRECT) {
    cout << "Matrix A: " << endl;
    Util::print_matrix(matrixA, N, N);
    cout << "Matrix B: " << endl;
    Util::print_matrix(matrixB, N, N);
    cout << "Matrix C: " << endl;
    Util::print_matrix(matrixC, N, N);
  }

  // Return normally.
  return 0;
}
