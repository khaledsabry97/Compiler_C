%error-verbose

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Abstract_Tree.h"
#include "print.h"
static int line_counter;

FILE *assembly_file; 
FILE *symbol_file; 
FILE *semantic_file;
static int line_counter;
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


%nonassoc NO_ELSE
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
       }
       ;
Declarations:  Type ID ';' {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = $2;
            struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
            declaration->id_type = $1;
            declaration->id = identifier;
            $$ = declaration;
        }
        | Declarations  Type ID ';' {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = $3;
            struct DECLARATION *declaration = (struct DECLARATION*) malloc (sizeof (struct DECLARATION));
            declaration->prev = $1;
            declaration->id_type = $2;
            declaration->id = identifier;
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
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = $2;

            struct PARAMETER *parameter = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            parameter->id_type = $1;
            parameter->id = identifier;
            parameter->prev = NULL;
            $$ = parameter;
        }
         | Parameters ',' Type ID {
            struct IDENTIFIER *identifier = (struct IDENTIFIER*) malloc (sizeof (struct IDENTIFIER));
            identifier->ID = $4;

            struct PARAMETER *parameter = (struct PARAMETER*) malloc (sizeof (struct PARAMETER));
            parameter->id_type = $3;
            parameter->id = identifier;
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
            stmt->stmt.assign_stmt = assign;

            $$ = stmt;
    } | RETURN ';' {
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
        
    | '{' Declarations Stmt_List '}' {
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
            |'{' Declarations '}' {
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
    | ID PP {
        //INTNUM = 1;
        struct ID_EXPR *id_expr = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_expr->ID = $1;

        struct EXPR *expr2 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr2->expr_type = Id_Type;  
        expr2->expression.id_expr = id_expr;

        struct EXPR *expr1 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr1->expr_type = IntNum_Type;
        expr1->expression.int_val = 1;

        struct ADD_OP *add_op = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        add_op->add_type = Plus_Type;
        add_op->left_side=expr2;
        add_op->right_side= expr1;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = add_op;

        struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
        assign->ID = $1;
        assign->expr = expr;
             
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Equ_Type;
        stmt->stmt.assign_stmt = assign;
        printf("sfsdfsdfsdF%d\n",line_counter);

        $$ = stmt;
    }| ID MM {
        //INTNUM = 1;
        struct ID_EXPR *id_expr = (struct ID_EXPR*)malloc(sizeof (struct ID_EXPR));
        id_expr->ID = $1;

        struct EXPR *expr2 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr2->expr_type = Id_Type;  
        expr2->expression.id_expr = id_expr;

        struct EXPR *expr1 = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr1->expr_type = IntNum_Type;
        expr1->expression.int_val = 1;

        struct ADD_OP *add_op = (struct ADD_OP*) malloc (sizeof (struct ADD_OP));
        add_op->add_type = Minus_Type;
        add_op->left_side=expr2;
        add_op->right_side= expr1;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Add_Type;
        expr->expression.add_op = add_op;

        struct ASSIGN_STMT *assign = (struct ASSIGN_STMT*) malloc (sizeof (struct ASSIGN_STMT));
        assign->ID = $1;
        assign->expr = expr;
             
        struct STMT *stmt = (struct STMT*) malloc (sizeof (struct STMT));
        stmt->stmt_type = Equ_Type;
        stmt->stmt.assign_stmt = assign;
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
           
                
            }| error '}' {printf("forgot to open statemtent group\n");yyerrok;}
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
    |  MINUS Expr %prec UMINUS {
        struct UNI_OP *uni_op = (struct UNI_OP*) malloc (sizeof (struct UNI_OP));
        uni_op->uni_type = Neg_Type;
        uni_op->expr = $2;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Uni_Type;
        expr->expression.uni_op = uni_op;
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
    |   '(' Expr ')' {
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
    | ID '(' Args ')' {
        struct FUNC_CALL *call = (struct FUNC_CALL*) malloc (sizeof (struct FUNC_CALL));
        call->ID = $1;
        call->arg = $3;

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = CallExpr_Type;  
        expr->expression.func_call = call;
        $$ = expr;
    }|INTNUM {
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

        struct EXPR *expr = (struct EXPR*) malloc (sizeof (struct EXPR));
        expr->expr_type = Id_Type;  
        expr->expression.id_expr = id_expr;
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

/*
void process(struct PROGRAM* head) {
    
    if(head == NULL)
        exit(1);
    head_scope_ptr = newBlock(Block_Global_Type, NULL);
    current_block_ptr = head_scope_ptr;
    if(head->declaration != NULL)
        compileDeclaration(head->declaration);
    if(head->function != NULL)
        compileFunction(head->function);
            compileProgram(head);
}
*/


void openFiles()
{
    assembly_file = fopen("assembly_file.txt","w");
    symbol_file = fopen("symbol_file.txt","w");
    semantic_file = fopen("semantic_file.txt","w");
}
void closeFiles()
{
    //fprintf(assembly_file, "\n");
    pclose(assembly_file);
    pclose(symbol_file);
    pclose(semantic_file);

}