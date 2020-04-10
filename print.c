#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include "symboltable.h"

//TODO: delete later
//extern struct PROGRAM *head;
extern FILE *fp;
extern FILE *fp2;

//global variable for making symboltable
int _rowNumber;
Type_e _curType;
bool _isParam = false;
bool _needPrinted = false;
bool _isTitlePrinted = false;
bool _isOtherComp = false;
bool _isCompound = false;

void printScopePath() {
    //when printing global variable
    if(scopeTail->type == sGLOBAL) {
        fprintf( fp2, "Global variables\n");
        return;  //print nothing at "location"
    }
   else {
        fprintf( fp2, "\nFunction name : ");
       fprintf(fp2, "%s", _curFuncName);
       struct scope* curNode = scopeHead->child;//start from Function node
       while(curNode->child != NULL) {
           fprintf(fp2, " - ");
            switch(curNode->child->type) {
                case sDOWHILE:
                    fprintf(fp2, "DOWHILE");
                    break;

                case sWHILE:
                    fprintf(fp2, "WHILE");
                    break;

                case sFOR:
                    fprintf(fp2, "FOR");
                    break;

                case sIF:
                    fprintf(fp2, "IF");
                    break;

                case sCOMPOUND:
                    fprintf(fp2, "COMPOUND");
                    break;
            }
            fprintf(fp2, "(%d) ", getMyOrder(curNode->child->type, curNode));
            curNode = curNode->child;
       }
       fprintf(fp2, "\n");
   }

}



//print symboltable, called before entering visitDeclaration
void printTitle() {

    _rowNumber = 1;

    printScopePath();
    fprintf( fp2, "%10s%10s%10s%10s%10s\n", "count","type","name","array","role");
}



