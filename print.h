#include "AST.h"
#define true 1 
#define false 0

typedef enum { Scope_Global_Type, Scope_Stmt_Group_Type, Scope_Func_Type, Scope_If_Type, Scope_For_Type, Scope_Do_While_Type, Scope_While_Type} SCOPE_TYPE; //s : SCOPE

struct SCOPE {
    int dowhile_n;  //_n: number
    int while_n;
    int for_n;
    int if_n;
    int compound_n;
    SCOPE_TYPE scope_type;
    struct SCOPE* parent_scope;
    struct SCOPE* child_scope;
};

struct SCOPE *scopeHead, *scopeTail;
char* current_func_name;

//make node
struct SCOPE* newScope(SCOPE_TYPE scope_type, struct SCOPE* parent_scope);

//delete node
void deleteScope(struct SCOPE** scopeTail);

//returns the order of current SCOPE
int getMyOrder(SCOPE_TYPE scope_type, struct SCOPE* parent_scope);


struct Assembly{
    struct Assembly* prev;
    char str[1000];
    
    struct DECLARATION* declaration;
    struct FUNCTION* funtion;    
        
    struct FUNC_CALL *func_call; 
    struct EXPR *return_expr; // return expr
    struct IF_STMT *if_stmt; 
    struct FOR_STMT *for_stmt; 
    struct WHILE_STMT *while_stmt;
    struct ASSIGN_STMT *assign_stmt;
    struct STMTSGROUP *stmts_group; 


    int int_val; 
    float floatval; 
    struct EXPR *bracket; // (expr)
    struct ID_EXPR *id_expr; 

    struct UNI_OP *uni_op; 
    struct ADD_OP *add_op; 
    struct MUL_OP *mul_op; 

    struct EQL_OP *eql_op; 
    struct COM_OP *com_op; 

};






























void processDeclaration   (struct DECLARATION* declaration);
void processIdentifier    (struct IDENTIFIER* identifier);
void processFunction      (struct FUNCTION* function);
void processParameter     (struct PARAMETER* parameter);
void processArg           (struct ARG* arg);

void processAssignStmt    (struct ASSIGN_STMT* assign);
void processStmtGroup  (struct STMTSGROUP* stmts_group);
void processStmt          (struct STMT* stmt);

void processExpr          (struct EXPR *expr);

