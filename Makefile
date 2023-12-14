TARGET=calc
SRC=main.c lexer.c reader.c
TEST:=./test.txt

${TARGET}: ${SRC}
	${CC} -o $@ $^ 

clean:
	rm -rf ${TARGET}

test: ${TEST} ${TARGET}
	./${TARGET} ${TEST}


.PHONY=clean test

