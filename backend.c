#include <stdio.h>

#include "parser.h"
#include "lexer.h"
#include "backend.h"

static const char *RULENAME[] = {
	[RULE_TERMINAL] = "TERMINAL",
	[RULE_E] = "E",
	[RULE_E2] = "E2",
	[RULE_E3] = "E3",
};

void PrintParseTree(ParseTree *T) {
	printf("rule: %s\n", RULENAME[T->r]);
	if (T->r == RULE_TERMINAL) {
		PrintToken(&(T->token));
	}
	putchar('\n');

	ParseTree *child = T->child;

	while (child) {
		PrintParseTree(child);
      		child = child->neighbor;
	}

	return;
}
