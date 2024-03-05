TARGET = calc
SRC = main.c lexer.c reader.c parser.c backend.c
OBJ = $(SRC:.c=.o)
HEADERS = $(wildcard *.h)
TEST := ./test.txt
CFLAGS := -Wall -Wshadow -g -O2 -march=native -std=c11 -pipe

${TARGET}: ${OBJ}
	${CC} ${CFLAGS} -o $@ $^

# rebuild all .o files when any .h file changes
${OBJ}: ${HEADERS}

clean:
	rm -f ${TARGET} ${OBJ}

test: ${TEST} ${TARGET}
	gdb --args ./${TARGET} ${TEST} 


.PHONY=clean test
