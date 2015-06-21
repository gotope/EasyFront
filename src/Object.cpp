/*-------------------------------------------------------------------
 * Purpose:
 *         Object.h
 * Time:
 *         2012年2月9日 20:50:41
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "Object.h"
#include "Executor.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

EF_NAMESPACE_BEGIN

/**
 * 
 */
Object::Object()
{
    return;
}
/**
 * 
 */
Object::~Object()
{
    return;
}
/**
 * 
 */
void Object::print(std::ostream& cout)
{
    return;
}
/**
 * 
 */
int32_t Object::hash()
{
    return 0;
}
bool Object::operator==( const Object& right ) const
{
    return true;
}
bool Object::operator<( const Object& right ) const
{
    return true;
}
bool Object::operator!=( const Object& right ) const
{
    return !(*this == right);
}
bool Object::operator<=( const Object& right ) const
{
    return !(right < (*this));
}

bool Object::operator>( const Object& right ) const
{
    return right < *this;
}

bool Object::operator>=( const Object& right ) const
{
    return !(*this < right);
}

Object::operator bool() const
{
    return false;
}

Object* Object::operator+( const Object& right ) const
{
    return NULL;
}
Object* Object::operator-( const Object& right ) const
{
    return NULL;
}
Object* Object::operator*( const Object& right ) const
{
    return NULL;
}

Object* Object::operator/( const Object& right ) const
{
    return NULL;
}

Object* Object::operator+=( const Object& right ) const
{
    return NULL;
}

Object* Object::operator-=( const Object& right ) const
{
    return NULL;
}

Object* Object::operator*=( const Object& right ) const
{
    return NULL;
}

Object* Object::operator/=( const Object& right ) const
{
    return NULL;
}

Object* Object::operator|( const Object& right ) const
{
    return NULL;
}
Object* Object::operator^( const Object& right ) const
{
    return NULL;
}

/**
 * 
 */
ObjectObject::ObjectObject( Object* t_ob,ObjectType ty )
:ob(t_ob),
type(ty)
{
    return;
}

ObjectObject::~ObjectObject()
{

}


bool ObjectObject::operator==( const ObjectObject& right ) const
{
    switch (type)
    {
    case LONG_TYPE:
        return (*(LongObject*)ob) == *(LongObject*)right.get_ob();
    case DOUBLE_TYPE:
        return (*(FloatObject*)ob) == *(FloatObject*)right.get_ob();
    case STRING_TYPE:
        return (*(StringObject*)ob) == *(StringObject*)right.get_ob();
    case CODE_TYPE:
        return (*(CodeObject*)ob) == *(CodeObject*)right.get_ob();
    case FUN_TYPE:
        return (*(FunObject*)ob) == *(FunObject*)right.get_ob();
    default:
        return false;
    }
}

bool ObjectObject::operator<( const ObjectObject& right ) const
{
    switch (type)
    {
    case LONG_TYPE:
        return (*(LongObject*)ob) < *(LongObject*)right.get_ob();
    case DOUBLE_TYPE:
        return (*(FloatObject*)ob) < *(FloatObject*)right.get_ob();
    case STRING_TYPE:
        return (*(StringObject*)ob) < *(StringObject*)right.get_ob();
    case CODE_TYPE:
        return (*(CodeObject*)ob) < *(CodeObject*)right.get_ob();
    case FUN_TYPE:
        return (*(FunObject*)ob) < *(FunObject*)right.get_ob();
    default:
        return false;
    }
}

bool ObjectObject::operator!=( const ObjectObject& right ) const
{
    return !(*this == right);
}

bool ObjectObject::operator<=( const ObjectObject& right ) const
{
    return !(right < (*this));
}

bool ObjectObject::operator>( const ObjectObject& right ) const
{
    return right < *this;
}

bool ObjectObject::operator>=( const ObjectObject& right ) const
{
    return !(*this < right);
}
ObjectObject::operator bool() const
{
    switch (type)
    {
    case LONG_TYPE:
        return (*(LongObject*)ob).operator bool();
    case DOUBLE_TYPE:
        return (*(FloatObject*)ob).operator bool();
    case STRING_TYPE:
        return (*(StringObject*)ob).operator bool();
    case CODE_TYPE:
        return (*(CodeObject*)ob).operator bool();
    case FUN_TYPE:
        return (*(FunObject*)ob).operator bool();
    default:
        return false;
    }
}

