#include "AST.h"
#define true 1 
#define false 0

typedef enum { sGLOBAL, sFUNC, sDOWHILE, sWHILE, sFOR, sIF, sCOMPOUND } SCOPETYPE; //s : scope

struct scope {
    int dowhile_n;  //_n: number
    int while_n;
    int for_n;
    int if_n;
    int compound_n;
    SCOPETYPE type;
    struct scope* parent;
    struct scope* child;
};

struct scope *scopeHead, *scopeTail;
char* _curFuncName;

//make node
struct scope* newScope(SCOPETYPE type, struct scope* parent);

//delete node
void deleteScope(struct scope** scopeTail);

//returns the order of current scope
int getMyOrder(SCOPETYPE type, struct scope* parent);

void printDeclaration   (struct DECLARATION* declaration);
void visitIdentifier    (struct IDENTIFIER* identifier);
void visitFunction      (struct FUNCTION* function);
void visitParameter     (struct PARAMETER* parameter);
void visitArg           (struct ARG* arg);

void visitCallStmt      (struct FUNC_CALL* call);
void visitIf_s          (struct IF_STMT* if_stmt);
void visitFor_s         (struct FOR_STMT* for_stmt);
void visitWhile_s       (struct WHILE_STMT* while_stmt);
void visitAssignStmt    (struct ASSIGN_STMT* assign);
void visitCompoundStmt  (struct STMTSGROUP* stmts_group);
void visitStmt          (struct STMT* stmt);

void visitId_s          (struct ID_EXPR* id_expr);
void visitExpr          (struct EXPR *expr);

