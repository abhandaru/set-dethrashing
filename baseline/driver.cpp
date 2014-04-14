//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "driver.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
  float* matrixA = (float*)malloc(N * N * sizeof(float));
  float* matrixB = (float*)malloc(N * N * sizeof(float));
  float* matrixC = (float*)malloc(N * N * sizeof(float));
  Generator::random(matrixA, N, N);
  Generator::random(matrixB, N, N);
  matrix_mul(matrixA, matrixB, matrixC, N);
  cout << "Matrix A: " << endl;
  Util::print_matrix(matrixA, N, N);
  cout << "Matrix B: " << endl;
  Util::print_matrix(matrixB, N, N);
  cout << "Matrix C: " << endl;
  Util::print_matrix(matrixC, N, N);
  return 0;
}
