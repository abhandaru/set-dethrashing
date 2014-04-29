# gcc macros
CC=g++
CFLAGS=-O2 -c -Wall -g
LDFLAGS=

# llvm macros
LL=clang
LLFLAGS=-O2 -emit-llvm
LLC=llc
LLCFLAGS=-filetype=obj

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
LLC_OBJECTS=$(LL_OBJECTS:.bc=.o)

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

$(LLC_OBJECTS): %.o: %.bc
	$(LLC) $(LLCFLAGS) $< -o $@

$(LL_OBJECTS): %.bc: %.cpp
	$(LL) -c $(LLFLAGS) $< -o $@


# clean
clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
	rm -f $(LL_OBJECTS)
