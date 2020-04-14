/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "compiler.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "print.h"
#include "symboltable.h"

FILE *tree_file;   //for AST
FILE *table_file;  //for symboltable 

//global variables which can be used in other .c .h
struct PROGRAM *head;
void yyerror(char* text) {

    fprintf(stderr, "%s\n", text);
}

/* void lyyerror(YYLTYPE t, char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    if(t.first_line)
        fprintf(stderr, "%d.%d-%d.%d: error: ", t.first_line, t.first_column, t.last_line, t.last_column);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
} */


#line 97 "compiler.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "compiler.tab.h".  */
#ifndef YY_YY_COMPILER_TAB_H_INCLUDED
# define YY_YY_COMPILER_TAB_H_INCLUDED
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
    MINUS = 263,
    PLUS = 264,
    MUL = 265,
    DIV = 266,
    LE = 267,
    GE = 268,
    EQ = 269,
    NE = 270,
    GT = 271,
    LT = 272,
    IF = 273,
    ELSE = 274,
    FOR = 275,
    WHILE = 276,
    DO = 277,
    RETURN = 278,
    DOUBLE_QT = 279,
    SINGLE_QT = 280,
    UNARY = 281,
    LOWER_THAN_ELSE = 282
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 32 "compiler.y" /* yacc.c:355  */

    ID_TYPE type;
    char* id;
    int intval;
    float floatval;
    

    struct PROGRAM       *_program;
    struct DECLARATION   *_declaration;
    struct IDENTIFIER    *_identifier;
    struct FUNCTION      *_function;
    struct PARAMETER     *_parameter;
    struct ARG           *_arg;

    struct FUNC_CALL          *_call;
    struct IF_STMT          *_if_stmt;
    struct FOR_STMT         *_for_stmt;
    struct WHILE_STMT       *_while_stmt;
    struct ASSIGN_STMT        *_assign_stmt;
    struct STMTSGROUP  *_stmtgroup;
    struct STMT          *_stmt;

    struct ID_EXPR          *_id_expr;
    struct ADD_OP        *_add_op;
    struct MUL_OP        *_mul_op;
    struct EQL_OP        *_eql_op;

    struct COM_OP        *_com_op;
    struct EXPR          *_expr;



#line 198 "compiler.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 215 "compiler.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   321

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  139

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,    29,     2,     2,    32,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,    26,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    27,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   129,   129,   136,   143,   151,   154,   161,   170,   173,
     180,   187,   196,   199,   207,   213,   219,   226,   235,   244,
     245,   249,   260,   266,   272,   279,   285,   292,   298,   304,
     310,   316,   322,   328,   334,   340,   344,   351,   359,   367,
     373,   380,   381,   388,   395,   398,   402,   412,   423,   434,
     445,   456,   462,   468,   474,   480,   487,   493,   500,   505,
     512,   517,   523,   528,   533,   538,   544,   549,   555,   562,
     570,   579,   586
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTNUM", "FLOATNUM", "INT",
  "FLOAT", "MINUS", "PLUS", "MUL", "DIV", "LE", "GE", "EQ", "NE", "GT",
  "LT", "IF", "ELSE", "FOR", "WHILE", "DO", "RETURN", "DOUBLE_QT",
  "SINGLE_QT", "'='", "UNARY", "'('", "')'", "LOWER_THAN_ELSE", "';'",
  "','", "'['", "']'", "'{'", "'}'", "$accept", "Program",
  "Declaration_List", "Declaration", "Identifier_List", "Identifier",
  "Function_List", "Parameter_List", "Parameter", "Function", "Type",
  "Stmt_Group", "Stmt_List", "Stmt", "Assign_Stmt", "Assign", "Call_Stmt",
  "Call", "Arg_List", "Arg", "Ret_Stmt", "Expr", "Id_Expr", "Add_Op",
  "Mul_Op", "Com_Op", "Eql_Op", "While_Stmt", "For_Stmt", "If_Stmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    61,   281,    40,    41,
     282,    59,    44,    91,    93,   123,   125
};
# endif

