/*-------------------------------------------------------------------
 * Purpose:
 *         Visitor.cpp
 * Time:
 *         2012年2月5日 15:49:37
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "Visitor.h"
#include "Exception.h"
#include "Debug.h"
#include <assert.h>


EF_NAMESPACE_BEGIN

#define THROW_ERROR(error_id) EFExc exc(context->get_file_path(),\
                    context->get_row(),context->get_col(),error_id);\
                    throw exc;
/**
 * 
 **/
Visitor::Visitor()
{
    return;
}
/**
 * 
 **/
Visitor::~Visitor()
{
    return;
}
/**
 * 
 **/
void Visitor::visit_stmt_seq( StmtSeq* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_simple_stmt( SimpleStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_del_stmt( DelStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_import_stmt( ImportStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_assign_stmt( Assign* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_derict_assign_stmt( DerictAssign* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_aug_assign_stmt( AugAssign* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_if_stmt( IfStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_elif_stmt( ElifStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_else_stmt( ElseStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_while_stmt( WhileStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_for_stmt( ForStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_try_stmt( TryStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_catch_stmt( CatchStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_fun_stmt( FunStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_class_stmt( ClassStmt* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_suite_stmt( Suite* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_parameters_expr( ParametersExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_no_star_parameter_expr( NostarParameterExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_tuple_parameter_expr( TupleParameterExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_map_parameter_expr( MapParameterExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_lambda_expr( LambdaExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_logical_or_expr( LogicalOrExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_logical_and_expr( LogicalAndExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_logical_not_expr( LogicalNotExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_logical_rel_expr( LogicalRelExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_logical_rel_expr_r( LogicalRelExprR* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_or_expr( OrExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_xor_expr( XorExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_and_expr( AndExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_shift_expr( ShiftExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_shift_expr_r( ShiftExprR* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_arith_expr( ArithExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_arith_expr_r( ArithExprR* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_term_expr( TermExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_term_expr_r( TermExprR* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_factor_expr( FactorExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_power_expr( PowerExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_tuple_expr( TupleExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_map_expr( MapExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_tuple_variable_expr( TupleVariableExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_map_variable_expr( MapVariableExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_number_expr( NumberExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_string_expr( StringExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_keyword_expr( KeyWordExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_name_expr( NameExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_fun_invoke_expr( FunInvokeExpr* context )
{
    return;
}
/**
 * 
 **/
void Visitor::visit_module_invoke_expr( ModuleInvokeExpr* context )
{
    return;
}
/******let's begin bytecode generate*************
 * 
 **/
ByteCodeGen::ByteCodeGen( CodeBuilder& t_code_builder )
:code_builder(t_code_builder)
{
    return;
}
/**
 * 
 **/
ByteCodeGen::~ByteCodeGen()
{
    return;
}
/**
 * 依次遍历每个语句节点
 **/
void ByteCodeGen::visit_stmt_seq( StmtSeq* context )
{
    Stmt* t_stmt = context->get_stmt();
    StmtSeq* stmt_seq = context->get_stmt_seq();

    assert(t_stmt != NULL);
    //前序遍历
    t_stmt->visit(*this);

    if (stmt_seq != NULL)
    {
        stmt_seq->visit(*this);
    }
    return;
}
/**
 * 简单语句的变量，不会引发作用域的问题
 **/
void ByteCodeGen::visit_simple_stmt( SimpleStmt* context )
{
    SmallStmt* small_stmt = context->get_small_stmt();
    SimpleStmt* small_stmt_r = context->get_small_stmt_r();

    assert(small_stmt != NULL);

    small_stmt->visit(*this);

    if (small_stmt_r != NULL)
    {
        small_stmt_r->visit(*this);
    }
    return;
}
/**
 * 删除语句的遍历
 **/
void ByteCodeGen::visit_del_stmt( DelStmt* context )
{
    std::string name = context->get_name();

    assert(name.empty() != true);

    //code_builder.addop_name(LOAD_NAME,name);  //不需要这一句
    //调用delete指令将name从符号表中删除
    code_builder.addop_name(DELETE_NAME,name);
    std::string message("DELETE_NAME:");
    message += name;
    D(message);
    return;
}
/**
 * 遍历import节点的时候要将import的name信息存入指令表中
 **/
void ByteCodeGen::visit_import_stmt( ImportStmt* context )
{
    std::string name = context->get_name();
    assert(name.empty() != true);

    code_builder.addop_name(IMPORT_NAME,name);
    //将name的文件引导进来并编译它，然后将该值村给name，也就是说name此时
    //持有的是字节码对象
    code_builder.addop_name(STORE_NAME,name);
    std::string message("IMPORT_NAME:");
    message += name;
    D(message);
    message.clear();
    message = ("STORE_NAME:");
    message += name;
    D(message);
    return;
}
/**
 * 这里对两种赋值采用不同的遍历方式
 **/
void ByteCodeGen::visit_assign_stmt( Assign* context )
{
    Expr* t_expr = context->get_expr();

    DerictAssign* derict_assign = context->get_derict_assign();
    AugAssign* aug_assign = context->get_aug_assign();

    assert(t_expr != NULL);
    //assert(assign_r != NULL);

    if (derict_assign != NULL)
    {
        //对单一赋值使用后序遍历
        derict_assign->visit(*this);
        //应该存储expr,存储的指令在遍历expr时，当遇到name被存储
        code_builder.set_context_ty(Store);
        t_expr->visit(*this);
        code_builder.set_context_ty(Empty);
    }
    else if (aug_assign != NULL)
    {
        //对于复合赋值使用前序遍历
        code_builder.set_context_ty(Load);
        t_expr->visit(*this);
        code_builder.set_context_ty(Empty);
        //应该load expr,复合赋值的指令在visit assign_r的时候被生成
        aug_assign->visit(*this);

        //再存储一次
        code_builder.set_context_ty(Store);
        t_expr->visit(*this);
        code_builder.set_context_ty(Empty);
    }
    else
    {
        code_builder.set_context_ty(Load);
        t_expr->visit(*this);
        code_builder.set_context_ty(Empty);
    }
    return;
}
/**
 * 遍历单一赋值语句
 **/
void ByteCodeGen::visit_derict_assign_stmt( DerictAssign* context )
{
    Expr* t_expr = context->get_expr();
    DerictAssign* exprs_r = context->get_exprs_r();

    assert(t_expr != NULL);
    
    //这里是递归调用，其实用循环会更好些
    if (exprs_r == NULL)
    {
        code_builder.set_context_ty(Load);
        //如果最右端的是数字则然，若是一个name，那么需要load
        t_expr->visit(*this);
        code_builder.set_context_ty(Empty);
        //用完之后重新置回去
        return;
    }
    //后序深度优先遍历每个DerictAssign的节点

    exprs_r->visit(*this);
    //将左节点遍历完成，并添加字节码
    //将该值复制一份保存在栈顶
    code_builder.addop(DUP_TOP);

    std::string message("DUP_TOP");
    D(message);

    code_builder.set_context_ty(Store);
    t_expr->visit(*this);    //储存新值
    code_builder.set_context_ty(Empty);
    //等递归调用完成之后，内存中还保留一份，留给Assign类
    return;
}
/**
 * 复合赋值使用前序遍历
 **/
void ByteCodeGen::visit_aug_assign_stmt( AugAssign* context )
{
    Expr* t_expr = context->get_expr();
    TokenFlag token_flag = context->get_token_flag();

    assert(t_expr != NULL);

    t_expr->visit(*this);
    Op opcode = code_builder.inplace_binop(token_flag);
    code_builder.addop(opcode);
    
    std::string message("AUG_ASSIGN");
    D(message);
    return;
}
/**
 * if语句
 * if语句要endblock支持，这是应该注意的一个地方
 **/
void ByteCodeGen::visit_if_stmt( IfStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElifStmt* elif = context->get_elif_stmt();
    ElseStmt* else_ = context->get_else_stmt();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);
    //分为四种情况：
    //t_stmt != null,elif == NULL,else_ == NULL
    //t_stmt != NULL,elif != NULL,else_ == NULL
    //t_stmt != NULL,elif != NULL,else_ != NULL
    //t_stmt != NULL,elif == NULL,else_ != NULL

    code_builder.enter_scope(context);  //进入一层牢房

    Basicblock *end, *next,*self;
    next =code_builder.new_block();
    self = code_builder.new_block();
    //结束位置在elif语句
    if (elif != NULL || else_ != NULL)
    {
        end = code_builder.new_block();
    }
    else
    {
        end = next;
    }

    code_builder.set_next_block(next);
    code_builder.set_endblock(end);
    code_builder.set_self_block(self);

    t_expr->visit(*this);    //访问表达式节点


    //确保在访问t_expr的时候没有添加最后一条跳转指令
    code_builder.addop_j_abs(POP_JUMP_IF_FALSE,next);
    std::string message("POP_JUMP_IF_FALSE");
    D(message);

    code_builder.use_next_block(self);

    //stmt语句不可以为空 
    if (t_stmt == NULL)
    {
        THROW_ERROR(ERROR_STMT_EMPTY);
    }
    t_stmt->visit(*this);    //访问stmt节点
    code_builder.addop_j_rel(JUMP_FORWARD,end);

    message = "JUMP_FORWARD";
    D(message);
    //if语句结束后直接跳转到最后

    //访问elif语句
    if (elif != NULL)
    {
        code_builder.use_next_block(next);
        //code_builder.next_block();
        //end块被elif使用
        code_builder.set_endblock(end);
        elif->visit(*this);
        //code_builder.addop_j(JUMP_FORWARD,end,0);
        //这一句在访问elif语句时候已经添加了，所以不再需要添加
        if (else_ != NULL)
        {
            next = code_builder.get_next_block();
            code_builder.use_next_block(next);
            //code_builder.next_block();
            //创建一个块，并使用它，即被else语句使用
            //code_builder.set_endblock(end);//直接执行完else紧接就是下一block
            else_->visit(*this);
        }
        code_builder.use_next_block(end);
        //code_builder.next_block();
        code_builder.set_endblock(NULL);    //为了确保

        return;
    }
    //到此说明elif为空,访问else语句
    if (else_ != NULL)
    {
        code_builder.use_next_block(next);
        //code_builder.set_endblock(end);//直接执行完else紧接就是下一block
        else_->visit(*this);
    }
    
    //将block的指针指向end
    code_builder.use_next_block(end);
    return;
}
/**
 * 对elif语句进行遍历
 **/
void ByteCodeGen::visit_elif_stmt( ElifStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElifStmt* elif = context->get_elif();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);
    
    code_builder.enter_scope(context);  //再进一层牢房

    //该expr使用的是在if语句中北设置过的一个快
    code_builder.set_context_ty(Load);

    Basicblock* next,*end,*self;
    self = code_builder.new_block();

    end = code_builder.get_endblock();
    //该end是由if语句传递下来的
    assert(end != NULL);

    //if (elif == NULL)
    //{
        //next = end;
    //}
    //else
    //{
        next = code_builder.new_block();
    //}
    code_builder.set_self_block(self);
    code_builder.set_next_block(next);

    t_expr->visit(*this);

    code_builder.addop_j_rel(POP_JUMP_IF_FALSE,next);

    std::string message("POP_JUMP_IF_FALSE");
    D(message);

    code_builder.use_next_block(self);
    t_stmt->visit(*this);
    code_builder.addop_j_abs(JUMP_FORWARD,end);

     message = "JUMP_FORWARD";
    D(message);

    //前序遍历访问所有的elif节点
    while (elif != NULL)
    {
        code_builder.use_next_block(next);

        t_expr = elif->get_expr();
        t_stmt = elif->get_suite();
        code_builder.enter_scope(elif);  //再进一层牢房

        elif = elif->get_elif();
        assert(t_expr != NULL);
        next = code_builder.new_block();
        self = code_builder.new_block();

        if (next == NULL)
        {
            THROW_ERROR(ERROR_NO_MEMORY);
        }

        code_builder.set_next_block(next);
        code_builder.set_self_block(self);

        t_expr->visit(*this);
        code_builder.addop_j_rel(POP_JUMP_IF_FALSE,next);

        message = "POP_JUMP_IF_FALSE";
        D(message);

        assert(t_stmt != NULL);

        code_builder.use_next_block(self);
        t_stmt->visit(*this);
        code_builder.addop_j_abs(JUMP_FORWARD,end);

        message = "JUMP_FORWARD";
        D(message);

    }
    code_builder.set_next_block(next);
    return;
}
/**
 * else statement
 **/
void ByteCodeGen::visit_else_stmt( ElseStmt* context )
{
    Suite* t_stmt = context->get_suite();

    assert(t_stmt != NULL);

    code_builder.enter_scope(context);  //换个牢房住住
    t_stmt->visit(*this);
    //code_builder.addop_i();直接进入下一块，不需要跳转
    return;
}
/**
 * while statement
 **/
void ByteCodeGen::visit_while_stmt( WhileStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElseStmt* else_ = context->get_else_stmt();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    code_builder.enter_scope(context);  //进入while牢房
    Basicblock *loop, *orelse, *end;

    loop = code_builder.new_block();    //循环体
    //loop = code_builder.get_cur_blocks();   
    //我们做一点优化，直接使用上级留下的block做循环体
    end = code_builder.new_block();     //结尾

    //注意：在这里舍弃了在dodebuilder初始化时的那一个block
    if (loop == NULL || end == NULL)
    {
        THROW_ERROR(ERROR_NO_MEMORY);
    }
    if (else_ != NULL)
    {
        orelse = code_builder.new_block();
        if (orelse == NULL)
        {
            THROW_ERROR(ERROR_NO_MEMORY);
        }
    }
    else
    {
        orelse = end;
    }

    //code_builder.addop_j_rel(SETUP_LOOP,end);

    //std::string message = "SETUP_LOOP";
    //D(message);
    //code_builder.use_next_block(loop);

    code_builder.set_next_block(end);
    code_builder.set_self_block(loop);

    code_builder.use_next_block(loop);
    code_builder.set_context_ty(Load);
    t_expr->visit(*this);
    code_builder.set_context_ty(Empty);
    code_builder.addop_j_abs(POP_JUMP_IF_FALSE,orelse);

    std::string message = "POP_JUMP_IF_FALSE";
    D(message);

    //表达式与stmt之间没有block之隔，它们是一体的，所以这里不在newblock
    t_stmt->visit(*this);
    code_builder.addop_j_abs(JUMP_ABSOLUTE,loop);

    message = "JUMP_ABSOLUTE";
    D(message);

    //无条件跳转到loop，重新做判断，重新循环

    //如果有else语句的话将else语句加在其后面
    if (else_ != NULL)
    {
        code_builder.use_next_block(orelse);
        else_->visit(*this);
        //else完了之后不做跳转，直接进入下一块
    }
    
    code_builder.use_next_block(end);

    return;
}
/**
 * for statement
 **/
void ByteCodeGen::visit_for_stmt( ForStmt* context )
{
    Expr* expr_con = context->get_expr_con();
    Expr* expr_range = context->get_expr_range();
    Suite* t_stmt = context->get_suite();
    ElseStmt* else_ = context->get_else_stmt();

    assert(expr_con != NULL);
    assert(expr_range != NULL);
    assert(t_stmt != NULL);

    code_builder.enter_scope(context);  //进入for枷锁
    Basicblock *start, *cleanup, *end;

    start = code_builder.new_block();
    end = code_builder.new_block();

    if (else_ != NULL)
    {
        cleanup = code_builder.new_block();
    }
    else
    {
        cleanup = end;
    }
    
    if (start == NULL || end == NULL || cleanup == NULL)
    {
        return ;
    }
    //遍历顺序，先遍历range再遍历条件，再stmt，再else
    code_builder.addop_j_rel(SETUP_LOOP,cleanup);

    std::string message = "SETUP_LOOP";
    D(message);

    //在这里expr range使用的是从上级传递下来的block，到expr_con时才使用新的
    //上下文环境设置成读取
    code_builder.set_context_ty(Load);
    expr_range->visit(*this);
    code_builder.set_context_ty(Empty);
    code_builder.addop(GET_ITER);

    message = "GET_ITER";
    D(message);
    //得到迭代器

    code_builder.use_next_block(start);
    code_builder.addop_j_rel(FOR_ITER,cleanup);

    message = "FOR_ITER";
    D(message);

    //上下文环境设置成存
    code_builder.set_context_ty(Store);
    expr_con->visit(*this);
    code_builder.set_context_ty(Empty);

    t_stmt->visit(*this);
    code_builder.addop_j_abs(JUMP_ABSOLUTE,start);

    message = "JUMP_ABSOLUTE";
    D(message);
    //调转到开始重新判断
    //到else语句，
    code_builder.use_next_block(cleanup);

    if (else_ != NULL)
    {
        else_->visit(*this);
    }
    
    //如果else语句为空，这一句其实是重复的
    code_builder.use_next_block(end);
    return;
}
/**
 * try catch
 **/
void ByteCodeGen::visit_try_stmt( TryStmt* context )
{
    Suite* stmt_target = context->get_target();
    CatchStmt* stmt_catchs = context->get_catchs();
    Suite* stmt_finally = context->get_finally();

    assert(stmt_target != NULL);
    assert(stmt_catchs != NULL);

    code_builder.enter_scope(context);
    //进入try作用域
    return;
}
/**
 * catch部分
 **/
void ByteCodeGen::visit_catch_stmt( CatchStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    CatchStmt* catchs = context->get_catchs();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    code_builder.enter_scope(context);
    //进入catch作用域
    return;
}
/**
 * 函数定义
 **/
void ByteCodeGen::visit_fun_stmt( FunStmt* context )
{
    std::string name = context->get_name();
    ParametersExpr* para = context->get_para();
    Suite* stmt = context->get_suite();

    assert(name.empty() != true);

    //参数可以为空，所以不做判断
    assert(stmt != NULL);

    code_builder.enter_scope(context);
    //进入function
    SymbolTable* cur_symbol_table = code_builder.get_symtable();
    CodeBuilder fun_code_builder(cur_symbol_table);
    ByteCodeGen fun_code_gen(fun_code_builder);

    fun_code_builder.set_context_ty(Param);
    para->visit(fun_code_gen);  //添加参数
    fun_code_builder.set_context_ty(Empty);

    fun_code_builder.set_context_ty(Load);
    stmt->visit(fun_code_gen);
    //如果这里将返回值一并添加上就好了
    fun_code_builder.set_context_ty(Empty);

    fun_code_builder.back_pach();
    CodeObject* op_code = fun_code_builder.get_code();

    op_code->print(debug_stream);
    code_builder.make_function(name,op_code);
    code_builder.out_scope();
    return ;
}
/**
 * 类定义
 **/
void ByteCodeGen::visit_class_stmt( ClassStmt* context )
{
    std::string name = context->get_name();
    Suite* stmt = context->get_suite();

    assert(name.empty() != true);
    assert(stmt != NULL);

    code_builder.enter_scope(context);
    //进入class作用域

    //类定义应该新生成一个CodeObject
    return;
}
/**
 * 一件套装，只需简单遍历即可
 **/
void ByteCodeGen::visit_suite_stmt( Suite* context )
{
    StmtSeq* stmts = context->get_stmts();
    SimpleStmt* simple_stmt = context->get_simple_stmt();

    assert(stmts != NULL || simple_stmt != NULL);

    if (simple_stmt != NULL)
    {
        simple_stmt->visit(*this);
    }
    else if (stmts != NULL)
    {
        stmts->visit(*this);
    }
    code_builder.out_scope();
    //suite完了之后退出作用域
    return;
}
/**
 * 遍历参数
 **/
void ByteCodeGen::visit_parameters_expr( ParametersExpr* context )
{
    ParameterExprAtom* parameter = context->get_parameter();
    ParametersExpr* other = context->get_other_para();

    assert(parameter != NULL);
    //code_builder.set_context_ty(Param);
    parameter->visit(*this);
    //code_builder.set_context_ty(Empty);

    while (other != NULL)
    {
        parameter = other->get_parameter();
        assert(parameter != NULL);
        parameter->visit(*this);
        other = other->get_other_para();

    }
    return;
}
/**
 * 通用参数
 **/
void ByteCodeGen::visit_no_star_parameter_expr( NostarParameterExpr* context )
{
    //std::string name = context->get_name();
    AtomExpr* atom = context->get_atom();
    Expr* t_expr = context->get_expr();

    assert(atom != NULL);

    atom->visit(*this);
    //t_expr为默认值，暂时不需要
    return;
}
/**
 * 元组参数
 **/
void ByteCodeGen::visit_tuple_parameter_expr( TupleParameterExpr* context )
{
    std::string name = context->get_name();
    Expr* t_expr = context->get_expr();

    assert(name.empty() != true);
    return;
}
/**
 **/
void ByteCodeGen::visit_map_parameter_expr( MapParameterExpr* context )
{
    std::string name = context->get_name();
    Expr* t_expr = context->get_expr();

    assert(name.empty() != true);
    return;
}
/**
 * lambda表达式需要进入一个新的作用域，要做的工作很多，
 * 先放着
 **/
void ByteCodeGen::visit_lambda_expr( LambdaExpr* context )
{
    ParametersExpr* parameters = context->get_parameters();
    ConExpr* t_expr = context->get_expr();

    //参数可以为空
    assert(t_expr != NULL);

    if (parameters != NULL)
    {
        parameters->visit(*this);
    }
    t_expr->visit(*this);
    return;
}
/**
 * 逻辑或
 * 逻辑或处在表达式节点的最高层......
 **/
void ByteCodeGen::visit_logical_or_expr( LogicalOrExpr* context )
{
    LogicalAndExpr* and_expr = context->get_and_expr();
    LogicalOrExpr* or_expr_r = context->get_or_expr_r();

    assert(and_expr != NULL);

    and_expr->visit(*this);

    if (or_expr_r == NULL)
    {
        return;
    }

    Basicblock* abs_next = code_builder.get_self_block();
    //这是Or语句的出口

    if (abs_next == NULL)
    {
        THROW_ERROR(ERROR_NO_MEMORY);
    }
    //或表达式需要前序遍历，只要发现前面的一个为真，全为真
    //先遍历左孩子
    code_builder.addop_j_abs(POP_JUMP_IF_TRUE,abs_next);

    std::string message = "POP_JUMP_IF_TRUE";
    D(message);
    //如果为真，直接跳转到最后

    LogicalOrExpr* child_or_expr = or_expr_r->get_or_expr_r();
    //对倒数第一个不添加字节码
    //遍历它的所有右孩子节点(右孩子的孩子)
    while (child_or_expr != NULL)
    {
        and_expr = or_expr_r->get_and_expr();
        assert(and_expr != NULL);

        and_expr->visit(*this);
        //对每个子节点的左孩子进行遍历

        //在这里不需要新的block
        code_builder.addop_j_abs(POP_JUMP_IF_TRUE,abs_next);

        message = "POP_JUMP_IF_TRUE";
        D(message);
        or_expr_r = child_or_expr;

        child_or_expr = or_expr_r->get_or_expr_r();
    }
    and_expr = or_expr_r->get_and_expr();
    assert(and_expr != NULL);
    and_expr->visit(*this);

    //最后一个是不生成绝对跳转地址的

    //code_builder.set_next_block(end);
    //code_builder.use_next_block(end);
    return;
}
/**
 * 逻辑与表达式
 **/
void ByteCodeGen::visit_logical_and_expr( LogicalAndExpr* context )
{
    LogicalNotExpr* not_expr = context->get_not_expr();
    LogicalAndExpr* and_expr = context->get_and_expr_r();

    assert(not_expr != NULL);

    not_expr->visit(*this);

    if (and_expr == NULL)
    {
        return;
    }

    Basicblock *abs_next;  //绝对跳转地址
    abs_next = code_builder.get_next_block();

    if (abs_next == NULL)
    {
        abs_next = code_builder.new_block();
    }
    //and与or实现完全一样，如果能合并到一块那会更好
    //只要有一处为假，就跳到做末尾
    code_builder.addop_j_abs(POP_JUMP_IF_FALSE,abs_next);
    //如果为假，直接跳转到最后

    std::string message = "POP_JUMP_IF_FALSE";
    D(message);

    LogicalAndExpr* child_and_expr = and_expr->get_and_expr_r();

    while (child_and_expr != NULL)
    {
        not_expr = and_expr->get_not_expr();
        assert(not_expr != NULL);

        not_expr->visit(*this);

        code_builder.addop_j_abs(POP_JUMP_IF_FALSE,abs_next);

        message = "POP_JUMP_IF_FALSE";
        D(message);
        and_expr = child_and_expr;

        child_and_expr = and_expr->get_and_expr_r();
    }
    not_expr = and_expr->get_not_expr();
    assert(not_expr != NULL);
    not_expr->visit(*this);

    //code_builder.set_endblock(end);
    //code_builder.use_next_block(end);
    return;
}
/**
 * 逻辑非
 **/
void ByteCodeGen::visit_logical_not_expr( LogicalNotExpr* context )
{
    //两个参数其中有一个必为空
    LogicalNotExpr* not_expr = context->get_not_expr();
    LogicalRelExpr* rel = context->get_rel_expr();

    assert(not_expr != NULL || rel != NULL);

    if (not_expr != NULL && rel == NULL)
    {
        not_expr->visit(*this);
        code_builder.addop(UNARY_NOT); 

        std::string message = "UNARY_NOT";
        D(message);
    }
    else if (not_expr == NULL && rel != NULL)
    {
        rel->visit(*this);
        //do nothing just visit it
    }
    return;
}
/**
 * 复合表达式
 **/
void ByteCodeGen::visit_logical_rel_expr( LogicalRelExpr* context )
{
    SmallExpr* small_expr = context->get_small_expr();
    LogicalRelExprR* rel = context->get_rel_r();

    assert(small_expr != NULL);

    //code_builder.set_context_ty(Load);
    small_expr->visit(*this);
    //code_builder.set_context_ty(Empty);

    if (rel != NULL)
    {
        rel->visit(*this);
    }
    return;
}
/**
 * 复合表达式的右端
 **/
void ByteCodeGen::visit_logical_rel_expr_r( LogicalRelExprR* context )
{
    SmallExpr* small_expr = context->get_small_expr();
    TokenFlag token_flag = context->get_token_flag();
    LogicalRelExprR* rel = context->get_rel_r();

    assert(small_expr != NULL);

    code_builder.set_context_ty(Load);
    small_expr->visit(*this);
    code_builder.set_context_ty(Empty);
    int32_t arg = code_builder.cmpop(token_flag);
    code_builder.addop_i(COMPARE_OP,arg);
    //注意：这里没有管rel，实际上我不打算实现它了

    std::string message = "COMPARE_OP";
    D(message);

    return;
}
/**
 * 或表达式BINARY_OR
 * 从按位操作开始生成字节码的方案都是一样的，如果能整合到一起
 *　那会更好，一种可行的方案是：将所有的访问类成员的函数命名
 * get_first和get_second，并将其集中到一个函数内，
 *　另一种可行的方案是，根本不需要这么多类，只要一个类，并
 * 记录其的操作符即可，python中就是这样做的
 **/
void ByteCodeGen::visit_or_expr( OrExpr* context )
{
    XorExpr* xor_expr = context->get_xor_expr();
    OrExpr* or_expr = context->get_or_expr_r();

    assert(xor_expr != NULL);

    //前序遍历
    xor_expr->visit(*this);
    while (or_expr != NULL)
    {
        xor_expr = or_expr->get_xor_expr();
        assert(xor_expr != NULL);

        xor_expr->visit(*this);
        code_builder.addop(BINARY_OR);

        std::string message = "BINARY_OR";
        D(message);

        or_expr = or_expr->get_or_expr_r();
    }
    return;
}
/**
 * 异或表达式
 **/
void ByteCodeGen::visit_xor_expr( XorExpr* context )
{
    AndExpr* and_expr = context->get_and_expr();
    XorExpr* xor_expr = context->get_xor_expr_r();

    assert(and_expr != NULL);

    and_expr->visit(*this);

    while (xor_expr != NULL)
    {
        and_expr = xor_expr->get_and_expr();
        assert(and_expr != NULL);

        and_expr->visit(*this);
        code_builder.addop(BINARY_XOR);

        std::string message = "BINARY_XOR";
        D(message);

        xor_expr = xor_expr->get_xor_expr_r();
    }
    return;
}
/**
 * 与表达式
 **/
void ByteCodeGen::visit_and_expr( AndExpr* context )
{
    ShiftExpr* shift_expr = context->get_shift_expr();
    AndExpr* and_expr = context->get_and_expr_r();

    assert(shift_expr != NULL);

    shift_expr->visit(*this);

    while (and_expr != NULL)
    {
        shift_expr = and_expr->get_shift_expr();
        assert(shift_expr != NULL);

        shift_expr->visit(*this);
        code_builder.addop(BINARY_AND);

        std::string message = "BINARY_AND";
        D(message);

        and_expr = and_expr->get_and_expr_r();
    }
    return;
}
/**
 * 左移右移表达式
 **/
void ByteCodeGen::visit_shift_expr( ShiftExpr* context )
{
    ArithExpr* arith_expr = context->get_arith_expr();
    ShiftExprR* shift_expr = context->get_shift_expr_r();

    assert(arith_expr != NULL);
    //assert(shift_expr != NULL);

    arith_expr->visit(*this);

    if (shift_expr != NULL)
    {
        shift_expr->visit(*this);
    }

    //这里有点不够统一，其实完全能够合并
    //注意这里并没有生成字节码，而是在下一个类中生成的
    return;
}
/**
 * 左移右移表达式的右端
 **/
void ByteCodeGen::visit_shift_expr_r( ShiftExprR* context )
{
    TokenFlag token_flag = context->get_token_flag();
    ArithExpr* arith_expr = context->get_arith_expr();
    ShiftExprR* shift_expr = context->get_shift_expr_r();

    assert(arith_expr != NULL);

    //这里代码有些冗余
    arith_expr->visit(*this);

    std::string message;
    if (token_flag == LEFTSHIFT)
    {
        code_builder.addop(BINARY_LSHIFT);

        message = "BINARY_LSHIFT";
        D(message);
    }
    else if (token_flag == RIGHTSHIFT)
    {
        code_builder.addop(BINARY_RSHIFT);

        message = "BINARY_RSHIFT";
        D(message);
    }
    while (shift_expr != NULL)
    {
        token_flag = shift_expr->get_token_flag();
        arith_expr = shift_expr->get_arith_expr();

        assert(arith_expr != NULL);

        arith_expr->visit(*this);
        if (token_flag == LEFTSHIFT)
        {
            code_builder.addop(BINARY_LSHIFT);

            message = "BINARY_LSHIFT";
            D(message);
        }
        else if (token_flag == RIGHTSHIFT)
        {
            code_builder.addop(BINARY_RSHIFT);

            message = "BINARY_RSHIFT";
            D(message);
        }

        shift_expr = shift_expr->get_shift_expr_r();
    }
    return;
}
/**
 * 算数表达式
 **/
void ByteCodeGen::visit_arith_expr( ArithExpr* context )
{
    TermExpr* term = context->get_term();
    ArithExprR* arith_expr = context->get_arith_expr_r();

    assert(term != NULL);
    //assert(arith_expr != NULL);

    term->visit(*this);
    if (arith_expr != NULL)
    {
        arith_expr->visit(*this);
    }
    //到这一步，代码冗余的太多了，还是跟着前人走过的路子好
    //注意，这里在下一类中生成了字节码
    return;
}
/**
 * 算数表达式的右端
 **/
void ByteCodeGen::visit_arith_expr_r( ArithExprR* context )
{
    TokenFlag token_flag = context->get_token_flag();
    TermExpr* term = context->get_term();
    ArithExprR* arith_expr = context->get_arith_expr_r();

    assert(term != NULL);

    term->visit(*this);

    std::string message;

    if (token_flag == PLUS)
    {
        code_builder.addop(BINARY_ADD);

        message = "BINARY_ADD";
        D(message);
    }
    else if (token_flag == MINUS)
    {
        code_builder.addop(BINARY_SUBSCR);

        message = "BINARY_SUBSCR";
        D(message);
    }

    while (arith_expr != NULL)
    {
        token_flag = arith_expr->get_token_flag();
        term = arith_expr->get_term();

        assert(term != NULL);
        
        term->visit(*this);
        if (token_flag == PLUS)
        {
            code_builder.addop(BINARY_ADD);

            message = "BINARY_ADD";
            D(message);
        }
        else if (token_flag == MINUS)
        {
            code_builder.addop(BINARY_SUBSCR);

            message = "BINARY_SUBSCR";
            D(message);
        }
        arith_expr = arith_expr->get_arith_expr_r();
    }
    return;
}
/**
 * term
 **/
void ByteCodeGen::visit_term_expr( TermExpr* context )
{
    FactorExpr* factor = context->get_factor();
    TermExprR* term_r = context->get_term_r();

    assert(factor != NULL);
    //assert(term_r != NULL);

    factor->visit(*this);

    if (term_r != NULL)
    {
        term_r->visit(*this);
    }
    return;
}
/**
 * term的右端
 **/
void ByteCodeGen::visit_term_expr_r( TermExprR* context )
{
    TokenFlag token_flag = context->get_token_flag();
    FactorExpr* factor = context->get_factor();
    TermExprR* term = context->get_term_r();

    assert(factor != NULL);

    std::string message;

    factor->visit(*this);
    if (token_flag == STAR)
    {
        code_builder.addop(BINARY_MULTIPLY);

        message = "BINARY_MULTIPLY";
        D(message);
    }
    else if (token_flag == SLASH)
    {
        code_builder.addop(BINARY_TRUE_DIVIDE);

        message = "BINARY_TRUE_DIVIDE";
        D(message);
    }
    else if (token_flag == PERCENT)
    {
        code_builder.addop(BINARY_MODULO);

        message = "BINARY_MODULO";
        D(message);
    }
    else if (token_flag == DOUBLESLASH)
    {
        code_builder.addop(BINARY_FLOOR_DIVIDE);

        message = "BINARY_FLOOR_DIVIDE";
        D(message);
    }

    while (term != NULL)
    {
        token_flag = term->get_token_flag();
        factor = term->get_factor();

        assert(factor != NULL);

        factor->visit(*this);
        if (token_flag == STAR)
        {
            code_builder.addop(BINARY_MULTIPLY);

            message = "BINARY_MULTIPLY";
            D(message);
        }
        else if (token_flag == SLASH)
        {
            code_builder.addop(BINARY_TRUE_DIVIDE);

            message = "BINARY_TRUE_DIVIDE";
            D(message);
        }
        else if (token_flag == PERCENT)
        {
            code_builder.addop(BINARY_MODULO);

            message = "BINARY_MODULO";
            D(message);
        }
        else if (token_flag == DOUBLESLASH)
        {
            code_builder.addop(BINARY_FLOOR_DIVIDE);

            message = "BINARY_FLOOR_DIVIDE";
            D(message);
        }

        term = term->get_term_r();
    }
    return;
}
/**
 * factor
 **/
void ByteCodeGen::visit_factor_expr( FactorExpr* context )
{
    TokenFlag token_flag = context->get_token_flag();
    FactorExpr* factor = context->get_factor();
    PowerExpr* power = context->get_power_expr();

    assert(factor != NULL || power != NULL);

    if (token_flag == EMPTY)
    {
        power->visit(*this);
        return;
    }
    std::string message;

    //到这里是第一种选择
    factor->visit(*this);
    if (token_flag == PLUS)
    {
        code_builder.addop(UNARY_POSITIVE);
        message = "UNARY_POSITIVE";
        D(message);
    }
    else if (token_flag == MINUS)
    {
        code_builder.addop(UNARY_NEGATIVE);

        message = "UNARY_NEGATIVE";
        D(message);
    }
    else if (token_flag == TILDE)
    {
        code_builder.addop(UNARY_INVERT);

        message = "UNARY_INVERT";
        D(message);
    }
    return;
}
/**
 * power平方
 **/
void ByteCodeGen::visit_power_expr( PowerExpr* context )
{
    AtomExpr* atom = context->get_atom();
    FactorExpr* factor = context->get_factor();

    assert(atom != NULL);

    atom->visit(*this);

    if (factor != NULL)
    {
        factor->visit(*this);
        code_builder.addop(BINARY_POWER);

        std::string message = "BINARY_POWER";
        D(message);
    }
    return;
}
/**
 * 元组,参数还存在很多问题，暂留吧
 **/
void ByteCodeGen::visit_tuple_expr( TupleExpr* context )
{
    TupleVariableExpr* variable = context->get_variable();

    assert(variable != NULL);

    variable->visit(*this);
    return;
}
/**
 * 映射类型
 **/
void ByteCodeGen::visit_map_expr( MapExpr* context )
{
    MapVariableExpr* variable = context->get_variable();

    assert(variable != NULL);

    variable->visit(*this);
    return;
}
/**
 * 元组参数
 **/
void ByteCodeGen::visit_tuple_variable_expr( TupleVariableExpr* context )
{
    Expr* t_expr = context->get_expr();
    TupleVariableExpr* variable = context->get_variable();

    assert(t_expr != NULL);

    t_expr->visit(*this);
    if (variable != NULL)
    {
        variable->visit(*this);  //递归调用自己
    }
    return;
}
/**
 * 映射类型参数
 **/
void ByteCodeGen::visit_map_variable_expr( MapVariableExpr* context )
{
    Expr* t_expr_l = context->get_expr_l();
    Expr* t_expr_r = context->get_expr_r();
    MapVariableExpr* variable = context->get_variable();

    assert(t_expr_l != NULL);
    assert(t_expr_r != NULL);

    t_expr_l->visit(*this);
    t_expr_r->visit(*this);
    variable->visit(*this);  //递归
    return;
}
/**
 * 数字
 **/
void ByteCodeGen::visit_number_expr( NumberExpr* context )
{
    LongObject* int_value = context->get_int();
    FloatObject* float_value = context->get_float();

    std::string message;

    if (int_value != NULL)
    {
        int32_t t_value = int_value->get_int();
        code_builder.addop_interger(LOAD_INT,t_value);

        message = "LOAD_INT";
        D(message);
    }
    else if (float_value != NULL)
    {
        double t_value = float_value->get_double();
        code_builder.addop_float(LOAD_FLOAT,t_value);

        message = "LOAD_FLOAT";
        D(message);
    }
    else
    {
        THROW_ERROR(ERROR_NO_NUMBER);
    }
    return;
}
/**
 * 字符串
 **/
void ByteCodeGen::visit_string_expr( StringExpr* context )
{
    std::string name = context->get_value();
    StringExpr* string_other = context->get_string_other();

    assert(name.empty() != true);

    code_builder.addop_const(LOAD_CONST,name);
    
    std::string message = "LOAD_CONST";
    D(message);

    if (string_other == NULL)
    {
        return;
    }
    string_other->visit(*this);
    return;
}
/**
 * 关键字集合
 **/
void ByteCodeGen::visit_keyword_expr( KeyWordExpr* context )
{
    LongObject* value = context->get_value();

    int t_value = value->get_int();

    std::string message;

    if (t_value)
    {
        code_builder.addop_interger(LOAD_INT,1);

        message = "LOAD_INT";
        D(message);
    }
    else
    {
        code_builder.addop_interger(LOAD_INT,0);
        message = "LOAD_INT";
        D(message);
    }
    return;
}
/**
 * 生成我们用的最多的字节码序列
 * 对NameExpr我们采用前序遍历
 **/
void ByteCodeGen::visit_name_expr( NameExpr* context )
{
    std::string name = context->get_name();
    AtomExpr* name_expr_r = context->get_name_expr_r();

    assert(name.empty() != true);

    std::string message;

    //如果不为空，那么一定是函数调用或模块调用，那么也就没有必要使用上下文
    //环境了，那一定是load，如果要对函数调用的返回值赋值，这只有C++这样的语言
    //能够支持，对Python不可能
    if (name_expr_r != NULL)
    {
        if (code_builder.find_symbol(name) == NULL)
        {
            THROW_ERROR(ERROR_NO_FOUND_SYMBOL);
        }
        code_builder.addop_name(LOAD_NAME,name);

        message = "LOAD_NAME";
        D(message);

        name_expr_r->visit(*this);
        return;
    }
    Expr_context_ty ext = code_builder.get_context_ty();

    Op opcode;

    switch (ext)
    {
    case Load:
        opcode = LOAD_NAME;
        message = "LOAD_NAME";
        break;
    case Store:
        opcode = STORE_NAME;
        message = "STORE_NAME";
        break;
    case Param:
        //code_builder.addop_varname(LOAD_NAME,name);
        code_builder.add_var(name);

        message = "add_var";
        D(message);
        //向参数中添加
        return ;
    default:
        opcode = LOAD_NAME;
        message = "LOAD_NAME";
    }
    code_builder.addop_name(opcode,name);

    D(message);
    return;
}
/**
 * 函数调用
 **/
void ByteCodeGen::visit_fun_invoke_expr( FunInvokeExpr* context )
{
    ParametersExpr* paras = context->get_paras();

    uint32_t counter = 0;

    //assert(paras != NULL);
    paras->visit(*this);
    //计算该函数共有几个参数
    while (paras != NULL)
    {
        paras = paras->get_other_para();
        counter++;
    }
    code_builder.addop_i(CALL_FUNCTION,counter);

    std::string message("CALL_FUNCTION");
    D(message);

    return;
}
/**
 * 模块调用，从下至上调用
 **/
void ByteCodeGen::visit_module_invoke_expr( ModuleInvokeExpr* context )
{
    std::string name = context->get_name();
    ModuleInvokeExpr* module_invoke = context->get_module_expr_r();

    assert(name.empty() != NULL);
    assert(module_invoke != NULL);

    code_builder.addop_name(LOAD_NAME,name);

    uint32_t counter = 1;
    while (module_invoke != NULL)
    {
        module_invoke = module_invoke->get_module_expr_r();
        name = module_invoke->get_name();
        assert(name.empty() != NULL);

        code_builder.addop_name(LOAD_NAME,name);
        counter++;
    }
    code_builder.addop_i(LOAD_BUILD_CLASS,counter);
    //将栈顶的counter个元素取出，从下往上调用
    return;
}
/*********begin SymTableGen class scope************
 *  每个符号表生成都是从语法树根部开始的，即模块，所以符号
 *  被初始化为了模块表
 **/
SymTableGen::SymTableGen(std::string& t_file_path)
{
    //模块前一符号表为空，恰好为返回标志
    //模块的名字为文件路径
    sym_table = new SymbolTable(NULL,t_file_path);
    sym_table->set_type(MODULE);    //初始化为一个模块类型的符号表
    return;
}
/**
 * do nothing，这里我们需要将建好的符号表返回，所以不能删除
 **/
SymTableGen::~SymTableGen()
{
    return;
}
/**
 * @context 上下文环境
 **/
void SymTableGen::visit_stmt_seq( StmtSeq* context )
{
    Stmt* t_stmt = context->get_stmt();
    StmtSeq* stmt_seq = context->get_stmt_seq();

    assert(t_stmt != NULL);

    t_stmt->visit(*this);
    if (stmt_seq != NULL)
    {
        stmt_seq->visit(*this);
    }
    return;
}
/**
 * simple_stmt是连续的，不进入作用域
 **/
void SymTableGen::visit_simple_stmt( SimpleStmt* context )
{
    SmallStmt* small_stmt = context->get_small_stmt();
    SimpleStmt* small_stmt_r = context->get_small_stmt_r();

    assert(small_stmt != NULL);

    //严格的前序遍历
    small_stmt->visit(*this);

    //递归终止条件
    if (small_stmt_r != NULL)
    {
        small_stmt_r->visit(*this);
    }
    return;
}
/**
 *   将DelStmt的NAME域加入符号表 
 **/
void SymTableGen::visit_del_stmt( DelStmt* context )
{
    std::string name = context->get_name();
    assert(name.empty() != true);

    sym_table->push_back(name);
    return;
}
/**
 * import与del语句相同，只是简单的向符号表中添加名字
 **/
void SymTableGen::visit_import_stmt( ImportStmt* context )
{
    std::string name = context->get_name();

    assert(name.empty() != true);

    sym_table->push_back(name);
    return;
}
/**
 * 赋值语句的左部与右部都不能为空
 **/
void SymTableGen::visit_assign_stmt( Assign* context )
{
    Expr* t_expr = context->get_expr();

    DerictAssign* derict_assign = context->get_derict_assign();
    AugAssign* aug_assign = context->get_aug_assign();

    assert(t_expr != NULL);

    if (derict_assign != NULL)
    {
        //对单一赋值使用后序遍历
        derict_assign->visit(*this);
        //应该存储expr,存储的指令在遍历expr时，当遇到name被存储
        t_expr->visit(*this);
    }
    else if (aug_assign != NULL)
    {
        //对于复合赋值使用前序遍历
        t_expr->visit(*this);
        //应该load expr,复合赋值的指令在visit assign_r的时候被生成
        aug_assign->visit(*this);
    }
    else
    {
        t_expr->visit(*this);
    }
    return;
}
/**
 *
 **/
void SymTableGen::visit_derict_assign_stmt( DerictAssign* context )
{
    Expr* t_expr = context->get_expr();
    DerictAssign* exprs_r = context->get_exprs_r();

    assert(t_expr != NULL);

    t_expr->visit(*this);
    //递归终止条件
    if (exprs_r != NULL)
    {
        exprs_r->visit(*this);
    }
    return;
}
/**
 *
 **/
void SymTableGen::visit_aug_assign_stmt( AugAssign* context )
{
    //对tokenflag不做处理
    Expr* t_expr = context->get_expr();

    assert(t_expr != NULL);

    t_expr->visit(*this);
    return;
}
/**
 * 访问if语句的时候要注意elif与else语句可以为空
 **/
void SymTableGen::visit_if_stmt( IfStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElifStmt* elif = context->get_elif_stmt();
    ElseStmt* else_ = context->get_else_stmt();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    //严格的前序遍历
    sym_table = sym_table->enter_scope("if",context);
    t_expr->visit(*this);
    t_stmt->visit(*this);

    if (elif != NULL)
    {
        elif->visit(*this);
    }
    if (else_ != NULL)
    {
        else_->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_elif_stmt( ElifStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElifStmt* elif = context->get_elif();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);
    
    sym_table = sym_table->enter_scope("elif",context);

    t_expr->visit(*this);
    t_stmt->visit(*this);

    //当elif为空时递归结束
    if (elif != NULL)
    {
        elif->visit(*this);
    }
    return;
}
/**
 * else语句只是简单的访问suite
 **/
void SymTableGen::visit_else_stmt( ElseStmt* context )
{
    Suite* t_stmt = context->get_suite();

    assert(t_stmt != NULL);

    sym_table = sym_table->enter_scope("else",context);
    t_stmt->visit(*this);
    return;
}
/**
 * else 语句也只是简单的访问，不对else进行访问
 **/
void SymTableGen::visit_while_stmt( WhileStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElseStmt* else_ = context->get_else_stmt();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    sym_table = sym_table->enter_scope("while",context);

    t_expr->visit(*this);
    t_stmt->visit(*this);
    if (else_ != NULL)
    {
        else_->visit(*this);
    }
    return;
}
/**
 * for statement
 **/
void SymTableGen::visit_for_stmt( ForStmt* context )
{
    Expr* expr_con = context->get_expr_con();
    Expr* expr_range = context->get_expr_range();
    Suite* stmt = context->get_suite();
    ElseStmt* else_ = context->get_else_stmt();

    assert(expr_con != NULL);
    assert(expr_range != NULL);
    assert(stmt != NULL);

    sym_table = sym_table->enter_scope("for",context);
    expr_con->visit(*this);
    expr_range->visit(*this);
    stmt->visit(*this);
    if (else_ != NULL)
    {
        else_->visit(*this);
    }
    return;
}
/**
 * finally可以为空
 **/
void SymTableGen::visit_try_stmt( TryStmt* context )
{
    Suite* stmt_target = context->get_target();
    CatchStmt* stmt_catchs = context->get_catchs();
    Suite* stmt_finally = context->get_finally();

    assert(stmt_target != NULL);
    assert(stmt_catchs != NULL);

    sym_table = sym_table->enter_scope("try",context);
    stmt_target->visit(*this);
    stmt_catchs->visit(*this);
    
    if (stmt_finally != NULL)
    {
        stmt_finally->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_catch_stmt( CatchStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    CatchStmt* catchs = context->get_catchs();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    sym_table = sym_table->enter_scope("catch",context);
    t_expr->visit(*this);
    t_stmt->visit(*this);
    //递归结束条件
    if (catchs != NULL)
    {
        catchs->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_fun_stmt( FunStmt* context )
{
    std::string name = context->get_name();
    ParametersExpr* para = context->get_para();
    Suite* stmt = context->get_suite();

    assert(name.empty() != true);

    //参数可以为空，所以不做判断
    assert(stmt != NULL);
   
    sym_table = sym_table->enter_scope(name,context,FUN);

    if (para != NULL)
    {
        para->visit(*this);
    }
    stmt->visit(*this);
    return;
}
/**
 * 
 **/
void SymTableGen::visit_class_stmt( ClassStmt* context )
{
    std::string name = context->get_name();
    Suite* stmt = context->get_suite();

    assert(name.empty() != true);
    assert(stmt != NULL);

    sym_table = sym_table->enter_scope(name,context,CLASS);
    stmt->visit(*this);
    return;
}
/**
 * 
 **/
void SymTableGen::visit_suite_stmt( Suite* context )
{
    StmtSeq* stmts = context->get_stmts();
    SimpleStmt* simple_stmt = context->get_simple_stmt();

    assert(stmts != NULL || simple_stmt != NULL);
    //两者之中必须有一个不为空

    if (simple_stmt != NULL)
    {
        simple_stmt->visit(*this);
    }
    else if (stmts != NULL)
    {
        stmts->visit(*this);
    }
    sym_table = sym_table->out_scope();
    //在后面退出
    return;
}
/**
 * 遍历所有参数
 **/
void SymTableGen::visit_parameters_expr( ParametersExpr* context )
{
    ParameterExprAtom* parameter = context->get_parameter();
    ParametersExpr* other = context->get_other_para();

    assert(parameter != NULL);
    parameter->visit(*this);

    if (other != NULL)
    {
        other->visit(*this);
    }
    return;
}
/**
 * 普通参数
 **/
void SymTableGen::visit_no_star_parameter_expr( NostarParameterExpr* context )
{
    //std::string name = context->get_name();
    AtomExpr* atom = context->get_atom();
    Expr* t_expr = context->get_expr();

    assert(atom != NULL);
    //可以有默认值
    //sym_table->push_back(context->get_name(),context);
    atom->visit(*this);

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_tuple_parameter_expr( TupleParameterExpr* context )
{
    std::string name = context->get_name();
    Expr* t_expr = context->get_expr();

    assert(name.empty() != true);
    //可以有默认参数
    sym_table->push_back(name);

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_map_parameter_expr( MapParameterExpr* context )
{
    std::string name = context->get_name();
    Expr* t_expr = context->get_expr();

    assert(name.empty() != true);
    //参数可以为空

    sym_table->push_back(name);

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_lambda_expr( LambdaExpr* context )
{
    ParametersExpr* parameters = context->get_parameters();
    ConExpr* t_expr = context->get_expr();

    //参数可以为空
    assert(t_expr != NULL);

    if (parameters != NULL)
    {
        parameters->visit(*this);
    }
    t_expr->visit(*this);
    return;
}
/**
 * 
 **/
void SymTableGen::visit_logical_or_expr( LogicalOrExpr* context )
{
    LogicalAndExpr* and_expr = context->get_and_expr();
    LogicalOrExpr* or_expr_r = context->get_or_expr_r();

    assert(and_expr != NULL);

    and_expr->visit(*this);

    if (or_expr_r != NULL)
    {
        or_expr_r->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_logical_and_expr( LogicalAndExpr* context )
{
    LogicalNotExpr* not_expr = context->get_not_expr();
    LogicalAndExpr* and_expr = context->get_and_expr_r();

    assert(not_expr != NULL);

    not_expr->visit(*this);
    if (and_expr != NULL)
    {
        and_expr->visit(*this);
    }
    return;
}
/**
 *  逻辑非
 **/
void SymTableGen::visit_logical_not_expr( LogicalNotExpr* context )
{
    LogicalNotExpr* not_expr = context->get_not_expr();
    LogicalRelExpr* rel = context->get_rel_expr();

    assert(not_expr != NULL || rel != NULL);
    //两者之中必须有一种不为空

    if (not_expr != NULL)
    {
        not_expr->visit(*this);
    }
    if (rel != NULL)
    {
        rel->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_logical_rel_expr( LogicalRelExpr* context )
{
    SmallExpr* small_expr = context->get_small_expr();
    LogicalRelExprR* rel = context->get_rel_r();

    //必须两者都不为空
    assert(small_expr != NULL);

    small_expr->visit(*this);
    if (rel != NULL)
    {
        rel->visit(*this);
    }
    return;
}
/**
 * 复合二元比较的右部
 **/
void SymTableGen::visit_logical_rel_expr_r( LogicalRelExprR* context )
{
    SmallExpr* small_expr = context->get_small_expr();
    LogicalRelExprR* rel = context->get_rel_r();

    assert(small_expr != NULL);

    small_expr->visit(*this);
    
    if (rel != NULL)
    {
        rel->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_or_expr( OrExpr* context )
{
    XorExpr* xor_expr = context->get_xor_expr();
    OrExpr* or_expr = context->get_or_expr_r();

    assert(xor_expr != NULL);

    xor_expr->visit(*this);

    if (or_expr != NULL)
    {
        or_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_xor_expr( XorExpr* context )
{
    AndExpr* and_expr = context->get_and_expr();
    XorExpr* xor_expr = context->get_xor_expr_r();

    assert(and_expr != NULL);

    and_expr->visit(*this);

    if (xor_expr != NULL)
    {
        xor_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_and_expr( AndExpr* context )
{
    ShiftExpr* shift_expr = context->get_shift_expr();
    AndExpr* and_expr = context->get_and_expr_r();

    assert(shift_expr != NULL);

    shift_expr->visit(*this);

    if (and_expr != NULL)
    {
        and_expr->visit(*this);
    }
    return;
}
/**
 * 包含有右部，其右部都必须不为空
 **/
void SymTableGen::visit_shift_expr( ShiftExpr* context )
{
    ArithExpr* arith_expr = context->get_arith_expr();
    ShiftExprR* shift_expr = context->get_shift_expr_r();

    assert(arith_expr != NULL);
    //assert(shift_expr != NULL);

    arith_expr->visit(*this);

    if (shift_expr != NULL)
    {
        shift_expr->visit(*this);
    }

    return;
}
/**
 * 
 **/
void SymTableGen::visit_shift_expr_r( ShiftExprR* context )
{
    ArithExpr* arith_expr = context->get_arith_expr();
    ShiftExprR* shift_expr = context->get_shift_expr_r();

    assert(arith_expr != NULL);

    //这里代码有些冗余
    arith_expr->visit(*this);

    if (shift_expr != NULL)
    {
        shift_expr->visit(*this);
    }
    return;
}
/**
 * 两个孩子都不能为空
 **/
void SymTableGen::visit_arith_expr( ArithExpr* context )
{
    TermExpr* term = context->get_term();
    ArithExprR* arith_expr = context->get_arith_expr_r();

    assert(term != NULL);
    //assert(arith_expr != NULL);

    term->visit(*this);

    if (arith_expr != NULL)
    {
        arith_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_arith_expr_r( ArithExprR* context )
{
    TermExpr* term = context->get_term();
    ArithExprR* arith_expr = context->get_arith_expr_r();

    assert(term != NULL);

    term->visit(*this);

    if (arith_expr != NULL)
    {
        arith_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_term_expr( TermExpr* context )
{
    FactorExpr* factor = context->get_factor();
    TermExprR* term_r = context->get_term_r();

    //因为有右部，所以两者都不能为空
    assert(factor != NULL);
    //assert(term_r != NULL);

    factor->visit(*this);

    if (term_r != NULL)
    {
        term_r->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_term_expr_r( TermExprR* context )
{
    FactorExpr* factor = context->get_factor();
    TermExprR* term_r = context->get_term_r();

    assert(factor != NULL);

    factor->visit(*this);

    if (term_r != NULL)
    {
        term_r->visit(*this);
    }
    return;
}
/**
 * factor要注意一下
 **/
void SymTableGen::visit_factor_expr( FactorExpr* context )
{
    FactorExpr* factor = context->get_factor();
    PowerExpr* power = context->get_power_expr();

    assert(factor != NULL || power != NULL);

    if (factor != NULL)
    {
        factor->visit(*this);
    }
    if (power != NULL)
    {
        power->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_power_expr( PowerExpr* context )
{
    AtomExpr* atom = context->get_atom();
    FactorExpr* factor = context->get_factor();

    assert(atom != NULL);
    //factor可以为空
    atom->visit(*this);
    if (factor != NULL)
    {
        factor->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_tuple_expr( TupleExpr* context )
{
    TupleVariableExpr* variable = context->get_variable();

    assert(variable != NULL);

    variable->visit(*this);
    return;
}
/**
 * 
 **/
void SymTableGen::visit_map_expr( MapExpr* context )
{
    MapVariableExpr* variable = context->get_variable();

    assert(variable != NULL);

    variable->visit(*this);
    return;
}
/**
 * 
 **/
void SymTableGen::visit_tuple_variable_expr( TupleVariableExpr* context )
{
    Expr* t_expr = context->get_expr();
    TupleVariableExpr* variable = context->get_variable();

    assert(t_expr != NULL);
    //可以只有一个参数

    t_expr->visit(*this);

    if (variable != NULL)
    {
        variable->visit(*this);  //递归调用自己
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_map_variable_expr( MapVariableExpr* context )
{
    Expr* t_expr_l = context->get_expr_l();
    Expr* t_expr_r = context->get_expr_r();
    MapVariableExpr* variable = context->get_variable();

    assert(t_expr_l != NULL);
    assert(t_expr_r != NULL);
    //可以只有一个参数，所以variable可以为空

    t_expr_l->visit(*this);
    t_expr_r->visit(*this);

    if (variable != NULL)
    {
        variable->visit(*this);  //递归
    }
    return;
}
/**
 * number属于常量，不需要想符号表中添加
 **/
void SymTableGen::visit_number_expr( NumberExpr* context )
{
    return;
}
/**
 * string也属于常量，也不需要想符号表中添加
 **/
void SymTableGen::visit_string_expr( StringExpr* context )
{
    return;
}
/**
 * do nothing
 **/
void SymTableGen::visit_keyword_expr( KeyWordExpr* context )
{
    return;
}
/**
 * 
 **/
void SymTableGen::visit_name_expr( NameExpr* context )
{
    std::string name = context->get_name();
    AtomExpr* name_expr = context->get_name_expr_r();

    assert(name.empty() != true);

    // 当没有后面部分的时候说明只是简单语句调用
    sym_table->push_back(name);
    if (name_expr != NULL)
    {
        name_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_fun_invoke_expr( FunInvokeExpr* context )
{
    ParametersExpr* paras = context->get_paras();

    //参数可以为空
    if (paras != NULL)
    {
        paras->visit(*this);
    }
    return;
}
/**
 * 
 **/
void SymTableGen::visit_module_invoke_expr( ModuleInvokeExpr* context )
{
    std::string name = context->get_name();
    ModuleInvokeExpr* module_invoke = context->get_module_expr_r();

    assert(name.empty() != NULL);
    assert(module_invoke != NULL);

    module_invoke->visit(*this);
    return;
}
/**
 * 
 **/
SymbolTable* SymTableGen::get_sym_table()
{
    return sym_table;
}


#ifdef EF_DEBUG
/**
 * 
 */
NodePrintor::NodePrintor(std::ostream& out)
:cout(out)
{
    cout.flags(std::ios_base::hex);
    return;
}
/**
 * 
 */
NodePrintor::~NodePrintor()
{
    return;
}
/**
 * @context 上下文环境
 **/
void NodePrintor::visit_stmt_seq( StmtSeq* context )
{
    Stmt* t_stmt = context->get_stmt();
    StmtSeq* stmt_seq = context->get_stmt_seq();

    assert(t_stmt != NULL);

    cout << "StmtSeq:" << context << "\t"
        << "Stmt:" << t_stmt << "\t"
        << "StmtSeq:" << stmt_seq << std::endl;

    t_stmt->visit(*this);
    if (stmt_seq != NULL)
    {
        stmt_seq->visit(*this);
    }
    return;
}
/**
 * simple_stmt是连续的，不进入作用域
 **/
void NodePrintor::visit_simple_stmt( SimpleStmt* context )
{
    SmallStmt* small_stmt = context->get_small_stmt();
    SimpleStmt* small_stmt_r = context->get_small_stmt_r();

    assert(small_stmt != NULL);

    cout << "SimpleStmt:" << context << "\t"
        << "SmallStmt:" << small_stmt << "\t"
        << "SimpleStmt:" << small_stmt_r << std::endl;

    //严格的前序遍历
    small_stmt->visit(*this);

    //递归终止条件
    if (small_stmt_r != NULL)
    {
        small_stmt_r->visit(*this);
    }
    return;
}
/**
 *   将DelStmt的NAME域加入符号表 
 **/
void NodePrintor::visit_del_stmt( DelStmt* context )
{
    std::string name = context->get_name();
    assert(name.empty() != true);

    cout << "DelStmt:" << context << "\t"
        << "name:" << name << std::endl;
    return;
}
/**
 * import与del语句相同，只是简单的向符号表中添加名字
 **/
void NodePrintor::visit_import_stmt( ImportStmt* context )
{
    std::string name = context->get_name();

    assert(name.empty() != true);

    cout << "ImportStmt:" << context << "\t"
        << "name:" << name << std::endl;
    return;
}
/**
 * 赋值语句的左部与右部都不能为空
 **/
void NodePrintor::visit_assign_stmt( Assign* context )
{
    Expr* t_expr = context->get_expr();

    DerictAssign* derict_assign = context->get_derict_assign();
    AugAssign* aug_assign = context->get_aug_assign();

    assert(t_expr != NULL);
    //assert(assign_r != NULL);

    cout << "Assign:" << context << "\t"
        << "Expr:" << t_expr << "\t"
        << "DerictAssign:" << derict_assign << "\t"
        << "AugAssign:" << aug_assign << std::endl;

    if (derict_assign != NULL)
    {
        //对单一赋值使用后序遍历
        derict_assign->visit(*this);
        //应该存储expr,存储的指令在遍历expr时，当遇到name被存储
        t_expr->visit(*this);
    }
    else if (aug_assign != NULL)
    {
        //对于复合赋值使用前序遍历
        t_expr->visit(*this);
        //应该load expr,复合赋值的指令在visit assign_r的时候被生成
        aug_assign->visit(*this);
    }
    else
    {
        t_expr->visit(*this);
    }
    return;
}
/**
 *
 **/
void NodePrintor::visit_derict_assign_stmt( DerictAssign* context )
{
    Expr* t_expr = context->get_expr();
    DerictAssign* exprs_r = context->get_exprs_r();

    assert(t_expr != NULL);

    cout << "DerictAssign:" << context << "\t"
        << "Expr:" << t_expr << "\t"
        << "DerictAssign:" << exprs_r << std::endl;

    t_expr->visit(*this);
    //递归终止条件
    if (exprs_r != NULL)
    {
        exprs_r->visit(*this);
    }
    return;
}
/**
 *
 **/
void NodePrintor::visit_aug_assign_stmt( AugAssign* context )
{
    //对tokenflag不做处理
    Expr* t_expr = context->get_expr();

    assert(t_expr != NULL);

    cout << "AugAssign:" << context << "\t"
        << "Expr:" << t_expr << std::endl;

    t_expr->visit(*this);
    return;
}
/**
 * 访问if语句的时候要注意elif与else语句可以为空
 **/
void NodePrintor::visit_if_stmt( IfStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElifStmt* elif = context->get_elif_stmt();
    ElseStmt* else_ = context->get_else_stmt();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    cout << "IFStmt::" << context << "\t"
        << "Expr:" << t_expr << "\t"
        << "Suite:" << t_stmt << "\t"
        << "ElifStmt:" << elif << "\t"
        << "ElseStmt:" << else_ << std::endl;

    //严格的前序遍历
    t_expr->visit(*this);
    t_stmt->visit(*this);

    if (elif != NULL)
    {
        elif->visit(*this);
    }
    if (else_ != NULL)
    {
        else_->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_elif_stmt( ElifStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElifStmt* elif = context->get_elif();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);
    
    cout << "Elifstmt::" << context << "\t"
        << "Expr:" << t_expr << "\t"
        << "Suite:" << t_stmt << "\t"
        << "ElifStmt:" << elif << std::endl;

    t_expr->visit(*this);
    t_stmt->visit(*this);

    //当elif为空时递归结束
    if (elif != NULL)
    {
        elif->visit(*this);
    }
    return;
}
/**
 * else语句只是简单的访问suite
 **/
void NodePrintor::visit_else_stmt( ElseStmt* context )
{
    Suite* t_stmt = context->get_suite();

    assert(t_stmt != NULL);

    cout << "ElseStmt::" << context << "\t"
        << "Suite:" << t_stmt << std::endl;

    t_stmt->visit(*this);
    return;
}
/**
 * else 语句也只是简单的访问，不对else进行访问
 **/
void NodePrintor::visit_while_stmt( WhileStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElseStmt* else_ = context->get_else_stmt();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    cout << "WhileStmt::" << context << "\t"
        << "Expr:" << t_expr << "\t"
        << "Suite:" << t_stmt << "\t"
        << "ElseStmt:" << else_ << std::endl;

    t_expr->visit(*this);
    t_stmt->visit(*this);
    if (else_ != NULL)
    {
        else_->visit(*this);
    }
    return;
}
/**
 * for statement
 **/
void NodePrintor::visit_for_stmt( ForStmt* context )
{
    Expr* expr_con = context->get_expr_con();
    Expr* expr_range = context->get_expr_range();
    Suite* stmt = context->get_suite();
    ElseStmt* else_ = context->get_else_stmt();

    assert(expr_con != NULL);
    assert(expr_range != NULL);
    assert(stmt != NULL);

    cout << "ForStmt::" << context << "\t"
        << "Expr:" << expr_con << "\t"
        << "Expr:" << expr_range << "\t"
        << "Suite:" << stmt << "\t"
        << "ElseStmt:" << else_ << std::endl;

    expr_con->visit(*this);
    expr_range->visit(*this);
    stmt->visit(*this);
    if (else_ != NULL)
    {
        else_->visit(*this);
    }
    return;
}
/**
 * finally可以为空
 **/
void NodePrintor::visit_try_stmt( TryStmt* context )
{
    Suite* stmt_target = context->get_target();
    CatchStmt* stmt_catchs = context->get_catchs();
    Suite* stmt_finally = context->get_finally();

    assert(stmt_target != NULL);
    assert(stmt_catchs != NULL);

    cout << "TryStmt::" << context << "\t"
        << "Suite:" << stmt_target << "\t"
        << "CatchStmt:" << stmt_catchs << "\t"
        << "Suite:" << stmt_finally << std::endl;

    stmt_target->visit(*this);
    stmt_catchs->visit(*this);
    
    if (stmt_finally != NULL)
    {
        stmt_finally->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_catch_stmt( CatchStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    CatchStmt* catchs = context->get_catchs();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    cout << "CatchStmt:" << context << "\t"
        << "Suite:" << t_stmt << "\t"
        << "CatchStmt:" << catchs << std::endl;

    t_expr->visit(*this);
    t_stmt->visit(*this);
    //递归结束条件
    if (catchs != NULL)
    {
        catchs->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_fun_stmt( FunStmt* context )
{
    std::string name = context->get_name();
    ParametersExpr* para = context->get_para();
    Suite* stmt = context->get_suite();

    assert(name.empty() != true);

    //参数可以为空，所以不做判断
    assert(stmt != NULL);
   
    cout << "FunStmt:" << context << "\t"
        << "name:" << name << "\t"
        << "ParametersExpr:" << para << "\t"
        << "Suite:" << stmt << std::endl;

    if (para != NULL)
    {
        para->visit(*this);
    }
    stmt->visit(*this);
    return;
}
/**
 * 
 **/
void NodePrintor::visit_class_stmt( ClassStmt* context )
{
    std::string name = context->get_name();
    Suite* stmt = context->get_suite();

    assert(name.empty() != true);
    assert(stmt != NULL);

    cout << "ClassStmt:" << context << "\t"
        << "name:" << name << "\t"
        << "Suite:" << stmt << std::endl;

    stmt->visit(*this);
    return;
}
/**
 * 
 **/
void NodePrintor::visit_suite_stmt( Suite* context )
{
    StmtSeq* stmts = context->get_stmts();
    SimpleStmt* simple_stmt = context->get_simple_stmt();

    assert(stmts != NULL || simple_stmt != NULL);
    //两者之中必须有一个不为空
    cout << "Suite:" << context << "\t"
        << "StmtSeq:" << stmts << "\t"
        << "SimpleStmt:" << simple_stmt << std::endl;

    if (simple_stmt != NULL)
    {
        simple_stmt->visit(*this);
    }
    else if (stmts != NULL)
    {
        stmts->visit(*this);
    }
    //在后面退出
    return;
}
/**
 * 遍历所有参数
 **/
void NodePrintor::visit_parameters_expr( ParametersExpr* context )
{
    ParameterExprAtom* parameter = context->get_parameter();
    ParametersExpr* other = context->get_other_para();

    assert(parameter != NULL);

    cout << "ParametersExpr:" << context << "\t"
        << "ParameterExprAtom:" << parameter << "\t"
        << "ParametersExpr:" << other << std::endl;

    parameter->visit(*this);

    if (other != NULL)
    {
        other->visit(*this);
    }
    return;
}
/**
 * 普通参数
 **/
void NodePrintor::visit_no_star_parameter_expr( NostarParameterExpr* context )
{
    //std::string name = context->get_name();
    AtomExpr* atom = context->get_atom();
    Expr* t_expr = context->get_expr();

    assert(atom != NULL);

    cout << "NostarParameterExpr:" << context << "\t"
        << "AtomExpr:" << atom << "\t"
        << "Expr:" << t_expr << std::endl;

    atom->visit(*this);

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_tuple_parameter_expr( TupleParameterExpr* context )
{
    std::string name = context->get_name();
    Expr* t_expr = context->get_expr();

    assert(name.empty() != true);

    cout << "TupleParameterExpr:" << context << "\t"
        << "name:" << name << "\t"
        << "Expr:" << t_expr << std::endl;

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_map_parameter_expr( MapParameterExpr* context )
{
    std::string name = context->get_name();
    Expr* t_expr = context->get_expr();

    assert(name.empty() != true);

    cout << "MapParameterExpr:" << context << "\t"
        << "name:" << name << "\t"
        << "Expr:" << t_expr << std::endl;

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_lambda_expr( LambdaExpr* context )
{
    ParametersExpr* parameters = context->get_parameters();
    ConExpr* t_expr = context->get_expr();

    //参数可以为空
    assert(t_expr != NULL);

    cout << "LambdaExpr:" << context << "\t"
        << "ParametersExpr:" << parameters << "\t"
        << "ConExpr:" << t_expr << std::endl;

    if (parameters != NULL)
    {
        parameters->visit(*this);
    }
    t_expr->visit(*this);
    return;
}
/**
 * 
 **/
void NodePrintor::visit_logical_or_expr( LogicalOrExpr* context )
{
    LogicalAndExpr* and_expr = context->get_and_expr();
    LogicalOrExpr* or_expr_r = context->get_or_expr_r();

    assert(and_expr != NULL);

    cout << "LogicalOrExpr:" << context << "\t"
        << "LogicalAndExpr:" << and_expr << "\t"
        << "LogicalOrExpr:" << or_expr_r << std::endl;

    and_expr->visit(*this);

    if (or_expr_r != NULL)
    {
        or_expr_r->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_logical_and_expr( LogicalAndExpr* context )
{
    LogicalNotExpr* not_expr = context->get_not_expr();
    LogicalAndExpr* and_expr = context->get_and_expr_r();

    assert(not_expr != NULL);

    cout << "LogicalAndExpr:" << context << "\t"
        << "LogicalNotExpr:" << not_expr << "\t"
        << "LogicalAndExpr:" << and_expr << std::endl;

    not_expr->visit(*this);
    if (and_expr != NULL)
    {
        and_expr->visit(*this);
    }
    return;
}
/**
 *  逻辑非
 **/
void NodePrintor::visit_logical_not_expr( LogicalNotExpr* context )
{
    LogicalNotExpr* not_expr = context->get_not_expr();
    LogicalRelExpr* rel = context->get_rel_expr();

    assert(not_expr != NULL || rel != NULL);
    //两者之中必须有一种不为空

    cout << "LogicalNotExpr:" << context << "\t"
        << "LogicalNotExpr:" << not_expr << "\t"
        << "LogicalRelExpr:" << rel << std::endl;

    if (not_expr != NULL)
    {
        not_expr->visit(*this);
    }
    if (rel != NULL)
    {
        rel->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_logical_rel_expr( LogicalRelExpr* context )
{
    SmallExpr* small_expr = context->get_small_expr();
    LogicalRelExprR* rel = context->get_rel_r();

    //必须两者都不为空
    assert(small_expr != NULL);

    cout << "LogicalRelExpr:" << context << "\t"
        << "SmallExpr:" << small_expr << "\t"
        << "LogicalRelExprR:" << rel << std::endl;

    small_expr->visit(*this);

    if (rel != NULL)
    {
        rel->visit(*this);
    }
    return;
}
/**
 * 复合二元比较的右部
 **/
void NodePrintor::visit_logical_rel_expr_r( LogicalRelExprR* context )
{
    SmallExpr* small_expr = context->get_small_expr();
    LogicalRelExprR* rel = context->get_rel_r();

    assert(small_expr != NULL);

    cout << "LogicalRelExprR:" << context << "\t"
        << "SmallExpr:" << small_expr << "\t"
        << "LogicalRelExprR:" << rel << std::endl;

    small_expr->visit(*this);
    
    if (rel != NULL)
    {
        rel->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_or_expr( OrExpr* context )
{
    XorExpr* xor_expr = context->get_xor_expr();
    OrExpr* or_expr = context->get_or_expr_r();

    assert(xor_expr != NULL);

    cout << "OrExpr:" << context << "\t"
        << "XorExpr:" << xor_expr << "\t"
        << "OrExpr:" << or_expr << std::endl;

    xor_expr->visit(*this);

    if (or_expr != NULL)
    {
        or_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_xor_expr( XorExpr* context )
{
    AndExpr* and_expr = context->get_and_expr();
    XorExpr* xor_expr = context->get_xor_expr_r();

    assert(and_expr != NULL);

    cout << "XorExpr:" << context << "\t"
        << "AndExpr:" << and_expr << "\t"
        << "XorExpr:" << xor_expr << std::endl;

    and_expr->visit(*this);

    if (xor_expr != NULL)
    {
        xor_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_and_expr( AndExpr* context )
{
    ShiftExpr* shift_expr = context->get_shift_expr();
    AndExpr* and_expr = context->get_and_expr_r();

    assert(shift_expr != NULL);

    cout << "AndExpr:" << context << "\t"
        << "ShiftExpr:" << shift_expr << "\t"
        << "AndExpr:" << and_expr << std::endl;

    shift_expr->visit(*this);

    if (and_expr != NULL)
    {
        and_expr->visit(*this);
    }
    return;
}
/**
 * 包含有右部，其右部都必须不为空
 **/
void NodePrintor::visit_shift_expr( ShiftExpr* context )
{
    ArithExpr* arith_expr = context->get_arith_expr();
    ShiftExprR* shift_expr = context->get_shift_expr_r();

    assert(arith_expr != NULL);
    //assert(shift_expr != NULL);

    cout << "ShiftExpr:" << context << "\t"
        << "ArithExpr:" << arith_expr << "\t"
        << "ShiftExprR:" << shift_expr << std::endl;

    arith_expr->visit(*this);

    if (shift_expr != NULL)
    {
        shift_expr->visit(*this);
    }

    return;
}
/**
 * 
 **/
void NodePrintor::visit_shift_expr_r( ShiftExprR* context )
{
    ArithExpr* arith_expr = context->get_arith_expr();
    ShiftExprR* shift_expr = context->get_shift_expr_r();

    assert(arith_expr != NULL);

    cout << "ShiftExprR:" << context << "\t"
        << "ArithExpr:" << arith_expr << "\t"
        << "ShiftExprR:" << shift_expr << std::endl;

    //这里代码有些冗余
    arith_expr->visit(*this);

    if (shift_expr != NULL)
    {
        shift_expr->visit(*this);
    }
    return;
}
/**
 * 两个孩子都不能为空
 **/
void NodePrintor::visit_arith_expr( ArithExpr* context )
{
    TermExpr* term = context->get_term();
    ArithExprR* arith_expr = context->get_arith_expr_r();

    assert(term != NULL);
    //assert(arith_expr != NULL);

    cout << "ArithExpr:" << context << "\t"
        << "TermExpr:" << term << "\t"
        << "ArithExprR:" << arith_expr << std::endl;

    term->visit(*this);
    
    if (arith_expr != NULL)
    {
        arith_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_arith_expr_r( ArithExprR* context )
{
    TermExpr* term = context->get_term();
    ArithExprR* arith_expr = context->get_arith_expr_r();

    assert(term != NULL);

    cout << "ArithExprR:" << context << "\t"
        << "TermExpr:" << term << "\t"
        << "ArithExprR:" << arith_expr << std::endl;

    term->visit(*this);

    if (arith_expr != NULL)
    {
        arith_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_term_expr( TermExpr* context )
{
    FactorExpr* factor = context->get_factor();
    TermExprR* term_r = context->get_term_r();

    //因为有右部，所以两者都不能为空
    assert(factor != NULL);
    //assert(term_r != NULL);

    cout << "TermExpr:" << context << "\t"
        << "FactorExpr:" << factor << "\t"
        << "TermExprR:" << term_r << std::endl;

    factor->visit(*this);

    if (term_r != NULL)
    {
        term_r->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_term_expr_r( TermExprR* context )
{
    FactorExpr* factor = context->get_factor();
    TermExprR* term_r = context->get_term_r();

    assert(factor != NULL);

    cout << "TermExprR:" << context << "\t"
        << "FactorExpr:" << factor << "\t"
        << "TermExprR:" << term_r << std::endl;

    factor->visit(*this);

    if (term_r != NULL)
    {
        term_r->visit(*this);
    }
    return;
}
/**
 * factor要注意一下
 **/
void NodePrintor::visit_factor_expr( FactorExpr* context )
{
    FactorExpr* factor = context->get_factor();
    PowerExpr* power = context->get_power_expr();

    assert(factor != NULL || power != NULL);

    cout << "FactorExpr:" << context << "\t"
        << "FactorExpr:" << factor << "\t"
        << "PowerExpr:" << power << std::endl;

    if (factor != NULL)
    {
        factor->visit(*this);
    }
    if (power != NULL)
    {
        power->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_power_expr( PowerExpr* context )
{
    AtomExpr* atom = context->get_atom();
    FactorExpr* factor = context->get_factor();

    assert(atom != NULL);

    cout << "PowerExpr:" << context << "\t"
        << "AtomExpr:" << atom << "\t"
        << "FactorExpr:" << factor << std::endl;

    //factor可以为空
    atom->visit(*this);
    if (factor != NULL)
    {
        factor->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_tuple_expr( TupleExpr* context )
{
    TupleVariableExpr* variable = context->get_variable();

    assert(variable != NULL);

    cout << "TupleExpr:" << context << "\t"
        << "TupleVariableExpr:" << variable << std::endl;

    variable->visit(*this);
    return;
}
/**
 * 
 **/
void NodePrintor::visit_map_expr( MapExpr* context )
{
    MapVariableExpr* variable = context->get_variable();

    assert(variable != NULL);

    cout << "MapExpr:" << context << "\t"
        << "MapVariableExpr:" << variable << std::endl;

    variable->visit(*this);
    return;
}
/**
 * 
 **/
void NodePrintor::visit_tuple_variable_expr( TupleVariableExpr* context )
{
    Expr* t_expr = context->get_expr();
    TupleVariableExpr* variable = context->get_variable();

    assert(t_expr != NULL);
    //可以只有一个参数

    cout << "TupleVariableExpr:" << context << "\t"
        << "Expr:" << t_expr << "\t"
        << "TupleVariableExpr:" << variable << std::endl;

    t_expr->visit(*this);

    if (variable != NULL)
    {
        variable->visit(*this);  //递归调用自己
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_map_variable_expr( MapVariableExpr* context )
{
    Expr* t_expr_l = context->get_expr_l();
    Expr* t_expr_r = context->get_expr_r();
    MapVariableExpr* variable = context->get_variable();

    assert(t_expr_l != NULL);
    assert(t_expr_r != NULL);
    //可以只有一个参数，所以variable可以为空

    cout << "MapVariableExpr:" << context << "\t"
        << "Exprl:" << t_expr_l << "\t"
        << "Exprr:" << t_expr_r << "\t"
        << "MapVariableExpr:" << variable << std::endl;

    t_expr_l->visit(*this);
    t_expr_r->visit(*this);

    if (variable != NULL)
    {
        variable->visit(*this);  //递归
    }
    return;
}
/**
 * number属于常量，不需要想符号表中添加
 **/
void NodePrintor::visit_number_expr( NumberExpr* context )
{
    LongObject* int_value = context->get_int();
    FloatObject* float_value = context->get_float();

    cout << "NumberExpr:" << context << "\t";
    cout << "LongObject:" << int_value << "\t";
    cout << "FloatObject:" << float_value << std::endl;

    if (int_value != NULL)
    {
        int32_t t_value = int_value->get_int();
        cout << "value:" << t_value << std::endl;
    }
    else if (float_value != NULL)
    {
        double t_value = float_value->get_double();
        cout << "value:" << t_value << std::endl;
    }
    else
    {
        THROW_ERROR(ERROR_NO_NUMBER);
    }
    return;
}
/**
 * string也属于常量，也不需要想符号表中添加
 **/
void NodePrintor::visit_string_expr( StringExpr* context )
{
    std::string name = context->get_value();
    StringExpr* string_other = context->get_string_other();

    assert(name.empty() != true);

    cout << "StringExpr:" << context << "\t"
        << "name:" << name << "\t"
        << "StringExpr:" << string_other << std::endl;;

    if (string_other == NULL)
    {
        return;
    }
    string_other->visit(*this);
    return;
}
/**
 * do nothing
 **/
void NodePrintor::visit_keyword_expr( KeyWordExpr* context )
{
    LongObject* value = context->get_value();

    int t_value = value->get_int();

    cout << "KeyWordExpr:" << context << "\t"
        << "LongObject:" << value << "\t"
        << "value:" << t_value << std::endl;;

    return;
}
/**
 * 
 **/
void NodePrintor::visit_name_expr( NameExpr* context )
{
    std::string name = context->get_name();
    AtomExpr* name_expr = context->get_name_expr_r();

    assert(name.empty() != true);

    cout << "MapVariableExpr:" << context << "\t"
        << "NameExpr:" << name << "\t"
        << "MapVariableExpr:" << name_expr << std::endl;

    if (name_expr != NULL)
    {
        name_expr->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_fun_invoke_expr( FunInvokeExpr* context )
{
    ParametersExpr* paras = context->get_paras();

    cout << "FunInvokeExpr:" << context << "\t"
        << "ParametersExpr:" << paras << std::endl;

    //参数可以为空
    if (paras != NULL)
    {
        paras->visit(*this);
    }
    return;
}
/**
 * 
 **/
void NodePrintor::visit_module_invoke_expr( ModuleInvokeExpr* context )
{
    std::string name = context->get_name();
    ModuleInvokeExpr* module_invoke = context->get_module_expr_r();

    assert(name.empty() != NULL);
    assert(module_invoke != NULL);

    cout << "ModuleInvokeExpr:" << context << "\t"
        << "Name:" << name << "\t"
        << "ModuleInvokeExpr:" << module_invoke << std::endl;

    module_invoke->visit(*this);
    return;
}
#endif //EF_DEBUG
/**
 * 
 */
NodeReleasor::NodeReleasor()
{
    return;
}
/**
 * 
 */
NodeReleasor::~NodeReleasor()
{
    return;
}
/**
 * @context 上下文环境
 **/
void NodeReleasor::visit_stmt_seq( StmtSeq* context )
{
    Stmt* t_stmt = context->get_stmt();
    StmtSeq* stmt_seq = context->get_stmt_seq();

    assert(t_stmt != NULL);

    t_stmt->visit(*this);
    delete t_stmt;

    if (stmt_seq != NULL)
    {
        stmt_seq->visit(*this);
        delete stmt_seq;
    }
    return;
}
/**
 * simple_stmt是连续的，不进入作用域
 **/
void NodeReleasor::visit_simple_stmt( SimpleStmt* context )
{
    SmallStmt* small_stmt = context->get_small_stmt();
    SimpleStmt* small_stmt_r = context->get_small_stmt_r();

    assert(small_stmt != NULL);
    //严格的前序遍历
    small_stmt->visit(*this);
    delete small_stmt;

    //递归终止条件
    if (small_stmt_r != NULL)
    {
        small_stmt_r->visit(*this);
        delete small_stmt_r;
    }
    return;
}
/**
 *
 **/
void NodeReleasor::visit_del_stmt( DelStmt* context )
{
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_import_stmt( ImportStmt* context )
{
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_assign_stmt( Assign* context )
{
    Expr* t_expr = context->get_expr();

    DerictAssign* derict_assign = context->get_derict_assign();
    AugAssign* aug_assign = context->get_aug_assign();

    assert(t_expr != NULL);

    if (derict_assign != NULL)
    {
        derict_assign->visit(*this);
        t_expr->visit(*this);
        delete t_expr;
        delete derict_assign;
    }
    else if (aug_assign != NULL)
    {
        t_expr->visit(*this);
        aug_assign->visit(*this);
        delete t_expr;
        delete aug_assign;
    }
    else
    {
        t_expr->visit(*this);
        delete t_expr;
    }
    return;
}
/**
 *
 **/
void NodeReleasor::visit_derict_assign_stmt( DerictAssign* context )
{
    Expr* t_expr = context->get_expr();
    DerictAssign* exprs_r = context->get_exprs_r();

    assert(t_expr != NULL);

    t_expr->visit(*this);
    delete t_expr;

    if (exprs_r != NULL)
    {
        exprs_r->visit(*this);
        delete exprs_r;
    }
    return;
}
/**
 *
 **/
void NodeReleasor::visit_aug_assign_stmt( AugAssign* context )
{
    //对tokenflag不做处理
    Expr* t_expr = context->get_expr();

    assert(t_expr != NULL);

    t_expr->visit(*this);
    delete t_expr;
    return;
}
/**
 * 访问if语句的时候要注意elif与else语句可以为空
 **/
void NodeReleasor::visit_if_stmt( IfStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElifStmt* elif = context->get_elif_stmt();
    ElseStmt* else_ = context->get_else_stmt();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    //严格的前序遍历
    t_expr->visit(*this);
    t_stmt->visit(*this);

    delete t_expr;
    delete t_stmt;

    if (elif != NULL)
    {
        elif->visit(*this);
        delete elif;
    }
    if (else_ != NULL)
    {
        else_->visit(*this);
        delete else_;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_elif_stmt( ElifStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElifStmt* elif = context->get_elif();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);
    
    t_expr->visit(*this);
    t_stmt->visit(*this);
    delete t_expr;
    delete t_stmt;

    //当elif为空时递归结束
    if (elif != NULL)
    {
        elif->visit(*this);
        delete elif;
    }
    return;
}
/**
 * else语句只是简单的访问suite
 **/
void NodeReleasor::visit_else_stmt( ElseStmt* context )
{
    Suite* t_stmt = context->get_suite();

    assert(t_stmt != NULL);

    t_stmt->visit(*this);
    delete t_stmt;
    return;
}
/**
 * else 语句也只是简单的访问，不对else进行访问
 **/
void NodeReleasor::visit_while_stmt( WhileStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    ElseStmt* else_ = context->get_else_stmt();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    t_expr->visit(*this);
    t_stmt->visit(*this);
    delete t_expr;
    delete t_stmt;

    if (else_ != NULL)
    {
        else_->visit(*this);
        delete else_;
    }
    return;
}
/**
 * for statement
 **/
void NodeReleasor::visit_for_stmt( ForStmt* context )
{
    Expr* expr_con = context->get_expr_con();
    Expr* expr_range = context->get_expr_range();
    Suite* stmt = context->get_suite();
    ElseStmt* else_ = context->get_else_stmt();

    assert(expr_con != NULL);
    assert(expr_range != NULL);
    assert(stmt != NULL);

    expr_con->visit(*this);
    expr_range->visit(*this);
    stmt->visit(*this);

    delete expr_con;
    delete expr_range;
    delete stmt;
    
    if (else_ != NULL)
    {
        else_->visit(*this);
        delete else_;
    }
    return;
}
/**
 * finally可以为空
 **/
void NodeReleasor::visit_try_stmt( TryStmt* context )
{
    Suite* stmt_target = context->get_target();
    CatchStmt* stmt_catchs = context->get_catchs();
    Suite* stmt_finally = context->get_finally();

    assert(stmt_target != NULL);
    assert(stmt_catchs != NULL);

    stmt_target->visit(*this);
    stmt_catchs->visit(*this);
    delete stmt_target;
    delete stmt_catchs;
    
    if (stmt_finally != NULL)
    {
        stmt_finally->visit(*this);
        delete stmt_finally;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_catch_stmt( CatchStmt* context )
{
    Expr* t_expr = context->get_expr();
    Suite* t_stmt = context->get_suite();
    CatchStmt* catchs = context->get_catchs();

    assert(t_expr != NULL);
    assert(t_stmt != NULL);

    t_expr->visit(*this);
    t_stmt->visit(*this);
    delete t_expr;
    delete t_stmt;
    //递归结束条件
    if (catchs != NULL)
    {
        catchs->visit(*this);
        delete catchs;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_fun_stmt( FunStmt* context )
{
    ParametersExpr* para = context->get_para();
    Suite* stmt = context->get_suite();

    assert(stmt != NULL);

    if (para != NULL)
    {
        para->visit(*this);
        delete para;
    }
    stmt->visit(*this);
    delete stmt;
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_class_stmt( ClassStmt* context )
{
    Suite* stmt = context->get_suite();

    assert(stmt != NULL);

    stmt->visit(*this);
    delete stmt;
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_suite_stmt( Suite* context )
{
    StmtSeq* stmts = context->get_stmts();
    SimpleStmt* simple_stmt = context->get_simple_stmt();

    assert(stmts != NULL || simple_stmt != NULL);

    if (simple_stmt != NULL)
    {
        simple_stmt->visit(*this);
        delete simple_stmt;
    }
    else if (stmts != NULL)
    {
        stmts->visit(*this);
        delete stmts;
    }
    return;
}
/**
 * 遍历所有参数
 **/
void NodeReleasor::visit_parameters_expr( ParametersExpr* context )
{
    ParameterExprAtom* parameter = context->get_parameter();
    ParametersExpr* other = context->get_other_para();

    assert(parameter != NULL);
    parameter->visit(*this);
    delete parameter;

    if (other != NULL)
    {
        other->visit(*this);
        delete other;
    }
    return;
}
/**
 * 普通参数
 **/
void NodeReleasor::visit_no_star_parameter_expr( NostarParameterExpr* context )
{
    //std::string name = context->get_name();
    AtomExpr* atom = context->get_atom();
    Expr* t_expr = context->get_expr();

    assert(atom != NULL);

    atom->visit(*this);
    delete atom;

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
        delete t_expr;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_tuple_parameter_expr( TupleParameterExpr* context )
{
    Expr* t_expr = context->get_expr();

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
        delete t_expr;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_map_parameter_expr( MapParameterExpr* context )
{
    Expr* t_expr = context->get_expr();

    if (t_expr != NULL)
    {
        t_expr->visit(*this);
        delete t_expr;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_lambda_expr( LambdaExpr* context )
{
    ParametersExpr* parameters = context->get_parameters();
    ConExpr* t_expr = context->get_expr();

    //参数可以为空
    assert(t_expr != NULL);

    if (parameters != NULL)
    {
        parameters->visit(*this);
        delete parameters;
    }
    t_expr->visit(*this);
    delete t_expr;
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_logical_or_expr( LogicalOrExpr* context )
{
    LogicalAndExpr* and_expr = context->get_and_expr();
    LogicalOrExpr* or_expr_r = context->get_or_expr_r();

    assert(and_expr != NULL);

    and_expr->visit(*this);
    delete and_expr;

    if (or_expr_r != NULL)
    {
        or_expr_r->visit(*this);
        delete or_expr_r;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_logical_and_expr( LogicalAndExpr* context )
{
    LogicalNotExpr* not_expr = context->get_not_expr();
    LogicalAndExpr* and_expr = context->get_and_expr_r();

    assert(not_expr != NULL);

    not_expr->visit(*this);
    delete not_expr;

    if (and_expr != NULL)
    {
        and_expr->visit(*this);
        delete and_expr;
    }
    return;
}
/**
 *  逻辑非
 **/
void NodeReleasor::visit_logical_not_expr( LogicalNotExpr* context )
{
    LogicalNotExpr* not_expr = context->get_not_expr();
    LogicalRelExpr* rel = context->get_rel_expr();

    assert(not_expr != NULL || rel != NULL);
    //两者之中必须有一种不为空

    if (not_expr != NULL)
    {
        not_expr->visit(*this);
        delete not_expr;
    }
    if (rel != NULL)
    {
        rel->visit(*this);
        delete rel;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_logical_rel_expr( LogicalRelExpr* context )
{
    SmallExpr* small_expr = context->get_small_expr();
    LogicalRelExprR* rel = context->get_rel_r();

    //必须两者都不为空
    assert(small_expr != NULL);

    small_expr->visit(*this);
    delete small_expr;

    if (rel != NULL)
    {
        rel->visit(*this);
        delete rel;
    }
    return;
}
/**
 * 复合二元比较的右部
 **/
void NodeReleasor::visit_logical_rel_expr_r( LogicalRelExprR* context )
{
    SmallExpr* small_expr = context->get_small_expr();
    LogicalRelExprR* rel = context->get_rel_r();

    assert(small_expr != NULL);
    small_expr->visit(*this);
    delete small_expr;
    
    if (rel != NULL)
    {
        rel->visit(*this);
        delete rel;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_or_expr( OrExpr* context )
{
    XorExpr* xor_expr = context->get_xor_expr();
    OrExpr* or_expr = context->get_or_expr_r();

    assert(xor_expr != NULL);

    xor_expr->visit(*this);
    delete xor_expr;

    if (or_expr != NULL)
    {
        or_expr->visit(*this);
        delete or_expr;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_xor_expr( XorExpr* context )
{
    AndExpr* and_expr = context->get_and_expr();
    XorExpr* xor_expr = context->get_xor_expr_r();

    assert(and_expr != NULL);

    and_expr->visit(*this);
    delete and_expr;

    if (xor_expr != NULL)
    {
        xor_expr->visit(*this);
        delete xor_expr;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_and_expr( AndExpr* context )
{
    ShiftExpr* shift_expr = context->get_shift_expr();
    AndExpr* and_expr = context->get_and_expr_r();

    assert(shift_expr != NULL);
    shift_expr->visit(*this);
    delete shift_expr;

    if (and_expr != NULL)
    {
        and_expr->visit(*this);
        delete and_expr;
    }
    return;
}
/**
 * 包含有右部，其右部都必须不为空
 **/
void NodeReleasor::visit_shift_expr( ShiftExpr* context )
{
    ArithExpr* arith_expr = context->get_arith_expr();
    ShiftExprR* shift_expr = context->get_shift_expr_r();

    assert(arith_expr != NULL);

    arith_expr->visit(*this);
    delete arith_expr;

    if (shift_expr != NULL)
    {
        shift_expr->visit(*this);
        delete shift_expr;
    }

    return;
}
/**
 * 
 **/
void NodeReleasor::visit_shift_expr_r( ShiftExprR* context )
{
    ArithExpr* arith_expr = context->get_arith_expr();
    ShiftExprR* shift_expr = context->get_shift_expr_r();

    assert(arith_expr != NULL);

    arith_expr->visit(*this);
    delete arith_expr;

    if (shift_expr != NULL)
    {
        shift_expr->visit(*this);
        delete shift_expr;
    }
    return;
}
/**
 * 两个孩子都不能为空
 **/
void NodeReleasor::visit_arith_expr( ArithExpr* context )
{
    TermExpr* term = context->get_term();
    ArithExprR* arith_expr = context->get_arith_expr_r();

    assert(term != NULL);

    term->visit(*this);
    delete term;
    
    if (arith_expr != NULL)
    {
        arith_expr->visit(*this);
        delete arith_expr;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_arith_expr_r( ArithExprR* context )
{
    TermExpr* term = context->get_term();
    ArithExprR* arith_expr = context->get_arith_expr_r();

    assert(term != NULL);

    term->visit(*this);
    delete term;

    if (arith_expr != NULL)
    {
        arith_expr->visit(*this);
        delete arith_expr;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_term_expr( TermExpr* context )
{
    FactorExpr* factor = context->get_factor();
    TermExprR* term_r = context->get_term_r();

    assert(factor != NULL);

    factor->visit(*this);
    delete factor;

    if (term_r != NULL)
    {
        term_r->visit(*this);
        delete term_r;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_term_expr_r( TermExprR* context )
{
    FactorExpr* factor = context->get_factor();
    TermExprR* term_r = context->get_term_r();

    assert(factor != NULL);

    factor->visit(*this);
    delete factor;

    if (term_r != NULL)
    {
        term_r->visit(*this);
        delete term_r;
    }
    return;
}
/**
 * factor要注意一下
 **/
void NodeReleasor::visit_factor_expr( FactorExpr* context )
{
    FactorExpr* factor = context->get_factor();
    PowerExpr* power = context->get_power_expr();

    assert(factor != NULL || power != NULL);

    if (factor != NULL)
    {
        factor->visit(*this);
        delete factor;
    }
    if (power != NULL)
    {
        power->visit(*this);
        delete power;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_power_expr( PowerExpr* context )
{
    AtomExpr* atom = context->get_atom();
    FactorExpr* factor = context->get_factor();

    assert(atom != NULL);

    atom->visit(*this);
    delete atom;

    if (factor != NULL)
    {
        factor->visit(*this);
        delete factor;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_tuple_expr( TupleExpr* context )
{
    TupleVariableExpr* variable = context->get_variable();

    assert(variable != NULL);
    variable->visit(*this);
    delete variable;
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_map_expr( MapExpr* context )
{
    MapVariableExpr* variable = context->get_variable();

    assert(variable != NULL);

    variable->visit(*this);
    delete variable;
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_tuple_variable_expr( TupleVariableExpr* context )
{
    Expr* t_expr = context->get_expr();
    TupleVariableExpr* variable = context->get_variable();

    assert(t_expr != NULL);

    t_expr->visit(*this);
    delete t_expr;

    if (variable != NULL)
    {
        variable->visit(*this);  //递归调用自己
        delete variable;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_map_variable_expr( MapVariableExpr* context )
{
    Expr* t_expr_l = context->get_expr_l();
    Expr* t_expr_r = context->get_expr_r();
    MapVariableExpr* variable = context->get_variable();

    assert(t_expr_l != NULL);
    assert(t_expr_r != NULL);

    t_expr_l->visit(*this);
    t_expr_r->visit(*this);
    delete t_expr_l;
    delete t_expr_r;

    if (variable != NULL)
    {
        variable->visit(*this);  //递归
        delete variable;
    }
    return;
}
/**
 * number属于常量，不需要想符号表中添加
 **/
void NodeReleasor::visit_number_expr( NumberExpr* context )
{
    return;
}
/**
 * string也属于常量，也不需要想符号表中添加
 **/
void NodeReleasor::visit_string_expr( StringExpr* context )
{
    StringExpr* string_other = context->get_string_other();

    if (string_other == NULL)
    {
        return;
    }
    string_other->visit(*this);
    delete string_other;
    return;
}
/**
 * do nothing
 **/
void NodeReleasor::visit_keyword_expr( KeyWordExpr* context )
{
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_name_expr( NameExpr* context )
{
    AtomExpr* name_expr = context->get_name_expr_r();

    if (name_expr != NULL)
    {
        name_expr->visit(*this);
        delete name_expr;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_fun_invoke_expr( FunInvokeExpr* context )
{
    ParametersExpr* paras = context->get_paras();

    if (paras != NULL)
    {
        paras->visit(*this);
        delete paras;
    }
    return;
}
/**
 * 
 **/
void NodeReleasor::visit_module_invoke_expr( ModuleInvokeExpr* context )
{
    ModuleInvokeExpr* module_invoke = context->get_module_expr_r();

    assert(module_invoke != NULL);

    module_invoke->visit(*this);
    delete module_invoke;
    return;
}

EF_NAMESPACE_END
