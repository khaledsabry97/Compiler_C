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
    ID_TYPE type;
    char* id;
    int intval;
    float floatval;
    

    struct PROGRAM       *_program;
    struct DECLARATION   *_declaration;
    struct IDENTIFIER    *_identifier;
    struct FUNCTION      *_function;
    struct PARAMETER     *_parameter;
    struct ARG           *_arg;

    struct FUNC_CALL          *_call;
    struct IF_STMT          *_if_stmt;
    struct FOR_STMT         *_for_stmt;
    struct WHILE_STMT       *_while_stmt;
    struct ASSIGN_STMT        *_assign_stmt;
    struct STMTSGROUP  *_stmtgroup;
    struct STMT          *_stmt;

    struct ID_EXPR          *_id_expr;
    struct ADD_OP        *_add_op;
    struct MUL_OP        *_mul_op;
    struct EQL_OP        *_eql_op;

    struct COM_OP        *_com_op;
    struct EXPR          *_expr;


}


%type <type> Type
%type <_program> Program
%type <_declaration> Declaration Declaration_List
%type <_identifier> Identifier Identifier_List
%type <_function> Function Function_List
%type <_parameter> Parameter Parameter_List 
%type <_stmtgroup> Stmt_Group
%type <_stmt> Stmt Stmt_List
%type <_assign_stmt> Assign Assign_Stmt 
%type <_call> Call Call_Stmt
%type <_arg> Arg Arg_List
%type <_while_stmt> While_Stmt
%type <_for_stmt> For_Stmt
%type <_if_stmt> If_Stmt
%type <_expr> Expr Ret_Stmt
%type <_add_op> Add_Op
%type <_mul_op> Mul_Op
%type <_com_op> Com_Op
%type <_eql_op> Eql_Op
%type <_id_expr> Id_Expr;


%token <id>ID
%token <intval>INTNUM
%token <floatval>FLOATNUM

%token INT
%token FLOAT
%token MINUS
%token PLUS
%token MUL
%token DIV
%token LE
%token GE
%token EQ
%token NE
%token GT
%token LT
%token IF
%token ELSE
%token FOR
%token WHILE
%token DO
%token RETURN
%token DOUBLE_QT
%token SINGLE_QT


%right '=' 
%left EQ NE
%left LE GE GT LT
%left PLUS MINUS
%left MUL DIV
%right UNARY
%left '(' ')' 


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start Program
%%
//입력이 없는 경우는 main() 에서 head = NULL 인 상태로 처리됨.
//"Declaration_List" in "Program" denotes global declaration
Program: Declaration_List Function_List {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->declaration = $1;
            prog->function = $2;
            head = prog;
            $$ = prog;
       }
       | Declaration_List {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->declaration = $1;
            prog->function = NULL;
            head = prog;
            $$ = prog;
       }
       | Function_List {
            struct PROGRAM *prog = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            prog->declaration = NULL;
            prog->function = $1;
            head = prog;
            $$ = prog;
       }
       ;
Declaration_List: Declaration {
            $$ = $1;
        }
        | Declaration_List Declaration {
            struct DECLARATION *declaration;
            declaration = $2;
            declaration->prev = $1;
            $$ = declaration;
        }
        ;
Function_List: Function {
            $$ = $1;
        }
        | Function_List Function {
            struct FUNCTION *function;
            function = $2;
            function->prev = $1;
            $$ = function;
        }
        ;
Declaration: Type Identifier_List ';' {
                struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
                declaration->id_type = $1;
                declaration->id = $2;
                $$ = declaration;
            }
           ;
