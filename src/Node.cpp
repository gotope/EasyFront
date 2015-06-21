/*-------------------------------------------------------------------
 * Purpose:
 *         Node.cpp抽象语法树的节点信息
 * Time:
 *         2012年1月15日 23:33:19
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "Node.h"
#include "Visitor.h"
#include "Debug.h"
#include <string>

EF_NAMESPACE_BEGIN

std::string Node::file_path;

/**
 * 
 **/
Node::Node(int32_t t_row,int32_t t_col)
:row(t_row),
col(t_col)
{
    return;
}
/**
 * 
 **/
Node::~Node()
{
    return;
}
/**
 * 
 **/
void Node::visit(Visitor& visitor)
{
    return ;
}
/********************begin Stmt class scope *********
 * 
 **/
Stmt::Stmt(int32_t t_row,int32_t t_col)
:Node(t_row,t_col)
{
    return;
}
/**
 * 
 **/
Stmt::~Stmt()
{
    return;
}
/**
 * 
 **/
void Stmt::visit(Visitor& visitor)
{
    return;
}
/************begin StmtSeq class scope*************
 * description:   构造语句序列
 * parameter:     @s1 
 *                @s2
 **/
StmtSeq::StmtSeq(Stmt *t_stmt,StmtSeq *t_stmt_seq)
:Stmt(t_stmt->get_row(),t_stmt->get_col()),
stmt(t_stmt),
stmt_seq(t_stmt_seq)
{
    D("now construct stmtseq");
    return;
}
/**
 * 
 **/
StmtSeq::~StmtSeq()
{
    return;
}
/**
 * 只是简单访问
 **/
void StmtSeq::visit(Visitor& visitor)
{
    visitor.visit_stmt_seq(this);
    return;
}
/**
 * 抽象类
 **/
SmallStmt::SmallStmt(int32_t t_row,int32_t t_col)
:Stmt(t_row,t_col)
{
    return;
}
/**
 * 
 **/
SmallStmt::~SmallStmt()
{
    return;
}
/**
 * 
 **/
void SmallStmt::visit(Visitor& visitor)
{
    return;
}
/**
 * 对节点信息的构造使用第一个语句的节点信息
 **/
SimpleStmt::SimpleStmt(SmallStmt* t_small_stmt,SimpleStmt* t_small_stmt_r)
:SmallStmt(t_small_stmt->get_row(),t_small_stmt->get_col()),
small_stmt(t_small_stmt),
small_stmt_r(t_small_stmt_r)
{
    D("now construct simple_stmt");
    return;
}
/**
 * 
 **/
SimpleStmt::~SimpleStmt()
{
    return;
}
/**
 * 
 **/
void SimpleStmt::visit(Visitor& visitor)
{
    visitor.visit_simple_stmt(this);
    return;
}
/********begin DelStmt class scope********
 * description:  根据token的str构造StringObject 
 **/
DelStmt::DelStmt(Token* token)
:SmallStmt(token->row,token->col)
{
    D("now construct delstmt");
    //name = new StringObject(token->str);
    name = token->str;
    return ;
}
/**
 * 
 **/
DelStmt::~DelStmt()
{
    return;
}
/**
 * 
 **/
void DelStmt::visit(Visitor& visitor)
{
    visitor.visit_del_stmt(this);
    return;
}
/*****************begin ImportStmt class scope******
 * 
 **/
ImportStmt::ImportStmt(Token* token)
:SmallStmt(token->row,token->col)
{
    D("now construct import_stmt");
    //name = new StringObject(token->str);
    name = token->str;
    return;
}
/**
 * 
 **/
ImportStmt::~ImportStmt()
{
    return;
}
/**
 * 
 **/
void ImportStmt::visit(Visitor& visitor)
{
    visitor.visit_import_stmt(this);
    return;
}
/**
 * 
 **/
AssignBase::AssignBase(int32_t t_row,int32_t t_col)
:SmallStmt(t_row,t_col)
{
    return;
}
/**
 * 
 **/
AssignBase::~AssignBase()
{
    return;
}
/**
 * 
 **/
void AssignBase::visit(Visitor& visitor)
{
    return;
}
/**
 * 
 **/
Assign::Assign( Expr* t_expr,DerictAssign* t_assign_r )
:AssignBase(t_expr->get_row(),t_expr->get_col()),
expr(t_expr),
derict_assign(t_assign_r),
aug_assign(NULL)
{
    return;
}
/**
 * 
 */