#define YYPACT_NINF -60

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-60)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      60,   -60,   -60,    11,    60,   -60,    60,   -60,    12,   -60,
     -60,    60,   -60,    31,     3,    50,   -60,    29,     0,    34,
     -60,    37,    33,    32,   -60,    37,    40,    52,   -60,    89,
     -60,    33,    60,   -60,   -60,    26,    55,    59,    69,   137,
     145,   -60,   -60,   110,    37,   -60,    27,   -60,   -60,    67,
     -60,    70,   -60,   -60,   -60,   -60,   -60,   -60,    86,    15,
      86,    86,    97,    86,    82,    23,   -60,   -60,    86,    86,
     -60,   -60,   206,   -60,   -60,   116,   -60,   -60,   -60,   -60,
     304,   -60,    47,   -60,   304,   169,   240,   -21,    73,   250,
      77,    86,   -60,   272,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,    86,    86,    86,    86,   -60,
     -60,    86,    80,   137,    86,   137,    86,   179,   -60,   304,
     304,   304,   304,   -60,    86,    96,   216,   -60,   282,   -60,
     304,   137,    97,    87,   -60,    92,   -60,   137,   -60
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    19,    20,     0,     3,     5,     4,    12,     0,     1,
       6,     2,    13,     0,    10,     0,     8,     0,     0,     0,
       7,     0,     0,     0,    14,     0,     0,    10,     9,     0,
      17,     0,     0,    16,    11,     0,     0,     0,     0,     0,
       0,    34,    21,     0,     0,    33,     0,    25,    27,     0,
      28,     0,    29,    30,    31,    32,    18,    15,     0,     0,
       0,     0,     0,     0,     0,    56,    52,    53,     0,     0,
      44,    51,     0,    54,    24,     0,    22,    26,    35,    38,
      36,    39,     0,    41,    43,     0,     0,     0,     0,     0,
       0,     0,    46,     0,    58,    59,    60,    61,    62,    63,
      66,    67,    64,    65,    45,     0,     0,     0,     0,    23,
      40,     0,     0,     0,     0,     0,     0,     0,    55,    47,
      48,    49,    50,    42,     0,    71,     0,    68,     0,    57,
      37,     0,     0,     0,    72,     0,    69,     0,    70
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,    93,    -2,   -60,   -12,   119,   -60,    94,    54,
      10,     4,    84,   -38,   -60,   -59,   -60,   -29,   -60,    18,
     -60,   -36,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    15,    16,     6,    23,    24,     7,
       8,    45,    46,    47,    48,    49,    50,    71,    82,    83,
      52,    84,    73,   105,   106,   107,   108,    53,    54,    55
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      51,    64,    10,    88,    72,    58,     1,     2,    77,    28,
      51,     9,    60,    33,    51,    14,    13,    51,    65,    66,
      67,    13,    80,    68,    85,    86,    30,    89,    25,    22,
      35,    18,    92,    93,    17,    56,    19,    77,    26,    44,
      27,    10,    25,    69,    81,    36,    51,    37,    38,    39,
      40,    59,    58,    44,    59,   117,    91,    18,    41,    60,
      12,    31,    29,    76,    32,    12,     1,     2,    29,   119,
     120,   121,   122,   135,    34,   125,   110,   127,   126,   111,
     128,    20,    21,    61,    51,    19,    51,    62,   130,    65,
      66,    67,    35,   134,    68,     1,     2,    63,    78,   138,
      87,    79,    51,    90,   114,   116,   124,    36,    51,    37,
      38,    39,    40,    35,    69,   131,     1,     2,   136,    35,
      41,   137,    43,    11,    29,    42,    57,    75,    36,   123,
      37,    38,    39,    40,    36,     0,    37,    38,    39,    40,
      35,    41,     0,     0,     0,    29,    74,    41,    65,    66,
      67,    29,   109,    68,     0,    36,     0,    37,    38,    39,
      40,     0,     0,     0,     0,     0,     0,     0,    41,     0,
       0,     0,    29,    69,     0,     0,    70,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,     0,     0,   112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,   118,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103
};

