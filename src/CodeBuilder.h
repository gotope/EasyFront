/*-------------------------------------------------------------------
 * Purpose:
 *         CodeBuilder.h�����ֽ���
 * Time:
 *         2012��2��9�� 17:06:19
 * Author:
 *         ������
--------------------------------------------------------------------*/

#ifndef _CODEBUILDER_H_2012_2_9_lisency
#define _CODEBUILDER_H_2012_2_9_lisency

//#include "Compiler.h"
#include "Opcode.h"
#include "Object.h"
#include "SymbolTable.h"
#include "Exception.h"

EF_NAMESPACE_BEGIN

class Assembler 
{
public:
    /**
     * ����һ��װ����
     * @nblocks ���ڷ����ڴ�
     * @firstlineno ���������ֽ�����к�
     */
    Assembler(int32_t nblocks);
    /**
     * 
     */
    ~Assembler();
    /**
     * 
     */
    void jump_offsets(Basicblock* blocks);
    /**
     * ������ȱ��������ɷ����
     */
    void dfs(Basicblock *b);
    /**
     * �����ֽ���
     */
    CodeObject* makecode();
protected:
    /**
     * ����ָ��Ĵ�С
     * �ú����ѷ���
     */
    inline int32_t instrsize(Instruction *instr)
    {
        if (!instr->i_hasarg)
            return 1;               /* 1 byte for the opcode*/
        if (instr->i_oparg > 0xffff)
            return 6;               /* 1 (opcode) + 1 (EXTENDED_ARG opcode) + 2 (oparg) + 2(oparg extended) */
        return 3;                   /* 1 (opcode) + 2 (oparg)*/
    }
private:
    int a_nblocks;
    /* number of reachable blocks */
    Basicblock **a_postorder;
    /* list of blocks in dfs postorder */
    Object *a_lnotab;
};

/**
 * �ֽ����������������ӿڷ������ɶ����ֽ��룬����ʹ��
 * ��Դ��Ŀ�е�optimization algorithm
 * ����ÿһ��IR�����ɷ�ʽ��һ��������Ҫʵ��ͬ���builder����
 **/
