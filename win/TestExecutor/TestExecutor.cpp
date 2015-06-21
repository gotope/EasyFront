/*-------------------------------------------------------------------
* Purpose:
*         test execute the bytecode
* Time:
*         2012年3月1日 23:13:18
* Author:
*         张彦升
--------------------------------------------------------------------*/

#include "Executor.h"
#include "Parser.h"
#include "Scanner.h"
#include "Debug.h"
#include "Compiler.h"

#include <string>

/**
 * execute bytecode
 **/
int main()
{
    try
    {
        std::string file_path("bit_operation.ef");
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