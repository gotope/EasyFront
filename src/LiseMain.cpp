/*-------------------------------------------------------------------
 * Purpose:
 *         ������������������ں����ٲ�ȫ
 *          �ع�ͷ�ٿ���ʱ������һ�Ρ��������ԭ�򣬷��ϲ�����
 *
 *          �����е�ì�ܣ�
 *          1.�Դ�����ʹ���׳��쳣���أ�����ʹ�ô���״̬��
 *            ����ʹ�ô���״̬�ܷ�����Ӵ���ָ���������Ҫ���������
 *            ���ǡ�Ŀǰ��ʹ���쳣���Դ�����û�������κ����Եľ���
 *          2.ʲô�����ʹ��C���Է��Ĵ��뷽ʽ��
 *            C�ķ��ʽ�򵥣�����ֻ���ķ�����ʹ�������ַ�����
 *            ���������£�ʹ����������������ģʽ�۶�
 * Time:
 *         2011��12��11�� 15:35:30
 * Author:
 *         ������
--------------------------------------------------------------------*/

#include "Scanner.h"
#include "Reader.h"
#include "Parser.h"

using namespace EF;

int main(int argc,char *argv[])
{
    //ϵͳ��Ŀ¼
    const std;:string root_dir("D:\\zh-y-sh\\ProgramDesign\\vs2008\\lise\\");
    //�����Ե��ļ�Ŀ¼
    const std::string file_dir = root_dir + "doc\\test\\";
    const std::string file_name = "program.py";
    const std::string file_path = file_dir + file_name;

    FileReader reader(file_path);

    EFScanner scanner(reader);
    EFParser parser(&scanner);
    Node* module = parser.module();
    //�����﷨����Ҫ�����м���ʽ���룬�����Ƿ���Ҫ��module�����з���

    Object* op_code;
    Compiler::compile(module,op_code);

    //parser = new Parser();//parser������Ǹ��ѵ�
    //concrettree = new ConcreteTree(reader); //���������
    //ASTtree = concrettree.toAST();//�о������������﷨��
    //�����﷨��ִ���������
    return 1;
};
