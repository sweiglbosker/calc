TARGET=calc
SRC=main.c lexer.c reader.c parser.c
TEST:=./test.txt

${TARGET}: ${SRC}
	${CC} -Wall -g -o $@ $^ 

clean:
	rm -rf ${TARGET}

test: ${TEST} ${TARGET}
	gdb --args ./${TARGET} ${TEST} 


.PHONY=clean test

