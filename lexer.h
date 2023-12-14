#ifndef _LEXER_H
#define _LEXER_H

#include "reader.h"

enum {
	TOKEN_NUMBER,
	TOKEN_LPAREN, 
	TOKEN_RPAREN,
	TOKEN_OPERATOR,
	TOKEN_ERR, 
	TOKEN_EOF 
};

static const char *TOKEN_NAME[] = {
	[TOKEN_NUMBER] = "TOKEN_NUMBER",
	[TOKEN_LPAREN] = "TOKEN_LPAREN",
	[TOKEN_RPAREN] = "TOKEN_RPAREN",
	[TOKEN_OPERATOR] = "TOKEN_OPERATOR",
	[TOKEN_ERR] = "TOKEN_ERR",
	[TOKEN_EOF] = "TOKEN_EOF",
};

enum Q { 
	INPUT_INVALID,
	INPUT_LPAREN,
	INPUT_RPAREN,
	INPUT_ASTERIX,
	INPUT_PLUS,
	INPUT_MINUS, 
	INPUT_SLASH, 
	INPUT_PERCENT, 
	INPUT_DIGIT,
	INPUT_EOF,
	INPUT_SPACE,
	INPUT_NEWLINE
};

typedef enum lexer_state {
	STATE_PHI,
	STATE_LPAREN,
	STATE_RPAREN,
	STATE_OP,
	STATE_NUM,
	STATE_A,
	STATE_B,
	STATE_EOF,
} LexerState;
	
#define NSTATES 9
#define NINPUT 12

#define ISFINALSTATE(x) ((x == STATE_B ||\
			  x == STATE_A) ? false : true)

static const int delta[NSTATES][NINPUT] = {
	/* state        INVALID    (	         ) 	       *	  +	     -	        /	   %	      digit      eof        space	*/	
	[STATE_PHI] = { STATE_PHI },
	[STATE_LPAREN] = { STATE_PHI },
	[STATE_RPAREN] = { STATE_PHI },
	[STATE_OP]  = { STATE_PHI },
	[STATE_NUM] = { STATE_PHI, STATE_PHI,    STATE_PHI,    STATE_PHI, STATE_PHI, STATE_PHI, STATE_PHI, STATE_PHI, STATE_NUM, STATE_PHI, STATE_PHI },
	[STATE_A] =   { STATE_PHI, STATE_LPAREN, STATE_RPAREN, STATE_OP,  STATE_B,   STATE_B,   STATE_OP,  STATE_OP,  STATE_NUM, STATE_EOF, STATE_A, STATE_A },
	[STATE_B] =   { STATE_PHI, STATE_PHI,    STATE_PHI,    STATE_PHI, STATE_PHI, STATE_PHI, STATE_PHI, STATE_PHI, STATE_NUM, STATE_EOF, STATE_OP, STATE_PHI },
	[STATE_EOF] = {0},
};

static inline char tolang(char c) {
	if (c >= 48 && c <= 57)
		return INPUT_DIGIT;

	switch (c) {
	case '(':
		return INPUT_LPAREN;
	case ')':
		return INPUT_RPAREN;
	case '+': 
		return INPUT_PLUS;
	case '-':
		return INPUT_MINUS;
	case '/':
		return INPUT_SLASH;
	case '%':
		return INPUT_PERCENT;
	case EOF:
		return INPUT_EOF;
	case ' ':
	case '\t':
		return INPUT_SPACE;
	case '\n':
		return INPUT_NEWLINE;
	default:
		return INPUT_INVALID;
	}
}

typedef struct {
	unsigned short kind;
	union {
		long number;
		char op;
		int err;
	} val;
} Token;

typedef struct {
	enum lexer_state state;
	Reader *r;
	int c;
	struct {
		int i, line, col;
	} pos;
} Lexer;

Lexer *NewLexer(Reader *r);

Token peek(Lexer *l);
Token lexer_advance(Lexer *l);

#endif /* _LEXER_H */
