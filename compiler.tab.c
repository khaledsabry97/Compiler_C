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
#line 3 "compiler.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Abstract_Tree.h"
#include "print.h"
static int line_counter;

FILE *assembly_file; 
FILE *symbol_file; 
FILE *semantic_file;
static int line_counter;
void process(struct PROGRAM* head);
void openFiles();
void closeFiles();
void yyerror(char* text) {

    fprintf(stderr, "%s\n", text);
}


#line 88 "compiler.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
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
    NO_ELSE = 283
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "compiler.y" /* yacc.c:355  */

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



#line 179 "compiler.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMPILER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 196 "compiler.tab.c" /* yacc.c:358  */

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   478

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

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
      29,    30,     2,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
       2,    27,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      25,    26,    28,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   113,   122,   131,   139,   151,   159,   168,
     176,   187,   197,   208,   214,   222,   223,   224,   225,   231,
     241,   247,   253,   264,   275,   297,   308,   320,   331,   341,
     352,   364,   396,   428,   432,   438,   445,   451,   458,   465,
     467,   473,   483,   494,   505,   516,   527,   537,   548,   559,
     570,   581,   592,   603,   609,   619,   628,   635,   641
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTNUM", "FLOATNUM", "INT",
  "FLOAT", "CONST", "MINUS", "MM", "PLUS", "PP", "MUL", "DIV", "LE", "GE",
  "EQ", "NE", "GT", "LT", "IF", "ELSE", "FOR", "WHILE", "DO", "RETURN",
  "'='", "UMINUS", "'('", "')'", "NO_ELSE", "';'", "','", "'{'", "'}'",
  "$accept", "Program", "Declarations", "Functions", "Parameters", "Args",
  "Type", "Stmt", "Stmt_Group", "Stmt_List", "Expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    61,   282,    40,
      41,   283,    59,    44,   123,   125
};
# endif

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,   -53,   -53,     3,     2,     8,     8,    18,   -53,   -53,
     -53,     8,    42,    58,    -6,    -1,    46,    99,   -53,   -53,
     111,    12,    22,    65,    12,    26,    47,    89,   -53,    12,
       8,   -53,   -53,    12,   -53,    53,    -5,    60,    64,    70,
     254,    15,   -53,   119,   -53,   149,    91,   -53,   194,   -53,
      97,   -53,   -53,   -53,   -53,    62,    62,    98,    62,    78,
      79,   -53,   -53,    62,    62,   -53,   276,   -53,   179,   209,
     -53,   106,   224,    84,   -53,   -53,   -53,   296,   356,   101,
     374,   102,    74,   -53,   392,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,   -53,   -53,   239,   -53,   104,
     -53,   -53,   254,    62,   254,    62,   -53,    39,   446,   -53,
      67,    67,   -53,   -53,   121,   121,   458,   458,   121,   121,
     -53,   115,   316,   -53,   410,   -53,    62,   254,    62,   107,
     446,   -53,   336,   -53,   130,   120,    62,   428,   254,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    15,    16,     0,     0,     3,     4,     0,    17,    18,
       1,     2,     0,     0,     0,     0,     0,     0,     5,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     0,
       0,    11,    10,     0,    39,     0,     0,     0,     0,     0,
       0,     0,    33,     0,    38,     0,     0,    40,     0,     9,
       0,     8,    34,    32,    31,     0,     0,     0,     0,     0,
      58,    56,    57,     0,     0,    20,     0,    30,     0,     0,
      37,     0,     0,     0,    36,    41,    12,     0,     0,     0,
       0,     0,     0,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    29,     0,    28,     0,
      35,    19,     0,     0,     0,     0,    54,     0,    13,    53,
      42,    43,    44,    45,    47,    48,    51,    52,    49,    50,
      27,    22,     0,    25,     0,    55,     0,     0,     0,     0,
      14,    23,     0,    26,     0,     0,     0,     0,     0,    24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,   -53,   -26,   133,   126,   -53,    43,   -40,    25,   -18,
     -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    22,   107,    13,    47,    28,    48,
      66
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    45,    10,    77,    78,    53,    80,    54,    75,     8,
       9,    83,    84,    26,     1,     2,     3,    68,    60,    61,
      62,    14,    55,    17,    63,    69,    18,    72,    17,    75,
     108,    19,    75,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,     7,    64,    15,    27,    65,    12,    32,
      97,   122,    29,   124,    49,    30,    33,    75,    51,    30,
      23,    16,   121,    23,   123,    60,    61,    62,    31,   125,
      46,    63,   126,    50,   130,    20,   132,    60,    61,    62,
      87,    88,    34,    63,   137,    52,    46,   131,    71,    56,
      35,    64,    36,    57,    73,     1,     2,     3,   139,    58,
      76,    79,    81,    64,   106,     1,     2,     3,    82,    99,
      37,    71,    38,    39,    40,    41,    18,     1,     2,     3,
      35,    42,    36,    43,    44,     1,     2,     3,   103,    21,
      85,   105,    86,   135,    87,    88,    19,   127,    11,   133,
      37,    24,    38,    39,    40,    41,    25,   136,     0,     0,
      35,    42,    36,    43,    67,     1,     2,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,    38,    39,    40,    41,     0,     0,     0,     0,
      35,    42,    36,    43,    70,     1,     2,     3,     0,     0,
       0,     0,     0,     0,     0,    35,     0,    36,     0,     0,
      37,     0,    38,    39,    40,    41,     0,     0,     0,     0,
      35,    42,    36,    43,    96,    37,     0,    38,    39,    40,
      41,     0,     0,     0,     0,    35,    42,    36,    43,    74,
      37,     0,    38,    39,    40,    41,     0,     0,     0,     0,
      35,    42,    36,    43,    98,    37,     0,    38,    39,    40,
      41,     0,     0,     0,     0,    35,    42,    36,    43,   100,
      37,     0,    38,    39,    40,    41,     0,     0,     0,     0,
       0,    42,     0,    43,   120,    37,     0,    38,    39,    40,
      41,     0,     0,     0,     0,    85,    42,    86,    43,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,    85,     0,    86,    95,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,    85,     0,    86,   101,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,    85,     0,    86,   128,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,    85,     0,    86,   134,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,    85,     0,    86,   102,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,     0,     0,     0,
       0,    85,     0,    86,   104,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,     0,     0,     0,     0,    85,
       0,    86,   109,    87,    88,    89,    90,    91,    92,    93,
      94,     0,     0,     0,     0,     0,     0,    85,     0,    86,
     129,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,    85,     0,    86,   138,    87,
      88,    89,    90,    91,    92,    93,    94,    85,     0,    86,
       0,    87,    88,    89,    90,     0,     0,    93,    94
};

