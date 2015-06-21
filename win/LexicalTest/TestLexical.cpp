/*-------------------------------------------------------------------
* Purpose:
*         
* Time:
*         2011年11月30日 16:58:29
* Author:
*         张彦升
--------------------------------------------------------------------*/

#include "Scanner.h"
#include "Reader.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace EF;

int main(int argc,char *argv[])
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
    std::fstream cout("output.txt",std::ios::out);
    try
    {
        FileReader reader(file_path);

        EFScanner scanner(reader);

        Token* token = scanner.nextToken();

        token->print_head(cout);
        token->print(cout);
        while (token != NULL && token->id != ERRORTOKEN &&
            token->id != ENDMARKER)
        {
            token = scanner.nextToken();
            token->print(cout);
        }

    }
    catch (EFExc e)
    {
        cout << e.what();
    }
    return 1;
}