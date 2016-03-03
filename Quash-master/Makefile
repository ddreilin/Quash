STUDENTID = 2643219
PROGNAME = quash

CC = gcc --std=gnu99
CFLAGS = -Wall -g -Og


####################################################################
#                           IMPORTANT                              #
####################################################################
# Add files to their respective line to get this makefile to build #
# them.                                                            #
####################################################################
# NOTE: The submission scripts assume all files in `CFILES` end with
# .c and all files in `HFILES` end in .h
CFILES = quash.c
HFILES = quash.h debug.h

# Add libraries that need linked as needed (e.g. -lm -lpthread)
LIBS =

DOXYGENCONF = quash.doxygen

OBJFILES = $(patsubst %.c,%.o,$(CFILES))
EXECNAME = $(patsubst %,./%,$(PROGNAME))

RAWC = $(patsubst %.c,%,$(CFILES))
RAWH = $(patsubst %.h,%,$(HFILES))


# Build the documentation and the quash executable
all: doc $(PROGNAME)

# Build the quash program
$(PROGNAME): $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $(PROGNAME) $(LIBS)

# Generic build target for all compilation units. NOTE: Changing a
# header requires you to rebuild the entire project
%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

# Build and run the program
test: $(PROGNAME)
	$(EXECNAME)

# Build the documentation for the project
doc: $(CFILES) $(HFILES) $(DOXYGENCONF) README.md
	doxygen $(DOXYGENCONF)

# Quickly build a submission then extract it. Useful for testing if
# we will be able to build your project from the code you gave us
testsubmit: submit unsubmit

# Build a safeassign friendly submission of the quash project
submit: clean
#	Perform renaming copies across the Makefile and all .c and .h
#	files
	cp Makefile Makefile.txt
	$(foreach file, $(RAWH), cp $(file).h $(file)-h.txt;)
	$(foreach file, $(RAWC), cp $(file).c $(file)-c.txt;)

#	Make a temporary directory
	mkdir -p $(STUDENTID)-project1-quash

#	Move all the renamed files into the temporary directory
	mv Makefile.txt $(STUDENTID)-project1-quash
	mv $(HFILES:.h=-h.txt) $(STUDENTID)-project1-quash
	mv $(CFILES:.c=-c.txt) $(STUDENTID)-project1-quash

#	Compress and remove temporary directory
	zip -r $(STUDENTID)-project1-quash.zip $(STUDENTID)-project1-quash
	-rm -rf $(STUDENTID)-project1-quash

# We will use this command to extract your submission and build
# it. Check to see if the build works before submitting.
unsubmit: $(STUDENTID)-project1-quash.zip
	unzip $< && \
	cd $(STUDENTID)-project1-quash && \
	mv Makefile.txt Makefile && \
	$(foreach file, $(RAWH), mv $(file)-h.txt $(file).h &&) \
	$(foreach file, $(RAWC), mv $(file)-c.txt $(file).c &&) \
	make $(PROGNAME)

# Remove all generated files and directories
clean:
	-rm -rf $(PROGNAME) *.o *~ doc $(STUDENTID)-project1-quash*

.PHONY: all test doc submit unsubmit testsubmit clean