Identifier_List: Identifier {
            $$ = $1;
        }
        | Identifier_List ',' Identifier {
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
Parameter_List: Parameter {
            struct PARAMETER *param;
            param = $1;
            param->prev = NULL;
            $$ = param;
        }
         | Parameter_List ',' Parameter {
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
Function: Type ID '(' ')' Stmt_Group {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = $1;
            function->ID = $2;
            function->param = NULL;
            function->stmts_group = $5;
            $$ = function;

        }
        | Type ID '(' Parameter_List ')' Stmt_Group {
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
//cf. Stmt 안에 Stmt_Group 존재
//Stmt_List 에서 empty 입력을 허용하지 않도록 Stmt_List 가 없는 Compound 정의
Stmt_Group: '{' '}' {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = NULL;
                comp->stmt = NULL;
                $$ = comp;
                /*
                { } 안에 { } 만 들어 있는 경우도 표현하기 위하여,
                NULL을 반환하지 않고 내용이 비어있어도 동적할당을 하였다.
                */
                
            }
            | '{' Stmt_List '}'  {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = NULL;
                comp->stmt = $2;
                $$ = comp;
            }
            |  '{' Declaration_List Stmt_List '}' {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = $2;
                comp->stmt = $3;
                $$ = comp;
            }
            |  '{' Declaration_List '}' {
                struct STMTSGROUP *comp = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                comp->declaration = $2;
                comp->stmt = NULL;
                $$ = comp;
            }
            ;
Stmt_List: Stmt {
            struct STMT *stmt;
            stmt = $1;
            stmt->prev = NULL;
            $$ = stmt;
        }
        | Stmt_List Stmt {
            struct STMT *stmt;
            stmt = $2;
            stmt->prev = $1;
            $$ = stmt;
        }
        ;
Stmt: Assign_Stmt { 
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Equ_Type;
        stmt->stmt.assign_stmt = $1;
        $$ = stmt;
    }
    | Call_Stmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Call_Type;
        stmt->stmt.func_call = $1;
        $$ = stmt;
    }
    | Ret_Stmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Return_Type;
        stmt->stmt.return_expr = $1;
        $$ = stmt;
    }
    | While_Stmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = While_Type;
        stmt->stmt.while_stmt = $1;
        $$ = stmt;
    }
    | For_Stmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = For_Type;
        stmt->stmt.for_stmt = $1;
        $$ = stmt;
    }
    | If_Stmt {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = If_Type;
        stmt->stmt.if_stmt = $1;
        $$ = stmt;
    }
    | Stmt_Group {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Comp_Type;
        stmt->stmt.stmts_group = $1;
        $$ = stmt;
    }
    | ';' {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Semi_Type;
        $$ = stmt;
    }
    ;
Assign_Stmt: Assign ';' { 
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
Call_Stmt: Call ';' {
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
    | ID '(' Arg_List ')' {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = $1;
        call->arg = $3;
        $$ = call;
    }
    ;
Arg_List: Arg { $$ = $1;}
       | Arg_List ',' Arg {
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
Ret_Stmt: RETURN ';' {
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
        expr->expr_type = Uni_Type;
        expr->expression.uni_op = unop;
        $$ = expr;
    }
    | Expr Add_Op Expr {
        struct ADD_OP *addiop;
        addiop = $2;
        addiop->left_side=$1;
        addiop->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = addiop;
        $$ = expr;
    }
    | Expr Mul_Op Expr {
        struct MUL_OP *multop;
        multop = $2;
        multop->left_side=$1;
        multop->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Mult_Type;   // eMult와 다름 
        expr->expression.mul_op = multop;
        $$ = expr;
    }
    | Expr Com_Op Expr {
        struct COM_OP *relaop;
        relaop = $2;
        relaop->left_side=$1;
        relaop->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = relaop;
        $$ = expr;
    }
    | Expr Eql_Op Expr {
        struct EQL_OP *eqltop;
        eqltop = $2;
        eqltop->left_side=$1;
        eqltop->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Eql_Type;  
        expr->expression.eql_op = eqltop;
        $$ = expr;
    }
    | Call {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = CallExpr_Type;  
        expr->expression.func_call = $1;
        $$ = expr;
    }
    | INTNUM {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = IntNum_Type;  
        expr->expression.int_val = $1;
        $$ = expr;
    }    
    | FLOATNUM {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = FloatNum_Type;  
        expr->expression.floatval = $1;
        $$ = expr;
    }
    | Id_Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Id_Type;  
        expr->expression.id_expr = $1;
        $$ = expr;
    } 
    | '(' Expr ')' {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Expr_Type;  
        expr->expression.bracket = $2;
        $$ = expr;
    }
    ;
Id_Expr: ID {
        struct ID_EXPR *id_s = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_s->ID = $1;
        id_s->expr = NULL;
        $$ = id_s;
    }
    | ID '[' Expr ']' {
        struct ID_EXPR *id_s = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_s->ID = $1;
        id_s->expr = $3;
        $$ = id_s;
    }
    ;
Add_Op: MINUS {
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
Mul_Op: MUL {
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
Com_Op: LE {
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
Eql_Op: EQ {
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
While_Stmt: WHILE '(' Expr ')'  Stmt  {
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
For_Stmt: FOR '(' Assign ';' Expr ';' Assign ')' Stmt {
           struct FOR_STMT *for_s = (struct FOR_STMT*) malloc (sizeof(struct FOR_STMT));
           for_s->init = $3;
           for_s->condition = $5;
           for_s->inc = $7;
           for_s->stmt = $9;
           $$ = for_s;
        }
       ;
If_Stmt: IF '(' Expr ')' Stmt %prec LOWER_THAN_ELSE {
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