class CodeBuilder
    :public Base
{
public:
    /**
    * 
    **/
    CodeBuilder(SymbolTable* t_sym_table);
    /**
     *
     **/
    virtual ~CodeBuilder();
    /**
    * �������ɵ��ֽ��룬��û���Ż�
    **/
    virtual CodeObject* get_code();
    /**
    * ���ط��ű�
    **/
    inline SymbolTable* get_symtable()
    {
        return sym_table;
    }
    /**
    * �õ�������Ĵ�С
    **/
    inline uint32_t get_consts_size()
    {
        return (uint32_t)consts.size();
    }
    /**
    * �õ����ֱ�Ĵ�С
    **/
    inline uint32_t get_names_size()
    {
        return (uint32_t)names.size();
    }
    /**
    * �õ�������Ĵ�С
    **/
    inline uint32_t get_varnames_size()
    {
        return (uint32_t)varnames.size();
    }
    /**
    * �ӷ��ű���Ѱ�ҷ���
    **/
    inline bool find_symbol(std::string& symbol)
    {
        bool b_found = sym_table->find(symbol);
        return b_found;
    }
    /**
    *  ����һ���¿�
    *  ���ش����õ��¿�ĵ�ַ
    **/
    virtual Basicblock* new_block();
    /**
    * ����һ���¿飬��ʹ��������û������ȫ�ֵ�������
    * ���ص��Ǵ�������һ���¿�ĵ�ַ
    **/
    virtual Basicblock* use_new_block();
    /**
    * ����һ���¿飬�����������Դ���������ĺ���
    * ���ش����õ�������
    **/
    virtual Basicblock* next_block();
    /**
    * ��new_block��use_new_block������������������������ȫ��
    * ����������
    * @t_block ���γ���תָ��ʱ����Ӧ�õĵ�ַ
    * ���ص���t_block������û��ʵ������
    **/
    virtual Basicblock* use_next_block(Basicblock* t_block);
    /**
     * ���ص�ǰָ���block
     */
    inline Basicblock* get_cur_blocks()
    {
        return curblock;
    }
    /**
    * ����һ���µ����飬��Ӧ�ķ��ű�ָ��Ҫ�ı�
    **/
    int32_t enter_scope(Node* node);
    /**
    *  �˳�һ���µ�������
    **/
    int32_t out_scope();
    /**
    * ����µĲ�����,�޲�
    **/
    virtual int32_t addop(Op opcode);
    /**
    * ����µĲ�����һ������
    **/
    virtual int32_t addop_i(Op opcode,int32_t oparg);
    /**
    *  ������תָ��
    **/
    virtual int32_t addop_j(Op opcode,Basicblock* b,
        int32_t absolute);
    /**
     * ֱ����ת
     */
    virtual int32_t addop_j_abs(Op opcode,Basicblock* b);
    /**
     * �����ת
     */
    virtual int32_t addop_j_rel(Op opcode,Basicblock* b);
    /**
    *  �ҵ�ָ�����ŵ�λ��
    **/
    virtual int32_t add_name(std::string& name);
    /**
    * �����������һ���ֽ���
    **/
    virtual int32_t addop_name(Op opcode,std::string& name);
    /**
    * �ҵ������ڳ������е�λ��
    **/
    virtual int32_t add_const(std::string& t_const);
    /**
    * ���ݳ�����������ֽ���
    **/
    virtual int32_t addop_const(Op opcode,std::string& t_const);
    /**
    *  
    **/
    virtual int32_t add_varname(std::string& var);
    /**
    *  
    **/
    virtual int32_t addop_varname(Op opcode,std::string& var);
    /**
    *  
    **/
    virtual int32_t add_interger(int32_t t_interger);
    /**
    *  
    **/
    virtual int32_t addop_interger(Op opcode,int32_t t_interger);
    /**
    *  
    **/
    virtual int32_t add_float(double t_double);
    /**
    *  
    **/
    virtual int32_t addop_float(Op opcode,double t_double);
    /**
    *  ��һ��ָ���λ��
    **/
    int32_t next_instr();
    /**
    *  ����ָ����к�
    **/
    void set_lineno(int32_t off);
    /**
    *  ���������Ļ���
    **/
    void set_context_ty(Expr_context_ty ty);
    /**
    *  �õ������Ļ���
    **/
    Expr_context_ty get_context_ty();
    /**
    * ���ý�����
    **/
    void set_endblock(Basicblock* t_endblock);
    /**
    * �õ�������λ��
    **/
    Basicblock* get_endblock();
    /**
    * �õ���Ԫ��������ָ��
    **/
    Op inplace_binop(TokenFlag tokenflag);
    /**
    * ���رȽϲ�����ָ��
    **/
    int32_t cmpop(TokenFlag token_flag);
    /**
     * ��CFG����
     */
    void back_pach();
    /**
     * ��Ӻ�������
     * @ fun_name ��������
     * @ opcode ���ɵĺ����ֽ������
     */
    virtual int32_t make_function(std::string fun_name,CodeObject* opcode);
    /**
     * �׳������쳣
     */
    inline int32_t throw_error(int32_t error_id)
    {
        std::string name = sym_table->get_name();

        EFExc exc(name,-1,-1,error_id);
        throw exc;
        return 0;
    }
    /**
     * �õ���һ����
     */
    Basicblock* get_next_block();
    /**
     * ������һ����
     */
    int32_t set_next_block(Basicblock* b);
    /**
     * 
     */
    Basicblock* get_self_block();
    /**
     * 
     */
    int32_t set_self_block(Basicblock* b);
    /**
     * 
     */
    std::vector<int32_t> get_vars();
    /**
     * 
     */
    int32_t add_var(std::string& var);
protected:

private:
    //��Щ������CodeObject���ã����ص�ʱ��Ӧ��һ������

    static const int DEFAULT_BLOCK_SIZE = 8;

    std::vector<int32_t> vars;  //ÿ��λ�ö�Ӧ�Ĳ���ID

    StrTable consts;//�ַ�������
    StrTable names; //������
    StrTable varnames;  //������
    IntTable intergers;
    FloatTable floats;
    CodeObjectEntry codes;   //���еĺ�����������

    SymbolTable* sym_table;

    Basicblock* block;  //Ϊ���γ�������������
    Basicblock* curblock;

    Basicblock* endblock;
    Basicblock* nextblock;
    Basicblock* selfblock;
    //Ϊ���ܹ��������������if��elif֮���޷�����ʱ��ʹ��

    Expr_context_ty etx;

    CodeObject* code_object;
};
/**
 *  ʵ��һ�ּ򵥵��ֽ����ʾ����
 *  IR��ʾ���Ż�������Ҫ��������Ҫ���������ϲο�
 **/
class SimpleCodeBuilder
    :public CodeBuilder
{
public:
    /**
    * 
    **/
    SimpleCodeBuilder(SymbolTable* t_sym_table);
    /**
    * 
    **/
    virtual ~SimpleCodeBuilder();
protected:

private:
};

//so, if I find any good intermediate representation
//this interface is useful

EF_NAMESPACE_END

#endif // _CODEBUILDER_H_2012_2_9_lisency