static const yytype_int16 yycheck[] =
{
      40,    27,     0,    55,    56,    10,    58,    12,    48,     6,
       7,    63,    64,     1,     6,     7,     8,    43,     3,     4,
       5,     3,    27,    29,     9,    43,    32,    45,    29,    69,
      82,    32,    72,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,    29,     3,    34,    32,     5,    24,
      68,   103,    30,   105,    29,    33,    30,    97,    33,    33,
      17,     3,   102,    20,   104,     3,     4,     5,     3,    30,
      27,     9,    33,    30,   126,    29,   128,     3,     4,     5,
      13,    14,    35,     9,   136,    32,    43,   127,    45,    29,
       1,    29,     3,    29,     3,     6,     7,     8,   138,    29,
       3,     3,    24,    29,    30,     6,     7,     8,    29,     3,
      21,    68,    23,    24,    25,    26,    32,     6,     7,     8,
       1,    32,     3,    34,    35,     6,     7,     8,    27,    30,
       9,    29,    11,     3,    13,    14,    32,    22,     5,    32,
      21,    30,    23,    24,    25,    26,    20,    27,    -1,    -1,
       1,    32,     3,    34,    35,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
       1,    32,     3,    34,    35,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,    -1,    -1,
      21,    -1,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
       1,    32,     3,    34,    35,    21,    -1,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,     1,    32,     3,    34,    35,
      21,    -1,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
       1,    32,     3,    34,    35,    21,    -1,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,     1,    32,     3,    34,    35,
      21,    -1,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    34,    35,    21,    -1,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,     9,    32,    11,    34,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,    11,    32,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,    11,    32,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,    11,    32,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,    11,    32,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    -1,    11,    30,    13,    14,    15,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    -1,    11,    30,    13,    14,    15,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      -1,    11,    30,    13,    14,    15,    16,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,     9,    -1,    11,
      30,    13,    14,    15,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    -1,    11,    30,    13,
      14,    15,    16,    17,    18,    19,    20,     9,    -1,    11,
      -1,    13,    14,    15,    16,    -1,    -1,    19,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,    37,    38,    39,    42,     6,     7,
       0,    39,    42,    42,     3,     3,     3,    29,    32,    32,
      29,    30,    40,    42,    30,    40,     1,    34,    44,    30,
      33,     3,    44,    30,    35,     1,     3,    21,    23,    24,
      25,    26,    32,    34,    35,    38,    42,    43,    45,    44,
      42,    44,    32,    10,    12,    27,    29,    29,    29,    43,
       3,     4,     5,     9,    29,    32,    46,    35,    38,    45,
      35,    42,    45,     3,    35,    43,     3,    46,    46,     3,
      46,    24,    29,    46,    46,     9,    11,    13,    14,    15,
      16,    17,    18,    19,    20,    32,    35,    45,    35,     3,
      35,    32,    30,    27,    30,    29,    30,    41,    46,    30,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      35,    43,    46,    43,    46,    30,    33,    22,    32,    30,
      46,    43,    46,    32,    32,     3,    27,    46,    30,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    37,    38,    38,    39,    39,    39,
      39,    40,    40,    41,    41,    42,    42,    42,    42,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    44,    44,    44,    44,    44,
      45,    45,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     3,     4,     5,     7,     6,
       6,     2,     4,     1,     3,     1,     1,     2,     2,     4,
       2,     3,     5,     7,    13,     5,     7,     4,     3,     3,
       2,     2,     2,     1,     2,     4,     3,     3,     2,     2,
       1,     2,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     1,     1,     1
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
#line 104 "compiler.y" /* yacc.c:1646  */
    {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = (yyvsp[-1]._declaration);
            program->function = (yyvsp[0]._function);
            compileProgram(program);
            printf("finally%d\n",line_counter);

            (yyval._program) = program; 
       }
#line 1429 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 113 "compiler.y" /* yacc.c:1646  */
    {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = (yyvsp[0]._declaration);
            program->function = NULL;
            compileProgram(program);
                        printf("finally%d\n",line_counter);

            (yyval._program) = program;
       }
#line 1443 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 122 "compiler.y" /* yacc.c:1646  */
    {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = NULL;
            program->function = (yyvsp[0]._function);
            compileProgram(program);
            printf("finally%d\n",line_counter);
            (yyval._program) = program;
       }
#line 1456 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 131 "compiler.y" /* yacc.c:1646  */
    {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = (yyvsp[-1].id);
            struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
            declaration->id_type = (yyvsp[-2].type);
            declaration->id = identifier;
            (yyval._declaration) = declaration;
        }
#line 1469 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 139 "compiler.y" /* yacc.c:1646  */
    {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = (yyvsp[-1].id);
            struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
            declaration->prev = (yyvsp[-3]._declaration);
            declaration->id_type = (yyvsp[-2].type);
            declaration->id = identifier;
            (yyval._declaration) = declaration;
        }
#line 1483 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 151 "compiler.y" /* yacc.c:1646  */
    {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = (yyvsp[-4].type);
            function->ID = (yyvsp[-3].id);
            function->parameter = NULL;
            function->stmts_group = (yyvsp[0]._stmtgroup);
            (yyval._function) = function;
        }
#line 1496 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 159 "compiler.y" /* yacc.c:1646  */
    {
        struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        function->prev = (yyvsp[-6]._function);
        function->id_type = (yyvsp[-5].type);
        function->ID = (yyvsp[-4].id);
        function->parameter = (yyvsp[-2]._parameter);
        function->stmts_group = (yyvsp[0]._stmtgroup);
        (yyval._function) = function;
    }
#line 1510 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 168 "compiler.y" /* yacc.c:1646  */
    {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = (yyvsp[-5].type);
            function->ID = (yyvsp[-4].id);
            function->parameter = (yyvsp[-2]._parameter);
            function->stmts_group = (yyvsp[0]._stmtgroup);
            (yyval._function) = function;
        }
#line 1523 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 176 "compiler.y" /* yacc.c:1646  */
    {
        struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        function->prev = (yyvsp[-5]._function);
        function->id_type = (yyvsp[-4].type);
        function->ID = (yyvsp[-3].id);
        function->parameter = NULL;
        function->stmts_group = (yyvsp[0]._stmtgroup);
        (yyval._function) = function;
    }
#line 1537 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 187 "compiler.y" /* yacc.c:1646  */
    {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = (yyvsp[0].id);

            struct PARAMETER *parameter = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            parameter->id_type = (yyvsp[-1].type);
            parameter->id = identifier;
            parameter->prev = NULL;
            (yyval._parameter) = parameter;
        }
#line 1552 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 197 "compiler.y" /* yacc.c:1646  */
    {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = (yyvsp[0].id);

            struct PARAMETER *parameter = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            parameter->id_type = (yyvsp[-1].type);
            parameter->id = identifier;
            parameter->prev = (yyvsp[-3]._parameter);
            (yyval._parameter) = parameter;
        }
#line 1567 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 208 "compiler.y" /* yacc.c:1646  */
    { 
    struct ARG *arg = (struct ARG*) malloc (sizeof (struct ARG));
    arg->expr = (yyvsp[0]._expr);
    arg->prev = NULL;
    (yyval._arg) = arg;
    }
#line 1578 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 214 "compiler.y" /* yacc.c:1646  */
    {
    struct ARG *arg = (struct ARG*) malloc (sizeof (struct ARG));
    arg->expr = (yyvsp[0]._expr);
    arg->prev = (yyvsp[-2]._arg);
    (yyval._arg) = arg;
        }
#line 1589 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 222 "compiler.y" /* yacc.c:1646  */
    { (yyval.type) = Int_Type;}
#line 1595 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 223 "compiler.y" /* yacc.c:1646  */
    { (yyval.type) = Float_Type;}
#line 1601 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 224 "compiler.y" /* yacc.c:1646  */
    { (yyval.type) = Const_Int_Type;}
#line 1607 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 225 "compiler.y" /* yacc.c:1646  */
    { (yyval.type) = Const_Float_Type;}
#line 1613 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 231 "compiler.y" /* yacc.c:1646  */
    { 
            struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            assign->ID = (yyvsp[-3].id);
            assign->expr = (yyvsp[-1]._expr);
             
            struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
            stmt->stmt_type = Equ_Type;
            stmt->stmt.assign_stmt = assign;

            (yyval._stmt) = stmt;
    }
#line 1629 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 241 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Return_Type;
        stmt->stmt.return_expr = NULL;
        (yyval._stmt) = stmt;
        }
