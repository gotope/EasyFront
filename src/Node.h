/*-------------------------------------------------------------------
 * Purpose:
 *         Node.h 具体语法树的节点
 *         使用interpreter模式
 * Time:
 *         2011年12月13日 22:04:49
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _NODE_H_2011_12_13_lisency
#define _NODE_H_2011_12_13_lisency

#include "Base.h"
#include "Token.h"
//#include "Visitor.h"
#include "Object.h"
#include <list>
#include <stdint.h>

EF_NAMESPACE_BEGIN

class Visitor;
class Node;
class Stmt;
class StmtSeq;
class SmallStmt;
class SimpleStmt;
class DelStmt;
class ImportStmt;
class AssignBase;
class Assign;
class DerictAssign;
class AugAssign;
class CompoundStmt;
class IfStmt;
class ElifStmt;
class ElseStmt;
class WhileStmt;
class ForStmt;
class TryStmt;
class CatchStmt;
class FunStmt;
class ClassStmt;
class Suite;
class Expr;
class ParameterExprAtom;
class ParametersExpr;
class NostarParameterExpr;
class TupleParameterExpr;
class MapParameterExpr;
class ConExpr;
class LambdaExpr;
class LogicalExpr;
class LogicalOrExpr;
class LogicalAndExpr;
class LogicalNotExpr;
class LogicalRelExpr;
class LogicalRelExprR;
class SmallExpr;
class OrExpr;
class XorExpr;
class AndExpr;
class ShiftExpr;
class ShiftExprR;
class ArithExpr;
class ArithExprR;
class TermExpr;
class TermExprR;
class FactorExpr;
class PowerExpr;
class AtomExpr;
class TupleExpr;
class MapExpr;
class VariablesExpr;
class TupleVariableExpr;
class MapVariableExpr;
class NumberExpr;
class StringExpr;
class KeyWordExpr;
class NameExpr;
class FunInvokeExpr;
class ModuleInvokeExpr;
/**
 * 抽象语法树的节点
 * 现在的问题是，并不是每个节点都有行号和列号信息
 **/
class Node
    :public Base
{
public:
    /**
    *  
    **/
    virtual ~Node() = 0;
    /**
    *  由visitor完成对语法树的访问工作
    **/
    virtual void visit(Visitor& visitor) = 0;
    /**
    * 得到列号
    **/
    inline int32_t get_row()
    {
        return row;
    }
    /**
    * 得到行号
    **/
    inline int32_t get_col()
    {
        return col;
    }
    /**
     * 设置文件路径，这只对打印有帮助
     */
    static void set_file_path(std::string& t_file_path)
    {
        file_path = t_file_path;
        return;
    }
    /**
    * 得到文件路径
    **/
    static std::string get_file_path()
    {
        return file_path;
    }
protected:
    /**
    * 抽象语法树的节点
    * 非必要提供默认构造函数。这么大的类继承，没有提供默认构造函数，限制
    * 每一个节点都有行号和列号
    * @row 存储行号，若为-1说明该节点没有存储行号和列号
    * @col 存储列号，
    **/
    Node(int32_t t_row,int32_t t_col);
private:
    int row;
    int col;
    static std::string file_path;
    //存该语法树的文件名，这样有利也有弊，对多文件，我们无能为力了
};

/**
 *  stmt包含所有的语句
 *   stmt -> simple_stmt | compound_stmt
 **/
class Stmt
    :public Node
{
public:
    /**
    *
    **/
    virtual ~Stmt() = 0;
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
protected:
    /**
    *
    **/
    Stmt(int32_t t_row,int32_t t_col);
private:
};
/**
 * 语句序列
 * StmtSeq -> stmt*
 *         StmtSeq
 *        /      \
 *            Stmt   StmtSeq
 **/
class StmtSeq
    :public Stmt
{
public:
    /**
    *  StmtSeq的节点行号和列好信息是节点stmt的行号和列号信息
    * 两个语句连接之后形成一个语法树
    **/
    StmtSeq(Stmt *t_stmt,StmtSeq *t_stmt_seq);
    /**
    *
    **/
    ~StmtSeq();
    /**
    *  对语句序列，一般visitor只是简单的访问
    **/
    virtual void visit(Visitor& visitor);
    /**
    * 返回左孩子stmt
    **/
    inline Stmt* get_stmt()
    {
        return stmt;
    }
    /**
    * 返回右孩子，一个语句序列
    **/
    inline StmtSeq* get_stmt_seq()
    {
        return stmt_seq;
    }
protected:
    Stmt* stmt;
    StmtSeq* stmt_seq;
private:
};
/**
 *   small_stmt -> assign | del_stmt | import_stmt
 **/
class SmallStmt
    :public Stmt
{
public:
    /**
    * 抽象类，析构函数什么都不做
    **/
    virtual ~SmallStmt() = 0;
    /**
    * visitor对访问者无用
    **/
    virtual void visit(Visitor& visitor);
protected:
    /**
    *
    **/
    SmallStmt(int32_t t_row,int32_t t_col);
private:
};
/**
 *   SimpleStmt -> small_stmt (';' small_stmt)* [';'] NEWLINE
 *                   SimpleStmt
 *                /             \
 *           small_stmt      SmallStmtList
 **/
