/*-------------------------------------------------------------------
* Purpose:
*         test bytecode generator
* Time:
*         2012��2��26�� 19:26:14
* Author:
*         ������
--------------------------------------------------------------------*/

#include "Scanner.h"
#include "Parser.h"

#include "Compiler.h"

using namespace std;
using namespace EF;

int main(int argc,char *argv[])
{
    std::string file_path;

    if (argc <= 1)
    {
        return -1;
    }
    file_path = argv[1];

    int32_t pos = file_path.find(".ef");

    if (pos == std::string::npos)
    {
        pos = file_path.find(".EF");
        if (pos == std::string::npos)
        {
            cout << "��ȷ�ļ�Ӧ����efΪ��׺���ļ�";
        }
    }
    try
    {
        FileReader reader(file_path);

        EFScanner scanner(reader);

        EFParser parser(scanner);
        Node* module = parser.module();

        CodeObject* byte_code = NULL;
        EfCompiler compiler;
        compiler.compile(module,byte_code);
    }
    catch (EFExc e)
    {
        cout << e.what() << endl;
    }
    return 0;
}