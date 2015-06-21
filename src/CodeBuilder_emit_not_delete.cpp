/*-------------------------------------------------------------------
* Purpose:
*         CodeBuilder.cpp 生成字节码实现
* Time:
*         2012年2月9日 17:06:50
* Author:
*         张彦升
--------------------------------------------------------------------*/

#include "CodeBuilder.h"

lise_NAMESPACE_BEGIN

/**
* description:    
* parameters:    
* return:        
**/
CodeBuilder::CodeBuilder()
{
    etx = Empty;
    b_etx_use = false;
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
    return;
}
/**
*  
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
    if (use_new_block() == NULL)
    {
        return 0;
    }
    return 1;
}
/**
*  
**/
int32_t CodeBuilder::out_scope()
{
    sym_table = sym_table->out_scope();
    return;
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
        return 0;
    b = curblock;
    i = &b->b_instr[off];
    i->i_opcode = opcode;
    i->i_hasarg = 0;
    if (opcode == RETURN_VALUE)
        b->b_return = 1;
    set_lineno(off);
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
    set_lineno(off);
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
    i = curblock->b_instr[off];
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
    set_lineno(off);
    return 1;
}
/**
* 从names变量中查找name是否存在
**/
int32_t CodeBuilder::add_name(std::string& name)
{
    StrTable::iterator iter = names.find(name);

    uint32_t size = names.size();

    if (iter == names.end())
    {
        names.insert(std::make_pair(name,size));
        return size;
    }
    else
    {
        return *iter;
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

    uint32_t size = consts.size();

    if (iter == consts.end())
    {
        consts.insert(std::make_pair(t_const,size));
        return size;
    }
    else
    {
        return *iter;
    }
    return;
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
std::int32_t CodeBuilder::add_varname( std::string& var )
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
        return *iter;
    }
    return;
}
/**
*   
**/
std::int32_t CodeBuilder::addop_varname( Op opcode,std::string& var )
{
    int arg = add_varname(var);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
/**
*   
**/
std::int32_t CodeBuilder::add_interger( int32_t t_interger )
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
        return *iter;
    }
}
/**
*   
**/
std::int32_t CodeBuilder::addop_interger( Op opcode,int32_t t_interger )
{
    int arg = addop_interger(t_interger);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
/**
*   
**/
std::int32_t CodeBuilder::add_float( double t_double )
{

    FloatObject::iterator iter = floats.find(t_double);

    uint32_t size = floats.size();

    if (iter == floats.end())
    {
        floats.insert(std::make_pair(t_double,size));
        return size;
    }
    else
    {
        return *iter;
    }
}
/**
*   
**/
std::int32_t CodeBuilder::addop_float( Op opcode,int32_t t_double )
{
    int arg = add_float(t_double);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
/**
*  下一条指令的偏移位置
**/
std::int32_t CodeBuilder::next_instr()
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

        if (newsize == 0) {
            std::string message("no memory");
            MemoryExc exc(message);
            return -1;
        }
        b->b_ialloc <<= 1;
        tmp = (Instruction *)realloc(
            (void *)b->b_instr, newsize);
        if (tmp == NULL) {
            std::string message("no memory");
            MemoryExc exc(message);
            return -1;
        }
        b->b_instr = tmp;
        memset((char *)b->b_instr + oldsize, 0, newsize - oldsize);
    }
    return b->b_iused++;
}
/**
*  设置指令的行号
**/
void CodeBuilder::set_lineno( int32_t off )
{
    Basicblock *b;
    if (lineno_set)
        return;
    lineno_set = 1;
    b = curblock;
    b->b_instr[off].i_lineno = lineno;
}
/**
 * 设置上下文环境
 */
void CodeBuilder::set_context_ty( Expr_context_ty ty )
{
    return etx = ty;
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
lise::Op CodeBuilder::inplace_binop( TokenFlag tokenflag )
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
        std::string message("the augument assign operator not found");
        SyntaxExc exc(message);
        throw exc;
    }
}
/**
 * 得到比较操作符
 */
