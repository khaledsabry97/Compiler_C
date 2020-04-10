#ifndef AST_H
#define AST_H

#define bool char 
#define true 1 
#define false 0

typedef enum {Int_Type,Float_Type} ID_TYPE;
typedef enum {eNegative} Unop_e;
typedef enum {Equ_Type,Call_Type,Return_Type,While_Type,For_Type,If_Type,Comp_Type,Semi_Type} STMT_TYPE;
typedef enum {eUnop,eAddi,eMulti,eRela,eEqlt,eCallExpr,eIntnum,eFloatnum,eId,eExpr} Expr_e;
typedef enum {Plus_Type,Minus_Type} ADD_TYPE;
typedef enum {Mul_Type,Div_Type} MUL_TYPE;
typedef enum {Lt_Type,Gt_Type,Le_Type,Ge_Type} COMP_TYPE;
typedef enum {Eq_Type,Ne_Type} EQCOM_TYPE;



struct PROGRAM
{
	struct DECLARATION *decl;
	struct FUNCTION *func;
};

struct DECLARATION
{
	ID_TYPE t;
	struct IDENTIFIER *id;
	struct DECLARATION *prev;
};

struct IDENTIFIER
{
	char *ID;
	int intval; // zero  , if scalar
	struct IDENTIFIER *prev;

};

struct FUNCTION  // *prev  type id (parameter) {} 
{
	ID_TYPE t;
	char *ID;
	struct PARAMETER *param;
	struct COMPOUNDSTMT *cstmt;
	struct FUNCTION *prev;
};

struct PARAMETER
{
	ID_TYPE t;
	struct IDENTIFIER *id;
	struct PARAMETER *prev;
};

struct COMPOUNDSTMT // {}
{
	struct DECLARATION *decl;
	struct STMT *stmt;
};
/*
break,semi stmt union stmt -> no value; 
*/
struct STMT 
{	
	STMT_TYPE s;
	union {
		struct ASSIGN *assign_; // id=expr;
		struct CALL *call_; // id(arg) 
		struct EXPR *return_; // return expr
		struct WHILE_S *while_; // while()stmt | do_while() stmt
		struct FOR_STMT *for_; // for()stmt
		struct IF_STMT *if_;  // if()stmt
		struct COMPOUNDSTMT *cstmt_; // {}
	} stmt; 
	struct STMT *prev;
};

/* id[index]=expr;  */
struct ASSIGN
{
	char *ID;
	struct EXPR *index; // Null, if LHS is scalar variable
	struct EXPR *expr;  // RHS
};

/* id(arglist?);  */
struct CALL
{
	char *ID;
	struct ARG *arg;
};

/* (expr,expr*)  */
struct ARG
{
	struct EXPR *expr;
	struct ARG *prev;

};

/* while(cond)stmt;  | do stmt while (cond) */ 
struct WHILE_S 
{
	bool do_while;
	struct EXPR *cond;
	struct STMT *stmt;

};

/* for(init;cond;inc)stmt;  */
struct FOR_STMT
{
	struct ASSIGN *init;
	struct EXPR *cond;
	struct ASSIGN *inc;
	struct STMT *stmt; 

};

/* if(cond)if_ptr else else_s  */
struct IF_STMT
{
	struct EXPR *cond;
	struct STMT *if_;
	struct STMT *else_; // NUll, if 'else' not exist
};

struct EXPR
{
	Expr_e e;   // EXPR type (enumeration type)
	union
	{
		int intval; // int
		float floatval; // float
		struct UNOP *unop_; // -expr
		struct ADDIOP *addiop_; // epxr + expr
		struct MULTOP *multop_; // expr * expr
		struct RELAOP *relaop_; // expr >= expr
		struct EQLTOP *eqltop_; // expr == expr
		struct CALL *call_; // call 
		struct EXPR *bracket; // (expr)
		struct ID_S *ID_; // id[expr]
	} expression;
};

struct UNOP
{
	Unop_e u;
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
