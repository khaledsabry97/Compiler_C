#include "print.h"

typedef enum { Int_Semantic_Type, Float_Semantic_Type } IDENTIFIER_SEMANTIC_TYPE; 
struct CHECKS
{
    bool check_identifier_name;
    bool check_identifier_type;
};

struct Semantic {
    struct Semantic* temp;
    struct Semantic* next;

    IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type;
    char* identifier_name;
    bool is_function;
    bool is_assigned;
    int value;
    struct SCOPE* scope;
};

struct Semantic* head;


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
                new_list = temp;
                new_list_head = new_list;
            }
            else
            {
                new_list->temp = temp;
                new_list = new_list->temp;
                new_list->temp = NULL;
            }
        }
        temp = temp->next;
    }

    
    return new_list_head;
}

bool checkScope(struct SCOPE* identifier_scope,struct SCOPE* current_scope)
{
    if(identifier_scope->scope_type == Scope_Global_Type)
        return true;
    while(current_scope->parent_scope != NULL)
    {
        current_scope = current_scope->parent_scope;
    }
    while(identifier_scope->parent_scope != NULL)
    {
        identifier_scope = identifier_scope->parent_scope;
    }
    while(identifier_scope->do_while_count == current_scope->do_while_count
    && identifier_scope->while_count == current_scope->while_count
    && identifier_scope->for_count == current_scope->for_count
    && identifier_scope->if_count == current_scope->if_count
    && identifier_scope->stmt_group_count == current_scope->stmt_group_count )
    {
        identifier_scope = identifier_scope->child_scope;
        current_scope = current_scope->child_scope;
        if(identifier_scope == NULL)
            return true;
        if(current_scope == NULL)
            return false;        
    }
    return false;
}


int checkSemantic(char* name, bool is_function,struct SCOPE* current_scope,struct CHECKS* checks,IDENTIFIER_SEMANTIC_TYPE identifier_semantic_type)
{
    struct Semantic* list_of_names = findIdentifier(name,is_function);
    int count = 0;
    

    if(is_function)
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
                
              
            
    }
    else
    {
        while(list_of_names != NULL)
        {
            bool ret = checkScope(list_of_names->scope,current_scope);
            if (ret == true)
            {
                count +=1;
            }
            list_of_names = list_of_names->temp;
        }
    }
    
   
    return count; //0 = no matching - 1 = one match - more than 1 is wrong
}


void addNewSemantic(struct Semantic* semantic)
{
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

void printSemantic()
{
     if (head == NULL)
        return;
    struct Semantic* temp = head;
    while(temp != NULL)
    {
        temp = temp->next;
    }
    return;

}


struct CHECKS* newCheck()
{
        return (struct CHECKS*) malloc (sizeof (struct CHECKS));
}