#line 1640 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 247 "compiler.y" /* yacc.c:1646  */
    {
         struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Return_Type;
        stmt->stmt.return_expr = (yyvsp[-1]._expr);
        (yyval._stmt) = stmt;
       }
#line 1651 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 253 "compiler.y" /* yacc.c:1646  */
    {
       struct IF_STMT *if_stmt = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_stmt->condition=(yyvsp[-2]._expr);
       if_stmt->if_stmt=(yyvsp[0]._stmt);
       if_stmt->else_stmt=NULL;
       
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = If_Type;
        stmt->stmt.if_stmt = if_stmt;
        (yyval._stmt) = stmt;
    }
#line 1667 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 264 "compiler.y" /* yacc.c:1646  */
    {
       struct IF_STMT *if_stmt = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_stmt->condition=(yyvsp[-4]._expr);
       if_stmt->if_stmt=(yyvsp[-2]._stmt);
       if_stmt->else_stmt=(yyvsp[0]._stmt);
       
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = If_Type;
        stmt->stmt.if_stmt = if_stmt;
        (yyval._stmt) = stmt;
      }
#line 1683 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 275 "compiler.y" /* yacc.c:1646  */
    {
            struct ASSIGN_STMT *assign1 = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            struct ASSIGN_STMT *assign2 = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));

            assign1->ID = (yyvsp[-10].id);
            assign1->expr = (yyvsp[-8]._expr);

            assign2->ID = (yyvsp[-4].id);
            assign2->expr = (yyvsp[-2]._expr);
            
          
           struct FOR_STMT *for_stmt = (struct FOR_STMT*) malloc (sizeof(struct FOR_STMT));
           for_stmt->init = assign1;
           for_stmt->condition = (yyvsp[-6]._expr);
           for_stmt->inc = assign2;
           for_stmt->stmt = (yyvsp[0]._stmt);
           
           struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = For_Type;
        stmt->stmt.for_stmt = for_stmt;
        (yyval._stmt) = stmt;
        }
