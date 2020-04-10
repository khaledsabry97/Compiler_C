#ifndef AST_H
#define AST_H

#define bool char 
#define true 1 
#define false 0

typedef enum
{eInt,eFloat} Type_e;
typedef enum
{eNegative} Unop_e;
typedef enum
{eAssign,eCall,eRet,eWhile,eFor,eIf,eCompound,eSemi} Stmt_e;
typedef enum
{eUnop,eAddi,eMulti,eRela,eEqlt,eCallExpr,eIntnum,eFloatnum,eId,eExpr} Expr_e;
typedef enum
{ePlus,eMinus} Addi_e;
typedef enum
{eMult,eDiv} Mult_e;
typedef enum
{eLT,eGT,eLE,eGE} Rela_e;
typedef enum
{eEQ,eNE} Eqlt_e;



struct PROGRAM
{
	struct DECLARATION *decl;
	struct FUNCTION *func;
};

struct DECLARATION
{
	Type_e t;
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
	Type_e t;
	char *ID;
	struct PARAMETER *param;
	struct COMPOUNDSTMT *cstmt;
	struct FUNCTION *prev;
};

struct PARAMETER
{
	Type_e t;
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
	Stmt_e s;
	union {
		struct ASSIGN *assign_; // id=expr;
		struct CALL *call_; // id(arg) 
		struct EXPR *return_; // return expr
		struct WHILE_S *while_; // while()stmt | do_while() stmt
		struct FOR_STMT *for_; // for()stmt
		struct IF_S *if_;  // if()stmt
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

/* if(cond)if_s else else_s  */
struct IF_S
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
	Addi_e a;
	struct EXPR *lhs;
	struct EXPR *rhs;
};

/* lhs multiop rhs */
struct MULTOP
{
	Mult_e m;
	struct EXPR *lhs;
	struct EXPR *rhs;
};

/* lhs relaop rhs */
struct RELAOP
{
	Rela_e r;
	struct EXPR *lhs;
	struct EXPR *rhs;
};

/* lhs eqltop rhs */
struct EQLTOP
{
	Eqlt_e e;
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