lise::Op CodeBuilder::cmpop( TokenFlag token_flag )
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
    case NOTEQUAL:
        return Cmp_IS_NOT;
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

    /* Set firstlineno if it wasn't explicitly set. */
    if (!firstlineno)
    {
        //根据第一个块的行号来指定总体的行号
        if (entryblock && entryblock->b_instr)
        {
            firstlineno = entryblock->b_instr->i_lineno;
        }
        else
        {
            firstlineno = 1;
        }
    }
    
    Assembler a(nblocks,firstlineno);
    //从entryblock中进入完成向反序表中添加
    a.dfs(entryblock);

    /* Can't modify the bytecode after computing jump offsets. */
    //从最末尾开始
    a.jump_offsets(block);
    //到这里将所有的跳转地址都填好了,现在生成指令

    /* Emit code in reverse postorder from dfs. */
    //从第一个申请的块开始
    for (int32_t i = a.a_nblocks - 1; i >= 0; i--)
    {
        b = a.a_postorder[i];
        for (int32_t j = 0; j < b->b_iused; j++)
        {
            if (!a.emit(&b->b_instr[j]))
            {
                return;
            }
        }
    }

    code_object = a.makecode();
    return;
}
/**
 * 装配填充
 * @nblocks 说明在生成CFG的时候有nblocks个块，到这里重新分配
 *          这么多内存，方便将其反序保存
 * @firstlineno 生成指令的第一个行号
 */
Assembler::Assembler( int32_t nblocks,int firstlineno )
{
    a_bytecode = new CodeObject();
    if (a_bytecode)
    {
        return 0;
    }
    a_offset = 0;
    a_nblocks = 0;
    //注意装配器的nblocks成员没有被赋nblocks值，它会是调用DFS
    //的时候递增，自动达到与n_blocks相同的大小
    //如果区块太大了会怎么要呢？反正我们这个小的要命
    a_postorder = (Basicblock **)malloc(
        sizeof(Basicblock *) * nblocks);
    if (!a_postorder)
    {
        //这里应该不只是return，应该是抛出内存异常
        return;
    }
    a_lnotab = new CodeObject();
    if (a_lnotab)
    {
        return 0;
    }
    a_lineno = firstlineno;
    a_lineno_off = 0;
    return;
}
/**
 * 装配
 */
Assembler::~Assembler()
{
    //还有两个变量的内存不知道要怎么释放才好
    //注意释放不用的内存
    if (a_postorder)
    {
        free(a_postorder);
    }
}
/**
 * 
 */
std::int32_t Assembler::lnotab( Instruction *i )
{
    int d_bytecode, d_lineno;
    int len;
    unsigned char *lnotab;

    d_bytecode = a_offset - a_lineno_off;
    d_lineno = i->i_lineno - a_lineno;

    assert(d_bytecode >= 0);
    assert(d_lineno >= 0);

    if(d_bytecode == 0 && d_lineno == 0)
    {
        return 1;
    }

    if (d_bytecode > 255)
    {
        int nbytes, ncodes = d_bytecode / 255;
        nbytes = a_lnotab_off + 2 * ncodes;
        len = PyBytes_GET_SIZE(a_lnotab);
        if (nbytes >= len)
        {
            if ((len <= INT_MAX / 2) && (len * 2 < nbytes))
            {
                len = nbytes;
            }
            else if (len <= INT_MAX / 2)
            {
                len *= 2;
            }
            else
            {
                PyErr_NoMemory();
                return 0;
            }
            if (_PyBytes_Resize(&a_lnotab, len) < 0)
            {
                return 0;
            }
        }
        lnotab = (unsigned char *)
            PyBytes_AS_STRING(a->a_lnotab) + a_lnotab_off;
        for (int j = 0; j < ncodes; j++)
        {
            *lnotab++ = 255;
            *lnotab++ = 0;
        }
        d_bytecode -= ncodes * 255;
        a_lnotab_off += ncodes * 2;
    }
    assert(d_bytecode <= 255);
    if (d_lineno > 255)
    {
        int j, nbytes, ncodes = d_lineno / 255;
        nbytes = a_lnotab_off + 2 * ncodes;
        len = PyBytes_GET_SIZE(a->a_lnotab);
        if (nbytes >= len)
        {
            if ((len <= INT_MAX / 2) && len * 2 < nbytes)
            {
                len = nbytes;
            }
            else if (len <= INT_MAX / 2)
            {
                len *= 2;
            }
            else
            {
                PyErr_NoMemory();
                return 0;
            }
            if (_PyBytes_Resize(&a_lnotab, len) < 0)
            {
                return 0;
            }
        }
        lnotab = (unsigned char *)
            PyBytes_AS_STRING(a->a_lnotab) + a_lnotab_off;
        *lnotab++ = d_bytecode;
        *lnotab++ = 255;
        d_bytecode = 0;
        for (j = 1; j < ncodes; j++)
        {
            *lnotab++ = 0;
            *lnotab++ = 255;
        }
        d_lineno -= ncodes * 255;
        a_lnotab_off += ncodes * 2;
    }

    len = PyBytes_GET_SIZE(a->a_lnotab);
    if (a_lnotab_off + 2 >= len)
    {
        if (_PyBytes_Resize(&a_lnotab, len * 2) < 0)
        {
            return 0;
        }
    }
    lnotab = (unsigned char *)
        PyBytes_AS_STRING(a->a_lnotab) + a_lnotab_off;

    a_lnotab_off += 2;
    if (d_bytecode)
    {
        *lnotab++ = d_bytecode;
        *lnotab++ = d_lineno;
    }
    else
    {      /* First line of a block; def stmt, etc. */
        *lnotab++ = 0;
        *lnotab++ = d_lineno;
    }
    a_lineno = i->i_lineno;
    a_lineno_off = a_offset;
    return 1;
}
/**
 * 
 */
