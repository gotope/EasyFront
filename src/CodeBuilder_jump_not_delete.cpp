/*-------------------------------------------------------------------
 * Purpose:
 *         CodeBuilder.cpp �����ֽ���ʵ��
 * Time:
 *         2012��2��9�� 17:06:50
 * Author:
 *         ������
--------------------------------------------------------------------*/

#include "CodeBuilder.h"
#include "Opcode.h"

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
    use_new_block();    //��ʼһ���յ�block

    lineno = 0;
    firstlineno = 0;
    col_offset = 0;
    lineno_set = 0;

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
 *  �����ֽ�������
 **/
CodeObject* CodeBuilder::get_code()
{
    return code_object;
}
/**
 *  ����һ���µ�block
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
    block = b;  //���˴�������
    return;
}
/**
 * ����ʹ��һ���飬�ڿ�ʼ�����ñȽϷ���
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
    curblock->b_next = t_block;    //����ǰһ����֮��
    curblock = t_block;    //��cur_blockָ��ǰ����

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
 *  ����һ���µ�������
 **/
int32_t CodeBuilder::enter_scope(Node* node)
{
    sym_table = sym_table->find_sym_table(node);
    //����������򣬲������µ����̿�
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
 *  ���һ���µ�ָ��
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
 * ֱ����ת
 */
int32_t CodeBuilder::addop_j_abs(Op opcode,Basicblock* b)
{
    addop_j(Op,b,1);
    return 1;
}
/**
 * �����ת
 */
int32_t CodeBuilder::addop_j_rel(Op opcode,Basicblock* b)
{
    addop_j(Op,b,0);
    return 1;
}
/**
 * ��names�����в���name�Ƿ����
 **/
int32_t CodeBuilder::add_name(std::string& name)
{
    StrTable::iterator iter = names.find(name);

    //���ҵ��򷵻���ID����û���ҵ��򷵻ص�ǰname��Ĵ�С��������name����
    //��names�У���Ϊ�����ֽ���֮ǰ��Ӧ���Ѿ��ж���ϸ�name�ڲ����ڵ����
    //���Ƿ�Ӧ�ñ�������ʱ�Ѿ��������ֽ���׶Σ���ʾ������Ҫ�÷��ţ����
    //ֱ�Ӵ���name����
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
        return *iter;
    }
    return;
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
        return *iter;
    }
}
/**
 *   
 **/
int32_t CodeBuilder::addop_interger( Op opcode,int32_t t_interger )
{
    int arg = addop_interger(t_interger);
    if (arg < 0)
        return 0;
    return addop_i(opcode, arg);
}
/**
 *   
 **/