Assign::Assign( Expr* t_expr,AugAssign* t_assign_r )
:AssignBase(t_expr->get_row(),t_expr->get_col()),
expr(t_expr),
aug_assign(t_assign_r),
derict_assign()
{
    return ;
}
/**
 * 
 **/
Assign::~Assign()
{
    return;
}
/**
 * 
 **/
void Assign::visit(Visitor& visitor)
{
    visitor.visit_assign_stmt(this);
    return ;
}
/**
 * 
 **/
DerictAssign::DerictAssign(Expr* t_expr,DerictAssign* t_exprs_r)
:AssignBase(t_expr->get_row(),t_expr->get_col()),
expr(t_expr),
exprs_r(t_exprs_r)
{
    D("now construct derictassign");
    return;
}
/**
 * 
 **/
DerictAssign::~DerictAssign()
{
    return;
}
/**
 * 
 **/
void DerictAssign::visit(Visitor& visitor)
{
    visitor.visit_derict_assign_stmt(this);

    return;
}
/**
 * 
 **/
AugAssign::AugAssign(Token* t_token,Expr* t_expr)
                     :AssignBase(t_token->row,t_token->col),
                     token_flag(t_token->id),
                     expr(t_expr)
{
    D("now construct augassign");
    return;
}
/**
 * 
 **/
AugAssign::~AugAssign()
{
    return;
}
/**
 * 
 **/
void AugAssign::visit(Visitor& visitor)
{
    visitor.visit_aug_assign_stmt(this);
    return;
}
/**
 * 
 **/
CompoundStmt::CompoundStmt(int32_t t_row,int32_t t_col)
:Stmt(t_row,t_col)
{
    return;
}
/**
 * 
 **/
CompoundStmt::~CompoundStmt()
{
    return;
}
/**
 * 
 **/
void CompoundStmt::visit(Visitor& visitor)
{
    return;
}
/**
 * 
 **/
IfStmt::IfStmt(Expr *t_expr,Suite *t_stmt,ElifStmt* t_elif,
               ElseStmt* t_else_)
               :CompoundStmt(t_expr->get_row(),t_expr->get_col()),
                expr(t_expr),
               stmt(t_stmt),
               elif(t_elif),
               else_(t_else_)
{
    D("now construct ifstmt");
    return;
}
/**
 * 
 **/
IfStmt::~IfStmt()
{
    return;
}
/**
 * 
 **/
void IfStmt::visit(Visitor& visitor)
{
    visitor.visit_if_stmt(this);
    return;
}
/**
 * 
 **/
ElifStmt::ElifStmt(Expr* t_expr,Suite* t_stmt,ElifStmt* t_elif)
:CompoundStmt(t_expr->get_row(),t_expr->get_col()),
expr(t_expr),
stmt(t_stmt),
elif(t_elif)
{
    D("now construct elifstmt");
    return;
}
/**
 * 
 **/
ElifStmt::~ElifStmt()
{
    return;
}
/**
 * 
 **/
void ElifStmt::visit(Visitor& visitor)
{
    visitor.visit_elif_stmt(this);
    return;
}
/**
 * 
 **/
ElseStmt::ElseStmt(Suite* t_stmt)
:CompoundStmt(t_stmt->get_row(),t_stmt->get_col()),
stmt(t_stmt)
{
    D("now construct elsestmt");
    return;
}
/**
 * 
 **/
ElseStmt::~ElseStmt()
{
    return;
}
/**
 * 
 **/
void ElseStmt::visit(Visitor& visitor)
{
    visitor.visit_else_stmt(this);
    return;
}
/**
 * 
 **/
WhileStmt::WhileStmt(Expr *t_expr,Suite *t_stmt,
                     ElseStmt* t_else_ /* = NULL */)
                     :CompoundStmt(t_expr->get_row(),t_expr->get_col()),
                     expr(t_expr),
                     stmt(t_stmt),
                     else_(t_else_)
{
    D("now construct whilestmt");
    return;
}
/**
 * 
 **/
WhileStmt::~WhileStmt()
{
    return;
}
/**
 * 
 **/
void WhileStmt::visit(Visitor& visitor)
{
    visitor.visit_while_stmt(this);
    return;
}
/**
 * 
 **/
