#include <stdio.h>
#include <stdlib.h>
#include "Semantic_Handler.h"
#include <string.h>

extern FILE *tree_file;
extern FILE *table_file;
extern FILE *semantic_file;

char *result;

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
int parameter_count = 1;
struct CHECKS* temp_check;
struct Semantic* temp_semantic;
struct SEMANTIC_STACK* temp_semantic_stack;



//make node
struct SCOPE* newScope(SCOPE_TYPE scope_type, struct SCOPE* parent_scope) {
    struct SCOPE* node = (struct SCOPE*) malloc (sizeof(struct SCOPE));
    node->scope_type = scope_type;
    node->do_while_count = 0;
    node->while_count = 0;
    node->for_count  = 0;
    node->if_count = 0;
    node->stmt_group_count = 0;
    if(scope_type == Scope_Global_Type)
        node->name = "Global Variables";
    node->name = current_func_name; //only important for function scope

    if(parent_scope != NULL) 
        parent_scope->child_scope = node;
    node->parent_scope = parent_scope;
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
            return (parent_scope->do_while_count);

        case Scope_While_Type:
            return (parent_scope->while_count);

        case Scope_For_Type:
            return (parent_scope->for_count);

        case Scope_If_Type:
            return (parent_scope->if_count);

        case Scope_Stmt_Group_Type:
            return (parent_scope->stmt_group_count);
    }
}






//char to_print[1200];


char* printScopePath(char* to_print1)
{
char to_print[1200];
//char *to_print = (char *)malloc(1000);

    //when printing global variable
    if (scopeTail->scope_type == Scope_Global_Type)
    {
        fprintf(table_file, "Global Variables\n");
        sprintf(to_print, "Global Variables\n");
        return to_print;
    }

    fprintf(table_file, "\nFunction name => ");
    sprintf(to_print, "\nFunction name => ");
    sprintf(to_print1, "\nFunction name => ");

    fprintf(table_file, "%s", current_func_name);
    sprintf(to_print, "%s %s", to_print,current_func_name);

    struct SCOPE *curNode = scopeHead->child_scope; //start from Function node
    while (curNode->child_scope != NULL)
    {
        fprintf(table_file, " - ");
        sprintf(to_print, "%s - ", to_print);

        switch (curNode->child_scope->scope_type)
        {
        case Scope_Do_While_Type:
            fprintf(table_file, "do_while");
            sprintf(to_print, "%s do_while ", to_print);

            break;

        case Scope_While_Type:
            fprintf(table_file, "while");
            sprintf(to_print, "%s while ", to_print);

            break;

        case Scope_For_Type:
            fprintf(table_file, "for");
            sprintf(to_print, "%s for ", to_print);

            break;

        case Scope_If_Type:
            fprintf(table_file, "if");
            sprintf(to_print, "%s if ", to_print);

            break;

        case Scope_Stmt_Group_Type:
            fprintf(table_file, "group_stmt");
            sprintf(to_print, "%s group_stmt ", to_print);

            break;
        }
        fprintf(table_file, "[%d]", getMyOrder(curNode->child_scope->scope_type, curNode));
        sprintf(to_print, "%s [%d] ", to_print,getMyOrder(curNode->child_scope->scope_type, curNode));

        curNode = curNode->child_scope;
    }
    fprintf(table_file, "\n");
    sprintf(to_print, "%s\n ", to_print);
    //char* results = (char*)malloc(sizeof(char) * strlen(to_print)+1); 
    //strcpy(results,to_print);
    //printf("%s \n", &to_print[0]);
    //printf("%s \n", results);
    //strcat(results,to_print);
    //printf("%s \n", results);
    //strcpy (to_print1, to_print);
   

    //printf("%s \n", to_print1);


    return to_print1;
}







//print symboltable
void printTitle()
{

    row_no = 1;
    char s[1000];
    printScopePath(s);

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
        //fprintf(tree_file, "int ");
        current_type = Int_Type;
        break;
    case Float_Type:
        //fprintf(tree_file, "float ");
        current_type = Float_Type;
        break;
    default:
        fprintf(stderr, "declaration does not exist.\n");
        exit(1);
    }
    printed = true;
    processIdentifier(declaration->id);
    printed = false;

    //fprintf(tree_file, ";\n");
    }

