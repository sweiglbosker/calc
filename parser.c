#include <stdlib.h>

#include "parser.h"
#include "lexer.h"

ParseTree *NewTree(Rule r) {
	ParseTree *tree = calloc(1, sizeof(ParseTree));
	tree->r = r;

	return tree;
}

void parsetree_free(ParseTree *T) {
	ParseTree *child, *neighbor;

	child = T->child;
	neighbor = T->neighbor;
	free(T);

	/* recursively frees until there is no children and no neighbors */
	if (child) 
		parsetree_free(child);
	
	if (neighbor) 
		parsetree_free(neighbor);

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

	tree->token.kind = tl->token.kind;
	tree->token.val = tl->token.val;
	
	*ptl = tl->next;

	return tree;
}

ParseTree *ParseE(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E);

	AppendChild(tree, ParseE2(t));
	AppendChild(tree, ParseER(t));

	return tree;
}

ParseTree *ParseER(TokenList **t) {
	ParseTree *tree = NewTree(RULE_ER);

	switch ((*t)->token.kind) {
	case TOKEN_PLUS:
	case TOKEN_MINUS:
		AppendChild(tree, ParseTerminal(t));
		AppendChild(tree, ParseE2(t));
		AppendChild(tree, ParseER(t));
	default:
		return tree;
	} 

	return tree;
}


ParseTree *ParseE2(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E2);

	AppendChild(tree, ParseE3(t));
	AppendChild(tree, ParseE2R(t));

	return tree;
}


ParseTree *ParseE2R(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E2R);

	switch ((*t)->token.kind) {
	case TOKEN_ASTERIX:
	case TOKEN_SLASH:
	case TOKEN_PERCENT:
		AppendChild(tree, ParseTerminal(t));
		AppendChild(tree, ParseE3(t));
		AppendChild(tree, ParseE2R(t));
	default:
		return tree;
	}

	return tree;
}


ParseTree *ParseE3(TokenList **t) {
	ParseTree *tree = NewTree(RULE_E3);

	switch ((*t)->token.kind) {
	case TOKEN_NUMBER: /* e3 → num */ 
		AppendChild(tree, ParseTerminal(t));
		break;
	case TOKEN_LPAREN:
		AppendChild(tree, ParseTerminal(t));
		AppendChild(tree, ParseE(t)); 
		AppendChild(tree, ParseTerminal(t)); 
		break;
	default:
		printf("error in ParseE3(): unexpected token.\n");
		PrintToken(&(*t)->token); 
	}

	return tree;
}
