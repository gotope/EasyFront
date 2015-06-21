/*-------------------------------------------------------------------
 * Purpose:
 *         config.h保存所有配置信息
 * Time:
 *         2011年11月30日 19:40:09
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

/************程序书写规则说明**************
1， 删除指针或数据务必在同一作用域内，在更深层域内不做任何删除动作
2， 在语法分析的时候使用自顶向下的预测分析技术，只要是上下文无关文法即可
    该语言的所有结构都为正则文法
3， 在实际写代码过程中我们经常要返回一些实例，那么这些实例应该由外层的作用域
    进行删除
4， 为了简单起见，暂不考虑多文件
5， 在构造语法树的节点时，有两种选择，一种是按照interpreter模式每个非终结符对应
    一个类，这样会使得类结构显得很庞大，另一个是对类结构进行压缩，对具有相同结构
    类型的非终结符进行划分，将其合并在一个类中，这使得函数个数及接口数量大大减少，
    但结构显得杂乱无章，对此，记住！我使用的是第一种，忘记第二种的好。
6， 对语法树的构造，考虑是否使用builder模式……使用builder模式可以方便的对IR
    扩充，这里暂时不考虑(若使用builder模式，那么必然要求节点能够自我生长，即添加
    与删除，而我们现在的节点信息不是活的，而是死的，所以显得十分困难,若使用list
    节点信息，删除与添加很灵活，但对节点内部信息部明确)
7，    剩余的工作，语法树中保存token是不对的
    符号表的设计
    由module返回节点信息，貌似不妥
    三元式代码组织方式
8， 宁以引用代替指针。在设计scanner传入parser中时，内部变量scanner以引用和指针保存
    的结果是一样的，我们用引用
 **/
#ifndef _CONFIG_H_2011_11_30_lisency
#define _CONFIG_H_2011_11_30_lisency

#include <string>

EF_NAMESPACE_BEGIN

//所有这些文件结尾统一保留'/'，这样会很方便
static const std::string ROOT_PATH = "./";    //根目录
static const std::string LOG_PATH = "./";        //log文件
static const std::string TEMP_PATH = "./";    //临时文件

EF_NAMESPACE_END

#endif // _CONFIG_H_2011_11_30_lisency

