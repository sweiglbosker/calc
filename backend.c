#include <stdio.h>

#include "parser.h"
#include "lexer.h"
#include "backend.h"

void PrintParseTree(ParseTree *T) {
	printf("rule: %s\n", RULENAME[T->r]);
	if (T->r == RULE_TERMINAL) {
		PrintToken(&(T->token));
		putchar('\n');
	}


	for (ParseTree *child = T->child; child != NULL; child = child->neighbor) {
		PrintParseTree(child);
	}

	return;
}
