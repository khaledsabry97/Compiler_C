#include <stdlib.h>
#include "symboltable.h"
//make node
struct scope* newScope(SCOPE_TYPE scope_type, struct scope* parent) {
    struct scope* node = (struct scope*) malloc (sizeof(struct scope));
    node->scope_type = scope_type;
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
int getMyOrder(SCOPE_TYPE scope_type, struct scope* parent) {
    switch(scope_type) {
        case Scope_Do_While_Type:
            return (parent->dowhile_n);

        case Scope_While_Type:
            return (parent->while_n);

        case Scope_For_Type:
            return (parent->for_n);

        case Scope_If_Type:
            return (parent->if_n);

        case Scope_Stmt_Group_Type:
            return (parent->compound_n);
    }
}

