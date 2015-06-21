/*-------------------------------------------------------------------
 * Purpose:
 *         Scanner.h 分词
 * Time:
 *         2011年12月1日 18:15:36
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _SCANNER_H_2011_12_1_lisency
#define _SCANNER_H_2011_12_1_lisency

#include <string>
#include <queue>

#include "Util.h"
#include "Base.h"
#include "Reader.h"
#include "Token.h"

EF_NAMESPACE_BEGIN
/**
 * 分词器，所有在最底层跑的这些类都被留了接口
 **/
class Scanner
    :public Base
{
public:
    /**
    * 构造函数
    **/
    Scanner(Reader &reader);
    /**
    * 析构
    **/
    virtual ~Scanner() = 0;
    /**
    * 获取下一字符串
    * 
    * the token have read,到文件末尾返回NULL
    * 预留问题1,不能有续行符
    *         2,不能有其它进制数字
    *         3,字符串没有处理'的情况,只有"
    *         4,我还不打算支持UTF8，甚至连GBK都难说
    **/
    virtual Token* nextToken();
    /**
    *得到缩进  //notation anded [2/17/2012 张彦升] 
    **/
    int32_t getpendin();
    /**
    *得到当前词法分析工作路径
    **/
    virtual std::string get_path() const
    {
        return reader.get_path();
    }
protected:
    static const int32_t MAXINDENTSIZE = 30;
    //最大缩进值
    Reader &reader;

    int32_t ch;             //当前读入的字符
    int32_t row;           //维护行号
    int32_t col;           //维护列号
    std::string buffer;     //缓存
    int32_t indent_stack[MAXINDENTSIZE];
    int32_t indent_index;   //堆栈的索引值
    int32_t pendin;         //由此得缩进与反缩进
    std::deque<char> back_look_char;
    //以上数据是与其子类共享的

    /**
    * 查看是否是关键字开始字符
    * @ch 要验证的字符
    * 是为真，否为假
    **/
    virtual bool isidentifierstart(int32_t ch);
    /**
    * 验证是否是关键字
    *  @ch 要验证的字符
    * EF_NAMESPACE_BEGIN是为true否为false
    **/
    virtual bool isidentifier(int32_t ch);
    /**
    * 判断是否是数字，其实不打算使这个能继承
    *                也没有多大的意义
    *  @ch 要判断的字符
    * 真为true否为false
    **/
    virtual bool isdigit(int32_t ch);
    /**
    * 验证是否是字符串开始标志，如' "
    *  @ch 要验证的字符
    *真为true假为false
    **/
    virtual bool isstringstart(int32_t ch);
    /**
    * 处理空白，包括tab
    **/
    virtual int32_t procspaces();
    /**
    * 处理缩进
    **/
    virtual int32_t procindent();
    /**
    * 处理新行
    **/
    virtual void procnewline();
    /**
    * 对一个字符的情况做处理
    *  @c1 第一个字符
    * 定义在Token.h中的常量符
    **/
    virtual TokenFlag proconechars(int32_t c1);
    /**
    * 对两个字符的情况做处理
    * @c1 第一个字符
    * @c2 第二个字符
    * 定义在Token.h中的常量符
    **/
    virtual TokenFlag proctwochars(int32_t c1,int32_t c2);
    /**
    * 对三个字符的情况做处理
    * @c1 第一个字符
    * @c2 第二个字符
    * @c3 第三个字符
    * 定义在Token.h中的常量符
    **/
    virtual TokenFlag procthreechars(int32_t c1,int32_t c2,int32_t c3);
    /**
    * 判断是否是注释,或者是注释的开头
    * 如果是，那么交给注释处理函数
    * @ch 要判断的字符
    **/
    virtual bool isannotation(int32_t ch);
    /**
    * 处理注释
    **/
    virtual void procannotation();
    /**
    * 递增行号
    **/
    inline void increaserow()
    {
        row++;    //行号递增
        col = 0;    //列号设为初始值
        return;
    }
    /**
    * 缓存关键字
    * @ch 读入的字符
    **/
    inline void backupch(int32_t ch)
    {
        //char buf[2] = "0";
        //itoa(ch,buf,10);
        //_itoa(ch,buf,10);
        //_itoa_s(ch,buf,2,10);
        //buf[1] = 0;
        buffer += char(ch);
    }
    /**
    * 得到下一字符,并递增列号
    * 返回得到的字符
    **/
    inline int32_t nextch()
    {
        int32_t ch = 0;

        if (back_look_char.empty() == true)
        {
            ch = reader.getch();
            col ++;
        }
        else
        {
            //返回对首的值，且不增行号
            ch = back_look_char.front();
            back_look_char.pop_front();
        }

        return ch;
    }
    /**
     * 根据预先在buffer中留的值构造token
     */
    inline Token* new_token(TokenFlag token_flag)
    {
        return new Token(token_flag,buffer,row,get_prev_col());
    }
    /**
     * 处理关键字
     */
    virtual Token* proc_keyword();
    /**
     * 得到上一词素返回后其起始行号
     */
    inline int32_t get_prev_col()
    {
        int32_t t_size = buffer.empty() ? 0 : buffer.size() - 1 ;
        int32_t t_col = col - t_size - back_look_char.size();

        return t_col;
    }
private:
};

