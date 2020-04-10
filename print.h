#include "AST.h"

void visitDeclaration   (struct DECLARATION* decl);
void visitFunction      (struct FUNCTION* func);
void visitIdentifier    (struct IDENTIFIER* iden);
void visitStmt          (struct STMT* stmt);
void visitParameter     (struct PARAMETER* param);
void visitCompoundStmt  (struct COMPOUNDSTMT* cstmt);
void visitAssignStmt    (struct ASSIGN* assign);
void visitCallStmt      (struct CALL* call);
void visitArg           (struct ARG* arg);
void visitExpr          (struct EXPR* expr);
void visitWhile_s       (struct WHILE_S* while_s);
void visitFor_s         (struct FOR_S* for_s);
void visitIf_s          (struct IF_S* if_s);
void visitId_s          (struct ID_S* id_s);
