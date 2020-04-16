%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "print.h"

FILE *tree_file; 
FILE *table_file; 
void print(struct PROGRAM* head);
void openFiles();
void closeFiles();
void yyerror(char* text) {

    fprintf(stderr, "%s\n", text);
}

/*
void yyerror(YYLTYPE t, char *s, ...)
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


    struct STMTSGROUP  *_stmtgroup;
    struct STMT          *_stmt;

    struct EXPR          *_expr;


}


%type <type> Type
%type <_program> Program
%type <_declaration>  Declaration_List
%type <_identifier> Identifier
%type <_function> Function_List
%type <_parameter> Parameter_List 
%type <_stmtgroup> Stmt_Group
%type <_stmt> Stmt Stmt_List
%type <_arg> Arg_List
%type <_expr> Expr 

;


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


%nonassoc NO_ELSE
%nonassoc ELSE

%start Program
%%

/******************************************************Program*********************************************************/

Program: Declaration_List Function_List {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = $1;
            program->function = $2;
            print(program);
            $$ = program;
       }
       | Declaration_List {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = $1;
            program->function = NULL;
            print(program);
            $$ = program;
       }
       | Function_List {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = NULL;
            program->function = $1;
            print(program);
            $$ = program;
       }
       ;
Declaration_List:  Type Identifier ';' {
                struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
                declaration->id_type = $1;
                declaration->id = $2;
                $$ = declaration;
        }
        | Declaration_List  Type Identifier ';' {
                struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
                declaration->prev = $1;
                declaration->id_type = $2;
                declaration->id = $3;
                $$ = declaration;
        }
        ;




Identifier: ID {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = $1;
            identifier->int_val = 0;   // zero, If scalar
            $$ = identifier;
          }
          | ID '[' INTNUM ']' {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = $1;
            identifier->int_val = $3;   // zero, If scalar
            $$ = identifier;
           }
          ;
          
Function_List: Type ID '(' ')' Stmt_Group {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = $1;
            function->ID = $2;
            function->parameter = NULL;
            function->stmts_group = $5;
            $$ = function;
        }
        | Function_List Type ID '(' Parameter_List ')' Stmt_Group {
        struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        function->prev = $1;
        function->id_type = $2;
        function->ID = $3;
        function->parameter = $5;
        function->stmts_group = $7;
        $$ = function;
    }
    | Type ID '(' Parameter_List ')' Stmt_Group {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = $1;
            function->ID = $2;
            function->parameter = $4;
            function->stmts_group = $6;
            $$ = function;
        }
        | Function_List Type ID '(' ')' Stmt_Group {
        struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        function->prev = $1;
        function->id_type = $2;
        function->ID = $3;
        function->parameter = NULL;
        function->stmts_group = $6;
        $$ = function;
    };


Parameter_List: Type Identifier {
            struct PARAMETER *parameter = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            parameter->id_type = $1;
            parameter->id = $2;
            parameter->prev = NULL;
            $$ = parameter;
        }
         | Parameter_List ',' Type Identifier {
            struct PARAMETER *parameter = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            parameter->id_type = $3;
            parameter->id = $4;
            parameter->prev = $1;
            $$ = parameter;
        };

Arg_List: Expr { 
    struct ARG *arg = (struct ARG*) malloc (sizeof (struct ARG));
    arg->expr = $1;
    arg->prev = NULL;
    $$ = arg;
    }
    | Arg_List ',' Expr {
    struct ARG *arg = (struct ARG*) malloc (sizeof (struct ARG));
    arg->expr = $3;
    arg->prev = $1;
    $$ = arg;
        }
       ;





Type: INT { $$ = Int_Type;}
    | FLOAT { $$ = Float_Type;}
    ;


/*********************************************** Statements **************************************************/