void processIdentifier(struct IDENTIFIER *identifier){
    //fprintf(tree_file, "%s", identifier->ID);
    /*if (identifier->int_val > 0) //int arr[n]; n must be >0 to be valid
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
    }*/
    if (identifier->int_val < 0) // int arr[-1]; there is no n = 0 is valid
    {
        fprintf(stderr, "error");
    }
    if (identifier->int_val == 0) //n = 0 this means int x;
    {
        if (!printed)
             return;
        


        struct Semantic* temp_semantic_identifier = newSemantic();
        temp_semantic_identifier->identifier_name = identifier->ID;

        char *cur_type;
        if (current_type == Int_Type)
        {
            cur_type = "int";
            temp_semantic_identifier->identifier_semantic_type= Int_Semantic_Type;

        }
        else if(current_type == Float_Type)
        {
            cur_type = "float";
            temp_semantic_identifier->identifier_semantic_type= Float_Semantic_Type;
        }
        fprintf(table_file, "%10d%10s%10s%10s%10s\n", row_no++, cur_type, identifier->ID, "", is_parameter ? "parameter" : "variable"); //row_no(x) ++row_no(x) row_no++(o)
        if(is_parameter== true)
        {
            temp = newAssembly();
            sprintf(temp->str, identifier->ID);
            push(temp);
        }
        temp_semantic_identifier->is_assigned = false;
        temp_semantic_identifier->is_function = false;
        temp_semantic_identifier->scope = scopeHead;
        temp_semantic_identifier->is_parameter = is_parameter;
    
        int count = checkSemantic(temp_semantic_identifier->identifier_name,false,temp_semantic_identifier->scope,NULL,temp_semantic_identifier->identifier_semantic_type);
        if(count != 0)
        fprintf(semantic_file,"ERORR: variable %s has been declared before %d times before \n",temp_semantic_identifier->identifier_name,count);
        addNewSemantic(temp_semantic_identifier);
        if(is_parameter == true)
        {
            addArgsToSemantic(temp_semantic,temp_semantic_identifier->identifier_semantic_type);
        }



        
    
    }}



