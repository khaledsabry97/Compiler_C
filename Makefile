all:
	flex Compiler.l 
	bison -d Compiler.y
	gcc -o Compiler Compiler.tab.c Compiler.c lex.yy.c -g -lfl 


clean:
	rm -rf lex.yy.c Compiler.tab.c Compiler.tab.h Compiler assembly_file.txt symbol_file.txt semantic_file.txt

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

	