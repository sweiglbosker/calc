#include <stdio.h>

#include "parser.h"
#include "lexer.h"
#include "backend.h"

static const char *RULENAME[] = {
	[RULE_TERMINAL] = "TERMINAL",
	[RULE_E] = "E",
	[RULE_ER] = "E'",
	[RULE_E2] = "E2",
	[RULE_E2R] = "E2'",
	[RULE_E3] = "E3",
};

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

long evalE(ParseTree *t) {
	long a = evalE2(t->child);

	return evalER(a, t->child->neighbor);
}

long evalE2(ParseTree *t) {
	long a = evalE3(t->child);

	return evalE2R(a, t->child->neighbor);
}

long evalE3(ParseTree *t) {
	if (t->child->r == RULE_TERMINAL) {
		switch (t->child->token.kind) {
		case TOKEN_NUMBER:
			return (long)t->child->token.val.number;
		case TOKEN_LPAREN:
			return evalE(t->child->neighbor);
		}
	} 
	printf("error in evalE3: unexpected token.\n");
	return 0;
}

long evalER(long a, ParseTree *t) {
	if (!t->child) /* ε production */
		return a;

	switch (t->child->token.kind) {
	case TOKEN_MINUS:
		return evalER(a - evalE2(t->child->neighbor), t->child->neighbor->neighbor);
	case TOKEN_PLUS:
		return evalER(a + evalE2(t->child->neighbor), t->child->neighbor->neighbor);
	}
}

long evalE2R(long a, ParseTree *t) {
	if (!t->child) 
		return a;

	switch (t->child->token.kind) {
	case TOKEN_ASTERIX:
		return evalE2R(a * evalE3(t->child->neighbor), t->child->neighbor->neighbor);
	case TOKEN_PLUS:
		return evalE2R(a + evalE3(t->child->neighbor), t->child->neighbor->neighbor);
	}
}
