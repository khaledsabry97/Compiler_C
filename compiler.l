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
"\""  {return DQUOT_T;}
"\'"  {return SQUOT_T;}
"\&"  {return AMP_T;}
"-"     return MINUS;
"+"     return PLUS;
"*"     return MULT;
"/"     return DIV;
"<="    return LE;
">="    return GE;
">"     return GT;
"<"     return LT;
"=="    return EQ;
"!="    return NE;
int     return INT;
float   return FLOAT;
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
[A-Za-z][A-Za-z0-9_]*   {
    yylval.id = strndup(yytext, yyleng);
    return ID;
}

[ \t\r\n] { break;}

%%
