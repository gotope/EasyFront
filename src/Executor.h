/*-------------------------------------------------------------------
* Purpose:
*         execute bytecode
* Time:
*         2012年2月26日 21:13:36
* Author:
*         张彦升
--------------------------------------------------------------------*/

#ifndef _EXECUTOR_H_2012_2_26_lisency
#define _EXECUTOR_H_2012_2_26_lisency

#include "Base.h"
#include "Opcode.h"
#include "object.h"
#include "Exception.h"

#include <stack>
#include <stdint.h>

EF_NAMESPACE_BEGIN

/**
 * 执行字节码
 */
class Executor
    :public Base
{
public:
	/**
     *
     */
    Executor(CodeObject* t_code_object);
    /**
     *
     */
    ~Executor();
    /**
     * 
     */
    inline int32_t throw_error(int32_t error_id)
    {
        EFExc exc("",-1,-1,error_id);
        throw exc;
        return 0;
    }
    /**
     * 
     */
    int32_t excute();
    /**
     * 
     */
    int32_t load_name(int32_t id);
    /**
     * 根据整型的找到该int值
     */
    int32_t load_int(int32_t id);
    /**
     * 
     */
    int32_t load_double(int32_t id);
    /**
     * 
     */
    int32_t load_const(int32_t id);
    /**
     * 
     */
    int32_t load_object(int32_t id);
    /**
     * 将栈顶元素存入该id所指定的name中
     */
    int32_t store_name(int32_t id);
    /**
     * 传入比较符，对栈顶的两个元素做比较
     */
    int32_t compare_op(int32_t arg);
    /**
     * 根据arg的值向执行栈中添加bool元素
     */
    int32_t push_bool(bool arg);
    /**
     * 根据参数的个数调用函数
     */
    int32_t call_function(int32_t arg);
    /**
     * 弹出并比较
     */
    Instruction* pop_jump_if_false(int32_t arg);
    /**
     * 
     */
    Instruction* pop_jump_if_true(int32_t arg);
    /**
     * 
     */
    Instruction* jump_forword(int32_t arg);
    /**
     * 绝对跳转
     */
    Instruction* jump_absulute(int32_t arg);
    /**
     * 
     */
    int32_t stack_push(Object* ob,ObjectType ty);
    /**
     * 二元加
     */
    int32_t binary_add(int32_t arg);
    /**
     * 减
     */
    int32_t binary_subscr(int32_t arg);
    /**
     * 
     */
    int32_t binary_multiply(int32_t arg);
    /**
     * 
     */
    int32_t binary_ture_divide(int32_t arg);
    /**
     * 
     */
    int32_t binary_modulo(int32_t arg);
    /**
     * 
     */
    int32_t binary_floor_divide(int32_t arg);
    /**
     * 
     */
    int32_t binary_or(int32_t arg);
    /**
     * 
     */
    int32_t binary_xor(int32_t arg);
    /**
     * 
     */
    int32_t make_function(int32_t arg);
    /**
     * 
     */
    ValueEntry* get_values();
protected:
    //因为要在指令间跳转，所以有必要将所有的指令全部传递进来

    ExeStack run_time_stack;    //运行执行栈
    NameEntry names;

    ValueEntry values;
    ConstStringEntry strings;
    IntEntry ints;
    DoubleEntry doubles;
    CodeObjectEntry codes;

private:
    CodeObject* code_object;
};

EF_NAMESPACE_END

#endif // _EXECUTOR_H_2012_2_26_lisency

