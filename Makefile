GCC=gcc -g -o

all: lex.yy.c parser

parser: syntax.tab.o symtable.o
	$(GCC) parser symtable.o syntax.tab.o list.c hash.c -ly -ll

syntax.tab.o: syntax.tab.c
	$(GCC) syntax.tab.o -c syntax.tab.c 

symtable.o: symtable.c
	$(GCC) symtable.o -c symtable.c

syntax.tab.c: syntax.y
	bison -d syntax.y

lex.yy.c: modified_lex.lex
	flex -l modified_lex.lex


clean:
	rm -rf *.o syntax.tab.* lex.yy.c parser *~
