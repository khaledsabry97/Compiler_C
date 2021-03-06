#include "Compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include "Enums.h"

struct CHECKS
{
    bool check_identifier_name;
    bool check_identifier_type;
};

struct SEMANTIC_STACK {
    IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type;
    struct SEMANTIC_STACK* prev;

};

struct SEMANTIC {
    struct SEMANTIC* temp;
    struct SEMANTIC* next;

    struct SEMANTIC_STACK* args_stack;
    IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type;
    char* identifier_name;
    bool is_function;
    bool is_assigned;
    bool is_const;
    bool is_parameter;
    int function_number;
    int value;
    struct BLOCK* block;
};



struct SEMANTIC* head;



struct BLOCK* newBlockToSemantic(struct BLOCK* current_block,struct BLOCK* parent_block_ptr) {
    if (current_block == NULL)
        return NULL;
    struct BLOCK* node = (struct BLOCK*) malloc (sizeof(struct BLOCK));
    node->block_type = current_block->block_type;
    node->do_while_count = current_block->do_while_count;
    node->while_count = current_block->while_count;
    node->for_count  = current_block->for_count;
    node->if_count = current_block->if_count;
    node->stmt_group_count = current_block->stmt_group_count;
    //node->name = current_block->name; //only important for function block
    if(current_block->block_type == Block_Global_Type)
        sprintf(node->name, "Global Variables");
    else
    sprintf(node->name, "%s",current_block->name);
    //node->name_ = malloc(sizeof(char) * (strlen(current_block->name)+1));
    //sprintf(node->name_, "%s",current_block->name);
    //node->name_ = "hello";
    //sprintf(node->name, "bad");
    node->function_number = current_block->function_number;
    node->parent_block_ptr = parent_block_ptr;
    //node->name = (char*)malloc(strlen(current_block->name) + 1); 
    //strcpy(node->name, current_block->name);
    //printf("current_block %s\n",node->name);
    node->child_block_ptr = newBlockToSemantic(current_block->child_block_ptr,node);
    return node;
}


//return a list of same identifier name
struct SEMANTIC* findIdentifier(char* name,bool is_function)
{
    struct SEMANTIC* temp = head;
    if (temp == NULL)
    {
        return NULL;
    }
    struct SEMANTIC* new_list= NULL;
    struct SEMANTIC* new_list_head= NULL;

    while(temp != NULL)
    {
        //printf("Comparison : %s - %s - %d \n",temp->identifier_name, name,strcmp(temp->identifier_name,name));
        if(strcmp(temp->identifier_name,name) == 0 && temp->is_function == is_function ) // comapre between two names and if function
        {

            if (new_list == NULL)
            {
                //printf("newlist\n");
                new_list = temp;
                new_list_head = new_list;
            }
            else
            {
                //printf("oldlist\n");
                new_list->temp = temp;
                new_list = new_list->temp;
                //printf("oldlist\n");
            }
            temp = temp->next;
        }
        else
            temp = temp->next;
    }
    //printf("out\n");
    if(new_list != NULL)
        new_list->temp = NULL;


    return new_list_head;
}


bool checkBlock(struct BLOCK* identifier_block,struct BLOCK* current_block)
{
    
    if(identifier_block->child_block_ptr == NULL)
    {
        //printf("global_block");
        return true;
    }



    /*struct BLOCK* temp;

    while(current_block->parent_block_ptr != NULL)
    {
        printf("1%s",current_block->name);
        temp = current_block;
        current_block = current_block->parent_block_ptr;  
        if (current_block == NULL)
        {
            current_block = temp;
            break; 
        }     
    }
    while(temp->parent_block_ptr != NULL)
    {
        printf("%s",temp->name);
        temp = temp->parent_block_ptr;

    }*/
    

    /*while(identifier_block->do_while_count == current_block->do_while_count
    && identifier_block->while_count == current_block->while_count
    && identifier_block->for_count == current_block->for_count
    && identifier_block->if_count == current_block->if_count
    && identifier_block->stmt_group_count == current_block->stmt_group_count
    && identifier_block->name == current_block->name )
    {
        printf("hello");
        identifier_block = identifier_block->child_block_ptr;
        current_block = current_block->child_block_ptr;
        printf("%s",identifier_block->name);
        if(identifier_block == NULL)
            return true;
        if(current_block == NULL)
            return false;        
    }*/

    printBlockFunctionName(identifier_block->child_block_ptr);
    while(1 == 1)
    {
        //printf("%s",identifier_block->function_number);
        identifier_block = identifier_block->child_block_ptr;
        current_block = current_block->child_block_ptr;
        if(identifier_block == NULL)
        {
            //printf("same block\n");
            return true;

        }
        if(current_block == NULL)
            return false;      


        if(identifier_block->parent_block_ptr->do_while_count != current_block->parent_block_ptr->do_while_count)
            return false;
        if(identifier_block->parent_block_ptr->for_count != current_block->parent_block_ptr->for_count)
            return false;
        if(identifier_block->parent_block_ptr->while_count != current_block->parent_block_ptr->while_count)
            return false;
        if(identifier_block->parent_block_ptr->if_count != current_block->parent_block_ptr->if_count)
            return false;
        if(identifier_block->parent_block_ptr->stmt_group_count != current_block->parent_block_ptr->stmt_group_count)
            return false;
        if(strcmp(identifier_block->name,current_block->name) != 0)
            return false;
        //printf("%s - %s\n",identifier_block->name,current_block->name);
        if(strcmp(identifier_block->name,current_block->name) == 0 && identifier_block->function_number != current_block->function_number)
            return false;
        

        
        //printf("%s\n",identifier_block->name);
  
    }

    
    //printf("sdfsdfsd%s",current_block->name);

    /*while(identifier_block->do_while_count - current_block->do_while_count == 0 )
    {
        identifier_block = identifier_block->child_block_ptr;
        current_block = current_block->child_block_ptr;
        printf("%s",identifier_block->name);
        if(identifier_block == NULL)
            return true;
        if(current_block == NULL)
            return false;        
    }*/
   
    
    //printf("two");

    return false;
}



