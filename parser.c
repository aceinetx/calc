#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lex.h"
#include "alloclist.h"

static struct token tok;

static struct node *parse_number();
static struct node *parse_factor();
static struct node *parse_term();
static struct node *parse_expression();

static struct node *parse_number(){
	struct node *node;

	if(tok.type != TOKEN_NUMBER){
		printf("expected number\n");
		return NULL;
	}

	node = malloc(sizeof(struct node));
	node->type = NODE_NUMBER;
	node->value = tok.value;
	node->left = NULL;
	node->right = NULL;
	tok = lex_next();

	add_alloclist(node);
	return node;
}

static struct node *parse_factor(){
	if(tok.type == TOKEN_LPAREN){
		struct node *expr;
		tok = lex_next();
		expr = parse_expression();
		if(!expr) return NULL;

		if(tok.type != TOKEN_RPAREN){
			printf("expected '('\n");
			free(expr);
			return NULL;
		}

		tok = lex_next();
		return expr;
	}

	return parse_number();
}

static struct node *parse_term(){
	struct token op;
	struct node *left_inner, *left, *right;
	
	left_inner = parse_factor();
	if(!left_inner) return NULL;

	op = tok;
	while(op.type == TOKEN_MUL || op.type == TOKEN_DIV){
		tok = lex_next();
	
		right = parse_factor();
		if(!right) return NULL;

		switch(op.type){
			case TOKEN_MUL:
				left = malloc(sizeof(struct node));
				left->type = NODE_BINOP;
				left->binop_type = BINOP_MUL;
				left->left = left_inner;
				left->right = right;
				left_inner = left;
				add_alloclist(left);
			break;
			case TOKEN_DIV:
				left = malloc(sizeof(struct node));
				left->type = NODE_BINOP;
				left->binop_type = BINOP_DIV;
				left->left = left_inner;
				left->right = right;
				left_inner = left;
				add_alloclist(left);
			break;
			default: break;
		}
		op = tok;
	}

	return left_inner;
}

static struct node *parse_expression(){
	struct node *left_inner, *left, *right;
	struct token op;

	left_inner = parse_term();
	if(!left_inner) return NULL;

	op = tok;
	while(op.type == TOKEN_PLUS || op.type == TOKEN_MINUS){
		tok = lex_next();

		right = parse_term();
		if(!right) return NULL;

		switch(op.type){
			case TOKEN_PLUS:
				left = malloc(sizeof(struct node));
				left->type = NODE_BINOP;
				left->binop_type = BINOP_ADD;
				left->left = left_inner;
				left->right = right;
				left_inner = left;
				add_alloclist(left);
			break;
			case TOKEN_MINUS:
				left = malloc(sizeof(struct node));
				left->type = NODE_BINOP;
				left->binop_type = BINOP_SUB;
				left->left = left_inner;
				left->right = right;
				left_inner = left;
				add_alloclist(left);
			break;
			default: break;
		}

		op = tok;
	}

	return left_inner;
}

struct node* parse(){
	tok = lex_next();
	while(tok.type != TOKEN_EOF){
		return parse_expression();
	}

	return NULL;
}
