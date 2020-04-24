#include <stdio.h>
#include <stdlib.h>
#include "Semantic_Handler.h"
#include <string.h>


char *result;
int row_no;
ID_TYPE current_type;
bool is_parameter = false;
bool printed = false;
bool title = false;
bool outside_group_stmt = false;
bool inside_group_stmt = false;
struct Assembly* assemhead;
struct Assembly *temp;
int counter = 0;
int parameter_count = 1;
struct CHECKS* temp_check;
struct Semantic* temp_semantic;
struct SEMANTIC_STACK* temp_semantic_stack;
struct BLOCK *current_block_ptr;
char* current_func_name;
int current_func_number;
extern FILE *assembly_file;
extern FILE *symbol_file;
extern FILE *semantic_file;



struct BLOCK* newBlock(struct BLOCK* parent_block, BLOCK_TYPE block_type) {
    struct BLOCK* node = (struct BLOCK*) malloc (sizeof(struct BLOCK));
    node->if_count = 0;
    node->for_count  = 0;
    node->while_count = 0;
    node->do_while_count = 0;
    node->stmt_group_count = 0;
    node->block_type = block_type;
    if(block_type == Block_Global_Type)
        sprintf(node->name, "Global Variables");
    else
    //node->name = current_func_name; //only important for function blcok
        sprintf(node->name, "%s",current_func_name);

    //sprintf(node->name,"%s",current_func_name);

    node->function_number = current_func_number;
    if(parent_block != NULL) 
        parent_block->child_block = node;
    node->parent_block = parent_block;
    node->child_block = NULL;

    //printf("curr %s\n",node->name);
    return node;
}

void removeBlock(struct BLOCK** current_block_ptr) {
    if((*current_block_ptr)->parent_block == NULL)
        return; 
    (*current_block_ptr)->parent_block->child_block = NULL;
    (*current_block_ptr) = (*current_block_ptr)->parent_block;
}

//returns the order of current BLOCK
int getMyOrder(BLOCK_TYPE block_type, struct BLOCK* parent_block) {
    switch(block_type) {
        case Block_Do_While_Type:
            return (parent_block->do_while_count);

        case Block_While_Type:
            return (parent_block->while_count);

        case Block_For_Type:
            return (parent_block->for_count);

        case Block_If_Type:
            return (parent_block->if_count);

        case Block_Stmt_Group_Type:
            return (parent_block->stmt_group_count);
    }
}






//char to_print[1200];