/*
bool checkBlock(char* identifier_block,char* current_block)
{
    int i = 1;

    int size_of_identifier = strlen(identifier_block);
    if(size_of_identifier > strlen(current_block))
    return false;
    while(i <= size_of_identifier)
    {
        if(strncmp(identifier_block, current_block,i) != 0)
        return false;
        i+=1;
    }
    return true;
}
*/

int checkSemantic(char* name, bool is_function,struct BLOCK* current_block,struct CHECKS* checks,IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type)
{
    //printf("%s\n",current_block);
            //printf("before\n");

    struct SEMANTIC* list_of_names = findIdentifier(name,is_function);
    int count = 0;
    if(is_function == true)
    {

          while(list_of_names != NULL)
            {

                if(checks->check_identifier_type)
                {
                    if(list_of_names->identifier_semantic_type == identifier_semantic_type)
                    {
                        count +=1;
                    }

                }
                else
                {
                    count +=1;
                }
               
                list_of_names = list_of_names->temp;
            }

                
        return count; //0 = no matching - 1 = one match - more than 1 is wrong


    }

        while(list_of_names != NULL)
        {
            printf("%s\n",list_of_names->identifier_name);
            bool ret = checkBlock(list_of_names->block,current_block);
            if (ret == true)
            {
                printf("sdfsdfsdf\n");
                count +=1;
            }

            list_of_names = list_of_names->temp;
        }    
   
    return count; //0 = no matching - 1 = one match - more than 1 is wrong
}


struct SEMANTIC_STACK* semantic_stack_head;

struct SEMANTIC_STACK* newSemanticStack()
{
    struct SEMANTIC_STACK* semantics =  (struct SEMANTIC_STACK*) malloc (sizeof (struct SEMANTIC_STACK));
    semantics->prev = NULL;
    return semantics;
}


void addNewSemantic(struct SEMANTIC* semantic)
{
    semantic->block = newBlockToSemantic(semantic->block,NULL);

    if (head == NULL)
    {
        head = semantic;
        return;
    }
    struct SEMANTIC* temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = semantic;

    return;

}

void addArgsToSemantic(struct SEMANTIC* semantic, IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type)
{
            printf("%dhello\n",semantic->args_stack);

    if (semantic->args_stack == NULL)
    {
                printf("hello\n");

        semantic->args_stack = newSemanticStack();
        semantic->args_stack->identifier_semantic_type = identifier_semantic_type;
        printf("stack: %d\n",semantic->args_stack->prev);

        return;
    }
    struct SEMANTIC_STACK* temp = semantic->args_stack;
    while(temp->prev != NULL) //deal with prev as if it's next in this case
    {
        //printf("%dthere\n",temp->identifier_semantic_type);
        temp = temp->prev;
    }
    temp->prev = newSemanticStack();
    temp->prev->identifier_semantic_type = identifier_semantic_type;
    printf("stacks: %d\n",temp->prev->prev);



}


void printNumberOfArgs(struct SEMANTIC_STACK* args)
{
    while(args != NULL)
    {
        printf("argtype: %d -> ",args->identifier_semantic_type);
        args = args->prev;
    }
    printf("\n");
}

void printBlockFunctionName(struct BLOCK* block)
{    
    while(block != NULL)
    {
        printf("%s -> ",block->name);
        block = block->child_block_ptr;
    }
    printf("\n");

    return;

}


struct CHECKS* newCheck()
{
        return (struct CHECKS*) malloc (sizeof (struct CHECKS));
}

struct SEMANTIC* newSemantic()
{
    struct SEMANTIC* semantics = (struct SEMANTIC*) malloc (sizeof (struct SEMANTIC));
    semantics->args_stack = NULL;
    semantics->next = NULL;
    semantics->temp = NULL;
    return semantics;
}


