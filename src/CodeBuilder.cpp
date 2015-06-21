/*-------------------------------------------------------------------
 * Purpose:
 *         CodeBuilder.cpp 生成字节码实现
 * Time:
 *         2012年2月9日 17:06:50
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "CodeBuilder.h"
#include "Opcode.h"

#include <assert.h>

EF_NAMESPACE_BEGIN

/**
 * description:    
 * parameters:    
 * return:        
 **/
CodeBuilder::CodeBuilder(SymbolTable* t_sym_table)
:sym_table(t_sym_table)
{
    block = NULL;
    curblock = NULL;
    endblock = NULL;
    nextblock = NULL;
    selfblock = NULL;

    use_new_block();    //初始一个空的block

    etx = Empty;
    return;
}
/**
 * description:    
 * parameters:    
 * return:        
 **/
CodeBuilder::~CodeBuilder()
{
    return;
}
/**
 *  返回字节码序列
 **/
CodeObject* CodeBuilder::get_code()
{
    return code_object;
}
/**
 *  创建一个新的block
 **/
Basicblock* CodeBuilder::new_block()
{
    Basicblock *b;

    b = new Basicblock;
    if (b == NULL) {
        return NULL;
    }
    memset((void *)b, 0, sizeof(Basicblock));
    b->b_list = block;
    block = b;  //将彼此链起来
    return b;
}
/**
 * 仅是使用一个块，在开始处调用比较方便
 **/
Basicblock* CodeBuilder::use_new_block()
{
    Basicblock *t_block = new_block();
    if (t_block == NULL)
    {
        return NULL;
    }

    curblock = t_block;
    return t_block;
}
/**
 *  
 **/
Basicblock* CodeBuilder::next_block()
{
    Basicblock *t_block = new_block();
    if (t_block == NULL)
    {
        return NULL;
    }
    curblock->b_next = t_block;    //链在前一链表之后
    curblock = t_block;    //让cur_block指向当前链表

    return t_block;
}
/**
 *  
 **/
Basicblock* CodeBuilder::use_next_block(Basicblock* t_block)
{
    assert(t_block != NULL);
    curblock->b_next = t_block;
    curblock = t_block;
    return t_block;
}
/**
 *  进入一个新的作用域
 **/
int32_t CodeBuilder::enter_scope(Node* node)
{
    sym_table = sym_table->find_sym_table(node);
    //进入该作用域，并创建新的流程块
    //原本的顾虑是：从函数作用域中进入时，要求完全进入另一状态，不能与当前的
    //block相连，因此，这里连若连到一起了，那么必然在回填的时候牵扯到函数
    //作用域中的块，而到后面我们设计成了在函数和模块作用域中又使用的是另一
    //个builder，所以两者不冲突，而在一般的作用域（if，while，for..）中都会
    //继承上一项留下的block，所以这里不实用这一句 
    /*if (use_new_block() == NULL)
    {
        return 0;
    }*/
    return 1;
}
/**
 *  
 **/
int32_t CodeBuilder::out_scope()
{
    sym_table = sym_table->out_scope();
    return 0;
}
/**
 *  添加一个新的指令
 * return:  
 **/
int32_t CodeBuilder::addop( Op opcode )
{
    Basicblock *b;
    Instruction *i;
    int off;
    off = next_instr();
    if (off < 0)
    {
        return 0;
    }
    b = curblock;
    i = &b->b_instr[off];
    i->i_opcode = opcode;
    i->i_hasarg = 0;
    
    if (opcode == RETURN_VALUE)
    {
        b->b_return = 1;
    }
    return 1;
}
/**
 *  
 **/
int32_t CodeBuilder::addop_i(Op opcode, int32_t oparg)
{
    Instruction *i;
    int off;
    off = next_instr();
    if (off < 0)
        return 0;
    i = &curblock->b_instr[off];
    i->i_opcode = opcode;
    i->i_oparg = oparg;
    i->i_hasarg = 1;
    return 1;
}
/**
 *  
 **/
int32_t CodeBuilder::addop_j(Op opcode, 
                             Basicblock *b,
                             int32_t absolute)
{
    Instruction *i;
    int off;

    assert(b != NULL);
    off = next_instr();
    if (off < 0)
        return 0;
    i = &curblock->b_instr[off];
    i->i_opcode = opcode;
    i->i_target = b;
    i->i_hasarg = 1;
    if (absolute)
    {
        i->i_jabs = 1;
    }
    else
    {
        i->i_jrel = 1;
    }
    return 1;
}
/**
 * 直接跳转
 */
