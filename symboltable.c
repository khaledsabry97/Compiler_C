#include <stdlib.h>
#include "symboltable.h"
//make node
struct SCOPE* newScope(SCOPE_TYPE scope_type, struct SCOPE* parent_scope) {
    struct SCOPE* node = (struct SCOPE*) malloc (sizeof(struct SCOPE));
    node->scope_type = scope_type;
    node->do_while_count = 0;
    node->while_count = 0;
    node->for_count  = 0;
    node->if_count = 0;
    node->stmt_group_count = 0;

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

