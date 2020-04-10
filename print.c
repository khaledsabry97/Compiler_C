#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include "symboltable.h"

//TODO: delete later
//extern struct PROGRAM *head;
extern FILE *tree_file;
extern FILE *table_file;

//global variable for making symboltable
int _rowNumber;
ID_TYPE _curType;
bool _isParam = false;
bool _needPrinted = false;
bool _isTitlePrinted = false;
bool _isOtherComp = false;
bool _isCompound = false;

void printScopePath() {
    //when printing global variable
    if(scopeTail->type == sGLOBAL) {
        fprintf( table_file, "Global variables\n");
        return;  //print nothing at "location"
    }
   else {
        fprintf( table_file, "\nFunction name : ");
       fprintf(table_file, "%s", _curFuncName);
       struct scope* curNode = scopeHead->child;//start from Function node
       while(curNode->child != NULL) {
           fprintf(table_file, " - ");
            switch(curNode->child->type) {
                case sDOWHILE:
                    fprintf(table_file, "DOWHILE");
                    break;

                case sWHILE:
                    fprintf(table_file, "WHILE");
                    break;

                case sFOR:
                    fprintf(table_file, "FOR");
                    break;

                case sIF:
                    fprintf(table_file, "IF");
                    break;

                case sCOMPOUND:
                    fprintf(table_file, "COMPOUND");
                    break;
            }
            fprintf(table_file, "(%d) ", getMyOrder(curNode->child->type, curNode));
            curNode = curNode->child;
       }
       fprintf(table_file, "\n");
   }

}



