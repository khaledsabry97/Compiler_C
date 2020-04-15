#include "AST.h"
#define true 1 
#define false 0

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
void visitId_s          (struct ID_EXPR* id_expr);
