/*-------------------------------------------------------------------
 * Purpose:
 *         Parser.cpp
 * Time:
 *         2011年12月1日 21:16:08
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "Parser.h"
#include "Debug.h"
#include "Exception.h"
#include "Token.h"

EF_NAMESPACE_BEGIN

/**
 *
 */
Parser::Parser(Scanner &t_scanner)
:scanner(t_scanner)
{
    return;
}
/**
 *
 */
Parser::~Parser()
{
    return;
}
/**
 *
 */
EFParser::EFParser(Scanner &scanner)
:Parser(scanner)
{
    file_path = scanner.get_path();
    Node::set_file_path(file_path);
    //设置节点的文件名
    return;
}
/**
 *
 */
EFParser::~EFParser()
{
    return;
}
/**
 * 向前查看一个词素
 */
void EFParser::move()
{
    look = scanner.nextToken();    //向前继续查看
#ifdef EF_DEBUG
    look->print(debug_stream);
#endif
    //这里还遗留着是否到达文件末尾的判断，是否需要？
    return;
}
/**
 * 根据当前输入的token，查看符号表中是否存在
 **/
bool EFParser::match(TokenFlag token_flag)
{
    TokenFlag t_token_flag = look->id;
    if (t_token_flag == token_flag)
    {
        move();
        return true;
    }
    else
    {
        return false;
    }
}
/**
 * 抛出异常，出发错误点
 **/
void EFParser::throw_error(int error_id)
{
    //抛出异常，文件以异常结束
    EFExc exc(file_path,look->row,look->col,error_id);
    throw exc;
}
/**
 * 程序模块
 * file_input -> StmtSeq ENDMARKER个模块
 *  返回语法树的根节点
 **/
Stmt* EFParser::module()
{
    D("now in module");
    move(); //首先向前看一个词素
    Stmt *stmt = stmts();
    bool b_match = match(ENDMARKER);
    if (b_match == false)
    {
        throw_error(ERROR_FILE_END_NOFORMOR);
    }
    return stmt;
}
/**
 * 对文件递归扫描，匹配更多的stmt
 * StmtSeq -> (NEWLINE | Stmt)*
 *           StmtSeq
 *           /     \
 *       stmt    StmtSeq
 **/
StmtSeq* EFParser::stmts()
{
    D("now in stmts");
    //结束
    if (match(ENDMARKER) == true)
    {
        return NULL;
    }
    //若是NEWLINE，全部略过
    while (match(NEWLINE) == true)
    {
        ;
    }
    Stmt* t_stmt = stmt();
    if (t_stmt == NULL)
    {
        return NULL;
    }
    return new StmtSeq(t_stmt,stmts());
}
/**
 * 根据文件读入的数据流匹配相应的数据流，匹配stmt
 * stmt -> simple_stmt | compound_stmt
 * simple_stmt -> small_stmt ( ';' small_stmt)* [';'] NEWLINE
 *  compound_stmt -> if_stmt |
 *                 while_stmt |
 *                 for_stmt |
 *                 try_stmt |
 *                 fundef_stmt |
 *                 classdef_stmt
 **/
Stmt* EFParser::stmt()
{
    D("now in stmt");
    //这里需要查看firstset，所以向前移动一个字符
    //move();

    TokenFlag token_flag = this->look->id;

    switch (token_flag)
    {
    case IF_MARKER:                         //是if语句
    case WHILE_MARKER:                      //是while循环
    case FOR_MARKER:                        //是for循环
    case FUN_MARKER:                        //是函数定义
    case CLASS_MARKER:                      //是类定义
    case TRY_MARKER:                        //是try语句
        return compound_stmt();
    default:
        return simple_stmt();
        //其余的全部是SimpleStmt
    //case DEL_MARKER:                        //删除语句
    //case IMPORT_MARKER:                     //导入语句
    //case NAME:                              //是赋值等语句
    //    return simple_stmt();
    }
}
/**
 * 返回一个简单语句
 * simple_stmt -> small_stmt (';' small_stmt)*[';'] NEWLINE
 **/
