/*-------------------------------------------------------------------
 * Purpose:
 *         symbol table 
 * Time:
 *         2012年1月7日 19:43:32
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "SymbolTable.h"

EF_NAMESPACE_BEGIN

/**
 *  构造函数，顺便连接在上一作用域上
 **/
SymbolTable::SymbolTable(SymbolTable *t_prev,std::string t_name)
:prev(t_prev),
name(t_name)
{
    return;
}
/**
 * 
 **/
SymbolTable::~SymbolTable()
{
    return;
}
/**
 * 将该作用域存入符号表
 **/
SymbolTable* SymbolTable::enter_scope(std::string t_name,Node* t_node,
                                      SymbolTableType t_type)
{
    SymbolTable* t_table = new SymbolTable(this,t_name);

    t_table->set_type(t_type);
    //将该符号表与其地址映射
    symbol_table_map.insert(std::make_pair(t_node,t_table));

    return t_table;
}
/**
 *  根据节点找到符号表入口
 **/
SymbolTable* SymbolTable::find_sym_table(Node* node)
{
    std::map<Node*,SymbolTable*>::iterator iter = symbol_table_map.find(node);

    if (iter == symbol_table_map.end())
    {
        return NULL;
    }
    return iter->second;
}
/**
 * 
 */
SymbolTable* SymbolTable::out_scope()
{
    return get_prev();
}
/**
 * 
 */
SymbolTable* SymbolTable::get_prev()
{
    return prev;
}
/**
 * 
 **/
void SymbolTable::set_type(SymbolTableType t_type)
{
    type = t_type;
    return ;
}
/**
 * 
 */
void SymbolTable::push_back(std::string item)
{
    if (find_local(item) == NULL)
    {
        symbols.insert(item);
    }
    return;
}
/**
 * 找到之后返回其值，否则返回NULL
 **/
bool SymbolTable::find(std::string item)
{
    SymbolTable* t_sym_table = this;

    while (t_sym_table != NULL)
    {
        bool b_found = t_sym_table->find_local(item);
        if (b_found == true)
        {
            return true;
        }
        t_sym_table = t_sym_table->get_prev();
    }
    return false;
}
/**
 * 
 */
std::string SymbolTable::get_name()
{
    return name;
}
/**
 * 在本作用域中查看，如果找到了在返回真，否在返回假
 **/
bool SymbolTable::find_local( std::string item )
{
    SymbolEntry::iterator iter = symbols.find(item);
    if (iter != symbols.end())
    {
        return true;
    }
    //存参数变量中寻找
    iter = varnames.find(item);

    if (iter != varnames.end())
    {
        return true;
    }
    return false;
}
/**
 * 添加一个新的参数成员
 **/
void SymbolTable::add_varnames(std::string item)
{
    varnames.insert(item);
    return;
}


EF_NAMESPACE_END