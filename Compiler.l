%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Abstract_Tree.h"
#include "compiler.tab.h"

%}


%%

"{" return '{';
"}" return '}';
"(" return '(';
")" return ')';
";" return ';';
"." return '.';
"," return ',';
"=" return '=';
"-"     return MINUS;
"+"     return PLUS;
"*"     return MUL;
"/"     return DIV;
"<="    return LE;
">="    return GE;
"<"     return LT;
">"     return GT;
"=="    return EQ;
"!="    return NE;
"++"    return PP;
"--"    return MM;
int     return INT;
float   return FLOAT;
const return CONST;
if return IF;
else return ELSE;
do return DO;
while return WHILE;
for return FOR;
return return RETURN;

[0-9]+ {
    yylval.intval = atoi(yytext);
    return INTNUM;
}
[0-9]+.[0-9]+ {
    yylval.floatval = atof(yytext);
    return FLOATNUM;
}
[A-Za-z][A-Za-z0-9_]*  {
    yylval.id = strndup(yytext, yyleng);
    return ID;
}

[ \t\c] { break;}
"\n" {printf("%d Parsing\n",line_counter++);  break;}
[0-9]+[A-Za-z]+ {printf("WARNING at line %d : you can't start your identifier with a number %s \n",line_counter,yytext);
yylval.id = strndup(yytext, yyleng);
    return ID;}

%%
