/*-------------------------------------------------------------------
 * Purpose:
 *         Parser.h 做语法分析
 *          Parser与设计模式的纠纷，使用词法分析器作为构造函数的好处使parser
 *          更好的与其它部分分离，以前使用的string与file明确的分工，这使得在
 *          scanner里面需要明确分工，在这里也需要明确的分工，从而出现了
 *          代码冗余。结论：使用更高级的产物要比低级的产物好，这是封装的必然
 *          
 *          该词法分析不能完成像C++这样能识别< <到底是减号，还是模板开始标志
 *          这样具有回溯特性的文法
 * Time:
 *         2011年12月1日 21:15:18
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _PARSER_H_2011_12_1_lisency
#define _PARSER_H_2011_12_1_lisency

#include "Scanner.h"
#include "Object.h"
#include "Node.h"
//#include "SymbolTable.h"

#include <stack>
#include <string>

EF_NAMESPACE_BEGIN

/**
 * 有没有留接口的必要呢
 **/
class Parser
    :public Base
{
public:
    /**
     * 
     */
    virtual ~Parser() = 0;
protected:
    /**
    * 开始这里直接传入文件名，但现在我们传入词法分析器
    * @scanner词法分析器
    **/
    Parser(Scanner &t_scanner);
    Scanner& scanner;//负责分词
    std::string file_path;
private:
};

/**
 *  本程序使用的语法分析器
 *  虽然保留了接口，但是以后用不用还不清楚
 *  程序可以有多个文件，以模块封装
 *    module            ::= file_input
 *    file_input        ::= stmt file_input | stmt
 *    stmt            ::= simple_stmt | compound_stmt
 *    simple_stmt        ::= small_stmt simple_stmt
 *    compound_stmt    ::= if_stmt | while_stmt | for_stmt | try_stmt 
 *                          | fundef_stmt | classdef_stmt
 **/
