#include <stdio.h>
#include <stdlib.h>
#include "Semantic_Handler.h"
#include <string.h>

bool header = false;
struct Assembly* assembly_head_ptr;
struct Assembly *temp;
int counter = 0;
int parameter_count = 1;
struct CHECKS* temp_check;
struct Semantic* temp_semantic;
struct SEMANTIC_STACK* temp_semantic_stack;
struct BLOCK *current_block_ptr;
bool outside_group_stmt = false;
bool inside_group_stmt = false;
char* current_func_name;
int current_func_number;
extern FILE *assembly_file;
extern FILE *symbol_file;
extern FILE *semantic_file;
struct BLOCK *temp_block;


/******Symbol Table*******/
struct BLOCK* newBlock(struct BLOCK* parent_block_ptr, BLOCK_TYPE block_type) {
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
    //node->name = current_func_name; //only important for function block
        sprintf(node->name, "%s",current_func_name);

    //sprintf(node->name,"%s",current_func_name);

    node->function_number = current_func_number;
    if(parent_block_ptr != NULL) 
        parent_block_ptr->child_block_ptr = node;
    node->parent_block_ptr = parent_block_ptr;
    node->child_block_ptr = NULL;

    //printf("curr %s\n",node->name);
    return node;
}

void removeBlock(struct BLOCK** current_block_ptr) {
    if((*current_block_ptr)->parent_block_ptr == NULL)
        return; 
    (*current_block_ptr)->parent_block_ptr->child_block_ptr = NULL;
    (*current_block_ptr) = (*current_block_ptr)->parent_block_ptr;
}
void makeNewBlockForStmts(BLOCK_TYPE block_type)
{
    outside_group_stmt = true;
    if(block_type == Block_If_Type)
    {
        current_block_ptr = newBlock(current_block_ptr, Block_If_Type);
        current_block_ptr->parent_block_ptr->if_count++;
    }
    else if(block_type == Block_For_Type)
    {
        current_block_ptr = newBlock(current_block_ptr, Block_For_Type);
        current_block_ptr->parent_block_ptr->for_count++;

    }
    else if(block_type == Block_While_Type)
    {
        current_block_ptr = newBlock(current_block_ptr, Block_While_Type);
        current_block_ptr->parent_block_ptr->while_count++;
    }
    else if(block_type == Block_Do_While_Type)
    {
        current_block_ptr = newBlock(current_block_ptr, Block_Do_While_Type);
        current_block_ptr->parent_block_ptr->do_while_count++;
    }
    else if(block_type == Block_Stmt_Group_Type)
    {
        current_block_ptr = newBlock(current_block_ptr, Block_Stmt_Group_Type);
        current_block_ptr->parent_block_ptr->stmt_group_count++;
    }

    header = false;
}

void printSymbolTableHeader()
{
    fprintf(symbol_file,"--------------------------------------------------------\n");
    fprintf(symbol_file,"--------------------------------------------------------\n");

    if (current_block_ptr->block_type == Block_Global_Type)
    {
        fprintf(symbol_file, "--------------------Global Variables--------------------");
    }
    else
    {
        fprintf(symbol_file, "------------%s", current_func_name);
        temp_block = head_block_ptr->child_block_ptr;
        while (temp_block->child_block_ptr != NULL)
        {
        
        fprintf(symbol_file, " ==> ");
        
        if(temp_block->child_block_ptr->block_type == Block_If_Type)
            fprintf(symbol_file, "if[%d]",temp_block->if_count);
        else if(temp_block->child_block_ptr->block_type == Block_For_Type)
            fprintf(symbol_file, "for[%d]", temp_block->for_count);       
        else if(temp_block->child_block_ptr->block_type == Block_While_Type)
            fprintf(symbol_file, "while[%d]", temp_block->while_count);
        else if(temp_block->child_block_ptr->block_type == Block_Do_While_Type)
            fprintf(symbol_file, "do_while[%d]",temp_block->do_while_count);
        else if(temp_block->child_block_ptr->block_type == Block_Stmt_Group_Type)
            fprintf(symbol_file, "group_stmt[%d]",temp_block->stmt_group_count);

        temp_block = temp_block->child_block_ptr;
        }
    }
    fprintf(symbol_file,"\n--------------------------------------------------------\n");
    fprintf(symbol_file, "%5s%10s%30s\n", "variable name", "type", "paremter/variable");
}