static const yytype_int16 yycheck[] =
{
      29,    39,     4,    62,    40,    26,     6,     7,    46,    21,
      39,     0,    33,    25,    43,     3,     6,    46,     3,     4,
       5,    11,    58,     8,    60,    61,    22,    63,    18,    29,
       3,    28,    68,    69,     3,    31,    33,    75,     4,    29,
       3,    43,    32,    28,    29,    18,    75,    20,    21,    22,
      23,    28,    26,    43,    28,    91,    33,    28,    31,    33,
       6,    29,    35,    36,    32,    11,     6,     7,    35,   105,
     106,   107,   108,   132,    34,   113,    29,   115,   114,    32,
     116,    31,    32,    28,   113,    33,   115,    28,   124,     3,
       4,     5,     3,   131,     8,     6,     7,    28,    31,   137,
       3,    31,   131,    21,    31,    28,    26,    18,   137,    20,
      21,    22,    23,     3,    28,    19,     6,     7,    31,     3,
      31,    29,    29,     4,    35,    36,    32,    43,    18,   111,
      20,    21,    22,    23,    18,    -1,    20,    21,    22,    23,
       3,    31,    -1,    -1,    -1,    35,    36,    31,     3,     4,
       5,    35,    36,     8,    -1,    18,    -1,    20,    21,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    35,    28,    -1,    -1,    31,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    38,    39,    40,    43,    46,    47,     0,
      40,    43,    46,    47,     3,    41,    42,     3,    28,    33,
      31,    32,    29,    44,    45,    47,     4,     3,    42,    35,
      48,    29,    32,    42,    34,     3,    18,    20,    21,    22,
      23,    31,    36,    39,    47,    48,    49,    50,    51,    52,
      53,    54,    57,    64,    65,    66,    48,    45,    26,    28,
      33,    28,    28,    28,    50,     3,     4,     5,     8,    28,
      31,    54,    58,    59,    36,    49,    36,    50,    31,    31,
      58,    29,    55,    56,    58,    58,    58,     3,    52,    58,
      21,    33,    58,    58,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    31,    60,    61,    62,    63,    36,
      29,    32,    34,    29,    31,    29,    28,    58,    29,    58,
      58,    58,    58,    56,    26,    50,    58,    50,    58,    34,
      58,    19,    31,    29,    50,    52,    31,    29,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    38,    38,    39,    39,    40,    41,    41,
      42,    42,    43,    43,    44,    44,    45,    46,    46,    47,
      47,    48,    48,    48,    48,    49,    49,    50,    50,    50,
      50,    50,    50,    50,    50,    51,    52,    52,    53,    54,
      54,    55,    55,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     2,     3,     1,     3,
       1,     4,     1,     2,     1,     3,     2,     5,     6,     1,
       1,     2,     3,     4,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     6,     2,     3,
       4,     1,     3,     1,     2,     3,     2,     3,     3,     3,
       3,     1,     1,     1,     1,     3,     1,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     7,
       9,     5,     7
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 129 "compiler.y" /* yacc.c:1646  */
    {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->declaration = (yyvsp[-1]._declaration);
            prog->function = (yyvsp[0]._function);
            head = prog;
            (yyval._program) = prog;
       }
#line 1428 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 136 "compiler.y" /* yacc.c:1646  */
    {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->declaration = (yyvsp[0]._declaration);
            prog->function = NULL;
            head = prog;
            (yyval._program) = prog;
       }
#line 1440 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 143 "compiler.y" /* yacc.c:1646  */
    {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->declaration = NULL;
            prog->function = (yyvsp[0]._function);
            head = prog;
            (yyval._program) = prog;
       }
#line 1452 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 151 "compiler.y" /* yacc.c:1646  */
    {
            (yyval._declaration) = (yyvsp[0]._declaration);
        }
#line 1460 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 154 "compiler.y" /* yacc.c:1646  */
    {
            struct DECLARATION *declaration;
            declaration = (yyvsp[0]._declaration);
            declaration->prev = (yyvsp[-1]._declaration);
            (yyval._declaration) = declaration;
        }
#line 1471 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 161 "compiler.y" /* yacc.c:1646  */
    {
                struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
                declaration->id_type = (yyvsp[-2].type);
                declaration->id = (yyvsp[-1]._identifier);
                (yyval._declaration) = declaration;
            }
#line 1482 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 170 "compiler.y" /* yacc.c:1646  */
    {
            (yyval._identifier) = (yyvsp[0]._identifier);
        }
#line 1490 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 173 "compiler.y" /* yacc.c:1646  */
    {
            struct IDENTIFIER *iden;
            iden = (yyvsp[0]._identifier);
            iden->prev = (yyvsp[-2]._identifier);
            (yyval._identifier) = iden;
        }
#line 1501 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 180 "compiler.y" /* yacc.c:1646  */
    {
            struct IDENTIFIER *iden = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            iden->ID = (yyvsp[0].id);
            iden->int_val = 0;   // zero, If scalar
            iden->prev = NULL;
            (yyval._identifier) = iden;
          }
#line 1513 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 187 "compiler.y" /* yacc.c:1646  */
    {
            struct IDENTIFIER *iden = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            iden->ID = (yyvsp[-3].id);
            iden->int_val = (yyvsp[-1].intval);   // zero, If scalar
            iden->prev = NULL;
            (yyval._identifier) = iden;
           }
#line 1525 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 196 "compiler.y" /* yacc.c:1646  */
    {
            (yyval._function) = (yyvsp[0]._function);
        }
#line 1533 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 199 "compiler.y" /* yacc.c:1646  */
    {
            struct FUNCTION *function;
            function = (yyvsp[0]._function);
            function->prev = (yyvsp[-1]._function);
            (yyval._function) = function;
        }
#line 1544 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 207 "compiler.y" /* yacc.c:1646  */
    {
            struct PARAMETER *param;
            param = (yyvsp[0]._parameter);
            param->prev = NULL;
            (yyval._parameter) = param;
        }
#line 1555 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 213 "compiler.y" /* yacc.c:1646  */
    {
            struct PARAMETER *param;
            param = (yyvsp[0]._parameter);
            param->prev = (yyvsp[-2]._parameter);
            (yyval._parameter) = param;
        }
#line 1566 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 219 "compiler.y" /* yacc.c:1646  */
    {
            struct PARAMETER *param = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            param->id_type = (yyvsp[-1].type);
            param->id = (yyvsp[0]._identifier);
            param->prev = NULL;
            (yyval._parameter) = param;
        }
#line 1578 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 226 "compiler.y" /* yacc.c:1646  */
    {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = (yyvsp[-4].type);
            function->ID = (yyvsp[-3].id);
            function->param = NULL;
            function->stmts_group = (yyvsp[0]._stmtgroup);
            (yyval._function) = function;

        }
#line 1592 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 235 "compiler.y" /* yacc.c:1646  */
    {
        struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        function->id_type = (yyvsp[-5].type);
        function->ID = (yyvsp[-4].id);
        function->param = (yyvsp[-2]._parameter);
        function->stmts_group = (yyvsp[0]._stmtgroup);
        (yyval._function) = function;
    }
#line 1605 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 244 "compiler.y" /* yacc.c:1646  */
    { (yyval.type) = Int_Type;}
#line 1611 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 245 "compiler.y" /* yacc.c:1646  */
    { (yyval.type) = Float_Type;}
#line 1617 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 249 "compiler.y" /* yacc.c:1646  */
    {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = NULL;
                comp->stmt = NULL;
                (yyval._stmtgroup) = comp;
                /*
                { } 안에 { } 만 들어 있는 경우도 표현하기 위하여,
                NULL을 반환하지 않고 내용이 비어있어도 동적할당을 하였다.
                */
                
            }
#line 1633 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 260 "compiler.y" /* yacc.c:1646  */
    {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = NULL;
                comp->stmt = (yyvsp[-1]._stmt);
                (yyval._stmtgroup) = comp;
            }
#line 1644 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 266 "compiler.y" /* yacc.c:1646  */
    {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = (yyvsp[-2]._declaration);
                comp->stmt = (yyvsp[-1]._stmt);
                (yyval._stmtgroup) = comp;
            }
#line 1655 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 272 "compiler.y" /* yacc.c:1646  */
    {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = (yyvsp[-1]._declaration);
                comp->stmt = NULL;
                (yyval._stmtgroup) = comp;
            }
#line 1666 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 279 "compiler.y" /* yacc.c:1646  */
    {
            struct STMT *stmt;
            stmt = (yyvsp[0]._stmt);
            stmt->prev = NULL;
            (yyval._stmt) = stmt;
        }
#line 1677 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 285 "compiler.y" /* yacc.c:1646  */
    {
            struct STMT *stmt;
            stmt = (yyvsp[0]._stmt);
            stmt->prev = (yyvsp[-1]._stmt);
            (yyval._stmt) = stmt;
        }
#line 1688 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 292 "compiler.y" /* yacc.c:1646  */
    { 
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Equ_Type;
        stmt->stmt.assign_stmt = (yyvsp[0]._assign_stmt);
        (yyval._stmt) = stmt;
    }
#line 1699 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 298 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Call_Type;
        stmt->stmt.func_call = (yyvsp[0]._call);
        (yyval._stmt) = stmt;
    }