void processFunction(struct FUNCTION *function){

    if (function->prev != NULL)
    {
        processFunction(function->prev);
    }
    //struct Semantic *semantic = (struct Semantic*) malloc (sizeof (struct Semantic));
    temp_semantic = newSemantic();
    current_func_name = function->ID;     //for symboltable
    switch (function->id_type)
        {
        case Int_Type:
            //fprintf(tree_file, "int ");
            temp_semantic->identifier_semantic_type = Int_Semantic_Type;

            break;
        case Float_Type:
            //fprintf(tree_file, "float ");
            temp_semantic->identifier_semantic_type = Float_Semantic_Type;

            break;
        default:
            fprintf(stderr, "Declaration does not exist.\n");
            exit(1);
        }
    temp_check = newCheck();
    temp_check->check_identifier_type = true;
    //char* c = printScopePath(temp_semantic->scope);
    //printf("%s \n",temp_semantic->scope);
    //printf("%s \n",c);

    //free(c);
   

    //list node
    scopeTail = newScope(Scope_Func_Type, scopeTail); //append it to the end of list
    temp_semantic->scope = scopeHead;

    int count = checkSemantic(function->ID,true,temp_semantic->scope,temp_check,temp_semantic->identifier_semantic_type);
    if(count != 0)
        fprintf(semantic_file,"ERORR: function %s appeared %d times before \n",function->ID,count);
    temp_semantic->identifier_name = function->ID;
    temp_semantic->is_function = true;
    addNewSemantic(temp_semantic);

    //fprintf(tree_file, "%s (", function->ID); //add function name
    fprintf(tree_file, "\n\n %s:",function->ID);


    if(strcmp(function->ID,"main")!= 0)
    {
        int jump_lable =  counter;
        fprintf(tree_file,"\n MOV $0 , %s_RET%d",function->ID,counter++);
        temp = newAssembly();
        sprintf(temp->str, "%s_RET%d", function->ID,jump_lable);
        push(temp);
    }
    print_title = false;
    if (function->parameter != NULL)
    {

        printTitle();
        print_title = true;
        parameter_count = 1;

        processParameter(function->parameter); //parameter
    }
    if(strcmp(function->ID,"main") != 0)
     fprintf(tree_file,"\n CLRQ");

    //fprintf(tree_file, ")\n");                //function name
    processStmtGroup(function->stmts_group); //compoundStmt

    
    fprintf(tree_file, "\n\n");

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
            if(isEmpty()) //then it's the main return
                fprintf(tree_file,"\n HALT");
            else
            {
                fprintf(tree_file,"\n JMP %s",pop()->str);
            }
            
        }
        else
        {
            if(isEmpty()) //then it's the main return
                fprintf(tree_file,"\n HALT");
            else
            {

                //fprintf(tree_file, "return ");
                processExpr(stmt->stmt.return_expr,false);
                fprintf(tree_file,"\n BIND %s",pop()->str);
                fprintf(tree_file,"\n JMP %s",pop()->str);
                //fprintf(tree_file, ";");
            }
            
         
        }
        break;

    case If_Type:
    {
        _isOtherComp = true;
        struct IF_STMT *if_stmt  = stmt->stmt.if_stmt;
        //making node for symbol table
        scopeTail = newScope(Scope_If_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->if_count++;

        //fprintf(tree_file, "if (");
        fprintf(tree_file, "\n IF%d:",counter++);
        processExpr(if_stmt->condition,true);
        int jump_lable = counter;
        struct Assembly* temp_expr = pop();
        fprintf(tree_file, "\n JIFN %s , END_IF%d",temp_expr->str,counter++);

        //fprintf(tree_file, ")\n");
        processStmt(if_stmt->if_stmt);
        int sec_jump_lable = counter;
        fprintf(tree_file,"\n JMP END_IF%d:",counter++);
        fprintf(tree_file,"\n END_IF%d:",jump_lable);
        if (if_stmt->else_stmt != NULL)
        {
            //fprintf(tree_file, "\nelse\n");
            processStmt(if_stmt->else_stmt);
        }

        fprintf(tree_file,"\n END_IF%d:",sec_jump_lable);


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
        scopeTail->parent_scope->for_count++;

        //fprintf(tree_file, "for (");
        int first_jump_lable = counter;
        processAssignStmt(for_stmt->init);
        fprintf(tree_file, "\n FOR%d:",counter++);

        //fprintf(tree_file, "; ");
        processExpr(for_stmt->condition,true);
        int jump_lable = counter;
        struct Assembly* temp_expr = pop();
        fprintf(tree_file, "\n JIFN %s , END_FOR%d",temp_expr->str,counter++);

        //fprintf(tree_file, "; ");
        processAssignStmt(for_stmt->inc);
        //fprintf(tree_file, ")\n");
        processStmt(for_stmt->stmt);
        fprintf(tree_file, "\n JMP FOR%d",first_jump_lable);
        fprintf(tree_file,"\n END_FOR%d:",jump_lable);

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
            scopeTail->parent_scope->do_while_count++;

            //fprintf(tree_file, "do");
            int jump_lable = counter;
            fprintf(tree_file, "\n DO_WHILE%d:",counter++);

            processStmt(while_stmt->stmt);
            //fprintf(tree_file, "while (");
            processExpr(while_stmt->condition,true);
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
            scopeTail->parent_scope->while_count++;

            /*fprintf(tree_file, "while (");*/
            int first_jump_lable = counter;
            fprintf(tree_file, "\n WHILE%d:",counter++);
           
            processExpr(while_stmt->condition,true);
            int jump_lable = counter;
            struct Assembly* temp_expr = pop();
            
            fprintf(tree_file, "\n JIFN %s , END_WHILE%d",temp_expr->str,counter++);

            //fprintf(tree_file, ")\n");
            processStmt(while_stmt->stmt);
            fprintf(tree_file, "\n JMP WHILE%d",first_jump_lable);
            fprintf(tree_file,"\n END_WHILE%d:",jump_lable);


        }

        //deleteCurScope
        deleteScope(&scopeTail);
        return;
 
     }
    case Equ_Type:
    {
        processAssignStmt(stmt->stmt.assign_stmt);
        //fprintf(tree_file, ";");
        break;
    }
    case Stmt_Group_Type:
        if (_isOtherComp == false)
            is_it_group_stmt = true;
        processStmtGroup(stmt->stmt.stmts_group);
        return;
        //break;

    case Semi_Colon_Type:
        //fprintf(tree_file, ";");
        break;
    }
    //fprintf(tree_file, "\n");
    }