SimpleStmt* EFParser::simple_stmt()
{
    D("now in simple_stmt");
    SmallStmt *t_small_stmt = small_stmt();

    if (t_small_stmt == NULL)
    {
        return NULL;
    }

    SimpleStmt* t_simple_stmt = new SimpleStmt(t_small_stmt,small_stmt_list());

    match(SEMI);  //略过分号，分号可有可无

    bool b_match = match(NEWLINE);

    /*未匹配到 NEWLINE符号，出错*/
    if (b_match == false)
    {
        throw_error(ERROR_NO_NEWLINE);
    }

    return t_simple_stmt;
}
/**
 * 返回一个小语句
 * small_stmt -> assign |
 *                 augassign |
 *                 del_stmt |
 *                 import_stmt
 **/
SmallStmt* EFParser::small_stmt()
{
    D("now in small_stmt");
    TokenFlag token_flag = this->look->id;

    switch (token_flag)
    {
    case DEL_MARKER:          return del_stmt();
    case IMPORT_MARKER:       return import_stmt();
    case NAME:                return assign_stmt();
    default:                  return NULL;
    }
    return NULL;
}
/**
 * 匹配SimpleStmt后面的部分
 * SmallStmtList -> (';' small_stmt)*
 **/
SimpleStmt* EFParser::small_stmt_list()
{
    D("now in small_stmt_list");
    bool b_match = match(SEMI);

    /*若没有匹配到分号，则返回NULL*/
    if (b_match == false)
    {
        return NULL;
    }
    SmallStmt* t_small_stmt = small_stmt();
    if (t_small_stmt == NULL)
    {
        throw_error(ERROR_NO_USE_WORD);
    }
    return new SimpleStmt(t_small_stmt,small_stmt_list());
}
/**
 *
 */
DelStmt* EFParser::del_stmt()
{
    D("now in del_stmt");
    bool b_match = match(DEL_MARKER);

    if (b_match == false)
    {
        return NULL;
    }
    Token* t_token = look;

    b_match = match(NAME);
    if (b_match == false)
    {
        throw_error(ERROR_STMT_END_NOFORMOR);
    }
    return new DelStmt(t_token);
}
/**
 *
 */
ImportStmt* EFParser::import_stmt()
{
    D("now in import_stmt");
    bool b_match = match(IMPORT_MARKER);

    if (b_match == false)
    {
        return NULL;
    }

    Token* t_token = look;

    b_match = match(NAME);
    if (b_match == false)
    {
        throw_error(ERROR_STMT_END_NOFORMOR);
    }
    return new ImportStmt(t_token);
}
/**
 *   Assign -> expr (derict_assign | augassign)
 *               Assign
 *             /       \
 *           expr     Assign(augassign or derict_assign)
 **/
Assign* EFParser::assign_stmt()
{
    D("now in assign_stmt");
    Expr* t_expr = expr();        //规则右部的第一个expr
    if (this->look->id == EQUAL)
    {
        return new Assign(t_expr,derict_assign());
    }
    else if (is_aug_assign(this->look))
    {
        return new Assign(t_expr,aug_assign());
    }
    else
    {
        //assign语句没有后面的部分时表示只有一个name
        return new Assign(t_expr);
    }
}
/**
 *  derict_assign -> ('=' expr)*
 *                   derict_assign
 *                    /         \
 *                 expr  (=)    derict_assign
 **/
DerictAssign* EFParser::derict_assign()
{
    D("now in derict_assign");
    bool b_match = match(EQUAL);

    if (b_match == false)
    {
        return NULL;
    }
    Expr* t_expr = expr();
    if (t_expr == NULL)
    {
        throw_error(ERROR_REDUNDANT_EQUAL);
    }
    return new DerictAssign(t_expr,derict_assign());
}
/**
 *   augassign -> augmentassign expr
 *                augassign
 *               /        \
 *     assign_operator    expr
 **/
