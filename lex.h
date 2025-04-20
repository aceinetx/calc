#ifndef LEX_H
#define LEX_H

enum {
	TOKEN_EOF,
	TOKEN_UNDEF,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MUL,
	TOKEN_DIV,
	TOKEN_LPAREN,
	TOKEN_RPAREN
};

struct token {
	char type;
	long value;	
};

extern char* lex_in;

struct token lex_next(void);

#endif