class EFParser
    :public Parser
{
public:
    /**
    * 
    **/
    EFParser(Scanner &scanner);
    /**
    * 
    **/
    virtual ~EFParser();
    /**
    *  向前继续分析
    **/
    void move();
    /**
    *  查看是否匹配
    *  若没有匹配跑出异常
    **/
    bool match(TokenFlag token_flag);
    /**
    * 根据错误ID抛出异常
    **/
    void throw_error(int error_id);
    /**
    * file_input -> StmtSeq ENDMARKER
    * 一个文件一个模块
    * 返回语法树的根节点
    **/
    Stmt* module();
    /**
    * 查找更多的stmt
    *   file_input -> StmtSeq ENDMARKER
    *           StmtSeq
    *           /     \
    *       stmt    StmtSeq
    **/
    StmtSeq* stmts();
    /**
    * 匹配一个stmt
    * stmt -> simple_stmt | compound_stmt | suite
    **/
    Stmt* stmt();
    /**
    * 返回一个简单语句
    * simple_stmt -> small_stmt (';' small_stmt)*[';'] NEWLINE
    **/
    SimpleStmt* simple_stmt();
    /**
    * 返回一个小语句
    * small_stmt -> assign |
    *            augassign |
    *             del_stmt |
    *          import_stmt
    **/
    SmallStmt* small_stmt();
    /**
    * 匹配SimpleStmt后面的部分
    * SmallStmtList -> (';' small_stmt)*
    **/
    SimpleStmt* small_stmt_list();
    /**
    * 删除语句
    **/
    DelStmt* del_stmt();
    /**
    * 导入语句
    **/
    ImportStmt* import_stmt();
    /**
    * 包含有关键字的语句，及赋值语句
    **/
    Assign* assign_stmt();
    /**
    * 返回一个直接赋值语句节点
    * derict_assign -> ('=' expr)*
    *                   derict_assign
    *                    /         \
    *                 expr  (=)    derict_assign
    **/
    DerictAssign* derict_assign();
    /**
    *   augassign -> augmentassign expr
    *                augassign
    *               /        \
    *     assign_operator    expr
    **/
    AugAssign* aug_assign();
    /**
    * 返回一个复合语句
    * compound_stmt -> if_stmt |
    *               while_stmt |
    *                 for_stmt |
    *                 try_stmt |
    *              fundef_stmt |
    *            classdef_stmt 
    **/
    CompoundStmt* compound_stmt();
    /**
    * 构造if语句节点
    * if_stmt -> 'if' expr ':' suite 
    *         ('elif' expr ';' suite) *
    *             ['else' ':' suite]
    *
    *                    if
    *                /    |    \      \
    *               /     |     \       \
    *            expr  stmt     elif     else
    *                        /  |  \
    *                我们先留下else语句
    **/
    IfStmt* if_stmt();
    /**
    * while语句
    **/
    WhileStmt* while_stmt();
    /**
    *
    **/
    ElifStmt* elif_stmt();
    /**
    *        
    **/
    ElseStmt* else_stmt();
    /**
    *        
    **/
    ForStmt* for_stmt();
    /**
    *        
    **/
    TryStmt* try_stmt();
    /**
    *        
    **/
    CatchStmt* catch_stmt();
    /**
    *        
    **/
    FunStmt* fun_stmt();
    /**
    *        
    **/
    ClassStmt* cla_stmt();
    /**
    *        
    **/
    Suite* suite();
    /**
    *        
    **/
    ParametersExpr* parameters();
    /**
    * 一个以逗号分割的参数
    **/
    ParameterExprAtom* atom_para();
    /**
    * 是否为一个表达式
    * expr -> con_expr | fun_invoke | module_invoke | simple_expr
    **/
    Expr* expr();
    /**
    * conditional expression
    **/
    ConExpr* con_expr();
    /**
    *        
    **/
    LambdaExpr* lambda_expr();
    /**
    *        
    **/
    LogicalOrExpr* logical_or_expr();
    /**
    *        
    **/
    LogicalOrExpr* logical_or_expr_r();
    /**
    *        
    **/
    LogicalAndExpr* logical_and_expr();
    /**
    *        
    **/
    LogicalAndExpr* logical_and_expr_r();
    /**
    *        
    **/
    LogicalNotExpr* not_expr();
    /**
    *        
    **/
    LogicalRelExpr* comparison();
    /**
    *       
    **/
    LogicalRelExprR* comparison_r();
    /**
    *        
    **/
    OrExpr* or_expr();
    /**
    *        
    **/
    OrExpr* or_expr_r();
    /**
    *        
    **/
    XorExpr* xor_expr();
    /**
    *        
    **/
    XorExpr* xor_expr_r();
    /**
    *        
    **/
    AndExpr* and_expr();
    /**
    *        
    **/
    AndExpr* and_expr_r();
    /**
    *        
    **/
    ShiftExpr* shift_expr();
    /**
    *        
    **/
    ShiftExprR* shift_expr_r();
    /**
    *        
    **/
    ArithExpr* arith_expr();
    /**
    *        
    **/
    ArithExprR* arith_expr_r();
    /**
    *        
    **/
    TermExpr* term_expr();
    /**
    *        
    **/
    TermExprR* term_expr_r();
    /**
    *        
    **/
    FactorExpr* factor();
    /**
    *        
    **/
    PowerExpr* power();
    /**
    *        
    **/
    AtomExpr* atom();
    /**
    *       
    **/
    TupleExpr* tuple_expr();
    /**
    *       
    **/
    TupleVariableExpr* tuple_variable_expr();
    /**
    *       
    **/
    TupleVariableExpr* tuple_variable_expr_r();
    /**
    *       
    **/
    MapExpr* map_expr();
    /**
    *       
    **/
    MapVariableExpr* map_variable_expr();
    /**
    *       
    **/
    MapVariableExpr* map_variable_expr_r();
    /**
    *       
    **/
    NumberExpr* number_expr();
    /**
    *       
    **/
    StringExpr* string_expr();
    /**
    *       
    **/
    KeyWordExpr* keyword_expr();
    /**
    *       
    **/
    NameExpr* name_expr();
    /**
    *        
    **/
    FunInvokeExpr* fun_invoke();
    /**
    *        
    **/
    ModuleInvokeExpr* module_invoke();
protected:
    Token *look;                        //向前看词法单元
    /**
    * 该词素是否是一个比较操作符
    **/
    inline bool is_com_op(Token *token)
    {
        TokenFlag token_flag = token->id;

        switch (token_flag)
        {
        case LESS:
        case GREATER:
        case EQEQUAL:
        case LESSEQUAL:
        case NOTEQUAL:
        case GREATEREQUAL:
            return true;
        default:
            return false;
        }
        return false;
    }
    /**
    * 是否是自增操作符
    **/
    inline bool is_aug_assign(Token* token)
    {
        TokenFlag token_flag = token->id;

        switch (token_flag)
        {
        case PLUSEQUAL:
        case MINEQUAL:
        case STAREQUAL:
        case SLASHEQUAL:
        case PERCENTEQUAL:
        case AMPEREQUAL:
        case VBAREQUAL:
        case CIRCUMFLEXEQUAL:
        case LEFTSHIFTEQUAL:
        case RIGHTSHIFTEQUAL:
        case DOUBLESTAREQUAL:
        case DOUBLESLASHEQUAL:
            return true;
        default:
            return false;
        }
        return false;
    }
private:
};

EF_NAMESPACE_END

#endif // _PARSER_H_2011_12_1_lisency