AugAssign* EFParser::aug_assign()
{
    D("now in aug_assign");
    if (is_aug_assign(this->look) == false)
    {
        return NULL;
    }

    Token *t_token = this->look;
    move();    //略过自增符号,未调用match函数时使用move

    Expr* t_expr = expr();

    if (t_expr == NULL)
    {
        throw_error(ERROR_REDUNDANT_EQUAL);
    }

    return new AugAssign(t_token,t_expr);
}
/**
 *   compound_stmt -> if_stmt |
 *                    while_stmt |
 *                    for_stmt |
 *                    try_stmt |
 *                    fundef_stmt |
 *                    classdef_stmt 
 **/
CompoundStmt* EFParser::compound_stmt()
{
    D("now in compound_stmt");
    TokenFlag token_flag = this->look->id;

    switch (token_flag)
    {
    case IF_MARKER:                      return if_stmt();      //是if语句
    case WHILE_MARKER:                   return while_stmt();   //是while循环
    case FOR_MARKER:                     return for_stmt();     //是for循环
    case FUN_MARKER:                     return fun_stmt();     //是函数定义
    case CLASS_MARKER:                   return cla_stmt();     //是类定义
    case TRY_MARKER:                     return try_stmt();     //是try语句
    default:
        return NULL;                        //碰到不能识别词素
    }
}
/**
 * 构造if语句节点
 *                    if
 *                /    |    \      \
 *               /     |     \       \
 *            expr  stmt     elif     else
 *                        /  |  \
 *                我们先留下else语句
 **/