void printSymbolTableContent(char* variable_name,char* type,char* parameter)
{
    fprintf(symbol_file,"--------------------------------------------------------\n");
    fprintf(symbol_file, "%6s%18s%25s\n", variable_name, type, parameter);
}


/****Assembly***/

struct Assembly* newAssembly()
{
    return (struct Assembly*) malloc (sizeof (struct Assembly));
}

void push(struct Assembly* assem)
{
    if (assembly_head_ptr == NULL)
    {
        assembly_head_ptr = assem;
        assembly_head_ptr->prev = NULL;
    }
    else
    {
        struct Assembly* temp2;
        temp2 = assembly_head_ptr;
        assembly_head_ptr = assem;
        assembly_head_ptr->prev = temp2;
    }
    
};

struct Assembly* pop()
{
    if(assembly_head_ptr == NULL)
    {
        return NULL;
    }
    else
    {
        struct Assembly* temp2;
        temp2 = assembly_head_ptr;
        assembly_head_ptr = assembly_head_ptr->prev;
        return temp2;
    }
}

bool isEmpty()
{
    if(assembly_head_ptr == NULL)
    return true;
    return false;

}


/*****************Compilation of Program*********************/
//start of the compilation
void compileProgram(struct PROGRAM* program)
{
    if(program == NULL)
        exit(1);
    head_block_ptr = newBlock(NULL, Block_Global_Type);
    current_block_ptr = head_block_ptr;

    fprintf(assembly_file,"%s\n\n","START main");
    compileDeclaration(program->declaration);
    compileFunction(program->function);
    checkNotAssignedIdentifiers();
}


//process declarations at the start of the block
void compileDeclaration(struct DECLARATION *declaration){
    if (declaration == NULL)
        return;
    
    compileDeclaration(declaration->prev);

    if (header == false)
        printSymbolTableHeader();
    header = true;
    compileIdentifier(declaration->id,declaration->id_type,false);
}

//int x could be mentioned as a paremeter or at the begining of a block
void compileIdentifier(struct IDENTIFIER *identifier,ID_TYPE current_type,bool is_parameter){
        struct Semantic* temp_semantic_identifier = newSemantic();
        temp_semantic_identifier->identifier_name = identifier->ID;

        char *type;
        if (current_type == Int_Type)
        {
            type = "int";
            temp_semantic_identifier->identifier_semantic_type= Int_Semantic_Type;
            temp_semantic_identifier->is_const = false;


        }
        else if(current_type == Float_Type)
        {
            type = "float";
            temp_semantic_identifier->identifier_semantic_type= Float_Semantic_Type;
            temp_semantic_identifier->is_const = false;

        }
        else if(current_type == Const_Int_Type)
        {
            type = "constant int";
            temp_semantic_identifier->identifier_semantic_type= Int_Semantic_Type;
            temp_semantic_identifier->is_const = true;

        }
        else if(current_type == Const_Float_Type)
        {
            type = "constant float";
            temp_semantic_identifier->identifier_semantic_type= Float_Semantic_Type;
            temp_semantic_identifier->is_const = true;
        }
        if(is_parameter)
            printSymbolTableContent(identifier->ID,type,"parameter");
        else
            printSymbolTableContent(identifier->ID,type,"variable");
        
        if(is_parameter== true)
        {
            temp = newAssembly();
            sprintf(temp->str, identifier->ID);
            push(temp);
        }
        temp_semantic_identifier->is_assigned = false;
        temp_semantic_identifier->is_function = false;
        temp_semantic_identifier->block = head_block_ptr;
        temp_semantic_identifier->is_parameter = is_parameter;
    
        int count = checkSemantic(temp_semantic_identifier->identifier_name,false,temp_semantic_identifier->block,NULL,temp_semantic_identifier->identifier_semantic_type);
        if(count != 0)
            fprintf(semantic_file,"ERORR: variable %s has been declared before %d times before \n",temp_semantic_identifier->identifier_name,count);
        else
        {
            printf("didn't found any variable in the smae block\n");
        }
        addNewSemantic(temp_semantic_identifier);
        printScopeFunctionName(temp_semantic_identifier->block);
        if(is_parameter == true)
        {
            addArgsToSemantic(temp_semantic,temp_semantic_identifier->identifier_semantic_type);
        }
    }