#line 1710 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 304 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Return_Type;
        stmt->stmt.return_expr = (yyvsp[0]._expr);
        (yyval._stmt) = stmt;
    }
#line 1721 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 310 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = While_Type;
        stmt->stmt.while_stmt = (yyvsp[0]._while_stmt);
        (yyval._stmt) = stmt;
    }
#line 1732 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 316 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = For_Type;
        stmt->stmt.for_stmt = (yyvsp[0]._for_stmt);
        (yyval._stmt) = stmt;
    }
#line 1743 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 322 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = If_Type;
        stmt->stmt.if_stmt = (yyvsp[0]._if_stmt);
        (yyval._stmt) = stmt;
    }
#line 1754 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 328 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Comp_Type;
        stmt->stmt.stmts_group = (yyvsp[0]._stmtgroup);
        (yyval._stmt) = stmt;
    }
#line 1765 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 334 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Semi_Type;
        (yyval._stmt) = stmt;
    }
#line 1775 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 340 "compiler.y" /* yacc.c:1646  */
    { 
            (yyval._assign_stmt) = (yyvsp[-1]._assign_stmt);
          }
#line 1783 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 344 "compiler.y" /* yacc.c:1646  */
    {
            struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            assign->ID = (yyvsp[-2].id);
            assign->index = NULL; //NUL, if LHS is scalar variable
            assign->expr = (yyvsp[0]._expr);
            (yyval._assign_stmt) = assign;
        }
