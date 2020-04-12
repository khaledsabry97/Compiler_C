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

/* void lyyerror(YYLTYPE t, char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    if(t.first_line)
        fprintf(stderr, "%d.%d-%d.%d: error: ", t.first_line, t.first_column, t.last_line, t.last_column);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
} */

%}

%union{
    struct PROGRAM       *ptr_program;
    struct DECLARATION   *ptr_declaration;
    struct IDENTIFIER    *ptr_identifier;
    struct FUNCTION      *ptr_function;
    struct PARAMETER     *ptr_parameter;
    struct STMTSGROUP  *ptr_compoundstmt;
    struct STMT          *ptr_stmt;
    struct ASSIGN_STMT        *ptr_assign;
    struct FUNC_CALL          *ptr_call;
    struct ARG           *ptr_arg;
    struct WHILE_STMT       *ptr_while_s;
    struct FOR_STMT         *_for_stmt;
    struct IF_STMT          *ptr_if_s;
    struct ID_S          *ptr_id_s;
    struct EXPR          *ptr_expr;
    struct ADD_OP        *ptr_addiop;
    struct MUL_OP        *ptr_multop;
    struct COM_OP        *ptr_relaop;
    struct EQL_OP        *ptr_eqltop;
    ID_TYPE type;
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
%type <_for_stmt> ForStmt
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
            prog->declaration = $1;
            prog->function = $2;
            head = prog;
            $$ = prog;
       }
       | DeclList {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->declaration = $1;
            prog->function = NULL;
            head = prog;
            $$ = prog;
       }
       | FuncList {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->declaration = NULL;
            prog->function = $1;
            head = prog;
            $$ = prog;
       }
       ;
DeclList: Declaration {
            $$ = $1;
        }
        | DeclList Declaration {
            struct DECLARATION *declaration;
            declaration = $2;
            declaration->prev = $1;
            $$ = declaration;
        }
        ;
FuncList: Function {
            $$ = $1;
        }
        | FuncList Function {
            struct FUNCTION *function;
            function = $2;
            function->prev = $1;
            $$ = function;
        }
        ;
Declaration: Type IdentList ';' {
                struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
                declaration->id_type = $1;
                declaration->id = $2;
                $$ = declaration;
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
            iden->int_val = 0;   // zero, If scalar
            iden->prev = NULL;
            $$ = iden;
          }
          | ID '[' INTNUM ']' {
            struct IDENTIFIER *iden = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            iden->ID = $1;
            iden->int_val = $3;   // zero, If scalar
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
            param->id_type = $1;
            param->id = $2;
            param->prev = NULL;
            $$ = param;
        }
Function: Type ID '(' ')' CompoundStmt {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = $1;
            function->ID = $2;
            function->param = NULL;
            function->stmts_group = $5;
            $$ = function;

        }
        | Type ID '(' ParamList ')' CompoundStmt {
        struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        function->id_type = $1;
        function->ID = $2;
        function->param = $4;
        function->stmts_group = $6;
        $$ = function;
    }
    ;
Type: INT { $$ = Int_Type;}
    | FLOAT { $$ = Float_Type;}
    ;
//cf. Stmt 안에 CompoundStmt 존재
//StmtList 에서 empty 입력을 허용하지 않도록 StmtList 가 없는 Compound 정의
CompoundStmt: '{' '}' {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = NULL;
                comp->stmt = NULL;
                $$ = comp;
                /*
                { } 안에 { } 만 들어 있는 경우도 표현하기 위하여,
                NULL을 반환하지 않고 내용이 비어있어도 동적할당을 하였다.
                */
                
            }
            | '{' StmtList '}'  {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = NULL;
                comp->stmt = $2;
                $$ = comp;
            }
            |  '{' DeclList StmtList '}' {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = $2;
                comp->stmt = $3;
                $$ = comp;
            }
            |  '{' DeclList '}' {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = $2;
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
        stmt->s = Equ_Type;
        stmt->stmt.assign_stmt = $1;
        $$ = stmt;
    }
    | CallStmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = Call_Type;
        stmt->stmt.func_call = $1;
        $$ = stmt;
    }
    | RetStmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = Return_Type;
        stmt->stmt.return_expr = $1;
        $$ = stmt;
    }
    | While_s {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = While_Type;
        stmt->stmt.while_stmt = $1;
        $$ = stmt;
    }
    | ForStmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = For_Type;
        stmt->stmt.for_stmt = $1;
        $$ = stmt;
    }
    | If_s {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = If_Type;
        stmt->stmt.if_stmt = $1;
        $$ = stmt;
    }
    | CompoundStmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = Comp_Type;
        stmt->stmt.stmts_group = $1;
        $$ = stmt;
    }
    | ';' {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->s = Semi_Type;
        $$ = stmt;
    }
    ;
AssignStmt: Assign ';' { 
            $$ = $1;
          }
          ;
