#include "eval.h"
#include "parser.h"
#include "alloclist.h"

int do_virtual(struct node *node);
int do_num(struct node *node);
int do_binop(struct node *node);

int do_num(struct node *node){
	return node->value;
}

int do_binop(struct node *node){
	int left = do_virtual(node->left);
	int right = do_virtual(node->right);

	switch(node->binop_type){
		case BINOP_ADD:
			return left+right;
		case BINOP_SUB:
			return left-right;
		case BINOP_MUL:
			return left*right;
		case BINOP_DIV:
			return left/right;
		default: break;
	}

	return 0;
}

int do_virtual(struct node *node){
	switch(node->type){
		case NODE_NUMBER:
			return do_num(node);
		case NODE_BINOP:
			return do_binop(node);
		default: break;
	}
	return 0;
}

int eval(void){
	struct node *node;
	int val;

	node = parse();
	if(!node) return 0;

	val = do_virtual(node);

	free_alloclist();

	return val;
}
