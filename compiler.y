%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "print.h"
#include "symboltable.h"

FILE *tree_file;   //for AST
FILE *table_file;  //for symboltable 

//global variables which can be used in other .c .h
struct PROGRAM *head;
void yyerror(char* text) {

    fprintf(stderr, "%s\n", text);
}
/*
void lyyerror(YYLTYPE t, char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    if(t.first_line)
        fprintf(stderr, "%d.%d-%d.%d: error: ", t.first_line, t.first_column, t.last_line, t.last_column);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
*/
%}

%union{
    struct PROGRAM       *ptr_program;
    struct DECLARATION   *ptr_declaration;
    struct IDENTIFIER    *ptr_identifier;
    struct FUNCTION      *ptr_function;
    struct PARAMETER     *ptr_parameter;
    struct COMPOUNDSTMT  *ptr_compoundstmt;
    struct STMT          *ptr_stmt;
    struct ASSIGN        *ptr_assign;
    struct CALL          *ptr_call;
    struct ARG           *ptr_arg;
    struct WHILE_S       *ptr_while_s;
    struct FOR_S         *ptr_for_s;
    struct IF_S          *ptr_if_s;
    struct ID_S          *ptr_id_s;
    struct EXPR          *ptr_expr;
    struct ADDIOP        *ptr_addiop;
    struct MULTOP        *ptr_multop;
    struct RELAOP        *ptr_relaop;
    struct EQLTOP        *ptr_eqltop;
    Type_e type;
    int intval;
    float floatval;
    char* id;
}

%token <intval>INTNUM <floatval>FLOATNUM <id>ID
%token INT FLOAT MINUS PLUS MULT DIV LE GE EQ NE GT LT
%token IF ELSE FOR WHILE DO RETURN DQUOT_T SQUOT_T AMP_T 


%type <type> Type

%type <ptr_program> Program
%type <ptr_declaration> Declaration DeclList
%type <ptr_identifier> Identifier IdentList
%type <ptr_function> Function FuncList
%type <ptr_parameter> Parameter ParamList 
%type <ptr_compoundstmt> CompoundStmt
%type <ptr_stmt> Stmt StmtList
%type <ptr_assign> Assign AssignStmt 
%type <ptr_call> Call CallStmt
%type <ptr_arg> Arg ArgList
%type <ptr_while_s> While_s
%type <ptr_for_s> For_s
%type <ptr_if_s> If_s
%type <ptr_expr> Expr RetStmt
%type <ptr_addiop> Addiop
%type <ptr_multop> Multop
%type <ptr_relaop> Relaop
%type <ptr_eqltop> Eqltop
%type <ptr_id_s> Id_s;


%right '=' 
%left EQ NE
%left LE GE GT LT
%left PLUS MINUS
%left MULT DIV
%right UNARY
%left '(' ')' 


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start Program
%%
//입력이 없는 경우는 main() 에서 head = NULL 인 상태로 처리됨.
//"DeclList" in "Program" denotes global declaration
Program: DeclList FuncList {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->decl = $1;
            prog->func = $2;
            head = prog;
            $$ = prog;
       }
       | DeclList {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->decl = $1;
            prog->func = NULL;
            head = prog;
            $$ = prog;
       }
       | FuncList {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->decl = NULL;
            prog->func = $1;
            head = prog;
            $$ = prog;
       }
       ;
DeclList: Declaration {
            $$ = $1;
        }
        | DeclList Declaration {
            struct DECLARATION *decl;
            decl = $2;
            decl->prev = $1;
            $$ = decl;
        }
        ;
FuncList: Function {
            $$ = $1;
        }
        | FuncList Function {
            struct FUNCTION *func;
            func = $2;
            func->prev = $1;
            $$ = func;
        }
        ;
Declaration: Type IdentList ';' {
                struct DECLARATION *decl = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
                decl->t = $1;
                decl->id = $2;
                $$ = decl;
            }
           ;
IdentList: Identifier {
            $$ = $1;
        }
        | IdentList ',' Identifier {
            struct IDENTIFIER *iden;
            iden = $3;
            iden->prev = $1;
            $$ = iden;
        }
        ;
