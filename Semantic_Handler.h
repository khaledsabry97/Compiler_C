#include "print.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { Int_Semantic_Type, Float_Semantic_Type,Bool_Semantic_Type,Error_Semantic_Type } IDENTIFIER_SEMANTIC_TYPE; 
struct CHECKS
{
    bool check_identifier_name;
    bool check_identifier_type;
};

struct SEMANTIC_STACK {
    IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type;
    struct SEMANTIC_STACK* prev;

};

struct Semantic {
    struct Semantic* temp;
    struct Semantic* next;

    struct SEMANTIC_STACK* args_stack;
    IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type;
    char* identifier_name;
    bool is_function;
    bool is_assigned;
    bool is_parameter;
    int function_number;
    int value;
    struct SCOPE* scope;
};



struct Semantic* head;



struct SCOPE* newScopeToSemantic(struct SCOPE* current_scope,struct SCOPE* parent_scope) {
    if (current_scope == NULL)
        return NULL;
    struct SCOPE* node = (struct SCOPE*) malloc (sizeof(struct SCOPE));
    node->scope_type = current_scope->scope_type;
    node->do_while_count = current_scope->do_while_count;
    node->while_count = current_scope->while_count;
    node->for_count  = current_scope->for_count;
    node->if_count = current_scope->if_count;
    node->stmt_group_count = current_scope->stmt_group_count;
    //node->name = current_scope->name; //only important for function scope
    if(current_scope->scope_type == Scope_Global_Type)
        sprintf(node->name, "Global Variables");
    else
    sprintf(node->name, "%s",current_scope->name);
    //node->name_ = malloc(sizeof(char) * (strlen(current_scope->name)+1));
    //sprintf(node->name_, "%s",current_scope->name);
    //node->name_ = "hello";
    //sprintf(node->name, "bad");
    node->function_number = current_scope->function_number;
    node->parent_scope = parent_scope;
    //node->name = (char*)malloc(strlen(current_scope->name) + 1); 
    //strcpy(node->name, current_scope->name);
    //printf("current_scope %s\n",node->name);
    node->child_scope = newScopeToSemantic(current_scope->child_scope,node);
    return node;
}


