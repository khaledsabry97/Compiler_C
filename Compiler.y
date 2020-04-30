%error-verbose

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Abstract_Tree.h"
#include "Compiler.h"

FILE *assembly_file; 
FILE *symbol_file; 
FILE *semantic_file;
extern int line_counter;
void process(struct PROGRAM* head);
void openFiles();
void closeFiles();
void yyerror(char* text) {

    fprintf(stderr, "%s\n", text);
}

%}

%union{
    ID_TYPE type;
    char* id;
    int intval;
    float floatval;
    

    struct PROGRAM       *_program;
    struct DECLARATION   *_declaration;
    struct FUNCTION      *_function;
    struct PARAMETER     *_parameter;
    struct ARG           *_arg;


    struct STMTSGROUP  *_stmtgroup;
    struct STMT          *_stmt;

    struct EXPR          *_expr;


}


%type <type> Type
%type <_program> Program
%type <_declaration>  Declarations
%type <_function> Functions
%type <_parameter> Parameters 
%type <_stmtgroup> Stmt_Group
%type <_stmt> Stmt Stmt_List
%type <_arg> Args
%type <_expr> Expr ;


%token <id>ID
%token <intval>INTNUM
%token <floatval>FLOATNUM

%token INT
%token FLOAT
%token CONST
%token MINUS
%token MM
%token PLUS
%token PP
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

%right '=' 
%left EQ NE
%left LE GE GT LT
%left PLUS MINUS
%left MUL DIV
%right UMINUS
%left '(' ')' 

%nonassoc IFX
%nonassoc ELSE

%start Program
%%

/******************************************************Program*********************************************************/

Program: Declarations Functions {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = $1;
            program->function = $2;
            compileProgram(program);
            printf("finally%d\n",line_counter);

            $$ = program; 
       }
       | Declarations {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = $1;
            program->function = NULL;
            compileProgram(program);
                        printf("finally%d\n",line_counter);

            $$ = program;
       }
       | Functions {
            struct PROGRAM *program = (struct PROGRAM*) malloc (sizeof (struct PROGRAM));
            program->declaration = NULL;
            program->function = $1;
            compileProgram(program);
            printf("finally%d\n",line_counter);
            $$ = program;
       }| %empty
       ;
Declarations:  Type ID ';' {
            struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
            declaration->id_type = $1;
            declaration->ID = $2;
            $$ = declaration;
        }
        | Declarations  Type ID ';' {
            struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
            declaration->prev = $1;
            declaration->id_type = $2;
            declaration->ID = $3;
            $$ = declaration;
        }
        ;

          
Functions: Type ID '(' ')' Stmt_Group {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = $1;
            function->ID = $2;
            function->parameter = NULL;
            function->stmts_group = $5;
            $$ = function;
        }
        | Functions Type ID '(' Parameters ')' Stmt_Group {
        struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        function->prev = $1;
        function->id_type = $2;
        function->ID = $3;
        function->parameter = $5;
        function->stmts_group = $7;
        $$ = function;
    }
    | Type ID '(' Parameters ')' Stmt_Group {
            struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
            function->id_type = $1;
            function->ID = $2;
            function->parameter = $4;
            function->stmts_group = $6;
            $$ = function;
        }
        | Functions Type ID '(' ')' Stmt_Group {
        struct FUNCTION *function = (struct FUNCTION*) malloc (sizeof (struct FUNCTION));
        function->prev = $1;
        function->id_type = $2;
        function->ID = $3;
        function->parameter = NULL;
        function->stmts_group = $6;
        $$ = function;
    };


Parameters: Type ID {
            struct PARAMETER *parameter = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            parameter->id_type = $1;
            parameter->ID = $2;
            parameter->prev = NULL;
            $$ = parameter;
        }
         | Parameters ',' Type ID {
            struct PARAMETER *parameter = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            parameter->id_type = $3;
            parameter->ID = $4;
            parameter->prev = $1;
            $$ = parameter;
        };

Args: Expr { 
    struct ARG *arg = (struct ARG*) malloc (sizeof (struct ARG));
    arg->expr = $1;
    arg->prev = NULL;
    $$ = arg;
    }
    | Args ',' Expr {
    struct ARG *arg = (struct ARG*) malloc (sizeof (struct ARG));
    arg->expr = $3;
    arg->prev = $1;
    $$ = arg;
        }
       ;

Type: INT { $$ = Int_Type;}
    | FLOAT { $$ = Float_Type;}
    | CONST INT { $$ = Const_Int_Type;}
    | CONST FLOAT { $$ = Const_Float_Type;}
    ;


/*********************************************** Statements **************************************************/