#line 1795 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 351 "compiler.y" /* yacc.c:1646  */
    {
            struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            assign->ID = (yyvsp[-5].id);
            assign->index = (yyvsp[-3]._expr); 
            assign->expr = (yyvsp[0]._expr);
            (yyval._assign_stmt) = assign;
        }
#line 1807 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 359 "compiler.y" /* yacc.c:1646  */
    {
            (yyval._call) = (yyvsp[-1]._call);
        }
#line 1815 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 367 "compiler.y" /* yacc.c:1646  */
    {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = (yyvsp[-2].id);
        call->arg = NULL;
        (yyval._call) = call;
    }
#line 1826 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 373 "compiler.y" /* yacc.c:1646  */
    {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = (yyvsp[-3].id);
        call->arg = (yyvsp[-1]._arg);
        (yyval._call) = call;
    }
#line 1837 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 380 "compiler.y" /* yacc.c:1646  */
    { (yyval._arg) = (yyvsp[0]._arg);}
#line 1843 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 381 "compiler.y" /* yacc.c:1646  */
    {
            struct ARG *arg;
            arg = (yyvsp[0]._arg);
            arg->prev = (yyvsp[-2]._arg);
            (yyval._arg) = arg;
        }
#line 1854 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 388 "compiler.y" /* yacc.c:1646  */
    {
    struct ARG *arg = (struct ARG*) malloc (sizeof (struct ARG));
    arg->expr = (yyvsp[0]._expr);
    arg->prev = NULL;
    (yyval._arg) = arg;
   }
#line 1865 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 395 "compiler.y" /* yacc.c:1646  */
    {
        (yyval._expr) = NULL;
        }
#line 1873 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 398 "compiler.y" /* yacc.c:1646  */
    {
        (yyval._expr) = (yyvsp[-1]._expr);
       }
