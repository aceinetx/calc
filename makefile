CFLAGS = -std=c90 -Wall -Wextra -Wpedantic -ggdb

all: calc

clean:
	rm *.o calc

calc.o: calc.c lex.h parser.h eval.h
	gcc -c -o calc.o $(CFLAGS) calc.c

lex.o: lex.c lex.h
	gcc -c -o lex.o $(CFLAGS) lex.c

parser.o: parser.c parser.h lex.h alloclist.h
	gcc -c -o parser.o $(CFLAGS) parser.c

eval.o: eval.c eval.h parser.h alloclist.h
	gcc -c -o eval.o $(CFLAGS) eval.c

alloclist.o: alloclist.c alloclist.h
	gcc -c -o alloclist.o $(CFLAGS) alloclist.c

calc: calc.o lex.o parser.o eval.o alloclist.o
	gcc calc.o lex.o parser.o eval.o alloclist.o -o calc
