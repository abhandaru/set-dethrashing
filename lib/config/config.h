//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <cstdlib>
#include <cstring>
#include <iostream>

// Run mode types.
typedef enum {
  NONE,
  PERF,
  CORRECT
} run_mode_t;


// Matrix dimensions.
#define M 8
#define N 8


// Config class members.
class Config {
 public:
  Config(int argc, char const *argv[]);

  // Mode
  run_mode_t mode;

 private:
  void print_usage();
};

#endif
