miniC (using flex&bison)
========
This project is compiler project using flex and bison.

## 1. Building
    make
    
    or

    flex miniC.l
    bison -d miniC.y
    gcc -o miniC miniC.tab.c print.cpp symboltable.c lex.yy.c -g -lfl
    
## 2. How to run
    miniC < input.txt

## 3. Results
    Abstract Syntax Tree (AST): tree.txt
    Symbol table: table.txt

## 4. We follow the rule below.

    Program := (Declarations)? (Functions)?   // Declarations Functions | Declarations | Functions | ε
    Declarations := (Declaration)+          // Declaration | Declarations Declaration
    Functions := (Function)+
    Declaration := Type Identifier_List ;
    Identifier_List := identifier (, identifier)*  // identifier | Identifier_List , identifier
    identifier := id | id [ intnum ]      // (Note) [, ] are not symbols used in regular expression
    Function := Type id ( (Parameters)? ) Stmt_Group
    Parameters := Type identifier (, Type identifier)*
    Type := int | float
    Stmt_Group := { (Declarations)? Stmt_List }
    Stmt_List := (Stmt)*
    Stmt := Assign_Stmt | Call_Stmt | Ret_Stmt | WhileStmt | For_Stmt | IfStmt | Stmt_Group | ;
    Assign_Stmt :=Assign ; 
    Assign := id = Expr | id [ Expr ] = Expr
    Call_Stmt := Call ;
    Call := id ( (Args)? )
    Ret_Stmt := return (Expr)? ; 
    
    So, Our miniC program doesn't follow the rule below.
        1. ++, --
        
   
