#include "AST.h"
#define true 1 
#define false 0

typedef enum { Scope_Global_Type, Scope_Stmt_Group_Type, Scope_Func_Type, Scope_If_Type, Scope_For_Type, Scope_Do_While_Type, Scope_While_Type} SCOPE_TYPE; //s : SCOPE

struct SCOPE {
    int do_while_count;  //_n: number
    int while_count;
    int for_count;
    int if_count;
    char* name;
    int stmt_group_count;
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
};






























void processDeclaration   (struct DECLARATION* declaration);
void processIdentifier    (struct IDENTIFIER* identifier);
void processFunction      (struct FUNCTION* function);
void processParameter     (struct PARAMETER* parameter);
void processArg           (struct ARG* arg);

void processAssignStmt    (struct ASSIGN_STMT* assign);
void processStmtGroup  (struct STMTSGROUP* stmts_group);
void processStmt          (struct STMT* stmt);

void processExpr          (struct EXPR *expr,bool must_return);