int32_t CodeBuilder::addop_j_abs(Op opcode,Basicblock* b)
{
    addop_j(opcode,b,1);
    return 1;
}
/**
 * 相对跳转
 */
int32_t CodeBuilder::addop_j_rel(Op opcode,Basicblock* b)
{
    addop_j(opcode,b,0);
    return 1;
}
/**
 * 从names变量中查找name是否存在
 **/
int32_t CodeBuilder::add_name(std::string& name)
{
    StrTable::iterator iter = names.find(name);

    //若找到则返回其ID，若没有找到则返回当前name域的大小，并将该name插入
    //到names中，因为生成字节码之前就应该已经判断完毕该name在不存在的情况
    //下是否应该报错，而此时已经在生产字节码阶段，表示我们需要该符号，因此
    //直接存入name域中
    int32_t size = names.size();

    if (iter == names.end())
    {
        names.insert(std::make_pair(name,size));
        return size;
    }
    else
    {
        return iter->second;
    }
}
/**
 *  
 **/
int32_t CodeBuilder::addop_name(Op opcode,std::string& name)
{
    int arg = add_name(name);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
/**
 *  
 **/
int32_t CodeBuilder::add_const(std::string& t_const)
{
    StrTable::iterator iter = consts.find(t_const);

    int32_t size = consts.size();

    if (iter == consts.end())
    {
        consts.insert(std::make_pair(t_const,size));
        return size;
    }
    else
    {
        return iter->second;
    }
    return 0;
}
/**
 *  
 **/
int32_t CodeBuilder::addop_const(Op opcode,std::string& t_const)
{
    int arg = add_const(t_const);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
/**
 *  
 **/
int32_t CodeBuilder::add_varname( std::string& var )
{

    StrTable::iterator iter = varnames.find(var);

    uint32_t size = varnames.size();

    if (iter == varnames.end())
    {
        varnames.insert(std::make_pair(var,size));
        return size;
    }
    else
    {
        return iter->second;
    }
    return 0;
}
/**
 *   
 **/
int32_t CodeBuilder::addop_varname( Op opcode,std::string& var )
{
    int arg = add_varname(var);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
int32_t CodeBuilder::add_var(std::string& var)
{
    int arg = add_name(var);
    vars.push_back(arg);
    return 1;
}
/**
 *   
 **/
int32_t CodeBuilder::add_interger( int32_t t_interger )
{

    IntTable::iterator iter = intergers.find(t_interger);

    uint32_t size = intergers.size();

    if (iter == intergers.end())
    {
        intergers.insert(std::make_pair(t_interger,size));
        return size;
    }
    else
    {
        return iter->second;
    }
}
/**
 *   
 **/
int32_t CodeBuilder::addop_interger( Op opcode,int32_t t_interger )
{
    int arg = add_interger(t_interger);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
/**
 *   
 **/
int32_t CodeBuilder::add_float( double t_double )
{

    FloatTable::iterator iter = floats.find(t_double);

    uint32_t size = floats.size();

    if (iter == floats.end())
    {
        floats.insert(std::make_pair(t_double,size));
        return size;
    }
    else
    {
        return iter->second;
    }
}
/**
 *   
 **/
int32_t CodeBuilder::addop_float( Op opcode,double t_double )
{
    int arg = add_float(t_double);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
/**
 * 返回下一条指令的偏移位置（相对本block）
 **/
int32_t CodeBuilder::next_instr()
{
    Basicblock* b = curblock;

    assert(b != NULL);

    if (b->b_instr == NULL)
    {
        b->b_instr = new Instruction[DEFAULT_BLOCK_SIZE];
        if (b->b_instr == NULL) {
            return -1;
        }

        b->b_ialloc = DEFAULT_BLOCK_SIZE;
        memset((char *)b->b_instr, 0,
            sizeof(Instruction) * DEFAULT_BLOCK_SIZE);
    }
    //空间已经用完
    else if (b->b_iused == b->b_ialloc)
    {
        Instruction *tmp;
        size_t oldsize, newsize;
        oldsize = b->b_ialloc * sizeof(Instruction);
        newsize = oldsize << 1;//内存是成倍增长的

        if (newsize == 0)
        {
            throw_error(ERROR_NO_MEMORY);
            return -1;
        }
        b->b_ialloc <<= 1;
        tmp = (Instruction *)realloc(
            (void *)b->b_instr, newsize);
        if (tmp == NULL)
        {
            throw_error(ERROR_NO_MEMORY);
            return -1;
        }
        b->b_instr = tmp;
        memset((char *)b->b_instr + oldsize, 0, newsize - oldsize);
    }
    return b->b_iused++;
}
/**
 * 设置上下文环境
 */
void CodeBuilder::set_context_ty( Expr_context_ty ty )
{
    etx = ty;
    return;
}
/**
 * 得到上下文环境
 */
Expr_context_ty CodeBuilder::get_context_ty()
{
    return etx;
}
/**
 * 设置结束区块
 */
void CodeBuilder::set_endblock( Basicblock* t_endblock )
{
    endblock = t_endblock;
    return;
}
/**
 * 得到结束区块
 */
Basicblock* CodeBuilder::get_endblock()
{
    return endblock;
}
/**
 * 复合二元操作符
 */
Op CodeBuilder::inplace_binop( TokenFlag tokenflag )
{
    switch (tokenflag) 
    {
    case PLUSEQUAL:
        return INPLACE_ADD;
    case MINEQUAL:
        return INPLACE_SUBTRACT;
    case STAREQUAL:
        return INPLACE_MULTIPLY;
    case SLASHEQUAL:
        return INPLACE_TRUE_DIVIDE;
    case PERCENTEQUAL:
        return INPLACE_MODULO;
    case DOUBLESTAREQUAL:
        return INPLACE_POWER;
    case LEFTSHIFTEQUAL:
        return INPLACE_LSHIFT;
    case RIGHTSHIFTEQUAL:
        return INPLACE_RSHIFT;
    case VBAREQUAL:
        return INPLACE_OR;
    case CIRCUMFLEXEQUAL:
        return INPLACE_XOR;
    case AMPEREQUAL:
        return INPLACE_AND;
    case DOUBLESLASHEQUAL:
        return INPLACE_FLOOR_DIVIDE;
    default:
        throw_error(ERROR_NO_BINOP);
    }
    return STOP_CODE;
}
/**
 * 得到比较操作符
 */
int32_t CodeBuilder::cmpop( TokenFlag token_flag )
{
    switch (token_flag)
    {
    case EQEQUAL:
        return Cmp_EQ;
    case NOTEQUAL:
        return Cmp_NE;
    case LESS:
        return Cmp_LT;
    case LESSEQUAL:
        return Cmp_LE;
    case GREATER:
        return Cmp_GT;
    case GREATEREQUAL:
        return Cmp_GE;
    default:
        return Cmp_BAD;
    }
}
/**
 * 回填CFG
 */
void CodeBuilder::back_pach()
{
    if (curblock->b_return)
    {
        next_block();
        //python在结束的时候添加了NONE，这里没有
        addop(RETURN_VALUE);
    }

    int32_t nblocks = 0;

    Basicblock *b, *entryblock;
    entryblock = NULL;
    //遍历所有的block，并计数，最终entry是第一个被分配的块地址
    //block现在是最末尾的块，所以向上遍历是对的
    for (b = block; b != NULL; b = b->b_list)
    {
        nblocks++;
        entryblock = b;
    }

    Assembler a(nblocks);
    //从entryblock中进入完成向反序表中添加
    a.dfs(entryblock);

    /* Can't modify the bytecode after computing jump offsets. */
    //从最末尾开始
    a.jump_offsets(block);
    //到这里将所有的跳转地址都填好了,现在生成指令

    code_object = a.makecode();
    //将剩余的全局信息全部拷贝过去
    code_object->set_consts(consts);
    code_object->set_names(names);
    code_object->set_varname(varnames);
    code_object->set_interger(intergers);
    code_object->set_floats(floats);
    code_object->set_codes(codes);
    code_object->set_var(vars);
    return;
}
/**
 * 添加函数
 * 主要添加三条指令，一条将该字节码从表中导入运行栈中，第二条提示栈顶是一个
 * 字节码对象，第三条指令根据函数名存入该字节码对象
 */
int32_t CodeBuilder::make_function( std::string fun_name,CodeObject* opcode )
{
    StrTable::iterator iter = names.find(fun_name);

    int32_t arg = names.size();
    if (iter == names.end())
    {
        names.insert(std::make_pair(fun_name,arg));
    }
    else
    {
        arg = iter->second;
    }
    //上面得到了name的ID，现在插入函数的字节码
    CodeObjectEntry::iterator iter_object = codes.find(arg);

    if (iter_object != codes.end())
    {
        //预留，这里已经出错了，函数重定义
        assert(0);  //到这里弹出
        return 0;
    }
    codes.insert(std::make_pair(arg,opcode));
    addop_i(LOAD_OBJECT,arg);

    addop(MAKE_FUNCTION);
    addop_name(STORE_NAME,fun_name);
    return 1;
}

Basicblock* CodeBuilder::get_next_block()
{
    return nextblock;
}

int32_t CodeBuilder::set_next_block( Basicblock* b )
{
    nextblock = b;
    return 0;
}

Basicblock* CodeBuilder::get_self_block()
{
    return selfblock;
}

int32_t CodeBuilder::set_self_block( Basicblock* b )
{
    selfblock = b;
    return 0;
}

std::vector<int32_t> CodeBuilder::get_vars()
{
    return vars;
}

/**
 * 装配填充
 * @nblocks 说明在生成CFG的时候有nblocks个块，到这里重新分配
 *          这么多内存，方便将其反序保存
 * @firstlineno 生成指令的第一个行号
 */
Assembler::Assembler( int32_t nblocks )
{
    a_nblocks = 0;
    //注意装配器的nblocks成员没有被赋nblocks值，它会是调用DFS
    //的时候递增，自动达到与n_blocks相同的大小
    //如果区块太大了会怎么要呢？反正我们这个小的要命
    a_postorder = (Basicblock **)malloc(
        sizeof(Basicblock *) * nblocks);
    if (!a_postorder)
    {
        //这里应该不只是return，应该是抛出内存异常
        throw(ERROR_NO_MEMORY);
        return;
    }
    return;
}
/**
 * 装配
 */
Assembler::~Assembler()
{
    //还有两个变量的内存不知道要怎么释放才好
    //注意释放不用的内存
    /*if (a_postorder)
    {
        free(a_postorder);
    }*/
    //该内存被codeobject使用，所以不能释放
}
/**
 * 回填跳转地址
 * 这里我们设计的当然有些不合理，按照python的设计方案，所有的字节码与java
 * 一样都是保存在文件中的，然后有专门的虚拟机来执行相应的字节码，然而，在
 * 这个项目中将虚拟机单独出来的想法就目前看来还有些不切实际，因为那将意味着
 * 你需要大量的代码来实现内存管理
 */
void Assembler::jump_offsets( Basicblock* blocks )
{
    Basicblock *b = NULL;
    int bsize = 0, 
        totsize = 0, 
        extended_arg_count = 0,
        last_extended_arg_count = 0;

    //for循环计算所有的便宜地址
    for (int i = a_nblocks - 1;i >= 0;i--)
    {
        a_postorder[i]->b_offset = totsize;
        totsize ++;

        //modified [3/4/2012 张彦升]
        /**
            b = a_postorder[i];
            bsize += b->b_iused;    //指令的个数

            b->b_offset = totsize;  //开始是零
            totsize += bsize;
        */
    }

    for (b = blocks; b != NULL; b = b->b_list)
    {
        //bsize = b->b_offset;

        for (int i = 0; i < b->b_iused; i++)
        {
            Instruction *instr = &b->b_instr[i];

           //bsize += 1;

            if (instr->i_jabs)
            {
                //将跳转地址指向目标地址
                instr->i_oparg = instr->i_target->b_offset;
            }
            else if (instr->i_jrel)
            {
                //相对调转的参数是该指令到目标地址的偏移大小

                //modified [3/4/2012 张彦升]
                /*
                    int delta = instr->i_target->b_offset - bsize;
                    instr->i_oparg = delta;
                */

                instr->i_oparg = instr->i_target->b_offset;
            }
        }
    }
    //到这里所有地址回填完毕
    return;
}
/**
 * depth first search
 * 递归调用DFS,深度优先遍历将所有的块反序保存
 */
void Assembler::dfs( Basicblock *b )
{
    if (b->b_seen)
    {
        return;
    }
    //如果b_seen不为1则设置为1
    b->b_seen = 1;
    if (b->b_next != NULL)
    {
        dfs(b->b_next);
    }

    Instruction *instr = NULL;
    //对该块的每一条指令进行遍历
    for (int i = 0; i < b->b_iused; i++)
    {
        instr = &b->b_instr[i];
        //如果该指令有跳转指令则将其跳转指令一块遍历
        if (instr->i_jrel || instr->i_jabs)
        {
            dfs(instr->i_target);
        }
    }
    //以后序的方式将块存在数组中
    a_postorder[a_nblocks++] = b;
}
/**
 * 装配完成之后生成字节码
 */
CodeObject* Assembler::makecode()
{
    CodeObject* code_object = new CodeObject();
    code_object->set_blocks(a_postorder);
    code_object->set_block_size(a_nblocks);

    return code_object;
}


SimpleCodeBuilder::SimpleCodeBuilder( SymbolTable* t_sym_table )
:CodeBuilder(t_sym_table)
{
    return;
}

SimpleCodeBuilder::~SimpleCodeBuilder()
{
    return;
}

EF_NAMESPACE_END
