all:
	flex compiler.l 
	bison -d compiler.y
	gcc -o compiler compiler.tab.c print.c lex.yy.c -g -lfl 

clean:
	rm -rf lex.yy.c compiler.tab.c compiler.tab.h compiler assembly_file.txt symbol_file.txt semantic_file.txt

test1:
	make
	./compiler < test1.c

	