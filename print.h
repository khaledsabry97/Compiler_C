#include "AST.h"
#define true 1 
#define false 0
void visitDeclaration   (struct DECLARATION* declaration);
void visitFunction      (struct FUNCTION* function);
void visitIdentifier    (struct IDENTIFIER* identifier);
void visitStmt          (struct STMT* stmt);
void visitParameter     (struct PARAMETER* parameter);
void visitCompoundStmt  (struct STMTSGROUP* stmts_group);
void visitAssignStmt    (struct ASSIGN_STMT* assign);
void visitCallStmt      (struct FUNC_CALL* call);
void visitArg           (struct ARG* arg);
void visitExpr          (struct EXPR* expr);
void visitWhile_s       (struct WHILE_STMT* while_stmt);
void visitFor_s         (struct FOR_STMT* for_stmt);
void visitIf_s          (struct IF_STMT* if_stmt);
void visitId_s          (struct ID_EXPR* id_expr);
