typedef enum { Block_Global_Type, Block_Func_Type, Block_Do_While_Type, Block_While_Type, Block_For_Type, Block_If_Type, Block_Stmt_Group_Type } BLOCK_TYPE; //s : BLOCK

struct BLOCK {
    int do_while_count;  //_n: number
    int while_count;
    int for_count;
    int if_count;
    int stmt_group_count;
    BLOCK_TYPE scope_type;
    struct BLOCK* parent_scope;
    struct BLOCK* child_scope;
};

struct BLOCK *head_scope_ptr, *current_scope_ptr;
char* current_func_name;

//make node
struct BLOCK* newScope(BLOCK_TYPE scope_type, struct BLOCK* parent_scope);

//delete node
void deleteScope(struct BLOCK** current_scope_ptr);

//returns the order of current BLOCK
int getMyOrder(BLOCK_TYPE scope_type, struct BLOCK* parent_scope);
