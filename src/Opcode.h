/*-------------------------------------------------------------------
* Purpose:
*         
* Time:
*         2012年2月25日 23:39:18
* Author:
*         张彦升
--------------------------------------------------------------------*/
#ifndef _OPCODE_H_2012_2_25_lisency
#define _OPCODE_H_2012_2_25_lisency

#include "Util.h"

#include <map>
#include <stack>
#include <stdint.h>

EF_NAMESPACE_BEGIN

class Object;
class CodeObject;
class ObjectObject;

typedef std::map<std::string,uint32_t> StrTable;
typedef std::map<int,int32_t> IntTable;
typedef std::map<double,int32_t> FloatTable;
//对于函数和类使用object来存储，这里是name的id到字节码之间的映射，所以
//查找的时候要根据name的id来查找
typedef std::stack<ObjectObject*> ExeStack;
//运行时刻栈内容
typedef std::map<int32_t,std::string> NameEntry;
//上面这一结构完全是为了打印，因为运行时刻不再关心名字的大问题，到字节码
//生成之后，所有的name都有相应的ID，而字节码中的执行参数就是该ID，所以
//我们不用去关心它
typedef std::map<int32_t,ObjectObject*> ValueEntry;
//运行时刻结果，存所有指令执行后的结果，结果的类型保存在ObjectObject中
typedef std::map<int32_t,std::string> ConstStringEntry;
//存所有的字符串常量
typedef std::map<int32_t,int32_t> IntEntry;
//存所有的的整型
typedef std::map<int32_t,double> DoubleEntry;
//存所有的实型
typedef std::map<int32_t,CodeObject*> CodeObjectEntry;
//存由名字ID到字节码对象的映射，当触发函数调用时，在这里找

enum Op
{
    STOP_CODE                   = 0,
    POP_TOP                     = 1,
    ROT_TWO                     = 2,
    ROT_THREE                   = 3,
    DUP_TOP                     = 4,
    DUP_TOP_TWO                 = 5,
    NOP                         = 9,
    UNARY_POSITIVE              = 10,
    UNARY_NEGATIVE              = 11,
    UNARY_NOT                   = 12,
    UNARY_INVERT                = 15,
    BINARY_POWER                = 19,
    BINARY_MULTIPLY             = 20,
    STORE_NAME                  = 21,    /* Index in name list */
    BINARY_MODULO               = 22,
    BINARY_ADD                  = 23,
    BINARY_SUBTRACT             = 24,
    BINARY_SUBSCR               = 25,
    BINARY_FLOOR_DIVIDE         = 26,
    BINARY_TRUE_DIVIDE          = 27,
    INPLACE_FLOOR_DIVIDE        = 28,
    INPLACE_TRUE_DIVIDE         = 29,
    STORE_MAP                   = 54,
    INPLACE_ADD                 = 55,
    INPLACE_SUBTRACT            = 56,
    INPLACE_MULTIPLY            = 57,
    INPLACE_MODULO              = 59,
    STORE_SUBSCR                = 60,
    LOAD_INT                    = 61,
    BINARY_LSHIFT               = 62,
    BINARY_RSHIFT               = 63,
    BINARY_AND                  = 64,
    BINARY_XOR                  = 65,
    BINARY_OR                   = 66,
    INPLACE_POWER               = 67,
    GET_ITER                    = 68,
    STORE_LOCALS                = 69,
    PRINT_EXPR                  = 70,
    LOAD_BUILD_CLASS            = 71,
    INPLACE_LSHIFT              = 75,
    INPLACE_RSHIFT              = 76,
    INPLACE_AND                 = 77,
    INPLACE_XOR                 = 78,
    INPLACE_OR                  = 79,
    BREAK_LOOP                  = 80,
    WITH_CLEANUP                = 81,
    RETURN_VALUE                = 83,
    IMPORT_STAR                 = 84,
    YIELD_VALUE                 = 86,
    POP_BLOCK                   = 87,
    END_FINALLY                 = 88,
    POP_EXCEPT                  = 89,
    HAVE_ARGUMENT               = 90,    /* Opcodes from here have an argument: */

    DELETE_NAME                 = 91,/* "" */
    UNPACK_SEQUENCE             = 92,    /* Number of sequence items */
    FOR_ITER                    = 93,
    UNPACK_EX                   = 94,      /* Num items before variable part +*;*/
    STORE_ATTR                  = 95,    /* Index in name list */

