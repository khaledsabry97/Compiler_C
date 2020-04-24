#include <stdlib.h>
#include "symboltable.h"
//make node
struct BLOCK* newBlock(BLOCK_TYPE block_type, struct BLOCK* parent_block) {
    struct BLOCK* node = (struct BLOCK*) malloc (sizeof(struct BLOCK));
    node->block_type = block_type;
    node->do_while_count = 0;
    node->while_count = 0;
    node->for_count  = 0;
    node->if_count = 0;
    node->stmt_group_count = 0;

    if(parent_block != NULL) {
        node->parent_block = parent_block;
        parent_block->child_block = node;
    } else {
        node->parent_block = NULL;
    }

    node->child_block = NULL;
    return node;
}

//current_block_ptr denotes curScope node
void removeBlock(struct BLOCK** current_block_ptr) {
    struct BLOCK* curScope = *current_block_ptr;
    struct BLOCK* parent_block = curScope->parent_block;
    if(parent_block != NULL) {
        parent_block->child_block = NULL;
        (*current_block_ptr) = parent_block;
        free(curScope);
      } 
      
//    free(curScope);
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