void compileParameter(struct PARAMETER *parameter){
    if(parameter == NULL)
        return;
    
    compileParameter(parameter->prev);
    compileIdentifier(parameter->id,parameter->id_type,true);

    temp = pop();
    fprintf(assembly_file,"\n MOV $%d , %s",parameter_count++,temp->str);

    }


void compileFunction(struct FUNCTION *function){
    if (function == NULL)
        return;
    compileFunction(function->prev);
    
    //struct Semantic *semantic = (struct Semantic*) malloc (sizeof (struct Semantic));
    temp_semantic = newSemantic();
    current_func_name = function->ID;    
    printf("%s\n",current_func_name);
    //sprintf(current_func_number,function->ID);
    current_func_number = counter;
    if(function->id_type == Int_Type )
        temp_semantic->identifier_semantic_type = Int_Semantic_Type;
    else if(function->id_type == Float_Type )
        temp_semantic->identifier_semantic_type = Float_Semantic_Type;
    else
    {
            fprintf(stderr, "Error in function type \n");
            exit(1);
    }
    
    temp_check = newCheck();
    temp_check->check_identifier_type = true;

   

    current_block_ptr = newBlock(current_block_ptr,Block_Func_Type); 
    temp_semantic->block = head_block_ptr;
    temp_semantic->function_number = current_func_number;


    //int count = checkSemantic(function->ID,true,temp_semantic->block,temp_check,temp_semantic->identifier_semantic_type);
    //if(count != 0)
        //fprintf(semantic_file,"ERORR: function %s appeared %d times before \n",function->ID,count);
    
    temp_semantic->identifier_name = function->ID;
    temp_semantic->is_function = true;



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
    
    header = false;
    if (function->parameter != NULL && strcmp(function->ID,"main")!= 0 )
    {

        printSymbolTableHeader();
        header = true;
        parameter_count = 1;
        
        compileParameter(function->parameter);

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

    compileStmtGroup(function->stmts_group);
    header = false;
    
    fprintf(assembly_file, "\n\n");

    removeBlock(&current_block_ptr);
  
    }

void compileArgs(struct ARG *arg,struct Semantic* sem)
{
    if (arg == NULL)
        return;

    compileArgs(arg->prev,sem);
    compileExpr(arg->expr,true);

    temp = pop();
    fprintf(assembly_file,"\n BIND %s , $%d",temp->str,parameter_count++);
    printf("f-arg\n");
    temp_semantic_stack = popSemanticStack();
    //pushSemanticStack(temp_semantic_stack);
    addArgsToSemantic(sem,temp_semantic_stack->identifier_semantic_type);
}


/*****************Compilation of statements*********************/
void compileStmt(struct STMT *stmt){
    if(stmt == NULL)
        return;
    compileStmt(stmt->prev);
    STMT_TYPE stmt_type = stmt->stmt_type;

    if(stmt_type == Return_Type )
    {
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

                compileExpr(stmt->stmt.return_expr,false);
                fprintf(assembly_file,"\n BIND %s",pop()->str);
                fprintf(assembly_file,"\n JMP %s",pop()->str);
            } 
        }
    }
    else if(stmt_type == If_Type )
    {
        struct IF_STMT *if_stmt  = stmt->stmt.if_stmt;
        makeNewBlockForStmts(Block_If_Type);

        fprintf(assembly_file, "\n IF%d:",counter++);
        compileExpr(if_stmt->condition,true);
        int jump_lable = counter;
        struct Assembly* temp_expr = pop();
        fprintf(assembly_file, "\n JIFN %s , END_IF%d",temp_expr->str,counter++);

        compileStmt(if_stmt->if_stmt);
        int sec_jump_lable = counter;
        fprintf(assembly_file,"\n JMP END_IF%d:",counter++);
        fprintf(assembly_file,"\n END_IF%d:",jump_lable);
        removeBlock(&current_block_ptr);        
        compileStmt(if_stmt->else_stmt);

        fprintf(assembly_file,"\n END_IF%d:",sec_jump_lable);
    }
    else if(stmt_type == For_Type)
    {
        struct FOR_STMT *for_stmt = stmt->stmt.for_stmt;
        makeNewBlockForStmts(Block_For_Type);
        int first_jump_lable = counter;
        compileAssignStmt(for_stmt->init);
        fprintf(assembly_file, "\n FOR%d:",counter++);

        compileExpr(for_stmt->condition,true);
        int jump_lable = counter;
        struct Assembly* temp_expr = pop();
        fprintf(assembly_file, "\n JIFN %s , END_FOR%d",temp_expr->str,counter++);

        compileAssignStmt(for_stmt->inc);
        compileStmt(for_stmt->stmt);
        fprintf(assembly_file, "\n JMP FOR%d",first_jump_lable);
        fprintf(assembly_file,"\n END_FOR%d:",jump_lable);
        removeBlock(&current_block_ptr);
    }
    else if(stmt_type == While_Type)
    {
        struct WHILE_STMT *while_stmt = stmt->stmt.while_stmt;
        if (while_stmt->do_while == true)
        {
           makeNewBlockForStmts(Block_Do_While_Type);

            int jump_lable = counter;
            fprintf(assembly_file, "\n DO_WHILE%d:",counter++);
            compileStmt(while_stmt->stmt);
            compileExpr(while_stmt->condition,true);

            struct Assembly* temp_expr = pop();
            fprintf(assembly_file, "\n JIF %s , DO_WHILE%d",temp->str,jump_lable);
            fprintf(assembly_file,"\n END__DO_WHILE%d:",counter++);
            removeBlock(&current_block_ptr);

        }
        else
        {
            makeNewBlockForStmts(Block_While_Type);

            int first_jump_lable = counter;
            fprintf(assembly_file, "\n WHILE%d:",counter++);
           
            compileExpr(while_stmt->condition,true);
            int jump_lable = counter;
            struct Assembly* temp_expr = pop();
            
            fprintf(assembly_file, "\n JIFN %s , END_WHILE%d",temp_expr->str,counter++);

            compileStmt(while_stmt->stmt);
            fprintf(assembly_file, "\n JMP WHILE%d",first_jump_lable);
            fprintf(assembly_file,"\n END_WHILE%d:",jump_lable);
            removeBlock(&current_block_ptr);
        }
    }
    else if(stmt_type == Equ_Type )
    {
        compileAssignStmt(stmt->stmt.assign_stmt);
    }
    else if(stmt_type == Stmt_Group_Type)
    {
        if (outside_group_stmt == false)
            inside_group_stmt = true;
        compileStmtGroup(stmt->stmt.stmts_group);
    }
    }

