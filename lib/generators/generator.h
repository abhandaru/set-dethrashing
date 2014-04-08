//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <cstdlib>

#define MIN_FLOAT 0.0
#define MAX_FLOAT 100.0

class Generator {
 public:
  Generator();
  static void random(float* matrix, size_t m, size_t n);
};

#endif
