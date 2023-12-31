#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "reader.h"
#include "lexer.h"

int main(int argc, char *argv[]) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s [file]", argv[0]);
		exit(1);
	}

	Reader *r = new_reader(READER_FILE, &argv[1]);

	Lexer *l = NewLexer(r);
	
	while (true) {
		Token t = lexer_advance(l);
		printf("found token of type %s", TOKEN_NAME[t.kind]);

		if (t.kind == TOKEN_NUMBER) 
			printf(" and value %d\n", (int)t.val.number);
		else 
			putchar('\n');
	
		if (t.kind == TOKEN_EOF || t.kind == TOKEN_ERR) 
			break;
	}
}
