#ifndef HEAD
#define HEAD
#define bool char 


static int line_counter = 0;



/******************************************************Enum Types*********************************************************/

typedef enum {Int_Type,Float_Type,Const_Int_Type,Const_Float_Type} ID_TYPE;

typedef enum {Equ_Type,If_Type,For_Type,While_Type,Call_Type,Return_Type,Declaration_Type,Stmt_Group_Type,Semi_Colon_Type} STMT_TYPE;

typedef enum {Neg_Type} UNI_OP_TYPE;
typedef enum {Plus_Type,Minus_Type} ADD_TYPE;
typedef enum {Mul_Type,Div_Type} MUL_TYPE;
typedef enum {Eq_Type,Ne_Type} EQCOM_TYPE;
typedef enum {Lt_Type,Gt_Type,Le_Type,Ge_Type} COMP_TYPE;
typedef enum {Uni_Type,Add_Type,Mult_Type,Com_Type,Eql_Type,CallExpr_Type,IntNum_Type,FloatNum_Type,Id_Type,Expr_Type} EXPR_TYPE;



/******************************************************Program*********************************************************/
//start of the program from here
struct PROGRAM
{

	struct DECLARATION *declaration;
	struct FUNCTION *function;
};

/*
- to declare variables before assignment int value;
id_type : int
id : value

*/
struct DECLARATION
{
	struct DECLARATION *prev;

	ID_TYPE id_type;
	struct IDENTIFIER *id;
};

/*
identifier like : int number
- ID: number
*/
struct IDENTIFIER
{
	char *ID;
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
	struct PARAMETER *parameter;
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
the sent arg in the function : doSomething(3,4==4)
- prev : 3
- expr : 4==4
*/
struct ARG
{
	struct ARG *prev;
	struct EXPR *expr;

};

/*********************************************** Statements **************************************************/

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
ASSIGN_STMT Operation
arr[0] = 5
- id => arr
- index => 0 and it could be null if you said " arr = 5"
- expr => 5
*/
struct ASSIGN_STMT
{
	char *ID;
	struct EXPR *expr;  
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

	STMT_TYPE stmt_type;
	union {
		struct FUNC_CALL *func_call; 
		struct EXPR *return_expr; // return expr
		struct IF_STMT *if_stmt; 
		struct FOR_STMT *for_stmt; 
		struct WHILE_STMT *while_stmt;
		struct ASSIGN_STMT *assign_stmt;
		struct STMTSGROUP *stmts_group; 
		struct DECLARATION* declaration;
	} stmt; 
};



/********************************Expressions***************************************/

/* 
arr[3==3]
*/
struct ID_EXPR
{
	char *ID;
};


/*
-3 or +3 or - expr
*/
struct UNI_OP
{
	UNI_OP_TYPE uni_type;
	struct EXPR *expr;
};

/*
3+4 or (3*2) + (4*2)
int + int or expr + expr
*/
struct ADD_OP
{
	ADD_TYPE add_type;
	struct EXPR *left_side;
	struct EXPR *right_side;
};

/*
expr * expr
3*3
(4+2)*(4+3)
left_side * right_side
*/
struct MUL_OP
{
	MUL_TYPE mul_type;
	struct EXPR *left_side;
	struct EXPR *right_side;
};



/*
3==2
*/
struct EQL_OP
{
	EQCOM_TYPE eql_type;
	struct EXPR *left_side;
	struct EXPR *right_side;
};

/*
5>=3
*/
struct COM_OP
{
	COMP_TYPE com_type;
	struct EXPR *left_side;
	struct EXPR *right_side;
};


/*
group all the expressions in the language
*/
struct EXPR
{
	EXPR_TYPE expr_type;   // EXPR type (enumeration type)
	union
	{
		int int_val; 
		float floatval; 
		struct FUNC_CALL *func_call;
		struct EXPR *bracket; // (expr)
		struct ID_EXPR *id_expr; 

		struct UNI_OP *uni_op; 
		struct ADD_OP *add_op; 
		struct MUL_OP *mul_op; 

		struct EQL_OP *eql_op; 
		struct COM_OP *com_op; 

	} expression;
};



#endif
