/*-------------------------------------------------------------------
 * Purpose:
 *         compiler
 * Time:
 *         2012年1月7日 19:48:43
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _COMPILER_H_2012_1_7_lisency
#define _COMPILER_H_2012_1_7_lisency

#include "Node.h"
#include "Object.h"

EF_NAMESPACE_BEGIN

/**
 * 编译接口
 * 我们不如将AST到字节码的过程称作中端，而这个类
 * 便实现中端
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
    * @ast_root 抽象语法树的根节点
    * @op_code 字节码流
    **/
    virtual int32_t compile(Node* ast_root,CodeObject*& op_code);
protected:

private:
};
/**
 * 本语言使用的编译方案
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
 * 使用SSA IR表示方案生成字节码
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