#line 1710 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 297 "compiler.y" /* yacc.c:1646  */
    {
        struct WHILE_STMT* while_stmt = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
        while_stmt->do_while = false;
        while_stmt->condition = (yyvsp[-2]._expr);
        while_stmt->stmt = (yyvsp[0]._stmt);

        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = While_Type;
        stmt->stmt.while_stmt = while_stmt;
        (yyval._stmt) = stmt;
        }
#line 1726 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 308 "compiler.y" /* yacc.c:1646  */
    {
        struct WHILE_STMT* while_stmt = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
        while_stmt->do_while = true;
        while_stmt->condition = (yyvsp[-2]._expr);
        while_stmt->stmt = (yyvsp[-5]._stmt);
           
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = While_Type;
        stmt->stmt.while_stmt = while_stmt;
        (yyval._stmt) = stmt;
        }
#line 1742 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 320 "compiler.y" /* yacc.c:1646  */
    {
        struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
        stmts_group->declaration = (yyvsp[-2]._declaration);
        stmts_group->stmt = (yyvsp[-1]._stmt);
        
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmt.stmts_group = stmts_group;
        (yyval._stmt) = stmt;
            }
#line 1757 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 331 "compiler.y" /* yacc.c:1646  */
    {
        struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
        stmts_group->declaration = NULL;
        stmts_group->stmt = (yyvsp[-1]._stmt);
        
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmt.stmts_group = stmts_group;
        (yyval._stmt) = stmt;
            }
