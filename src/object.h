/*-------------------------------------------------------------------
 * Purpose:
 *         this file include the base object information
 *          Floatobject...will inherit from this
 * Time:
 *         2011年11月13日 10:23:36
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _OBJECT_H_2011_11_13_lisency
#define _OBJECT_H_2011_11_13_lisency

#include "Util.h"
#include "Base.h"
#include "Opcode.h"
#include "Debug.h"

#include <yvals.h>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>

EF_NAMESPACE_BEGIN

/**
 * 不得不承认，我还是没能掌握C++的多态性质，原本以为通过一个基类就可以动态
 * 的定位每一个在运行时刻申请的不同object类型对象，但是从实践来看，我将指针
 * 保存在堆栈中，弹出来之后发现多态性质表现不出来了。。
 */
enum ObjectType
{
    LONG_TYPE       = 0,
    DOUBLE_TYPE     = 1,
    STRING_TYPE     = 2,
    CODE_TYPE       = 3,
    FUN_TYPE        = 4,
};
class Object;
class ObjectObject;
class NumObject;
class LongObject;
class FloatObject;
class StringObject;

/**
 *  object是最基类，实现内存管理
 **/
class Object
    :public Base
{
public:
    /**
     * 
     */
    virtual ~Object() = 0;
    /**
     * 
     */
    virtual void print(std::ostream& cout);
    /**
     * 
     */
    virtual int32_t hash();
    bool operator == (const Object& right) const;
    bool operator < (const Object& right) const;
    bool operator != (const Object& right) const;
    bool operator <= (const Object& right) const;
    bool operator > (const Object& right) const;
    bool operator >= (const Object& right) const;

    operator bool() const;

    Object* operator + (const Object& right) const;
    Object* operator - (const Object& right) const;
    Object* operator * (const Object& right) const;
    Object* operator / (const Object& right) const;

    Object* operator += (const Object& right) const;
    Object* operator -= (const Object& right) const;
    Object* operator *= (const Object& right) const;
    Object* operator /= (const Object& right) const;

    Object* operator | (const Object& right) const;
    Object* operator ^ (const Object& right) const;

    //here defined some super data,like document
    std::string doc;
protected:
    /**
     * 
     */
    Object();
private:
    //iterator
    //data
    //data_lenght
    size_t refcnt;  //智能指针计数器

    Object* ob_next;    //形成双向链表，构成对象链
    Object* ob_pre;

    std::string name;        //for print
};
/**
 * 
 */
class ObjectObject
    :public Object
{
public:
	/**
     *
     */
    ObjectObject(Object* t_ob,ObjectType ty);
    /**
     *
     */
    virtual ~ObjectObject();

    bool operator == (const ObjectObject& right) const;
    bool operator < (const ObjectObject& right) const;
    bool operator != (const ObjectObject& right) const;
    bool operator <= (const ObjectObject& right) const;
    bool operator > (const ObjectObject& right) const;
    bool operator >= (const ObjectObject& right) const;
    operator bool() const;

    ObjectObject* operator + (const ObjectObject& right) const;
    ObjectObject* operator - (const ObjectObject& right) const;
    ObjectObject* operator * (const ObjectObject& right) const;
    ObjectObject* operator / (const ObjectObject& right) const;
    ObjectObject* operator % (const ObjectObject& right) const;

    ObjectObject* operator += (const ObjectObject& right) const;
    ObjectObject* operator -= (const ObjectObject& right) const;
    ObjectObject* operator *= (const ObjectObject& right) const;
    ObjectObject* operator /= (const ObjectObject& right) const;

    ObjectObject* operator | (const ObjectObject& right) const;
    ObjectObject* operator ^ (const ObjectObject& right) const;

    inline Object* get_ob() const
    {
        return ob;
    }
    inline ObjectType get_type() const
    {
        return type;
    }
    /**
     * 
     */
    ObjectObject* to_longobject();
    /**
     * 
     */
    ObjectObject* to_floatobject();
protected:
    Object* ob;
    ObjectType type;
private:
};
/**
 *  包括系统提供的基本数据类型
 **/
