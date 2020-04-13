miniC (using flex&bison)
========
This project is compiler project using flex and bison.

## 1. Building
    make
    
    or

    flex miniC.l
    bison -d miniC.y
    gcc -o miniC miniC.tab.c print.c symboltable.c lex.yy.c -g -lfl
    
## 2. How to run
    miniC < input.txt

## 3. Results
    Abstract Syntax Tree (AST): tree.txt
    Symbol table: table.txt

## 4. We follow the rule below.

    Program := (Declaration_List)? (Function_List)?   // Declaration_List Function_List | Declaration_List | Function_List | ε
    Declaration_List := (Declaration)+          // Declaration | Declaration_List Declaration
    Function_List := (Function)+
    Declaration := Type Identifier_List ;
    Identifier_List := identifier (, identifier)*  // identifier | Identifier_List , identifier
    identifier := id | id [ intnum ]      // (Note) [, ] are not symbols used in regular expression
    Function := Type id ( (Parameter_List)? ) Stmt_Group
    Parameter_List := Type identifier (, Type identifier)*
    Type := int | float
    Stmt_Group := { (Declaration_List)? Stmt_List }
    Stmt_List := (Stmt)*
    Stmt := Assign_Stmt | Call_Stmt | Ret_Stmt | WhileStmt | For_Stmt | IfStmt | Stmt_Group | ;
    Assign_Stmt :=Assign ; 
    Assign := id = Expr | id [ Expr ] = Expr
    Call_Stmt := Call ;
    Call := id ( (Arg_List)? )
    Ret_Stmt := return (Expr)? ; 
    
    So, Our miniC program doesn't follow the rule below.
        1. ++, --
        
   
