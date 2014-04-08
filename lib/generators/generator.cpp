//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "generator.h"


Generator::Generator() { };


void Generator::random(float* matrix, size_t m, size_t n) {
	srand(6);
	for(unsigned int i = 0; i < m * n; i++) {
		*(matrix + i) = MIN_FLOAT + (rand() / (RAND_MAX / (MAX_FLOAT - MIN_FLOAT)));
	}
}
