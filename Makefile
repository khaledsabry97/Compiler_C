all:
	flex compiler.l
	bison -d compiler.y
	gcc -o compiler compiler.tab.c print.c lex.yy.c -g -lfl 
	./compiler < sa3.txt





	


clean:
	rm -rf lex.yy.c compiler.tab.c compiler.tab.h compiler tree.txt table.txt semantic_file.txt
