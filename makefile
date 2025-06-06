CFLAGS = -std=c90 -Wall -Wextra -Wpedantic -ggdb -Oz
CC = cc

all: calc

clean:
	rm *.o calc -rf

calc.o: calc.c lex.h eval.h
	$(CC) -c -o calc.o $(CFLAGS) calc.c

lex.o: lex.c lex.h
	$(CC) -c -o lex.o $(CFLAGS) lex.c

parser.o: parser.c parser.h lex.h alloclist.h
	$(CC) -c -o parser.o $(CFLAGS) parser.c

eval.o: eval.c eval.h parser.h alloclist.h
	$(CC) -c -o eval.o $(CFLAGS) eval.c

alloclist.o: alloclist.c alloclist.h
	$(CC) -c -o alloclist.o $(CFLAGS) alloclist.c

calc: calc.o lex.o parser.o eval.o alloclist.o
	$(CC) calc.o lex.o parser.o eval.o alloclist.o -o calc