class SimpleStmt
    :public SmallStmt
{
public:
    /**
    * small_stmt有两个节点，以圆括号分割，构造函数分别传入两个节点
    **/
    SimpleStmt(SmallStmt* t_small_stmt,SimpleStmt* t_small_stmt_r);
    /**
    *
    **/
    ~SimpleStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    * 得到左孩子  
    **/
    inline SmallStmt* get_small_stmt()
    {
        return small_stmt;
    }
    /**
    * 得到剩余语句序列
    **/
    inline SimpleStmt* get_small_stmt_r()
    {
        return small_stmt_r;
    }
protected:
    SmallStmt* small_stmt;
    SimpleStmt* small_stmt_r;
private:
};
/**
 * del_stmt -> 'del' NAME
 **/
class DelStmt
    :public SmallStmt
{
public:
    /**
    *
    **/
    DelStmt(Token* token);
    /**
    *
    **/
    virtual ~DelStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   返回删除对象
    **/
    inline std::string get_name()
    {
        return name;
    }
protected:
    std::string name;
private:
};
/**
 * import -> 'import' NAME
 **/
class ImportStmt
    :public SmallStmt
{
public:
    /**
    * 仅有一个参数
    **/
    ImportStmt(Token* token);
    /**
    *
    **/
    virtual ~ImportStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   返回要导入的模块对象
    **/
    inline std::string get_name()
    {
        return name;
    }
protected:
    std::string name;
private:
};
/**
 * 抽象类
 **/
class AssignBase
    :public SmallStmt
{
public:
    /**
    *
    **/
    ~AssignBase();
    /**
    *        
    **/
    virtual void visit(Visitor& visitor);
protected:
	/**
    *
    **/
    AssignBase(int32_t t_row,int32_t t_col);
private:
};

/**
 *   Assign -> expr (derict_assign | augassign)
 *               Assign
 *             /       \
 *           expr     Assign(augassign or derict_assign)
 **/
class Assign
    :public AssignBase
{
public:
	/**
    *  @t_expr
    *  @assign_r赋值语句的右部
    **/
    Assign(Expr* t_expr,DerictAssign* t_assign_r = NULL);
	/**
    *  @t_expr
    *  @assign_r赋值语句的右部
    **/
    Assign(Expr* t_expr,AugAssign* t_assign_r);
    /**
    *
    **/
    ~Assign();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *  
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
    /**
     * 
     */
    inline DerictAssign* get_derict_assign()
    {
        return derict_assign;
    }
    /**
     * 
     */
    inline AugAssign* get_aug_assign()
    {
        return aug_assign;
    }
protected:
    Expr* expr;
    DerictAssign* derict_assign;
    AugAssign* aug_assign;
private:
};
/**
 *  derict_assign -> ('=' expr)*
 *                   derict_assign
 *                    /         \
 *                 expr  (=)    derict_assign
 **/
class DerictAssign
    :public AssignBase
{
public:
    /**
    *
    **/
    DerictAssign(Expr* t_expr,DerictAssign* t_exprs_r);
    /**
    *
    **/
    ~DerictAssign();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
    /**
    *   
    **/
    inline DerictAssign* get_exprs_r()
    {
        return exprs_r  ;
    }
protected:
    Expr* expr;
    DerictAssign* exprs_r;    //右部出现的所有符号,当此项为NULL时语法树结束
private:
};
/**
 *   augassign -> augmentassign expr
 *               augassign
 *               /       \
 *     assign_operator    expr
 **/
