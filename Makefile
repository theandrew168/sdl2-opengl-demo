# Request POSIX Make behavior and disable any default suffix-based rules
.POSIX:
.SUFFIXES:


# Declare compiler tools and flags
CC      = cc
CFLAGS  = -std=c99
CFLAGS += -fPIC -g -Og
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -Wno-unused-parameter -Wno-unused-result -Wno-unused-function
CFLAGS += -Isrc/
LDFLAGS =
LDLIBS  = -lGL -lSDL2


# Build the main executable
demo: src/main.c src/opengl.c src/opengl.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/main.c src/opengl.c $(LDLIBS)


# Helper target that cleans up build artifacts
.PHONY: clean
clean:
	rm -fr demo demo.exe src/*.o


# Default rule for compiling .c files to .o object files
.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
