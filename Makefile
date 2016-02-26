STUDENTID = XXXXXXX
PROGNAME = quash

CC = gcc --std=c99
CFLAGS = -Wall -g -Og

# Add files to their respective line to get this makefile to build them
CFILES = quash.c
HFILES = quash.h debug.h

# Add libraries that need linked as needed (e.g. -lm)
LIBS =

DOXYGENCONF = quash.doxygen

OBJFILES = $(patsubst %.c,%.o,$(CFILES))
EXECNAME = $(patsubst %,./%,$(PROGNAME))


all: doc $(PROGNAME)

$(PROGNAME): $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $(PROGNAME) $(LIBS)

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

test: $(PROGNAME)
	$(EXECNAME)

doc: $(CFILES) $(HFILES) $(DOXYGENCONF) README.md
	doxygen $(DOXYGENCONF)

tar: clean
	tar cfzv $(STUDENTID)-quash.tar.gz *

clean:
	-rm -rf $(PROGNAME) *.o *~ doc

.PHONY: clean
