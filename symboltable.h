typedef enum { sGLOBAL, sFUNC, sDOWHILE, sWHILE, sFOR, sIF, sCOMPOUND } SCOPETYPE; //s : scope

struct scope {
    int dowhile_n;  //_n: number
    int while_n;
    int for_n;
    int if_n;
    int compound_n;
    SCOPETYPE type;
    struct scope* parent;
    struct scope* child;
};

struct scope *scopeHead, *scopeTail;
char* _curFuncName;

//make node
struct scope* newScope(SCOPETYPE type, struct scope* parent);

//delete node
void deleteScope(struct scope** scopeTail);

//returns the order of current scope
int getMyOrder(SCOPETYPE type, struct scope* parent);