void compileStmtGroup(struct STMTSGROUP *stmts_group){
    if (inside_group_stmt == true)
        makeNewBlockForStmts(Block_Stmt_Group_Type);
    outside_group_stmt = false;

    fprintf(assembly_file, "\n");

    compileDeclaration(stmts_group->declaration);
    compileStmt(stmts_group->stmt);
    outside_group_stmt = false;
    fprintf(assembly_file, "\n");

    if (inside_group_stmt == true)
        removeBlock(&current_block_ptr);
    inside_group_stmt = false;


}
void compileAssignStmt(struct ASSIGN_STMT *assign)
{
    compileExpr(assign->expr,true);
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


/*****************Compilation of Expressions*********************/
void compileExpr(struct EXPR *expr,bool must_return)
{
    EXPR_TYPE expr_type = expr->expr_type;
    if(expr_type == Id_Type )
    {
        
        struct ID_EXPR *id_expr = expr->expression.id_expr;
        
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
    }
    else if(expr_type == IntNum_Type)
    {
        temp = newAssembly();
        sprintf(temp->str, "%d", expr->expression.int_val);
        push(temp);
        //add to semantic stack
        printf("j");
        temp_semantic_stack = newSemanticStack();
        temp_semantic_stack->identifier_semantic_type = Int_Semantic_Type;
        pushSemanticStack(temp_semantic_stack);
    }
    else if(expr_type == FloatNum_Type)
    {
        temp = newAssembly();
        sprintf(temp->str, "%f", expr->expression.floatval);
        push(temp);
        //add to semantic stack
        temp_semantic_stack = newSemanticStack();
        temp_semantic_stack->identifier_semantic_type = Float_Semantic_Type;
        pushSemanticStack(temp_semantic_stack);
    }
    else if(expr_type == Uni_Type)
    {
        compileExpr(expr->expression.uni_op->expr,true);
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
    }
    else if(expr_type == Add_Type)
    {
        compileExpr(expr->expression.add_op->left_side,true);
        compileExpr(expr->expression.add_op->right_side,true);

        struct Assembly* right = pop();
        struct Assembly* left = pop();
        int ret_counter = counter;
        temp = newAssembly();
        if (expr->expression.add_op->add_type == Plus_Type)
        {

            sprintf(temp->str, "ADD_RES%d", ret_counter);
            printf("dhellor%d\n",right->str);

            fprintf(assembly_file, "\n ADD %s , %s , ADD_RES%d ",left->str,right->str,counter++);
            printf("dhellor\n");

        }
        else
        {
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
    }
    else if(expr_type == Mult_Type )
    {
        compileExpr(expr->expression.mul_op->left_side,true);
        compileExpr(expr->expression.mul_op->right_side,true);
        struct Assembly* right = pop();
        struct Assembly* left = pop();
        int ret_counter = counter;
        temp = newAssembly();
        if (expr->expression.mul_op->mul_type == Mul_Type)
        {
            sprintf(temp->str, "MUL_RES%d", ret_counter);
            fprintf(assembly_file, "\n MUL %s , %s , MUL_RES%d ",left->str,right->str,counter++);
        }
        else
        {
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
    }
    else if(expr_type == Com_Type )
    {
        compileExpr(expr->expression.com_op->left_side,true);
        compileExpr(expr->expression.com_op->right_side,true);

        struct Assembly* right = pop();
        struct Assembly* left = pop();
        int ret_counter = counter;
        temp = newAssembly();
        sprintf(temp->str, "RES%d", ret_counter);
        push(temp);
        COMP_TYPE com_type = expr->expression.com_op->com_type;
        if(com_type == Lt_Type)
            fprintf(assembly_file, "\n CMPL %s , %s , RES%d ",left->str,right->str,counter++);
        else if(com_type == Gt_Type)
            fprintf(assembly_file, "\n CMPG %s , %s , RES%d ",left->str,right->str,counter++);
        else if(com_type == Le_Type)
            fprintf(assembly_file, "\n CMPLE %s , %s , RES%d ",left->str,right->str,counter++);
        else if(com_type == Ge_Type)
            fprintf(assembly_file, "\n CMPGE %s , %s , RES%d ",left->str,right->str,counter++);

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
        
    }
    else if(expr_type == Eql_Type )
    {
        compileExpr(expr->expression.eql_op->left_side,true);
        compileExpr(expr->expression.eql_op->right_side,true);
        struct Assembly* right = pop();
        struct Assembly* left = pop();
        int ret_counter = counter;
        temp = newAssembly();
        sprintf(temp->str, "RES%d", ret_counter);
        push(temp);

        if (expr->expression.eql_op->eql_type == Eq_Type)
        {
            fprintf(assembly_file, "\n CMPE %s , %s , RES%d ",left->str,right->str,counter++);

        }
        else
        {
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
        
    }
    else if(expr_type == CallExpr_Type)
    {
        struct FUNC_CALL *call = expr->expression.func_call;
        int jump_lable = counter;
        fprintf(assembly_file,"\n BIND %s%d",call->ID,counter++);

        struct Semantic* semantic = newSemantic();

    
        if (call->arg != NULL)
            parameter_count = 1;
        compileArgs(call->arg,semantic);


        
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
        int sec_counter = counter;
        if (must_return == true)
        {
            temp = newAssembly();
            sprintf(temp->str, "RET_VAL%d", sec_counter);
            push(temp);
            fprintf(assembly_file, "\n MOV $1 , RET_VAL%d", counter++);
        }
    }
    else if(expr_type == Expr_Type)
    {
        compileExpr(expr->expression.bracket,false);
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







