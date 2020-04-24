#include <stdlib.h>
#include "symboltable.h"
//make node
struct BLOCK* newBlock(BLOCK_TYPE block_type, struct BLOCK* parent_block_ptr) {
    struct BLOCK* node = (struct BLOCK*) malloc (sizeof(struct BLOCK));
    node->block_type = block_type;
    node->do_while_count = 0;
    node->while_count = 0;
    node->for_count  = 0;
    node->if_count = 0;
    node->stmt_group_count = 0;

    if(parent_block_ptr != NULL) {
        node->parent_block_ptr = parent_block_ptr;
        parent_block_ptr->child_block_ptr = node;
    } else {
        node->parent_block_ptr = NULL;
    }

    node->child_block_ptr = NULL;
    return node;
}

//current_block_ptr denotes curScope node
void removeBlock(struct BLOCK** current_block_ptr) {
    struct BLOCK* curScope = *current_block_ptr;
    struct BLOCK* parent_block_ptr = curScope->parent_block_ptr;
    if(parent_block_ptr != NULL) {
        parent_block_ptr->child_block_ptr = NULL;
        (*current_block_ptr) = parent_block_ptr;
        free(curScope);
      } 
      
//    free(curScope);
}

//returns the order of current BLOCK
int getMyOrder(BLOCK_TYPE block_type, struct BLOCK* parent_block_ptr) {
    switch(block_type) {
        case Block_Do_While_Type:
            return (parent_block_ptr->do_while_count);

        case Block_While_Type:
            return (parent_block_ptr->while_count);

        case Block_For_Type:
            return (parent_block_ptr->for_count);

        case Block_If_Type:
            return (parent_block_ptr->if_count);

        case Block_Stmt_Group_Type:
            return (parent_block_ptr->stmt_group_count);
    }
}