ForStmt::ForStmt(Expr* t_expr_con,Expr* t_expr_range,
                 Suite* t_stmt, ElseStmt* t_else_)
                 :CompoundStmt(t_expr_con->get_row(),t_expr_con->get_col()),
                 expr_con(t_expr_con),
                 expr_range(t_expr_range),
                 stmt(t_stmt),
                 else_(t_else_)
{
    D("now construct for_stmt");
    return;
}
/**
 * 
 **/
ForStmt::~ForStmt()
{
    return;
}
/**
 * 
 **/
void ForStmt::visit(Visitor& visitor)
{
    visitor.visit_for_stmt(this);
    return;
}
/**
 * 
 **/
TryStmt::TryStmt(Suite* t_stmt_target,CatchStmt* t_stmt_catchs,
                 Suite* t_stmt_finally)
                 :CompoundStmt(t_stmt_target->get_row(),t_stmt_target->get_col()),
                 stmt_target(t_stmt_target),
                 stmt_catchs(t_stmt_catchs),
                 stmt_finally(t_stmt_finally)
{
    D("now construct try_stmt");
    return;
}
/**
 * 
 **/
TryStmt::~TryStmt()
{
    return;
}
/**
 * 
 **/
void TryStmt::visit(Visitor& visitor)
{
    visitor.visit_try_stmt(this);
    return;
}
/**
 * 
 **/
CatchStmt::CatchStmt(Expr* t_expr,Suite* t_stmt,CatchStmt* t_catchs)
:CompoundStmt(t_expr->get_row(),t_expr->get_col()),
expr(t_expr),
stmt(t_stmt),
catchs(t_catchs)
{
    D("now construct catch_stmt");
    return;
}
/**
 * 
 **/
CatchStmt::~CatchStmt()
{
    return;
}
/**
 * 
 **/
void CatchStmt::visit(Visitor& visitor)
{
    visitor.visit_catch_stmt(this);
    return;
}
/**
 * 
 **/
FunStmt::FunStmt(Token* t_token,ParametersExpr* t_para,Suite* t_stmt)
:CompoundStmt(t_token->row,t_token->col),
para(t_para),
stmt(t_stmt)
{
    D("now construct funstmt");
    //name = new StringObject(t_token->str);
    name = t_token->str;
    return;
}
/**
 * 
 **/
FunStmt::~FunStmt()
{
    return;
}
/**
 * 
 **/
void FunStmt::visit(Visitor& visitor)
{
    visitor.visit_fun_stmt(this);
    return;
}
/**
 * 
 **/
ClassStmt::ClassStmt(Token* t_token,Suite* t_stmt)
:CompoundStmt(t_token->row,t_token->col),
stmt(t_stmt)
{
    D("now construct class_stmt");
    //name = new StringObject(t_token->str);
    name = t_token->str;
    return;
}
/**
 * 
 **/
ClassStmt::~ClassStmt()
{
    return;
}
/**
 * 
 **/
void ClassStmt::visit(Visitor& visitor)
{
    visitor.visit_class_stmt(this);
    return;
}
/**
 * 
 **/
Suite::Suite( StmtSeq* t_stmts )
:Stmt(t_stmts->get_row(),t_stmts->get_col()),
stmts(t_stmts),
simple_stmt(NULL)
{
    D("now construct suite");
    return;
}
/**
 * 
 **/
Suite::Suite( SimpleStmt* t_simple_stmt )
:Stmt(t_simple_stmt->get_row(),t_simple_stmt->get_col()),
simple_stmt(t_simple_stmt),
stmts(NULL)
{
    return;
}
/**
 * 
 **/

Suite::~Suite()
{
    return;
}
/**
 * 
 **/
void Suite::visit( Visitor& visitor )
{
    visitor.visit_suite_stmt(this);
    return;
}
/***************begin Expr class scope******************
 * 
 **/
Expr::Expr(int32_t t_row,int32_t t_col)
:Node(t_row,t_col)
{
    return;
}
/**
 * 
 **/
Expr::~Expr()
{
    return;
}
/**
 * 
 **/
void Expr::visit(Visitor& visitor)
{
    return;
}
/**
 * 
 **/
ParameterExprAtom::ParameterExprAtom(int32_t t_row,int32_t t_col)
:Expr(t_row,t_col)
{
    return;
}
/**
 * 
 **/
