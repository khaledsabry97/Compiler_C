typedef enum { Scope_Global_Type, Scope_Func_Type, Scope_Do_While_Type, Scope_While_Type, Scope_For_Type, Scope_If_Type, Scope_Stmt_Group_Type } SCOPE_TYPE; //s : scope

struct scope {
    int dowhile_n;  //_n: number
    int while_n;
    int for_n;
    int if_n;
    int compound_n;
    SCOPE_TYPE scope_type;
    struct scope* parent;
    struct scope* child;
};

struct scope *scopeHead, *scopeTail;
char* _curFuncName;

//make node
struct scope* newScope(SCOPE_TYPE scope_type, struct scope* parent);

//delete node
void deleteScope(struct scope** scopeTail);

//returns the order of current scope
int getMyOrder(SCOPE_TYPE scope_type, struct scope* parent);
