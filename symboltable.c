#include <stdlib.h>
#include "symboltable.h"
//make node
struct scope* newScope(SCOPETYPE type, struct scope* parent) {
    struct scope* node = (struct scope*) malloc (sizeof(struct scope));
    node->type = type;
    node->dowhile_n = 0;
    node->while_n = 0;
    node->for_n  = 0;
    node->if_n = 0;
    node->compound_n = 0;

    if(parent != NULL) {
        node->parent = parent;
        parent->child = node;
    } else {
        node->parent = NULL;
    }

    node->child = NULL;
    return node;
}

//scopeTail denotes curScope node
void deleteScope(struct scope** scopeTail) {
    struct scope* curScope = *scopeTail;
    struct scope* parent = curScope->parent;
    if(parent != NULL) {
        parent->child = NULL;
        (*scopeTail) = parent;
        free(curScope);
      } 
      
//    free(curScope);
}

//returns the order of current scope
int getMyOrder(SCOPETYPE type, struct scope* parent) {
    switch(type) {
        case sDOWHILE:
            return (parent->dowhile_n);

        case sWHILE:
            return (parent->while_n);

        case sFOR:
            return (parent->for_n);

        case sIF:
            return (parent->if_n);

        case sCOMPOUND:
            return (parent->compound_n);
    }
}