ObjectObject* ObjectObject::operator+( const ObjectObject& right ) const
{
    if (type == LONG_TYPE)
    {
        LongObject* result = (*(LongObject*)ob) + *(LongObject*)right.get_ob();
        return new ObjectObject(result,LONG_TYPE);
    }
    else if (type == DOUBLE_TYPE)
    {
        FloatObject* result = (*(FloatObject*)ob) + *(FloatObject*)right.get_ob();
        return new ObjectObject(result,DOUBLE_TYPE);
    }
    else if (type == STRING_TYPE)
    {
        StringObject* result = (*(StringObject*)ob) + *(StringObject*)right.get_ob();
        return new ObjectObject(result,STRING_TYPE);
    }
    else if (type == CODE_TYPE)
    {
        CodeObject* result = (*(CodeObject*)ob) + *(CodeObject*)right.get_ob();
        return new ObjectObject(result,CODE_TYPE);
    }
    else if (type == FUN_TYPE)
    {
        FunObject* result = (*(FunObject*)ob) + *(FunObject*)right.get_ob();
        return new ObjectObject(result,FUN_TYPE);
    }
    return NULL;
}

ObjectObject* ObjectObject::operator-( const ObjectObject& right ) const
{
    if (type == LONG_TYPE)
    {
        LongObject* result = (*(LongObject*)ob) - *(LongObject*)right.get_ob();
        return new ObjectObject(result,LONG_TYPE);
    }
    else if (type == DOUBLE_TYPE)
    {
        FloatObject* result = (*(FloatObject*)ob) - *(FloatObject*)right.get_ob();
        return new ObjectObject(result,DOUBLE_TYPE);
    }
    else if (type == STRING_TYPE)
    {
        StringObject* result = (*(StringObject*)ob) - *(StringObject*)right.get_ob();
        return new ObjectObject(result,STRING_TYPE);
    }
    else if (type == CODE_TYPE)
    {
        CodeObject* result = (*(CodeObject*)ob) - *(CodeObject*)right.get_ob();
        return new ObjectObject(result,CODE_TYPE);
    }
    else if (type == FUN_TYPE)
    {
        FunObject* result = (*(FunObject*)ob) - *(FunObject*)right.get_ob();
        return new ObjectObject(result,FUN_TYPE);
    }
    return NULL;
}

ObjectObject* ObjectObject::operator*( const ObjectObject& right ) const
{
    if (type == LONG_TYPE)
    {
        LongObject* result = (*(LongObject*)ob) * *(LongObject*)right.get_ob();
        return new ObjectObject(result,LONG_TYPE);
    }
    else if (type == DOUBLE_TYPE)
    {
        FloatObject* result = (*(FloatObject*)ob) * *(FloatObject*)right.get_ob();
        return new ObjectObject(result,DOUBLE_TYPE);
    }
    else if (type == STRING_TYPE)
    {
        StringObject* result = (*(StringObject*)ob) * *(LongObject*)right.get_ob();
        return new ObjectObject(result,STRING_TYPE);
    }
    else if (type == CODE_TYPE)
    {
        CodeObject* result = (*(CodeObject*)ob) * *(CodeObject*)right.get_ob();
        return new ObjectObject(result,CODE_TYPE);
    }
    else if (type == FUN_TYPE)
    {
        FunObject* result = (*(FunObject*)ob) * *(FunObject*)right.get_ob();
        return new ObjectObject(result,FUN_TYPE);
    }
    return NULL;
}

ObjectObject* ObjectObject::operator/( const ObjectObject& right ) const
{
    if (type == LONG_TYPE)
    {
        LongObject* result = (*(LongObject*)ob) / *(LongObject*)right.get_ob();
        return new ObjectObject(result,LONG_TYPE);
    }
    else if (type == DOUBLE_TYPE)
    {
        FloatObject* result = (*(FloatObject*)ob) / *(FloatObject*)right.get_ob();
        return new ObjectObject(result,DOUBLE_TYPE);
    }
    else if (type == STRING_TYPE)
    {
        StringObject* result = (*(StringObject*)ob) / *(StringObject*)right.get_ob();
        return new ObjectObject(result,STRING_TYPE);
    }
    else if (type == CODE_TYPE)
    {
        CodeObject* result = (*(CodeObject*)ob) / *(CodeObject*)right.get_ob();
        return new ObjectObject(result,CODE_TYPE);
    }
    else if (type == FUN_TYPE)
    {
        FunObject* result = (*(FunObject*)ob) / *(FunObject*)right.get_ob();
        return new ObjectObject(result,FUN_TYPE);
    }
    return NULL;
}