class GeneralObject
    :public Object
{
public:
    /**
     * 
     */
    virtual ~GeneralObject() = 0;
protected:
    /**
     * 
     */
    GeneralObject();
private:
};
/**
 *   抽象数据类型
 **/
class AbstractObject
    :public Object
{
public:
    /**
     * 
     */
    virtual ~AbstractObject() = 0;
protected:
    /**
     * 
     */
    AbstractObject();
private:
};
/**
 *
 **/
class ExceptionObject
    :public AbstractObject
{
public:
    /**
     * 
     */
    ExceptionObject();
    /**
     * 
     */
    ~ExceptionObject();
protected:
    
private:
};
/**
 * 字节码对象
 **/
class CodeObject
    :public AbstractObject
{
public:
    /**
     * 
     */
    CodeObject();
    /**
     * 该类仅是一个错误，不再使用,虽然没放到protected里面，但是记得勿动
     */
    CodeObject(CodeObject& right);

    bool operator == (const CodeObject& right) const;
    bool operator < (const CodeObject& right) const;
    bool operator != (const CodeObject& right) const;
    bool operator <= (const CodeObject& right) const;
    bool operator > (const CodeObject& right) const;
    bool operator >= (const CodeObject& right) const;
    /**
     * 
     */
    operator bool() const;

    CodeObject* operator + (const CodeObject& right) const;
    CodeObject* operator - (const CodeObject& right) const;
    CodeObject* operator * (const CodeObject& right) const;
    CodeObject* operator / (const CodeObject& right) const;
    CodeObject* operator % (const CodeObject& right) const;

    CodeObject* operator += (const CodeObject& right) const;
    CodeObject* operator -= (const CodeObject& right) const;
    CodeObject* operator *= (const CodeObject& right) const;
    CodeObject* operator /= (const CodeObject& right) const;

    CodeObject* operator | (const CodeObject& right) const;
    CodeObject* operator ^ (const CodeObject& right) const;
    /**
     * 
     */
    ~CodeObject();
    /**
     * 字节码对象的哈希值
     */
    virtual int32_t hash();
    /**
     * 打印字节码
     */
    virtual void print(std::ostream& cout);
    /**
     * 存入常量字符串
     */
    void set_consts(StrTable& consts_table);
    /**
     * 存入名字表
     */
    void set_names(StrTable& names_table);
    /**
     * 存入参数表
     */
    void set_varname(StrTable& varname_table);
    /**
     * 存入整数表
     */
    void set_interger(IntTable& inter_table);
    /**
     * 存入浮点数表
     */
    void set_floats(FloatTable& float_table);
    /**
     * 
     */
    void set_codes(CodeObjectEntry t_cods);
    /**
     * 存入块
     */
    void set_blocks(Basicblock** t_blocks);
    /**
     * 存入块大小
     */
    void set_block_size(int32_t block_size);
    /**
     * 
     */
    Instruction* next_instr();
    /**
     * 根据偏移得到指令
     */
    Instruction* next_instr(int32_t pos);
    /**
     * 
     */
    ConstStringEntry get_const();
    /**
     * 
     */
    NameEntry get_names();
    /**
     * 
     */
    NameEntry get_varnames();
    /**
     * 
     */
    IntEntry get_interger();
    /**
     * 
     */
    DoubleEntry get_floats();
    /**
     * 
     */
    CodeObjectEntry get_codes();
    /**
     * 
     */
    std::string find_const(int32_t id);
    /**
     * 
     */
    std::string find_name(int32_t id);
    /**
     * 
     */
    std::string find_varname(int32_t id);
    /**
     * 
     */
    int32_t find_int(int32_t id);
    /**
     * 
     */
    double find_double(int32_t id);
    /**
     * 
     */
    CodeObject* find_code(int32_t id);
    /**
     * 
     */
    int32_t add_var(std::string& var);
    /**
     * 
     */
    int32_t set_var(std::vector<int32_t>& var);
    /**
     * 
     */
    std::vector<int32_t> get_vars();
    /**
     * 
     */
    int32_t get_var_size();
    /**
     * 
     */
    int32_t reset_iter();
protected:
    //这些表为特定字节码所有，执行的时候要将这些表传递出去，共执行类所用
    ConstStringEntry consts;    //字符串常量
    NameEntry names;     //变量名
    NameEntry varnames;  //参数名

    std::vector<int32_t> vars;  //每个位置对应的参数ID
    IntEntry intergers; //整数表
    DoubleEntry doubles;  //浮点数表
    CodeObjectEntry codes;   //存函数或类的字节码对象

    Basicblock** block;  //字节码块
    int32_t nblocks;    //块大小
private:
    int32_t iter_block;
    int32_t iter_instr;

//#ifdef EF_DEBUG
    inline std::string compare_op(int32_t arg)
    {
        switch (arg)
        {
        case 0:         return "<";
        case 1:         return "<=";
        case 2:         return "==";
        case 3:         return "!=";
        case 4:         return ">";
        case 5:         return ">=";
        case 6:         return "in";
        case 7:         return "not in";
        case 8:         return "is";
        case 9:         return "is not";
        case 10:        return "exe match";
        case 11:        return "bad";
        default:        return "error";
        }
        return "error";
    }
    /**
     * 根据操作符查找其对应的名称
     */
    inline std::string op_name(Op opcode)
    {
        //这么多还不如写到map里面去得了
        switch (opcode)
        {
        case STOP_CODE:                 return "STOP_CODE";
        case POP_TOP:                   return "POP_TOP";
        case ROT_TWO:                   return "ROT_TWO";
        case ROT_THREE:                 return "ROT_THREE";
        case DUP_TOP:                   return "DUP_TOP";
        case DUP_TOP_TWO:               return "DUP_TOP_TWO";
        case NOP:                       return "NOP";
        case UNARY_POSITIVE:            return "UNARY_POSITIVE";
        case UNARY_NEGATIVE:            return "UNARY_NEGATIVE";
        case UNARY_NOT:                 return "UNARY_NOT";
        case UNARY_INVERT:              return "UNARY_INVERT";
        case BINARY_POWER:              return "BINARY_POWER";
        case BINARY_MULTIPLY:           return "BINARY_MULTIPLY";
        case BINARY_MODULO:             return "BINARY_MODULO";
        case BINARY_ADD:                return "BINARY_ADD";
        case BINARY_SUBTRACT:           return "BINARY_SUBTRACT";
        case BINARY_SUBSCR:             return "BINARY_SUBSCR";
        case BINARY_FLOOR_DIVIDE:       return "BINARY_FLOOR_DIVIDE";
        case BINARY_TRUE_DIVIDE:        return "BINARY_TRUE_DIVIDE";
        case INPLACE_FLOOR_DIVIDE:      return "INPLACE_FLOOR_DIVIDE";
        case INPLACE_TRUE_DIVIDE:       return "INPLACE_TRUE_DIVIDE";
        case STORE_MAP:                 return "STORE_MAP";
        case INPLACE_ADD:               return "INPLACE_ADD";
        case INPLACE_SUBTRACT:          return "INPLACE_SUBTRACT";
        case INPLACE_MULTIPLY:          return "INPLACE_MULTIPLY";
        case INPLACE_MODULO:            return "INPLACE_MODULO";
        case STORE_SUBSCR:              return "STORE_SUBSCR";
        case LOAD_INT:                  return "LOAD_INT";
        case BINARY_LSHIFT:             return "BINARY_LSHIFT";
        case BINARY_RSHIFT:             return "BINARY_RSHIFT";
        case BINARY_AND:                return "BINARY_AND";
        case BINARY_XOR:                return "BINARY_XOR";
        case BINARY_OR:                 return "BINARY_OR";
        case INPLACE_POWER:             return "INPLACE_POWER";
        case GET_ITER:                  return "GET_ITER";
        case STORE_LOCALS:              return "STORE_LOCALS";
        case PRINT_EXPR:                return "PRINT_EXPR";
        case LOAD_BUILD_CLASS:          return "LOAD_BUILD_CLASS";
        case INPLACE_LSHIFT:            return "INPLACE_LSHIFT";
        case INPLACE_RSHIFT:            return "INPLACE_RSHIFT";
        case INPLACE_AND:               return "INPLACE_AND";
        case INPLACE_XOR:               return "INPLACE_XOR";
        case INPLACE_OR:                return "INPLACE_OR";
        case BREAK_LOOP:                return "BREAK_LOOP";
        case WITH_CLEANUP:              return "WITH_CLEANUP";
        case RETURN_VALUE:              return "RETURN_VALUE";
        case IMPORT_STAR:               return "IMPORT_STAR";
        case YIELD_VALUE:               return "YIELD_VALUE";
        case POP_BLOCK:                 return "POP_BLOCK";
        case END_FINALLY:               return "END_FINALLY";
        case POP_EXCEPT:                return "POP_EXCEPT";
        case HAVE_ARGUMENT:             return "HAVE_ARGUMENT";
        case STORE_NAME:                return "STORE_NAME";
        case DELETE_NAME:               return "DELETE_NAME";
        case UNPACK_SEQUENCE:           return "UNPACK_SEQUENCE";
        case FOR_ITER:                  return "FOR_ITER";
        case UNPACK_EX:                 return "UNPACK_EX";
        case STORE_ATTR:                return "STORE_ATTR";
        case STORE_GLOBAL:              return "STORE_GLOBAL";
        case LOAD_CONST:                return "LOAD_CONST";
        case  LOAD_NAME:                return "LOAD_NAME";
        case  BUILD_TUPLE:              return "BUILD_TUPLE";
        case BUILD_LIST:                return "BUILD_LIST";
        case BUILD_SET:                 return "BUILD_SET";
        case BUILD_MAP:                 return "BUILD_MAP";
        case LOAD_ATTR:                 return "LOAD_ATTR";
        case COMPARE_OP:                return "COMPARE_OP";
        case IMPORT_NAME:               return "IMPORT_NAME";
        case IMPORT_FROM:               return "IMPORT_FROM";
        case JUMP_FORWARD:              return "JUMP_FORWARD";
        case JUMP_IF_FALSE_OR_POP:      return "JUMP_IF_FALSE_OR_POP";
        case JUMP_IF_TRUE_OR_POP:       return "JUMP_IF_TRUE_OR_POP";
        case JUMP_ABSOLUTE:             return "JUMP_ABSOLUTE";
        case POP_JUMP_IF_FALSE:         return "POP_JUMP_IF_FALSE";
        case POP_JUMP_IF_TRUE:          return "POP_JUMP_IF_TRUE";
        case LOAD_GLOBAL:               return "LOAD_GLOBAL";
        case CONTINUE_LOOP:             return "CONTINUE_LOOP";
        case SETUP_LOOP:                return "SETUP_LOOP";
        case SETUP_EXCEPT:              return "SETUP_EXCEPT";
        case SETUP_FINALLY:             return "SETUP_FINALLY";
        case LOAD_FAST:                 return "LOAD_FAST";
        case STORE_FAST:                return "STORE_FAST";
        case RAISE_VARARGS:             return "RAISE_VARARGS";
        case CALL_FUNCTION:             return "CALL_FUNCTION";
        case MAKE_FUNCTION:             return "MAKE_FUNCTION";
        case BUILD_SLICE:               return "BUILD_SLICE";
        case MAKE_CLOSURE:              return "MAKE_CLOSURE";
        case LOAD_CLOSURE:              return "LOAD_CLOSURE";
        case LOAD_DEREF:                return "LOAD_DEREF";
        case STORE_DEREF:               return "STORE_DEREF";
        case CALL_FUNCTION_VAR:         return "CALL_FUNCTION_VAR";
        case CALL_FUNCTION_KW:          return "CALL_FUNCTION_KW";
        case CALL_FUNCTION_VAR_KW:      return "CALL_FUNCTION_VAR_KW";
        case SETUP_WITH:                return "SETUP_WITH";
        case EXTENDED_ARG:              return "EXTENDED_ARG";
        case LIST_APPEND:               return "LIST_APPEND";
        case SET_ADD:                   return "SET_ADD";
        case MAP_ADD:                   return "MAP_ADD";
        case LOAD_FLOAT:                return "LOAD_FLOAT";
        case LOAD_OBJECT:               return "LOAD_OBJECT";
        }
        return "ERROR When find opcode name";
    }
//#endif //EF_DEBU
};
/**
 *
 **/