std::int32_t Assembler::emit( Instruction *i )
{
    int size, arg = 0, ext = 0;
    Py_ssize_t len = PyBytes_GET_SIZE(a_bytecode);
    char *code;

    size = instrsize(i);
    if (i->i_hasarg)
    {
        arg = i->i_oparg;
        //指令的参数小于0XFFFF的ext都是0
        ext = arg >> 16;//arg > 0XFFFF
    }
    if (i->i_lineno && !lnotab(a, i))
    {
        return 0;
    }
    if (a_offset + size >= len)
    {
        if (_PyBytes_Resize(&a_bytecode, len * 2) < 0)
        {
            return 0;
        }
    }
    code = PyBytes_AS_STRING(a_bytecode) + a_offset;
    a_offset += size;
    if (size == 6)
    {
        assert(i->i_hasarg);
        *code++ = (char)EXTENDED_ARG;
        *code++ = ext & 0xff;
        *code++ = ext >> 8;
        arg &= 0xffff;
    }
    *code++ = i->i_opcode;
    if (i->i_hasarg)
    {
        assert(size == 3 || size == 6);
        *code++ = arg & 0xff;
        *code++ = arg >> 8;
    }
    return 1;
}
/**
 * 
 */
void Assembler::jump_offsets(Basicblock* blocks)
{
    Basicblock *b = NULL;
    int bsize = 0, 
        totsize = 0, 
        extended_arg_count = 0,
        last_extended_arg_count = 0;

    /* Compute the size of each block and fixup jump args.
       Replace block pointer with position in bytecode. */
    do
    {
        totsize = 0;
        //postorder是反序放的，所以还是从最开始分配的那一个开始遍历
        for (int i = a_nblocks - 1; i >= 0; i--)
        {
            b = a_postorder[i];

            //得到块b的大小
            for (int pos = 0; pos < b->b_iused; pos++)
            {
                //加上指令的大小
                Instruction *instr = &b->b_instr[pos];
                bsize += instrsize(instr);
            }
            //对当前指令添加跳转偏移，跳转偏移是总指令空间大小
            b->b_offset = totsize;
            totsize += bsize;
        }
        //到这里所有的空间大小已计算完毕

        last_extended_arg_count = extended_arg_count;
        extended_arg_count = 0;
        //blocks指向的是最后申请的那一个块，所以用b_list遍历
        //循环对每一条指令计算偏移地址
        for (b = blocks; b != NULL; b = b->b_list)
        {
            bsize = b->b_offset;
            for (int i = 0; i < b->b_iused; i++)
            {
                struct instr *instr = &b->b_instr[i];
                /* Relative jumps are computed relative to
                   the instruction pointer after fetching
                   the jump instruction.
                */
                bsize += instrsize(instr);

                if (instr->i_jabs)
                {
                    //将跳转地址指向目标地址
                    instr->i_oparg = instr->i_target->b_offset;
                }
                else if (instr->i_jrel)
                {
                    //相对调转的参数是该指令到目标地址的偏移大小
                    int delta = instr->i_target->b_offset - bsize;
                    instr->i_oparg = delta;
                }
                else
                {
                    continue;
                }
                if (instr->i_oparg > 0xffff)
                {
                    extended_arg_count++;
                }
            }
        }
    } while (last_extended_arg_count != extended_arg_count);
    //当扩展参数的个数不再增长时，结束循环
    //这是由于i_oparg在第二个循环才被赋值，因此要求重新计算
    /* XXX: This is an awful hack that could hurt performance, but
        on the bright side it should work until we come up
        with a better solution.

        The issue is that in the first loop blocksize() is called
        which calls instrsize() which requires i_oparg be set
        appropriately.          There is a bootstrap problem because
        i_oparg is calculated in the second loop above.

        So we loop until we stop seeing new EXTENDED_ARGs.
        The only EXTENDED_ARGs that could be popping up are
        ones in jump instructions.  So this should converge
        fairly quickly.
    */
}
/**
 * depth first search
 * 递归调用DFS,深度优先遍历将所有的块反序保存
 */
void Assembler::dfs( Instruction *b )
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
}

lise_NAMESPACE_END
