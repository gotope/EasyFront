/*-------------------------------------------------------------------
* Purpose:
*         execute bytecode
* Time:
*         2012��2��26�� 21:13:36
* Author:
*         ������
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
 * ִ���ֽ���
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
     * �������͵��ҵ���intֵ
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
     * ��ջ��Ԫ�ش����id��ָ����name��
     */
    int32_t store_name(int32_t id);
    /**
     * ����ȽϷ�����ջ��������Ԫ�����Ƚ�
     */
    int32_t compare_op(int32_t arg);
    /**
     * ����arg��ֵ��ִ��ջ�����boolԪ��
     */
    int32_t push_bool(bool arg);
    /**
     * ���ݲ����ĸ������ú���
     */
    int32_t call_function(int32_t arg);
    /**
     * �������Ƚ�
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
     * ������ת
     */
    Instruction* jump_absulute(int32_t arg);
    /**
     * 
     */
    int32_t stack_push(Object* ob,ObjectType ty);
    /**
     * ��Ԫ��
     */
    int32_t binary_add(int32_t arg);
    /**
     * ��
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
    //��ΪҪ��ָ�����ת�������б�Ҫ�����е�ָ��ȫ�����ݽ���

    ExeStack run_time_stack;    //����ִ��ջ
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

