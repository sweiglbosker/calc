#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reader.h"
#include "lexer.h"
#include "parser.h"
#include "backend.h"

void interactive() {
	while (true) {
		Reader *r = new_reader(READER_STDIN, NULL);

		if (reader_peek(r) == 'q')
			break;

		Lexer *l = NewLexer(r);

		TokenList *tokens = Scan(l);

		if (!tokens) {
			lexer_free(l);
			reader_free(r);
			continue;
		}

		ParseTree *parsetree = ParseE(&tokens); 
		long result = evalE(parsetree);

		printf("result: %li\n", result);


		tokenlist_free(tokens);
		reader_free(r);
		lexer_free(l);
		parsetree_free(parsetree);
	}
}

int main(int argc, char *argv[]) {
	Reader *r = NULL;
	Lexer *l = NULL;
	TokenList *tokens = NULL;
	ParseTree *parsetree = NULL;

	if (argc != 2) {
		fprintf(stderr, "usage: %s [file]", argv[0]);
		exit(1);
	}

	if (!strcmp(argv[1], "-i")) {
		interactive();
	} else {
		r = new_reader(READER_FILE, &argv[1]);

		l = NewLexer(r);
		tokens = Scan(l);

		parsetree = ParseE(&tokens);
		//	PrintParseTree(parsetree);
		long result = evalE(parsetree);
		printf("result: %li\n", result);
	}




}
