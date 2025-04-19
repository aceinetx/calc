#include <stdlib.h>
#include "alloclist.h"

static void** alloclist = NULL;
static unsigned int alloclist_len = 0;
static unsigned int alloclist_capacity = 0;

void add_alloclist(void* ptr){
	unsigned int i;
	for(i = 0; i < alloclist_len; i++){
		if(alloclist[i] == ptr) return;
	}

	alloclist = realloc(alloclist, alloclist_capacity + sizeof(void*));
	alloclist[alloclist_len] = ptr;

	alloclist_len++;
	alloclist_capacity += sizeof(void*);
}

void free_alloclist(){
	unsigned int i;

	if(!alloclist) return;

	for(i = 0; i < alloclist_len; i++){
		free(alloclist[i]);
	}
	alloclist_len = 0;
	alloclist_capacity = 0;
	free(alloclist);
}