char* printScopePath(char* to_print1)
{
char to_print[1200];
//char *to_print = (char *)malloc(1000);

    //when printing global variable
    if (current_block_ptr->block_type == Block_Global_Type)
    {
        fprintf(symbol_file, "Global Variables\n");
        sprintf(to_print, "Global Variables\n");
        return to_print;
    }

    fprintf(symbol_file, "\nFunction name => ");
    sprintf(to_print, "\nFunction name => ");
    sprintf(to_print1, "\nFunction name => ");

    fprintf(symbol_file, "%s", current_func_name);
    sprintf(to_print, "%s %s", to_print,current_func_name);

    struct BLOCK *curNode = head_scope_ptr->child_block; //start from Function node
    while (curNode->child_block != NULL)
    {
        fprintf(symbol_file, " - ");
        sprintf(to_print, "%s - ", to_print);

        switch (curNode->child_block->block_type)
        {
        case Block_Do_While_Type:
            fprintf(symbol_file, "do_while");
            sprintf(to_print, "%s do_while ", to_print);

            break;

        case Block_While_Type:
            fprintf(symbol_file, "while");
            sprintf(to_print, "%s while ", to_print);

            break;

        case Block_For_Type:
            fprintf(symbol_file, "for");
            sprintf(to_print, "%s for ", to_print);

            break;

        case Block_If_Type:
            fprintf(symbol_file, "if");
            sprintf(to_print, "%s if ", to_print);

            break;

        case Block_Stmt_Group_Type:
            fprintf(symbol_file, "group_stmt");
            sprintf(to_print, "%s group_stmt ", to_print);

            break;
        }
        fprintf(symbol_file, "[%d]", getMyOrder(curNode->child_block->block_type, curNode));
        sprintf(to_print, "%s [%d] ", to_print,getMyOrder(curNode->child_block->block_type, curNode));

        curNode = curNode->child_block;
    }
    fprintf(symbol_file, "\n");
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

    fprintf(symbol_file, "%10s%10s%10s%10s%10s\n", "count", "block_type", "name", "array", "role");
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












void processProgram(struct PROGRAM* program)
{
    if(program == NULL)
        exit(1);
    head_scope_ptr = newBlock(NULL, Block_Global_Type);
    current_block_ptr = head_scope_ptr;

    fprintf(assembly_file,"%s\n\n","START main");
    if(program->declaration != NULL)
        processDeclaration(program->declaration);
    if(program->function != NULL)
        processFunction(program->function);
    checkNotAssignedIdentifiers();
}











void processDeclaration(struct DECLARATION *declaration){
    is_parameter = false;
    if (declaration->prev != NULL)
        processDeclaration(declaration->prev);

    if (!title)
    {
        printTitle();
        title = true;
    }

    switch (declaration->id_type)
    {
    case Int_Type:
        //fprintf(assembly_file, "int ");
        current_type = Int_Type;
        break;
    case Float_Type:
        //fprintf(assembly_file, "float ");
        current_type = Float_Type;
        break;

    case Const_Int_Type:
        //fprintf(assembly_file, "int ");
        current_type = Const_Int_Type;
        break;
    case Const_Float_Type:
        //fprintf(assembly_file, "float ");
        current_type = Const_Float_Type;
        break;
    default:
        fprintf(stderr, "declaration does not exist.\n");
        exit(1);
    }
    printed = true;
    processIdentifier(declaration->id);
    printed = false;

    //fprintf(assembly_file, ";\n");
    }

void processIdentifier(struct IDENTIFIER *identifier){
        if (!printed)
             return;
        


        struct Semantic* temp_semantic_identifier = newSemantic();
        temp_semantic_identifier->identifier_name = identifier->ID;

        char *cur_type;
        if (current_type == Int_Type)
        {
            cur_type = "int";
            temp_semantic_identifier->identifier_semantic_type= Int_Semantic_Type;
            temp_semantic_identifier->is_const = false;


        }
        else if(current_type == Float_Type)
        {
            cur_type = "float";
            temp_semantic_identifier->identifier_semantic_type= Float_Semantic_Type;
            temp_semantic_identifier->is_const = false;

        }
        else if(current_type == Const_Int_Type)
        {
            cur_type = "constant int";
            temp_semantic_identifier->identifier_semantic_type= Int_Semantic_Type; //to look for later because of constant
            temp_semantic_identifier->is_const = true;

        }
        else if(current_type == Const_Float_Type)
        {
            cur_type = "constant float";
            temp_semantic_identifier->identifier_semantic_type= Float_Semantic_Type;
            temp_semantic_identifier->is_const = true;
        }
        fprintf(symbol_file, "%10d%10s%10s%10s%10s\n", row_no++, cur_type, identifier->ID, "", is_parameter ? "parameter" : "variable"); //row_no(x) ++row_no(x) row_no++(o)
        if(is_parameter== true)
        {
            temp = newAssembly();
            sprintf(temp->str, identifier->ID);
            push(temp);
        }
        temp_semantic_identifier->is_assigned = false;
        temp_semantic_identifier->is_function = false;
        temp_semantic_identifier->blcok = head_scope_ptr;
        temp_semantic_identifier->is_parameter = is_parameter;
    
        int count = checkSemantic(temp_semantic_identifier->identifier_name,false,temp_semantic_identifier->blcok,NULL,temp_semantic_identifier->identifier_semantic_type);
        if(count != 0)
            fprintf(semantic_file,"ERORR: variable %s has been declared before %d times before \n",temp_semantic_identifier->identifier_name,count);
        else
        {
            printf("didn't found any variable in the smae blcok\n");
        }
        addNewSemantic(temp_semantic_identifier);
        printScopeFunctionName(temp_semantic_identifier->blcok);
        if(is_parameter == true)
        {
            //printf("\nnew%s\n",temp_semantic->identifier_name);
            addArgsToSemantic(temp_semantic,temp_semantic_identifier->identifier_semantic_type);
        }

                //printf("hello\n");




        
    
    }



void processFunction(struct FUNCTION *function){

    if (function->prev != NULL)
    {
        processFunction(function->prev);
    }
    //struct Semantic *semantic = (struct Semantic*) malloc (sizeof (struct Semantic));
    temp_semantic = newSemantic();
    current_func_name = function->ID;     //for symboltable
    printf("%s\n",current_func_name);
    //sprintf(current_func_number,function->ID);
    current_func_number = counter;
    switch (function->id_type)
        {
        case Int_Type:
            //fprintf(assembly_file, "int ");
            temp_semantic->identifier_semantic_type = Int_Semantic_Type;

            break;
        case Float_Type:
            //fprintf(assembly_file, "float ");
            temp_semantic->identifier_semantic_type = Float_Semantic_Type;

            break;
        default:
            fprintf(stderr, "Declaration does not exist.\n");
            exit(1);
        }
    temp_check = newCheck();
    temp_check->check_identifier_type = true;

   

    current_block_ptr = newBlock(current_block_ptr,Block_Func_Type); 
    temp_semantic->blcok = head_scope_ptr;
    temp_semantic->function_number = current_func_number;


    //int count = checkSemantic(function->ID,true,temp_semantic->blcok,temp_check,temp_semantic->identifier_semantic_type);
    //if(count != 0)
        //fprintf(semantic_file,"ERORR: function %s appeared %d times before \n",function->ID,count);
    
    temp_semantic->identifier_name = function->ID;
    temp_semantic->is_function = true;

    //fprintf(assembly_file, "%s (", function->ID); //add function name


    if(strcmp(function->ID,"main")!= 0)
    {
        fprintf(assembly_file, "\n\n %s%d:",function->ID,counter++);
        int jump_lable =  counter;
        fprintf(assembly_file,"\n MOV $0 , %s_RET%d",function->ID,counter++);
        temp = newAssembly();
        sprintf(temp->str, "%s_RET%d", function->ID,jump_lable);
        push(temp);
    }
    else
    {
        fprintf(assembly_file, "\n\n %s:",function->ID);

    }
    
    title = false;


    if (function->parameter != NULL && strcmp(function->ID,"main")!= 0 )
    {

        printTitle();
        title = true;
        parameter_count = 1;
        
        processParameter(function->parameter); //parameter

    }
        //addNewSemantic(temp_semantic);

    //printf("%s\n",temp_semantic->identifier_name);


        printf("hello\n");


        if(findSemanticFunction(function->ID,temp_semantic->args_stack) != NULL)
        {
            printf("hello\n");
            fprintf(semantic_file,"ERORR: function %s appeared before with the name and argument numbers and its types and order \n",function->ID);
        }
        else
        {
            printf("\n %d error\n",temp_semantic->args_stack);
            addNewSemantic(temp_semantic);
            //printf("\nnew%s\n",temp_semantic->identifier_name);

        }
        

    if(strcmp(function->ID,"main") != 0)
     fprintf(assembly_file,"\n CLRQ");

    //fprintf(assembly_file, ")\n");                //function name
    processStmtGroup(function->stmts_group); //compoundStmt

    
    fprintf(assembly_file, "\n\n");

    //deleteCurScope
    removeBlock(&current_block_ptr);
    title = false;}



void processStmt(struct STMT *stmt){
    if (stmt->prev != NULL)
        processStmt(stmt->prev);
    switch (stmt->stmt_type)
    {
    
    case Call_Type: //deprecated
        /*
        fprintf(assembly_file, "%s(", stmt->stmt.func_call->ID);
        if (stmt->stmt.func_call->arg != NULL)
        {
            struct Semantic* sem = newSemantic();
            processArg(stmt->stmt.func_call->arg,sem);
        }
        fprintf(assembly_file, ")");
        fprintf(assembly_file, ";");
        */
        break;


    case Return_Type:
        if (stmt->stmt.return_expr == NULL)
        {
            if(isEmpty()) //then it's the main return
                fprintf(assembly_file,"\n HALT");
            else
            {
                fprintf(assembly_file,"\n JMP %s",pop()->str);
            }
            
        }
        else
        {
            if(isEmpty()) //then it's the main return
                fprintf(assembly_file,"\n HALT");
            else
            {

                //fprintf(assembly_file, "return ");
                processExpr(stmt->stmt.return_expr,false);
                fprintf(assembly_file,"\n BIND %s",pop()->str);
                fprintf(assembly_file,"\n JMP %s",pop()->str);
                //fprintf(assembly_file, ";");
            }
            
         
        }
        break;

    case If_Type:
    {
        outside_group_stmt = true;
        struct IF_STMT *if_stmt  = stmt->stmt.if_stmt;
        //making node for symbol table
        current_block_ptr = newBlock(current_block_ptr, Block_If_Type);
        title = false;
        current_block_ptr->parent_block->if_count++;

        //fprintf(assembly_file, "if (");
        fprintf(assembly_file, "\n IF%d:",counter++);
        processExpr(if_stmt->condition,true);
        int jump_lable = counter;
        struct Assembly* temp_expr = pop();
        fprintf(assembly_file, "\n JIFN %s , END_IF%d",temp_expr->str,counter++);

        //fprintf(assembly_file, ")\n");
        processStmt(if_stmt->if_stmt);
        int sec_jump_lable = counter;
        fprintf(assembly_file,"\n JMP END_IF%d:",counter++);
        fprintf(assembly_file,"\n END_IF%d:",jump_lable);
        if (if_stmt->else_stmt != NULL)
        {
            //fprintf(assembly_file, "\nelse\n");
            processStmt(if_stmt->else_stmt);
        }

        fprintf(assembly_file,"\n END_IF%d:",sec_jump_lable);


        //deleteCurScope
        removeBlock(&current_block_ptr);        
        return;
    }

    case For_Type:
    {
        outside_group_stmt = true;
        struct FOR_STMT *for_stmt = stmt->stmt.for_stmt;
         //making node for symbol table
        current_block_ptr = newBlock(current_block_ptr, Block_For_Type);
        title = false;
        current_block_ptr->parent_block->for_count++;

        //fprintf(assembly_file, "for (");
        int first_jump_lable = counter;
        processAssignStmt(for_stmt->init);
        fprintf(assembly_file, "\n FOR%d:",counter++);

        //fprintf(assembly_file, "; ");
        processExpr(for_stmt->condition,true);
        int jump_lable = counter;
        struct Assembly* temp_expr = pop();
        fprintf(assembly_file, "\n JIFN %s , END_FOR%d",temp_expr->str,counter++);

        //fprintf(assembly_file, "; ");
        processAssignStmt(for_stmt->inc);
        //fprintf(assembly_file, ")\n");
        processStmt(for_stmt->stmt);
        fprintf(assembly_file, "\n JMP FOR%d",first_jump_lable);
        fprintf(assembly_file,"\n END_FOR%d:",jump_lable);

        //deleteCurScope
        removeBlock(&current_block_ptr);

        
        return;
    }
     case While_Type:
     {
        outside_group_stmt = true;
        struct WHILE_STMT *while_stmt = stmt->stmt.while_stmt;
        if (while_stmt->do_while == true)
        {
            //making node for symbol table
            current_block_ptr = newBlock(current_block_ptr, Block_Do_While_Type);
            title = false;
            current_block_ptr->parent_block->do_while_count++;

            //fprintf(assembly_file, "do");
            int jump_lable = counter;
            fprintf(assembly_file, "\n DO_WHILE%d:",counter++);

            processStmt(while_stmt->stmt);
            //fprintf(assembly_file, "while (");
            processExpr(while_stmt->condition,true);
            struct Assembly* temp_expr = pop();
            fprintf(assembly_file, "\n JIF %s , DO_WHILE%d",temp->str,jump_lable);
            fprintf(assembly_file,"\n END__DO_WHILE%d:",counter++);
            //fprintf(assembly_file, ");\n");
        }
        else
        {
            //making node for symbol table
            current_block_ptr = newBlock(current_block_ptr, Block_While_Type);
            title = false;
            current_block_ptr->parent_block->while_count++;

            /*fprintf(assembly_file, "while (");*/
            int first_jump_lable = counter;
            fprintf(assembly_file, "\n WHILE%d:",counter++);
           
            processExpr(while_stmt->condition,true);
            int jump_lable = counter;
            struct Assembly* temp_expr = pop();
            
            fprintf(assembly_file, "\n JIFN %s , END_WHILE%d",temp_expr->str,counter++);

            //fprintf(assembly_file, ")\n");
            processStmt(while_stmt->stmt);
            fprintf(assembly_file, "\n JMP WHILE%d",first_jump_lable);
            fprintf(assembly_file,"\n END_WHILE%d:",jump_lable);


        }

        //deleteCurScope
        removeBlock(&current_block_ptr);
        return;
 
     }
    case Equ_Type:
    {
        processAssignStmt(stmt->stmt.assign_stmt);
        //fprintf(assembly_file, ";");
        break;
    }
    case Stmt_Group_Type:
        if (outside_group_stmt == false)
            inside_group_stmt = true;
        processStmtGroup(stmt->stmt.stmts_group);
        return;
        //break;

    case Semi_Colon_Type:
        //fprintf(assembly_file, ";");
        break;
    }
    //fprintf(assembly_file, "\n");
    }


void processParameter(struct PARAMETER *parameter){
    is_parameter = true;

    if (parameter->prev != NULL)
    {
        processParameter(parameter->prev);

        //fprintf(assembly_file, ", ");
    }
    switch (parameter->id_type)
    {
    case Int_Type:
        //fprintf(assembly_file, "int ");
        current_type = Int_Type;
        break;
    case Float_Type:
        //fprintf(assembly_file, "float ");
        current_type = Float_Type;
        break;

    case Const_Int_Type:
        //fprintf(assembly_file, "int ");
        current_type = Const_Int_Type;
        break;
    case Const_Float_Type:
        //fprintf(assembly_file, "float ");
        current_type = Const_Float_Type;
        break;
    default:
        fprintf(stderr, "Declaration does not exist.\n");
        exit(1);
    }
    printed = true;

    processIdentifier(parameter->id);
    printed = false;

    temp = pop();
    fprintf(assembly_file,"\n MOV $%d , %s",parameter_count++,temp->str);

    }

void processStmtGroup(struct STMTSGROUP *stmts_group){
    if (inside_group_stmt == true)
    {
        //making node for symbol table
        current_block_ptr = newBlock(current_block_ptr, Block_Stmt_Group_Type);
        title = false;
        current_block_ptr->parent_block->stmt_group_count++;
    }
    outside_group_stmt = false;

    fprintf(assembly_file, "\n");
    if (stmts_group->declaration != NULL)
    {
        processDeclaration(stmts_group->declaration);
    }
    if (stmts_group->stmt != NULL)
        processStmt(stmts_group->stmt);
    fprintf(assembly_file, "\n");

    if (inside_group_stmt == true)
    {
        removeBlock(&current_block_ptr);
    }
    inside_group_stmt = false;
    outside_group_stmt = false;
}
void processAssignStmt(struct ASSIGN_STMT *assign)
{
    //fprintf(assembly_file, "%s ", assign->ID);
    /*if (assign->index != NULL)
    {
        fprintf(assembly_file, "[");
        processExpr(assign->index);
        fprintf(assembly_file, "]");
    }
    */
    //fprintf(assembly_file, " = ");
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
            if(semantic_temp->is_const == true && semantic_temp->is_assigned == true)
            {
                fprintf(semantic_file,"ERROR: Constant Identifier %s can't be initialized again\n",assign->ID);

            }
            else if(semantic_temp->is_const == true && semantic_temp->is_parameter == true)
            {
                fprintf(semantic_file,"ERROR: Constant Identifier %s can't be initialized again\n",assign->ID);

            }
            else
            {
                semantic_temp->is_assigned = true;            
            }
            
        }
    }

    fprintf(assembly_file, "\n MOV %s , %s",pop()->str,assign->ID);

}

