CC=$(CXX)
INCLUDE=-I include
PROGNAME=dns
ifndef OPTIMIZATION
OPTLEVEL=-O3
else
OPTLEVEL=$(OPTIMIZATION)
endif

CFLAGS=$(INCLUDE) -c -pedantic -Wall -Werror $(OPTLEVEL) $(SYMBOLS) -DBYTE_ORDER=LITTLE_ENDIAN -DPROGRAM_NAME=\"$(PROGNAME)\"
LDFLAGS=

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

EXECUTABLE=../$(PROGNAME)

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

