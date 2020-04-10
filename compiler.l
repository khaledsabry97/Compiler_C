%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "compiler.tab.h"
%}



intval [0-9]+
floatval [0-9]+.[0-9]+
id [A-Za-z][A-Za-z0-9_]*     
space [ \t\r\n]


%%

int     return INT;
float   return FLOAT;

if return IF;
else return ELSE;
for return FOR;
while return WHILE;
do return DO;
return return RETURN;

"[" |
"]" |
"{" |
"}" |
"(" |
")" |
";" |
"." |
"," |
"=" {return yytext[0];} //Return the character
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

{intval} {
    yylval.intval = atoi(yytext);
    return INTNUM;
}
{floatval} {
    yylval.floatval = atof(yytext);
    return FLOATNUM;
}
{id}   {
    yylval.id = strndup(yytext, yyleng);
    return ID;
}

{space} { break;}

%%