Identifier: ID {
            struct IDENTIFIER *iden = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            iden->ID = $1;
            iden->intval = 0;   // zero, If scalar
            iden->prev = NULL;
            $$ = iden;
          }
          | ID '[' INTNUM ']' {
            struct IDENTIFIER *iden = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            iden->ID = $1;
            iden->intval = $3;   // zero, If scalar
            iden->prev = NULL;
            $$ = iden;
           }
          ;
ParamList: Parameter {
            struct PARAMETER *param;
            param = $1;
            param->prev = NULL;
            $$ = param;
        }
         | ParamList ',' Parameter {
            struct PARAMETER *param;
            param = $3;
            param->prev = $1;
            $$ = param;
        }
Parameter: Type Identifier {
            struct PARAMETER *param = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            param->t = $1;
            param->id = $2;
            param->prev = NULL;
            $$ = param;
        }
Function: Type ID '(' ')' CompoundStmt {
            struct FUNCTION *func = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            func->t = $1;
            func->ID = $2;
            func->param = NULL;
            func->cstmt = $5;
            $$ = func;

        }
        | Type ID '(' ParamList ')' CompoundStmt {
        struct FUNCTION *func = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        func->t = $1;
        func->ID = $2;
        func->param = $4;
        func->cstmt = $6;
        $$ = func;
    }
    ;
Type: INT { $$ = eInt;}
    | FLOAT { $$ = eFloat;}
    ;
//cf. Stmt 안에 CompoundStmt 존재
//StmtList 에서 empty 입력을 허용하지 않도록 StmtList 가 없는 Compound 정의
CompoundStmt: '{' '}' {
                struct COMPOUNDSTMT *comp = (struct COMPOUNDSTMT*) malloc (sizeof (struct COMPOUNDSTMT));
                comp->decl = NULL;
                comp->stmt = NULL;
                $$ = comp;
                /*
                { } 안에 { } 만 들어 있는 경우도 표현하기 위하여,
                NULL을 반환하지 않고 내용이 비어있어도 동적할당을 하였다.
                */
                
            }
            | '{' StmtList '}'  {
                struct COMPOUNDSTMT *comp = (struct COMPOUNDSTMT*) malloc (sizeof (struct COMPOUNDSTMT));
                comp->decl = NULL;
                comp->stmt = $2;
                $$ = comp;
            }
            |  '{' DeclList StmtList '}' {
                struct COMPOUNDSTMT *comp = (struct COMPOUNDSTMT*) malloc (sizeof (struct COMPOUNDSTMT));
                comp->decl = $2;
                comp->stmt = $3;
                $$ = comp;
            }
            |  '{' DeclList '}' {
                struct COMPOUNDSTMT *comp = (struct COMPOUNDSTMT*) malloc (sizeof (struct COMPOUNDSTMT));
                comp->decl = $2;
                comp->stmt = NULL;
                $$ = comp;
            }
            ;
StmtList: Stmt {
            struct STMT *stmt;
            stmt = $1;
            stmt->prev = NULL;
            $$ = stmt;
        }
        | StmtList Stmt {
            struct STMT *stmt;
            stmt = $2;
            stmt->prev = $1;
            $$ = stmt;
        }
        ;
Stmt: AssignStmt { 
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = eAssign;
        stmt->stmt.assign_ = $1;
        $$ = stmt;
    }
    | CallStmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = eCall;
        stmt->stmt.call_ = $1;
        $$ = stmt;
    }
    | RetStmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = eRet;
        stmt->stmt.return_ = $1;
        $$ = stmt;
    }
    | While_s {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = eWhile;
        stmt->stmt.while_ = $1;
        $$ = stmt;
    }
    | For_s {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = eFor;
        stmt->stmt.for_ = $1;
        $$ = stmt;
    }
    | If_s {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = eIf;
        stmt->stmt.if_ = $1;
        $$ = stmt;
    }
    | CompoundStmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = eCompound;
        stmt->stmt.cstmt_ = $1;
        $$ = stmt;
    }
    | ';' {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = eSemi;
        $$ = stmt;
    }
    ;
AssignStmt: Assign ';' { 
            $$ = $1;
          }
          ;
