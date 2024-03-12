#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "reader.h"
#include "lexer.h"
#include "parser.h"
#include "backend.h"

int main(int argc, char *argv[]) {

	if (argc != 2) {
		fprintf(stderr, "usage: %s [file]", argv[0]);
		exit(1);
	}

	Reader *r = new_reader(READER_FILE, &argv[1]);

	Lexer *l = NewLexer(r);
	TokenList *tokens = Scan(l);
	TokenList *p = tokens;

	while (p->next != NULL) {
		PrintToken(&p->token);
		p = p->next;
	}

	ParseTree *parsetree = ParseE(&tokens);

	PrintParseTree(parsetree);
	long result = evalE(parsetree);
	printf("result: %li\n", result);

}
