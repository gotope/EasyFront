/*-------------------------------------------------------------------
* Purpose:
*         
* Time:
*         2012年2月25日 20:49:50
* Author:
*         张彦升
--------------------------------------------------------------------*/

#include "../../src/Parser.h"

#include <iostream>
#include <string>
#include <fstream>

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
            cout << "正确文件应是以ef为后缀的文件";
        }
    }
    try
    {
        FileReader reader(file_path);

        EFScanner scanner(reader);

        EFParser parser(scanner);
        Node* module = parser.module();
    }
    catch (EFExc e)
    {
        cout << e.what() << endl;
    }
    return 0;
}