Stmt: ID '=' Expr ';' { 
            struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            assign->ID = $1;
            assign->expr = $3;
             
            struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
            stmt->stmt_type = Equ_Type;
            stmt->assign_stmt = assign;

            $$ = stmt;
    } | RETURN ';' {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Return_Type;
        stmt->return_expr = NULL;
        $$ = stmt;
        }
       | RETURN Expr ';' {
         struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Return_Type;
        stmt->return_expr = $2;
        $$ = stmt;
       } 
    | IF '(' Expr ')' Stmt %prec IFX {
       struct IF_STMT *if_stmt = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_stmt->condition=$3;
       if_stmt->if_stmt=$5;
       if_stmt->else_stmt=NULL;
       
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = If_Type;
        stmt->if_stmt = if_stmt;
        $$ = stmt;
    }
      | IF '(' Expr ')' Stmt ELSE Stmt{
       struct IF_STMT *if_stmt = (struct IF_STMT*) malloc (sizeof(struct IF_STMT));
       if_stmt->condition=$3;
       if_stmt->if_stmt=$5;
       if_stmt->else_stmt=$7;
       
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = If_Type;
        stmt->if_stmt = if_stmt;
        $$ = stmt;
      }
    | FOR '(' ID '=' Expr ';' Expr ';' ID '=' Expr ')' Stmt {
            struct ASSIGN_STMT *assign1 = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
            struct ASSIGN_STMT *assign2 = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));

            assign1->ID = $3;
            assign1->expr = $5;

            assign2->ID = $9;
            assign2->expr = $11;
            
          
           struct FOR_STMT *for_stmt = (struct FOR_STMT*) malloc (sizeof(struct FOR_STMT));
           for_stmt->init = assign1;
           for_stmt->condition = $7;
           for_stmt->inc = assign2;
           for_stmt->stmt = $13;
           
           struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = For_Type;
        stmt->for_stmt = for_stmt;
        $$ = stmt;
        } 
    | WHILE '(' Expr ')'  Stmt  {
        struct WHILE_STMT* while_stmt = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
        while_stmt->do_while = false;
        while_stmt->condition = $3;
        while_stmt->stmt = $5;

        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = While_Type;
        stmt->while_stmt = while_stmt;
        $$ = stmt;
        }
         | DO  Stmt  WHILE '(' Expr ')' ';' {
        struct WHILE_STMT* while_stmt = (struct WHILE_STMT*) malloc (sizeof(struct WHILE_STMT));
        while_stmt->do_while = true;
        while_stmt->condition = $5;
        while_stmt->stmt = $2;
           
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = While_Type;
        stmt->while_stmt = while_stmt;
        $$ = stmt;
        }
        
    | Stmt_Group {

        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Stmt_Group_Type;
        stmt->stmts_group = $1;
        $$ = stmt;
            }
             
    | ID PP {
        struct EXPR *expr2 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr2->expr_type = Id_Type;  
        expr2->ID = $1;

        struct EXPR *expr1 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr1->expr_type = IntNum_Type;
        expr1->int_val = 1;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Plus_Type;
        expr->left_side=expr2;
        expr->right_side= expr1;

        struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
        assign->ID = $1;
        assign->expr = expr;
             
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Equ_Type;
        stmt->assign_stmt = assign;
        printf("sfsdfsdfsdF%d\n",line_counter);

        $$ = stmt;
    }| ID MM {
        struct EXPR *expr2 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr2->expr_type = Id_Type;  
        expr2->ID = $1;

        struct EXPR *expr1 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr1->expr_type = IntNum_Type;
        expr1->int_val = 1;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Minus_Type;
        expr->left_side=expr2;
        expr->right_side= expr1;

        struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
        assign->ID = $1;
        assign->expr = expr;
             
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Equ_Type;
        stmt->assign_stmt = assign;
        printf("sfsdfsdfsdF%d\n");

        $$ = stmt;
    }| ';' {
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Semi_Colon_Type;
        $$ = stmt;
    }| error ';' {printf("forget to add semicolon at \n"); yyerrok;}
    ;




Stmt_Group: '{' Declarations Stmt_List '}' {
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
            |'{' Declarations '}' {
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
            | error '}' {printf("forgot to open statemtent group\n");
            yyerrok;
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

Expr: Expr MINUS Expr {


        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Minus_Type;
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    | Expr PLUS Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Plus_Type;
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    | Expr MUL Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Mul_Type;  
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    | Expr DIV Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Div_Type;  
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    |  MINUS Expr %prec UMINUS {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Neg_Type;
        expr->right_side = $2;
        $$ = expr;
    }
    | Expr LE Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Le_Type;  
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    | Expr GE Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Ge_Type;  
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    | Expr GT Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Gt_Type;  
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    | Expr LT Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Lt_Type;  
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    | Expr EQ Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Eq_Type;  
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    | Expr NE Expr {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Ne_Type;  
        expr->left_side=$1;
        expr->right_side=$3;
        $$ = expr;
    }
    |   '(' Expr ')' {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Expr_Type;  
        expr->expr = $2;
        $$ = expr;
    }
    | ID '(' ')' {

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Call_Type;  
        expr->ID = $1;
        $$ = expr;
    }
    | ID '(' Args ')' {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Call_Type;  
        expr->ID = $1;
        expr->arg = $3;
        $$ = expr;
    }|INTNUM {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = IntNum_Type;  
        expr->int_val = $1;
        $$ = expr;
    }    
    
    | FLOATNUM {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = FloatNum_Type;  
        expr->floatval = $1;
        $$ = expr;
    }
    | ID {
        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Id_Type;  
        expr->ID = $1;
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



void openFiles()
{
    assembly_file = fopen("assembly_file.txt","w");
    symbol_file = fopen("symbol_file.txt","w");
    semantic_file = fopen("semantic_file.txt","w");
}
void closeFiles()
{
    pclose(assembly_file);
    pclose(symbol_file);
    pclose(semantic_file);

}