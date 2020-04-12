#ifndef AST_H
#define AST_H

#define bool char 
#define true 1 
#define false 0

typedef enum {Int_Type,Float_Type} ID_TYPE;
typedef enum {Neg_Type} UNIOP_TYPE;
typedef enum {Equ_Type,If_Type,For_Type,While_Type,Call_Type,Return_Type,Comp_Type,Semi_Type} STMT_TYPE;
typedef enum {Plus_Type,Minus_Type} ADD_TYPE;
typedef enum {Mul_Type,Div_Type} MUL_TYPE;
typedef enum {Eq_Type,Ne_Type} EQCOM_TYPE;
typedef enum {Lt_Type,Gt_Type,Le_Type,Ge_Type} COMP_TYPE;
typedef enum {eUnop,eAddi,eMulti,eRela,eEqlt,eCallExpr,eIntnum,eFloatnum,eId,eExpr} Expr_e;


//start of the program from here
struct PROGRAM
{

	struct DECLARATION *declaration;
	struct FUNCTION *function;
};

/*
-


*/
struct DECLARATION
{
	ID_TYPE id_type;
	struct IDENTIFIER *id;
	struct DECLARATION *prev;
};

/*
identifier like : int number
- ID: number
- int_val: its value
*/
struct IDENTIFIER
{
	struct IDENTIFIER *prev;

	char *ID;
	int int_val;
};

/*
- prev: previous function
- ID: int or float or anything for future work
- parameters: send paramperter
- STMTSGROUP: { }
*/
struct FUNCTION 
{
	struct FUNCTION *prev;
	
	ID_TYPE id_type;
	char *ID;
	struct PARAMETER *param;
	struct STMTSGROUP *stmts_group;
};

/*
what we send in the function
- prev : if there is another parameter
- id_type: the type of identifier
- id: pointer on the identifier
*/
struct PARAMETER
{
	struct PARAMETER *prev;

	ID_TYPE id_type;
	struct IDENTIFIER *id;
};
/*
group of statements grouped by {   }
- declaration : its declaration
- stmt: last statement pointor on it
*/
struct STMTSGROUP 
{
	struct DECLARATION *declaration;
	struct STMT *stmt;
};

/*
every statment in the code we compile means one of those
*/
struct STMT 
{	
	struct STMT *prev;

	STMT_TYPE s;
	union {
		struct ASSIGN_STMT *assign_stmt; // id=expr;
		struct IF_STMT *if_stmt;  // if()stmt
		struct WHILE_STMT *while_stmt; // while()stmt | do_while() stmt
		struct FOR_STMT *for_stmt; // for()stmt
		struct STMTSGROUP *stmts_group; // {}
		struct FUNC_CALL *func_call; // id(arg) 
		struct EXPR *return_expr; // return expr
	} stmt; 

};

/*
ASSIGN_STMT Operation
arr[0] = 5
- id => arr
- index => 0 and it could be null if you said " arr = 5"
- expr => 5
*/
struct ASSIGN_STMT
{
	char *ID;
	struct EXPR *index; 
	struct EXPR *expr;  
};

/*
calling a function : doSomething(3)
- ID: doSomthing
- arg: 3
*/
struct FUNC_CALL
{
	char *ID;
	struct ARG *arg;
};

/*
the sent arg in the function : doSomething(3,4==4)
- prev : 3
- expr : 4==4
*/
struct ARG
{
	struct ARG *prev;
	struct EXPR *expr;

};

/*
-do_while = true if it's do while operation, false otherwise
- conditon => between the while
- stmt inside the while
*/
struct WHILE_STMT 
{
	bool do_while;
	struct EXPR *condition;
	struct STMT *stmt;

};

/*
for loop statment : for(i = 1; i <10; i = i+1){}
- init => i=1
- condition => i < 10
- inc => i=i+1
- stmt => {}
*/
struct FOR_STMT
{
	struct ASSIGN_STMT *init;
	struct EXPR *condition;
	struct ASSIGN_STMT *inc;
	struct STMT *stmt; 
};

/*
if ( condition ) if_statment else else_statemetn
- there must be condition
- else statement could be null
*/

struct IF_STMT
{
	struct EXPR *condition;
	struct STMT *if_stmt;
	struct STMT *else_stmt; // NUll, if 'else' not exist
};

struct EXPR
{
	Expr_e e;   // EXPR type (enumeration type)
	union
	{
		int int_val; // int
		float floatval; // float
		struct UNOP *unop_; // -expr
		struct ADDIOP *addiop_; // epxr + expr
		struct MULTOP *multop_; // expr * expr
		struct RELAOP *relaop_; // expr >= expr
		struct EQLTOP *eqltop_; // expr == expr
		struct FUNC_CALL *func_call; // call 
		struct EXPR *bracket; // (expr)
		struct ID_S *ID_; // id[expr]
	} expression;
};

struct UNOP
{
	UNIOP_TYPE u;
	struct EXPR *expr;
};

/* lhs addiop rhs */
struct ADDIOP
{
	ADD_TYPE a;
	struct EXPR *lhs;
	struct EXPR *rhs;
};

/* lhs multiop rhs */
struct MULTOP
{
	MUL_TYPE m;
	struct EXPR *lhs;
	struct EXPR *rhs;
};

/* lhs relaop rhs */
struct RELAOP
{
	COMP_TYPE r;
	struct EXPR *lhs;
	struct EXPR *rhs;
};

/* lhs eqltop rhs */
struct EQLTOP
{
	EQCOM_TYPE e;
	struct EXPR *lhs;
	struct EXPR *rhs;
};

/* id[expr]  */
struct ID_S
{
	char *ID;
	struct EXPR *expr; // NULL , if scalar variable
};

#endif