Stmt: ID '=' Expr ';' { 
            struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            assign->ID = $1;
            assign->index = NULL; 
            assign->expr = $3;
             
            struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
            stmt->stmt_type = Equ_Type;
            stmt->stmt.assign_stmt = assign;
            $$ = stmt;
          }
    | ID '[' Expr ']' '=' Expr ';' {
            struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            assign->ID = $1;
            assign->index = $3; 
            assign->expr = $6;
            
            struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
            stmt->stmt_type = Equ_Type;
            stmt->stmt.assign_stmt = assign;
            $$ = stmt;
             }
            
    | ID '(' ')' ';' {
                struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
                call->ID = $1;
                call->arg = NULL;
                struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Call_Type;
        stmt->stmt.func_call = call;
        $$ = stmt;
                }
    | ID '(' Arg_List ')' ';' {
                    struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
                    call->ID = $1;
                    call->arg = $3;
                    struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Call_Type;
        stmt->stmt.func_call = call;
        $$ = stmt;
                }
    | RETURN ';' {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Return_Type;
        stmt->stmt.return_expr = NULL;
        $$ = stmt;
        }
       | RETURN Expr ';' {
         struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Return_Type;
        stmt->stmt.return_expr = $2;
        $$ = stmt;
       } 
    | IF '(' Expr ')' Stmt %prec NO_ELSE {
       struct IF_STMT *if_stmt = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_stmt->condition=$3;
       if_stmt->if_stmt=$5;
       if_stmt->else_stmt=NULL;
       
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = If_Type;
        stmt->stmt.if_stmt = if_stmt;
        $$ = stmt;
    }
      | IF '(' Expr ')' Stmt ELSE Stmt{
       struct IF_STMT *if_stmt = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_stmt->condition=$3;
       if_stmt->if_stmt=$5;
       if_stmt->else_stmt=$7;
       
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = If_Type;
        stmt->stmt.if_stmt = if_stmt;
        $$ = stmt;
      }
    | FOR '(' ID '=' Expr ';' Expr ';' ID '=' Expr ')' Stmt {
            struct ASSIGN_STMT *assign1 = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            struct ASSIGN_STMT *assign2 = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));

            assign1->ID = $3;
            assign1->index = NULL; 
            assign1->expr = $5;

            assign2->ID = $9;
            assign2->index = NULL; 
            assign2->expr = $11;
            
          
           struct FOR_STMT *for_stmt = (struct FOR_STMT*) malloc (sizeof(struct FOR_STMT));
           for_stmt->init = assign1;
           for_stmt->condition = $7;
           for_stmt->inc = assign2;
           for_stmt->stmt = $13;
           
           struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = For_Type;
        stmt->stmt.for_stmt = for_stmt;
        $$ = stmt;
        } 
    | WHILE '(' Expr ')'  Stmt  {
        struct WHILE_STMT* while_stmt = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
        while_stmt->do_while = false;
        while_stmt->condition = $3;
        while_stmt->stmt = $5;

        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = While_Type;
        stmt->stmt.while_stmt = while_stmt;
        $$ = stmt;
        }
         | DO  Stmt  WHILE '(' Expr ')' ';' {
        struct WHILE_STMT* while_stmt = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
        while_stmt->do_while = true;
        while_stmt->condition = $5;
        while_stmt->stmt = $2;
           
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = While_Type;
        stmt->stmt.while_stmt = while_stmt;
        $$ = stmt;
        }
        
    | '{' Declaration_List Stmt_List '}' {
        struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
        stmts_group->declaration = $2;
        stmts_group->stmt = $3;
        
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmt.stmts_group = stmts_group;
        $$ = stmt;
            }
            | 
             '{' Stmt_List '}'  {
        struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
        stmts_group->declaration = NULL;
        stmts_group->stmt = $2;
        
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmt.stmts_group = stmts_group;
        $$ = stmt;
            }
            |'{' Declaration_List '}' {
        struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
        stmts_group->declaration = $2;
        stmts_group->stmt = NULL;
        
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmt.stmts_group = stmts_group;
        $$ = stmt;
            }
            |
             '{' '}' {
        struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
        stmts_group->declaration = NULL;
        stmts_group->stmt = NULL;
        
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmt.stmts_group = stmts_group;
        $$ = stmt;
           
                
            }  
    | ';' {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Semi_Colon_Type;
        $$ = stmt;
    }
    ;