void processParameter(struct PARAMETER *parameter){
    is_parameter = true;

    if (parameter->prev != NULL)
    {
        processParameter(parameter->prev);
        //fprintf(tree_file, ", ");
    }
    switch (parameter->id_type)
    {
    case Int_Type:
        //fprintf(tree_file, "int ");
        current_type = Int_Type;
        break;
    case Float_Type:
        //fprintf(tree_file, "float ");
        current_type = Float_Type;
        break;
    default:
        fprintf(stderr, "Declaration does not exist.\n");
        exit(1);
    }
    printed = true;

    processIdentifier(parameter->id);
    printed = false;

    temp = pop();
    fprintf(tree_file,"\n MOV $%d , %s",parameter_count++,temp->str);

    }

void processStmtGroup(struct STMTSGROUP *stmts_group){
    if (is_it_group_stmt == true)
    {
        //making node for symbol table
        scopeTail = newScope(Scope_Stmt_Group_Type, scopeTail);
        print_title = false;
        scopeTail->parent_scope->stmt_group_count++;
    }
    _isOtherComp = false;

    fprintf(tree_file, "\n");
    if (stmts_group->declaration != NULL)
    {
        processDeclaration(stmts_group->declaration);
    }
    if (stmts_group->stmt != NULL)
        processStmt(stmts_group->stmt);
    fprintf(tree_file, "\n");

    if (is_it_group_stmt == true)
    {
        deleteScope(&scopeTail);
    }
    is_it_group_stmt = false;
    _isOtherComp = false;
}
void processAssignStmt(struct ASSIGN_STMT *assign)
{
    //fprintf(tree_file, "%s ", assign->ID);
    /*if (assign->index != NULL)
    {
        fprintf(tree_file, "[");
        processExpr(assign->index);
        fprintf(tree_file, "]");
    }
    */
    //fprintf(tree_file, " = ");
    processExpr(assign->expr,true);

        //check if identifier was found

    struct Semantic* semantic_temp = findSemanticIdentifier(assign->ID);
    if(semantic_temp == NULL)
        {
            fprintf(semantic_file,"ERROR: Identifier %s wasn't declared before to use it in an assignment\n",assign->ID);
        }
    else
    {

        //check if identifier type match todo and assign identifier
            temp_semantic_stack = popSemanticStack();
        //printf("%d\n",temp_semantic_stack);

        if (temp_semantic_stack->identifier_semantic_type != semantic_temp->identifier_semantic_type)
        {
            if(temp_semantic_stack->identifier_semantic_type == Error_Semantic_Type)
            {
            fprintf(semantic_file,"ERROR: Solve previous error\n",assign->ID);

            }
            else
            fprintf(semantic_file,"ERROR: Identifier %s is not the same type of the assignment\n",assign->ID);
        }
        else
        {
            semantic_temp->is_assigned = true;            
        }
    }

    fprintf(tree_file, "\n MOV %s , %s",pop()->str,assign->ID);

}

