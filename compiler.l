%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "compiler.tab.h"

%}


%%

"{" |
"}" |
"[" |
"]" |
"(" |
")" |
";" |
"." |
"," |
"=" {return yytext[0];}
"\""  {return DOUBLE_QT;}
"\'"  {return SINGLE_QT;}
"-"     return MINUS;
"+"     return PLUS;
"*"     return MUL;
"/"     return DIV;
"<="    return LE;
">="    return GE;
">"     return GT;
"<"     return LT;
"=="    return EQ;
"!="    return NE;
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

[ \t\c\n] { break;}

%%
