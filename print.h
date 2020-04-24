#include "Abstract_Tree.h"
#include "Enums.h"
#define true 1 
#define false 0


struct BLOCK {
    int if_count;
    int for_count;
    int while_count;    
    int do_while_count;

    char name[1000];
    //char* name_;
    int function_number;
    int stmt_group_count;
    BLOCK_TYPE scope_type;
    struct BLOCK* parent_scope;
    struct BLOCK* child_scope;
};

struct BLOCK *head_scope_ptr;
struct BLOCK *current_scope_ptr;
char* current_func_name;
int current_func_number;

//make node
struct BLOCK* newScope(BLOCK_TYPE scope_type, struct BLOCK* parent_scope);

//delete node
void deleteScope(struct BLOCK** current_scope_ptr);

//returns the order of current BLOCK
int getMyOrder(BLOCK_TYPE scope_type, struct BLOCK* parent_scope);


struct Assembly{
    struct Assembly* prev;
    char str[1000];
};
























//struct Semantic;


void processProgram        (struct PROGRAM* program);
void processDeclaration   (struct DECLARATION* declaration);
void processIdentifier    (struct IDENTIFIER* identifier);
void processFunction      (struct FUNCTION* function);
void processParameter     (struct PARAMETER* parameter);
//void processArg           (struct ARG* arg, struct Semantic* sem);

void processAssignStmt    (struct ASSIGN_STMT* assign);
void processStmtGroup  (struct STMTSGROUP* stmts_group);
void processStmt          (struct STMT* stmt);

void processExpr          (struct EXPR *expr,bool must_return);

