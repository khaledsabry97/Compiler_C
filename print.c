#include <stdio.h>
#include <stdlib.h>
#include "print.h"

//TODO: delete later
//extern struct PROGRAM *head;
extern FILE *tree_file;
extern FILE *table_file;

//global variable for making symboltable
int row_no;
ID_TYPE current_type;
bool is_parameter = false;
bool printed = false;
bool _isTitlePrinted = false;
bool _isOtherComp = false;
bool _isCompound = false;




//make node
struct scope* newScope(SCOPETYPE type, struct scope* parent) {
    struct scope* node = (struct scope*) malloc (sizeof(struct scope));
    node->type = type;
    node->dowhile_n = 0;
    node->while_n = 0;
    node->for_n  = 0;
    node->if_n = 0;
    node->compound_n = 0;

    if(parent != NULL) {
        node->parent = parent;
        parent->child = node;
    } else {
        node->parent = NULL;
    }

    node->child = NULL;
    return node;
}

//scopeTail denotes curScope node
void deleteScope(struct scope** scopeTail) {
    struct scope* curScope = *scopeTail;
    struct scope* parent = curScope->parent;
    if(parent != NULL) {
        parent->child = NULL;
        (*scopeTail) = parent;
        free(curScope);
      } 
      
//    free(curScope);
}

//returns the order of current scope
int getMyOrder(SCOPETYPE type, struct scope* parent) {
    switch(type) {
        case sDOWHILE:
            return (parent->dowhile_n);

        case sWHILE:
            return (parent->while_n);

        case sFOR:
            return (parent->for_n);

        case sIF:
            return (parent->if_n);

        case sCOMPOUND:
            return (parent->compound_n);
    }
}
























