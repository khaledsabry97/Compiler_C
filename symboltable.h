typedef enum { Scope_Global_Type, Scope_Func_Type, Scope_Do_While_Type, Scope_While_Type, Scope_For_Type, Scope_If_Type, Scope_Stmt_Group_Type } SCOPE_TYPE; //s : SCOPE

struct SCOPE {
    int dowhile_n;  //_n: number
    int while_n;
    int for_n;
    int if_n;
    int compound_n;
    SCOPE_TYPE scope_type;
    struct SCOPE* parent_scope;
    struct SCOPE* child_scope;
};

struct SCOPE *scopeHead, *scopeTail;
char* current_func_name;

//make node
struct SCOPE* newScope(SCOPE_TYPE scope_type, struct SCOPE* parent_scope);

//delete node
void deleteScope(struct SCOPE** scopeTail);

//returns the order of current SCOPE
int getMyOrder(SCOPE_TYPE scope_type, struct SCOPE* parent_scope);