class TypeObject
    :public AbstractObject
{
public:
    /**
     * 
     */
    TypeObject();
    /**
     * 
     */
    ~TypeObject();
protected:
    
private:
};
/**
 * 
 **/
class MethodObject
    :public AbstractObject
{
public:
    /**
     * 
     */
    MethodObject();
    /**
     * 
     */
    ~MethodObject();
protected:
    
private:
};
/**
 * 
 **/
class IterObject
    :public AbstractObject
{
public:
    /**
     * 
     */
    IterObject();
    /**
     * 
     */
    ~IterObject();
protected:
    
private:
};
/**
 * 
 **/
class ClassObject
    :public AbstractObject
{
public:
    /**
     * 
     */
    ClassObject();
    /**
     * 
     */
    ~ClassObject();
protected:
    
private:
};
/**
 * 
 **/
class BytesObject
    :public GeneralObject
{
public:
    /**
     * 
     */
    BytesObject();
    /**
     * 
     */
    ~BytesObject();
protected:
    
private:
};
/**
 * 映射类型，对遍历整个表，需要迭代器，而这个太需要时间了
 **/
class MapObject
    :public GeneralObject
{
public:
    typedef std::map<Object*,Object*> MapEntry;
    /**
    *  默认构造函数，构造一个空映射
    **/
    MapObject();
    /**
    * 
    **/
    ~MapObject();
    /**
    *  插入一个新元素
    *  @key
    *  @value
    *  nothing
    **/
    void insert(Object* key,Object* value);
    /**
    * 删除一个元素
    * @key
    * nothing
    **/
    void erase(Object* key);
    /**
    * 清楚整个映射表
    **/
    void clear();
    /**
    * 返回下一value
    **/
    Object* next();
    /**
    * 返回表的大小
    **/
    int32_t get_size();
    /**
    * 找到一个元素
    * @key
    **/
    Object* find(Object* key);
    /**
    * 合并两张表
    * @other
    **/
    MapObject* merge(MapObject* other);
protected:
    static const int32_t MIN_MAP_SIZE = 8;
    //struct MapEntry
    //{
        //Object* key;    //根据key排序，排列value
        //Object* value;
    //};
private:
    MapEntry* map_table;
    //本来要自己写，现在直接用STL

    int32_t size;           //真实大小
    int32_t reverse_size;   //保留大小

    /**
    * 将begin到end区间的所有元素拷贝至dst空间
    * @ begin
    * @ end
    * @ dst 目标地址
    * return: 拷贝的大小，非绝对地址空间
    **/
    int32_t copy_table(MapEntry* begin,MapEntry* end,MapEntry* dst );
};
/**
 * 
 **/