ObjectObject* ObjectObject::operator%( const ObjectObject& right ) const
{
    if (type == LONG_TYPE)
    {
        LongObject* result = (*(LongObject*)ob) % *(LongObject*)right.get_ob();
        return new ObjectObject(result,LONG_TYPE);
    }
    else if (type == DOUBLE_TYPE)
    {
        FloatObject* result = (*(FloatObject*)ob) % *(FloatObject*)right.get_ob();
        return new ObjectObject(result,DOUBLE_TYPE);
    }
    else if (type == STRING_TYPE)
    {
        StringObject* result = (*(StringObject*)ob) % *(StringObject*)right.get_ob();
        return new ObjectObject(result,STRING_TYPE);
    }
    else if (type == CODE_TYPE)
    {
        CodeObject* result = (*(CodeObject*)ob) % *(CodeObject*)right.get_ob();
        return new ObjectObject(result,CODE_TYPE);
    }
    else if (type == FUN_TYPE)
    {
        FunObject* result = (*(FunObject*)ob) % *(FunObject*)right.get_ob();
        return new ObjectObject(result,FUN_TYPE);
    }
    return NULL;
}

ObjectObject* ObjectObject::operator+=( const ObjectObject& right ) const
{
    return NULL;
}

ObjectObject* ObjectObject::operator-=( const ObjectObject& right ) const
{
    return NULL;
}

ObjectObject* ObjectObject::operator*=( const ObjectObject& right ) const
{
    return NULL;
}

ObjectObject* ObjectObject::operator/=( const ObjectObject& right ) const
{
    return NULL;
}

ObjectObject* ObjectObject::operator|( const ObjectObject& right ) const
{
    if (type == LONG_TYPE)
    {
        LongObject* result = (*(LongObject*)ob) | *(LongObject*)right.get_ob();
        return new ObjectObject(result,LONG_TYPE);
    }
    else if (type == DOUBLE_TYPE)
    {
        FloatObject* result = (*(FloatObject*)ob) | *(FloatObject*)right.get_ob();
        return new ObjectObject(result,DOUBLE_TYPE);
    }
    else if (type == STRING_TYPE)
    {
        StringObject* result = (*(StringObject*)ob) | *(StringObject*)right.get_ob();
        return new ObjectObject(result,STRING_TYPE);
    }
    else if (type == CODE_TYPE)
    {
        CodeObject* result = (*(CodeObject*)ob) | *(CodeObject*)right.get_ob();
        return new ObjectObject(result,CODE_TYPE);
    }
    else if (type == FUN_TYPE)
    {
        FunObject* result = (*(FunObject*)ob) | *(FunObject*)right.get_ob();
        return new ObjectObject(result,FUN_TYPE);
    }
    return NULL;
}

ObjectObject* ObjectObject::operator^( const ObjectObject& right ) const
{
    return NULL;
}
ObjectObject* ObjectObject::to_longobject()
{
    //内存泄漏
    if (type == DOUBLE_TYPE)
    {
        double val = ((FloatObject*)ob)->get_double();
        ob = new LongObject((int32_t)val);
    }
    return this;
}

ObjectObject* ObjectObject::to_floatobject()
{
    //内存泄漏
    if (type == LONG_TYPE)
    {
        int32_t val = ((LongObject*)ob)->get_int();
        ob = new FloatObject(val * 1.0);
    }
    return this;
}

/**
 * 
 */
GeneralObject::GeneralObject()
{
    return;
}
/**
 * 
 */
GeneralObject::~GeneralObject()
{
    return;
}
/**
 * 
 */
AbstractObject::AbstractObject()
{
    return;
}
/**
 * 
 */
AbstractObject::~AbstractObject()
{
    return;
}
ExceptionObject::ExceptionObject()
{
    return;
}
ExceptionObject::~ExceptionObject()
{
    return;
}
/**
 * 字节码对象
 */
CodeObject::CodeObject()
{
    iter_block = 0;
    iter_instr = 0;

    return;
}
/**
 * 拷贝构造函数
 */
CodeObject::CodeObject( CodeObject& right )
:consts(right.consts),
names(right.names),
varnames(right.varnames),
intergers(right.intergers),
doubles(right.doubles),
codes(right.codes),
block(right.block),
nblocks(right.nblocks)
{
    iter_block = right.nblocks - 1;
    iter_instr = 0;
    return;
}
/**
 * do nothing
 */
CodeObject::~CodeObject()
{
    return;
}
/**
 * 
 */
int32_t CodeObject::hash()
{
    return 0;
}
/**
 * 打印字节码
 */
