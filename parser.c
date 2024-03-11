#include <stdlib.h>

#include "parser.h"
#include "lexer.h"

ParseTree *NewTree(Rule r) {
	ParseTree *tree = calloc(1, sizeof(ParseTree));
	tree->r = r;
	return tree;
}

static void AppendChild(ParseTree *parent, ParseTree *child) {
	ParseTree *p = parent->child;

	if (!p) {
		parent->child = child;
		return;
	}

	while (p->neighbor) {
		p = p->neighbor;
	}

	p->neighbor = child;
}


ParseTree *ParseTerminal(TokenList **ptl) {
	ParseTree *tree = NewTree(RULE_TERMINAL);
	TokenList *tl = *ptl;

	printf("parsing terminal\n");
//	if (desired && desired != (*t)->token.kind) 
//		return NULL;
	printf("parsed terminal: %s\n", TOKEN_NAME[tl->token.kind]);

	tree->token.kind = tl->token.kind;
	tree->token.val = tl->token.val;
	
	*ptl = tl->next;

	return tree;
}

/* could also use a table where we use t->next.token as key to pick production for rule */
/* TODO: handle eof (and error?) (in ParseE()?) */
ParseTree *ParseE(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E);
	printf("parsing E\n");

	/* all production for e start with a nonterminal, so we pick by checking next token */
	AppendChild(tree, ParseE2(t));
	AppendChild(tree, ParseER(t));

	return tree;
}

ParseTree *ParseER(TokenList **t) {
	ParseTree *tree = NewTree(RULE_ER);
	printf("parsing E'\n");

	switch ((*t)->token.kind) {
	case TOKEN_PLUS:
	case TOKEN_MINUS:
		AppendChild(tree, ParseTerminal(t));
		AppendChild(tree, ParseER(t));
	default:
		/* TODO: should we create special node for ε? */
		return tree;
	} 

	return tree;
}


ParseTree *ParseE2(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E2);
	printf("parsing E2\n");

	AppendChild(tree, ParseE3(t));
	AppendChild(tree, ParseE2R(t));

	return tree;
}


ParseTree *ParseE2R(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E2R);
	printf("parsing E'\n");

	switch ((*t)->token.kind) {
	case TOKEN_ASTERIX:
	case TOKEN_SLASH:
	case TOKEN_PERCENT:
		AppendChild(tree, ParseTerminal(t));
		AppendChild(tree, ParseE2R(t));
	default:
		return tree;
	}
	return tree;
}


ParseTree *ParseE3(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E3);
	printf("parsing E3\n");

	switch ((*t)->token.kind) {
	case TOKEN_NUMBER: /* e3 → num */ 
		AppendChild(tree, ParseTerminal(t));
		break;
	case TOKEN_LPAREN:
		AppendChild(tree, ParseTerminal(t));
		AppendChild(tree, ParseE(t));
		AppendChild(tree, ParseTerminal(t)); // HACK. we only checked LPAREN
		break;
	}
	return tree;
}
