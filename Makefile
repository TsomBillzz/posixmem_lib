CC=cc
LIBS=-lrt
CFLAGS=-std=c99 -Wall -Wextra -pedantic -D_XOPEN_SOURCE=500

TESTS=mem_writer mem_reader

all: ${TESTS}

${TESTS}: posixmem_lib.c posixmem_lib.h mem_writer.c
	${CC} ${CFLAGS} posixmem_lib.c $@.c -o $@ ${LIBS}

clean:
	rm -f ${TESTS}

run: all
	./mem_writer
	./mem_reader