void CodeObject::print(std::ostream& cout)
{
    cout.unsetf(std::ios_base::hex);
    //遍历所有块,块是反序放的，但是指令并没有反序存放
    for (int32_t i = nblocks - 1;i >= 0;i--)
    {
        Basicblock* b = block[i];

        cout  << std::setw(4) << std::left << nblocks - i - 1;

        int32_t instr_size = block[i]->b_iused;
        //遍历所有指令
        for (int32_t j = 0;j < instr_size;j++)
        {
            Instruction instr = b->b_instr[j];

            Op opcode = instr.i_opcode;
            int i_oparg = instr.i_oparg;
            //int off = instr.i
            if (j != 0)
            {
                cout << std::left << std::setw(4) << "  ";
            }
            cout << std::left << std::setw(4) << j;

            cout  << std::setw(20) << std::left << op_name(opcode);

            switch (opcode)
            {
            case LOAD_NAME:
                cout << i_oparg << " " << "(" 
                    << find_name(i_oparg) << ")" << std::endl;
                break;
            case LOAD_INT:
                cout << i_oparg << " " << "("
                    << find_int(i_oparg) << ")" << std::endl;
                break;
            case LOAD_FLOAT:
                cout << i_oparg << " " << "("
                    << find_double(i_oparg) << ")" << std::endl;
                break;
            case LOAD_CONST:
                cout << i_oparg << " " << "("
                    << find_const(i_oparg) << ")" << std::endl;
                break;
            case STORE_NAME:
                cout << i_oparg << " " << "("
                    << find_name(i_oparg) << ")" << std::endl;
                break;
            case COMPARE_OP:
                cout << compare_op(i_oparg) << std::endl;
                break;
            default:
                cout << i_oparg << std::endl;
            }
        }
        cout << std::endl;
    }
    cout << "--------------------------------------------" << std::endl;
    return;
}


bool CodeObject::operator==( const CodeObject& right ) const
{
    if (block == right.block)
    {
        return true;
    }
    return false;
}

bool CodeObject::operator<( const CodeObject& right ) const
{
    debug_stream << "在CodeObject之间有小于号比较，这是不允许的" << std::endl;
    return false;
}

bool CodeObject::operator!=( const CodeObject& right ) const
{
    return !(*this == right);
}

bool CodeObject::operator<=( const CodeObject& right ) const
{
    return !(right < (*this));
}

bool CodeObject::operator>( const CodeObject& right ) const
{
    return right < *this;
}

bool CodeObject::operator>=( const CodeObject& right ) const
{
    return !(*this < right);
}
CodeObject::operator bool() const
{
    if (block == NULL)
    {
        return false;
    }
    return true;
}