int32_t CodeBuilder::add_float( double t_double )
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
 * ������һ��ָ���ƫ��λ�ã���Ա�block��
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
    //�ռ��Ѿ�����
    else if (b->b_iused == b->b_ialloc)
    {
        Instruction *tmp;
        size_t oldsize, newsize;
        oldsize = b->b_ialloc * sizeof(Instruction);
        newsize = oldsize << 1;//�ڴ��ǳɱ�������

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
 *  ����ָ����к�
 * @off��ǰ���ƫ�ƣ������кŸ���CodeBuilder��lineno����
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
 * ���������Ļ���
 */
void CodeBuilder::set_context_ty( Expr_context_ty ty )
{
    return etx = ty;
}
/**
 * �õ������Ļ���
 */
Expr_context_ty CodeBuilder::get_context_ty()
{
    return etx;
}
/**
 * ���ý�������
 */
void CodeBuilder::set_endblock( Basicblock* t_endblock )
{
    endblock = t_endblock;
    return;
}
/**
 * �õ���������
 */
Basicblock* CodeBuilder::get_endblock()
{
    return endblock;
}
/**
 * ���϶�Ԫ������
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
}
/**
 * �õ��Ƚϲ�����
 */
Op CodeBuilder::cmpop( TokenFlag token_flag )
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
 * ����CFG
 */
void CodeBuilder::back_pach()
{
    if (curblock->b_return)
    {
        next_block();
        //python�ڽ�����ʱ�������NONE������û��
        addop(RETURN_VALUE);
    }

    int32_t nblocks = 0;

    Basicblock *b, *entryblock;
    entryblock = NULL;
    //�������е�block��������������entry�ǵ�һ��������Ŀ��ַ
    //block��������ĩβ�Ŀ飬�������ϱ����ǶԵ�
    for (b = block; b != NULL; b = b->b_list)
    {
        nblocks++;
        entryblock = b;
    }

    /* Set firstlineno if it wasn't explicitly set. */
    if (!firstlineno)
    {
        //���ݵ�һ������к���ָ��������к�
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
    //��entryblock�н����������������
    a.dfs(entryblock);

    /* Can't modify the bytecode after computing jump offsets. */
    //����ĩβ��ʼ
    a.jump_offsets(block);
    //�����ｫ���е���ת��ַ�������,��������ָ��

    code_object = a.makecode();
    //��ʣ���ȫ����Ϣȫ��������ȥ
    code_object->set_consts(consts);
    code_object->set_names(names);
    code_object->set_varname(varnames);
    code_object->set_interger(intergers);
    code_object->set_floats(floats);
    return;
}
/**
 * ��Ӻ���
 * ��Ҫ�������ָ�һ�������ֽ���ӱ��е�������ջ�У��ڶ�����ʾջ����һ��
 * �ֽ�����󣬵�����ָ����ݺ�����������ֽ������
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
        arg = *iter;
    }
    //����õ���name��ID�����ڲ��뺯�����ֽ���
    ObjectEntry::iterator iter = codes.find(arg);

    if (iter != codes.end())
    {
        //Ԥ���������Ѿ������ˣ������ض���
        return 0;
    }
    codes.insert(std::make_pair(arg,opcode));
    addop_j(LOAD_OBJECT,arg);

    addop(MAKE_FUNCTION);
    addop_name(STORE_NAME,fun_name);
    return 1;
}
/**
 * װ�����
 * @nblocks ˵��������CFG��ʱ����nblocks���飬���������·���
 *          ��ô���ڴ棬���㽫�䷴�򱣴�
 * @firstlineno ����ָ��ĵ�һ���к�
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
    //ע��װ������nblocks��Աû�б���nblocksֵ�������ǵ���DFS
    //��ʱ��������Զ��ﵽ��n_blocks��ͬ�Ĵ�С
    //�������̫���˻���ôҪ�أ������������С��Ҫ��
    a_postorder = (Basicblock **)malloc(
        sizeof(Basicblock *) * nblocks);
    if (!a_postorder)
    {
        //����Ӧ�ò�ֻ��return��Ӧ�����׳��ڴ��쳣
        throw(ERROR_NO_MEMORY);
        return;
    }
    a_lnotab = new CodeObject();
    if (a_lnotab)
    {
        return;
    }
    a_lineno = firstlineno;
    a_lineno_off = 0;
    return;
}
/**
 * װ��
 */
Assembler::~Assembler()
{
    //���������������ڴ治֪��Ҫ��ô�ͷŲź�
    //ע���ͷŲ��õ��ڴ�
    if (a_postorder)
    {
        free(a_postorder);
    }
}
/**
 * ������ת��ַ
 */
void Assembler::jump_offsets( Basicblock* blocks )
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
        //postorder�Ƿ���ŵģ����Ի��Ǵ��ʼ�������һ����ʼ����
        for (int i = a_nblocks - 1; i >= 0; i--)
        {
            b = a_postorder[i];

            //�õ���b�Ĵ�С
            for (int pos = 0; pos < b->b_iused; pos++)
            {
                //����ָ��Ĵ�С
                Instruction *instr = &b->b_instr[pos];
                bsize += instrsize(instr);
            }
            //�Ե�ǰָ�������תƫ�ƣ���תƫ������ָ��ռ��С
            b->b_offset = totsize;
            totsize += bsize;
        }
        //���������еĿռ��С�Ѽ������

        last_extended_arg_count = extended_arg_count;
        extended_arg_count = 0;
        //blocksָ���������������һ���飬������b_list����
        //ѭ����ÿһ��ָ�����ƫ�Ƶ�ַ
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
                    //����ת��ַָ��Ŀ���ַ
                    instr->i_oparg = instr->i_target->b_offset;
                }
                else if (instr->i_jrel)
                {
                    //��Ե�ת�Ĳ����Ǹ�ָ�Ŀ���ַ��ƫ�ƴ�С
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
    //����չ�����ĸ�����������ʱ������ѭ��
    //��������i_oparg�ڵڶ���ѭ���ű���ֵ�����Ҫ�����¼���
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
 * �ݹ����DFS,������ȱ��������еĿ鷴�򱣴�
 */
void Assembler::dfs( Instruction *b )
{
    if (b->b_seen)
    {
        return;
    }
    //���b_seen��Ϊ1������Ϊ1
    b->b_seen = 1;
    if (b->b_next != NULL)
    {
        dfs(b->b_next);
    }

    Instruction *instr = NULL;
    //�Ըÿ��ÿһ��ָ����б���
    for (int i = 0; i < b->b_iused; i++)
    {
        instr = &b->b_instr[i];
        //�����ָ������תָ��������תָ��һ�����
        if (instr->i_jrel || instr->i_jabs)
        {
            dfs(instr->i_target);
        }
    }
    //�Ժ���ķ�ʽ�������������
    a_postorder[a_nblocks++] = b;
}
/**
 * װ�����֮�������ֽ���
 */
CodeObject* Assembler::makecode()
{
    CodeObject* code_object = new CodeObject();
    code_object->set_blocks(a_postorder);
    code_object->set_block_size(a_nblocks);

    return code_object;
}
EF_NAMESPACE_END