ParameterExprAtom::~ParameterExprAtom()
{
    return;
}
/**
 * 
 **/
void ParameterExprAtom::visit( Visitor& visitor )
{
    return;
}
/**
 * 
 **/
ParametersExpr::ParametersExpr( ParameterExprAtom* t_parameter,
                               ParametersExpr* other_para )
                               :ParameterExprAtom(t_parameter->get_row(),t_parameter->get_col()),
                               parameter(t_parameter),
                               others(other_para)
{
    D("now construct ParameterExpr");
    return;
}
/**
 * 
 **/
ParametersExpr::~ParametersExpr()
{
    return;
}
/**
 * 
 **/
void ParametersExpr::visit( Visitor& visitor )
{
    visitor.visit_parameters_expr(this);
    return;
}

/**
 * 
 **/
NostarParameterExpr::NostarParameterExpr(AtomExpr* t_atom,Expr* t_expr )
:ParameterExprAtom(t_atom->get_row(),t_atom->get_col()),
atom(t_atom),
expr(t_expr)
{
    D("now construct NostarParameterExpr");
    //name = new StringObject(t_token->str);
    return;
}
/**
 * 
 **/
NostarParameterExpr::~NostarParameterExpr()
{
    return;
}
/**
 * 
 **/
void NostarParameterExpr::visit( Visitor& visitor )
{
    visitor.visit_no_star_parameter_expr(this);
    return;
}
/**
 * 
 **/
TupleParameterExpr::TupleParameterExpr( Token* t_token,Expr* t_expr )
:ParameterExprAtom(t_token->row,t_token->col),
expr(t_expr)
{
    D("now construct TupleParameterExpr");
    //name = new StringObject(t_token->str);
    name = t_token->str;
    return;
}
/**
 * 
 **/
TupleParameterExpr::~TupleParameterExpr()
{
    return;
}
/**
 * 
 **/
void TupleParameterExpr::visit( Visitor& visitor )
{
    visitor.visit_tuple_parameter_expr(this);
    return;
}
/**
 * 
 **/
MapParameterExpr::MapParameterExpr( Token* t_token,Expr* t_expr )
:ParameterExprAtom(t_token->row,t_token->col),
expr(t_expr)
{
    D("now construct MapParameterExpr");
    //name = new StringObject(t_token->str);
    name = t_token->str;
    return;
}
/**
 * 
 **/
MapParameterExpr::~MapParameterExpr()
{
    return;
}
/**
 * 
 **/
void MapParameterExpr::visit( Visitor& visitor )
{
    visitor.visit_map_parameter_expr(this);
    return;
}
/**
 * 
 **/
ConExpr::ConExpr(int32_t t_row,int32_t t_col)
:Expr(t_row,t_col)
{
    return;
}
/**
 * 
 **/
ConExpr::~ConExpr()
{
    return;
}
/**
 * 
 **/
void ConExpr::visit( Visitor& visitor )
{
    return;
}
/**
 * 
 **/
LambdaExpr::LambdaExpr( ParametersExpr* t_paramters,ConExpr* t_expr )
:ConExpr(t_paramters->get_row(),t_paramters->get_col()),
parameters(t_paramters),
expr(t_expr)
{
    D("now construct lambdaExpr");
    return;
}
/**
 * 
 **/
LambdaExpr::~LambdaExpr()
{
    return;
}
/**
 * 
 **/
void LambdaExpr::visit( Visitor& visitor )
{
    visitor.visit_lambda_expr(this);
    return;
}
/**
 * 
 **/
LogicalExpr::LogicalExpr(int32_t t_row,int32_t t_col)
:ConExpr(t_row,t_col)
{
    return;
}
/**
 * 
 **/
LogicalExpr::~LogicalExpr()
{
    return;
}
/**
 * 
 **/
void LogicalExpr::visit( Visitor& visitor )
{
    return;
}
/**
 * 
 **/
LogicalOrExpr::LogicalOrExpr( LogicalAndExpr* t_and_expr,
                             LogicalOrExpr* t_or_expr_r )
                             :LogicalExpr(t_and_expr->get_row(),t_and_expr->get_col()),
                             and_expr(t_and_expr),
                             or_expr_r(t_or_expr_r)
{
    D("now construct logical_or_expr");
    return;
}
/**
 * 
 **/
LogicalOrExpr::~LogicalOrExpr()
{
    return;
}
/**
 * 
 **/