void processArg(struct ARG *arg)
{
    if (arg->prev != NULL)
    {
        processArg(arg->prev);
        //fprintf(tree_file, ", ");
    }
    processExpr(arg->expr,true);
    temp = pop();
    fprintf(tree_file,"\n BIND %s , $%d",temp->str,parameter_count++);

    temp_semantic_stack = popSemanticStack();
    pushSemanticStack(temp_semantic_stack);


}
void processExpr(struct EXPR *expr,bool must_return)
{

    switch (expr->expr_type)
    {

    case Id_Type: // some_variable = ID;
    {
        struct ID_EXPR *id_expr = expr->expression.id_expr;
        //fprintf(tree_file, "%s", id_expr->ID);
        /*if (id_expr->expr != NULL)
        {
            fprintf(tree_file, "[");
            processExpr(id_expr->expr);
            fprintf(tree_file, "]");
        }
        */
        temp = newAssembly();
        sprintf(temp->str, "%s", id_expr->ID);
        push(temp);

        //check identifier is found
        temp_semantic = findSemanticIdentifier(id_expr->ID);
        printf("hellor");
        if(temp_semantic == NULL )
        {
                fprintf(semantic_file,"ERROR: Identifier %s wasn't declared before to be used\n",id_expr->ID);
                 //add to semantic stack
            temp_semantic_stack = newSemanticStack();
            temp_semantic_stack->identifier_semantic_type = Error_Semantic_Type;
            pushSemanticStack(temp_semantic_stack);
        }

        else if(temp_semantic->is_assigned == false && temp_semantic->is_parameter == false)
        {
            fprintf(semantic_file,"ERROR: Identifier %s wasn't assigned any value before to be used\n",id_expr->ID);
                 //add to semantic stack
            temp_semantic_stack = newSemanticStack();
            temp_semantic_stack->identifier_semantic_type = temp_semantic->identifier_semantic_type;
            pushSemanticStack(temp_semantic_stack);
        }
        else
        {
             //add to semantic stack
            temp_semantic_stack = newSemanticStack();
            temp_semantic_stack->identifier_semantic_type = temp_semantic->identifier_semantic_type;
            pushSemanticStack(temp_semantic_stack);
            
        }
        break;
    }
    case IntNum_Type:

    {
        //fprintf(tree_file, "%d", expr->expression.int_val);
        temp = newAssembly();
        sprintf(temp->str, "%d", expr->expression.int_val);
        push(temp);
        //add to semantic stack
        printf("j");
        temp_semantic_stack = newSemanticStack();
        temp_semantic_stack->identifier_semantic_type = Int_Semantic_Type;
        pushSemanticStack(temp_semantic_stack);
        break;
    }

    case FloatNum_Type:
        //fprintf(tree_file, "%f", expr->expression.floatval);
        temp = newAssembly();
        sprintf(temp->str, "%d", expr->expression.floatval);
        push(temp);
        //add to semantic stack
        temp_semantic_stack = newSemanticStack();
        temp_semantic_stack->identifier_semantic_type = Float_Semantic_Type;
        pushSemanticStack(temp_semantic_stack);

        break;

    case Uni_Type:
    {
        //fprintf(tree_file, "-");
        processExpr(expr->expression.uni_op->expr,true);
        struct Assembly* right = pop();
        int ret_counter = counter;
        temp = newAssembly();
        sprintf(temp->str, "UNI_RES%d", ret_counter);
        push(temp);
        fprintf(tree_file, "\n MUL %s , %s , UNI_RES%d ",right->str,"-1",counter++);
        //add to semantic stack
        printf("SdfsdF");
        temp_semantic_stack = popSemanticStack();
        pushSemanticStack(temp_semantic_stack);
        break;
    }

    case Add_Type:
        processExpr(expr->expression.add_op->left_side,true);
        processExpr(expr->expression.add_op->right_side,true);
        struct Assembly* right = pop();
        struct Assembly* left = pop();
        int ret_counter = counter;
        temp = newAssembly();
        if (expr->expression.add_op->add_type == Plus_Type)
        {
            //fprintf(tree_file, " + ");
            sprintf(temp->str, "ADD_RES%d", ret_counter);
            fprintf(tree_file, "\n ADD %s , %s , ADD_RES%d ",left->str,right->str,counter++);
        }
        else
        {
            //fprintf(tree_file, " - ");
            sprintf(temp->str, "SUB_RES%d", ret_counter);

            fprintf(tree_file, "\n SUB %s , %s , SUB_RES%d ",left->str,right->str,counter++);
        }
        push(temp);

        //add to semantic stack
        struct SEMANTIC_STACK* left_semantic = popSemanticStack();
        struct SEMANTIC_STACK* right_semantic = popSemanticStack();
        temp_semantic_stack = newSemanticStack();
        temp_semantic_stack->identifier_semantic_type = compareTypes(left_semantic->identifier_semantic_type,right_semantic->identifier_semantic_type);
        if(temp_semantic_stack->identifier_semantic_type == Error_Semantic_Type)
        {
            fprintf(semantic_file,"Error: two different identifier one is bool and other is float/int\n");

        }
        pushSemanticStack(temp_semantic_stack);


        break;

    case Mult_Type:
{
        processExpr(expr->expression.mul_op->left_side,true);
        processExpr(expr->expression.mul_op->right_side,true);
        struct Assembly* right = pop();
        struct Assembly* left = pop();
        int ret_counter = counter;
        temp = newAssembly();
        if (expr->expression.mul_op->mul_type == Mul_Type)
        {
            //fprintf(tree_file, " * ");
            sprintf(temp->str, "MUL_RES%d", ret_counter);
            fprintf(tree_file, "\n MUL %s , %s , MUL_RES%d ",left->str,right->str,counter++);
        }
        else
        {
            //fprintf(tree_file, " / ");
            sprintf(temp->str, "DIV_RES%d", ret_counter);
            fprintf(tree_file, "\n DIV %s , %s , DIV_RES%d ",left->str,right->str,counter++);
        }
        push(temp);



        struct SEMANTIC_STACK* left_semantic = popSemanticStack();
        struct SEMANTIC_STACK* right_semantic = popSemanticStack();
        temp_semantic_stack = newSemanticStack();
        temp_semantic_stack->identifier_semantic_type = compareTypes(left_semantic->identifier_semantic_type,right_semantic->identifier_semantic_type);
        if(temp_semantic_stack->identifier_semantic_type == Error_Semantic_Type)
        {
            fprintf(semantic_file,"Error: two different identifier one is bool and other is float/int\n");

        }
        pushSemanticStack(temp_semantic_stack);

        break;
}
    case Com_Type:
    {
        //printf("compare");
        processExpr(expr->expression.com_op->left_side,true);
        processExpr(expr->expression.com_op->right_side,true);
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


        struct SEMANTIC_STACK* left_semantic = popSemanticStack();
        struct SEMANTIC_STACK* right_semantic = popSemanticStack();
        temp_semantic_stack = newSemanticStack();
        if(left_semantic->identifier_semantic_type == Error_Semantic_Type || right_semantic->identifier_semantic_type == Error_Semantic_Type)
        {
            printf("er\n");
        }
        else
        {
            temp_semantic_stack->identifier_semantic_type = Bool_Semantic_Type;
            pushSemanticStack(temp_semantic_stack);

        }
        
        break;
    }
    case Eql_Type:
    {
        processExpr(expr->expression.eql_op->left_side,true);
        processExpr(expr->expression.eql_op->right_side,true);
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


        struct SEMANTIC_STACK* left_semantic = popSemanticStack();
        struct SEMANTIC_STACK* right_semantic = popSemanticStack();
        temp_semantic_stack = newSemanticStack();
        if(left_semantic->identifier_semantic_type == Error_Semantic_Type || right_semantic->identifier_semantic_type == Error_Semantic_Type)
        {
            printf("er\n");
        }
        else
        {
            temp_semantic_stack->identifier_semantic_type = Bool_Semantic_Type;
            pushSemanticStack(temp_semantic_stack);

        }

        break;
    }

    case CallExpr_Type:
    {
        //fprintf(tree_file,"");
        struct FUNC_CALL *call = expr->expression.func_call;
        int jump_lable = counter;
        fprintf(tree_file,"\n BIND %s%d",call->ID,counter++);


    
        if (call->arg != NULL)
        {
            parameter_count = 1;
            processArg(call->arg);
        }

        
        //check function existance
        struct SEMANTIC_STACK* args_stack;
        args_stack = NULL;
        int parmater_count_temp = parameter_count -1;
        
        while(parmater_count_temp > 0)
        {
            printf("h%dh\n",parmater_count_temp);
            if (args_stack == NULL)
            {
                args_stack = popSemanticStack();
                args_stack->prev = NULL;
            }
            else
            {
                struct SEMANTIC_STACK* temp2;
                temp2 = args_stack;
                args_stack = popSemanticStack();
                args_stack->prev = temp2;
            }
            parmater_count_temp = parmater_count_temp - 1;
        }
        
        printf("args%d\n",args_stack);
        temp_semantic = findSemanticFunction(call->ID,args_stack);
        temp_semantic_stack = newSemanticStack();
        printf("%d\n",temp_semantic);
        if (temp_semantic == NULL)
        {
            fprintf(semantic_file,"ERROR: didn't found any function matching the types or number of arguments\n");
            temp_semantic_stack->identifier_semantic_type = Error_Semantic_Type;
        }
        else
        {
            printf("found%d\n",temp_semantic->identifier_semantic_type);
            temp_semantic_stack->identifier_semantic_type = temp_semantic->identifier_semantic_type;
        }
        pushSemanticStack(temp_semantic_stack);








        fprintf(tree_file, "\n JMP %s", call->ID);
        fprintf(tree_file,"\n %s%d:",call->ID,jump_lable);
        //TO DO IN ASSEMBLY CHECK if it's a return type function or not
        int sec_counter = counter;
        if (must_return == true)
        {
            temp = newAssembly();
            sprintf(temp->str, "RET_VAL%d", sec_counter);
            push(temp);
            fprintf(tree_file, "\n MOV $1 , RET_VAL%d", counter++);
        }

        //fprintf(tree_file, ")");
        break;
    }
    case Expr_Type:
    {
        //fprintf(tree_file, "(");
        processExpr(expr->expression.bracket,false);
        //fprintf(tree_file, ")");
        break;


    }
    }
}