IfStmt* EFParser::if_stmt()
{
    D("now in if_stmt");
    bool b_match = match(IF_MARKER);

    if (b_match == false)
    {
        return NULL;
    }

    Expr* t_expr = expr();

    if (t_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    b_match = match(COLON);

    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Suite* t_stmt = suite();

    if (t_stmt == NULL)
    {
        throw_error(ERROR_NO_SUITE);
    }

    ElifStmt* elif = elif_stmt();
    ElseStmt* else_ = else_stmt();

    return new IfStmt(t_expr,t_stmt,elif,else_);
}
/**
 *
 */
WhileStmt* EFParser::while_stmt()
{
    D("now in while_stmt");
    bool b_match = match(WHILE_MARKER);

    if (b_match == false)
    {
        return NULL;
    }
    Expr* t_expr = expr();
    if (t_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    b_match = match(COLON);

    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new WhileStmt(t_expr,suite(),else_stmt());
}
/**
 * 注意if与elif共用一个If结构
 **/
ElifStmt* EFParser::elif_stmt()
{
    D("now in elif_stmt");
    bool b_match = match(ELIF_MARKER);        //匹配elif语句
    if (b_match == false)
    {
        return NULL;
    }
    Expr* t_expr = expr();
    if (t_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Suite* t_stmt = suite();
    return new ElifStmt(t_expr,t_stmt,elif_stmt());
}
/**
 *
 */
ElseStmt* EFParser::else_stmt()
{
    D("now in else_stmt");
    bool b_match = match(ELSE_MARKER);
    if (b_match == false)
    {
        return NULL;
    }
    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Suite* t_stmt = suite();
    if (t_stmt == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new ElseStmt(t_stmt);
}
/**
 *
 */
ForStmt* EFParser::for_stmt()
{
    D("now in for_stmt");
    bool b_match = match(FOR_MARKER);
    if (b_match == false)
    {
        return NULL;
    }

    Expr* t_expr = expr();
    if (t_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    b_match = match(IN_MARKER);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Expr* expr_range = expr();
    if (expr_range == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Suite* t_stmt = suite();
    if (t_stmt == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new ForStmt(t_expr,expr_range,t_stmt,else_stmt());
}
/**
 *
 */
TryStmt* EFParser::try_stmt()
{
    D("now in try_stmt");
    bool b_match = match(TRY_MARKER);
    if (b_match == false)
    {
        return NULL;
    }
    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Suite* stmt_try = suite();
    if (stmt_try == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    CatchStmt* t_catchs_stmt = catch_stmt();
    if (t_catchs_stmt == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    //finally可以为空
    b_match = match(FINALLY_MARKER);
    if (b_match == false)
    {
        //throw_error(ERROR_KEY_MARKER);
        return new TryStmt(stmt_try,t_catchs_stmt,NULL);
    }
    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Suite* stmt_finally = suite();
    if (stmt_finally == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new TryStmt(stmt_try,t_catchs_stmt,stmt_finally);
}
/**
 *
 */
CatchStmt* EFParser::catch_stmt()
{
    D("now in catch_stmt");
    bool b_match = match(CATCH_MARKER);
    if (b_match == false)
    {
        return NULL;
    }

    Expr* t_expr = expr();
    if (t_expr == NULL  )
    {
        //do nothing,这个可以为空
    }

    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Suite* t_stmt = suite();
    if (t_stmt == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new CatchStmt(t_expr,t_stmt,catch_stmt());
}
/**
 *
 */
FunStmt* EFParser::fun_stmt()
{
    D("now in fun_stmt");
    bool b_match = match(FUN_MARKER);
    if (b_match == false)
    {
        return NULL;
    }
    Token* token = this->look;  //记录函数名称
    b_match = match(NAME);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }

    b_match = match(LPAR);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }

    ParametersExpr* t_para = parameters();

    b_match = match(RPAR);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }

    if (t_para == NULL)
    {
        // do nothing 函数参数可以为空
    }
    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Suite* stmt = suite();
    if (stmt == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new FunStmt(token,t_para,stmt);
}
/**
 *
 */
ClassStmt* EFParser::cla_stmt()
{
    D("now in cla_stmt");
    bool b_match = match(CLASS_MARKER);

    if (b_match == false)
    {
        return NULL;
    }
    b_match = match(NAME);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Token* t_token = this->look;
    //记录类名
    if (t_token == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }

    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }

    Suite* t_stmt = suite();

    if (t_stmt == NULL)
    {
        throw_error(ERROR_NO_SUITE);
    }
    return new ClassStmt(t_token,t_stmt);
}

/**
 * suite -> simple_stmt | NEWLINE INDENT stmt+ DEDENT
 **/
Suite* EFParser::suite()
{
    D("now in suite");
    bool b_match = match(NEWLINE);
    if (b_match == false)
    {
        return new Suite(simple_stmt());
    }
    b_match = match(INDENT);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    StmtSeq* t_stmts = stmts();
    if (t_stmts == NULL)
    {
        //do nothing可以为空
    }
    Token* t_token = look;
    if (t_token->id == ENDMARKER)
    {
        return new Suite(t_stmts);
    }
    else if (t_token->id == DEDENT)
    {
        move(); //略过反缩进
        return new Suite(t_stmts);
    }
    throw_error(ERROR_KEY_MARKER);
    return NULL;
}
/**
 * expr -> con_expr | fun_invoke | module_invoke | simple_expr
 * 虽然这里是一个NFA，但不影响我们的程序
 * 预测分析表为
 *              expr
 *    NAME    module_invoke -> NAME ( '.' NAME)*
 *            fun_invoke -> NAME ( '(' parameters ')' )*
 **/
Expr* EFParser::expr()
{
    D("now in expr");
    TokenFlag token_flag = this->look->id;

    switch (token_flag)
    {
        //+-~号,facor -> ('+' | '-' | '~' ) factor | power
    case PLUS:              //+
    case MINUS:             //-
    case TILDE:             //~
    case LPAR:              //( tuple parameter
    case LSQB:              //[ map parameter
    case STAR:              //*
    case NUMBER:            //数字
    case STRING:            //字符串
    case NAME:              //标识符
    case NULL_MARKER:       //null
    case FALSE_MARKER:      //false
    case TRY_MARKER:        //true
    case LAMBDA_MARKER:     //lambda
    case NOT_MARKER:        //not
        return con_expr();
    }
    //!号,取反,词法分析程序为返回感叹号，所以暂留
    return NULL;
}
/**
 *
 */
ParametersExpr* EFParser::parameters()
{
    D("now in parameters");
    ParameterExprAtom* t_atom_para = atom_para();
    if (t_atom_para == NULL)
    {
        return NULL;    //无参
    }
    bool b_match = match(COMMA);
    if (b_match == false)
    {
        return new ParametersExpr(t_atom_para,NULL);
    }
    return new ParametersExpr(t_atom_para,parameters());
}
/**
 *
 */
ParameterExprAtom* EFParser::atom_para()
{
    D("now in atom_para");
    TokenFlag token_flag = this->look->id;
    bool b_match = false;
    Token* token = NULL;
    if (token_flag == STAR)
    {
        move();    //略过星号
        b_match = match(NAME);
        if (b_match == false)
        {
            //错误处理
        }
        token = this->look;
        b_match = match(EQUAL);
        token = this->look;

        if (b_match == false)
        {
            return new TupleParameterExpr(token,NULL);
        }
        else
        {
            return new TupleParameterExpr(token,expr());
        }
    }
    //map参数
    else if (token_flag == DOUBLESTAR)
    {
        move();    //略过双星号
        b_match = match(NAME);
        if (b_match == false)
        {
            //错误处理
        }
        token = this->look;
        b_match = match(EQUAL);
        token = this->look;

        if (b_match == false)
        {
            return new MapParameterExpr(token,NULL);
        }
        else
        {
            return new MapParameterExpr(token,expr());
        }
    }
    //普通参数
    else
    {
        AtomExpr* t_atom = atom();

        if (t_atom == NULL)
        {
            return NULL;
        }

        b_match = match(EQUAL);

        if (b_match == false)
        {
            NostarParameterExpr* para = new NostarParameterExpr(t_atom,NULL);
            return para;
        }
        else
        {
            return new NostarParameterExpr(t_atom,expr());
        }
    }
    //tuple参数
}

/**
 * 条件语句
 * conditional_expr -> logical_or_expr | lambda_expr
 **/
ConExpr* EFParser::con_expr()
{
    D("now in con_expr");
    //lambda and not expression is considered at expr method,so none of them considered at here
    bool b_match = match(LAMBDA_MARKER);
    if (b_match == true)
    {
        return lambda_expr();
    }
    else
    {
        return logical_or_expr();
    }
}
/**
 * LambdaExpr -> 'lambda' [parameters] ':' con_expr
 **/
LambdaExpr* EFParser::lambda_expr()
{
    D("now in lambda_expr");
    bool b_match = match(LAMBDA_MARKER);

    if (b_match == false)
    {
        return NULL;
    }
    ParametersExpr* t_para = parameters();

    if (t_para == NULL)
    {
        // do nothing 参数可以为空
    }
    b_match = match(COLON);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    ConExpr* t_expr = con_expr();
    if (t_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new LambdaExpr(t_para,t_expr);
}
/**
 *
 */
LogicalOrExpr* EFParser::logical_or_expr()
{
    D("now in lagical_or_expr");
    LogicalAndExpr* and_expr = logical_and_expr();
    if (and_expr == NULL)
    {
        return NULL;
    }
    return new LogicalOrExpr(and_expr,logical_or_expr_r());
}
/**
 * 这里没有实现&&，||，等，暂留，如果要实现的话，在词法分析的
 * 过程中直接标志为OR_MARKER等
 **/
LogicalOrExpr* EFParser::logical_or_expr_r()
{
    D("now in lagical_or_expr_r");
    bool b_match = match(OR_MARKER);
    if (b_match == false)
    {
        return NULL;
    }
    LogicalAndExpr* and_expr = logical_and_expr();
    if (and_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new LogicalOrExpr(and_expr,logical_or_expr_r());
}
/**
 *
 */
LogicalAndExpr* EFParser::logical_and_expr()
{
    D("now in lagical_and_expr");
    LogicalNotExpr* t_not_expr = not_expr();
    if (t_not_expr == NULL)
    {
        return NULL;
    }
    return new LogicalAndExpr(t_not_expr,logical_and_expr_r());
}
/**
 *
 */
LogicalAndExpr* EFParser::logical_and_expr_r()
{
    D("now in lagical_and_expr_r");
    bool b_match = match(AND_MARKER);
    if (b_match == false)
    {
        return NULL;
    }
    LogicalNotExpr* t_not_expr = not_expr();
    if (t_not_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new LogicalAndExpr(t_not_expr,logical_and_expr_r());
}
/**
 *
 */
LogicalNotExpr* EFParser::not_expr()
{
    D("now in not_expr");
    bool b_match = match(NOT_MARKER);
    //note! here is true ,in the if scope its return the not expr
    if (b_match == true)
    {
        return new LogicalNotExpr(not_expr());
    }
    LogicalRelExpr* t_comparison = comparison();
    if (t_comparison == NULL)
    {
        return NULL;
    }
    return new LogicalNotExpr(t_comparison);
}
/**
 *
 */
LogicalRelExpr* EFParser::comparison()
{
    D("now in comparison");
    OrExpr* t_small_expr1 = or_expr();
    if (t_small_expr1 == NULL)
    {
        return NULL;
    }
    return new LogicalRelExpr(t_small_expr1,comparison_r());
}
/**
 *
 */
LogicalRelExprR* EFParser::comparison_r()
{
    D("now in comparison_r");
    bool b_match = is_com_op(this->look);
    if (b_match == false)
    {
        return NULL;
    }
    Token* t_token = look;

    move(); //略过比较符号
    SmallExpr* t_small_expr = or_expr();
    if (t_small_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new LogicalRelExprR(t_token,t_small_expr,comparison_r());
}
/**
 *
 */
OrExpr* EFParser::or_expr()
{
    D("now in or_expr");
    XorExpr* t_xor_expr = xor_expr();
    if (t_xor_expr == NULL)
    {
        return NULL;
    }
    return new OrExpr(t_xor_expr,or_expr_r());
}
/**
 *
 */
OrExpr* EFParser::or_expr_r()
{
    D("now in or_expr_r");
    bool b_match = match(VBAR);
    if (b_match == false)
    {
        return NULL;
    }
    XorExpr* t_xor_expr = xor_expr();
    if (t_xor_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new OrExpr(t_xor_expr,or_expr_r());
}
/**
 *
 */
XorExpr* EFParser::xor_expr()
{
    D("now in xor_expr");
    AndExpr* t_and_expr = and_expr();
    if (t_and_expr == NULL)
    {
        return NULL;
    }
    return new XorExpr(t_and_expr,xor_expr_r());
}
/**
 *
 */
XorExpr* EFParser::xor_expr_r()
{
    D("now in xor_expr_r");
    bool b_match = match(CIRCUMFLEX);
    if (b_match == false)
    {
        return NULL;
    }
    AndExpr* t_and_expr = and_expr();
    if (t_and_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new XorExpr(t_and_expr,xor_expr_r());
}
/**
 *
 */
AndExpr* EFParser::and_expr()
{
    D("now in and_expr");
    bool b_match = match(CIRCUMFLEX);
    ShiftExpr* t_shift_expr = shift_expr();
    if (t_shift_expr == NULL)
    {
        return NULL;
    }
    return new AndExpr(t_shift_expr,and_expr_r());
}
/**
 *
 */
AndExpr* EFParser::and_expr_r()
{
    D("now in and_expr_r");
    bool b_match = match(AMPER);
    if (b_match == false)
    {
        return NULL;
    }
    ShiftExpr* t_shift_expr = shift_expr();
    if (t_shift_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new AndExpr(t_shift_expr,and_expr_r());
}
/**
 *
 */
ShiftExpr* EFParser::shift_expr()
{
    D("now in shitf_expr");
    ArithExpr* t_arith_expr = arith_expr();
    if (t_arith_expr == NULL)
    {
        return NULL;
    }
    return new ShiftExpr(t_arith_expr,shift_expr_r());
}
/**
 *
 */
ShiftExprR* EFParser::shift_expr_r()
{
    D("now in shitf_expr_r");
    Token* token = this->look;

    if (token->id != LEFTSHIFT
        && token->id != RIGHTSHIFT)
    {
        return NULL;
    }
    move();        //略过左移与右移符号
    ArithExpr* t_arith_expr = arith_expr();
    if (t_arith_expr == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new ShiftExprR(token,t_arith_expr,shift_expr_r());
}
/**
 *
 */
ArithExpr* EFParser::arith_expr()
{
    D("now in arith_expr");
    TermExpr* t_term = term_expr();
    if (t_term == NULL)
    {
        return NULL;
    }
    return new ArithExpr(t_term,arith_expr_r());
}
/**
 *
 */
ArithExprR* EFParser::arith_expr_r()
{
    D("now in arith_expr_r");
    Token* token = this->look;
    if (token->id != PLUS
        && token->id != MINUS)
    {
        return NULL;
    }
    move();    //略过加减号
    TermExpr* t_term = term_expr();
    if (t_term == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
        //错误处理
    }
    return new ArithExprR(token,t_term,arith_expr_r());
}
/**
 *
 */
TermExpr* EFParser::term_expr()
{
    D("now in term_expr");
    FactorExpr* t_factor = factor();
    if (t_factor == NULL)
    {
        return NULL;
    }
    return new TermExpr(t_factor,term_expr_r());
}
/**
 *
 */
TermExprR* EFParser::term_expr_r()
{
    D("now in term_expr_r");
    Token* token = this->look;

    if (token->id != STAR
        && token->id != SLASH
        && token->id != PERCENT
        && token->id != DOUBLESLASH)
    {
        return NULL;
    }
    move();        //略过*/ // %符号
    FactorExpr* t_factor = factor();
    if (t_factor == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new TermExprR(token,t_factor,term_expr_r());
}
/**
 *
 */
FactorExpr* EFParser::factor()
{
    D("now in factor");
    Token* token = this->look;

    if (token->id == PLUS
        || token->id == MINUS
        || token->id == TILDE)
    {
        FactorExpr* t_factor = factor();
        if (t_factor == NULL)
        {
            throw_error(ERROR_KEY_MARKER);
        }
        else
        {
            return new FactorExpr(token,t_factor);
        }
    }
    PowerExpr* t_power = power();
    if (t_power == NULL)
    {
        return NULL;
    }
    return new FactorExpr(t_power);
}
/**
 *
 */
PowerExpr* EFParser::power()
{
    D("now in power");
    AtomExpr* t_atom = atom();
    if (t_atom == NULL)
    {
        return NULL;
    }
    bool b_match = match(DOUBLESTAR);
    if (b_match == false)
    {
        return new PowerExpr(t_atom);
    }
    FactorExpr* t_factor = factor();
    if (t_factor == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
        //错误处理
    }
    return new PowerExpr(t_atom,t_factor);
}
/**
 *
 */
AtomExpr* EFParser::atom()
{
    D("now in atom");
    TokenFlag token_flag = look->id;

    switch (token_flag)
    {
    case LPAR:                    //(
        return tuple_expr();
    case LSQB:                    //[
        return map_expr();
    case NUMBER:                  //NUMBER
        return number_expr();
    case STRING:                  //STRING
        return string_expr();
    case NULL_MARKER:             //null
    case TRUE_MARKER:             //true
    case FALSE_MARKER:            //false
        return keyword_expr();
    case NAME:                    //NAME
        return name_expr();
    default:   
        return NULL;
    }
}
/**
 *
 */
TupleExpr* EFParser::tuple_expr()
{
    D("now in tuple_expr");
    bool b_match = match(LPAR);
    if (b_match == false)
    {
        return NULL;
    }
    TupleVariableExpr* tuple_vaiable = tuple_variable_expr();
    if (tuple_vaiable == NULL)
    {
        return NULL;
    }
    b_match = match(RPAR);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new TupleExpr(tuple_vaiable);
}
/**
 *
 */
TupleVariableExpr* EFParser::tuple_variable_expr()
{
    D("now in tuple_variable_expr");
    Expr* t_expr = expr();
    if (t_expr == NULL)
    {
        return NULL;
    }
    return new TupleVariableExpr(t_expr,tuple_variable_expr_r());
}
/**
 *
 */
TupleVariableExpr* EFParser::tuple_variable_expr_r()
{
    D("now in tuple_variable_expr_r");
    bool b_match = match(COMMA);
    if (b_match == false)
    {
        return NULL;
    }
    Expr* t_expr = expr();
    if (t_expr == NULL)
    {
        //本来要做错误处理的，但是在语法分析时，可以容忍后面多一个逗号，所以
        //直接返回
        return NULL;
    }
    return new TupleVariableExpr(t_expr,tuple_variable_expr_r());
}
/**
 *
 */
MapExpr* EFParser::map_expr()
{
    D("now in map_expr");
    bool b_match = match(LSQB);
    if (b_match == false)
    {
        return NULL;
    }
    MapVariableExpr* map_vaiable = map_variable_expr();
    if (map_vaiable == NULL)
    {
        return NULL;
    }
    b_match = match(RSQB);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new MapExpr(map_vaiable);
}
/**
 *
 */
MapVariableExpr* EFParser::map_variable_expr()
{
    D("now in map_variable_expr");
    Expr* t_expr_l = expr();
    if (t_expr_l == NULL)
    {
        return NULL;
    }
    bool b_match = match(EQUAL);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Expr* t_expr_r = expr();
    if (t_expr_r == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new MapVariableExpr(t_expr_l,t_expr_r,map_variable_expr_r());
}
/**
 *
 */
MapVariableExpr* EFParser::map_variable_expr_r()
{
    D("now in map_variable_expr_r");
    bool b_match = match(COMMA);
    if (b_match == false)
    {
        return false;
    }
    Expr* t_expr_l = expr();
    if (t_expr_l == NULL)
    {
        //可以容忍多一个逗号的出现
        return NULL;
    }
    b_match = match(EQUAL);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    Expr* t_expr_r = expr();
    if (t_expr_r == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new MapVariableExpr(t_expr_l,t_expr_r,map_variable_expr_r());
}
/**
 *
 */
NumberExpr* EFParser::number_expr()
{
    D("now in number_expr");
    Token* t_token = look;
    bool b_match = match(NUMBER);

    if (b_match == false)
    {
        return NULL;
    }
    return new NumberExpr(t_token);
}
/**
 *
 */
StringExpr* EFParser::string_expr()
{
    D("now in string_expr");
    Token* t_token = look;
    bool b_match = match(STRING);
    if (b_match == false)
    {
        return NULL;
    }
    return new StringExpr(t_token,string_expr());
}
/**
 *
 */
KeyWordExpr* EFParser::keyword_expr()
{
    D("now in keyword_expr");
    Token* t_token = look;
    if (NULL_MARKER != t_token->id &&
        TRUE_MARKER != t_token->id &&
        FALSE_MARKER != t_token->id
        )
    {
        return NULL;
    }
    move(); //略过这些关键字
    return new KeyWordExpr(t_token);
}
/**
 *
 */
NameExpr* EFParser::name_expr()
{
    D("now in name_expr");
    Token* token = look;
    bool b_match = match(NAME);

    if (b_match == false)
    {
        //其实这里更像要错误处理才好
        return NULL;
    }

    if (look->id == DOT)
    {
        return new NameExpr(token,module_invoke());
    }
    else if (look->id == LPAR)
    {
        return new NameExpr(token,fun_invoke());
    }
    else
    {
        return new NameExpr(token,NULL);
    }
}
/*    fun_invoke -> '(' parameters ')'
 *                fun_invoke
 *                   |
 *               parameters
 */
FunInvokeExpr* EFParser::fun_invoke()
{
    D("now in fun_invoke");
    Token* t_token = look;//为传递节点位置预留

    bool b_match = match(LPAR);
    if (b_match == false)
    {
        return NULL;
    }
    ParametersExpr* parameter = parameters();

    b_match = match(RPAR);

    if (b_match == false)
    {
        throw_error(ERROR_NO_RPAR);
    }

    if (parameter == NULL)
    {
        //无参
        return new FunInvokeExpr(t_token->row,t_token->col);
    }
    else
    {
        return new FunInvokeExpr(parameter);
    }
}
/**
 *
 */
ModuleInvokeExpr* EFParser::module_invoke()
{
    D("now in module_invoke");
    bool b_match = match(DOT);

    if (b_match == false)
    {
        return NULL;
    }
    Token* token = look;

    b_match = match(NAME);
    if (b_match == false)
    {
        throw_error(ERROR_KEY_MARKER);
    }
    return new ModuleInvokeExpr(token,module_invoke());
}

EF_NAMESPACE_END

