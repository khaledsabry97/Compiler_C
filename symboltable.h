typedef enum { Scope_Global_Type, Scope_Func_Type, Scope_Do_While_Type, Scope_While_Type, Scope_For_Type, Scope_If_Type, Scope_Stmt_Group_Type } SCOPE_TYPE; //s : SCOPE

struct SCOPE {
    int do_while_count;  //_n: number
    int while_count;
    int for_count;
    int if_count;
    int stmt_group_count;
    SCOPE_TYPE scope_type;
    struct SCOPE* parent_scope;
    struct SCOPE* child_scope;
};

struct SCOPE *head_scope_ptr, *current_scope_ptr;
char* current_func_name;

//make node
struct SCOPE* newScope(SCOPE_TYPE scope_type, struct SCOPE* parent_scope);

//delete node
void deleteScope(struct SCOPE** current_scope_ptr);

//returns the order of current SCOPE
int getMyOrder(SCOPE_TYPE scope_type, struct SCOPE* parent_scope);
