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


ParseTree *ParseTerminal(TokenList **t) {
//	if (desired && desired != (*t)->token.kind) 
//		return NULL;
	ParseTree *tree = NewTree(RULE_TERMINAL);
	printf("parsed terminal: %s\n", TOKEN_NAME[(*t)->token.kind]);
	tree->token = (*t)->token;
	
	return tree;
}

/* could also use a table where we use t->next.token as key to pick production for rule */
/* TODO: handle eof (and error?) (in ParseE()?) */
ParseTree *ParseE(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E);
	printf("parsing E\n");

	/* all production for e start with a nonterminal, so we pick by checking next token */
	/* there are tons of obvious optimizations (ex: we can skip 3 iterations by checking '(') but im ignoring for abstraction sake */
	switch ((*t)->next->token.kind) {
		TOKEN_PLUS: 	/* e → e + e2 */
		TOKEN_MINUS:	/* e → e - e2 */
			AppendChild(tree, ParseE(t));
			AppendChild(tree, ParseTerminal(t));
			AppendChild(tree, ParseE2(t));
			break;
		default:	/* e → e2 */
			AppendChild(tree, ParseE2(t));
	}

	return tree;
}

ParseTree *ParseE2(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E2);
	printf("parsing E2\n");

	switch ((*t)->next->token.kind) {
		TOKEN_ASTERIX:	/* e2 → e2 * e3 */ 
		TOKEN_SLASH:	/* e2 → e2 / e3 */ 
		TOKEN_PERCENT:	/* e2 % e3 */ 
			AppendChild(tree, ParseE2(t));
			AppendChild(tree, ParseTerminal(t));
			AppendChild(tree, ParseE3(t));
			break;
		default: 	/* e2 → e3 */ 
			AppendChild(tree, ParseE3(t));
	}
	return tree;
}

ParseTree *ParseE3(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E3);
	printf("parsing E3\n");

	switch ((*t)->token.kind) {
	TOKEN_NUMBER: /* e3 → num */ 
		AppendChild(tree, ParseTerminal(t));
		break;
	TOKEN_LPAREN:
		AppendChild(tree, ParseTerminal(t));
		AppendChild(tree, ParseE(t));
		AppendChild(tree, ParseTerminal(t)); // HACK. we only checked LPAREN
	}
	return tree;
}
