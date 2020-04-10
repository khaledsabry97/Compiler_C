all:
	flex compiler.l
	bison -d compiler.y
	gcc -o compiler compiler.tab.c print.c symboltable.c lex.yy.c -g -lfl 

clean:
	rm -rf lex.yy.c compiler.tab.c compiler.tab.h compiler tree.txt table.txt