//return a list of same identifier name
struct Semantic* findIdentifier(char* name,bool is_function)
{
    struct Semantic* temp = head;
    if (temp == NULL)
    {
        return NULL;
    }
    struct Semantic* new_list= NULL;
    struct Semantic* new_list_head= NULL;

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


bool checkScope(struct SCOPE* identifier_scope,struct SCOPE* current_scope)
{
    
    if(identifier_scope->child_scope == NULL)
    {
        //printf("global_scope");
        return true;
    }



    /*struct SCOPE* temp;

    while(current_scope->parent_scope != NULL)
    {
        printf("1%s",current_scope->name);
        temp = current_scope;
        current_scope = current_scope->parent_scope;  
        if (current_scope == NULL)
        {
            current_scope = temp;
            break; 
        }     
    }
    while(temp->parent_scope != NULL)
    {
        printf("%s",temp->name);
        temp = temp->parent_scope;

    }*/
    

    /*while(identifier_scope->do_while_count == current_scope->do_while_count
    && identifier_scope->while_count == current_scope->while_count
    && identifier_scope->for_count == current_scope->for_count
    && identifier_scope->if_count == current_scope->if_count
    && identifier_scope->stmt_group_count == current_scope->stmt_group_count
    && identifier_scope->name == current_scope->name )
    {
        printf("hello");
        identifier_scope = identifier_scope->child_scope;
        current_scope = current_scope->child_scope;
        printf("%s",identifier_scope->name);
        if(identifier_scope == NULL)
            return true;
        if(current_scope == NULL)
            return false;        
    }*/

    printScopeFunctionName(identifier_scope->child_scope);
    while(1 == 1)
    {
        //printf("%s",identifier_scope->function_number);
        identifier_scope = identifier_scope->child_scope;
        current_scope = current_scope->child_scope;
        if(identifier_scope == NULL)
        {
            //printf("same scope\n");
            return true;

        }
        if(current_scope == NULL)
            return false;      


        if(identifier_scope->parent_scope->do_while_count != current_scope->parent_scope->do_while_count)
            return false;
        if(identifier_scope->parent_scope->for_count != current_scope->parent_scope->for_count)
            return false;
        if(identifier_scope->parent_scope->while_count != current_scope->parent_scope->while_count)
            return false;
        if(identifier_scope->parent_scope->if_count != current_scope->parent_scope->if_count)
            return false;
        if(identifier_scope->parent_scope->stmt_group_count != current_scope->parent_scope->stmt_group_count)
            return false;
        if(strcmp(identifier_scope->name,current_scope->name) != 0)
            return false;
        //printf("%s - %s\n",identifier_scope->name,current_scope->name);
        if(strcmp(identifier_scope->name,current_scope->name) == 0 && identifier_scope->function_number != current_scope->function_number)
            return false;
        

        
        //printf("%s\n",identifier_scope->name);
  
    }

    
    //printf("sdfsdfsd%s",current_scope->name);

    /*while(identifier_scope->do_while_count - current_scope->do_while_count == 0 )
    {
        identifier_scope = identifier_scope->child_scope;
        current_scope = current_scope->child_scope;
        printf("%s",identifier_scope->name);
        if(identifier_scope == NULL)
            return true;
        if(current_scope == NULL)
            return false;        
    }*/
   
    
    //printf("two");

    return false;
}



/*
bool checkScope(char* identifier_scope,char* current_scope)
{
    int i = 1;

    int size_of_identifier = strlen(identifier_scope);
    if(size_of_identifier > strlen(current_scope))
    return false;
    while(i <= size_of_identifier)
    {
        if(strncmp(identifier_scope, current_scope,i) != 0)
        return false;
        i+=1;
    }
    return true;
}
*/

int checkSemantic(char* name, bool is_function,struct SCOPE* current_scope,struct CHECKS* checks,IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type)
{
    //printf("%s\n",current_scope);
            //printf("before\n");

    struct Semantic* list_of_names = findIdentifier(name,is_function);
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
            bool ret = checkScope(list_of_names->scope,current_scope);
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
    return (struct SEMANTIC_STACK*) malloc (sizeof (struct SEMANTIC_STACK));
}


void addNewSemantic(struct Semantic* semantic)
{
    semantic->next = NULL;
    semantic->temp = NULL;
    semantic->scope = newScopeToSemantic(semantic->scope,NULL);

    if(semantic->args_stack == NULL)
    {
        semantic->args_stack = NULL;
    }
    if (head == NULL)
    {
        head = semantic;
        return;
    }
    struct Semantic* temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = semantic;

    return;

}

void addArgsToSemantic(struct Semantic* semantic, IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type)
{
    if (semantic->args_stack == NULL)
    {
        semantic->args_stack = newSemanticStack();
        semantic->args_stack->identifier_semantic_type = identifier_semantic_type;
        semantic->args_stack->prev = NULL;

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
    temp->prev->prev = NULL;


}

void printScopeFunctionName(struct SCOPE* scope)
{    
    while(scope != NULL)
    {
        printf("%s -> ",scope->name);
        scope = scope->child_scope;
    }
    printf("\n");


    return;

}


struct CHECKS* newCheck()
{
        return (struct CHECKS*) malloc (sizeof (struct CHECKS));
}

struct Semantic* newSemantic()
{
        return (struct Semantic*) malloc (sizeof (struct Semantic));
}


struct Semantic* findSemanticIdentifier(char* identifier_name)
{
    struct Semantic* list_of_names = findIdentifier(identifier_name,false);
    while(list_of_names != NULL)
    {
        //printf("%s\n",list_of_names->identifier_name);
        bool ret = checkScope(list_of_names->scope,scopeHead);
        if (ret == true)
        {
            list_of_names->temp = NULL;
            return list_of_names;
        }

        list_of_names = list_of_names->temp;
    }    
    return NULL;
}

struct Semantic* findSemanticFunction(char* identifier_name,struct SEMANTIC_STACK* semantic_stack)
{
    struct Semantic* list_of_names = findIdentifier(identifier_name,true);
    struct SEMANTIC_STACK* temp = semantic_stack;
    struct SEMANTIC_STACK* temp2;

    while(list_of_names != NULL)
    {
        //printf("%s %d errrorror\n",list_of_names->identifier_name,list_of_names->args_stack);
        /*if(check_function_type == true)
        {
            if(list_of_names->identifier_semantic_type != semantic->identifier_semantic_type )
            {
                list_of_names = list_of_names->temp;
                continue;
            }
            



        }*/
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

// you can't have two names of same type in function
// you can have more than one function with same name but different return types
// you can have one variable with same name if declared as global variable
// never mix between different scopes
// you can identify funcation with the same name of a variable no problem
// tell you how many times the variable declared
// tell if an identifier not declared before wether if it's on the rhs or lhs
// error: if rhs identifier is not assigned value before it's used
// error: if rhs is different type from lhs
// error: if compare between integer and bool or between float and bool
// error: if not found a function name matching the calling function
// float [+/*-] integer => float
// float/integer [><==] float/integer => bool
// error: if you send an arguments and not matched with the number of another function with same name 
// error: if you send an arguments with different types
// error: if return type of function doesn't match with the identifier
