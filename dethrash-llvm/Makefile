#
# 15745 - Set Dethrashing
# Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
# Brief: This makefile is for use on the linux VM distributed by 15-745
#

all: dethrash.so

CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -O0

%.so: %.o
	$(CXX) -dylib -flat_namespace -shared $^ -o $@

clean:
	rm -f *.o *~ *.so
