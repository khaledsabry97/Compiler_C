#include "Abstract_Tree.h"
#include "Enums.h"
#define true 1 
#define false 0


struct BLOCK *head_block_ptr;

struct BLOCK {
    struct BLOCK* parent_block_ptr;
    struct BLOCK* child_block_ptr;

    int if_count;
    int for_count;
    int while_count;    
    int do_while_count;
    int stmt_group_count;

    char name[1000];
    //char* name_;
    int function_number;

    BLOCK_TYPE block_type;
};


struct Assembly{
    struct Assembly* prev;
    char str[1000];
};




























