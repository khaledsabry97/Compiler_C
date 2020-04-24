#include "Abstract_Tree.h"
#include "Enums.h"
#define true 1 
#define false 0


struct BLOCK *head_scope_ptr;

struct BLOCK {
    int if_count;
    int for_count;
    int while_count;    
    int do_while_count;

    char name[1000];
    //char* name_;
    int function_number;
    int stmt_group_count;
    BLOCK_TYPE block_type;
    struct BLOCK* parent_block;
    struct BLOCK* child_block;
};


struct Assembly{
    struct Assembly* prev;
    char str[1000];
};




























