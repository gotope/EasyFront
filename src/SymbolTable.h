/*-------------------------------------------------------------------
 * Purpose:
 *         symbol table
 *          ���ű�
 * Time:
 *         2012��1��7�� 19:42:37
 * Author:
 *         ������
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
 * ���ű�����ͣ����������ͣ��������ͣ�ģ������
 **/
enum SymbolTableType
{
    CLASS = 1,
    FUN = 2,
    MODULE = 3,
    OTHER = 4,  //����if��for��û�в��������
};

enum SymbolType
{
    FREE = 1,
    GLOBAL = 2,
    LOCAL = 3,
    CELL = 4,
};
/**
 * ���ű����
 * ���ݲ�ͬ�������ɲ�ͬ�ķ��ſռ�
 * һ���ļ�������֮�󱻳�Ϊģ�飬һ��ģ���п����в�ͬ����
 *���ռ䣬һ�������ռ��д��ж������
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
    * �õ�ǰһ��������ű�
    * ����prev
    **/
    virtual SymbolTable* get_prev();
    /**
    * 
    **/
    virtual void set_type(SymbolTableType t_type);
    /**
    * description:   ����ǰ����ѹ����ű�
    * ѹ����ű�ʱ�鿴�Ƿ���ڣ�������������Ӧ�ͱ�
    * return:        
    **/
    virtual void push_back(std::string item);
    /**
    * ֻ��Ҫ�жϸ÷����Ƿ���ڣ����ű����ṩ���ŵ�ֵ
    **/
    virtual bool find(std::string item);
    /**
    * �ڱ��������в��Ҹ÷���
    **/
    virtual bool find_local(std::string item);
    /**
     * �õ���ǰ���ű������
     */
    virtual std::string get_name();
    /**
    * ���ݲ���
    **/
    virtual void add_varnames(std::string item);
protected:
    typedef std::set<std::string> SymbolEntry;
    SymbolEntry symbols;  //�����з��ţ���Ӧ��ֵ

    std::map<Node*,SymbolTable*> symbol_table_map;   
    //������������еķ��ű�,�����ű��һ�α�������֮�󣬺����������ֽ����
    //ʱ��û����һ���������ʱ��Ҫ���ݸ��������AST���ڵ������ű�
    std::string name;
    //�÷��ű�����ƣ�ģ���Ӧ�ļ�����������Ӧ�����������Ӧ����,������ʱʹ��
    SymbolTableType type;
    //Ҫ����type���ж��Ƿ�÷��ű���ڲ���
    SymbolEntry varnames;
    //�洢�÷�����ڵĲ���

private:
    SymbolTable* prev;    //����������ʽ������ű�

};

EF_NAMESPACE_END

#endif // _SYMBOLTABLE_H_2012_1_7_lisency

