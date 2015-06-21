/*-------------------------------------------------------------------
 * Purpose:
 *         CodeBuilder.h生成字节码
 * Time:
 *         2012年2月9日 17:06:19
 * Author:
 *         张彦升
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
     * 构造一个装配器
     * @nblocks 用于分配内存
     * @firstlineno 用于生成字节码的行号
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
     * 深度优先遍历，生成反序表
     */
    void dfs(Basicblock *b);
    /**
     * 返回字节码
     */
    CodeObject* makecode();
protected:
    /**
     * 返回指令的大小
     * 该函数已废弃
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
 * 字节码生成器。保留接口方便生成多种字节码，容易使用
 * 开源项目中的optimization algorithm
 * 由于每一种IR的生成方式不一样，所以要实现同意的builder很难
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
    * 返回生成的字节码，还没有优化
    **/
    virtual CodeObject* get_code();
    /**
    * 返回符号表
    **/
    inline SymbolTable* get_symtable()
    {
        return sym_table;
    }
    /**
    * 得到常量表的大小
    **/
    inline uint32_t get_consts_size()
    {
        return (uint32_t)consts.size();
    }
    /**
    * 得到名字表的大小
    **/
    inline uint32_t get_names_size()
    {
        return (uint32_t)names.size();
    }
    /**
    * 得到参数表的大小
    **/
    inline uint32_t get_varnames_size()
    {
        return (uint32_t)varnames.size();
    }
    /**
    * 从符号表中寻找符号
    **/
    inline bool find_symbol(std::string& symbol)
    {
        bool b_found = sym_table->find(symbol);
        return b_found;
    }
    /**
    *  创建一个新块
    *  返回创建好的新块的地址
    **/
    virtual Basicblock* new_block();
    /**
    * 创建一个新块，并使用它，但没有链到全局的链表中
    * 返回的是创建的这一个新块的地址
    **/
    virtual Basicblock* use_new_block();
    /**
    * 创建一个新块，并将其链在以创建的区块的后面
    * 返回创建好的新区块
    **/
    virtual Basicblock* next_block();
    /**
    * 将new_block和use_new_block这两个函数创建的区块链在全局
    * 的区块链上
    * @t_block 在形成跳转指令时，被应用的地址
    * 返回的是t_block本身，并没有实际意义
    **/
    virtual Basicblock* use_next_block(Basicblock* t_block);
    /**
     * 返回当前指向的block
     */
    inline Basicblock* get_cur_blocks()
    {
        return curblock;
    }
    /**
    * 进入一个新的区块，相应的符号表指针要改变
    **/
    int32_t enter_scope(Node* node);
    /**
    *  退出一个新的作用域
    **/
    int32_t out_scope();
    /**
    * 添加新的操作码,无参
    **/
    virtual int32_t addop(Op opcode);
    /**
    * 添加新的操作，一个参数
    **/
    virtual int32_t addop_i(Op opcode,int32_t oparg);
    /**
    *  生成跳转指令
    **/
    virtual int32_t addop_j(Op opcode,Basicblock* b,
        int32_t absolute);
    /**
     * 直接跳转
     */
    virtual int32_t addop_j_abs(Op opcode,Basicblock* b);
    /**
     * 相对跳转
     */
    virtual int32_t addop_j_rel(Op opcode,Basicblock* b);
    /**
    *  找到指定符号的位置
    **/
    virtual int32_t add_name(std::string& name);
    /**
    * 根据名称添加一个字节码
    **/
    virtual int32_t addop_name(Op opcode,std::string& name);
    /**
    * 找到常量在常量表中的位置
    **/
    virtual int32_t add_const(std::string& t_const);
    /**
    * 根据常量名称添加字节码
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
    *  下一条指令的位置
    **/
    int32_t next_instr();
    /**
    *  设置指令的行号
    **/
    void set_lineno(int32_t off);
    /**
    *  设置上下文环境
    **/
    void set_context_ty(Expr_context_ty ty);
    /**
    *  得到上下文环境
    **/
    Expr_context_ty get_context_ty();
    /**
    * 设置结束链
    **/
    void set_endblock(Basicblock* t_endblock);
    /**
    * 得到结束链位置
    **/
    Basicblock* get_endblock();
    /**
    * 得到二元操作符的指令
    **/
    Op inplace_binop(TokenFlag tokenflag);
    /**
    * 返回比较操作符指令
    **/
    int32_t cmpop(TokenFlag token_flag);
    /**
     * 对CFG回填
     */
    void back_pach();
    /**
     * 添加函数对象
     * @ fun_name 函数名称
     * @ opcode 生成的函数字节码对象
     */
    virtual int32_t make_function(std::string fun_name,CodeObject* opcode);
    /**
     * 抛出错误异常
     */
    inline int32_t throw_error(int32_t error_id)
    {
        std::string name = sym_table->get_name();

        EFExc exc(name,-1,-1,error_id);
        throw exc;
        return 0;
    }
    /**
     * 得到下一个块
     */
    Basicblock* get_next_block();
    /**
     * 设置下一个块
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
    //这些变量被CodeObject公用，返回的时候应该一并带上

    static const int DEFAULT_BLOCK_SIZE = 8;

    std::vector<int32_t> vars;  //每个位置对应的参数ID

    StrTable consts;//字符串常量
    StrTable names; //变量名
    StrTable varnames;  //参数名
    IntTable intergers;
    FloatTable floats;
    CodeObjectEntry codes;   //所有的函数和类的入口

    SymbolTable* sym_table;

    Basicblock* block;  //为了形成链表，保留此项
    Basicblock* curblock;

    Basicblock* endblock;
    Basicblock* nextblock;
    Basicblock* selfblock;
    //为了能够回填结束链，在if到elif之间无法穿梭时，使用

    Expr_context_ty etx;

    CodeObject* code_object;
};
/**
 *  实现一种简单的字节码表示方案
 *  IR表示对优化至关重要，我们需要大量的资料参考
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

