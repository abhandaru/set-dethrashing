//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "config.h"

using std::cout;
using std::endl;
using std::string;

Config::Config(int argc, char const *argv[]) {
  // See if we have enough arguments
  if (argc < 3) {
    print_usage();
  }

  // Determine the run mode.
  mode = NONE;
  for (int i = 0; i < argc; i++) {
    string token(argv[i]);
    if (token.compare("-mode") == 0 && i < argc - 1) {
      string mode_token(argv[i + 1]);
      if (mode_token.compare("correct") == 0) {
        mode = CORRECT;
      } else if (mode_token.compare("perf") == 0) {
        mode = PERF;
      } else {
        print_usage();
      }
    }
  }
}


void Config::print_usage() {
  cout << "Usage: driver.out -mode [correct, perf]" << endl;
  exit(1);
}
