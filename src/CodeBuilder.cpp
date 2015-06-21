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

    use_new_block();    //��ʼһ���յ�block

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
    return b;
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
    //ԭ���Ĺ����ǣ��Ӻ����������н���ʱ��Ҫ����ȫ������һ״̬�������뵱ǰ��
    //block��������ˣ�������������һ���ˣ���ô��Ȼ�ڻ����ʱ��ǣ��������
    //�������еĿ飬��������������Ƴ����ں�����ģ������������ʹ�õ�����һ
    //��builder���������߲���ͻ������һ���������if��while��for..���ж���
    //�̳���һ�����µ�block���������ﲻʵ����һ�� 
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
 * ֱ����ת
 */
int32_t CodeBuilder::addop_j_abs(Op opcode,Basicblock* b)
{
    addop_j(opcode,b,1);
    return 1;
}
/**
 * �����ת
 */
int32_t CodeBuilder::addop_j_rel(Op opcode,Basicblock* b)
{
    addop_j(opcode,b,0);
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
 * ���������Ļ���
 */
void CodeBuilder::set_context_ty( Expr_context_ty ty )
{
    etx = ty;
    return;
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
    return STOP_CODE;
}
/**
 * �õ��Ƚϲ�����
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

    Assembler a(nblocks);
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
    code_object->set_codes(codes);
    code_object->set_var(vars);
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
        arg = iter->second;
    }
    //����õ���name��ID�����ڲ��뺯�����ֽ���
    CodeObjectEntry::iterator iter_object = codes.find(arg);

    if (iter_object != codes.end())
    {
        //Ԥ���������Ѿ������ˣ������ض���
        assert(0);  //�����ﵯ��
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
 * װ�����
 * @nblocks ˵��������CFG��ʱ����nblocks���飬���������·���
 *          ��ô���ڴ棬���㽫�䷴�򱣴�
 * @firstlineno ����ָ��ĵ�һ���к�
 */
Assembler::Assembler( int32_t nblocks )
{
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
    return;
}
/**
 * װ��
 */
Assembler::~Assembler()
{
    //���������������ڴ治֪��Ҫ��ô�ͷŲź�
    //ע���ͷŲ��õ��ڴ�
    /*if (a_postorder)
    {
        free(a_postorder);
    }*/
    //���ڴ汻codeobjectʹ�ã����Բ����ͷ�
}
/**
 * ������ת��ַ
 * ����������Ƶĵ�Ȼ��Щ����������python����Ʒ��������е��ֽ�����java
 * һ�����Ǳ������ļ��еģ�Ȼ����ר�ŵ��������ִ����Ӧ���ֽ��룬Ȼ������
 * �����Ŀ�н�����������������뷨��Ŀǰ��������Щ����ʵ�ʣ���Ϊ�ǽ���ζ��
 * ����Ҫ�����Ĵ�����ʵ���ڴ����
 */
void Assembler::jump_offsets( Basicblock* blocks )
{
    Basicblock *b = NULL;
    int bsize = 0, 
        totsize = 0, 
        extended_arg_count = 0,
        last_extended_arg_count = 0;

    //forѭ���������еı��˵�ַ
    for (int i = a_nblocks - 1;i >= 0;i--)
    {
        a_postorder[i]->b_offset = totsize;
        totsize ++;

        //modified [3/4/2012 ������]
        /**
            b = a_postorder[i];
            bsize += b->b_iused;    //ָ��ĸ���

            b->b_offset = totsize;  //��ʼ����
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
                //����ת��ַָ��Ŀ���ַ
                instr->i_oparg = instr->i_target->b_offset;
            }
            else if (instr->i_jrel)
            {
                //��Ե�ת�Ĳ����Ǹ�ָ�Ŀ���ַ��ƫ�ƴ�С

                //modified [3/4/2012 ������]
                /*
                    int delta = instr->i_target->b_offset - bsize;
                    instr->i_oparg = delta;
                */

                instr->i_oparg = instr->i_target->b_offset;
            }
        }
    }
    //���������е�ַ�������
    return;
}
/**
 * depth first search
 * �ݹ����DFS,������ȱ��������еĿ鷴�򱣴�
 */
void Assembler::dfs( Basicblock *b )
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