Assign: ID '=' Expr {
            struct ASSIGN *assign = (struct ASSIGN*) malloc (sizeof (struct ASSIGN));
            assign->ID = $1;
            assign->index = NULL; //NUL, if LHS is scalar variable
            assign->expr = $3;
            $$ = assign;
        }
      | ID '[' Expr ']' '=' Expr {
            struct ASSIGN *assign = (struct ASSIGN*) malloc (sizeof (struct ASSIGN));
            assign->ID = $1;
            assign->index = $3; 
            assign->expr = $6;
            $$ = assign;
        }
      ;
CallStmt: Call ';' {
            $$ = $1;
        }
        ;
/*
ArgList의 정의에서 empty가 되지 않도록
Call의 정의에서 ArgList가 빠진 형태를 추가하였다.
*/
Call: ID '(' ')' {
        struct CALL *call = (struct CALL*) malloc (sizeof (struct CALL));
        call->ID = $1;
        call->arg = NULL;
        $$ = call;
    }
    | ID '(' ArgList ')' {
        struct CALL *call = (struct CALL*) malloc (sizeof (struct CALL));
        call->ID = $1;
        call->arg = $3;
        $$ = call;
    }
    ;
ArgList: Arg { $$ = $1;}
       | ArgList ',' Arg {
            struct ARG *arg;
            arg = $3;
            arg->prev = $1;
            $$ = arg;
        }
       ;
Arg: Expr {
    struct ARG *arg = (struct ARG*) malloc (sizeof (struct ARG));
    arg->expr = $1;
    arg->prev = NULL;
    $$ = arg;
   }
   ;
RetStmt: RETURN ';' {
        $$ = NULL;
        }
       | RETURN Expr ';' {
        $$ = $2;
       }
       ;
Expr: MINUS Expr %prec UNARY {
        struct UNOP *unop = (struct UNOP*) malloc (sizeof (struct UNOP));
        unop->u = eNegative;
        unop->expr = $2;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eUnop;
        expr->expression.unop_ = unop;
        $$ = expr;
    }
    | Expr Addiop Expr {
        struct ADDIOP *addiop;
        addiop = $2;
        addiop->lhs=$1;
        addiop->rhs=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eAddi;
        expr->expression.addiop_ = addiop;
        $$ = expr;
    }
    | Expr Multop Expr {
        struct MULTOP *multop;
        multop = $2;
        multop->lhs=$1;
        multop->rhs=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eMulti;   // eMult와 다름 
        expr->expression.multop_ = multop;
        $$ = expr;
    }
    | Expr Relaop Expr {
        struct RELAOP *relaop;
        relaop = $2;
        relaop->lhs=$1;
        relaop->rhs=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eRela;  
        expr->expression.relaop_ = relaop;
        $$ = expr;
    }
    | Expr Eqltop Expr {
        struct EQLTOP *eqltop;
        eqltop = $2;
        eqltop->lhs=$1;
        eqltop->rhs=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eEqlt;  
        expr->expression.eqltop_ = eqltop;
        $$ = expr;
    }
    | Call {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eCallExpr;  
        expr->expression.call_ = $1;
        $$ = expr;
    }
    | INTNUM {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eIntnum;  
        expr->expression.intval = $1;
        $$ = expr;
    }    
    | FLOATNUM {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eFloatnum;  
        expr->expression.floatval = $1;
        $$ = expr;
    }
    | Id_s {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eId;  
        expr->expression.ID_ = $1;
        $$ = expr;
    } 
    | '(' Expr ')' {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->e = eExpr;  
        expr->expression.bracket = $2;
        $$ = expr;
    }
    ;
Id_s: ID {
        struct ID_S *id_s = (struct ID_S*)malloc(sizeof (struct ID_S));
        id_s->ID = $1;
        id_s->expr = NULL;
        $$ = id_s;
    }
    | ID '[' Expr ']' {
        struct ID_S *id_s = (struct ID_S*)malloc(sizeof (struct ID_S));
        id_s->ID = $1;
        id_s->expr = $3;
        $$ = id_s;
    }
    ;
