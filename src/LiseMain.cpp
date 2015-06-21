/*-------------------------------------------------------------------
 * Purpose:
 *         主函数，这个函数会在后面再补全
 *          回过头再看的时候，再问一次“六大设计原则，符合不？”
 *
 *          程序中的矛盾：
 *          1.对错误处理使用抛出异常好呢？还是使用错误状态？
 *            考虑使用错误状态能方便添加错误恢复，但其需要更加周详的
 *            考虑。目前在使用异常。对错误处理没有做出任何理性的抉择
 *          2.什么情况下使用C语言风格的代码方式？
 *            C的风格方式简单，我们只在文法部分使用了这种方案，
 *            大多数情况下，使用面向对象风格，以设计模式累堆
 * Time:
 *         2011年12月11日 15:35:30
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "Scanner.h"
#include "Reader.h"
#include "Parser.h"

using namespace EF;

int main(int argc,char *argv[])
{
    //系统根目录
    const std;:string root_dir("D:\\zh-y-sh\\ProgramDesign\\vs2008\\lise\\");
    //做测试的文件目录
    const std::string file_dir = root_dir + "doc\\test\\";
    const std::string file_name = "program.py";
    const std::string file_path = file_dir + file_name;

    FileReader reader(file_path);

    EFScanner scanner(reader);
    EFParser parser(&scanner);
    Node* module = parser.module();
    //生成语法树后要生成中间表达式代码，考虑是否需要在module函数中返回

    Object* op_code;
    Compiler::compile(module,op_code);

    //parser = new Parser();//parser的设计是个难点
    //concrettree = new ConcreteTree(reader); //构造具体树
    //ASTtree = concrettree.toAST();//有具体树到抽象语法树
    //抽象语法树执行语意分析
    return 1;
};
