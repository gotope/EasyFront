/*-------------------------------------------------------------------
* Purpose:
*         TestReader.cpp 完成对Reader类的测试工作
* Time:
*         2011年12月8日 19:35:45
* Author:
*         张彦升
--------------------------------------------------------------------*/

#include "../../src/Debug.h"
#include "../../src/Reader.h"

#include <string>

using namespace EF;
using namespace std;

int main()
{
    string file_path("./readertestfile.txt");
    FileReader reader(file_path);
    string buffer;
    uint32_t err = reader.readLine(buffer);
    D(buffer);
    while (err != READ_END)
    {
        err = reader.readLine(buffer);
        D(buffer);
    }
    StdinReader stdinReader;
    stdinReader.readLine(buffer);
    D(buffer);
    stdinReader.readLine(buffer);
    D(buffer);
    return 1;
}