void LogicalOrExpr::visit( Visitor& visitor )
{
    visitor.visit_logical_or_expr(this);
    return;
}
/**
 * 
 **/
LogicalAndExpr::LogicalAndExpr( LogicalNotExpr* t_not_expr,
                               LogicalAndExpr* t_and_expr_r )
                               :LogicalExpr(t_not_expr->get_row(),t_not_expr->get_col()),
                               not_expr(t_not_expr),
                               and_expr_r(t_and_expr_r)
{
    D("now construct logical_and_expr");
    return;
}
/**
 * 
 **/
LogicalAndExpr::~LogicalAndExpr()
{
    return;
}
/**
 * 
 **/
void LogicalAndExpr::visit( Visitor& visitor )
{
    visitor.visit_logical_and_expr(this);
    return;
}
/**
 * 
 **/
LogicalNotExpr::LogicalNotExpr( LogicalRelExpr* t_rel )
:LogicalExpr(t_rel->get_row(),t_rel->get_col()),
rel(t_rel),
not_expr(NULL)
{
    D("now construct logical_not_expr");
    return;
}
/**
 * 
 **/
LogicalNotExpr::LogicalNotExpr( LogicalNotExpr* t_not_expr )
:LogicalExpr(t_not_expr->get_row(),t_not_expr->get_col()),
not_expr(t_not_expr),
rel(NULL)
{
    return;
}
/**
 * 
 **/
LogicalNotExpr::~LogicalNotExpr()
{
    return;
}
/**
 * 
 **/
void LogicalNotExpr::visit( Visitor& visitor )
{
    visitor.visit_logical_not_expr(this);
    return;
}
/**
 * 
 **/
LogicalRelExpr::LogicalRelExpr( SmallExpr* t_small_expr1,
                               LogicalRelExprR* t_rel_r )
                               :LogicalExpr(t_small_expr1->get_row(),
                               t_small_expr1->get_col()),
                               small_expr1(t_small_expr1),
                               rel_r(t_rel_r)
{
    D("now construct logical_rel_expr");
    return;
}
/**
 * 
 **/
LogicalRelExpr::~LogicalRelExpr()
{
    return;
}
/**
 * 
 **/
void LogicalRelExpr::visit( Visitor& visitor )
{
    visitor.visit_logical_rel_expr(this);
    return;
}
/**
 * 
 **/
LogicalRelExprR::LogicalRelExprR( Token* t_token,
                                 SmallExpr* t_small_expr,
                                 LogicalRelExprR* t_rel_r )
                                 :LogicalExpr(t_token->row,t_token->col),
                                 small_expr1(t_small_expr),
                                 rel_r(t_rel_r)
{
    D("now construct logical_rel_expr_r");
    token_flag = t_token->id;
    return;
}
/**
 * 
 **/
LogicalRelExprR::~LogicalRelExprR()
{
    return;
}
/**
 * 
 **/
void LogicalRelExprR::visit( Visitor& visitor )
{
    visitor.visit_logical_rel_expr_r(this);
    return;
}
/**
 * 
 **/
SmallExpr::SmallExpr(int32_t t_row,int32_t t_col)
:Expr(t_row,t_col)
{
    return;
}
/**
 * 
 **/
SmallExpr::~SmallExpr()
{
    return;
}
/**
 * 
 **/
void SmallExpr::visit( Visitor& visitor )
{
    return;
}
/**
 * description:    
 * parameter:    @t_xor_expr第一个节点
 *                @t_or_expr_r第二个节点
 * return:        
 **/
OrExpr::OrExpr(XorExpr* t_xor_expr,OrExpr* t_or_expr_r)
:SmallExpr(t_xor_expr->get_row(),t_xor_expr->get_col()),
xor_expr(t_xor_expr),
or_expr_r(t_or_expr_r)
{
    D("now construct or_expr");
    return;
}
/**
 * 
 **/
OrExpr::~OrExpr()
{
    return;
}
/**
 * 
 **/
void OrExpr::visit(Visitor& visitor)
{
    visitor.visit_or_expr(this);
    return;
}
/**
 * 
 **/
XorExpr::XorExpr( AndExpr* t_and_expr,XorExpr* t_xor_expr_r )
:SmallExpr(t_and_expr->get_row(),t_and_expr->get_col()),
and_expr(t_and_expr),
xor_expr_r(t_xor_expr_r)
{
    D("now construct xor_expr");
    return;
}
/**
 * 
 **/