class TupleObject
    :public GeneralObject
{
public:
    /**
     * 
     */
    TupleObject();
    /**
     * 
     */
    ~TupleObject();
protected:
    
private:
};
/**
 * 
 **/
class ListObject
    :public GeneralObject
{
public:
    /**
     * 
     */
    ListObject();
    /**
     * 
     */
    ~ListObject();
protected:
    
private:
};
/**
 * 
 **/
class SetObject
    :public GeneralObject
{
public:
    /**
     * 
     */
    SetObject();
    /**
     * 
     */
    ~SetObject();
protected:
    
private:
};
/**
 *  将数字类型单独隔离
 **/
class NumObject
    :public GeneralObject
{
public:
    /**
     * 
     */
    NumObject();
    /**
     * 从字符串中构造整型或实型对象
     */
    NumObject(std::string& str);
    /**
     * 
     */
    ~NumObject();
    /**
     * 
     */
    bool operator == (const NumObject& right) const;
    bool operator < (const NumObject& right) const;
    bool operator != (const NumObject& right) const;
    bool operator <= (const NumObject& right) const;
    bool operator > (const NumObject& right) const;
    bool operator >= (const NumObject& right) const;
    operator bool() const;
protected:
    
private:
};
/**
 * int型的设计是最基本的，其设计相当复杂，我们应考虑到从各个数据类型到int类型的转换
 * 可以考虑是从构造函数转换，也可以是工厂函数
 **/
