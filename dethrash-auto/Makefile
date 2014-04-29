# gcc macros
CC=g++
CFLAGS=-O2 -c -Wall -g
LDFLAGS=

# llvm macros
PASS=../dethrash-pass/dethrash.so
PASS_NAME=-dethrash
LL=clang
LLFLAGS=-O2 -emit-llvm
LLC=llc
LLCFLAGS=-filetype=obj
OPT=opt
OPTFLAGS=-load $(PASS) $(PASS_NAME)

# grouped sources
GPP_SOURCES= \
  ../lib/config/config.cpp \
  ../lib/generators/generator.cpp \
  ../lib/util/util.cpp \
  ../baseline/driver.cpp
LL_SOURCES= \
  ../baseline/matrix_mul.cpp
GPP_OBJECTS=$(GPP_SOURCES:.cpp=.o)
LL_OBJECTS=$(LL_SOURCES:.cpp=.bc)
OPT_OBJECTS=$(LL_OBJECTS:.bc=.out.bc)
LLC_OBJECTS=$(OPT_OBJECTS:.out.bc=.o)

# combined dependencies
SOURCES=$(GPP_SOURCES) $(LL_SOURCES)
OBJECTS=$(GPP_OBJECTS) $(LLC_OBJECTS)
EXECUTABLE=driver.out


# targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(GPP_OBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# build chain for the llvm pass
$(LLC_OBJECTS): %.o: %.out.bc
	$(LLC) $(LLCFLAGS) $< -o $@
	@llvm-dis $< -o $(subst ../baseline/,./,$(@:.o=.ll))

$(OPT_OBJECTS): %.out.bc: %.bc $(PASS)
	$(OPT) $(OPTFLAGS) $< -o $@

$(LL_OBJECTS): %.bc: %.cpp
	$(LL) -c $(LLFLAGS) $< -o $@


# clean
clean:
	rm -f $(EXECUTABLE)
	rm -f $(GPP_OBJECTS)
	rm -f $(LLC_OBJECTS)
	rm -f $(OPT_OBJECTS)
	rm -f $(LL_OBJECTS)
