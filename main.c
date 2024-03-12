#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reader.h"
#include "lexer.h"
#include "parser.h"
#include "backend.h"

int main(int argc, char *argv[]) {
	bool interactive = false;
	Reader *r = NULL;
	Lexer *l = NULL;
	TokenList *tokens = NULL;
	ParseTree *parsetree = NULL;

	if (argc != 2) {
		fprintf(stderr, "usage: %s [file]", argv[0]);
		exit(1);
	}

	if (!strcmp(argv[1], "-i")) 
		interactive = true;

	if (interactive) 
		r = new_reader(READER_STDIN, NULL);
	else 
		r = new_reader(READER_FILE, &argv[1]);


	l = NewLexer(r);
	tokens = Scan(l);

	parsetree = ParseE(&tokens);

//	PrintParseTree(parsetree);
	long result = evalE(parsetree);
	printf("result: %li\n", result);

}