/**
 * 在生成grammrinit.h和grammarinit.cpp的时候会用到
 * 该类已废弃……
 * 如果想起需要处理正则的时候说不定有用
 **/
class RegScanner
    :public Scanner
{
public:
    /**
    * 将参数直接传给基类，自己不持有
    *  @reader 读取内容，或是文件中的，或是Stdin
    **/
    RegScanner(Reader &reader);
    /**
    * I'm do nothing at here
    **/
    virtual ~RegScanner();
protected:
    /**
    * 无需自己扩展
    * 
    * EF_NAMESPACE_BEGIN
    **/
    //virtual bool isidentifierstart(int32_t ch);
    /**
    * 判断是否是关键字，无需自己扩展
    **/
    //virtual bool isidentifier(int32_t ch);
    /**
    * 对本正则表达式的规则中单引号包围的是字符串
    *  @ch 要验证的字符
    * 真为true假为false
    **/
    virtual bool isstringstart(int32_t ch);
    /**
    * 对正则表达式的处理几乎只要将空格和tab删除即可
    * 如果处理空白时，向前看了一位字符，并且刚好要返回
    * indent或dedent，则对下面的程序没有什么影响，但是
    * 如果该缩进与前一缩进有着相同的偏移，那么这一个向前
    * 看字符势必会影响我们后面的程序，为此，返回一个标
    * 志，是否有预留字符
    **/
    virtual int32_t procspaces();
    /**
    * 对缩进没有要求，全部会删掉
    **/
    virtual int32_t procindent();
    /**
    * RegScanner处理新行并不严格
    **/
    virtual void procnewline();
    /**
    * 对一个字符的情况做处理
    *                正则表达式的特殊字符有[]{}|^$?，无需再扩展
    * @c1 第一个字符
    *定义在Token.h中的常量符
    **/
    //virtual TokenFlag proconechars(int32_t c1);
    /**
    * 
    **/
    //virtual TokenFlag proctwochars(int32_t c1,int32_t c2);
    /**
    * 
    **/
    //virtual TokenFlag procthreechars(int32_t c1,int32_t c2,int32_t c3);
    /**
    * 判断是否是注释,或者是注释的开头
    *                如果是，那么交给注释处理函数
    *  @ch 要判断的字符
    **/
    virtual bool isannotation(int32_t ch);
    /**
    * 处理注释
    *暂将注释定为#，完全可以改正
    **/
    virtual void procannotation();
    /**
     * 处理关键字
     */
    virtual Token* proc_keyword();
private:
};
/**
 * 程序分词器
 **/
class EFScanner
    :public Scanner
{
public:
    /**
    * 同样，将参数传给最基类
    *  @reader 读取数据类
    **/
    EFScanner(Reader &reader);
    /**
    * has none special
    **/
    virtual ~EFScanner();
protected:
    /**
    * [a-zA-Z_]使用省缺函数
    * @ch 要验证的字符
    * 是为真，否为假
    **/
    //virtual bool isidentifierstart(int32_t ch);
    /**
    * [a-zA-Z0-9_]使用省缺函数
    * @ch 要验证的字符
    * 是为true否为false
    **/
    //virtual bool isidentifier(int32_t ch);
    /**
    * 验证是否是字符串开始标志，如' "
    这个函数是最有可能扩展的一个函数，以后有可能会做扩展
    * @ch 要验证的字符
    * 真为true假为false
    **/
    virtual bool isstringstart(int32_t ch);
    /**
    * 处理空白，包括tab
    **/
    virtual int32_t procspaces();
    /**
    * 对缩进在这里要求的严格了些，不过不影响：
    * 所有的缩进必须以tab键开始，不允许空格
    **/
    virtual int32_t procindent();
    /**
    * 对本程序来说，处理新行，往往很重要
    **/
    virtual void procnewline();
    /**
    * 对一个字符的情况做处理,使用省缺函数
    * @c1 第一个字符
    * 定义在Token.h中的常量符
    **/
    //virtual TokenFlag proconechars(int32_t c1);
    /**
    * 使用省缺函数，暂时没必要扩展
    **/
    //virtual TokenFlag proctwochars(int32_t c1,int32_t c2);
    /**
    *  使用省缺函数
    **/
    //virtual TokenFlag procthreechars(int32_t c1,int32_t c2,int32_t c3);
    /**
    * 本程序注释以#号开头，没有多行注释
    * 所以处理起来相对简单
    * @ch 要判断的字符
    * 若这个字符是注释的标志，返回真，否为假
    **/
    virtual bool isannotation(int32_t ch);
    /**
    * 处理注释
    **/
    virtual void procannotation();
    /**
     * 处理关键字
     */
    virtual Token* proc_keyword();
private:
};

EF_NAMESPACE_END

#endif // _SCANNER_H_2011_12_1_lisency