Assign: ID '=' Expr {
            struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            assign->ID = $1;
            assign->index = NULL; //NUL, if LHS is scalar variable
            assign->expr = $3;
            $$ = assign;
        }
      | ID '[' Expr ']' '=' Expr {
            struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
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
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = $1;
        call->arg = NULL;
        $$ = call;
    }
    | ID '(' ArgList ')' {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
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
        struct UNI_OP *unop = (struct UNI_OP*) malloc (sizeof (struct UNI_OP));
        unop->uni_type = Neg_Type;
        unop->expr = $2;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eUnop;
        expr->expression.uni_op = unop;
        $$ = expr;
    }
    | Expr Addiop Expr {
        struct ADD_OP *addiop;
        addiop = $2;
        addiop->left_side=$1;
        addiop->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eAddi;
        expr->expression.add_op = addiop;
        $$ = expr;
    }
    | Expr Multop Expr {
        struct MUL_OP *multop;
        multop = $2;
        multop->left_side=$1;
        multop->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eMulti;   // eMult와 다름 
        expr->expression.mul_op = multop;
        $$ = expr;
    }
    | Expr Relaop Expr {
        struct COM_OP *relaop;
        relaop = $2;
        relaop->left_side=$1;
        relaop->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eRela;  
        expr->expression.com_op = relaop;
        $$ = expr;
    }
    | Expr Eqltop Expr {
        struct EQL_OP *eqltop;
        eqltop = $2;
        eqltop->left_side=$1;
        eqltop->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eEqlt;  
        expr->expression.eql_op = eqltop;
        $$ = expr;
    }
    | Call {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eCallExpr;  
        expr->expression.func_call = $1;
        $$ = expr;
    }
    | INTNUM {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eIntnum;  
        expr->expression.int_val = $1;
        $$ = expr;
    }    
    | FLOATNUM {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eFloatnum;  
        expr->expression.floatval = $1;
        $$ = expr;
    }
    | Id_s {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eId;  
        expr->expression.ID_ = $1;
        $$ = expr;
    } 
    | '(' Expr ')' {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = eExpr;  
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
         struct ADD_OP *addiop = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
         addiop->add_type = Minus_Type;
         $$ = addiop;
      }
      | PLUS { 
        struct ADD_OP *addiop = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        addiop->add_type = Plus_Type;
      $$ = addiop;
      }

      ;
Multop: MULT {
         struct MUL_OP *multop = (struct MUL_OP*) malloc (sizeof (struct MUL_OP));
         multop->mul_type = Mul_Type;
         $$ = multop;
      }
      | DIV {
         struct MUL_OP *multop = (struct MUL_OP*) malloc (sizeof (struct MUL_OP));
         multop->mul_type = Div_Type;
         $$ = multop;
      }
      ;
Relaop: LE {
         struct COM_OP *relaop = (struct COM_OP*) malloc (sizeof (struct COM_OP));
         relaop->com_type = Le_Type;
         $$ = relaop;
      }
      | GE {
         struct COM_OP *relaop = (struct COM_OP*) malloc (sizeof (struct COM_OP));
         relaop->com_type = Ge_Type;
         $$ = relaop;
      }
      | GT {
         struct COM_OP *relaop = (struct COM_OP*) malloc (sizeof (struct COM_OP));
         relaop->com_type = Gt_Type;
         $$ = relaop;
      }
      | LT { 
         struct COM_OP *relaop = (struct COM_OP*) malloc (sizeof (struct COM_OP));
         relaop->com_type = Lt_Type;
         $$ = relaop;
      }
      ;
Eqltop: EQ {
         struct EQL_OP *eqltop = (struct EQL_OP*) malloc (sizeof (struct EQL_OP));
         eqltop->eql_type = Eq_Type;
         $$ = eqltop;
      }
      | NE { 
         struct EQL_OP *eqltop = (struct EQL_OP*) malloc (sizeof (struct EQL_OP));
         eqltop->eql_type = Ne_Type;
         $$ = eqltop;
      }
      ;
While_s: WHILE '(' Expr ')'  Stmt  {
           struct WHILE_STMT* while_s = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
           while_s->do_while = false;
           while_s->condition = $3;
           while_s->stmt = $5;
           $$ = while_s;
        }
         | DO  Stmt  WHILE '(' Expr ')' ';' {
           struct WHILE_STMT* while_s = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
           while_s->do_while = true;
           while_s->condition = $5;
           while_s->stmt = $2;
           $$ = while_s;
        }
         ;
ForStmt: FOR '(' Assign ';' Expr ';' Assign ')' Stmt {
           struct FOR_STMT *for_s = (struct FOR_STMT*) malloc (sizeof(struct FOR_STMT));
           for_s->init = $3;
           for_s->condition = $5;
           for_s->inc = $7;
           for_s->stmt = $9;
           $$ = for_s;
        }
       ;
If_s: IF '(' Expr ')' Stmt %prec LOWER_THAN_ELSE {
       struct IF_STMT *if_ptr = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_ptr->condition=$3;
       if_ptr->if_stmt=$5;
       if_ptr->else_stmt=NULL;
       $$ = if_ptr;
    }
      | IF '(' Expr ')' Stmt ELSE Stmt{
       struct IF_STMT *if_ptr = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_ptr->condition=$3;
       if_ptr->if_stmt=$5;
       if_ptr->else_stmt=$7;
       $$ = if_ptr;
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
    if(head->declaration != NULL)
        visitDeclaration(head->declaration);
    if(head->function != NULL)
        visitFunction(head->function);
}