Stmt_Group: '{' Declaration_List Stmt_List '}' {
                struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                stmts_group->declaration = $2;
                stmts_group->stmt = $3;
                $$ = stmts_group;
            }
            | 
             '{' Stmt_List '}'  {
                struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                stmts_group->declaration = NULL;
                stmts_group->stmt = $2;
                $$ = stmts_group;
            }
            |'{' Declaration_List '}' {
                struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                stmts_group->declaration = $2;
                stmts_group->stmt = NULL;
                $$ = stmts_group;
            }
            |
             '{' '}' {
                struct STMTSGROUP *stmts_group = (struct STMTSGROUP*) malloc (sizeof (struct STMTSGROUP));
                stmts_group->declaration = NULL;
                stmts_group->stmt = NULL;
                $$ = stmts_group;
           
                
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

/********************************Expressions***************************************/

Expr: MINUS Expr %prec UNARY {
        struct UNI_OP *uni_op = (struct UNI_OP*) malloc (sizeof (struct UNI_OP));
        uni_op->uni_type = Neg_Type;
        uni_op->expr = $2;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Uni_Type;
        expr->expression.uni_op = uni_op;
        $$ = expr;
    }
    | Expr MINUS Expr {
        struct ADD_OP *add_op = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        add_op->add_type = Minus_Type;
        add_op->left_side=$1;
        add_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = add_op;
        $$ = expr;
    }
    | Expr PLUS Expr {
        struct ADD_OP *add_op = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        add_op->add_type = Plus_Type;
        add_op->left_side=$1;
        add_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = add_op;
        $$ = expr;
    }
    | Expr MUL Expr {
        struct MUL_OP *mul_op = (struct MUL_OP*) malloc (sizeof (struct MUL_OP));
        mul_op->mul_type = Mul_Type;
        mul_op->left_side=$1;
        mul_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Mult_Type;  
        expr->expression.mul_op = mul_op;
        $$ = expr;
    }
    | Expr DIV Expr {
        struct MUL_OP *mul_op = (struct MUL_OP*) malloc (sizeof (struct MUL_OP));
        mul_op->mul_type = Div_Type;
        mul_op->left_side=$1;
        mul_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Mult_Type;  
        expr->expression.mul_op = mul_op;
        $$ = expr;
    }
    | Expr LE Expr {
        struct COM_OP *com_op = (struct COM_OP*) malloc (sizeof (struct COM_OP));
        com_op->com_type = Le_Type;
        com_op->left_side=$1;
        com_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = com_op;
        $$ = expr;
    }
    | Expr GE Expr {
        struct COM_OP *com_op = (struct COM_OP*) malloc (sizeof (struct COM_OP));
        com_op->com_type = Ge_Type;
        com_op->left_side=$1;
        com_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = com_op;
        $$ = expr;
    }
    | Expr GT Expr {
        struct COM_OP *com_op = (struct COM_OP*) malloc (sizeof (struct COM_OP));
        com_op->com_type = Gt_Type;
        com_op->left_side=$1;
        com_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = com_op;
        $$ = expr;
    }
    | Expr LT Expr {
        struct COM_OP *com_op = (struct COM_OP*) malloc (sizeof (struct COM_OP));
        com_op->com_type = Lt_Type;
        com_op->left_side=$1;
        com_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Com_Type;  
        expr->expression.com_op = com_op;
        $$ = expr;
    }
    | Expr EQ Expr {
        struct EQL_OP *eql_op = (struct EQL_OP*) malloc (sizeof (struct EQL_OP));
        eql_op->eql_type = Eq_Type;
        eql_op->left_side=$1;
        eql_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Eql_Type;  
        expr->expression.eql_op = eql_op;
        $$ = expr;
    }
    | Expr NE Expr {
        struct EQL_OP *eql_op = (struct EQL_OP*) malloc (sizeof (struct EQL_OP));
        eql_op->eql_type = Ne_Type;
        eql_op->left_side=$1;
        eql_op->right_side=$3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Eql_Type;  
        expr->expression.eql_op = eql_op;
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
    | ID {
        struct ID_EXPR *id_expr = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_expr->ID = $1;
        id_expr->expr = NULL;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Id_Type;  
        expr->expression.id_expr = id_expr;
        $$ = expr;
    } 
    | ID '[' Expr ']' {
        struct ID_EXPR *id_expr = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_expr->ID = $1;
        id_expr->expr = $3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Id_Type;  
        expr->expression.id_expr = id_expr;
        $$ = expr;
    } 
    | '(' Expr ')' {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Expr_Type;  
        expr->expression.bracket = $2;
        $$ = expr;
    }
    | ID '(' ')' {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = $1;
        call->arg = NULL;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = CallExpr_Type;  
        expr->expression.func_call = call;
        $$ = expr;
    }
    | ID '(' Arg_List ')' {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = $1;
        call->arg = $3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = CallExpr_Type;  
        expr->expression.func_call = call;
        $$ = expr;
    }
    ;



%%




int main(int argc, char* argv[]) {
    openFiles();
    yyparse();
    closeFiles();
    return 0;
}
void print(struct PROGRAM* head) {
    if(head == NULL)
        exit(1);
    scopeHead = newScope(Scope_Global_Type, NULL);
    scopeTail = scopeHead;
    if(head->declaration != NULL)
        processDeclaration(head->declaration);
    if(head->function != NULL)
        processFunction(head->function);
}


void openFiles()
{
    tree_file = fopen("tree.txt","w");
    table_file = fopen("table.txt","w");
}
void closeFiles()
{
    fprintf(tree_file, "\n");
    pclose(tree_file);
    pclose(table_file);
}