void printScopePath()
{
    //when printing global variable
    if (scopeTail->type == sGLOBAL)
    {
        fprintf(table_file, "Global variables\n");
        return; //print nothing at "location"
    }
    else
    {
        fprintf(table_file, "\nFunction name : ");
        fprintf(table_file, "%s", _curFuncName);
        struct scope *curNode = scopeHead->child; //start from Function node
        while (curNode->child != NULL)
        {
            fprintf(table_file, " - ");
            switch (curNode->child->type)
            {
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

//print symboltable, called before entering printDeclaration
void printTitle()
{

    row_no = 1;

    printScopePath();
    fprintf(table_file, "%10s%10s%10s%10s%10s\n", "count", "type", "name", "array", "role");
}

void printDeclaration(struct DECLARATION *declaration)
{
    is_parameter = false;
    if (declaration->prev != NULL)
        printDeclaration(declaration->prev);

    if (!_isTitlePrinted)
    {
        printTitle();
        _isTitlePrinted = true;
    }

    switch (declaration->id_type)
    {
    case Int_Type:
        fprintf(tree_file, "int ");
        current_type = Int_Type;
        break;
    case Float_Type:
        fprintf(tree_file, "float ");
        current_type = Float_Type;
        break;
    default:
        fprintf(stderr, "declaration does not exist.\n");
        exit(1);
    }
    printed = true;
    visitIdentifier(declaration->id);
    printed = false;
    fprintf(tree_file, ";\n");
}
void visitFunction(struct FUNCTION *function)
{
    if (function->prev != NULL)
    {
        visitFunction(function->prev);
    }
    //for symboltable
    _curFuncName = function->ID;
    //list node
    scopeTail = newScope(sFUNC, scopeTail); //append it to the end of list

    switch (function->id_type)
    {
    case Int_Type:
        fprintf(tree_file, "int ");
        break;
    case Float_Type:
        fprintf(tree_file, "float ");
        break;
    default:
        fprintf(stderr, "Declaration does not exist.\n");
        exit(1);
    }
    fprintf(tree_file, "%s (", function->ID); //function name
    _isTitlePrinted = false;
    if (function->parameter != NULL)
    {
        printTitle();
        _isTitlePrinted = true;
        visitParameter(function->parameter); //parameter
    }
    fprintf(tree_file, ")\n");                //function name
    visitCompoundStmt(function->stmts_group); //compoundStmt
    fprintf(tree_file, "\n");

    //deleteCurScope
    deleteScope(&scopeTail);
    _isTitlePrinted = false;
}
void visitIdentifier(struct IDENTIFIER *identifier)
{

    fprintf(tree_file, "%s", identifier->ID);
    if (identifier->int_val > 0)
    {
        fprintf(tree_file, "[%d]", identifier->int_val);

        if (printed)
        {
            char *curType;
            if (current_type == Int_Type)
                curType = "int";
            else if (current_type == Float_Type)
                curType = "float";

            if (is_parameter)
                fprintf(table_file, "%10d%10s%10s%10d%10s\n", row_no++, curType, identifier->ID, identifier->int_val,"parameter");
            else
                fprintf(table_file, "%10d%10s%10s%10d%10s\n", row_no++, curType, identifier->ID, identifier->int_val,"variable");
            
        }
    }
    else if (identifier->int_val < 0)
    {
        fprintf(stderr, "error");
    }
    else
    {
        //scalar
        if (printed == true)
        {
            char *curType;
            if (current_type == Int_Type)
                curType = "int";
            else
                curType = "float";
            fprintf(table_file, "%10d%10s%10s%10s%10s\n", row_no++, curType, identifier->ID, "", is_parameter ? "parameter" : "variable"); //row_no(x) ++row_no(x) row_no++(o)
        }
    }
}
void visitStmt(struct STMT *stmt)
{
    //TODO
    if (stmt->prev != NULL)
        visitStmt(stmt->prev);
    switch (stmt->stmt_type)
    {
    case Equ_Type:
        visitAssignStmt(stmt->stmt.assign_stmt);
        fprintf(tree_file, ";");
        break;

    case Call_Type:
        visitCallStmt(stmt->stmt.func_call);
        fprintf(tree_file, ";");
        break;

    case Return_Type:
        if (stmt->stmt.return_expr == NULL)
        {
            fprintf(tree_file, "return;");
        }
        else
        {
            fprintf(tree_file, "return ");
            visitExpr(stmt->stmt.return_expr);
            fprintf(tree_file, ";");
        }
        break;

    case While_Type:
        _isOtherComp = true;
        visitWhile_s(stmt->stmt.while_stmt);
        return;
    case For_Type:
        _isOtherComp = true;
        visitFor_s(stmt->stmt.for_stmt);
        return;
    case If_Type:
        _isOtherComp = true;
        visitIf_s(stmt->stmt.if_stmt);
        return;

    case Comp_Type:
        if (_isOtherComp == false)
            _isCompound = true;
        visitCompoundStmt(stmt->stmt.stmts_group);
        return;
        //break;

    case Semi_Type:
        fprintf(tree_file, ";");
        break;
    }
    fprintf(tree_file, "\n");
}
void visitParameter(struct PARAMETER *parameter)
{
    is_parameter = true;
    if (parameter->prev != NULL)
    {
        visitParameter(parameter->prev);
        fprintf(tree_file, ", ");
    }
    switch (parameter->id_type)
    {
    case Int_Type:
        fprintf(tree_file, "int ");
        current_type = Int_Type;
        break;
    case Float_Type:
        fprintf(tree_file, "float ");
        current_type = Float_Type;
        break;
    default:
        fprintf(stderr, "Declaration does not exist.\n");
        exit(1);
    }
    printed = true;
    visitIdentifier(parameter->id);
    printed = false;
}
void visitCompoundStmt(struct STMTSGROUP *stmts_group)
{
    if (_isCompound == true)
    {
        //making node for symbol table
        scopeTail = newScope(sCOMPOUND, scopeTail);
        _isTitlePrinted = false;
        scopeTail->parent->compound_n++;
    }
    _isOtherComp = false;

    fprintf(tree_file, "{\n");
    if (stmts_group->declaration != NULL)
    {
        printDeclaration(stmts_group->declaration);
    }
    if (stmts_group->stmt != NULL)
        visitStmt(stmts_group->stmt);
    fprintf(tree_file, "}\n");

    if (_isCompound == true)
    {
        deleteScope(&scopeTail);
    }
    _isCompound = false;
    _isOtherComp = false;
}
void visitAssignStmt(struct ASSIGN_STMT *assign)
{
    fprintf(tree_file, "%s ", assign->ID);
    if (assign->index != NULL)
    {
        fprintf(tree_file, "[");
        visitExpr(assign->index);
        fprintf(tree_file, "]");
    }
    fprintf(tree_file, " = ");
    visitExpr(assign->expr);
}
void visitCallStmt(struct FUNC_CALL *call)
{
    fprintf(tree_file, "%s(", call->ID);
    if (call->arg != NULL)
    {
        visitArg(call->arg);
    }
    fprintf(tree_file, ")");
}
void visitArg(struct ARG *arg)
{
    if (arg->prev != NULL)
    {
        visitArg(arg->prev);
        fprintf(tree_file, ", ");
    }
    visitExpr(arg->expr);
}
void visitExpr(struct EXPR *expr)
{
    switch (expr->expr_type)
    {
    case Uni_Type:
        fprintf(tree_file, "-");
        visitExpr(expr->expression.uni_op->expr);
        break;

    case Add_Type:
        visitExpr(expr->expression.add_op->left_side);
        if (expr->expression.add_op->add_type == Plus_Type)
            fprintf(tree_file, " + ");
        else
            fprintf(tree_file, " - ");
        visitExpr(expr->expression.add_op->right_side);
        break;

    case Mult_Type:
        visitExpr(expr->expression.mul_op->left_side);
        if (expr->expression.mul_op->mul_type == Mul_Type)
            fprintf(tree_file, " * ");
        else
            fprintf(tree_file, " / ");
        visitExpr(expr->expression.mul_op->right_side);
        break;

    case Com_Type:
        visitExpr(expr->expression.com_op->left_side);
        switch (expr->expression.com_op->com_type)
        {
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
        visitExpr(expr->expression.com_op->right_side);
        break;

    case Eql_Type:
        visitExpr(expr->expression.eql_op->left_side);
        if (expr->expression.eql_op->eql_type == Eq_Type)
        {
            fprintf(tree_file, " == ");
        }
        else
        {
            fprintf(tree_file, " != ");
        }
        visitExpr(expr->expression.eql_op->right_side);
        break;

    case CallExpr_Type:
        visitCallStmt(expr->expression.func_call);
        break;

    case Expr_Type:
        fprintf(tree_file, "(");
        visitExpr(expr->expression.bracket);
        fprintf(tree_file, ")");
        break;

    case Id_Type:
        visitId_s(expr->expression.id_expr);
        break;
    case IntNum_Type:
        fprintf(tree_file, "%d", expr->expression.int_val);
        break;

    case FloatNum_Type:
        fprintf(tree_file, "%f", expr->expression.floatval);
        break;
    }
}
void visitWhile_s(struct WHILE_STMT *while_stmt)
{
    if (while_stmt->do_while == true)
    {
        //making node for symbol table
        scopeTail = newScope(sDOWHILE, scopeTail);
        _isTitlePrinted = false;
        scopeTail->parent->dowhile_n++;

        fprintf(tree_file, "do");
        visitStmt(while_stmt->stmt);
        fprintf(tree_file, "while (");
        visitExpr(while_stmt->condition);
        fprintf(tree_file, ");\n");
    }
    else
    {
        //making node for symbol table
        scopeTail = newScope(sWHILE, scopeTail);
        _isTitlePrinted = false;
        scopeTail->parent->while_n++;

        fprintf(tree_file, "while (");
        visitExpr(while_stmt->condition);
        fprintf(tree_file, ")\n");
        visitStmt(while_stmt->stmt);
    }

    //deleteCurScope
    deleteScope(&scopeTail);
}
void visitFor_s(struct FOR_STMT *for_stmt)
{
    //making node for symbol table
    scopeTail = newScope(sFOR, scopeTail);
    _isTitlePrinted = false;
    scopeTail->parent->for_n++;

    fprintf(tree_file, "for (");
    visitAssignStmt(for_stmt->init);
    fprintf(tree_file, "; ");
    visitExpr(for_stmt->condition);
    fprintf(tree_file, "; ");
    visitAssignStmt(for_stmt->inc);
    fprintf(tree_file, ")\n");
    visitStmt(for_stmt->stmt);

    //deleteCurScope
    deleteScope(&scopeTail);
}
void visitIf_s(struct IF_STMT *if_stmt)
{
    //making node for symbol table
    scopeTail = newScope(sIF, scopeTail);
    _isTitlePrinted = false;
    scopeTail->parent->if_n++;

    fprintf(tree_file, "if (");
    visitExpr(if_stmt->condition);
    fprintf(tree_file, ")\n");
    visitStmt(if_stmt->if_stmt);
    if (if_stmt->else_stmt != NULL)
    {
        fprintf(tree_file, "\nelse\n");
        visitStmt(if_stmt->else_stmt);
    }

    //deleteCurScope
    deleteScope(&scopeTail);
}
void visitId_s(struct ID_EXPR *id_expr)
{
    fprintf(tree_file, "%s", id_expr->ID);
    if (id_expr->expr != NULL)
    {
        fprintf(tree_file, "[");
        visitExpr(id_expr->expr);
        fprintf(tree_file, "]");
    }
}
