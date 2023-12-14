#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "reader.h"

Lexer *NewLexer(Reader *r) {
	Lexer *l = calloc(1, sizeof(Lexer));
	l->r = r;
	l->state = STATE_A;
	
	return l;
}

Token lexer_advance(Lexer *l) {
	Token t = {0};
	l->state = STATE_A;

	while (true) {
		int c = reader_peek(l->r);
		printf("INPUT = ");
		putchar(c);
		putchar('\n');

		enum Q input = tolang(c);
		
		enum lexer_state nextstate = delta[l->state][input];
		printf("got input %d, so we transition from state %d state %d\n", input, l->state, nextstate);

		if (nextstate == STATE_PHI) {
			if (ISFINALSTATE(l->state))
				break;
			else {
				printf("unable to identify token. state = %d, input = %d, i = %d\n", l->state, input, l->pos.i);
				t.kind = TOKEN_ERR;
				t.val.err = 1;
				break;
			}
		} 
		c = reader_next(l->r);
		l->pos.i++;
		l->state = nextstate;
	}

	switch(l->state) {
		case (STATE_LPAREN):
			t.kind = TOKEN_LPAREN; 
			break;
		case (STATE_RPAREN):
			t.kind = TOKEN_LPAREN; 
			break;
		case (STATE_NUM):
			t.kind = TOKEN_NUMBER;
			break;
		case (STATE_EOF):
			t.kind = TOKEN_EOF;
			break;
		case (STATE_OP):
			t.kind = TOKEN_OPERATOR;
			break;
		default:
			printf("idk what happend... final state: %d\n", l->state);
			break;
	}

	return t;
}