XorExpr::~XorExpr()
{
    return;
}
/**
 * 
 **/
void XorExpr::visit( Visitor& visitor )
{
    visitor.visit_xor_expr(this);
    return;
}
/**
 * 
 **/
AndExpr::AndExpr( ShiftExpr* t_shift_expr,AndExpr* t_and_expr_r )
:SmallExpr(t_shift_expr->get_row(),t_shift_expr->get_col()),
shift_expr(t_shift_expr),
and_expr_r(t_and_expr_r)
{
    D("now construct and_expr");
    return;
}
/**
 * 
 **/
AndExpr::~AndExpr()
{
    return;
}
/**
 * 
 **/
void AndExpr::visit( Visitor& visitor )
{
    visitor.visit_and_expr(this);
    return;
}
/**
 * 
 **/
ShiftExpr::ShiftExpr( ArithExpr* t_arith_expr,
                     ShiftExprR* t_shift_expr_r )
                     :SmallExpr(t_arith_expr->get_row(),t_arith_expr->get_col()),
                     arith_expr(t_arith_expr),
                     shift_expr_r(t_shift_expr_r)
{
    D("now construct shift_expr");
    return;
}
/**
 * 
 **/
ShiftExpr::~ShiftExpr()
{
    return;
}
/**
 * 
 **/
void ShiftExpr::visit( Visitor& visitor )
{
    visitor.visit_shift_expr(this);
    return;
}
/**
 * 
 **/
ShiftExprR::ShiftExprR( Token* t_token,
                       ArithExpr* t_arith_expr,
                       ShiftExprR* t_shift_expr_r )
                       :SmallExpr(t_token->row,t_token->col),
                       arith_expr(t_arith_expr),
                       shift_expr_r(t_shift_expr_r)
{
    D("now construct shift_expr_r");
    token_flag = t_token->id;
    return;
}
/**
 * 
 **/
ShiftExprR::~ShiftExprR()
{
    return;
}
/**
 * 
 **/
void ShiftExprR::visit( Visitor& visitor )
{
    visitor.visit_shift_expr_r(this);
    return;
}
/**
 * 
 **/
ArithExpr::ArithExpr( TermExpr* t_term,ArithExprR* t_arith_expr_r )
:SmallExpr(t_term->get_row(),t_term->get_col()),
term(t_term),
arith_expr_r(t_arith_expr_r)
{
    D("now construct arith_expr");
    return;
}
/**
 * 
 **/
ArithExpr::~ArithExpr()
{
    return;
}
/**
 * 
 **/
void ArithExpr::visit( Visitor& visitor )
{
    visitor.visit_arith_expr(this);
    return;
}
/**
 * 
 **/
ArithExprR::ArithExprR( Token* t_token,TermExpr* t_term,
                       ArithExprR* t_arith_expr_r )
                       :SmallExpr(t_token->row,t_token->col),
                       term(t_term),
                       arith_expr_r(t_arith_expr_r)
{
    D("now construct arith_expr_r");
    token_flag = t_token->id;
    return;
}
/**
 * 
 **/
ArithExprR::~ArithExprR()
{
    return;
}
/**
 * 
 **/
void ArithExprR::visit( Visitor& visitor )
{
    visitor.visit_arith_expr_r(this);
    return;
}
/**
 * 
 **/
TermExpr::TermExpr( FactorExpr* t_factor,TermExprR* t_term_r )
:SmallExpr(t_factor->get_row(),t_factor->get_col()),
factor(t_factor),
term_r(t_term_r)
{
    D("now construct term_expr");
    return;
}
/**
 * 
 **/
TermExpr::~TermExpr()
{
    return;
}
/**
 * 
 **/
void TermExpr::visit( Visitor& visitor )
{
    visitor.visit_term_expr(this);
    return;
}
/**
 * 
 **/
TermExprR::TermExprR( Token* t_token,FactorExpr* t_factor,
                     TermExprR* t_term_r )
                     :SmallExpr(t_token->row,t_token->col),
                     factor(t_factor),
                     term_r(t_term_r)
{
    D("now construct term_expr_r");
    token_flag = t_token->id;
    return;
}
/**
 * 
 **/
TermExprR::~TermExprR()
{
    return;
}
/**
 * 
 **/
