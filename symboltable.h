typedef enum { Block_Global_Type, Block_Func_Type, Block_Do_While_Type, Block_While_Type, Block_For_Type, Block_If_Type, Block_Stmt_Group_Type } BLOCK_TYPE; //s : BLOCK

struct BLOCK {
    int do_while_count;  //_n: number
    int while_count;
    int for_count;
    int if_count;
    int stmt_group_count;
    BLOCK_TYPE block_type;
    struct BLOCK* parent_block_ptr;
    struct BLOCK* child_block_ptr;
};

struct BLOCK *head_scope_ptr, *current_block_ptr;
char* current_func_name;

//make node
struct BLOCK* newBlock(BLOCK_TYPE block_type, struct BLOCK* parent_block_ptr);

//delete node
void removeBlock(struct BLOCK** current_block_ptr);

//returns the order of current BLOCK
int getMyOrder(BLOCK_TYPE block_type, struct BLOCK* parent_block_ptr);
