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

    Program := (DeclList)? (FuncList)?   // DeclList FuncList | DeclList | FuncList | ε
    DeclList := (Declaration)+          // Declaration | DeclList Declaration
    FuncList := (Function)+
    Declaration := Type IdentList ;
    IdentList := identifier (, identifier)*  // identifier | IdentList , identifier
    identifier := id | id [ intnum ]      // (Note) [, ] are not symbols used in regular expression
    Function := Type id ( (ParamList)? ) CompoundStmt
    ParamList := Type identifier (, Type identifier)*
    Type := int | float
    CompoundStmt := { (DeclList)? StmtList }
    StmtList := (Stmt)*
    Stmt := AssignStmt | CallStmt | RetStmt | WhileStmt | ForStmt | IfStmt | CompoundStmt | ;
    AssignStmt :=Assign ; 
    Assign := id = Expr | id [ Expr ] = Expr
    CallStmt := Call ;
    Call := id ( (ArgList)? )
    RetStmt := return (Expr)? ; 
    
    So, Our miniC program doesn't follow the rule below.
        1. ++, --
        
   