    STORE_GLOBAL                = 97,    /* "" */
    LOAD_CONST                  = 100,    /* Index in const list */
    LOAD_NAME                   = 101,    /* Index in name list */
    BUILD_TUPLE                 = 102,    /* Number of tuple items */
    BUILD_LIST                  = 103,    /* Number of list items */
    BUILD_SET                   = 104,     /* Number of set items */
    BUILD_MAP                   = 105,    /* Always zero for now */
    LOAD_ATTR                   = 106,    /* Index in name list */
    COMPARE_OP                  = 107,    /* Comparison operator */
    IMPORT_NAME                 = 108,    /* Index in name list */
    IMPORT_FROM                 = 109,    /* Index in name list */
    JUMP_FORWARD                = 110,    /* Number of bytes to skip */
    JUMP_IF_FALSE_OR_POP        = 111,    /* Target byte offset from beginning of code */
    JUMP_IF_TRUE_OR_POP         = 112,    /* "" */
    JUMP_ABSOLUTE               = 113,    /* "" */
    POP_JUMP_IF_FALSE           = 114,    /* "" */
    POP_JUMP_IF_TRUE            = 115,    /* "" */
    LOAD_GLOBAL                 = 116,    /* Index in name list */
    CONTINUE_LOOP               = 119,    /* Start of loop (absolute) */
    SETUP_LOOP                  = 120,    /* Target address (relative) */
    SETUP_EXCEPT                = 121,    /* "" */
    SETUP_FINALLY               = 122,    /* "" */
    LOAD_FAST                   = 124,    /* Local variable number */
    STORE_FAST                  = 125,    /* Local variable number */
    RAISE_VARARGS               = 130,    /* Number of raise arguments (1, 2 or 3) */

    CALL_FUNCTION               = 131,    /* #args + (#kwargs<<8) */
    MAKE_FUNCTION               = 132,    /* #defaults + #kwdefaults<<8 + #annotations<<16 */
    BUILD_SLICE                 = 133,    /* Number of items */
    MAKE_CLOSURE                = 134,    /* same as MAKE_FUNCTION */
    LOAD_CLOSURE                = 135,     /* Load free variable from closure */
    LOAD_DEREF                  = 136,     /* Load and dereference from closure cell */ 
    STORE_DEREF                 = 137,     /* Store into cell */ 

    CALL_FUNCTION_VAR           = 140,    /* #args + (#kwargs<<8) */
    CALL_FUNCTION_KW            = 141,    /* #args + (#kwargs<<8) */
    CALL_FUNCTION_VAR_KW        = 142,    /* #args + (#kwargs<<8) */
    SETUP_WITH                  = 143,

    EXTENDED_ARG                = 144,
    LIST_APPEND                 = 145,
    SET_ADD                     = 146,
    MAP_ADD                     = 147,

    LOAD_FLOAT                  = 149,
    LOAD_OBJECT                 = 150,  //装载字节码对象
};
enum cmp_op {
    Cmp_LT            = 0,
    Cmp_LE            = 1,
    Cmp_EQ            = 2,
    Cmp_NE            = 3,
    Cmp_GT            = 4,
    Cmp_GE            = 5,
    Cmp_IN            = 6,  //保留
    Cmp_NOT_IN        = 7,  //保留
    Cmp_IS            = 8,  //保留
    Cmp_IS_NOT        = 9,
    Cmp_EXC_MATCH     = 10, //保留
    Cmp_BAD           = 11,
};
struct Basicblock;

struct Instruction 
{
    unsigned i_jabs : 1;
    unsigned i_jrel : 1;
    unsigned i_hasarg : 1;
    Op i_opcode;          //操作符
    int i_oparg;
    Basicblock *i_target; /* target block (if jump instruction) */
    int i_lineno;
};

struct Basicblock
{
    /* Each basicblock in a compilation unit is linked via b_list in the
       reverse order that the block are allocated.  b_list points to the next
       block, not to be confused with b_next, which is next by control flow. */
    Basicblock* b_list;
    /* number of instructions used */
    int b_iused;
    /* length of instruction array (b_instr) */
    int b_ialloc;
    /* pointer to an array of instructions, initially NULL */
    Instruction* b_instr;
    /* If b_next is non-NULL, it is a pointer to the next
       block reached by normal control flow. */
    Basicblock* b_next;
    /* b_seen is used to perform a DFS of basicblocks. */
    unsigned b_seen : 1;
    /* b_return is true if a RETURN_VALUE opcode is inserted. */
    unsigned b_return : 1;
    /* depth of stack upon entry of block, computed by stackdepth() */
    int b_startdepth;
    /* instruction offset for block, computed by assemble_jump_offsets() */
    int b_offset;
};

enum Expr_context_ty 
{
    Empty           = 0,
    Load            = 1, 
    Store           = 2,
    Del             = 3,
    AugLoad         = 4,
    AugStore        = 5,
    Param           = 6
};

EF_NAMESPACE_END

#endif // _OPCODE_H_2012_2_25_lisency

