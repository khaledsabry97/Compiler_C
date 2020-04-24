#ifndef enums
#define enums
/******************************************************Abstract Tree Types*********************************************************/

typedef enum {Int_Type,Float_Type,Const_Int_Type,Const_Float_Type} ID_TYPE;

typedef enum {Equ_Type,If_Type,For_Type,While_Type,Return_Type,Declaration_Type,Stmt_Group_Type,Semi_Colon_Type} STMT_TYPE;

typedef enum {Neg_Type} UNI_OP_TYPE;
typedef enum {Plus_Type,Minus_Type} ADD_TYPE;
typedef enum {Mul_Type,Div_Type} MUL_TYPE;
typedef enum {Eq_Type,Ne_Type} EQCOM_TYPE;
typedef enum {Lt_Type,Gt_Type,Le_Type,Ge_Type} COMP_TYPE;
typedef enum {Uni_Type,Add_Type,Mult_Type,Com_Type,Eql_Type,CallExpr_Type,IntNum_Type,FloatNum_Type,Id_Type,Expr_Type} EXPR_TYPE;

/******************************************************Block Types*********************************************************/
typedef enum { Block_Global_Type, Block_Stmt_Group_Type, Block_Func_Type, Block_If_Type, Block_For_Type, Block_Do_While_Type, Block_While_Type} BLOCK_TYPE;

#endif