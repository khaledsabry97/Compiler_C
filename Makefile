all:
	flex compiler.l
	bison -d compiler.y
	gcc -o compiler compiler.tab.c print.c lex.yy.c -g -lfl 
	./compiler < sa1.txt
	./compiler < sa2.txt
	./compiler < sa3.txt
	./compiler < sa4.txt
	./compiler < sa6.txt
	./compiler < sa5.c
	gcc –S sa5.c

clean:
	rm -rf lex.yy.c compiler.tab.c compiler.tab.h compiler tree.txt table.txt
