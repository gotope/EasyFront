/*-------------------------------------------------------------------
 * Purpose:
 *         symbol table 
 * Time:
 *         2012��1��7�� 19:43:32
 * Author:
 *         ������
--------------------------------------------------------------------*/

#include "SymbolTable.h"

EF_NAMESPACE_BEGIN

/**
 *  ���캯����˳����������һ��������
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
 * ���������������ű�
 **/
SymbolTable* SymbolTable::enter_scope(std::string t_name,Node* t_node,
                                      SymbolTableType t_type)
{
    SymbolTable* t_table = new SymbolTable(this,t_name);

    t_table->set_type(t_type);
    //���÷��ű������ַӳ��
    symbol_table_map.insert(std::make_pair(t_node,t_table));

    return t_table;
}
/**
 *  ���ݽڵ��ҵ����ű����
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
 * �ҵ�֮�󷵻���ֵ�����򷵻�NULL
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
 * �ڱ��������в鿴������ҵ����ڷ����棬���ڷ��ؼ�
 **/
bool SymbolTable::find_local( std::string item )
{
    SymbolEntry::iterator iter = symbols.find(item);
    if (iter != symbols.end())
    {
        return true;
    }
    //�����������Ѱ��
    iter = varnames.find(item);

    if (iter != varnames.end())
    {
        return true;
    }
    return false;
}
/**
 * ���һ���µĲ�����Ա
 **/
void SymbolTable::add_varnames(std::string item)
{
    varnames.insert(item);
    return;
}


EF_NAMESPACE_END