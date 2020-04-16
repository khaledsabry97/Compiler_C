#include <stdlib.h>
#include "symboltable.h"
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

