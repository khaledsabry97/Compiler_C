#include "AST.h"

void visitDeclaration   (struct DECLARATION* declaration);
void visitFunction      (struct FUNCTION* function);
void visitIdentifier    (struct IDENTIFIER* iden);
void visitStmt          (struct STMT* stmt);
void visitParameter     (struct PARAMETER* param);
void visitCompoundStmt  (struct STMTSGROUP* stmts_group);
void visitAssignStmt    (struct ASSIGN* assign);
void visitCallStmt      (struct FUNC_CALL* call);
void visitArg           (struct ARG* arg);
void visitExpr          (struct EXPR* expr);
void visitWhile_s       (struct WHILE_S* while_s);
void visitFor_s         (struct FOR_STMT* for_s);
void visitIf_s          (struct IF_STMT* if_ptr);
void visitId_s          (struct ID_S* id_s);