//print symboltable, called before entering visitDeclaration
void printTitle() {

    _rowNumber = 1;

    printScopePath();
    fprintf( table_file, "%10s%10s%10s%10s%10s\n", "count","type","name","array","role");
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
        case Int_Type:
            fprintf (tree_file, "int ");    
            _curType = Int_Type;
            break;
        case Float_Type:
            fprintf (tree_file, "float ");
            _curType = Float_Type;
            break;
        default:
            fprintf(stderr, "Declaration does not exist.\n");
            exit(1);
    }
    _needPrinted = true;
    visitIdentifier(decl->id);
    _needPrinted = false;
    fprintf (tree_file, ";\n");
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
        case Int_Type:
            fprintf (tree_file, "int ");    
            break;
        case Float_Type:
            fprintf (tree_file, "float ");
            break;
        default:
            fprintf(stderr, "Declaration does not exist.\n");
            exit(1);
    }
    fprintf (tree_file, "%s (", func->ID);//function name
    _isTitlePrinted = false;
    if(func->param != NULL) {
        printTitle();
        _isTitlePrinted = true;
        visitParameter(func->param);    //parameter 
    }
    fprintf (tree_file, ")\n");//function name
    visitCompoundStmt(func->cstmt); //compoundStmt
    fprintf(tree_file, "\n");

    //deleteCurScope 
    deleteScope(&scopeTail);
    _isTitlePrinted = false;
}
void visitIdentifier    (struct IDENTIFIER* iden) {
    if(iden->prev != NULL) {
        visitIdentifier(iden->prev);
        fprintf(tree_file, ", ");
    }
    fprintf (tree_file, "%s", iden->ID);
    if(iden->intval > 0) {
        fprintf (tree_file, "[%d]", iden->intval);


        if( _needPrinted == true) {
            char* curType;
            if(_curType == Int_Type)
                curType = "int";
            else
                curType = "float";
            fprintf( table_file, "%10d%10s%10s%10d%10s\n", _rowNumber++ , curType, iden->ID, iden->intval, _isParam ? "parameter" : "variable");
        }
    } else if(iden->intval < 0) {
        fprintf(stderr, "minus array");
    } else { 
        //scalar
        if( _needPrinted == true) {
            char* curType;
            if(_curType == Int_Type)
                curType = "int";
            else
                curType = "float";
            fprintf( table_file, "%10d%10s%10s%10s%10s\n", _rowNumber++ , curType, iden->ID, "", _isParam ? "parameter" : "variable"); //_rowNumber(x) ++_rowNumber(x) _rowNumber++(o)
        }
    }
}
void visitStmt          (struct STMT* stmt) {
    //TODO
    if(stmt->prev != NULL)
        visitStmt(stmt->prev);
    switch(stmt->s) {
        case Equ_Type:
            visitAssignStmt(stmt->stmt.assign_);
            fprintf(tree_file, ";");
            break;

        case Call_Type:
            visitCallStmt(stmt->stmt.call_);
            fprintf(tree_file, ";");
            break;

        case Return_Type:
            if(stmt->stmt.return_ == NULL){
                fprintf (tree_file, "return;");
            }
            else {
                fprintf (tree_file, "return ");
                visitExpr(stmt->stmt.return_);
                fprintf (tree_file, ";");
            }
            break;

        case While_Type:
             _isOtherComp = true;
            visitWhile_s(stmt->stmt.while_);
            return;
        case For_Type:
             _isOtherComp = true;
            visitFor_s(stmt->stmt.for_);
            return;
        case If_Type:
             _isOtherComp = true;
            visitIf_s(stmt->stmt.if_);
            return;

        case Comp_Type:
            if(_isOtherComp == false)
                _isCompound = true;
            visitCompoundStmt(stmt->stmt.cstmt_);
            return;
            //break;

        case Semi_Type:
            fprintf(tree_file, ";");
            break;

    }
    fprintf(tree_file, "\n");
}
void visitParameter     (struct PARAMETER* param) {
    _isParam = true;
    if(param->prev != NULL) {
        visitParameter(param->prev);
        fprintf (tree_file, ", ");
    }
    switch(param->t) {
        case Int_Type:
            fprintf (tree_file, "int ");    
            _curType = Int_Type;
            break;
        case Float_Type:
            fprintf (tree_file, "float ");
            _curType = Float_Type;
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

    fprintf(tree_file, "{\n");
    if(cstmt->decl != NULL) { 
        visitDeclaration(cstmt->decl);
    }
    if(cstmt->stmt != NULL)
        visitStmt(cstmt->stmt);
    fprintf(tree_file, "}\n");

    if(_isCompound == true) {
        deleteScope(&scopeTail);
    }
    _isCompound = false;
    _isOtherComp = false;
}
void visitAssignStmt    (struct ASSIGN* assign) {
    fprintf(tree_file, "%s ",assign->ID);
    if(assign->index != NULL) {
        fprintf(tree_file, "[");
        visitExpr(assign->index);
        fprintf(tree_file, "]");
    }
    fprintf(tree_file, " = ");
    visitExpr(assign->expr);
}
void visitCallStmt      (struct CALL* call) {
    fprintf(tree_file, "%s(", call->ID);
    if(call->arg != NULL) {
        visitArg(call->arg);
    }
    fprintf(tree_file, ")");
}
void visitArg           (struct ARG* arg) {
    if(arg->prev != NULL) {
        visitArg(arg->prev);
        fprintf(tree_file,", ");
    }   
    visitExpr(arg->expr);
}
void visitExpr          (struct EXPR* expr) {
    switch(expr->e) {
        case eUnop:
            fprintf(tree_file, "-");
            visitExpr(expr->expression.unop_->expr);
            break;


        case eAddi:
            visitExpr(expr->expression.addiop_->lhs);
            if(expr->expression.addiop_->a == Plus_Type)
                fprintf(tree_file, " + ");
            else
                fprintf(tree_file, " - ");
            visitExpr(expr->expression.addiop_->rhs);
            break;


        case eMulti:
            visitExpr(expr->expression.multop_->lhs);
            if(expr->expression.multop_->m == Mul_Type)
                fprintf(tree_file, " * ");
            else
                fprintf(tree_file, " / ");
            visitExpr(expr->expression.multop_->rhs);
            break;

        case eRela:
            visitExpr(expr->expression.relaop_->lhs);
            switch(expr->expression.relaop_->r) {
                case Lt_Type:
                    fprintf(tree_file, " < ");
                    break;

                case Gt_Type:
                    fprintf(tree_file, " > ");
                    break;

                case Le_Type:
                    fprintf(tree_file, " <= ");

                    break;

                case Ge_Type:
                    fprintf(tree_file, " >= ");
                    break;
            }
            visitExpr(expr->expression.relaop_->rhs);
            break;

        case eEqlt:
            visitExpr(expr->expression.eqltop_->lhs);
            if(expr->expression.eqltop_->e == Eq_Type) {
                fprintf(tree_file, " == ");
            } else {
                fprintf(tree_file, " != " );
            }
            visitExpr(expr->expression.eqltop_->rhs);
            break;

        case eCallExpr:
            visitCallStmt(expr->expression.call_);
            break;

        case eExpr:
            fprintf(tree_file, "(");
            visitExpr(expr->expression.bracket);
            fprintf(tree_file, ")");
            break;

        case eId:
            visitId_s(expr->expression.ID_);
            break;
        case eIntnum:
            fprintf(tree_file, "%d", expr->expression.intval);
            break;

        case eFloatnum:
            fprintf(tree_file, "%f", expr->expression.floatval);
            break;
    }

}
void visitWhile_s       (struct WHILE_S* while_s) {
    if(while_s->do_while == true) {
        //making node for symbol table
        scopeTail = newScope(sDOWHILE, scopeTail);
        _isTitlePrinted = false;
        scopeTail->parent->dowhile_n++;

        fprintf(tree_file, "do");
        visitStmt(while_s->stmt);
        fprintf(tree_file, "while (");
        visitExpr(while_s->cond);
        fprintf(tree_file, ");\n");
    } else {
        //making node for symbol table
        scopeTail = newScope(sWHILE, scopeTail);
        _isTitlePrinted = false;
        scopeTail->parent->while_n++;

        fprintf(tree_file, "while (");
        visitExpr(while_s->cond);
        fprintf(tree_file, ")\n");
        visitStmt(while_s->stmt);
    }

    //deleteCurScope 
    deleteScope(&scopeTail);
}
void visitFor_s         (struct FOR_STMT* for_s) {
    //making node for symbol table
    scopeTail = newScope(sFOR, scopeTail);
    _isTitlePrinted = false;
    scopeTail->parent->for_n++;

    fprintf(tree_file, "for (");
    visitAssignStmt(for_s->init);
    fprintf(tree_file, "; ");  
    visitExpr(for_s->cond);
    fprintf(tree_file, "; ");  
    visitAssignStmt(for_s->inc);
    fprintf(tree_file, ")\n");
    visitStmt(for_s->stmt);

    //deleteCurScope 
    deleteScope(&scopeTail);
}
void visitIf_s          (struct IF_STMT* if_ptr) {
    //making node for symbol table
    scopeTail = newScope(sIF, scopeTail);
    _isTitlePrinted = false;
    scopeTail->parent->if_n++;

    fprintf(tree_file, "if (");
    visitExpr(if_ptr->cond);
    fprintf(tree_file, ")\n");
    visitStmt(if_ptr->if_);
    if (if_ptr->else_ != NULL) {
        fprintf(tree_file,"\nelse\n");
        visitStmt(if_ptr->else_);
    }

    //deleteCurScope 
    deleteScope(&scopeTail);
}
void visitId_s          (struct ID_S* id_s) {
   fprintf(tree_file,"%s",id_s->ID);
   if(id_s->expr != NULL) {
    fprintf(tree_file, "[");
    visitExpr(id_s->expr);
    fprintf(tree_file, "]");
   }
}