#line 1772 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 341 "compiler.y" /* yacc.c:1646  */
    {
        struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
        stmts_group->declaration = (yyvsp[-1]._declaration);
        stmts_group->stmt = NULL;
        
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmt.stmts_group = stmts_group;
        (yyval._stmt) = stmt;
            }
#line 1787 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 352 "compiler.y" /* yacc.c:1646  */
    {
        struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
        stmts_group->declaration = NULL;
        stmts_group->stmt = NULL;
        
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmt.stmts_group = stmts_group;
        (yyval._stmt) = stmt;
           
                
            }
#line 1804 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 364 "compiler.y" /* yacc.c:1646  */
    {
        //INTNUM = 1;
        struct ID_EXPR *id_expr = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_expr->ID = (yyvsp[-1].id);

        struct EXPR *expr2 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr2->expr_type = Id_Type;  
        expr2->expression.id_expr = id_expr;

        struct EXPR *expr1 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr1->expr_type = IntNum_Type;
        expr1->expression.int_val = 1;

        struct ADD_OP *add_op = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        add_op->add_type = Plus_Type;
        add_op->left_side=expr2;
        add_op->right_side= expr1;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = add_op;

        struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
        assign->ID = (yyvsp[-1].id);
        assign->expr = expr;
             
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Equ_Type;
        stmt->stmt.assign_stmt = assign;
        printf("sfsdfsdfsdF%d\n",line_counter);

        (yyval._stmt) = stmt;
    }
#line 1842 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 396 "compiler.y" /* yacc.c:1646  */
    {
        //INTNUM = 1;
        struct ID_EXPR *id_expr = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_expr->ID = (yyvsp[-1].id);

        struct EXPR *expr2 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr2->expr_type = Id_Type;  
        expr2->expression.id_expr = id_expr;

        struct EXPR *expr1 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr1->expr_type = IntNum_Type;
        expr1->expression.int_val = 1;

        struct ADD_OP *add_op = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        add_op->add_type = Minus_Type;
        add_op->left_side=expr2;
        add_op->right_side= expr1;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = add_op;

        struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
        assign->ID = (yyvsp[-1].id);
        assign->expr = expr;
             
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Equ_Type;
        stmt->stmt.assign_stmt = assign;
        printf("sfsdfsdfsdF%d\n");

        (yyval._stmt) = stmt;
    }
#line 1880 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 428 "compiler.y" /* yacc.c:1646  */
    {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Semi_Colon_Type;
        (yyval._stmt) = stmt;
    }
