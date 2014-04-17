# macros
CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=


# dependencies
SOURCES= \
	../lib/config/config.cpp \
	../lib/generators/generator.cpp \
	../lib/util/util.cpp \
	driver.cpp \
	matrix_mul.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=driver.out


# targets
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


# clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
