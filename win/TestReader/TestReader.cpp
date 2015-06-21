/*-------------------------------------------------------------------
* Purpose:
*         TestReader.cpp ��ɶ�Reader��Ĳ��Թ���
* Time:
*         2011��12��8�� 19:35:45
* Author:
*         ������
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