void visitDeclaration   (struct DECLARATION* decl) {
    _isParam = false;   //needed when we have to decide it is parameter or variable.
    if(decl->prev != NULL) {
        visitDeclaration(decl->prev);
    }
    if(!_isTitlePrinted) {
        printTitle();
        _isTitlePrinted = true;
    }

    switch(decl->t) {
        case eInt:
            fprintf (fp, "int ");    
            _curType = eInt;
            break;
        case eFloat:
            fprintf (fp, "float ");
            _curType = eFloat;
            break;
        default:
            fprintf(stderr, "Declaration does not exist.\n");
            exit(1);
    }
    _needPrinted = true;
    visitIdentifier(decl->id);
    _needPrinted = false;
    fprintf (fp, ";\n");
}
void visitFunction      (struct FUNCTION* func) {
    if(func->prev != NULL) {
        visitFunction(func->prev);
    }
    //for symboltable
    _curFuncName = func->ID;
    //list node
    scopeTail = newScope(sFUNC, scopeTail); //append it to the end of list

    switch(func->t) {
        case eInt:
            fprintf (fp, "int ");    
            break;
        case eFloat:
            fprintf (fp, "float ");
            break;
        default:
            fprintf(stderr, "Declaration does not exist.\n");
            exit(1);
    }
    fprintf (fp, "%s (", func->ID);//function name
    _isTitlePrinted = false;
    if(func->param != NULL) {
        printTitle();
        _isTitlePrinted = true;
        visitParameter(func->param);    //parameter 
    }
    fprintf (fp, ")\n");//function name
    visitCompoundStmt(func->cstmt); //compoundStmt
    fprintf(fp, "\n");

    //deleteCurScope 
    deleteScope(&scopeTail);
    _isTitlePrinted = false;
}
void visitIdentifier    (struct IDENTIFIER* iden) {
    if(iden->prev != NULL) {
        visitIdentifier(iden->prev);
        fprintf(fp, ", ");
    }
    fprintf (fp, "%s", iden->ID);
    if(iden->intval > 0) {
        fprintf (fp, "[%d]", iden->intval);


        if( _needPrinted == true) {
            char* curType;
            if(_curType == eInt)
                curType = "int";
            else
                curType = "float";
            fprintf( fp2, "%10d%10s%10s%10d%10s\n", _rowNumber++ , curType, iden->ID, iden->intval, _isParam ? "parameter" : "variable");
        }
    } else if(iden->intval < 0) {
        fprintf(stderr, "minus array");
    } else { 
        //scalar
        if( _needPrinted == true) {
            char* curType;
            if(_curType == eInt)
                curType = "int";
            else
                curType = "float";
            fprintf( fp2, "%10d%10s%10s%10s%10s\n", _rowNumber++ , curType, iden->ID, "", _isParam ? "parameter" : "variable"); //_rowNumber(x) ++_rowNumber(x) _rowNumber++(o)
        }
    }
}
void visitStmt          (struct STMT* stmt) {
    //TODO
    if(stmt->prev != NULL)
        visitStmt(stmt->prev);
    switch(stmt->s) {
        case eAssign:
            visitAssignStmt(stmt->stmt.assign_);
            fprintf(fp, ";");
            break;

        case eCall:
            visitCallStmt(stmt->stmt.call_);
            fprintf(fp, ";");
            break;

        case eRet:
            if(stmt->stmt.return_ == NULL){
                fprintf (fp, "return;");
            }
            else {
                fprintf (fp, "return ");
                visitExpr(stmt->stmt.return_);
                fprintf (fp, ";");
            }
            break;

        case eWhile:
             _isOtherComp = true;
            visitWhile_s(stmt->stmt.while_);
            return;
        case eFor:
             _isOtherComp = true;
            visitFor_s(stmt->stmt.for_);
            return;
        case eIf:
             _isOtherComp = true;
            visitIf_s(stmt->stmt.if_);
            return;

        case eCompound:
            if(_isOtherComp == false)
                _isCompound = true;
            visitCompoundStmt(stmt->stmt.cstmt_);
            return;
            //break;

        case eSemi:
            fprintf(fp, ";");
            break;

    }
    fprintf(fp, "\n");
}
void visitParameter     (struct PARAMETER* param) {
    _isParam = true;
    if(param->prev != NULL) {
        visitParameter(param->prev);
        fprintf (fp, ", ");
    }
    switch(param->t) {
        case eInt:
            fprintf (fp, "int ");    
            _curType = eInt;
            break;
        case eFloat:
            fprintf (fp, "float ");
            _curType = eFloat;
            break;
        default:
            fprintf(stderr, "Declaration does not exist.\n");
            exit(1);
    }
    _needPrinted = true;
    visitIdentifier(param->id);
    _needPrinted = false;
}
void visitCompoundStmt  (struct COMPOUNDSTMT* cstmt) {
    if(_isCompound == true) {
        //making node for symbol table
        scopeTail = newScope(sCOMPOUND, scopeTail);
        _isTitlePrinted = false;
        scopeTail->parent->compound_n++;
    }
    _isOtherComp = false;

    fprintf(fp, "{\n");
    if(cstmt->decl != NULL) { 
        visitDeclaration(cstmt->decl);
    }
    if(cstmt->stmt != NULL)
        visitStmt(cstmt->stmt);
    fprintf(fp, "}\n");

    if(_isCompound == true) {
        deleteScope(&scopeTail);
    }
    _isCompound = false;
    _isOtherComp = false;
}
void visitAssignStmt    (struct ASSIGN* assign) {
    fprintf(fp, "%s ",assign->ID);
    if(assign->index != NULL) {
        fprintf(fp, "[");
        visitExpr(assign->index);
        fprintf(fp, "]");
    }
    fprintf(fp, " = ");
    visitExpr(assign->expr);
}
void visitCallStmt      (struct CALL* call) {
    fprintf(fp, "%s(", call->ID);
    if(call->arg != NULL) {
        visitArg(call->arg);
    }
    fprintf(fp, ")");
}
void visitArg           (struct ARG* arg) {
    if(arg->prev != NULL) {
        visitArg(arg->prev);
        fprintf(fp,", ");
    }   
    visitExpr(arg->expr);
}
void visitExpr          (struct EXPR* expr) {
    switch(expr->e) {
        case eUnop:
            fprintf(fp, "-");
            visitExpr(expr->expression.unop_->expr);
            break;


        case eAddi:
            visitExpr(expr->expression.addiop_->lhs);
            if(expr->expression.addiop_->a == ePlus)
                fprintf(fp, " + ");
            else
                fprintf(fp, " - ");
            visitExpr(expr->expression.addiop_->rhs);
            break;


        case eMulti:
            visitExpr(expr->expression.multop_->lhs);
            if(expr->expression.multop_->m == eMult)
                fprintf(fp, " * ");
            else
                fprintf(fp, " / ");
            visitExpr(expr->expression.multop_->rhs);
            break;

        case eRela:
            visitExpr(expr->expression.relaop_->lhs);
            switch(expr->expression.relaop_->r) {
                case eLT:
                    fprintf(fp, " < ");
                    break;

                case eGT:
                    fprintf(fp, " > ");
                    break;

                case eLE:
                    fprintf(fp, " <= ");

                    break;

                case eGE:
                    fprintf(fp, " >= ");
                    break;
            }
            visitExpr(expr->expression.relaop_->rhs);
            break;

        case eEqlt:
            visitExpr(expr->expression.eqltop_->lhs);
            if(expr->expression.eqltop_->e == eEQ) {
                fprintf(fp, " == ");
            } else {
                fprintf(fp, " != " );
            }
            visitExpr(expr->expression.eqltop_->rhs);
            break;

        case eCallExpr:
            visitCallStmt(expr->expression.call_);
            break;

        case eExpr:
            fprintf(fp, "(");
            visitExpr(expr->expression.bracket);
            fprintf(fp, ")");
            break;

        case eId:
            visitId_s(expr->expression.ID_);
            break;
        case eIntnum:
            fprintf(fp, "%d", expr->expression.intval);
            break;

        case eFloatnum:
            fprintf(fp, "%f", expr->expression.floatval);
            break;
    }

}
void visitWhile_s       (struct WHILE_S* while_s) {
    if(while_s->do_while == true) {
        //making node for symbol table
        scopeTail = newScope(sDOWHILE, scopeTail);
        _isTitlePrinted = false;
        scopeTail->parent->dowhile_n++;

        fprintf(fp, "do");
        visitStmt(while_s->stmt);
        fprintf(fp, "while (");
        visitExpr(while_s->cond);
        fprintf(fp, ");\n");
    } else {
        //making node for symbol table
        scopeTail = newScope(sWHILE, scopeTail);
        _isTitlePrinted = false;
        scopeTail->parent->while_n++;

        fprintf(fp, "while (");
        visitExpr(while_s->cond);
        fprintf(fp, ")\n");
        visitStmt(while_s->stmt);
    }

    //deleteCurScope 
    deleteScope(&scopeTail);
}
void visitFor_s         (struct FOR_S* for_s) {
    //making node for symbol table
    scopeTail = newScope(sFOR, scopeTail);
    _isTitlePrinted = false;
    scopeTail->parent->for_n++;

    fprintf(fp, "for (");
    visitAssignStmt(for_s->init);
    fprintf(fp, "; ");  
    visitExpr(for_s->cond);
    fprintf(fp, "; ");  
    visitAssignStmt(for_s->inc);
    fprintf(fp, ")\n");
    visitStmt(for_s->stmt);

    //deleteCurScope 
    deleteScope(&scopeTail);
}
void visitIf_s          (struct IF_S* if_s) {
    //making node for symbol table
    scopeTail = newScope(sIF, scopeTail);
    _isTitlePrinted = false;
    scopeTail->parent->if_n++;

    fprintf(fp, "if (");
    visitExpr(if_s->cond);
    fprintf(fp, ")\n");
    visitStmt(if_s->if_);
    if (if_s->else_ != NULL) {
        fprintf(fp,"\nelse\n");
        visitStmt(if_s->else_);
    }

    //deleteCurScope 
    deleteScope(&scopeTail);
}
void visitId_s          (struct ID_S* id_s) {
   fprintf(fp,"%s",id_s->ID);
   if(id_s->expr != NULL) {
    fprintf(fp, "[");
    visitExpr(id_s->expr);
    fprintf(fp, "]");
   }
}