class LongObject
    :public NumObject
{
public:
    /**
    *
    **/
    LongObject(int32_t t_value);
    /**
     * 
     */
    LongObject(std::string& str);
    /**
     * 
     */
    ~LongObject();
    /**
     * 
     */
    virtual void print(std::ostream& cout);
    /**
    *   
    **/
    virtual int32_t get_int() const;
    /**
     * 
     */
    bool operator == (const LongObject& right) const;
    bool operator < (const LongObject& right) const;
    bool operator != (const LongObject& right) const;
    bool operator <= (const LongObject& right) const;
    bool operator > (const LongObject& right) const;
    bool operator >= (const LongObject& right) const;
    operator bool() const;

    LongObject* operator + (const LongObject& right) const;
    LongObject* operator - (const LongObject& right) const;
    LongObject* operator * (const LongObject& right) const;
    LongObject* operator / (const LongObject& right) const;
    LongObject* operator % (const LongObject& right) const;

    LongObject* operator += (const LongObject& right) const;
    LongObject* operator -= (const LongObject& right) const;
    LongObject* operator *= (const LongObject& right) const;
    LongObject* operator /= (const LongObject& right) const;

    LongObject* operator | (const LongObject& right) const;
    LongObject* operator ^ (const LongObject& right) const;

    operator FloatObject* ();
protected:
    int32_t value;
private:
};
/**
 * 
 **/
