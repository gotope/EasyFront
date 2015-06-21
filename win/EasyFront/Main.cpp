/*-------------------------------------------------------------------
* Purpose:
*         
* Time:
*         2012年2月28日 22:44:28
* Author:
*         张彦升
--------------------------------------------------------------------*/

#include "Util.h"
#include "Base.h"
#include "Scanner.h"
#include "Parser.h"

#include "Compiler.h"
#include "Executor.h"

#include <string>

using namespace std;
using namespace EF;

int main(int argc,char* argv[])
{
    std::string bytecode_file = "bytecode.txt";
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
            cout << "正确文件应是以ef为后缀的文件";
        }
    }

    std::fstream bytecode_stream(bytecode_file.c_str());

    if (file_path.empty())
    {
        return -1;
    }
    try
    {
        EF::FileReader reader(file_path);

        EF::EFScanner scanner(reader);

        EF::EFParser parser(scanner);
        EF::Node* module = parser.module();

        EF::CodeObject* byte_code = NULL;
        EF::EfCompiler compiler;
        compiler.compile(module,byte_code);

        EF::Executor  executor(byte_code);

        int32_t ret = executor.excute();

        if (ret == -1)
        {
            EF::debug_stream << "字节码执行有误" << std::endl;
        }
    }
    catch (EF::EFExc e)
    {
        EF::debug_stream << e.what() << std::endl;
    }
    return 0;
}