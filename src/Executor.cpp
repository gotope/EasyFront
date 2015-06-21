/*-------------------------------------------------------------------
* Purpose:
*         byte code executor
* Time:
*         2012��2��26�� 21:16:56
* Author:
*         ������
--------------------------------------------------------------------*/

#include "Executor.h"
#include "SysLib.h"
#include "Debug.h"

#include <vector>
#include <iostream>

EF_NAMESPACE_BEGIN
/**
 * 
 */
Executor::Executor( CodeObject* t_code_object )
:code_object(t_code_object),
names(t_code_object->get_names()),
strings(t_code_object->get_const()),
ints(t_code_object->get_interger()),
doubles(t_code_object->get_floats()),
codes(t_code_object->get_codes())
{
    return;
}
/**
 * 
 */
Executor::~Executor()
{
    return;
}
/**
 * ������һ��ָ���ƫ��λ��
 */
int32_t Executor::excute()
{
    Instruction* instr = code_object->next_instr();

    while (instr != NULL)
    {

        Op opcode = instr->i_opcode;
        int32_t arg = instr->i_oparg;

        int32_t ret = 1;

        switch (opcode)
        {
        case LOAD_NAME:
            ret = load_name(arg);
            if (ret == -1)
            {
                throw_error(ERROR_NO_FOUND_SYMBOL);
            }
            break;
        case LOAD_INT:
            ret = load_int(arg);
            if (ret == -1)
            {
                throw_error(ERROR_NO_NUMBER);
            }
            break;
        case LOAD_FLOAT:
            ret = load_double(arg);
            if (ret == -1)
            {
                throw_error(ERROR_NO_NUMBER);
            }
            break;
        case LOAD_CONST:
            ret = load_const(arg);
            if (ret == -1)
            {
                throw_error(ERROR_NO_STRING);
            }
            break;
        case LOAD_OBJECT:
            ret = load_object(arg);
            if (ret == -1)
            {
                throw_error(ERROR_NO_OBJECT);
            }
            break;
        case STORE_NAME:
            ret = store_name(arg);
            if (ret == -1)
            {
                throw_error(ERROR_NO_FOUND_SYMBOL);
            }
            break;
        case COMPARE_OP:
            ret = compare_op(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case MAKE_FUNCTION:
            ret = make_function(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case CALL_FUNCTION:
            ret = call_function(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case POP_JUMP_IF_FALSE:
            instr = pop_jump_if_false(arg);
            //���instrΪ�棬˵����Ҫ��ת
            if (instr == NULL)
            {
                break;
            }
            else
            {
                continue;
            }
        case POP_JUMP_IF_TRUE:
            instr = pop_jump_if_true(arg);
            //���instrΪ�棬˵����Ҫ��ת
            if (instr == NULL)
            {
                break;
            }
            else
            {
                continue;
            }
            break;
        case JUMP_FORWARD:
            instr = jump_forword(arg);
            //���instrΪNULL��˵���ѵ�ĩβ
            continue;
        case JUMP_ABSOLUTE:
            instr = jump_absulute(arg);
            if (instr == NULL)
            {
                //����
                return 1;
            }
            continue;
        case BINARY_ADD:
        case INPLACE_ADD:
            ret = binary_add(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case BINARY_SUBSCR:
        case INPLACE_SUBTRACT:
            ret = binary_subscr(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case BINARY_MULTIPLY:
        case INPLACE_MULTIPLY:
            ret = binary_multiply(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case BINARY_TRUE_DIVIDE:
        case INPLACE_TRUE_DIVIDE:
            ret = binary_ture_divide(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case BINARY_MODULO:
        case INPLACE_MODULO:
            ret = binary_modulo(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case BINARY_FLOOR_DIVIDE:
        case INPLACE_FLOOR_DIVIDE:
            ret = binary_floor_divide(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case BINARY_OR:
        case INPLACE_OR:
            ret = binary_or(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case BINARY_XOR:
        case INPLACE_XOR:
            ret = binary_xor(arg);
            if (ret == -1)
            {
                throw_error(ERROR_WRONG_TYPE);
            }
            break;
        case BINARY_AND:
        case INPLACE_AND:
            break;
        case BINARY_LSHIFT:
        case INPLACE_LSHIFT:
            break;
        case BINARY_RSHIFT:
        case INPLACE_RSHIFT:
            break;
        case UNARY_INVERT:
            break;
        case UNARY_NEGATIVE:
            break;
        case UNARY_NOT:
            break;
        case BINARY_POWER:
            break;
        default:
            break;
        }
        instr = code_object->next_instr();
    }
    return 1;
}
/**
 * ����name��id�ڵ�ǰ���ջ�в��Ҹ�name��ֵ
 */
int32_t Executor::load_name(int32_t id)
{
    ValueEntry::iterator iter_value = values.find(id);

    Object* ob = NULL;
    //δ�ҵ��÷��ţ�˵������δ����
    if (iter_value == values.end())
    {
        NameEntry::iterator iter_name = names.find(id);

        //D(names[id]);
        if (iter_name == names.end())
        {
            return -1;
        }
        //�ҵ�ϵͳ�����ؼ���
        std::string name = iter_name->second;
        ob = reserver(name);
        run_time_stack.push(new ObjectObject(ob,FUN_TYPE));    //����ֵ����ջ��
        return 1;
    }
    run_time_stack.push(iter_value->second);    //����ֵ����ջ��

    return 1;
}
/**
 * 
 */
int32_t Executor::load_int( int32_t id )
{
    IntEntry::iterator iter_int = ints.find(id);

    //δ�ҵ��÷��ţ�˵������δ����
    if (iter_int == ints.end())
    {
        return -1;
    }
    int32_t value = iter_int->second;
    LongObject* ob = new LongObject(value);
    run_time_stack.push(new ObjectObject(ob,LONG_TYPE));    //����ֵ����ջ��

    return 1;
}
/**
 * 
 */
int32_t Executor::load_double( int32_t id )
{
    DoubleEntry::iterator iter_double = doubles.find(id);

    //δ�ҵ��÷��ţ�˵������δ����
    if (iter_double == doubles.end())
    {
        return -1;
    }
    double value = iter_double->second;
    FloatObject* ob = new FloatObject(value);
    run_time_stack.push(new ObjectObject(ob,DOUBLE_TYPE));    //����ֵ����ջ��

    return 1;
}
/**
 * 
 */
int32_t Executor::load_const( int32_t id )
{
    ConstStringEntry::iterator iter_string = strings.find(id);

    //δ�ҵ��÷��ţ�˵������δ����
    if (iter_string == strings.end())
    {
        return -1;
    }
    std::string value = iter_string->second;
    StringObject* ob = new StringObject(value);
    run_time_stack.push(new ObjectObject(ob,STRING_TYPE));    //����ֵ����ջ��

    return 1;
}
/**
 * 
 */
int32_t Executor::load_object( int32_t id )
{
    CodeObjectEntry::iterator iter_code = codes.find(id);

    //δ�ҵ��÷��ţ�˵������δ����
    if (iter_code == codes.end())
    {
        return -1;
    }
    CodeObject* ob = iter_code->second;
    run_time_stack.push(new ObjectObject(ob,CODE_TYPE));    //����ֵ����ջ��

    return 1;
}
/**
 * �洢
 */
int32_t Executor::store_name( int32_t id )
{
    if (run_time_stack.empty() == true)
    {
        return -1;
    }
    ObjectObject* ob = run_time_stack.top();  //�õ�ջ��Ԫ��
    run_time_stack.pop();   //������
    values[id] = ob;
    return 1;
}
/**
 * 
 */
int32_t Executor::compare_op( int32_t arg )
{
    //����ջ������Ԫ��
    ObjectObject* top1 = run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* top2 = run_time_stack.top();
    run_time_stack.pop();

    //������load�����ұߵķ��ţ����ԱȽϵ�ʱ��������
#define COMPARE(right,left,arg,ty)                  \
    switch (arg)                                    \
    {                                               \
    case Cmp_EQ:                                    \
        push_bool(*((ty*)right) == (*(ty*)left));   \
        break;                                      \
    case Cmp_NE:                                    \
        push_bool(*((ty*)right) != (*(ty*)left));   \
        break;                                      \
    case Cmp_LT:                                    \
        push_bool(*((ty*)right) < (*(ty*)left));    \
        break;                                      \
    case Cmp_LE:                                    \
        push_bool(*((ty*)right) <= (*(ty*)left));   \
        break;                                      \
    case Cmp_GT:                                    \
        push_bool(*((ty*)right) > (*(ty*)left));    \
        break;                                      \
    case Cmp_GE:                                    \
        push_bool(*((ty*)right) >= (*(ty*)left));   \
        break;                                      \
    default:                                        \
        return -1;                                  \
    }

    ObjectType ty = top1->get_type();
    Object* ob1 = top2->get_ob();
    Object* ob2 = top1->get_ob();

    /**
     * �Ƚϵ�ʱ�����һ��bug��
     * ʹ�ø�������int�ͱȽϣ���������ת�����⣬�Ӷ�ʹ�ø�������Զ��������
     * ������⣬��ʹ�ñ�׼�ıȽϲ�����ֻ�ṩ== <����ʱ�������˳���������>
     * �ȽϽ�����<����������ʱright������ǰ������������������ͣ��������
     * ���͵�bool <��������float���͵Ĳ������Ӷ���float���͵�������������
     * ������ı�ʾ������������Ĵ�С
     */
    switch (ty)
    {
    case LONG_TYPE:             COMPARE(ob1,ob2,arg,LongObject);
        break;
    case DOUBLE_TYPE:           COMPARE(ob1,ob2,arg,FloatObject);
        break;
    case STRING_TYPE:           COMPARE(ob1,ob2,arg,StringObject);
        break;
    case CODE_TYPE:             COMPARE(ob1,ob2,arg,CodeObject);
        break;
    case FUN_TYPE:              COMPARE(ob1,ob2,arg,FunObject);
        break;
    }
#undef COMPARE
    return 1;
}
/**
 * 
 */
int32_t Executor::push_bool( bool arg )
{
    LongObject* ob_true = new LongObject(1);
    LongObject* ob_false = new LongObject(0);
    
    if (arg)
    {
        run_time_stack.push(new ObjectObject(ob_true,LONG_TYPE));
    }
    else
    {
        run_time_stack.push(new ObjectObject(ob_false,LONG_TYPE));
    }
    return 1;
}
/**
 * 
 */
int32_t Executor::call_function( int32_t arg )
{
    int32_t count = arg;
    std::vector<ObjectObject*> args;  //�洢���в���
    ObjectObject* ob = NULL;

    /*
    std::vector<int32_t> vars = code_object->get_vars();
    int32_t var_size = vars.size();

    for (int i = var_size - 1;i >= 0;i --)
    {
        //load_name(vars[i]);
        if (- 1 == store_name(vars[i]))
        {
            debug_stream << "" << std::endl;
            return -1;
        }
    }
    for (int i = 0;i < var_size;i ++)
    {
        load_name(vars[i]);
    }
    */
    while (count > 0)
    {
        ob = run_time_stack.top();
        run_time_stack.pop();
        args.push_back(ob);
        count--;
    }
    //���һ��Ӧ���Ǻ�������
    ob = run_time_stack.top();
    run_time_stack.pop();

    //assert(ob->get_type() == FUN_TYPE);
    FunObject* fun_ob = (FunObject*)ob->get_ob();
    fun_ob->invoke(args);
    return 1;
}
/**
 * ��������ת
 */
Instruction* Executor::pop_jump_if_false( int32_t arg )
{
    ObjectObject* ob = (ObjectObject*)run_time_stack.top();
    run_time_stack.pop();

    //���Ϊ�٣�����ת
    if (*ob == false)
    {
        return code_object->next_instr(arg);
    }
    return NULL;
}

Instruction* Executor::pop_jump_if_true( int32_t arg )
{
    ObjectObject* ob = (ObjectObject*)run_time_stack.top();
    run_time_stack.pop();

    //���Ϊ�٣�����ת
    if (*ob == true)
    {
        return code_object->next_instr(arg);
    }
    return NULL;
}
/**
 * 
 */
Instruction* Executor::jump_forword( int32_t arg )
{
    return code_object->next_instr(arg);
}
Instruction* Executor::jump_absulute(int32_t arg)
{
    return code_object->next_instr(arg);
}
/**
 * 
 */
int32_t Executor::binary_add(int32_t arg )
{
    ObjectObject* ob_top1 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* ob_top2 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    ObjectObject* ob_result = *ob_top1 + *ob_top2;
    run_time_stack.push(ob_result);
    return 1;
}
/**
 * 
 */
int32_t Executor::binary_subscr( int32_t arg )
{
    ObjectObject* ob_top1 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* ob_top2 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    ObjectObject* ob_result = *ob_top2 - *ob_top1;
    run_time_stack.push(ob_result);
    return 1;
}
/**
 * 
 */
int32_t Executor::binary_multiply( int32_t arg )
{
    ObjectObject* ob_top1 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* ob_top2 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    ObjectObject* ob_result = *ob_top2 * *ob_top1;
    run_time_stack.push(ob_result);
    return 1;
}
/**
 * 
 */
int32_t Executor::binary_ture_divide( int32_t arg )
{
    ObjectObject* ob_top1 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* ob_top2 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    ObjectObject* ob_result = *ob_top2 / *ob_top1;
    run_time_stack.push(ob_result);
    return 1;
}
/**
 * 
 */
int32_t Executor::binary_modulo( int32_t arg )
{
    ObjectObject* ob_top1 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* ob_top2 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    ObjectObject* ob_result = *ob_top2 % *ob_top1;
    run_time_stack.push(ob_result);
    return 1;
}
/**
 * 
 */
int32_t Executor::binary_floor_divide( int32_t arg )
{
    ObjectObject* ob_top1 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* ob_top2 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    ObjectObject* ob_result = *ob_top2 / *ob_top1;

    ob_result = ob_result->to_longobject();
    run_time_stack.push(ob_result);
    return 1;
}
/**
 * 
 */
int32_t Executor::binary_or( int32_t arg )
{
    ObjectObject* ob_top1 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* ob_top2 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    ObjectObject* ob_result = *ob_top2 | *ob_top1;
    run_time_stack.push(ob_result);
    return 1;
}
/**
 * 
 */
int32_t Executor::binary_xor( int32_t arg )
{
    ObjectObject* ob_top1 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();
    ObjectObject* ob_top2 = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    ObjectObject* ob_result = (*ob_top2) ^ (*ob_top1);
    run_time_stack.push(ob_result);
    return 1;
}
/**
 * 
 */
int32_t Executor::make_function( int32_t arg )
{
    ObjectObject* ob_top = (ObjectObject*) run_time_stack.top();
    run_time_stack.pop();

    FunObject* ob = new FunObject((CodeObject*)ob_top->get_ob());

    run_time_stack.push(new ObjectObject(ob,FUN_TYPE));
    return 1;
}

ValueEntry* Executor::get_values()
{
    return &values;
}

EF_NAMESPACE_END

