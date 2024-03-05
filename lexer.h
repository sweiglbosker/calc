#ifndef _LEXER_H
#define _LEXER_H

#include "reader.h"

enum {
	TOKEN_NUMBER,
	TOKEN_LPAREN, 
	TOKEN_RPAREN,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_ASTERIX,
	TOKEN_SLASH,
	TOKEN_PERCENT,
	TOKEN_ERR, 
	TOKEN_EOF 
};


extern const char *TOKEN_NAME[];

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
	int kind;
	union {
		long number;
		char op;
		int err;
	} val;
} Token;

typedef struct TokenList {
	Token token;
	struct TokenList *next;
} TokenList;

typedef struct {
	enum lexer_state state;
	Reader *r;
	int c;
	struct {
		int i, line, col;
	} pos;
} Lexer;

Lexer *NewLexer(Reader *r);
TokenList *Scan(Lexer *l);
Token lexer_advance(Lexer *l);
void PrintToken(Token *t);

#endif /* _LEXER_H */