void TermExprR::visit( Visitor& visitor )
{
    visitor.visit_term_expr_r(this);
    return;
}
/**
 * 
 **/
FactorExpr::FactorExpr( Token* t_token,FactorExpr* t_factor )
:SmallExpr(t_token->row,t_token->col),
power(NULL),
factor(t_factor)
{
    D("now construct factor");
    token_flag = t_token->id;
    return;
}
/**
 * 
 **/
FactorExpr::FactorExpr(PowerExpr* t_power )
:SmallExpr(t_power->get_row(),t_power->get_col()),
power(t_power),
factor(NULL)
{
    D("now construct factor");
    token_flag = EMPTY;
    return;
}
/**
 * 
 **/
FactorExpr::~FactorExpr()
{
    return;
}
/**
 * 
 **/
void FactorExpr::visit( Visitor& visitor )
{
    visitor.visit_factor_expr(this);
    return;
}
/**
 * 
 **/
PowerExpr::PowerExpr( AtomExpr* t_atom,
                     FactorExpr* t_factor /*= NULL*/ )
                     :SmallExpr(t_atom->get_row(),t_atom->get_col()),
                     atom(t_atom),
                     factor(t_factor)
{
    D("now construct power_expr");
    return;
}
/**
 * 
 **/
PowerExpr::~PowerExpr()
{
    return;
}
/**
 * 
 **/
void PowerExpr::visit( Visitor& visitor )
{
    visitor.visit_power_expr(this);
    return;
}
/**
 * 
 **/
AtomExpr::AtomExpr(int32_t t_row,int32_t t_col)
:SmallExpr(t_row,t_col)
{
    return;
}
/**
 * 
 **/
AtomExpr::~AtomExpr()
{
    return;
}
/**
 * 
 **/
void AtomExpr::visit( Visitor& visitor )
{
    return;
}
/**
 * 
 **/
TupleExpr::TupleExpr( TupleVariableExpr* t_variable )
:AtomExpr(t_variable->get_row(),t_variable->get_col()),
variable(t_variable)
{
    D("now construct tupleexpr");
    return;
}
/**
 * 
 **/
TupleExpr::~TupleExpr()
{
    return;
}
/**
 * 
 **/
void TupleExpr::visit( Visitor& visitor )
{
    visitor.visit_tuple_expr(this);
    return;
}
/**
 * 
 **/
MapExpr::MapExpr( MapVariableExpr* t_variable )
:AtomExpr(t_variable->get_row(),t_variable->get_col()),
variable(t_variable)
{
    D("now construct mapExpr");
    return;
}
/**
 * 
 **/
MapExpr::~MapExpr()
{
    return;
}
/**
 * 
 **/
void MapExpr::visit( Visitor& visitor )
{
    visitor.visit_map_expr(this);
    return;
}
/**
 * 
 **/
VariablesExpr::VariablesExpr(int32_t t_row,int32_t t_col)
:Expr(t_row,t_col)
{
    D("now construct variable_expr");
    return;
}
/**
 * 
 **/
VariablesExpr::~VariablesExpr()
{
    return;
}
/**
 * 
 **/
void VariablesExpr::visit( Visitor& visitor )
{
    return;
}
/**
 * 
 **/
TupleVariableExpr::TupleVariableExpr( Expr* t_expr,
                                     TupleVariableExpr* t_variable_r )
                                     :VariablesExpr(t_expr->get_row(),t_expr->get_col()),
                                     expr(t_expr),
                                     variable_r(t_variable_r)
{
    D("now construct tuple_variable_expr");
    return;
}
/**
 * 
 **/
TupleVariableExpr::~TupleVariableExpr()
{
    return;
}
/**
 * 
 **/
void TupleVariableExpr::visit( Visitor& visitor )
{
    visitor.visit_tuple_variable_expr(this);
    return;
}
/**
 * 
 **/
MapVariableExpr::MapVariableExpr( Expr* t_expr_l,
                                 Expr* t_expr_r, 
                                 MapVariableExpr* t_variable_r )
                                 :VariablesExpr(t_expr_l->get_row(),t_expr_l->get_col()),
                                 expr_l(t_expr_l),
                                 expr_r(t_expr_r),
                                 variable_r(t_variable_r)
{
    D("now construct map_variable_expr");
    return;
}
/**
 * 
 **/