class FloatObject
    :public NumObject
{
public:
    /**
     * 
     */
    FloatObject(double t_value);
    /**
     * 
     */
    FloatObject(std::string& str);
    /**
     * 
     */
    ~FloatObject();
    /**
     * 
     */
    virtual void print(std::ostream& cout);
    /**
    *   
    **/
    virtual double get_double() const;
    /**
     * 
     */
    bool operator == (const FloatObject& right) const;
    bool operator < (const FloatObject& right) const;
    bool operator != (const FloatObject& right) const;
    bool operator <= (const FloatObject& right) const;
    bool operator > (const FloatObject& right) const;
    bool operator >= (const FloatObject& right) const;

    operator bool() const;

    FloatObject* operator + (const FloatObject& right) const;
    FloatObject* operator - (const FloatObject& right) const;
    FloatObject* operator * (const FloatObject& right) const;
    FloatObject* operator / (const FloatObject& right) const;
    FloatObject* operator % (const FloatObject& right) const;

    FloatObject* operator += (const FloatObject& right) const;
    FloatObject* operator -= (const FloatObject& right) const;
    FloatObject* operator *= (const FloatObject& right) const;
    FloatObject* operator /= (const FloatObject& right) const;

    FloatObject* operator | (const FloatObject& right) const;
    FloatObject* operator ^ (const FloatObject& right) const;

    operator LongObject* ();
protected:
    double value;
private:
};
/**
 * 
 **/
