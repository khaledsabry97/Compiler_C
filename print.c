#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include <string.h>




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
struct Assembly* assemhead;
struct Assembly *temp;
int counter = 0;



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


/****Assembly***/

struct Assembly* newAssembly()
{
    return (struct Assembly*) malloc (sizeof (struct Assembly));
}

void push(struct Assembly* assem)
{
    if (assemhead == NULL)
    {
        assemhead = assem;
        assemhead->prev = NULL;
    }
    else
    {
        struct Assembly* temp2;
        temp2 = assemhead;
        assemhead = assem;
        assemhead->prev = temp2;
    }
    
};

struct Assembly* pop()
{
    if(assemhead == NULL)
    {
        return NULL;
    }
    else
    {
        struct Assembly* temp2;
        temp2 = assemhead;
        assemhead = assemhead->prev;
        return temp2;
    }
}

bool isEmpty()
{
    if(assemhead == NULL)
    return true;
    return false;

}
























void processDeclaration(struct DECLARATION *declaration){
    is_parameter = false;
    if (declaration->prev != NULL)
        processDeclaration(declaration->prev);

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
    processIdentifier(declaration->id);
    printed = false;
    fprintf(tree_file, ";\n");}

void processIdentifier(struct IDENTIFIER *identifier){
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



void processFunction(struct FUNCTION *function){
    if (function->prev != NULL)
    {
        processFunction(function->prev);
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
        processParameter(function->parameter); //parameter
    }
    fprintf(tree_file, ")\n");                //function name
    processStmtGroup(function->stmts_group); //compoundStmt
    fprintf(tree_file, "\n");

    //deleteCurScope
    deleteScope(&scopeTail);
    print_title = false;}



void processStmt(struct STMT *stmt){
    if (stmt->prev != NULL)
        processStmt(stmt->prev);
    switch (stmt->stmt_type)
    {
    
    case Call_Type:
        
        fprintf(tree_file, "%s(", stmt->stmt.func_call->ID);
        if (stmt->stmt.func_call->arg != NULL)
        {
            processArg(stmt->stmt.func_call->arg);
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
            processExpr(stmt->stmt.return_expr);
            fprintf(tree_file, ";");
        }
        break;

    case If_Type:
    {
        _isOtherComp = true;
        struct IF_STMT *if_stmt  = stmt->stmt.if_stmt;
        //making node for symbol table
        scopeTail = newScope(Scope_If_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->if_n++;

        fprintf(tree_file, "if (");
        processExpr(if_stmt->condition);
        fprintf(tree_file, ")\n");
        processStmt(if_stmt->if_stmt);
        if (if_stmt->else_stmt != NULL)
        {
            fprintf(tree_file, "\nelse\n");
            processStmt(if_stmt->else_stmt);
        }

        //deleteCurScope
        deleteScope(&scopeTail);        
        return;
    }

    case For_Type:
    {
        _isOtherComp = true;
        struct FOR_STMT *for_stmt = stmt->stmt.for_stmt;
         //making node for symbol table
        scopeTail = newScope(Scope_For_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->for_n++;

        fprintf(tree_file, "for (");
        processAssignStmt(for_stmt->init);
        fprintf(tree_file, "; ");
        processExpr(for_stmt->condition);
        fprintf(tree_file, "; ");
        processAssignStmt(for_stmt->inc);
        fprintf(tree_file, ")\n");
        processStmt(for_stmt->stmt);

        //deleteCurScope
        deleteScope(&scopeTail);

        
        return;
    }
     case While_Type:
     {
        _isOtherComp = true;
        struct WHILE_STMT *while_stmt = stmt->stmt.while_stmt;
        if (while_stmt->do_while == true)
        {
            //making node for symbol table
            scopeTail = newScope(Scope_Do_While_Type, scopeTail);
            print_title = false;
            scopeTail->parent_scope->dowhile_n++;

            //fprintf(tree_file, "do");
            int jump_lable = counter;
            fprintf(tree_file, "\n DO_WHILE%d:",counter++);

            processStmt(while_stmt->stmt);
            //fprintf(tree_file, "while (");
            processExpr(while_stmt->condition);
            struct Assembly* temp_expr = pop();
            fprintf(tree_file, "\n JIF %s , DO_WHILE%d",temp->str,jump_lable);
            fprintf(tree_file,"\n END__DO_WHILE%d:",counter++);
            //fprintf(tree_file, ");\n");
        }
        else
        {
            //making node for symbol table
            scopeTail = newScope(Scope_While_Type, scopeTail);
            print_title = false;
            scopeTail->parent_scope->while_n++;

            /*fprintf(tree_file, "while (");*/
            fprintf(tree_file, "\n WHILE%d:",counter++);
           
            processExpr(while_stmt->condition);
            int jump_lable = counter;
            struct Assembly* temp_expr = pop();
            
            fprintf(tree_file, "\n JIF %s , END_WHILE%d",temp->str,counter++);

            //fprintf(tree_file, ")\n");
            processStmt(while_stmt->stmt);
            fprintf(tree_file,"\n END_WHILE%d:",jump_lable);


        }

        //deleteCurScope
        deleteScope(&scopeTail);
        return;
 
     }
    case Equ_Type:
    {
        processAssignStmt(stmt->stmt.assign_stmt);
        fprintf(tree_file, ";");
        break;
    }
    case Stmt_Group_Type:
        if (_isOtherComp == false)
            is_it_group_stmt = true;
        processStmtGroup(stmt->stmt.stmts_group);
        return;
        //break;

    case Semi_Colon_Type:
        fprintf(tree_file, ";");
        break;
    }
    fprintf(tree_file, "\n");}


void processParameter(struct PARAMETER *parameter){
    is_parameter = true;
    if (parameter->prev != NULL)
    {
        processParameter(parameter->prev);
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
    processIdentifier(parameter->id);
    printed = false;}
void processStmtGroup(struct STMTSGROUP *stmts_group){
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
        processDeclaration(stmts_group->declaration);
    }
    if (stmts_group->stmt != NULL)
        processStmt(stmts_group->stmt);
    fprintf(tree_file, "}\n");

    if (is_it_group_stmt == true)
    {
        deleteScope(&scopeTail);
    }
    is_it_group_stmt = false;
    _isOtherComp = false;
}
void processAssignStmt(struct ASSIGN_STMT *assign)
{
    fprintf(tree_file, "%s ", assign->ID);
    if (assign->index != NULL)
    {
        fprintf(tree_file, "[");
        processExpr(assign->index);
        fprintf(tree_file, "]");
    }
    fprintf(tree_file, " = ");
    processExpr(assign->expr);
}

void processArg(struct ARG *arg)
{
    if (arg->prev != NULL)
    {
        processArg(arg->prev);
        fprintf(tree_file, ", ");
    }
    processExpr(arg->expr);
}
void processExpr(struct EXPR *expr)
{

    switch (expr->expr_type)
    {

    case Id_Type:
    {
        printf("\n Id_Type \n");

        fprintf(tree_file,"");
        struct ID_EXPR *id_expr = expr->expression.id_expr;
        fprintf(tree_file, "%s", id_expr->ID);
        if (id_expr->expr != NULL)
        {
            fprintf(tree_file, "[");
            processExpr(id_expr->expr);
            fprintf(tree_file, "]");
        }

        break;
    }
    case IntNum_Type:

    {
        //fprintf(tree_file, "%d", expr->expression.int_val);
        fprintf(tree_file, "");
        temp = newAssembly();
        temp->int_val = expr->expression.int_val;
        //temp->str = expr->expression.int_val;
        sprintf(temp->str, "%d", expr->expression.int_val);

        push(temp);
        break;
    }

    case FloatNum_Type:
        fprintf(tree_file, "%f", expr->expression.floatval);
        break;

    case Uni_Type:
        fprintf(tree_file, "-");
        processExpr(expr->expression.uni_op->expr);
        break;

    case Add_Type:
        processExpr(expr->expression.add_op->left_side);
        processExpr(expr->expression.add_op->right_side);

        if (expr->expression.add_op->add_type == Plus_Type)
            fprintf(tree_file, " + ");
        else
            fprintf(tree_file, " - ");
        break;

    case Mult_Type:

        processExpr(expr->expression.mul_op->left_side);
        if (expr->expression.mul_op->mul_type == Mul_Type)
            fprintf(tree_file, " * ");
        else
            fprintf(tree_file, " / ");
        processExpr(expr->expression.mul_op->right_side);
        break;

    case Com_Type:
    {
        //printf("compare");
        processExpr(expr->expression.com_op->left_side);
        processExpr(expr->expression.com_op->right_side);
        struct Assembly* right = pop();
        struct Assembly* left = pop();
        int ret_counter = counter;
        temp = newAssembly();
        sprintf(temp->str, "RES%d", ret_counter);
        push(temp);

        switch (expr->expression.com_op->com_type)
        {
        case Lt_Type:
            //fprintf(tree_file, " < ");
            fprintf(tree_file, "\n CMPL %s , %s , RES%d ",left->str,right->str,counter++);

            break;

        case Gt_Type:
           {
            fprintf(tree_file, "\n CMPG %s , %s , RES%d ",left->str,right->str,counter++);
            break;
           }

        case Le_Type:
            //fprintf(tree_file, " <= ");
            fprintf(tree_file, "\n CMPLE %s , %s , RES%d ",left->str,right->str,counter++);

            break;

        case Ge_Type:
            //fprintf(tree_file, " >= ");
            fprintf(tree_file, "\n CMPGE %s , %s , RES%d ",left->str,right->str,counter++);

            break;
        }
        break;
    }
    case Eql_Type:
    {
        processExpr(expr->expression.eql_op->left_side);
        processExpr(expr->expression.eql_op->right_side);
        struct Assembly* right = pop();
        struct Assembly* left = pop();
        int ret_counter = counter;
        temp = newAssembly();
        sprintf(temp->str, "RES%d", ret_counter);
        push(temp);

        if (expr->expression.eql_op->eql_type == Eq_Type)
        {
            //fprintf(tree_file, " == ");
            fprintf(tree_file, "\n CMPE %s , %s , RES%d ",left->str,right->str,counter++);

        }
        else
        {
            //fprintf(tree_file, " != ");
            fprintf(tree_file, "\n CMPNE %s , %s , RES%d ",left->str,right->str,counter++);

        }
        break;
    }

    case CallExpr_Type:
    {
        fprintf(tree_file,"");
        struct FUNC_CALL *call = expr->expression.func_call;
        fprintf(tree_file, "%s(", call->ID);
        if (call->arg != NULL)
        {
            processArg(call->arg);
        }
        fprintf(tree_file, ")");
        break;
    }
    case Expr_Type:
    {
        fprintf(tree_file, "(");
        processExpr(expr->expression.bracket);
        fprintf(tree_file, ")");
        break;


    }
    }
}



//JIF RES,JUMB_LABLE // JUMP IF RES > 0 to JUMB_LABLE
//CMPG X,Y,Z //COMPARE IF X GREATER THAN Y SET Z = 1 ELSE SET Z =-1
//CMPL X,Y,Z //COMPARE IF X LOWER THAN Y SET Z = 1 ELSE SET Z =-1
//CMPGE X,Y,Z //COMPARE IF X GREATER THAN OR EQUAL Y SET Z = 1 ELSE SET Z =-1
//CMPLE X,Y,Z //COMPARE IF X LOWER THAN OR EQUAL Y SET Z = 1 ELSE SET Z =-1
//CMPE X,Y,Z //COMPARE IF X EQUAL Y SET Z = 1 ELSE SET Z =-1
//CMPNE X,Y,Z //COMPARE IF X NOT EQUAL Y SET Z = 1 ELSE SET Z =-1