# Makefile that puts .o in obj and executable files in bin
# In progress

CC      = gcc
CFLAGS  = -O3 -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 #-Wall -g -Werror -pedantic -fsanitize=signed-integer-overflow -fsanitize-undefined-trap-on-error
OBJECTS = emulate.o memory.o cpu.o instruction.o shifter.o conditions.o

BIN = ../../bin

emulate: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/emulate

%.o: %.c    
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f *.o
	rm -f emulate

.PHONY: all clean
