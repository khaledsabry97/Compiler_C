#include <stdio.h>
#include <stdlib.h>
#include "print.h"


extern FILE *tree_file;
extern FILE *table_file;


//global variable for making symboltable
int row_no;
ID_TYPE current_type;
bool is_parameter = false;
bool printed = false;
bool print_title = false;
bool _isOtherComp = false;
bool is_it_group_stmt = false;




//make node
struct SCOPE* newScope(SCOPE_TYPE scope_type, struct SCOPE* parent_scope) {
    struct SCOPE* node = (struct SCOPE*) malloc (sizeof(struct SCOPE));
    node->scope_type = scope_type;
    node->dowhile_n = 0;
    node->while_n = 0;
    node->for_n  = 0;
    node->if_n = 0;
    node->compound_n = 0;

    if(parent_scope != NULL) {
        node->parent_scope = parent_scope;
        parent_scope->child_scope = node;
    } else {
        node->parent_scope = NULL;
    }

    node->child_scope = NULL;
    return node;
}

//scopeTail denotes curScope node
void deleteScope(struct SCOPE** scopeTail) {
    struct SCOPE* curScope = *scopeTail;
    struct SCOPE* parent_scope = curScope->parent_scope;
    if(parent_scope != NULL) {
        parent_scope->child_scope = NULL;
        (*scopeTail) = parent_scope;
        free(curScope);
      } 
      
//    free(curScope);
}

//returns the order of current SCOPE
int getMyOrder(SCOPE_TYPE scope_type, struct SCOPE* parent_scope) {
    switch(scope_type) {
        case Scope_Do_While_Type:
            return (parent_scope->dowhile_n);

        case Scope_While_Type:
            return (parent_scope->while_n);

        case Scope_For_Type:
            return (parent_scope->for_n);

        case Scope_If_Type:
            return (parent_scope->if_n);

        case Scope_Stmt_Group_Type:
            return (parent_scope->compound_n);
    }
}








void printScopePath()
{
    //when printing global variable
    if (scopeTail->scope_type == Scope_Global_Type)
    {
        fprintf(table_file, "Global variables\n");
        return; //print nothing at "location"
    }
    else
    {
        fprintf(table_file, "\nFunction name : ");
        fprintf(table_file, "%s", current_func_name);
        struct SCOPE *curNode = scopeHead->child_scope; //start from Function node
        while (curNode->child_scope != NULL)
        {
            fprintf(table_file, " - ");
            switch (curNode->child_scope->scope_type)
            {
            case Scope_Do_While_Type:
                fprintf(table_file, "do_while");
                break;

            case Scope_While_Type:
                fprintf(table_file, "while");
                break;

            case Scope_For_Type:
                fprintf(table_file, "for");
                break;

            case Scope_If_Type:
                fprintf(table_file, "if");
                break;

            case Scope_Stmt_Group_Type:
                fprintf(table_file, "group_stmt");
                break;
            }
            fprintf(table_file, "(%d) ", getMyOrder(curNode->child_scope->scope_type, curNode));
            curNode = curNode->child_scope;
        }
        fprintf(table_file, "\n");
    }
}

//print symboltable
void printTitle()
{

    row_no = 1;

    printScopePath();
    fprintf(table_file, "%10s%10s%10s%10s%10s\n", "count", "scope_type", "name", "array", "role");
}