Addiop: MINUS {
         struct ADDIOP *addiop = (struct ADDIOP*) malloc (sizeof (struct ADDIOP));
         addiop->a = eMinus;
         $$ = addiop;
      }
      | PLUS { 
        struct ADDIOP *addiop = (struct ADDIOP*) malloc (sizeof (struct ADDIOP));
        addiop->a = ePlus;
      $$ = addiop;
      }

      ;
Multop: MULT {
         struct MULTOP *multop = (struct MULTOP*) malloc (sizeof (struct MULTOP));
         multop->m = eMult;
         $$ = multop;
      }
      | DIV {
         struct MULTOP *multop = (struct MULTOP*) malloc (sizeof (struct MULTOP));
         multop->m = eDiv;
         $$ = multop;
      }
      ;
Relaop: LE {
         struct RELAOP *relaop = (struct RELAOP*) malloc (sizeof (struct RELAOP));
         relaop->r = eLE;
         $$ = relaop;
      }
      | GE {
         struct RELAOP *relaop = (struct RELAOP*) malloc (sizeof (struct RELAOP));
         relaop->r = eGE;
         $$ = relaop;
      }
      | GT {
         struct RELAOP *relaop = (struct RELAOP*) malloc (sizeof (struct RELAOP));
         relaop->r = eGT;
         $$ = relaop;
      }
      | LT { 
         struct RELAOP *relaop = (struct RELAOP*) malloc (sizeof (struct RELAOP));
         relaop->r = eLT;
         $$ = relaop;
      }
      ;
Eqltop: EQ {
         struct EQLTOP *eqltop = (struct EQLTOP*) malloc (sizeof (struct EQLTOP));
         eqltop->e = eEQ;
         $$ = eqltop;
      }
      | NE { 
         struct EQLTOP *eqltop = (struct EQLTOP*) malloc (sizeof (struct EQLTOP));
         eqltop->e = eNE;
         $$ = eqltop;
      }
      ;
While_s: WHILE '(' Expr ')'  Stmt  {
           struct WHILE_S* while_s = (struct WHILE_S*) malloc (sizeof(struct WHILE_S));
           while_s->do_while = false;
           while_s->cond = $3;
           while_s->stmt = $5;
           $$ = while_s;
        }
         | DO  Stmt  WHILE '(' Expr ')' ';' {
           struct WHILE_S* while_s = (struct WHILE_S*) malloc (sizeof(struct WHILE_S));
           while_s->do_while = true;
           while_s->cond = $5;
           while_s->stmt = $2;
           $$ = while_s;
        }
         ;
For_s: FOR '(' Assign ';' Expr ';' Assign ')' Stmt {
           struct FOR_S *for_s = (struct FOR_S*) malloc (sizeof(struct FOR_S));
           for_s->init = $3;
           for_s->cond = $5;
           for_s->inc = $7;
           for_s->stmt = $9;
           $$ = for_s;
        }
       ;
If_s: IF '(' Expr ')' Stmt %prec LOWER_THAN_ELSE {
       struct IF_S *if_s = (struct IF_S*) malloc (sizeof(struct IF_S));
       if_s->cond=$3;
       if_s->if_=$5;
       if_s->else_=NULL;
       $$ = if_s;
    }
      | IF '(' Expr ')' Stmt ELSE Stmt{
       struct IF_S *if_s = (struct IF_S*) malloc (sizeof(struct IF_S));
       if_s->cond=$3;
       if_s->if_=$5;
       if_s->else_=$7;
       $$ = if_s;
      }
      ;
%%
void doProcess();
int main(int argc, char* argv[]) {
    head = NULL;
    scopeHead = NULL;
    scopeTail = NULL;
    //print AST
    tree_file = fopen("tree.txt","w");
    table_file = fopen("table.txt","w");
    if(!yyparse())
        doProcess();
    fprintf(tree_file, "\n");
    close(tree_file);
    close(table_file);
    return 0;
}
void doProcess() {
    //TODO
    if(head == NULL)
        exit(1);
    //make global node
    scopeHead = newScope(sGLOBAL, NULL);
    scopeTail = scopeHead;
    if(head->decl != NULL)
        visitDeclaration(head->decl);
    if(head->func != NULL)
        visitFunction(head->func);
}
