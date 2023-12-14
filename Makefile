TARGET=calc
SRC=main.c lexer.c reader.c

${TARGET}: ${SRC}
	${CC} -o $@ $^ 

clean:
	rm -rf ${TARGET}

.PHONY=clean