class AugAssign
    :public AssignBase
{
public:
    /**
    *  将t_token的id保存到token_flag中
    **/
    AugAssign(Token* t_token,Expr* t_expr);
    /**
    *
    **/
    virtual ~AugAssign();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   
    **/
    inline TokenFlag get_token_flag()
    {
        return token_flag;
    }
    /**
    *   
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
protected:
    TokenFlag token_flag;       //保存所有自增符号的标志符号
    Expr* expr;                 //右部
private:
};
/**
 *  又是一个抽象类
 *   compound_stmt -> if_stmt |
 *                    while_stmt |
 *                    for_stmt |
 *                    try_stmt |
 *                    fundef_stmt |
 *                    classdef_stmt
 **/
class CompoundStmt
    :public Stmt
{
public:
    /**
    *
    **/
    ~CompoundStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
protected:
    /**
    *
    **/
    CompoundStmt(int32_t t_row,int32_t t_col);
private:
};

/**
 *  构造if语句节点
 *                    if
 *                /    |    \      \
 *               /     |     \       \
 *            expr  stmt     elif     else
 *                        /  |  \
 *                我们先留下else语句
 **/
class IfStmt
    :public CompoundStmt
{
public:
    /**
    * 'if' conditional_expr ':' suite 
    * ('elif' conditional_expr ':' suite)['else'':'suite]
    * @expr->conditional_expr
    * @stmt->remain statement
    **/
    IfStmt(Expr *t_expr,Suite *t_stmt,ElifStmt* t_elif,
        ElseStmt* t_else_);
    /**
    *
    **/
    virtual ~IfStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    * 
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
    /**
    * 
    **/
    inline Suite* get_suite()
    {
        return stmt;
    }
    /**
    *        
    **/
    inline ElifStmt* get_elif_stmt()
    {
        return elif;
    }
    /**
    *        
    **/
    inline ElseStmt* get_else_stmt()
    {
        return else_;
    }
protected:
    Expr* expr;
    Suite* stmt;
    ElifStmt* elif;    //可以为空
    ElseStmt* else_;//可以为空
private:
};
/**
 *                elif
 *            /      |        \
 *        expr    suite    elif
 **/
class ElifStmt
    :public CompoundStmt
{
public:
    /**
    *
    **/
    ElifStmt(Expr* t_expr,Suite* t_stmt,ElifStmt* t_elif);
    /**
    *
    **/
    ~ElifStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
    /**
    *        
    **/
    inline Suite* get_suite()
    {
        return stmt;
    }
    /**
    *        
    **/
    inline ElifStmt* get_elif()
    {
        return elif;
    }
protected:
    Expr* expr;
    Suite* stmt;
    ElifStmt* elif;
private:
};
/**
 * 
 **/
class ElseStmt
    :public CompoundStmt
{
public:
    /**
    *
    **/
    ElseStmt(Suite* t_stmt);
    /**
    *
    **/
    virtual ~ElseStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline Suite* get_suite()
    {
        return stmt;
    }
protected:
    Suite* stmt;
private:
};
/**
 *  while子节点
 *                  while
 *                /   |        \
 *            expr   stmt    Else
 **/
class WhileStmt
    :public CompoundStmt
{
public:
    /**
    *  while ::= 'while' conditional_expr ':' suite ['else' ':'suite]
    **/
    WhileStmt(Expr *t_expr,Suite *t_stmt,ElseStmt* t_else_ = NULL);
    /**
    *
    **/
    ~WhileStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
    /**
    *   
    **/
    inline Suite* get_suite()
    {
        return stmt;
    }
    /**
    *        
    **/
    inline ElseStmt* get_else_stmt()
    {
        return else_;
    }
protected:
    Expr* expr;
    Suite* stmt;
    ElseStmt* else_;    //可以为空
private:
};
/**
 *    for_smt -> 'for' expr 'in' expr ':' suite ['else' ':' suite]
 *                  for
 *            /     |     \        \
 *         expr    expr  stmt   else
 **/
class ForStmt
    :public CompoundStmt
{
public:
    /**
    *
    **/
    ForStmt(Expr* t_expr_con,Expr* t_expr_range,Suite* t_stmt,
        ElseStmt* t_else_);
    /**
    *
    **/
    virtual ~ForStmt();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline Expr* get_expr_con()
    {
        return expr_con;
    }
    /**
    *        
    **/
    inline Expr* get_expr_range()
    {
        return expr_range;
    }
    /**
    * 
    **/
    inline Suite* get_suite()
    {
        return stmt;
    }
    /**
    *
    **/
    inline ElseStmt* get_else_stmt()
    {
        return else_;
    }
protected:
    Expr* expr_con;    //for循环中的条件语句
    Expr* expr_range;        //范围
    Suite* stmt;
    ElseStmt* else_;            //可以为空
private:
};
/**
 *        try_stmt -> 'try' ':' suite 
 *                catch_clase+ ['finally' ':' suite]
 *                        try
 *                /        |        \
 *            stmt    catch    stmt(finally)
 **/
class TryStmt
    :public CompoundStmt
{
public:
    /**
    *
    **/
    TryStmt(Suite* t_stmt_target,CatchStmt* t_stmt_catchs,
        Suite* t_stmt_finally);
    /**
    *
    **/
    virtual ~TryStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline Suite* get_target()
    {
        return stmt_target;
    }
    /**
    *        
    **/
    inline CatchStmt* get_catchs()
    {
        return stmt_catchs;
    }
    /**
    *        
    **/
    inline Suite* get_finally()
    {
        return stmt_finally;
    }
protected:
    Suite* stmt_target;    //try语句的目标
    CatchStmt* stmt_catchs;    //catch
    Suite* stmt_finally;
private:
};
/**
 *        catch -> 'catch' [expr ] ':' suite
 *                    catch
 *            /        |        \
 *         expr        stmt    catch
 **/
class CatchStmt
    :public CompoundStmt
{
public:
    /**
    *
    **/
    CatchStmt(Expr* t_expr,Suite* t_stmt,CatchStmt* t_catchs);
    /**
    *
    **/
    virtual ~CatchStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *  
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
    /**
    *        
    **/
    inline Suite* get_suite()
    {
        return stmt;
    }
    /**
    * 
    **/
    inline CatchStmt* get_catchs()
    {
        return catchs;
    }
protected:
    Expr* expr;        //可以为空
    Suite* stmt;
    CatchStmt* catchs;    //最后一个为空
private:
};
/**
 *   fundef_stmt -> 'fun' NAME [parameters] ':' suite
 *                    fundef_stmt
 *                /        |        \
 *            name    parameters    stmt
 **/
class FunStmt
    :public CompoundStmt
{
public:
    /**
    *
    **/
    FunStmt(Token* t_token,ParametersExpr* t_para,Suite* t_stmt);
    /**
    *
    **/
    virtual ~FunStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    * 
    **/
    inline std::string get_name()
    {
        return name;
    }
    /**
    *        
    **/
    inline ParametersExpr* get_para()
    {
        return para;
    }
    /**
    * 
    **/
    inline Suite* get_suite()
    {
        return stmt;
    }
protected:
    std::string name;
    ParametersExpr* para;
    Suite* stmt;
private:
};
/**
 *  先假设没有继承机制，即exprlist没有
 *                classdef_stmt -> 'class' NAME ':' suite
 *               classdef_stmt
 *                /        \
 *            NAME        suite
 **/
class ClassStmt
    :public CompoundStmt
{
public:
    /**
    *
    **/
    ClassStmt(Token* t_token,Suite* t_stmt);
    /**
    *
    **/
    ~ClassStmt();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   
    **/
    inline std::string get_name()
    {
        return name;
    }
    /**
    *   
    **/
    inline Suite* get_suite()
    {
        return stmt;
    }
protected:
    std::string name;
    Suite* stmt;
private:
};
/**
 *  因为SimpleStmt本身就是一个suite，这里提供两个构造函数，方便
 *                 对SimpleStmt的构造
 *   suite -> simple_stmt | NEWLINE INDENT stmt + DEDENT
 **/
class Suite
    :public Stmt
{
public:
    /**
    *  @t_stmts 是一个复合语句的序列
    **/
    Suite(StmtSeq* t_stmts);
    /**
    *  @t_simple_stmt 一个简单语句
    **/
    Suite(SimpleStmt* t_simple_stmt);
    /**
    * 
    **/
    virtual ~Suite();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   
    **/
    inline StmtSeq* get_stmts()
    {
        return stmts;
    }
    /**
    *        
    **/
    inline SimpleStmt* get_simple_stmt()
    {
        return simple_stmt;
    }
protected:
    StmtSeq* stmts;
    SimpleStmt* simple_stmt;
private:
};
/**
 *  这又是一个抽象类，OK
 *   Expr -> con_expr | parameters | small_expr
 *   这里实现的时候并没有按照常规，而是我们简单的变化了一下，因为con_expr包含
 *   smal_expr，所以small_expr被嵌套在了con_expr中，关于这个类继承的方式，纠结
 *   了好多天
 *   parameters这个只有在函数定义（调用）的时候会用到，所以不必担心其会影响
 *   其它，关于这个不随整体的实现确实让人揪心，它破坏了parser的整体性
 **/
class Expr
    :public Node
{
public:
    /**
    *
    **/
    virtual ~Expr() = 0;
    /**
    *
    **/
    virtual void visit(Visitor& visitor) = 0;
protected:
    /**
    *
    **/
    Expr(int32_t t_row,int32_t t_col);
private:
};
/**
 *  这也是一个抽象类
 *   ParameterExprAtom -> (nostart_parameter | tuple_parameter | map_parameter)
 **/
class ParameterExprAtom
    :public Expr
{
public:
    /**
    *
    **/
    virtual ~ParameterExprAtom() = 0;
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
protected:
    /**
    *
    **/
    ParameterExprAtom(int32_t t_row,int32_t t_col);
private:
};
/**
 *   ParameterExpr -> ParameterExprAtom (',' ParameterExprAtom)*
 *               ParameterExpr
 *             /            \
 *  ParametersExprAtom     ParametersExpr
 **/
class ParametersExpr
    :public ParameterExprAtom
{
public:
    /**
    *
    **/
    ParametersExpr(ParameterExprAtom* t_parameter,
        ParametersExpr* other_para);
    /**
    *
    **/
    virtual ~ParametersExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   
    **/
    inline ParameterExprAtom* get_parameter()
    {
        return parameter;
    }
    /**
    *        
    **/
    inline ParametersExpr* get_other_para()
    {
        return others;
    }
protected:
    ParameterExprAtom* parameter;
    ParametersExpr* others;
private:
};
/**
 *  通用参数
 *   NostartParameterExpr -> atom ['=' expr]
 *           NostarParameterExpr
 *             /           \
 *         atom          expr
 **/
class NostarParameterExpr
    :public ParameterExprAtom
{
public:
    /**
    *
    **/
    NostarParameterExpr(AtomExpr* t_atom,Expr* t_expr);
    /**
    *
    **/
    virtual ~NostarParameterExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *
    **/
    inline AtomExpr* get_atom()
    {
        return atom;
    }
    /**
    *
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
protected:
    AtomExpr* atom;
    Expr* expr;             //可以为空
private:
};
/**
 *   TupleParameterExpr -> '*' NAME ['=' expr]
 *                   TupleParameterExpr
 *                     /           \
 *                   NAME        expr
 **/
class TupleParameterExpr
    :public ParameterExprAtom
{
public:
    /**
    *
    **/
    TupleParameterExpr(Token* t_token,Expr* t_expr);
    /**
    *
    **/
    virtual ~TupleParameterExpr();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline std::string get_name()
    {
        return name;
    }
    /**
    *        
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
protected:
    std::string name;
    Expr* expr;
private:
};
/**
 *   MapParameterExpr -> '**' NAME ['=' expr]
 *               MapParameterExpr
 *               /           \
 *            name           expr
 **/
class MapParameterExpr
    :public ParameterExprAtom
{
public:
    /**
    *
    **/
    MapParameterExpr(Token* t_token,Expr* t_expr);
    /**
    *
    **/
    virtual ~MapParameterExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline std::string get_name()
    {
        return name;
    }
    /**
    *        
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
protected:
    std::string name;
    Expr* expr;
private:
};
/**
 *  这也是一个抽象类
 *        语法树中并没有包含lambda表达式，但是在程序中实际上是包含关系，这个
 *       矛盾希望在后面的工作中能够解决掉
 *    con_expr -> logical_or_expr | lambda_expr
 **/
class ConExpr
    :public Expr
{
public:
    /**
    *
    **/
    virtual ~ConExpr() = 0;
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
protected:
    /**
    *
    **/
    ConExpr(int32_t t_row,int32_t t_col);
private:
};
/**
 * lambda表达式的后面要是能跟SimpleStmt的话是不是会更好呢？
 *                这真是一个好想法，以后翻起的时候想着实现
 *   LambdaExpr -> 'lambda' [parameters] ':' con_expr
 *                   LambdaExpr
 *                 /         \
 *            parameters     con_expr
 * lambda 表达式的参数可以为空
 **/
class LambdaExpr
    :public ConExpr
{
public:
	/**
    * 
    **/
    LambdaExpr(ParametersExpr* t_paramters,ConExpr* t_expr);
    /**
    *
    **/
    ~LambdaExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline ParametersExpr* get_parameters()
    {
        return parameters;
    }
    /**
    *        
    **/
    inline ConExpr* get_expr()
    {
        return expr;
    }
protected:
    ParametersExpr* parameters;
    ConExpr* expr;
private:
};
/**
 *  这也是一个抽象类
 **/
class LogicalExpr
    :public ConExpr
{
public:
    /**
    *
    **/
    virtual ~LogicalExpr() = 0;
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
protected:
    /**
    *
    **/
    LogicalExpr(int32_t t_row,int32_t t_col);
private:
};
/**
 *  逻辑或
 *    logical_or_expr -> logical_and_expr ('or' logical_and_expr)*
 *                    logical_or_expr
 *                    /            \
 *            logical_and_expr    logical_or_expr_r
 *                                /            \
 *                        logical_and_expr    logical_or_expr_r
 *    因为logical_or_expr_r与logical_or_expr有着相同的语法结构，所以这里不再重新安排新的类
 **/
class LogicalOrExpr
    :public LogicalExpr
{
public:
    /**
    *  
    **/
    LogicalOrExpr(LogicalAndExpr* t_and_expr,
        LogicalOrExpr* t_or_expr_r);
    /**
    *
    **/
    virtual ~LogicalOrExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline LogicalAndExpr* get_and_expr()
    {
        return and_expr;
    }
    /**
    *        
    **/
    inline LogicalOrExpr* get_or_expr_r()
    {
        return or_expr_r;
    }
protected:
    LogicalAndExpr* and_expr;
    LogicalOrExpr* or_expr_r;
private:
};
/**
 *  逻辑与
 *    logical_and_expr -> not_expr ('and' not_expr)*
 *                这里关乎not_expr的优先级，在方法expr中的实际上不必考虑(暂时这么认为)
 *                        logical_and_expr
 *                        /            \
 *                    not_expr    logical_and_expr_r
 *                                /            \
 *                            not_expr    logical_and_expr_r
 **/
class LogicalAndExpr
    :public LogicalExpr
{
public:
    /**
    *
    **/
    LogicalAndExpr(LogicalNotExpr* t_not_expr,
        LogicalAndExpr* t_and_expr_r);
    /**
    *
    **/
    virtual ~LogicalAndExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline LogicalNotExpr* get_not_expr()
    {
        return not_expr;
    }
    /**
    *        
    **/
    inline LogicalAndExpr* get_and_expr_r()
    {
        return and_expr_r;
    }
protected:
    LogicalNotExpr* not_expr;
    LogicalAndExpr* and_expr_r;
private:
};
/**
 *   逻辑非
 *    由于这个类有两个实现版本，我们使用两个构造函数
 *    not -> 'not' not_expr | comparison
 *            not                not
 *        /        \              |
 *    'not'    not_expr      comparision
 **/
class LogicalNotExpr
    :public LogicalExpr
{
public:
    /**
    *  rel = t_rel,not_expr = NULL
    **/
    LogicalNotExpr(LogicalRelExpr* t_rel);
    /**
    *  rel = NULL,not_expr = t_not_expr
    **/
    LogicalNotExpr(LogicalNotExpr* t_not_expr);
    /**
    *
    **/
    virtual ~LogicalNotExpr();
    /**
    * 当分析这个类的时候，分别判断两者之中有没有空状态
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline LogicalNotExpr* get_not_expr()
    {
        return not_expr;
    }
    /**
    *        
    **/
    inline LogicalRelExpr* get_rel_expr()
    {
        return rel;
    }
protected:
    //bool b_is_not;        //是否含有关键字not
    LogicalNotExpr* not_expr;
    LogicalRelExpr* rel;
private:
};
/**
 *  实现< <= != >= == > 
 * comparision -> small_expr (comp_op small_expr)*
 *               comparision
 *               /         \
 *           small_expr  comparision_r
 **/
class LogicalRelExpr
    :public LogicalExpr
{
public:
    /**
    * 这种多个表达式连在一起的比较真叫人纠结，暂时只要一个，没发现它会有什么
    * 太好的用处
    **/
    LogicalRelExpr(SmallExpr* t_small_expr1,LogicalRelExprR* t_rel_r);
    /**
    *
    **/
    virtual ~LogicalRelExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline SmallExpr* get_small_expr()
    {
        return small_expr1;
    }
    /**
    *        
    **/
    inline LogicalRelExprR* get_rel_r()
    {
        return rel_r;
    }
protected:
    SmallExpr* small_expr1;
    LogicalRelExprR* rel_r;
private:
};
/**
 *   comparision_r -> (comp_op small_expr)*
 *                  comparision 
 *             /         |          \
 *       comp_op    small_expr  comparision_r
 *  改进为comparison_r -> com_op small_expr
 **/
class LogicalRelExprR
    :LogicalExpr
{
public:
	/**
    *
    **/
    LogicalRelExprR(Token* t_token,SmallExpr* t_small_expr,
        LogicalRelExprR* t_rel_r);
    /**
    *
    **/
    ~LogicalRelExprR();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline SmallExpr* get_small_expr()
    {
        return small_expr1;
    }
    /**
    *        
    **/
    inline TokenFlag get_token_flag()
    {
        return token_flag;
    }
    /**
    *   
    **/
    inline LogicalRelExprR* get_rel_r()
    {
        return rel_r;
    }
protected:
    SmallExpr* small_expr1;
    TokenFlag token_flag;
    LogicalRelExprR* rel_r;
private:
};
/**
 *  这也是一个抽象类
 *                SimpleExpr被视为or_expr
 **/
class SmallExpr
    :public Expr
{
public:
    /**
    *
    **/
    virtual ~SmallExpr() = 0;
    /**
    *  访问这个节点，对SimpleExpr除了有这个antion操作之外还有什么内部共有的操作？
    **/
    virtual void visit(Visitor& visitor) = 0;
protected:
    /**
    *
    **/
    SmallExpr(int32_t t_row,int32_t t_col);
private:
};
/**
 *    OrExpr -> xor_expr ('|' xor_expr)*
 *                    OrExpr
 *                /            \
 *            xor_expr        OrExpr_r
 *                            /            \
 *                        xor_expr    OrExpr_r
 **/
class OrExpr
    :public SmallExpr
{
public:
    /**
    *
    **/
    OrExpr(XorExpr* t_xor_expr,OrExpr* t_or_expr_r);
    /**
    *
    **/
    virtual ~OrExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *
    **/
    inline XorExpr* get_xor_expr()
    {
        return xor_expr;
    }
    /**
    *
    **/
    inline OrExpr* get_or_expr_r()
    {
        return or_expr_r;
    }
protected:
    XorExpr* xor_expr;
    OrExpr* or_expr_r;
private:
};
/**
 *    xor_expr -> and_expr ('^' and_expr)*
 *                xor_expr
 *                /        \
 *            and_expr    xor_expr_r
 *                        /        \
 *                    and_expr    xor_expr_r
 **/
class XorExpr
    :public SmallExpr
{
public:
    /**
    *
    **/
    XorExpr(AndExpr* t_and_expr,XorExpr* t_xor_expr_r);
    /**
    *
    **/
    virtual ~XorExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline AndExpr* get_and_expr()
    {
        return and_expr;
    }
    /**
    *        
    **/
    inline XorExpr* get_xor_expr_r()
    {
        return xor_expr_r;
    }
protected:
    AndExpr* and_expr;
    XorExpr* xor_expr_r;
private:
};
/**
 *    and_expr -> shift_expr ('&' shift_expr)*
 *                    and_expr
 *                    /        \
 *                shift_expr  and_expr_r
 *                            /        \
 *                        shift_expr    and_expr_r
 **/
class AndExpr
    :public SmallExpr
{
public:
    /**
    *
    **/
    AndExpr(ShiftExpr* t_shift_expr,AndExpr* t_and_expr_r);
    /**
    *
    **/
    virtual ~AndExpr();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline ShiftExpr* get_shift_expr()
    {
        return shift_expr;
    }
    /**
    *        
    **/
    inline AndExpr* get_and_expr_r()
    {
        return and_expr_r;
    }
protected:
    ShiftExpr* shift_expr;
    AndExpr* and_expr_r;
private:
};
/**
 *    shift_expr -> arith_expr (('<<' | '>>' ) arith_expr )*
 *            shift_expr
 *            /        \
 *    arith_expr        shift_expr_r
 *                /        |        \
 *            token     arith_expr        shift_expr_r
 **/
class ShiftExpr
    :public SmallExpr
{
public:
    /**
    *
    **/
    ShiftExpr(ArithExpr* t_arith_expr,ShiftExprR* t_shift_expr_r);
    /**
    *
    **/
    virtual ~ShiftExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline ArithExpr* get_arith_expr()
    {
        return arith_expr;
    }
    /**
    *        
    **/
    inline ShiftExprR* get_shift_expr_r()
    {
        return shift_expr_r;
    }
protected:
    ArithExpr* arith_expr;
    ShiftExprR* shift_expr_r;
private:
};
/**
 *    shift_expr_r -> (('<<' | '>>' ) arith_expr )*
 *                   shift_expr_r
 *                /        |        \
 *            token     arith_expr        shift_expr_r
 **/
class ShiftExprR
    :public SmallExpr
{
public:
    /**
    *
    **/
    ShiftExprR(Token* t_token,ArithExpr* t_arith_expr,
        ShiftExprR* t_shift_expr_r);
    /**
    *
    **/
    ~ShiftExprR();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline TokenFlag get_token_flag()
    {
        return token_flag;
    }
    /**
    *        
    **/
    inline ArithExpr* get_arith_expr()
    {
        return arith_expr;
    }
    /**
    *   
    **/
    inline ShiftExprR* get_shift_expr_r()
    {
        return shift_expr_r;
    }
protected:
    TokenFlag token_flag;
    ArithExpr* arith_expr;
    ShiftExprR* shift_expr_r;
private:
};
/**
 *    arith_exxpr -> term (('+' | '-' ) term )*
 *                arith_expr
 *            /            \
 *        term      arith_expr_r
 *                /        |        \
 *            token      term        arith_expr_r
 **/
class ArithExpr
    :public SmallExpr
{
public:
    /**
    *
    **/
    ArithExpr(TermExpr* t_term,ArithExprR* t_arith_expr_r);
    /**
    *
    **/
    virtual ~ArithExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline TermExpr* get_term()
    {
        return term;
    }
    /**
    *        
    **/
    inline ArithExprR* get_arith_expr_r()
    {
        return arith_expr_r;
    }
protected:
    TermExpr* term;
    ArithExprR* arith_expr_r;
private:
};
/**
 * 
 **/
class ArithExprR
    :public SmallExpr
{
public:
    /**
    *
    **/
    ArithExprR(Token* t_token,TermExpr* t_term,ArithExprR* t_arith_expr_r);
    /**
    *
    **/
    virtual ~ArithExprR();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline TokenFlag get_token_flag()
    {
        return token_flag;
    }
    /**
    *   
    **/
    inline TermExpr* get_term()
    {
        return term;
    }
    /**
    *        
    **/
    inline ArithExprR* get_arith_expr_r()
    {
        return arith_expr_r;
    }
protected:
    TokenFlag token_flag;
    TermExpr* term;
    ArithExprR* arith_expr_r;
private:
};
/**
 *    term -> factor (('*' | '/' | '%' | '//' ) factor)*
 *                    term
 *                /        \
 *            factor         term_r
 *                    /        |        \
 *                token     factor    term_r
 **/
class TermExpr
    :public SmallExpr
{
public:
    /**
    *
    **/
    TermExpr(FactorExpr* t_factor,TermExprR* t_term_r);
    /**
    *
    **/
    virtual ~TermExpr();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   
    **/
    inline FactorExpr* get_factor()
    {
        return factor;
    }
    /**
    *   
    **/
    inline TermExprR* get_term_r()
    {
        return term_r;
    }
protected:
    FactorExpr* factor;
    TermExprR* term_r;
private:
};
/**
 * 
 **/
class TermExprR
    :public SmallExpr
{
public:
    /**
    *
    **/
    TermExprR(Token* t_token,FactorExpr* t_factor,
        TermExprR* t_term_r);
    /**
    *
    **/
    ~TermExprR();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline TokenFlag get_token_flag()
    {
        return token_flag;
    }
    /**
    *        
    **/
    inline FactorExpr* get_factor()
    {
        return factor;
    }
    /**
    *        
    **/
    inline TermExprR* get_term_r()
    {
        return term_r;
    }
protected:
    TokenFlag token_flag;
    FactorExpr* factor;
    TermExprR* term_r;
private:
};
/**
 *    factor -> ('+' | '-' | '~' ) factor | power
 *              factor           factor
 *            /        \           |
 *         token        factor    power
 **/
class FactorExpr
    :public SmallExpr
{
public:
    /**
    *  token_flag = t_token->id,power = t_power,factor = NULL
    **/
    FactorExpr(Token* t_token,FactorExpr* t_factor);
    /**
    *   token_flag = EMPTY,power = NULL,factor = t_factor
    **/
    FactorExpr(PowerExpr* t_power);
    /**
    * 
    **/
    virtual ~FactorExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline TokenFlag get_token_flag()
    {
        return token_flag;
    }
    /**
    *   
    **/
    inline FactorExpr* get_factor()
    {
        return factor;
    }
    /**
    *   
    **/
    inline PowerExpr* get_power_expr()
    {
        return power;
    }
protected:
    TokenFlag token_flag;   //如果这个为EMPTY的话则说明是第二种选择
    FactorExpr* factor;

    PowerExpr* power;
private:
};
/**
 *    power -> atom ['**' factor]
 *            power
 *        /        \
 *     atom        factor
 **/
class PowerExpr
    :public SmallExpr
{
public:
    /**
    *  后面的factor为空的话，表明没有求平方
    **/
    PowerExpr(AtomExpr* t_atom,FactorExpr* t_factor = NULL);
    /**
    *
    **/
    virtual ~PowerExpr();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline AtomExpr* get_atom()
    {
        return atom;
    }
    /**
    *        
    **/
    inline FactorExpr* get_factor()
    {
        return factor;
    }
protected:
    AtomExpr* atom;
    FactorExpr* factor;    //可以为空，这里的递归已经不关其它的事情
private:
};
/**
 * 这也是一个抽象类
 *   atom -> tuple_expr |
 *           map_expr |
 *           number_expr |
 *           string_expr |
 *           keyword_expr |
 *           name_expe
 *           )
 **/
class AtomExpr
    :public SmallExpr
{
public:
    /**
    *
    **/
    virtual ~AtomExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
protected:
    /**
    *   
    **/
    AtomExpr(int32_t t_row,int32_t t_col);
private:
};
/**
 *  
 * 根据asdl生成IR的提示，将atom规则右部作为其子类较好
 *   tuple_expr -> '(' tuple_variables ')'
 *               tuple_expr
 *                   |
 *             tuple_variables
 **/
class TupleExpr
    :public AtomExpr
{
public:
    /**
    * 
    **/
    TupleExpr(TupleVariableExpr* t_variable);
    /**
    * 
    **/
    ~TupleExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline TupleVariableExpr* get_variable()
    {
        return variable;
    }
protected:
    TupleVariableExpr* variable;
    //TupleObject *value;
private:
};
/**
 *   map_expr -> '[' map_variables ']'
 *               map_expr
 *                  |
 *            map_variables
 **/
class MapExpr
    :public AtomExpr
{
public:
    /**
    * 
    **/
    MapExpr(MapVariableExpr* t_variable);
    /**
    *
    **/
    ~MapExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline MapVariableExpr* get_variable()
    {
        return variable;
    }
protected:
    //MapObject *value;
    MapVariableExpr* variable;
private:
};
/**
 *   保存tuple与map的变量,这也是一个抽象类
 **/
class VariablesExpr
    :public Expr
{
public:
    /**
    *
    **/
    ~VariablesExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
protected:
	/**
    *
    **/
    VariablesExpr(int32_t t_row,int32_t t_col);
private:
};
/**
 *   tuple_variables -> expr (',' expr)* [',']
 *               tuple_varialbles
 *               /           \
 *           expr         tuple_variables
 **/
class TupleVariableExpr
    :public VariablesExpr
{
public:
	/**
    *
    **/
    TupleVariableExpr(Expr* t_expr,TupleVariableExpr* t_variable_r);
    /**
    *
    **/
    ~TupleVariableExpr();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   
    **/
    inline Expr* get_expr()
    {
        return expr;
    }
    /**
    *   
    **/
    inline TupleVariableExpr* get_variable()
    {
        return variable_r;
    }
protected:
    Expr* expr;
    TupleVariableExpr* variable_r;
private:
};
/**
 *   map_variable -> ( expr '=' expr ) (expr '='expr)* [',']
 *              map_variable
 *          /       |       \
 *       expr_l    expr_r   map_variable
 **/
class MapVariableExpr
    :public VariablesExpr
{
public:
	/**
    * 
    **/
    MapVariableExpr(Expr* t_expr_l,
        Expr* t_expr_r,
        MapVariableExpr* t_variable_r);
    /**
    * 
    **/
    ~MapVariableExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline Expr* get_expr_l()
    {
        return expr_l;
    }
    /**
    *        
    **/
    inline Expr* get_expr_r()
    {
        return expr_r;
    }
    /**
    *   
    **/
    inline MapVariableExpr* get_variable()
    {
        return variable_r;
    }
protected:
    Expr* expr_l;
    Expr* expr_r;
    MapVariableExpr* variable_r;
private:
};
/**
 *   number_expr -> NUMBER
 **/
class NumberExpr
    :public AtomExpr
{
public:
    /**
    * 
    **/
    NumberExpr(Token *t_token);
    /**
    *
    **/
    ~NumberExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline LongObject* get_int()
    {
        return int_value;
    }
    /**
     * 
     */
    inline FloatObject* get_float()
    {
        return float_value;
    }
protected:
    FloatObject* float_value;
    LongObject* int_value;
private:
};
/**
 *   string_expr -> STRING+
 **/
class StringExpr
    :public AtomExpr
{
public:
    /**
    *
    **/
    StringExpr(Token *t_token,StringExpr* t_string_other);
    /**
    *
    **/
    ~StringExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *   
    **/
    inline std::string get_value()
    {
        return value;
    }
    /**
    *        
    **/
    inline StringExpr* get_string_other()
    {
        return string_other;
    }
protected:
    std::string value;
    StringExpr* string_other;
private:
};
/**
 *   将关键字集合独立实现，即null,false,true
 *   keyword_expr -> 'null' | 'true' | 'false'
 **/
class KeyWordExpr
    :public AtomExpr
{
public:
    /**
    * 传入token的值，根据token的字符串值判断key_value中存的实际值
    **/
    KeyWordExpr(Token *t_token);
    /**
    * 
    **/
    ~KeyWordExpr();
    /**
    *
    **/
    void visit(Visitor& visitor);
    /**
    *        
    **/
    inline LongObject* get_value()
    {
        return value;
    }
protected:
    LongObject *value;  //考虑这样实现，null存0，false存0，true存1，
                            //使用int类型来实现
private:
};
/**
 *   NameExpr与fun_invoke和module_invoke配合
 *   name_expr -> NAME (fun_invoke | module_invoke)
 *               name_expr
 *               /       \
 *            NAME    atom_expr
 **/
class NameExpr
    :public AtomExpr
{
public:
	/**
    *
    **/
    NameExpr(Token* t_token,AtomExpr* t_name_expr_r);
    /**
    * 
    **/
    ~NameExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline std::string get_name()
    {
        return name;
    }
    /**
    *        
    **/
    inline AtomExpr* get_name_expr_r()
    {
        return name_expr_r;
    }
protected:
    std::string name;
    AtomExpr* name_expr_r;  //可以是fun_invoke和module_invoke中的一个，也可以
                            //为空
    //可以使用下面代码做判断
    //if (typeid(name_expr_r) != typeid(FunInvokeExpr)
        //||  typeid(name_expr_r) != typeid(ModuleInvokeExpr))
    //{
        //return false;
    //}
private:
};
/**
 *    fun_invoke -> '(' parameters ')'
 *                fun_invoke
 *                   |
 *               parameters
 **/
class FunInvokeExpr
    :public AtomExpr
{
public:
    /**
    *
    **/
    FunInvokeExpr(ParametersExpr* t_paras);
    /**
     * 当函数调用无参的时候直接传入行号，而使paras变量为NULL
     */
    FunInvokeExpr(int32_t row,int32_t col);
    /**
    *
    **/
    virtual ~FunInvokeExpr();
    /**
    *
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline ParametersExpr* get_paras()
    {
        return paras;
    }
protected:
    ParametersExpr* paras;
private:
};
/**
 *    module_invoke -> ( '.' NAME )*
 *                    module_invoke
 *                    /        \
 *                Token    module_invoke
 *                        /        \
 *                    Token    module_invoke
 **/
class ModuleInvokeExpr
    :public AtomExpr
{
public:
    /**
    *
    **/
    ModuleInvokeExpr(Token* t_token,
        ModuleInvokeExpr* t_module_invoke_r);
    /**
    *
    **/
    virtual ~ModuleInvokeExpr();
    /**
    *  
    **/
    virtual void visit(Visitor& visitor);
    /**
    *        
    **/
    inline std::string get_name()
    {
        return name;
    }
    /**
    *        
    **/
    inline ModuleInvokeExpr* get_module_expr_r()
    {
        return module_invoke_r;
    }
protected:
    std::string name;    //stringObject类型的模块名
    ModuleInvokeExpr* module_invoke_r;
private:
};

EF_NAMESPACE_END

#endif // _NODE_H_2011_12_13_lisency