//JIF RES,JUMB_LABLE // JUMP IF RES > 0 to JUMB_LABLE
//JIFN RES,JUMB_LABLE // JUMP IF RES < 0 to JUMB_LABLE

//CMPG X,Y,Z //COMPARE IF X GREATER THAN Y SET Z = 1 ELSE SET Z =-1
//CMPL X,Y,Z //COMPARE IF X LOWER THAN Y SET Z = 1 ELSE SET Z =-1
//CMPGE X,Y,Z //COMPARE IF X GREATER THAN OR EQUAL Y SET Z = 1 ELSE SET Z =-1
//CMPLE X,Y,Z //COMPARE IF X LOWER THAN OR EQUAL Y SET Z = 1 ELSE SET Z =-1
//CMPE X,Y,Z //COMPARE IF X EQUAL Y SET Z = 1 ELSE SET Z =-1
//CMPNE X,Y,Z //COMPARE IF X NOT EQUAL Y SET Z = 1 ELSE SET Z =-1

//ADD X,Y,Z //ADD X + Y AND STORE RESULT IN Z
//SUB X,Y,Z //SUB X - Y AND STORE RESULT IN Z
//MUL X,Y,Z //MULTIPLY X * Y AND STORE RESULT IN Z
//DIV X,Y,Z //DIVIDE X / Y AND STORE RESULT IN Z

//MOV X,Y //MOV X TO Y SO Y=X


//BIND X , $x //SEND PARAMTER X BY ATTCHING IT TO RESERVED VARIABLES IN MEMORY SPECIALIZED FOR FUNCTIONS
//CLRQ //CLEAR THE VALUES IN $x CALL IT AFTER FINISHING MOVING PARAMTER TO LOCAL FUNCTION DOMAIN
//$x // x COULD BE A VALUE FROM 0 TO N, $0 SPECIAL FOR RETURN POINTER

//HALT //STOP PROGRAM







