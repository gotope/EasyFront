/*-------------------------------------------------------------------
 * Purpose:
 *         symbol table
 *          符号表
 * Time:
 *         2012年1月7日 19:42:37
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _SYMBOLTABLE_H_2012_1_7_lisency
#define _SYMBOLTABLE_H_2012_1_7_lisency

#include "Base.h"
#include "Node.h"
#include "Token.h"

#include <map>
#include <set>
#include <stack>

EF_NAMESPACE_BEGIN

/**
 * 符号表的类型，包括类类型，函数类型，模块类型
 **/
enum SymbolTableType
{
    CLASS = 1,
    FUN = 2,
    MODULE = 3,
    OTHER = 4,  //包括if，for等没有参数的语句
};

enum SymbolType
{
    FREE = 1,
    GLOBAL = 2,
    LOCAL = 3,
    CELL = 4,
};
/**
 * 符号表管理
 * 根据不同区块生成不同的符号空间
 * 一个文件被引入之后被称为模块，一个模块中可以有不同的命
 *名空间，一个命名空间中存有多个符号
 **/
class SymbolTable
    :public Base
{
public:
    /**
    * description:
    **/
    SymbolTable(SymbolTable* t_prev,std::string t_name);
    /**
    * description:    
    **/
    virtual ~SymbolTable();
    /**
     * 
     */
    virtual SymbolTable* enter_scope(std::string t_name,Node* t_node,
        SymbolTableType t_type = OTHER);
    /**
    *  
    **/
    virtual SymbolTable* find_sym_table(Node* node);
    /**
     * 
     */
    virtual SymbolTable* out_scope();
    /**
    * 得到前一作用域符号表
    * 返回prev
    **/
    virtual SymbolTable* get_prev();
    /**
    * 
    **/
    virtual void set_type(SymbolTableType t_type);
    /**
    * description:   将当前符号压入符号表
    * 压入符号表时查看是否存在，并对其设置相应型别
    * return:        
    **/
    virtual void push_back(std::string item);
    /**
    * 只需要判断该符号是否存在，符号表不会提供符号的值
    **/
    virtual bool find(std::string item);
    /**
    * 在本作用域中查找该符号
    **/
    virtual bool find_local(std::string item);
    /**
     * 得到当前符号表的名字
     */
    virtual std::string get_name();
    /**
    * 传递参数
    **/
    virtual void add_varnames(std::string item);
protected:
    typedef std::set<std::string> SymbolEntry;
    SymbolEntry symbols;  //存所有符号，对应其值

    std::map<Node*,SymbolTable*> symbol_table_map;   
    //该作用域的所有的符号表,当符号表第一次被建立好之后，后面在生产字节码的
    //时候，没进入一个作用域的时候，要根据该作用域的AST跟节点得其符号表。
    std::string name;
    //该符号表的名称，模块对应文件名，函数对应函数名，类对应类名,当调用时使用
    SymbolTableType type;
    //要根据type来判断是否该符号表存在参数
    SymbolEntry varnames;
    //存储该符号入口的参数

private:
    SymbolTable* prev;    //采用链表形式保存符号表

};

EF_NAMESPACE_END

#endif // _SYMBOLTABLE_H_2012_1_7_lisency

