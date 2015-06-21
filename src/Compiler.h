/*-------------------------------------------------------------------
 * Purpose:
 *         compiler
 * Time:
 *         2012��1��7�� 19:48:43
 * Author:
 *         ������
--------------------------------------------------------------------*/

#ifndef _COMPILER_H_2012_1_7_lisency
#define _COMPILER_H_2012_1_7_lisency

#include "Node.h"
#include "Object.h"

EF_NAMESPACE_BEGIN

/**
 * ����ӿ�
 * ���ǲ��罫AST���ֽ���Ĺ��̳����жˣ��������
 * ��ʵ���ж�
 **/
class Compiler
    :public Base
{
public:
    /**
     * 
     */
    Compiler();
    /**
     * 
     */
    ~Compiler();
    /**
    * 
    * @ast_root �����﷨���ĸ��ڵ�
    * @op_code �ֽ�����
    **/
    virtual int32_t compile(Node* ast_root,CodeObject*& op_code);
protected:

private:
};
/**
 * ������ʹ�õı��뷽��
 **/
class EfCompiler
    :public Compiler
{
public:
    /**
     * 
     */
    EfCompiler();
    /**
     * 
     */
    ~EfCompiler();
    /**
     * 
     */
    virtual int32_t compile(Node* ast_root,CodeObject*& op_code);
protected:

private:
};
/**
 * ʹ��SSA IR��ʾ���������ֽ���
 **/
class SSACompiler
    :public Compiler
{
public:
    /**
     * 
     */
    SSACompiler();
    /**
     * 
     */
    ~SSACompiler();
    /**
     * 
     */
    virtual int32_t compile(Node* ast_root,CodeObject*& op_code);
protected:
    
private:
};

EF_NAMESPACE_END

#endif // _COMPILER_H_2012_1_7_lisency

