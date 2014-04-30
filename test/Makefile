CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -O0

all: insert.so pass
	llvm-dis out.bc -o out.ll

pass: link
	opt -load ./insert.so -bishe_insert link.bc -o out.bc

link: print test
	llvm-link print.bc test.bc -o link.bc

%.so: %.o
	$(CXX) -dylib -flat_namespace -shared $^ -o $@

print: print.c
	clang -c -O0 -emit-llvm print.c -o print.bc

test: test.c
	clang -c -O0 -emit-llvm test.c -o test.bc

clean:
	rm -f *.o *~ *.so *.bc *.ll
