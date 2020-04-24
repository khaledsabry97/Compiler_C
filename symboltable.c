#include <stdlib.h>
#include "symboltable.h"
//make node
struct BLOCK* newScope(BLOCK_TYPE scope_type, struct BLOCK* parent_scope) {
    struct BLOCK* node = (struct BLOCK*) malloc (sizeof(struct BLOCK));
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

//current_scope_ptr denotes curScope node
void deleteScope(struct BLOCK** current_scope_ptr) {
    struct BLOCK* curScope = *current_scope_ptr;
    struct BLOCK* parent_scope = curScope->parent_scope;
    if(parent_scope != NULL) {
        parent_scope->child_scope = NULL;
        (*current_scope_ptr) = parent_scope;
        free(curScope);
      } 
      
//    free(curScope);
}

//returns the order of current BLOCK
int getMyOrder(BLOCK_TYPE scope_type, struct BLOCK* parent_scope) {
    switch(scope_type) {
        case Block_Do_While_Type:
            return (parent_scope->do_while_count);

        case Block_While_Type:
            return (parent_scope->while_count);

        case Block_For_Type:
            return (parent_scope->for_count);

        case Block_If_Type:
            return (parent_scope->if_count);

        case Block_Stmt_Group_Type:
            return (parent_scope->stmt_group_count);
    }
}

