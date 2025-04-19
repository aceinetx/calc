#ifndef PARSER_H
#define PARSER_H

enum {
	NODE_NUMBER,
	NODE_BINOP
};

enum {
	BINOP_ADD,
	BINOP_SUB,
	BINOP_MUL,
	BINOP_DIV
};

struct node {
	char type;
	int value;

	struct node *left;
	struct node *right;
	char binop_type;
};

struct node* parse(void);

#endif
