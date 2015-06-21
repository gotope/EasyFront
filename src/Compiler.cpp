/*-------------------------------------------------------------------
 * Purpose:
 *         compiler
 * Time:
 *         2012��1��7�� 19:49:42
 * Author:
 *         ������
--------------------------------------------------------------------*/

#include "Compiler.h"
#include "SymbolTable.h"
#include "CodeBuilder.h"
#include "Visitor.h"
#include "Debug.h"

EF_NAMESPACE_BEGIN

/**
 *
 **/
Compiler::Compiler()
{
    return;
}
/**
 *
 **/
Compiler::~Compiler()
{
    return;
}
/**
 *
 **/
int32_t Compiler::compile(Node* ast_root,CodeObject*& op_code)
{
    return 0;
}
/*********begin LiseCompiler class scope*******
/**
 *
 **/
EfCompiler::EfCompiler()
{
    return;
}
/**
 *
 **/
EfCompiler::~EfCompiler()
{
    return;
}
/**
 *
 **/
int32_t EfCompiler::compile(Node* ast_root,CodeObject*& op_code)
{
#ifdef EF_DEBUG
    NodePrintor printor(debug_stream);
    ast_root->visit(printor);

#endif
    SymTableGen sym_table_gen(ast_root->get_file_path());
    ast_root->visit(sym_table_gen);

    SymbolTable* sym_table = sym_table_gen.get_sym_table();//���ط��ű�

    SimpleCodeBuilder code_builder(sym_table);

    //�������÷�ʽ���ݽ�ȥ��
    ByteCodeGen byte_code_gen(code_builder);
    ast_root->visit(byte_code_gen);

    code_builder.back_pach();
    op_code = code_builder.get_code();
    op_code->print(debug_stream);

    NodeReleasor releasor;
    ast_root->visit(releasor);
    delete ast_root;
    //�������Ż�����
    return 1;
}
/*******begin SSACompiler class scope*********
/**
 *
 **/
SSACompiler::SSACompiler()
{
    return;
}
/**
 *
 **/
SSACompiler::~SSACompiler()
{
    return;
}
/**
 * 
 */
int32_t SSACompiler::compile(Node* ast_root,CodeObject*& op_code)
{
    return 0;
}

EF_NAMESPACE_END