#line 1881 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 402 "compiler.y" /* yacc.c:1646  */
    {
        struct UNI_OP *unop = (struct UNI_OP*) malloc (sizeof (struct UNI_OP));
        unop->uni_type = Neg_Type;
        unop->expr = (yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Uni_Type;
        expr->expression.uni_op = unop;
        (yyval._expr) = expr;
    }
#line 1896 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 412 "compiler.y" /* yacc.c:1646  */
    {
        struct ADD_OP *addiop;
        addiop = (yyvsp[-1]._add_op);
        addiop->left_side=(yyvsp[-2]._expr);
        addiop->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = addiop;
        (yyval._expr) = expr;
    }
#line 1912 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 423 "compiler.y" /* yacc.c:1646  */
    {
        struct MUL_OP *multop;
        multop = (yyvsp[-1]._mul_op);
        multop->left_side=(yyvsp[-2]._expr);
        multop->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Mult_Type;   // eMult와 다름 
        expr->expression.mul_op = multop;
        (yyval._expr) = expr;
    }
#line 1928 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 434 "compiler.y" /* yacc.c:1646  */
    {
        struct COM_OP *relaop;
        relaop = (yyvsp[-1]._com_op);
        relaop->left_side=(yyvsp[-2]._expr);
        relaop->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = relaop;
        (yyval._expr) = expr;
    }
#line 1944 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 445 "compiler.y" /* yacc.c:1646  */
    {
        struct EQL_OP *eqltop;
        eqltop = (yyvsp[-1]._eql_op);
        eqltop->left_side=(yyvsp[-2]._expr);
        eqltop->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Eql_Type;  
        expr->expression.eql_op = eqltop;
        (yyval._expr) = expr;
    }
#line 1960 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 456 "compiler.y" /* yacc.c:1646  */
    {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = CallExpr_Type;  
        expr->expression.func_call = (yyvsp[0]._call);
        (yyval._expr) = expr;
    }
#line 1971 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 462 "compiler.y" /* yacc.c:1646  */
    {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = IntNum_Type;  
        expr->expression.int_val = (yyvsp[0].intval);
        (yyval._expr) = expr;
    }
#line 1982 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 468 "compiler.y" /* yacc.c:1646  */
    {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = FloatNum_Type;  
        expr->expression.floatval = (yyvsp[0].floatval);
        (yyval._expr) = expr;
    }
#line 1993 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 474 "compiler.y" /* yacc.c:1646  */
    {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Id_Type;  
        expr->expression.id_expr = (yyvsp[0]._id_expr);
        (yyval._expr) = expr;
    }
#line 2004 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 480 "compiler.y" /* yacc.c:1646  */
    {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Expr_Type;  
        expr->expression.bracket = (yyvsp[-1]._expr);
        (yyval._expr) = expr;
    }
#line 2015 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 487 "compiler.y" /* yacc.c:1646  */
    {
        struct ID_EXPR *id_s = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_s->ID = (yyvsp[0].id);
        id_s->expr = NULL;
        (yyval._id_expr) = id_s;
    }
#line 2026 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 493 "compiler.y" /* yacc.c:1646  */
    {
        struct ID_EXPR *id_s = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_s->ID = (yyvsp[-3].id);
        id_s->expr = (yyvsp[-1]._expr);
        (yyval._id_expr) = id_s;
    }
#line 2037 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 500 "compiler.y" /* yacc.c:1646  */
    {
         struct ADD_OP *addiop = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
         addiop->add_type = Minus_Type;
         (yyval._add_op) = addiop;
      }
#line 2047 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 505 "compiler.y" /* yacc.c:1646  */
    { 
        struct ADD_OP *addiop = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        addiop->add_type = Plus_Type;
      (yyval._add_op) = addiop;
      }
#line 2057 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 512 "compiler.y" /* yacc.c:1646  */
    {
         struct MUL_OP *multop = (struct MUL_OP*) malloc (sizeof (struct MUL_OP));
         multop->mul_type = Mul_Type;
         (yyval._mul_op) = multop;
      }
#line 2067 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 517 "compiler.y" /* yacc.c:1646  */
    {
         struct MUL_OP *multop = (struct MUL_OP*) malloc (sizeof (struct MUL_OP));
         multop->mul_type = Div_Type;
         (yyval._mul_op) = multop;
      }
#line 2077 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 523 "compiler.y" /* yacc.c:1646  */
    {
         struct COM_OP *relaop = (struct COM_OP*) malloc (sizeof (struct COM_OP));
         relaop->com_type = Le_Type;
         (yyval._com_op) = relaop;
      }
#line 2087 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 528 "compiler.y" /* yacc.c:1646  */
    {
         struct COM_OP *relaop = (struct COM_OP*) malloc (sizeof (struct COM_OP));
         relaop->com_type = Ge_Type;
         (yyval._com_op) = relaop;
      }
#line 2097 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 533 "compiler.y" /* yacc.c:1646  */
    {
         struct COM_OP *relaop = (struct COM_OP*) malloc (sizeof (struct COM_OP));
         relaop->com_type = Gt_Type;
         (yyval._com_op) = relaop;
      }
#line 2107 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 538 "compiler.y" /* yacc.c:1646  */
    { 
         struct COM_OP *relaop = (struct COM_OP*) malloc (sizeof (struct COM_OP));
         relaop->com_type = Lt_Type;
         (yyval._com_op) = relaop;
      }
#line 2117 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 544 "compiler.y" /* yacc.c:1646  */
    {
         struct EQL_OP *eqltop = (struct EQL_OP*) malloc (sizeof (struct EQL_OP));
         eqltop->eql_type = Eq_Type;
         (yyval._eql_op) = eqltop;
      }
#line 2127 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 549 "compiler.y" /* yacc.c:1646  */
    { 
         struct EQL_OP *eqltop = (struct EQL_OP*) malloc (sizeof (struct EQL_OP));
         eqltop->eql_type = Ne_Type;
         (yyval._eql_op) = eqltop;
      }
#line 2137 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 555 "compiler.y" /* yacc.c:1646  */
    {
           struct WHILE_STMT* while_s = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
           while_s->do_while = false;
           while_s->condition = (yyvsp[-2]._expr);
           while_s->stmt = (yyvsp[0]._stmt);
           (yyval._while_stmt) = while_s;
        }
#line 2149 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 562 "compiler.y" /* yacc.c:1646  */
    {
           struct WHILE_STMT* while_s = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
           while_s->do_while = true;
           while_s->condition = (yyvsp[-2]._expr);
           while_s->stmt = (yyvsp[-5]._stmt);
           (yyval._while_stmt) = while_s;
        }
#line 2161 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 570 "compiler.y" /* yacc.c:1646  */
    {
           struct FOR_STMT *for_s = (struct FOR_STMT*) malloc (sizeof(struct FOR_STMT));
           for_s->init = (yyvsp[-6]._assign_stmt);
           for_s->condition = (yyvsp[-4]._expr);
           for_s->inc = (yyvsp[-2]._assign_stmt);
           for_s->stmt = (yyvsp[0]._stmt);
           (yyval._for_stmt) = for_s;
        }
#line 2174 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 579 "compiler.y" /* yacc.c:1646  */
    {
       struct IF_STMT *if_ptr = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_ptr->condition=(yyvsp[-2]._expr);
       if_ptr->if_stmt=(yyvsp[0]._stmt);
       if_ptr->else_stmt=NULL;
       (yyval._if_stmt) = if_ptr;
    }
#line 2186 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 586 "compiler.y" /* yacc.c:1646  */
    {
       struct IF_STMT *if_ptr = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_ptr->condition=(yyvsp[-4]._expr);
       if_ptr->if_stmt=(yyvsp[-2]._stmt);
       if_ptr->else_stmt=(yyvsp[0]._stmt);
       (yyval._if_stmt) = if_ptr;
      }
#line 2198 "compiler.tab.c" /* yacc.c:1646  */
    break;


#line 2202 "compiler.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 594 "compiler.y" /* yacc.c:1906  */

void doProcess();
int main(int argc, char* argv[]) {
    head = NULL;
    scopeHead = NULL;
    scopeTail = NULL;
    //print AST
    tree_file = fopen("tree.txt","w");
    table_file = fopen("table.txt","w");
    if(!yyparse())
        doProcess();
    fprintf(tree_file, "\n");
    close(tree_file);
    close(table_file);
    return 0;
}
void doProcess() {
    //TODO
    if(head == NULL)
        exit(1);
    //make global node
    scopeHead = newScope(sGLOBAL, NULL);
    scopeTail = scopeHead;
    if(head->declaration != NULL)
        visitDeclaration(head->declaration);
    if(head->function != NULL)
        visitFunction(head->function);
}
