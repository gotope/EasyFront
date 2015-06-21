/*-------------------------------------------------------------------
 * Purpose:
 *         Visitor.h
 *          ����һ��������ģʽ,���Ǻ�����ͨ���������չһ���µ�IR��ʾ����
 * Time:
 *         2012��2��5�� 15:46:56
 * Author:
 *         ������
--------------------------------------------------------------------*/

#ifndef _LISEVISITOR_2012_2_5_lisency
#define _LISEVISITOR_2012_2_5_lisency

#include "Base.h"
#include "Node.h"
#include "CodeBuilder.h"

#include <ostream>

EF_NAMESPACE_BEGIN

/**
 * �ṩ�������󣬼��ӿ�
 **/
class Visitor
    :public Base
{
public:
    /**
    **/
    virtual ~Visitor() = 0;
    /**
	* 
    **/
    virtual void visit_stmt_seq(StmtSeq* context);
    /**
	* 
    **/
    virtual void visit_simple_stmt(SimpleStmt* context);
    /**
	* 
    **/
    virtual void visit_del_stmt(DelStmt* context);
    /**
	* 
    **/
    virtual void visit_import_stmt(ImportStmt* context);
    /**
	* 
    **/
    virtual void visit_assign_stmt(Assign* context);
    /**
	* 
    **/
    virtual void visit_derict_assign_stmt(DerictAssign* context);
    /**
	* 
    **/
    virtual void visit_aug_assign_stmt(AugAssign* context);
    /**
	* 
    **/
    virtual void visit_if_stmt(IfStmt* context);
    /**
	* 
    **/
    virtual void visit_elif_stmt(ElifStmt* context);
    /**
	* 
    **/
    virtual void visit_else_stmt(ElseStmt* context);
    /**
	* 
    **/
    virtual void visit_while_stmt(WhileStmt* context);
    /**
	* 
    **/
    virtual void visit_for_stmt(ForStmt* context);
    /**
	* 
    **/
    virtual void visit_try_stmt(TryStmt* context);
    /**
	* 
    **/
    virtual void visit_catch_stmt(CatchStmt* context);
    /**
	* 
    **/
    virtual void visit_fun_stmt(FunStmt* context);
    /**
	* 
    **/
    virtual void visit_class_stmt(ClassStmt* context);
    /**
	* 
    **/
    virtual void visit_suite_stmt(Suite* context);
    /**
	* 
    **/
    virtual void visit_parameters_expr(ParametersExpr* context);
    /**
	* 
    **/
    virtual void visit_no_star_parameter_expr(NostarParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_parameter_expr(TupleParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_map_parameter_expr(MapParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_lambda_expr(LambdaExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_or_expr(LogicalOrExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_and_expr(LogicalAndExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_not_expr(LogicalNotExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr(LogicalRelExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr_r(LogicalRelExprR* context);
    /**
    * ���ʻ�ڵ�
    * ��Щ�ڵ㲻һ���Ǵ���ģ����������Բ�ʵ����
    * һ���汾
    **/
    virtual void visit_or_expr(OrExpr* context);
    /**
	* 
    **/
    virtual void visit_xor_expr(XorExpr* context);
    /**
	* 
    **/
    virtual void visit_and_expr(AndExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr(ShiftExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr_r(ShiftExprR* context);
    /**
	* 
    **/
    virtual void visit_arith_expr(ArithExpr* context);
    /**
	* 
    **/
    virtual void visit_arith_expr_r(ArithExprR* context);
    /**
	* 
    **/
    virtual void visit_term_expr(TermExpr* context);
    /**
	* 
    **/
    virtual void visit_term_expr_r(TermExprR* context);
    /**
	* 
    **/
    virtual void visit_factor_expr(FactorExpr* context);
    /**
	* 
    **/
    virtual void visit_power_expr(PowerExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_expr(TupleExpr* context);
    /**
	* 
    **/
    virtual void visit_map_expr(MapExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_variable_expr(TupleVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_map_variable_expr(MapVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_number_expr(NumberExpr* context);
    /**
	* 
    **/
    virtual void visit_string_expr(StringExpr* context);
    /**
	* 
    **/
    virtual void visit_keyword_expr(KeyWordExpr* context);
    /**
	* 
    **/
    virtual void visit_name_expr(NameExpr* context);
    /**
	* 
    **/
    virtual void visit_fun_invoke_expr(FunInvokeExpr* context);
    /**
	* 
    **/
    virtual void visit_module_invoke_expr(ModuleInvokeExpr* context);
protected:
    /**
    * constructor
    **/
    Visitor();
private:
};
/**
 * �ֽ���������
 **/
class ByteCodeGen
    :public Visitor
{
public:
    /**
    * 
    **/
    ByteCodeGen(CodeBuilder& t_code_builder);
    /**
    * 
    **/
    virtual ~ByteCodeGen();
    /**
	* 
    **/
    virtual void visit_stmt_seq(StmtSeq* context);
    /**
	* 
    **/
    virtual void visit_simple_stmt(SimpleStmt* context);
    /**
	* 
    **/
    virtual void visit_del_stmt(DelStmt* context);
    /**
	* 
    **/
    virtual void visit_import_stmt(ImportStmt* context);
    /**
	* 
    **/
    virtual void visit_assign_stmt(Assign* context);
    /**
	* 
    **/
    virtual void visit_derict_assign_stmt(DerictAssign* context);
    /**
	* 
    **/
    virtual void visit_aug_assign_stmt(AugAssign* context);
    /**
	* 
    **/
    virtual void visit_if_stmt(IfStmt* context);
    /**
	* 
    **/
    virtual void visit_elif_stmt(ElifStmt* context);
    /**
	* 
    **/
    virtual void visit_else_stmt(ElseStmt* context);
    /**
	* 
    **/
    virtual void visit_while_stmt(WhileStmt* context);
    /**
	* 
    **/
    virtual void visit_for_stmt(ForStmt* context);
    /**
	* 
    **/
    virtual void visit_try_stmt(TryStmt* context);
    /**
	* 
    **/
    virtual void visit_catch_stmt(CatchStmt* context);
    /**
	* 
    **/
    virtual void visit_fun_stmt(FunStmt* context);
    /**
	* 
    **/
    virtual void visit_class_stmt(ClassStmt* context);
    /**
	* 
    **/
    virtual void visit_suite_stmt(Suite* context);
    /**
	* 
    **/
    virtual void visit_parameters_expr(ParametersExpr* context);
    /**
	* 
    **/
    virtual void visit_no_star_parameter_expr(NostarParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_parameter_expr(TupleParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_map_parameter_expr(MapParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_lambda_expr(LambdaExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_or_expr(LogicalOrExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_and_expr(LogicalAndExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_not_expr(LogicalNotExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr(LogicalRelExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr_r(LogicalRelExprR* context);
    /**
    * ���ʻ�ڵ�
    * ��Щ�ڵ㲻һ���Ǵ���ģ����������Բ�ʵ����
    * һ���汾
    **/
    virtual void visit_or_expr(OrExpr* context);
    /**
    * ���ڵ�
    **/
    virtual void visit_xor_expr(XorExpr* context);
    /**
	* 
    **/
    virtual void visit_and_expr(AndExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr(ShiftExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr_r(ShiftExprR* context);
    /**
	* 
    **/
    virtual void visit_arith_expr(ArithExpr* context);
    /**
	* 
    **/
    virtual void visit_arith_expr_r(ArithExprR* context);
    /**
	* 
    **/
    virtual void visit_term_expr(TermExpr* context);
    /**
	* 
    **/
    virtual void visit_term_expr_r(TermExprR* context);
    /**
	* 
    **/
    virtual void visit_factor_expr(FactorExpr* context);
    /**
	* 
    **/
    virtual void visit_power_expr(PowerExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_expr(TupleExpr* context);
    /**
	* 
    **/
    virtual void visit_map_expr(MapExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_variable_expr(TupleVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_map_variable_expr(MapVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_number_expr(NumberExpr* context);
    /**
	* 
    **/
    virtual void visit_string_expr(StringExpr* context);
    /**
	* 
    **/
    virtual void visit_keyword_expr(KeyWordExpr* context);
    /**
	* 
    **/
    virtual void visit_name_expr(NameExpr* context);
    /**
	* 
    **/
    virtual void visit_fun_invoke_expr(FunInvokeExpr* context);
    /**
	* 
    **/
    virtual void visit_module_invoke_expr(ModuleInvokeExpr* context);
protected:
    CodeBuilder& code_builder;
private:

};
/**
 * description:    ���ű�������
 **/
class SymTableGen
    :public Visitor
{
public:
    /**
	* 
    **/
    SymTableGen(std::string& t_file_path);
    /**
	* 
    **/
    ~SymTableGen();
    /**
	* 
    **/
    virtual void visit_stmt_seq(StmtSeq* context);
    /**
	* 
    **/
    virtual void visit_simple_stmt(SimpleStmt* context);
    /**
	* 
    **/
    virtual void visit_del_stmt(DelStmt* context);
    /**
	* 
    **/
    virtual void visit_import_stmt(ImportStmt* context);
    /**
	* 
    **/
    virtual void visit_assign_stmt(Assign* context);
    /**
	* 
    **/
    virtual void visit_derict_assign_stmt(DerictAssign* context);
    /**
	* 
    **/
    virtual void visit_aug_assign_stmt(AugAssign* context);
    /**
	* 
    **/
    virtual void visit_if_stmt(IfStmt* context);
    /**
	* 
    **/
    virtual void visit_elif_stmt(ElifStmt* context);
    /**
	* 
    **/
    virtual void visit_else_stmt(ElseStmt* context);
    /**
	* 
    **/
    virtual void visit_while_stmt(WhileStmt* context);
    /**
	* 
    **/
    virtual void visit_for_stmt(ForStmt* context);
    /**
	* 
    **/
    virtual void visit_try_stmt(TryStmt* context);
    /**
	* 
    **/
    virtual void visit_catch_stmt(CatchStmt* context);
    /**
	* 
    **/
    virtual void visit_fun_stmt(FunStmt* context);
    /**
	* 
    **/
    virtual void visit_class_stmt(ClassStmt* context);
    /**
	* 
    **/
    virtual void visit_suite_stmt(Suite* context);
    /**
	* 
    **/
    virtual void visit_parameters_expr(ParametersExpr* context);
    /**
	* 
    **/
    virtual void visit_no_star_parameter_expr(NostarParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_parameter_expr(TupleParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_map_parameter_expr(MapParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_lambda_expr(LambdaExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_or_expr(LogicalOrExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_and_expr(LogicalAndExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_not_expr(LogicalNotExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr(LogicalRelExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr_r(LogicalRelExprR* context);
    /**
    * ���ʻ�ڵ�
    * ��Щ�ڵ㲻һ���Ǵ���ģ����������Բ�ʵ����
    * һ���汾
    **/
    virtual void visit_or_expr(OrExpr* context);
    /**
    * ���ڵ�
    **/
    virtual void visit_xor_expr(XorExpr* context);
    /**
	* 
    **/
    virtual void visit_and_expr(AndExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr(ShiftExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr_r(ShiftExprR* context);
    /**
	* 
    **/
    virtual void visit_arith_expr(ArithExpr* context);
    /**
	* 
    **/
    virtual void visit_arith_expr_r(ArithExprR* context);
    /**
	* 
    **/
    virtual void visit_term_expr(TermExpr* context);
    /**
	* 
    **/
    virtual void visit_term_expr_r(TermExprR* context);
    /**
	* 
    **/
    virtual void visit_factor_expr(FactorExpr* context);
    /**
	* 
    **/
    virtual void visit_power_expr(PowerExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_expr(TupleExpr* context);
    /**
	* 
    **/
    virtual void visit_map_expr(MapExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_variable_expr(TupleVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_map_variable_expr(MapVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_number_expr(NumberExpr* context);
    /**
	* 
    **/
    virtual void visit_string_expr(StringExpr* context);
    /**
	* 
    **/
    virtual void visit_keyword_expr(KeyWordExpr* context);
    /**
	* 
    **/
    virtual void visit_name_expr(NameExpr* context);
    /**
	* 
    **/
    virtual void visit_fun_invoke_expr(FunInvokeExpr* context);
    /**
	* 
    **/
    virtual void visit_module_invoke_expr(ModuleInvokeExpr* context);
    /**
    * description:    ͨ���ݹ�ķ�ʽ����AST��ÿ���ڵ�֮������
    *                 �ķ��ű�ͨ���˺�������
    * parameters:     
    * return:         ���ع���ķ��ű�
    **/
    SymbolTable* get_sym_table();
protected:
    SymbolTable* sym_table;
private:
};
#ifdef EF_DEBUG
/**
 * �ڵ��Ե�ʱ����ɴ�ӡ����
 */
class NodePrintor
    :public Visitor
{
public:
	/**
     *
     */
    NodePrintor(std::ostream& out);
    /**
     *
     */
    ~NodePrintor();
    /**
	* 
    **/
    virtual void visit_stmt_seq(StmtSeq* context);
    /**
	* 
    **/
    virtual void visit_simple_stmt(SimpleStmt* context);
    /**
	* 
    **/
    virtual void visit_del_stmt(DelStmt* context);
    /**
	* 
    **/
    virtual void visit_import_stmt(ImportStmt* context);
    /**
	* 
    **/
    virtual void visit_assign_stmt(Assign* context);
    /**
	* 
    **/
    virtual void visit_derict_assign_stmt(DerictAssign* context);
    /**
	* 
    **/
    virtual void visit_aug_assign_stmt(AugAssign* context);
    /**
	* 
    **/
    virtual void visit_if_stmt(IfStmt* context);
    /**
	* 
    **/
    virtual void visit_elif_stmt(ElifStmt* context);
    /**
	* 
    **/
    virtual void visit_else_stmt(ElseStmt* context);
    /**
	* 
    **/
    virtual void visit_while_stmt(WhileStmt* context);
    /**
	* 
    **/
    virtual void visit_for_stmt(ForStmt* context);
    /**
	* 
    **/
    virtual void visit_try_stmt(TryStmt* context);
    /**
	* 
    **/
    virtual void visit_catch_stmt(CatchStmt* context);
    /**
	* 
    **/
    virtual void visit_fun_stmt(FunStmt* context);
    /**
	* 
    **/
    virtual void visit_class_stmt(ClassStmt* context);
    /**
	* 
    **/
    virtual void visit_suite_stmt(Suite* context);
    /**
	* 
    **/
    virtual void visit_parameters_expr(ParametersExpr* context);
    /**
	* 
    **/
    virtual void visit_no_star_parameter_expr(NostarParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_parameter_expr(TupleParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_map_parameter_expr(MapParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_lambda_expr(LambdaExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_or_expr(LogicalOrExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_and_expr(LogicalAndExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_not_expr(LogicalNotExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr(LogicalRelExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr_r(LogicalRelExprR* context);
    /**
    * ���ʻ�ڵ�
    * ��Щ�ڵ㲻һ���Ǵ���ģ����������Բ�ʵ����
    * һ���汾
    **/
    virtual void visit_or_expr(OrExpr* context);
    /**
    * ���ڵ�
    **/
    virtual void visit_xor_expr(XorExpr* context);
    /**
	* 
    **/
    virtual void visit_and_expr(AndExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr(ShiftExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr_r(ShiftExprR* context);
    /**
	* 
    **/
    virtual void visit_arith_expr(ArithExpr* context);
    /**
	* 
    **/
    virtual void visit_arith_expr_r(ArithExprR* context);
    /**
	* 
    **/
    virtual void visit_term_expr(TermExpr* context);
    /**
	* 
    **/
    virtual void visit_term_expr_r(TermExprR* context);
    /**
	* 
    **/
    virtual void visit_factor_expr(FactorExpr* context);
    /**
	* 
    **/
    virtual void visit_power_expr(PowerExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_expr(TupleExpr* context);
    /**
	* 
    **/
    virtual void visit_map_expr(MapExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_variable_expr(TupleVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_map_variable_expr(MapVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_number_expr(NumberExpr* context);
    /**
	* 
    **/
    virtual void visit_string_expr(StringExpr* context);
    /**
	* 
    **/
    virtual void visit_keyword_expr(KeyWordExpr* context);
    /**
	* 
    **/
    virtual void visit_name_expr(NameExpr* context);
    /**
	* 
    **/
    virtual void visit_fun_invoke_expr(FunInvokeExpr* context);
    /**
	* 
    **/
    virtual void visit_module_invoke_expr(ModuleInvokeExpr* context);
protected:
    std::ostream& cout;
private:
};
#endif //EF_DEBUG
class NodeReleasor
    :public Visitor
{
public:
	/**
     *
     */
    NodeReleasor();
    /**
     *
     */
    ~NodeReleasor();
    /**
	* 
    **/
    virtual void visit_stmt_seq(StmtSeq* context);
    /**
	* 
    **/
    virtual void visit_simple_stmt(SimpleStmt* context);
    /**
	* 
    **/
    virtual void visit_del_stmt(DelStmt* context);
    /**
	* 
    **/
    virtual void visit_import_stmt(ImportStmt* context);
    /**
	* 
    **/
    virtual void visit_assign_stmt(Assign* context);
    /**
	* 
    **/
    virtual void visit_derict_assign_stmt(DerictAssign* context);
    /**
	* 
    **/
    virtual void visit_aug_assign_stmt(AugAssign* context);
    /**
	* 
    **/
    virtual void visit_if_stmt(IfStmt* context);
    /**
	* 
    **/
    virtual void visit_elif_stmt(ElifStmt* context);
    /**
	* 
    **/
    virtual void visit_else_stmt(ElseStmt* context);
    /**
	* 
    **/
    virtual void visit_while_stmt(WhileStmt* context);
    /**
	* 
    **/
    virtual void visit_for_stmt(ForStmt* context);
    /**
	* 
    **/
    virtual void visit_try_stmt(TryStmt* context);
    /**
	* 
    **/
    virtual void visit_catch_stmt(CatchStmt* context);
    /**
	* 
    **/
    virtual void visit_fun_stmt(FunStmt* context);
    /**
	* 
    **/
    virtual void visit_class_stmt(ClassStmt* context);
    /**
	* 
    **/
    virtual void visit_suite_stmt(Suite* context);
    /**
	* 
    **/
    virtual void visit_parameters_expr(ParametersExpr* context);
    /**
	* 
    **/
    virtual void visit_no_star_parameter_expr(NostarParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_parameter_expr(TupleParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_map_parameter_expr(MapParameterExpr* context);
    /**
	* 
    **/
    virtual void visit_lambda_expr(LambdaExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_or_expr(LogicalOrExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_and_expr(LogicalAndExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_not_expr(LogicalNotExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr(LogicalRelExpr* context);
    /**
	* 
    **/
    virtual void visit_logical_rel_expr_r(LogicalRelExprR* context);
    /**
    * ���ʻ�ڵ�
    * ��Щ�ڵ㲻һ���Ǵ���ģ����������Բ�ʵ����
    * һ���汾
    **/
    virtual void visit_or_expr(OrExpr* context);
    /**
    * ���ڵ�
    **/
    virtual void visit_xor_expr(XorExpr* context);
    /**
	* 
    **/
    virtual void visit_and_expr(AndExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr(ShiftExpr* context);
    /**
	* 
    **/
    virtual void visit_shift_expr_r(ShiftExprR* context);
    /**
	* 
    **/
    virtual void visit_arith_expr(ArithExpr* context);
    /**
	* 
    **/
    virtual void visit_arith_expr_r(ArithExprR* context);
    /**
	* 
    **/
    virtual void visit_term_expr(TermExpr* context);
    /**
	* 
    **/
    virtual void visit_term_expr_r(TermExprR* context);
    /**
	* 
    **/
    virtual void visit_factor_expr(FactorExpr* context);
    /**
	* 
    **/
    virtual void visit_power_expr(PowerExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_expr(TupleExpr* context);
    /**
	* 
    **/
    virtual void visit_map_expr(MapExpr* context);
    /**
	* 
    **/
    virtual void visit_tuple_variable_expr(TupleVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_map_variable_expr(MapVariableExpr* context);
    /**
	* 
    **/
    virtual void visit_number_expr(NumberExpr* context);
    /**
	* 
    **/
    virtual void visit_string_expr(StringExpr* context);
    /**
	* 
    **/
    virtual void visit_keyword_expr(KeyWordExpr* context);
    /**
	* 
    **/
    virtual void visit_name_expr(NameExpr* context);
    /**
	* 
    **/
    virtual void visit_fun_invoke_expr(FunInvokeExpr* context);
    /**
	* 
    **/
    virtual void visit_module_invoke_expr(ModuleInvokeExpr* context);
protected:
private:
};
EF_NAMESPACE_END

#endif //_LISEVISITOR_2012_2_5_lisency

