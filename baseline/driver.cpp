//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "driver.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
  float* matrixA = (float*)malloc(100 * 100 * sizeof(float));
  float* matrixB = (float*)malloc(100 * 100 * sizeof(float));
  float* matrixC = (float*)malloc(100 * 100 * sizeof(float));
  Generator::random(matrixA, 100, 100);
  Generator::random(matrixB, 100, 100);
  matrix_mul(matrixA, matrixB, matrixC, 100);
  cout << *matrixA << endl;
  cout << *matrixB << endl;
  cout << *matrixC << endl;
  return 0;
}