class StringObject
    :public GeneralObject
{
public:
    /**
     * 
     */
    StringObject(std::string t_value);
    /**
     * 
     */
    ~StringObject();
    /**
     * 
     */
    inline std::string get_value() const
    {
        return value;
    }
    virtual void print(std::ostream& cout);
    /**
     * 
     */
    bool operator == (const StringObject& right) const;
    bool operator < (const StringObject& right) const;
    bool operator != (const StringObject& right) const;
    bool operator <= (const StringObject& right) const;
    bool operator > (const StringObject& right) const;
    bool operator >= (const StringObject& right) const;
    operator bool() const;

    StringObject* operator + (const StringObject& right) const;
    StringObject* operator - (const StringObject& right) const;
    StringObject* operator * (const LongObject& right) const;
    StringObject* operator / (const StringObject& right) const;
    StringObject* operator % (const StringObject& right) const;

    StringObject* operator += (const StringObject& right) const;
    StringObject* operator -= (const StringObject& right) const;
    StringObject* operator *= (const StringObject& right) const;
    StringObject* operator /= (const StringObject& right) const;

    StringObject* operator | (const StringObject& right) const;
    StringObject* operator ^ (const StringObject& right) const;
protected:
    std::string value;
private:
};
/**
 * 
 **/
class FunObject
    :public AbstractObject
{
public:
    /**
     * 
     */
    FunObject();
    /**
     * 
     */
    FunObject(CodeObject* ob);
    /**
     * 
     */
    ~FunObject();
    /**
     * 如何支持多个参数,考虑可变参数
     */
    virtual int32_t invoke(std::vector<ObjectObject*> arg);

    bool operator == (const FunObject& right) const;
    bool operator < (const FunObject& right) const;
    bool operator != (const FunObject& right) const;
    bool operator <= (const FunObject& right) const;
    bool operator > (const FunObject& right) const;
    bool operator >= (const FunObject& right) const;

    operator bool() const;

    FunObject* operator + (const FunObject& right) const;
    FunObject* operator - (const FunObject& right) const;
    FunObject* operator * (const FunObject& right) const;
    FunObject* operator / (const FunObject& right) const;
    FunObject* operator % (const FunObject& right) const;

    FunObject* operator += (const FunObject& right) const;
    FunObject* operator -= (const FunObject& right) const;
    FunObject* operator *= (const FunObject& right) const;
    FunObject* operator /= (const FunObject& right) const;

    FunObject* operator | (const FunObject& right) const;
    FunObject* operator ^ (const FunObject& right) const;
protected:
    CodeObject* op_code;
private:
};
/**
 * 
 */
class CoutObject
    :public FunObject
{
public:
	/**
     *
     */
    CoutObject();
    /**
     *
     */
    ~CoutObject();
    /**
     * 
     */
    virtual int32_t invoke(std::vector<ObjectObject*> arg);

    bool operator == (const FunObject& right) const;
    bool operator < (const FunObject& right) const;
    bool operator != (const FunObject& right) const;
    bool operator <= (const FunObject& right) const;
    bool operator > (const FunObject& right) const;
    bool operator >= (const FunObject& right) const;
    operator bool() const;
protected:
    
private:
};

/**
 * 
 **/
class BoolObject
    :public GeneralObject
{
public:
    /**
     * 
     */
    BoolObject();
    /**
     * 
     */
    ~BoolObject();
protected:
    
private:
};

EF_NAMESPACE_END

#endif // _OBJECT_H_2011_11_13_lisency