struct SEMANTIC* findSemanticIdentifier(char* identifier_name)
{
    struct SEMANTIC* list_of_names = findIdentifier(identifier_name,false);
    while(list_of_names != NULL)
    {
        //printf("%s\n",list_of_names->identifier_name);
        bool ret = checkBlock(list_of_names->block,head_block_ptr);
        if (ret == true)
        {
            list_of_names->temp = NULL;
            return list_of_names;
        }

        list_of_names = list_of_names->temp;
    }    
    return NULL;
}

struct SEMANTIC* findSemanticFunction(char* identifier_name,struct SEMANTIC_STACK* semantic_stack)
{
    struct SEMANTIC* list_of_names = findIdentifier(identifier_name,true);
    struct SEMANTIC_STACK* temp = semantic_stack;
    struct SEMANTIC_STACK* temp2;

    while(list_of_names != NULL)
    {

        printNumberOfArgs(list_of_names->args_stack);
        printNumberOfArgs(temp);
        temp2 = list_of_names->args_stack;
        while (true)
        {
            printf("c\n");
            if(temp2 == NULL || temp == NULL)
            {
                printf("%d-%d\n",temp,temp2);
                break;
            }
            if(temp2->identifier_semantic_type != temp->identifier_semantic_type)
            {
                printf("%d - %d\n",temp2->identifier_semantic_type ,temp->identifier_semantic_type );
                break;
            }
            temp2 = temp2->prev; //deal with prev as next
            temp = temp->prev;
        }

        if(temp2 == NULL && temp == NULL)
        {
            return list_of_names;
        }
        temp = semantic_stack;
        list_of_names = list_of_names->temp;
    }
    return NULL;
}





void pushSemanticStack(struct SEMANTIC_STACK* semantic_stack)
{
    if (semantic_stack_head == NULL)
    {
        //printf("good");
        semantic_stack_head = semantic_stack;
        semantic_stack_head->prev = NULL;
    }
    else
    {
        struct SEMANTIC_STACK* temp2;
        temp2 = semantic_stack_head;
        semantic_stack_head = semantic_stack;
        semantic_stack_head->prev = temp2;
    }
    
};

struct SEMANTIC_STACK* popSemanticStack()
{
    if(semantic_stack_head == NULL)
    {
        //printf("bad");
        return NULL;
    }
    else
    {
        struct SEMANTIC_STACK* temp2;
        temp2 = semantic_stack_head;
        semantic_stack_head = semantic_stack_head->prev;
        return temp2;
    }
}

bool isEmptySemanticStack()
{
    if(semantic_stack_head == NULL)
        return true;
    return false;
}

IDENTIFIER_SEMANTIC_TYPE compareTypes(IDENTIFIER_SEMANTIC_TYPE type1, IDENTIFIER_SEMANTIC_TYPE type2)
{
    if(type1 == Float_Semantic_Type)
    {
        if(type2 == Bool_Semantic_Type)
            return Error_Semantic_Type;
        return Float_Semantic_Type;
    }

    if(type2 == Float_Semantic_Type)
    {
        if(type1 == Bool_Semantic_Type)
            return Error_Semantic_Type;
        return Float_Semantic_Type;
    }

    if(type1 == Int_Semantic_Type)
    {
        if(type2 == Bool_Semantic_Type)
            return Error_Semantic_Type;
        return Int_Semantic_Type;
    }

    if(type2 == Int_Semantic_Type)
    {
        if(type1 == Bool_Semantic_Type)
            return Error_Semantic_Type;
        return Int_Semantic_Type;
    }

    if(type1 == Bool_Semantic_Type)
    {
        if(type2 != Bool_Semantic_Type)
            return Error_Semantic_Type;
        return Bool_Semantic_Type;
    }

    
    if(type2 == Bool_Semantic_Type)
    {
        if(type1 != Bool_Semantic_Type)
            return Error_Semantic_Type;
        return Bool_Semantic_Type;
    }

    return Error_Semantic_Type;


}
extern FILE *semantic_file;


void checkNotAssignedIdentifiers()
{
    struct SEMANTIC* temp = head;
    while(temp!=NULL)
    {
        if (temp->is_assigned == false && temp->is_function == false && temp->is_parameter == false)
        {
            fprintf(semantic_file,"WARNING: Identified a variable %s but not assigend a value to it\n",temp->identifier_name);
        }
        head = temp;
        temp = temp->next;
        free(head);
    }
}



//if not found a function name matching the calling function - (no function found)
// if Identified a variable  but not assigend a value later
// if send  arguments with different types - (no function found)
// if return type of function doesn't match with the identifier - (no function found)
// if send arguments with different number of arguments - (no function found)
// can't reassign a constant variable
// can't reassign a constant parameter
// if compare between bool and int/float
// if rhs is different type from lhs
//if rhs identifier is not assigned value before it's used
// If identifier not declared before wether if it's on the rhs or lhs
// tell you how many times the variable declared before in same block
// If you have two names of the same type in the same block