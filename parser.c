#include <stdlib.h>

#include "parser.h"
#include "lexer.h"

#define child(tree, n) ((T*)tree->child->neighb

/* note: might be good to keep track of depth for debugging sake */ 
T *ParseE(TokenList *t) {
	T *tree = calloc(1, sizeof(T));
	tree->r = RULE_E;

	/* all production for e start with a nonterminal, so we pick by checking next token */
	/* there are tons of obvious optimizations (ex: we can skip 3 iterations by checking '(') but im ignoring for abstraction sake */
	switch (t->next->token.kind) {
		TOKEN_PLUS:  /* e → e + e2 */
			tree->child = ParseE(t);
			ch
		break;
		TOKEN_MINUS: /* e → e - e2 */
		break;
		default:     /* e -> e2 */
		
	}


	return tree;
}