CodeObject* CodeObject::operator+( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator-( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator*( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator/( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator%( const CodeObject& right ) const
{
    return NULL;
}
CodeObject* CodeObject::operator+=( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator-=( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator*=( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator/=( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator|( const CodeObject& right ) const
{
    return NULL;
}

CodeObject* CodeObject::operator^( const CodeObject& right ) const
{
    return NULL;
}

Instruction* CodeObject::next_instr()
{
    //这里注意iter_block的大小，由于对CodeObject有两种构造方式，无参的
    //一种对其设置的是0，必须在set_block_size的时候初始化成最后一位
    if (iter_block < 0)
    {
        return NULL;
    }
    Basicblock* b = block[iter_block];

    if (iter_instr >= b->b_iused)
    {
        iter_block --;
        //指令已经用完
        if (iter_block < 0)
        {
            return NULL;
        }
        b = block[iter_block];
        iter_instr = 0;
    }
    if (iter_instr >= b->b_iused)
    {
        return NULL;
    }
    return &b->b_instr[iter_instr++];
}

Instruction* CodeObject::next_instr( int32_t pos )
{
    pos = nblocks - pos - 1;
    if (pos > nblocks - 1)
    {
        debug_stream << "在读取下一条指令的时候发现，要跳转的指令地址"
            "超出我们已分配的指令范围" << std::endl;
    }
    Basicblock* b = block[pos];
    iter_block = pos;
    iter_instr = 0;
    if (iter_instr >= b->b_iused)
    {
        return NULL;
    }
    return &b->b_instr[iter_instr++];
}

std::string CodeObject::find_const( int32_t id )
{
    ConstStringEntry::iterator iter = consts.find(id);
    if (iter == consts.end())
    {
        D("在codeobject中查找字符串时未找到");
        return "";
    }

    return iter->second;
}

std::string CodeObject::find_name( int32_t id )
{
    NameEntry::iterator iter = names.find(id);
    if (iter == names.end())
    {
        D("在codeobject中查找name时未找到");
        return "";
    }

    return iter->second;
}

std::string CodeObject::find_varname( int32_t id )
{
    NameEntry::iterator iter = varnames.find(id);
    if (iter == varnames.end())
    {
        D("在codeobject中查找varname时未找到");
        return "";
    }

    return iter->second;
}

int32_t CodeObject::find_int( int32_t id )
{
    IntEntry::iterator iter = intergers.find(id);
    if (iter == intergers.end())
    {
        D("在codeobject中查找int时未找到");
        return -1;
    }

    return iter->second;
}

double CodeObject::find_double( int32_t id )
{
    DoubleEntry::iterator iter = doubles.find(id);
    if (iter == doubles.end())
    {
        D("在codeobject中查找int时未找到");
        return -1.0;
    }

    return iter->second;
}

CodeObject* CodeObject::find_code( int32_t id )
{
    CodeObjectEntry::iterator iter = codes.find(id);
    if (iter == codes.end())
    {
        D("在codeobject中查找int时未找到");
        return NULL;
    }

    return iter->second;
}

void CodeObject::set_consts( StrTable& consts_table )
{
    invertMap(consts_table,consts);
}

void CodeObject::set_names( StrTable& names_table )
{
    invertMap(names_table,names);
}

void CodeObject::set_varname( StrTable& varname_table )
{
    invertMap(varname_table,varnames);
}

void CodeObject::set_codes( CodeObjectEntry t_cods )
{
    codes = t_cods;
    return;
}

void CodeObject::set_interger( IntTable& inter_table )
{
    invertMap(inter_table,intergers);
}

void CodeObject::set_floats( FloatTable& float_table )
{
    invertMap(float_table,doubles);
}

void CodeObject::set_blocks( Basicblock** t_blocks )
{
    block = t_blocks;
}

void CodeObject::set_block_size( int32_t block_size )
{
    nblocks = block_size;
    iter_block = nblocks -1;
}

ConstStringEntry CodeObject::get_const()
{
    return consts;
}

NameEntry CodeObject::get_names()
{
    return names;
}

NameEntry CodeObject::get_varnames()
{
    return varnames;
}

IntEntry CodeObject::get_interger()
{
    return intergers;
}

DoubleEntry CodeObject::get_floats()
{
    return doubles;
}

CodeObjectEntry CodeObject::get_codes()
{
    return codes;
}

std::vector<int32_t> CodeObject::get_vars()
{
    return vars;
}

int32_t CodeObject::set_var( std::vector<int32_t>& var )
{
    vars = var;
    return 1;
}

int32_t CodeObject::get_var_size()
{
    return vars.size();
}

int32_t CodeObject::reset_iter()
{
    nblocks = nblocks;
    iter_block = nblocks -1;
    iter_instr = 0;
    return 1;
}

TypeObject::TypeObject()
{
    return;
}
TypeObject::~TypeObject()
{
    return;
}
MethodObject::MethodObject()
{
    return;
}
MethodObject::~MethodObject()
{
    return;
}
IterObject::IterObject()
{
    return;
}
IterObject::~IterObject()
{
    return;
}
ClassObject::ClassObject()
{
    return;
}
ClassObject::~ClassObject()
{
    return;
}
BytesObject::BytesObject()
{
    return;
}
BytesObject::~BytesObject()
{
    return;
}
/**
 * 
 */
MapObject::MapObject()
{
    map_table = new MapEntry[MIN_MAP_SIZE];
    reverse_size = MIN_MAP_SIZE;
    size = 0;
    return;
}
/**
 * 
 **/
MapObject::~MapObject()
{
    return;
}
/**
 * 
 */
void MapObject::insert( Object* key,Object* value )
{
    map_table->insert(std::make_pair(key,value));
    //如果空间太小，则成倍增
    /*
    if (size >= reverse_size)
    {
        reverse_size *= 2;
        MapEntry* t_map_table = new MapEntry[reverse_size];
        copy_table(map_table,
            map_table + sizeof(map_table) / sizeof(MapEntry),t_map_table);
        delete[] map_table;
        map_table = t_map_table;
    }

    //最好用平衡树的
    size++;
    map_table[size].key = key;
    map_table[size].value = value;
    */
    return;
}
/**
 * 
 */
void MapObject::erase( Object* key )
{
    MapEntry::iterator iter = map_table->find(key);
    map_table->erase(iter);
    return;
}
/**
 * 
 */
void MapObject::clear()
{
    map_table->clear();
    return;
}
/**
 * 
 */
Object* MapObject::next()
{
    return NULL;
}
/**
 * 
 */
int32_t MapObject::get_size()
{
    return map_table->size();
}
/**
 * description:    
 **/
Object* MapObject::find( Object* key )
{
    MapEntry::iterator iter = map_table->find(key);
    //return *iter;
    return NULL;
}
/**
 * 
 */
MapObject* MapObject::merge( MapObject* other )
{
    return NULL;
}
/**
 * 
 */
int32_t MapObject::copy_table( MapEntry* begin,MapEntry* end,MapEntry* dst )
{
    /*int pos = 0;
    while (begin != end)
    {
        dst[pos++] = *begin;
        ++begin;
    }*/
    return 0;
}
TupleObject::TupleObject()
{
    return;
}
TupleObject::~TupleObject()
{
    return;
}
ListObject::ListObject()
{
    return;
}
ListObject::~ListObject()
{
    return;
}
SetObject::SetObject()
{
    return;
}
SetObject::~SetObject()
{
    return;
}
NumObject::NumObject()
{
    return;
}
NumObject::NumObject(std::string& str)
{
    return;
}
NumObject::~NumObject()
{
    return;
}

bool NumObject::operator==( const NumObject& right ) const
{
    return false;
}

bool NumObject::operator<( const NumObject& right ) const
{
    return false;
}


bool NumObject::operator!=( const NumObject& right ) const
{
    return !(*this == right);
}

bool NumObject::operator<=( const NumObject& right ) const
{
    return !(right < (*this));
}

bool NumObject::operator>( const NumObject& right ) const
{
    return right < *this;
}

bool NumObject::operator>=( const NumObject& right ) const
{
    return !(*this < right);
}
NumObject::operator bool() const
{
    return false;
}

/**
 * 
 */
LongObject::LongObject(int32_t t_value)
:value(t_value)
{
    return;
}

LongObject::LongObject( std::string& str )
{
    return;
}

/**
 * 
 */
LongObject::~LongObject()
{
    return;
}
/**
 *   
 **/
int32_t LongObject::get_int() const
{
    return value;
}
/**
 * 
 */
bool LongObject::operator==( const LongObject& right ) const
{
    int32_t right_value = right.get_int();

    if (right_value == value)
    {
        return true;
    }
    return false;
}
/**
 * 
 */
bool LongObject::operator<( const LongObject& right ) const
{
    int32_t right_value = right.get_int();

    if (value < right_value)
    {
        return true;
    }
    return false;
}
bool LongObject::operator!=( const LongObject& right ) const
{
    return !(*this == right);
}
bool LongObject::operator<=( const LongObject& right ) const
{
    return !(right < (*this));
}

bool LongObject::operator>( const LongObject& right ) const
{
    return right < *this;
}

bool LongObject::operator>=( const LongObject& right ) const
{
    return !(*this < right);
}
void LongObject::print( std::ostream& cout )
{
    cout << value;
}

LongObject::operator bool() const
{
    if (value == 0)
    {
        return false;
    }
    return true;
}

LongObject* LongObject::operator+( const LongObject& right ) const
{
    int32_t t_value = value + right.get_int();
    return new LongObject(t_value);
}

LongObject* LongObject::operator-( const LongObject& right ) const
{
    int32_t t_value = value - right.get_int();
    return new LongObject(t_value);
}

LongObject* LongObject::operator*( const LongObject& right ) const
{
    int32_t t_value = value * right.get_int();
    return new LongObject(t_value);
}

LongObject* LongObject::operator/( const LongObject& right ) const
{
    int32_t t_value = value / right.get_int();
    return new LongObject(t_value);
}

LongObject* LongObject::operator%( const LongObject& right ) const
{
    int32_t t_value = value % right.get_int();
    return new LongObject(t_value);
}

LongObject* LongObject::operator+=( const LongObject& right ) const
{
    //value += right.get_int();
    return NULL;
}

LongObject* LongObject::operator-=( const LongObject& right ) const
{
    return NULL;
}

LongObject* LongObject::operator*=( const LongObject& right ) const
{
    return NULL;
}

LongObject* LongObject::operator/=( const LongObject& right ) const
{
    return NULL;
}

LongObject::operator FloatObject*()
{
    return new FloatObject(value * 1.0);
}

LongObject* LongObject::operator|( const LongObject& right ) const
{
    int32_t t_value = value | right.get_int();

    return new LongObject(t_value);
}

LongObject* LongObject::operator^( const LongObject& right ) const
{
    int32_t t_value = value ^ right.get_int();

    return new LongObject(t_value);
}

/**
 * 
 */
FloatObject::FloatObject(double t_value)
:value(t_value)
{
    return;
}
/**
 * 
 */
FloatObject::~FloatObject()
{
    return;
}
/**
 *   
 **/
double FloatObject::get_double() const
{
    return value;
}
bool FloatObject::operator==( const FloatObject& right ) const
{
    double right_value = right.get_double();
    if (value == right_value) 
    {
        return true;
    }
    return false;
}
/**
 * bug
 */
bool FloatObject::operator<( const FloatObject& right ) const
{
    double right_value = right.get_double();
    if (value < right_value) 
    {
        return true;
    }
    return false;
}


bool FloatObject::operator!=( const FloatObject& right ) const
{
    return !(*this == right);
}

bool FloatObject::operator<=( const FloatObject& right ) const
{
    return !(right < (*this));
}

bool FloatObject::operator>( const FloatObject& right ) const
{
    return right < *this;
}

bool FloatObject::operator>=( const FloatObject& right ) const
{
    return !(*this < right);
}

FloatObject::operator bool() const
{
    if (value == 0)
    {
        return false;
    }
    return true;
}
void FloatObject::print( std::ostream& cout )
{
    cout << value;
}

FloatObject* FloatObject::operator+( const FloatObject& right ) const
{
    double t_value = value + right.get_double();
    return new FloatObject(t_value);
}

FloatObject* FloatObject::operator-( const FloatObject& right ) const
{
    double t_value = value - right.get_double();
    return new FloatObject(t_value);
}

FloatObject* FloatObject::operator*( const FloatObject& right ) const
{
    double t_value = value * right.get_double();
    return new FloatObject(t_value);
}

FloatObject* FloatObject::operator/( const FloatObject& right ) const
{
    double t_value = value / right.get_double();
    return new FloatObject(t_value);
}

FloatObject* FloatObject::operator%( const FloatObject& right ) const
{
    int32_t value1 = int32_t(value);
    int32_t value2 = int32_t(right.get_double());
    if (value2 == 0)
    {
        value2 = 1;
    }
    int32_t t_value = value1 % value2;

    return new FloatObject(1.0 * t_value);
}

FloatObject* FloatObject::operator+=( const FloatObject& right ) const
{
    return NULL;
}

FloatObject* FloatObject::operator-=( const FloatObject& right ) const
{
    return NULL;
}

FloatObject* FloatObject::operator*=( const FloatObject& right ) const
{
    return NULL;
}

FloatObject* FloatObject::operator/=( const FloatObject& right ) const
{
    return NULL;
}

FloatObject::operator LongObject*()
{
    return new LongObject(int32_t(value));
}

FloatObject* FloatObject::operator|( const FloatObject& right ) const
{
    //double t_value = value | right.get_double();
    //return new FloatObject(t_value);
    return NULL;
}

FloatObject* FloatObject::operator^( const FloatObject& right ) const
{
    //double t_value = value ^ right.get_double();
    //return new FloatObject(t_value);
    return NULL;
}

/**
 * 
 */
StringObject::StringObject(std::string t_value)
:value(t_value)
{
    return;
}
/**
 * 
 */
StringObject::~StringObject()
{
    return;
}

bool StringObject::operator==( const StringObject& right ) const
{
    std::string right_value = right.get_value();
    if (right_value == value)
    {
        return true;
    }
    return false;
}
bool StringObject::operator<( const StringObject& right ) const
{
    std::string right_value = right.get_value();
    if (value < right_value)
    {
        return true;
    }
    return false;
}


bool StringObject::operator!=( const StringObject& right ) const
{
    return !(*this == right);
}

bool StringObject::operator<=( const StringObject& right ) const
{
    return !(right < (*this));
}

bool StringObject::operator>( const StringObject& right ) const
{
    return right < *this;
}

bool StringObject::operator>=( const StringObject& right ) const
{
    return !(*this < right);
}

void StringObject::print( std::ostream& cout )
{
    cout << value;
}

StringObject::operator bool() const
{
    if (value.empty())
    {
        return false;
    }
    return true;
}

StringObject* StringObject::operator+( const StringObject& right ) const
{
    std::string t_value = right.get_value() + value;

    return new StringObject(t_value);
}

StringObject* StringObject::operator-( const StringObject& right ) const
{
    int32_t pos = value.find(right.get_value());
    if (pos == std::string::npos)
    {
        return NULL;
    }
    std::string t_value = value;
    t_value.erase(pos,right.get_value().size());

    return new StringObject(t_value);
}

StringObject* StringObject::operator*( const LongObject& right ) const
{
    std::string t_value = value;
    int32_t count = right.get_int();

    std::string result;
    while (count)
    {
        result += t_value;
        count--;
    }
    return new StringObject(result);
}

StringObject* StringObject::operator/( const StringObject& right ) const
{
    return NULL;
}

StringObject* StringObject::operator%( const StringObject& right ) const
{
    return NULL;
}

StringObject* StringObject::operator+=( const StringObject& right ) const
{
    return NULL;
}

StringObject* StringObject::operator-=( const StringObject& right ) const
{
    return NULL;
}

StringObject* StringObject::operator*=( const StringObject& right ) const
{
    return NULL;
}

StringObject* StringObject::operator/=( const StringObject& right ) const
{
    return NULL;
}

StringObject* StringObject::operator^( const StringObject& right ) const
{
    return NULL;
}

StringObject* StringObject::operator|( const StringObject& right ) const
{
    return NULL;
}

FunObject::FunObject()
{
    return;
}

FunObject::FunObject( CodeObject* ob )
{
    op_code = ob;
    return;
}

FunObject::~FunObject()
{
    return;
}
//class Executor;

int32_t FunObject::invoke(std::vector<ObjectObject*> arg )
{
    std::vector<int32_t> vars = op_code->get_vars();
    if (arg.size() > vars.size())
    {
        debug_stream << "函数的参数过多"
            << std::endl;
        return -1;
    }
    //将所有的参数值存入values中
    Executor* fun_executor = new Executor(op_code);
    ValueEntry* val = fun_executor->get_values();

    std::vector<ObjectObject*>::reverse_iterator iter = arg.rbegin();

    int32_t pos = 0;

    for (;iter != arg.rend();++iter)
    {
        int32_t id = vars[pos++];

        (*val)[id] = (*iter);   //对所有参数赋值
    }
    fun_executor->excute();
    delete fun_executor;
    op_code->reset_iter();
    //函数返回值没有添加
    return 1;
}
bool FunObject::operator==( const FunObject& right ) const
{
    debug_stream << "在两个函数object之间存在了等于比较，这个功能未完成"
        << std::endl;
    return false;
}

bool FunObject::operator<( const FunObject& right ) const
{
    debug_stream << "在两个函数object之间存在了小于比较，这个功能未完成"
        << std::endl;
    return false;
    return false;
}

bool FunObject::operator!=( const FunObject& right ) const
{
    return !(*this == right);
}

bool FunObject::operator<=( const FunObject& right ) const
{
    return !(right < (*this));
}

bool FunObject::operator>( const FunObject& right ) const
{
    return right < *this;
}

bool FunObject::operator>=( const FunObject& right ) const
{
    return !(*this < right);
}

FunObject::operator bool() const
{
    return false;
}

FunObject* FunObject::operator+( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator-( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator*( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator/( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator%( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator+=( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator-=( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator*=( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator/=( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator|( const FunObject& right ) const
{
    return NULL;
}

FunObject* FunObject::operator^( const FunObject& right ) const
{
    return NULL;
}

BoolObject::BoolObject()
{
    return;
}
BoolObject::~BoolObject()
{
    return;
}


CoutObject::CoutObject()
{

}

CoutObject::~CoutObject()
{

}

int32_t CoutObject::invoke( std::vector<ObjectObject*> arg )
{
    std::vector<ObjectObject*>::reverse_iterator iter = arg.rbegin();

    for (;iter != arg.rend();++iter)
    {
        (*iter)->get_ob()->print(std::cout);
        (*iter)->get_ob()->print(debug_stream);
    }
    std::cout << std::endl;
    debug_stream << std::endl;
    return 1;
}
bool CoutObject::operator==( const FunObject& right ) const
{
    debug_stream << "在两个CoutObject之间存在了等于比较，这个功能未完成"
        << std::endl;
    return false;
}

bool CoutObject::operator<( const FunObject& right ) const
{
    debug_stream << "在两个CoutObject之间存在了小于比较，这个功能未完成"
        << std::endl;
    return false;
}

bool CoutObject::operator!=( const FunObject& right ) const
{
    return !(*this == right);
}

bool CoutObject::operator<=( const FunObject& right ) const
{
    return !(right < (*this));
}

bool CoutObject::operator>( const FunObject& right ) const
{
    return right < *this;
}

bool CoutObject::operator>=( const FunObject& right ) const
{
    return !(*this < right);
}

CoutObject::operator bool() const
{
    return true;
}

EF_NAMESPACE_END
