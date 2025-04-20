#include "eval.h"
#include "parser.h"
#include "alloclist.h"

long do_virtual(struct node *node);
long do_num(struct node *node);
long do_binop(struct node *node);

long do_num(struct node *node){
	return node->value;
}

long do_binop(struct node *node){
	long left = do_virtual(node->left);
	long right = do_virtual(node->right);

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

long do_virtual(struct node *node){
	switch(node->type){
		case NODE_NUMBER:
			return do_num(node);
		case NODE_BINOP:
			return do_binop(node);
		default: break;
	}
	return 0;
}

long eval(void){
	struct node *node;
	long val;

	node = parse();
	if(!node) return 0;

	val = do_virtual(node);

	free_alloclist();

	return val;
}
