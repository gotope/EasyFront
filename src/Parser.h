/*-------------------------------------------------------------------
 * Purpose:
 *         Parser.h ���﷨����
 *          Parser�����ģʽ�ľ��ף�ʹ�ôʷ���������Ϊ���캯���ĺô�ʹparser
 *          ���õ����������ַ��룬��ǰʹ�õ�string��file��ȷ�ķֹ�����ʹ����
 *          scanner������Ҫ��ȷ�ֹ���������Ҳ��Ҫ��ȷ�ķֹ����Ӷ�������
 *          �������ࡣ���ۣ�ʹ�ø��߼��Ĳ���Ҫ�ȵͼ��Ĳ���ã����Ƿ�װ�ı�Ȼ
 *          
 *          �ôʷ��������������C++������ʶ��< <�����Ǽ��ţ�����ģ�忪ʼ��־
 *          �������л������Ե��ķ�
 * Time:
 *         2011��12��1�� 21:15:18
 * Author:
 *         ������
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
 * ��û�����ӿڵı�Ҫ��
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
    * ��ʼ����ֱ�Ӵ����ļ��������������Ǵ���ʷ�������
    * @scanner�ʷ�������
    **/
    Parser(Scanner &t_scanner);
    Scanner& scanner;//����ִ�
    std::string file_path;
private:
};

/**
 *  ������ʹ�õ��﷨������
 *  ��Ȼ�����˽ӿڣ������Ժ��ò��û������
 *  ��������ж���ļ�����ģ���װ
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
    *  ��ǰ��������
    **/
    void move();
    /**
    *  �鿴�Ƿ�ƥ��
    *  ��û��ƥ���ܳ��쳣
    **/
    bool match(TokenFlag token_flag);
    /**
    * ���ݴ���ID�׳��쳣
    **/
    void throw_error(int error_id);
    /**
    * file_input -> StmtSeq ENDMARKER
    * һ���ļ�һ��ģ��
    * �����﷨���ĸ��ڵ�
    **/
    Stmt* module();
    /**
    * ���Ҹ����stmt
    *   file_input -> StmtSeq ENDMARKER
    *           StmtSeq
    *           /     \
    *       stmt    StmtSeq
    **/
    StmtSeq* stmts();
    /**
    * ƥ��һ��stmt
    * stmt -> simple_stmt | compound_stmt | suite
    **/
    Stmt* stmt();
    /**
    * ����һ�������
    * simple_stmt -> small_stmt (';' small_stmt)*[';'] NEWLINE
    **/
    SimpleStmt* simple_stmt();
    /**
    * ����һ��С���
    * small_stmt -> assign |
    *            augassign |
    *             del_stmt |
    *          import_stmt
    **/
    SmallStmt* small_stmt();
    /**
    * ƥ��SimpleStmt����Ĳ���
    * SmallStmtList -> (';' small_stmt)*
    **/
    SimpleStmt* small_stmt_list();
    /**
    * ɾ�����
    **/
    DelStmt* del_stmt();
    /**
    * �������
    **/
    ImportStmt* import_stmt();
    /**
    * �����йؼ��ֵ���䣬����ֵ���
    **/
    Assign* assign_stmt();
    /**
    * ����һ��ֱ�Ӹ�ֵ���ڵ�
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
    * ����һ���������
    * compound_stmt -> if_stmt |
    *               while_stmt |
    *                 for_stmt |
    *                 try_stmt |
    *              fundef_stmt |
    *            classdef_stmt 
    **/
    CompoundStmt* compound_stmt();
    /**
    * ����if���ڵ�
    * if_stmt -> 'if' expr ':' suite 
    *         ('elif' expr ';' suite) *
    *             ['else' ':' suite]
    *
    *                    if
    *                /    |    \      \
    *               /     |     \       \
    *            expr  stmt     elif     else
    *                        /  |  \
    *                ����������else���
    **/
    IfStmt* if_stmt();
    /**
    * while���
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
    * һ���Զ��ŷָ�Ĳ���
    **/
    ParameterExprAtom* atom_para();
    /**
    * �Ƿ�Ϊһ�����ʽ
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
    Token *look;                        //��ǰ���ʷ���Ԫ
    /**
    * �ô����Ƿ���һ���Ƚϲ�����
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
    * �Ƿ�������������
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

