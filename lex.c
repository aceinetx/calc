#include <stdio.h>
#include <string.h>
#include "lex.h"

char* lex_in;
unsigned int lex_pos;

static char is_digit(char c){
	return c >= '0' && c <= '9';
}

static struct token lex_number(){
	unsigned int lex_len;
	struct token tok;	

	lex_len = strlen(lex_in);
	tok.value = 0;
	tok.type = TOKEN_NUMBER;

	while(lex_pos < lex_len){
		char c = lex_in[lex_pos];
		if(!is_digit(c)){
			break;
		}

		tok.value *= 10;
		tok.value += c - '0';

		lex_pos++;
	}

	return tok;
}

struct token lex_peek(int fwd){
	unsigned int old_pos;
	int i;
	struct token tok;

	old_pos = lex_pos;

	for(i=0; i<fwd; i++){
		tok = lex_next();
	}

	lex_pos = old_pos;
	return tok;
}

struct token lex_next(){
	unsigned int lex_len;
	struct token tok;	

	lex_len = strlen(lex_in);
	tok.value = 0;
	tok.type = TOKEN_UNDEF;

	while(lex_pos < lex_len){
		char c = lex_in[lex_pos];

		tok.type = TOKEN_UNDEF;
	
		if(c == '+'){
			tok.type = TOKEN_PLUS;
			lex_pos++;
		} else if (c == '-'){
			tok.type = TOKEN_MINUS;
			lex_pos++;
		} else if (c == '*'){
			tok.type = TOKEN_MUL;
			lex_pos++;
		} else if (c == '/'){
			tok.type = TOKEN_DIV;
			lex_pos++;
		} else if (c == '('){
			tok.type = TOKEN_LPAREN;
			lex_pos++;
		} else if (c == ')'){
			tok.type = TOKEN_RPAREN;
			lex_pos++;
		} else if (is_digit(c)){
			tok = lex_number();
		}

		if(tok.type != TOKEN_UNDEF) return tok;

		lex_pos++;
	}

	tok.type = TOKEN_EOF;
	return tok;
}
