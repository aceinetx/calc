#include <stdio.h>
#include <string.h>
#include "lex.h"
#include "parser.h"
#include "eval.h"

int main(int argc, char** argv){
	FILE* fp;
	char buf[1024];
	int c;
	unsigned int count;

	count = 0;
	memset(buf, 0, sizeof(buf));

	if(argc < 2)
		fp = stdin;
	else {
		fp = fopen(argv[1], "r");
		if(!fp){
			perror("fopen() failed");
			return 1;
		}
	}

	while((c = getc(fp)) != EOF && count < sizeof(buf) - 1){
		buf[count] = c;
		count++;	
	}

	lex_in = buf;
	printf("%ld\n", eval());

	if(argc > 1) fclose(fp);
	return 0;
}
