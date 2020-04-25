#ifndef HEAD
#define HEAD
#define bool char 
#include"Enums.h"

static int line_counter = 0;

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
the sent arg in the function : doSomething(3,4+4)
- prev : 3
- expr : 4+4
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


/*
if ( condition ) if_statment else else_statemetn
- there must be condition
- else statement could be null
*/
struct IF_STMT
{
	struct EXPR *condition;
	struct STMT *if_stmt;
	struct STMT *else_stmt; 
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
x = 5
- id => x
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
	
	struct EXPR *return_expr; 
	struct IF_STMT *if_stmt; 
	struct FOR_STMT *for_stmt; 
	struct WHILE_STMT *while_stmt;
	struct ASSIGN_STMT *assign_stmt;
	struct STMTSGROUP *stmts_group; 
	struct DECLARATION* declaration;
};



/********************************Expressions***************************************/


/*
group all the expressions in the language
*/
struct EXPR
{
	EXPR_TYPE expr_type; 
	struct EXPR *left_side;
	struct EXPR *right_side;
	struct EXPR *expr;

	char *ID;
	int int_val; 
	float floatval; 

	struct ARG *arg;

};



#endif
