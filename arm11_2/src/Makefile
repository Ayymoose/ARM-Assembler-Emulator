CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic -c -I header/

.SUFFIXES: .c .o

all: emulate

#assemble: assemble.o

emulate: emulate.o pipeline.o loader.o auxiliary.o
	$(CC) emulate.o pipeline.o loader.o auxiliary.o -o emulate

emulate.o: emulate.c header/processor.h
	$(CC) $(CFLAGS) emulate.c -o emulate.o

pipeline.o: pipeline.c
	$(CC) $(CFLAGS) pipeline.c -o pipeline.o

loader.o: loader.c
	$(CC) $(CFLAGS) loader.c -o loader.o

auxiliary.o: auxiliary.c
	$(CC) $(CFLAGS) auxiliary.c -o auxiliary.o


clean:
	rm -f *.o
	rm -f emulate

.PHONY: all clean
