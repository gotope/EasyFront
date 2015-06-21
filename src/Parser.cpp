/*-------------------------------------------------------------------
 * Purpose:
 *         Parser.cpp
 * Time:
 *         2011��12��1�� 21:16:08
 * Author:
 *         ������
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
    //���ýڵ���ļ���
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
 * ��ǰ�鿴һ������
 */
void EFParser::move()
{
    look = scanner.nextToken();    //��ǰ�����鿴
#ifdef EF_DEBUG
    look->print(debug_stream);
#endif
    //���ﻹ�������Ƿ񵽴��ļ�ĩβ���жϣ��Ƿ���Ҫ��
    return;
}
/**
 * ���ݵ�ǰ�����token���鿴���ű����Ƿ����
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
 * �׳��쳣�����������
 **/
void EFParser::throw_error(int error_id)
{
    //�׳��쳣���ļ����쳣����
    EFExc exc(file_path,look->row,look->col,error_id);
    throw exc;
}
/**
 * ����ģ��
 * file_input -> StmtSeq ENDMARKER��ģ��
 *  �����﷨���ĸ��ڵ�
 **/
Stmt* EFParser::module()
{
    D("now in module");
    move(); //������ǰ��һ������
    Stmt *stmt = stmts();
    bool b_match = match(ENDMARKER);
    if (b_match == false)
    {
        throw_error(ERROR_FILE_END_NOFORMOR);
    }
    return stmt;
}
/**
 * ���ļ��ݹ�ɨ�裬ƥ������stmt
 * StmtSeq -> (NEWLINE | Stmt)*
 *           StmtSeq
 *           /     \
 *       stmt    StmtSeq
 **/
StmtSeq* EFParser::stmts()
{
    D("now in stmts");
    //����
    if (match(ENDMARKER) == true)
    {
        return NULL;
    }
    //����NEWLINE��ȫ���Թ�
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
 * �����ļ������������ƥ����Ӧ����������ƥ��stmt
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
    //������Ҫ�鿴firstset��������ǰ�ƶ�һ���ַ�
    //move();

    TokenFlag token_flag = this->look->id;

    switch (token_flag)
    {
    case IF_MARKER:                         //��if���
    case WHILE_MARKER:                      //��whileѭ��
    case FOR_MARKER:                        //��forѭ��
    case FUN_MARKER:                        //�Ǻ�������
    case CLASS_MARKER:                      //���ඨ��
    case TRY_MARKER:                        //��try���
        return compound_stmt();
    default:
        return simple_stmt();
        //�����ȫ����SimpleStmt
    //case DEL_MARKER:                        //ɾ�����
    //case IMPORT_MARKER:                     //�������
    //case NAME:                              //�Ǹ�ֵ�����
    //    return simple_stmt();
    }
}
/**
 * ����һ�������
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

    match(SEMI);  //�Թ��ֺţ��ֺſ��п���

    bool b_match = match(NEWLINE);

    /*δƥ�䵽 NEWLINE���ţ�����*/
    if (b_match == false)
    {
        throw_error(ERROR_NO_NEWLINE);
    }

    return t_simple_stmt;
}
/**
 * ����һ��С���
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
 * ƥ��SimpleStmt����Ĳ���
 * SmallStmtList -> (';' small_stmt)*
 **/
SimpleStmt* EFParser::small_stmt_list()
{
    D("now in small_stmt_list");
    bool b_match = match(SEMI);

    /*��û��ƥ�䵽�ֺţ��򷵻�NULL*/
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
    Expr* t_expr = expr();        //�����Ҳ��ĵ�һ��expr
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
        //assign���û�к���Ĳ���ʱ��ʾֻ��һ��name
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
    move();    //�Թ���������,δ����match����ʱʹ��move

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
    case IF_MARKER:                      return if_stmt();      //��if���
    case WHILE_MARKER:                   return while_stmt();   //��whileѭ��
    case FOR_MARKER:                     return for_stmt();     //��forѭ��
    case FUN_MARKER:                     return fun_stmt();     //�Ǻ�������
    case CLASS_MARKER:                   return cla_stmt();     //���ඨ��
    case TRY_MARKER:                     return try_stmt();     //��try���
    default:
        return NULL;                        //��������ʶ�����
    }
}
/**
 * ����if���ڵ�
 *                    if
 *                /    |    \      \
 *               /     |     \       \
 *            expr  stmt     elif     else
 *                        /  |  \
 *                ����������else���
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
 * ע��if��elif����һ��If�ṹ
 **/
ElifStmt* EFParser::elif_stmt()
{
    D("now in elif_stmt");
    bool b_match = match(ELIF_MARKER);        //ƥ��elif���
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
    //finally����Ϊ��
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
        //do nothing,�������Ϊ��
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
    Token* token = this->look;  //��¼��������
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
        // do nothing ������������Ϊ��
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
    //��¼����
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
        //do nothing����Ϊ��
    }
    Token* t_token = look;
    if (t_token->id == ENDMARKER)
    {
        return new Suite(t_stmts);
    }
    else if (t_token->id == DEDENT)
    {
        move(); //�Թ�������
        return new Suite(t_stmts);
    }
    throw_error(ERROR_KEY_MARKER);
    return NULL;
}
/**
 * expr -> con_expr | fun_invoke | module_invoke | simple_expr
 * ��Ȼ������һ��NFA������Ӱ�����ǵĳ���
 * Ԥ�������Ϊ
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
        //+-~��,facor -> ('+' | '-' | '~' ) factor | power
    case PLUS:              //+
    case MINUS:             //-
    case TILDE:             //~
    case LPAR:              //( tuple parameter
    case LSQB:              //[ map parameter
    case STAR:              //*
    case NUMBER:            //����
    case STRING:            //�ַ���
    case NAME:              //��ʶ��
    case NULL_MARKER:       //null
    case FALSE_MARKER:      //false
    case TRY_MARKER:        //true
    case LAMBDA_MARKER:     //lambda
    case NOT_MARKER:        //not
        return con_expr();
    }
    //!��,ȡ��,�ʷ���������Ϊ���ظ�̾�ţ���������
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
        return NULL;    //�޲�
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
        move();    //�Թ��Ǻ�
        b_match = match(NAME);
        if (b_match == false)
        {
            //������
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
    //map����
    else if (token_flag == DOUBLESTAR)
    {
        move();    //�Թ�˫�Ǻ�
        b_match = match(NAME);
        if (b_match == false)
        {
            //������
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
    //��ͨ����
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
    //tuple����
}

/**
 * �������
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
        // do nothing ��������Ϊ��
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
 * ����û��ʵ��&&��||���ȣ����������Ҫʵ�ֵĻ����ڴʷ�������
 * ������ֱ�ӱ�־ΪOR_MARKER��
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

    move(); //�Թ��ȽϷ���
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
    move();        //�Թ����������Ʒ���
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
    move();    //�Թ��Ӽ���
    TermExpr* t_term = term_expr();
    if (t_term == NULL)
    {
        throw_error(ERROR_KEY_MARKER);
        //������
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
    move();        //�Թ�*/ // %����
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
        //������
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
        //����Ҫ��������ģ��������﷨����ʱ���������̺����һ�����ţ�����
        //ֱ�ӷ���
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
        //�������̶�һ�����ŵĳ���
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
    move(); //�Թ���Щ�ؼ���
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
        //��ʵ�������Ҫ������ź�
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
    Token* t_token = look;//Ϊ���ݽڵ�λ��Ԥ��

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
        //�޲�
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

