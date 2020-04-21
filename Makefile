all:
	flex compiler.l 
	bison -d compiler.y
	gcc -o compiler compiler.tab.c print.c lex.yy.c -g -lfl 
	./compiler < sa5.c
	./compiler < sa1.txt
	./compiler < sa2.txt
	./compiler < test7-while.c
	./compiler < test9_multiple_variable_declaration.c
	./compiler < sa3.txt
	
	


clean:
	rm -rf lex.yy.c compiler.tab.c compiler.tab.h compiler assembly_file.txt symbol_file.txt semantic_file.txt