void printDeclaration(struct DECLARATION *declaration){
    is_parameter = false;
    if (declaration->prev != NULL)
        printDeclaration(declaration->prev);

    if (!print_title)
    {
        printTitle();
        print_title = true;
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
    printIdentifier(declaration->id);
    printed = false;
    fprintf(tree_file, ";\n");}

void printIdentifier(struct IDENTIFIER *identifier){
    fprintf(tree_file, "%s", identifier->ID);
    if (identifier->int_val > 0) //int arr[n]; n must be >0 to be valid
    {
        fprintf(tree_file, "[%d]", identifier->int_val);

        if (printed)
        {
            char *cur_type;
            if (current_type == Int_Type)
                cur_type = "int";
            else if (current_type == Float_Type)
                cur_type = "float";

            if (is_parameter)
                fprintf(table_file, "%10d%10s%10s%10d%10s\n", row_no++, cur_type, identifier->ID, identifier->int_val,"parameter");
            else
                fprintf(table_file, "%10d%10s%10s%10d%10s\n", row_no++, cur_type, identifier->ID, identifier->int_val,"variable");
            
        }
    }
    else if (identifier->int_val < 0) // int arr[-1]; there is no n = 0 is valid
    {
        fprintf(stderr, "error");
    }
    else //n = 0 this means int x;
    {
        if (!printed)
             return;
        
        char *cur_type;
        if (current_type == Int_Type)
            cur_type = "int";
        else if(current_type == Float_Type)
            cur_type = "float";
        fprintf(table_file, "%10d%10s%10s%10s%10s\n", row_no++, cur_type, identifier->ID, "", is_parameter ? "parameter" : "variable"); //row_no(x) ++row_no(x) row_no++(o)
    
    }}



void printFunction(struct FUNCTION *function){
    if (function->prev != NULL)
    {
        printFunction(function->prev);
    }
    current_func_name = function->ID;     //for symboltable

    //list node
    scopeTail = newScope(Scope_Func_Type, scopeTail); //append it to the end of list

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
    fprintf(tree_file, "%s (", function->ID); //add function name
    print_title = false;
    if (function->parameter != NULL)
    {
        printTitle();
        print_title = true;
        printParameter(function->parameter); //parameter
    }
    fprintf(tree_file, ")\n");                //function name
    printStmtGroup(function->stmts_group); //compoundStmt
    fprintf(tree_file, "\n");

    //deleteCurScope
    deleteScope(&scopeTail);
    print_title = false;}



void visitStmt(struct STMT *stmt){
    if (stmt->prev != NULL)
        visitStmt(stmt->prev);
    switch (stmt->stmt_type)
    {
    
    case Call_Type:
        
        fprintf(tree_file, "%s(", stmt->stmt.func_call->ID);
        if (stmt->stmt.func_call->arg != NULL)
        {
            visitArg(stmt->stmt.func_call->arg);
        }
        fprintf(tree_file, ")");
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

    case If_Type:
        _isOtherComp = true;
        struct IF_STMT *if_stmt  = stmt->stmt.if_stmt;
        //making node for symbol table
        scopeTail = newScope(Scope_If_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->if_n++;

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
        return;

    case For_Type:
        _isOtherComp = true;
        struct FOR_STMT *for_stmt = stmt->stmt.for_stmt;
         //making node for symbol table
        scopeTail = newScope(Scope_For_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->for_n++;

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

        
        return;

     case While_Type:
        _isOtherComp = true;
        struct WHILE_STMT *while_stmt = stmt->stmt.while_stmt;
        if (while_stmt->do_while == true)
        {
            //making node for symbol table
            scopeTail = newScope(Scope_Do_While_Type, scopeTail);
            print_title = false;
            scopeTail->parent_scope->dowhile_n++;

            fprintf(tree_file, "do");
            visitStmt(while_stmt->stmt);
            fprintf(tree_file, "while (");
            visitExpr(while_stmt->condition);
            fprintf(tree_file, ");\n");
        }
        else
        {
            //making node for symbol table
            scopeTail = newScope(Scope_While_Type, scopeTail);
            print_title = false;
            scopeTail->parent_scope->while_n++;

            fprintf(tree_file, "while (");
            visitExpr(while_stmt->condition);
            fprintf(tree_file, ")\n");
            visitStmt(while_stmt->stmt);
        }

        //deleteCurScope
        deleteScope(&scopeTail);
        return;
 
 
    case Equ_Type:
        visitAssignStmt(stmt->stmt.assign_stmt);
        fprintf(tree_file, ";");
        break;

    case Stmt_Group_Type:
        if (_isOtherComp == false)
            is_it_group_stmt = true;
        printStmtGroup(stmt->stmt.stmts_group);
        return;
        //break;

    case Semi_Colon_Type:
        fprintf(tree_file, ";");
        break;
    }
    fprintf(tree_file, "\n");}


void printParameter(struct PARAMETER *parameter){
    is_parameter = true;
    if (parameter->prev != NULL)
    {
        printParameter(parameter->prev);
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
    printIdentifier(parameter->id);
    printed = false;}
void printStmtGroup(struct STMTSGROUP *stmts_group){
    if (is_it_group_stmt == true)
    {
        //making node for symbol table
        scopeTail = newScope(Scope_Stmt_Group_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->compound_n++;
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

    if (is_it_group_stmt == true)
    {
        deleteScope(&scopeTail);
    }
    is_it_group_stmt = false;
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
        scopeTail = newScope(Scope_Do_While_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->dowhile_n++;

        fprintf(tree_file, "do");
        visitStmt(while_stmt->stmt);
        fprintf(tree_file, "while (");
        visitExpr(while_stmt->condition);
        fprintf(tree_file, ");\n");
    }
    else
    {
        //making node for symbol table
        scopeTail = newScope(Scope_While_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->while_n++;

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
    scopeTail = newScope(Scope_For_Type, scopeTail);
    print_title = false;
    scopeTail->parent_scope->for_n++;

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
    scopeTail = newScope(Scope_If_Type, scopeTail);
    print_title = false;
    scopeTail->parent_scope->if_n++;

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
