#ifndef _PARSER_H
#define _PARSER_H

#include "lexer.h"

typedef enum {
	TERMINAL,
	RULE_E,
	RULE_E2,  
	RULE_E3
} Rule; 

// Parse Tree
typedef struct T {
	Rule r;	/* grammar used to contruct tree */ 
	Token terminal;
//	int n;	/* number of child trees. (X) */
//	struct T *X[];
	struct T *neighbor; /* one of the few optimizations I will make. children/siblings are already ordered so we can use linked list */ 
	struct T *child;
} T;


// production = table[nonterminal][terminal]

T* Parse(TokenList *t);
T* ParseE(TokenList *t);
T* ParseE2(TokenList *t);
T* ParseE3(TokenList *t);

#endif /* PARSER_H */ 
