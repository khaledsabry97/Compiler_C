/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTNUM = 259,
    FLOATNUM = 260,
    INT = 261,
    FLOAT = 262,
    CONST = 263,
    MINUS = 264,
    MM = 265,
    PLUS = 266,
    PP = 267,
    MUL = 268,
    DIV = 269,
    LE = 270,
    GE = 271,
    EQ = 272,
    NE = 273,
    GT = 274,
    LT = 275,
    IF = 276,
    ELSE = 277,
    FOR = 278,
    WHILE = 279,
    DO = 280,
    RETURN = 281,
    UMINUS = 282,
    IFX = 283
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "parser.y" /* yacc.c:1909  */

    ID_TYPE type;
    char* id;
    int intval;
    float floatval;
    

    struct PROGRAM       *_program;
    struct DECLARATION   *_declaration;
    struct FUNCTION      *_function;
    struct PARAMETER     *_parameter;
    struct ARG           *_arg;


    struct STMTSGROUP  *_stmtgroup;
    struct STMT          *_stmt;

    struct EXPR          *_expr;



#line 105 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