#line 1890 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 432 "compiler.y" /* yacc.c:1646  */
    {printf("forget to add semicolon at \n"); yyerrok;}
#line 1896 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 438 "compiler.y" /* yacc.c:1646  */
    {
                struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                stmts_group->declaration = (yyvsp[-2]._declaration);
                stmts_group->stmt = (yyvsp[-1]._stmt);
                (yyval._stmtgroup) = stmts_group;
            }
#line 1907 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 445 "compiler.y" /* yacc.c:1646  */
    {
                struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                stmts_group->declaration = NULL;
                stmts_group->stmt = (yyvsp[-1]._stmt);
                (yyval._stmtgroup) = stmts_group;
            }
#line 1918 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 451 "compiler.y" /* yacc.c:1646  */
    {
                struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                stmts_group->declaration = (yyvsp[-1]._declaration);
                stmts_group->stmt = NULL;
                (yyval._stmtgroup) = stmts_group;
            }
#line 1929 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 458 "compiler.y" /* yacc.c:1646  */
    {
                struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                stmts_group->declaration = NULL;
                stmts_group->stmt = NULL;
                (yyval._stmtgroup) = stmts_group;
           
                
            }
#line 1942 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 465 "compiler.y" /* yacc.c:1646  */
    {printf("forgot to open statemtent group\n");yyerrok;}
#line 1948 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 467 "compiler.y" /* yacc.c:1646  */
    {
            struct STMT *stmt;
            stmt = (yyvsp[0]._stmt);
            stmt->prev = NULL;
            (yyval._stmt) = stmt;
        }
#line 1959 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 473 "compiler.y" /* yacc.c:1646  */
    {
            struct STMT *stmt;
            stmt = (yyvsp[0]._stmt);
            stmt->prev = (yyvsp[-1]._stmt);
            (yyval._stmt) = stmt;
        }
#line 1970 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 483 "compiler.y" /* yacc.c:1646  */
    {
        struct ADD_OP *add_op = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        add_op->add_type = Minus_Type;
        add_op->left_side=(yyvsp[-2]._expr);
        add_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = add_op;
        (yyval._expr) = expr;
    }
#line 1986 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 494 "compiler.y" /* yacc.c:1646  */
    {
        struct ADD_OP *add_op = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        add_op->add_type = Plus_Type;
        add_op->left_side=(yyvsp[-2]._expr);
        add_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = add_op;
        (yyval._expr) = expr;
    }
#line 2002 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 505 "compiler.y" /* yacc.c:1646  */
    {
        struct MUL_OP *mul_op = (struct MUL_OP*) malloc (sizeof (struct MUL_OP));
        mul_op->mul_type = Mul_Type;
        mul_op->left_side=(yyvsp[-2]._expr);
        mul_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Mult_Type;  
        expr->expression.mul_op = mul_op;
        (yyval._expr) = expr;
    }
#line 2018 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 516 "compiler.y" /* yacc.c:1646  */
    {
        struct MUL_OP *mul_op = (struct MUL_OP*) malloc (sizeof (struct MUL_OP));
        mul_op->mul_type = Div_Type;
        mul_op->left_side=(yyvsp[-2]._expr);
        mul_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Mult_Type;  
        expr->expression.mul_op = mul_op;
        (yyval._expr) = expr;
    }