MapVariableExpr::~MapVariableExpr()
{
    return;
}
/**
 * 
 **/
void MapVariableExpr::visit( Visitor& visitor )
{
    visitor.visit_map_variable_expr(this);
    return;
}
/**
 * 
 **/
NumberExpr::NumberExpr( Token *t_token )
:AtomExpr(t_token->row,t_token->col)
{
    D("now construct number_expr");

    bool b_double = is_float(t_token->str);
    if (b_double == true)
    {
        double num = atof(t_token->str.c_str());
        float_value = new FloatObject(num);
        int_value = NULL;
    }
    else
    {
        int32_t num = atol(t_token->str.c_str());
        int_value = new LongObject(num);
        float_value = NULL;
    }
    return;
}
/**
 * 
 **/
NumberExpr::~NumberExpr()
{
    return;
}
/**
 * 
 **/
void NumberExpr::visit( Visitor& visitor )
{
    visitor.visit_number_expr(this);
    return;
}
/**
 * 
 **/
StringExpr::StringExpr( Token *t_token,StringExpr* t_string_other )
:AtomExpr(t_token->row,t_token->col),
string_other(t_string_other)
{
    D("now construct string_expr");
    //value = new StringObject(t_token->str);
    value = t_token->str;
    return;
}
/**
 * 
 **/
StringExpr::~StringExpr()
{
    return;
}
/**
 * 
 **/
void StringExpr::visit( Visitor& visitor )
{
    visitor.visit_string_expr(this);
    return;
}
/**
 * 
 **/
KeyWordExpr::KeyWordExpr( Token *t_token )
:AtomExpr(t_token->row,t_token->col)
{
    D("now construct keyword_expr");
    value = new LongObject(t_token->str);
    if (t_token->id == NULL_MARKER)
    {
        value = new LongObject(0);
    }
    else if (t_token->id == TRUE_MARKER)
    {
        value = new LongObject(1);
    }
    else if (t_token->id == FALSE_MARKER)
    {
        value = new LongObject(0);
    }
    else
    {
        value = NULL;
    }
    return;
}
/**
 * 
 **/
KeyWordExpr::~KeyWordExpr()
{
    return;
}
/**
 * 
 **/
void KeyWordExpr::visit( Visitor& visitor )
{
    visitor.visit_keyword_expr(this);
    return;
}
/**
 * 
 **/
NameExpr::NameExpr( Token* t_token,AtomExpr* t_name_expr_r )
:AtomExpr(t_token->row,t_token->col),
name_expr_r(t_name_expr_r)
{
    D("now construct name_expr");
    //name = new StringObject(t_token->str);
    name = t_token->str;
    return;
}
/**
 * 
 **/
NameExpr::~NameExpr()
{
    return;
}
/**
 * 
 **/
void NameExpr::visit( Visitor& visitor )
{
    visitor.visit_name_expr(this);
    return;
}
/**
 * 
 **/
FunInvokeExpr::FunInvokeExpr( ParametersExpr* t_paras )
:AtomExpr(t_paras->get_row(),t_paras->get_col()),
paras(t_paras)
{
    D("now construct fun_invoke_expr");
    //name = new StringObject(t_token->str);
    return;
}
/**
 *  为无参函数预留的构造函数
 */
FunInvokeExpr::FunInvokeExpr( int32_t row,int32_t col )
:AtomExpr(row,col)
{
    paras = NULL;
    return;
}
/**
 * 
 **/
FunInvokeExpr::~FunInvokeExpr()
{
    return;
}
/**
 * 
 **/
void FunInvokeExpr::visit( Visitor& visitor )
{
    visitor.visit_fun_invoke_expr(this);
    return;
}
/**
 * 
 **/
ModuleInvokeExpr::ModuleInvokeExpr( Token* t_token,
                                   ModuleInvokeExpr* t_module_invoke_r )
                                   :AtomExpr(t_token->row,t_token->col),
                                   module_invoke_r(t_module_invoke_r)
{
    D("now construct module_invoke_expr");
    //name = new StringObject(t_token->str);
    name = t_token->str;
    return;
}
/**
 * 
 **/
ModuleInvokeExpr::~ModuleInvokeExpr()
{
    return;
}
/**
 * 
 **/
void ModuleInvokeExpr::visit( Visitor& visitor )
{
    visitor.visit_module_invoke_expr(this);
    return;
}

EF_NAMESPACE_END
