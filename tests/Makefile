CC=$(CXX)
CFLAGS=-I ../src -I ../src/include -g -c -Wall
LDFLAGS= -ldl -l cppunit
SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
MAIN_OBJECTS := $(patsubst ../src/main.o, , $(patsubst %.cpp,%.o,$(wildcard ../src/*.cpp)))
BIN := $(patsubst %.cpp,%,$(SOURCES))
TEST := $(patsubst %.cpp,%.xml,$(SOURCES))

all: source tests

source:
	$(MAKE) OPTIMIZATION=-O0 SYMBOLS=-g -C ../src all

tests: $(OBJECTS) $(BIN) $(TEST)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

$(BIN):
	$(CC) $(LDFLAGS) $@.o $(MAIN_OBJECTS) $< -o $@

$(TEST): ;echo $@ $(shell ./$(patsubst %.xml,%,$@) -o $@)

clean:
	rm -f *.o $(BIN) $(TEST)
	$(MAKE) -C ../src clean