void processArg(struct ARG *arg,struct Semantic* sem)
{
    if (arg->prev != NULL)
    {
        processArg(arg->prev,sem);
        //fprintf(assembly_file, ", ");
    }
    processExpr(arg->expr,true);
    temp = pop();
    fprintf(assembly_file,"\n BIND %s , $%d",temp->str,parameter_count++);
    printf("f-arg\n");
    temp_semantic_stack = popSemanticStack();
    //pushSemanticStack(temp_semantic_stack);
    addArgsToSemantic(sem,temp_semantic_stack->identifier_semantic_type);


}
void processExpr(struct EXPR *expr,bool must_return)
{

    switch (expr->expr_type)
    {

    case Id_Type: // some_variable = ID;
    {
        struct ID_EXPR *id_expr = expr->expression.id_expr;
        //fprintf(assembly_file, "%s", id_expr->ID);
        /*if (id_expr->expr != NULL)
        {
            fprintf(assembly_file, "[");
            processExpr(id_expr->expr);
            fprintf(assembly_file, "]");
        }
        */
        temp = newAssembly();
        printf("%s\n",id_expr->ID);
        printf("damn\n");
        sprintf(temp->str, "%s", id_expr->ID);
        push(temp);

        //check identifier is found
        temp_semantic = findSemanticIdentifier(id_expr->ID);
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
            printf("\n%s : %d\n",id_expr->ID,temp_semantic->identifier_semantic_type);
            pushSemanticStack(temp_semantic_stack);
            
        }
        break;
    }
    case IntNum_Type:

    {
        printf("%d\n",expr->expression.int_val);
        //fprintf(assembly_file, "%d", expr->expression.int_val);
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
        //fprintf(assembly_file, "%f", expr->expression.floatval);
        temp = newAssembly();
        sprintf(temp->str, "%f", expr->expression.floatval);
        push(temp);
        //add to semantic stack
        temp_semantic_stack = newSemanticStack();
        temp_semantic_stack->identifier_semantic_type = Float_Semantic_Type;
        pushSemanticStack(temp_semantic_stack);

        break;

    case Uni_Type:
    {
        //fprintf(assembly_file, "-");
        processExpr(expr->expression.uni_op->expr,true);
        struct Assembly* right = pop();
        int ret_counter = counter;
        temp = newAssembly();
        sprintf(temp->str, "UNI_RES%d", ret_counter);
        push(temp);
        fprintf(assembly_file, "\n MUL %s , %s , UNI_RES%d ",right->str,"-1",counter++);
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

            //fprintf(assembly_file, " + ");
            sprintf(temp->str, "ADD_RES%d", ret_counter);
                                        printf("dhellor%d\n",right->str);

            fprintf(assembly_file, "\n ADD %s , %s , ADD_RES%d ",left->str,right->str,counter++);
                                        printf("dhellor\n");

        }
        else
        {
            //fprintf(assembly_file, " - ");
            sprintf(temp->str, "SUB_RES%d", ret_counter);

            fprintf(assembly_file, "\n SUB %s , %s , SUB_RES%d ",left->str,right->str,counter++);
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
            //fprintf(assembly_file, " * ");
            sprintf(temp->str, "MUL_RES%d", ret_counter);
            fprintf(assembly_file, "\n MUL %s , %s , MUL_RES%d ",left->str,right->str,counter++);
        }
        else
        {
            //fprintf(assembly_file, " / ");
            sprintf(temp->str, "DIV_RES%d", ret_counter);
            fprintf(assembly_file, "\n DIV %s , %s , DIV_RES%d ",left->str,right->str,counter++);
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
            //fprintf(assembly_file, " < ");
            fprintf(assembly_file, "\n CMPL %s , %s , RES%d ",left->str,right->str,counter++);

            break;

        case Gt_Type:
           {
            fprintf(assembly_file, "\n CMPG %s , %s , RES%d ",left->str,right->str,counter++);
            break;
           }

        case Le_Type:
            //fprintf(assembly_file, " <= ");
            fprintf(assembly_file, "\n CMPLE %s , %s , RES%d ",left->str,right->str,counter++);

            break;

        case Ge_Type:
            //fprintf(assembly_file, " >= ");
            fprintf(assembly_file, "\n CMPGE %s , %s , RES%d ",left->str,right->str,counter++);

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
            struct SEMANTIC_STACK* temp_semantic_stack2 = newSemanticStack();
            temp_semantic_stack2->identifier_semantic_type = compareTypes(left_semantic->identifier_semantic_type,right_semantic->identifier_semantic_type);
            if(temp_semantic_stack2->identifier_semantic_type == Error_Semantic_Type)
            {
                fprintf(semantic_file,"Error: two different identifier one is bool and other is float/int\n");
            }
            //temp_semantic_stack->identifier_semantic_type = Bool_Semantic_Type;
            pushSemanticStack(temp_semantic_stack2);
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
            //fprintf(assembly_file, " == ");
            fprintf(assembly_file, "\n CMPE %s , %s , RES%d ",left->str,right->str,counter++);

        }
        else
        {
            //fprintf(assembly_file, " != ");
            fprintf(assembly_file, "\n CMPNE %s , %s , RES%d ",left->str,right->str,counter++);

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
        //fprintf(assembly_file,"");
        struct FUNC_CALL *call = expr->expression.func_call;
        int jump_lable = counter;
        fprintf(assembly_file,"\n BIND %s%d",call->ID,counter++);

        struct Semantic* semantic = newSemantic();

    
        if (call->arg != NULL)
        {
            parameter_count = 1;
            processArg(call->arg,semantic);
        }

        
        //check function existance
        /*struct SEMANTIC_STACK* args_stack;
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
        }*/
        
        //printf("args%d\n",args_stack);
        
        temp_semantic = findSemanticFunction(call->ID,semantic->args_stack);
        temp_semantic_stack = newSemanticStack();
        printf("%d\n",temp_semantic);
        if (temp_semantic == NULL)
        {
            printf("why\n");
            fprintf(semantic_file,"ERROR: didn't found any function matching the types or number of arguments\n");
            temp_semantic_stack->identifier_semantic_type = Error_Semantic_Type;
        }
        else
        {
            printf("found%d\n",temp_semantic->identifier_semantic_type);
            temp_semantic_stack->identifier_semantic_type = temp_semantic->identifier_semantic_type;
            fprintf(assembly_file, "\n JMP %s%d", call->ID,temp_semantic->function_number);

        }
        pushSemanticStack(temp_semantic_stack);








        fprintf(assembly_file,"\n %s%d:",call->ID,jump_lable);
        //TO DO IN ASSEMBLY CHECK if it's a return type function or not
        int sec_counter = counter;
        if (must_return == true)
        {
            temp = newAssembly();
            sprintf(temp->str, "RET_VAL%d", sec_counter);
            push(temp);
            fprintf(assembly_file, "\n MOV $1 , RET_VAL%d", counter++);
        }

        //fprintf(assembly_file, ")");
        break;
    }
    case Expr_Type:
    {
        //fprintf(assembly_file, "(");
        processExpr(expr->expression.bracket,false);
        //fprintf(assembly_file, ")");
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

//START label //START FROM SPECIFIC LABLE MENTIONED ONLY AT THE START OF THE PROGRAM
//HALT //STOP PROGRAM







