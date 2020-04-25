all:
	flex lexer.l 
	bison -d parser.y
	gcc -o compiler compiler.tab.c Compiler.c lex.yy.c -g -lfl 


clean:
	rm -rf lex.yy.c compiler.tab.c compiler.tab.h compiler assembly_file.txt symbol_file.txt semantic_file.txt

test1:
	make
	./compiler < test1.c

test2:
	make
	./compiler < test2.c

test3:
	make
	./compiler < test3.c

test4:
	make
	./compiler < test4.c

	