#line 2034 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 527 "compiler.y" /* yacc.c:1646  */
    {
        struct UNI_OP *uni_op = (struct UNI_OP*) malloc (sizeof (struct UNI_OP));
        uni_op->uni_type = Neg_Type;
        uni_op->expr = (yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Uni_Type;
        expr->expression.uni_op = uni_op;
        (yyval._expr) = expr;
    }
#line 2049 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 537 "compiler.y" /* yacc.c:1646  */
    {
        struct COM_OP *com_op = (struct COM_OP*) malloc (sizeof (struct COM_OP));
        com_op->com_type = Le_Type;
        com_op->left_side=(yyvsp[-2]._expr);
        com_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = com_op;
        (yyval._expr) = expr;
    }
#line 2065 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 548 "compiler.y" /* yacc.c:1646  */
    {
        struct COM_OP *com_op = (struct COM_OP*) malloc (sizeof (struct COM_OP));
        com_op->com_type = Ge_Type;
        com_op->left_side=(yyvsp[-2]._expr);
        com_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = com_op;
        (yyval._expr) = expr;
    }
#line 2081 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 559 "compiler.y" /* yacc.c:1646  */
    {
        struct COM_OP *com_op = (struct COM_OP*) malloc (sizeof (struct COM_OP));
        com_op->com_type = Gt_Type;
        com_op->left_side=(yyvsp[-2]._expr);
        com_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = com_op;
        (yyval._expr) = expr;
    }
#line 2097 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 570 "compiler.y" /* yacc.c:1646  */
    {
        struct COM_OP *com_op = (struct COM_OP*) malloc (sizeof (struct COM_OP));
        com_op->com_type = Lt_Type;
        com_op->left_side=(yyvsp[-2]._expr);
        com_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = com_op;
        (yyval._expr) = expr;
    }
#line 2113 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 581 "compiler.y" /* yacc.c:1646  */
    {
        struct EQL_OP *eql_op = (struct EQL_OP*) malloc (sizeof (struct EQL_OP));
        eql_op->eql_type = Eq_Type;
        eql_op->left_side=(yyvsp[-2]._expr);
        eql_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Eql_Type;  
        expr->expression.eql_op = eql_op;
        (yyval._expr) = expr;
    }
#line 2129 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 592 "compiler.y" /* yacc.c:1646  */
    {
        struct EQL_OP *eql_op = (struct EQL_OP*) malloc (sizeof (struct EQL_OP));
        eql_op->eql_type = Ne_Type;
        eql_op->left_side=(yyvsp[-2]._expr);
        eql_op->right_side=(yyvsp[0]._expr);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Eql_Type;  
        expr->expression.eql_op = eql_op;
        (yyval._expr) = expr;
    }
#line 2145 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 603 "compiler.y" /* yacc.c:1646  */
    {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Expr_Type;  
        expr->expression.bracket = (yyvsp[-1]._expr);
        (yyval._expr) = expr;
    }
#line 2156 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 609 "compiler.y" /* yacc.c:1646  */
    {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = (yyvsp[-2].id);
        call->arg = NULL;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = CallExpr_Type;  
        expr->expression.func_call = call;
        (yyval._expr) = expr;
    }
#line 2171 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 619 "compiler.y" /* yacc.c:1646  */
    {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = (yyvsp[-3].id);
        call->arg = (yyvsp[-1]._arg);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = CallExpr_Type;  
        expr->expression.func_call = call;
        (yyval._expr) = expr;
    }
#line 2186 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 628 "compiler.y" /* yacc.c:1646  */
    {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = IntNum_Type;  
        expr->expression.int_val = (yyvsp[0].intval);
        (yyval._expr) = expr;
    }
#line 2197 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 635 "compiler.y" /* yacc.c:1646  */
    {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = FloatNum_Type;  
        expr->expression.floatval = (yyvsp[0].floatval);
        (yyval._expr) = expr;
    }
#line 2208 "compiler.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 641 "compiler.y" /* yacc.c:1646  */
    {
        struct ID_EXPR *id_expr = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_expr->ID = (yyvsp[0].id);

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Id_Type;  
        expr->expression.id_expr = id_expr;
        (yyval._expr) = expr;
    }
#line 2222 "compiler.tab.c" /* yacc.c:1646  */
    break;


#line 2226 "compiler.tab.c" /* yacc.c:1646  */
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
#line 654 "compiler.y" /* yacc.c:1906  */





int main(int argc, char* argv[]) {
    openFiles();
    yyparse();
    closeFiles();
    return 0;
}

/*
void process(struct PROGRAM* head) {
    
    if(head == NULL)
        exit(1);
    head_scope_ptr = newBlock(Block_Global_Type, NULL);
    current_block_ptr = head_scope_ptr;
    if(head->declaration != NULL)
        compileDeclaration(head->declaration);
    if(head->function != NULL)
        compileFunction(head->function);
            compileProgram(head);
}
*/


void openFiles()
{
    assembly_file = fopen("assembly_file.txt","w");
    symbol_file = fopen("symbol_file.txt","w");
    semantic_file = fopen("semantic_file.txt","w");
}
void closeFiles()
{
    //fprintf(assembly_file, "\n");
    pclose(assembly_file);
    pclose(symbol_file);
    pclose(semantic_file);

}
