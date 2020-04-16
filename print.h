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

void printDeclaration   (struct DECLARATION* declaration);
void printIdentifier    (struct IDENTIFIER* identifier);
void printFunction      (struct FUNCTION* function);
void printParameter     (struct PARAMETER* parameter);
void visitArg           (struct ARG* arg);

void visitCallStmt      (struct FUNC_CALL* call);
void visitIf_s          (struct IF_STMT* if_stmt);
void visitFor_s         (struct FOR_STMT* for_stmt);
void visitWhile_s       (struct WHILE_STMT* while_stmt);
void visitAssignStmt    (struct ASSIGN_STMT* assign);
void printStmtGroup  (struct STMTSGROUP* stmts_group);
void visitStmt          (struct STMT* stmt);

void visitId_s          (struct ID_EXPR* id_expr);
void visitExpr          (struct EXPR *expr);

