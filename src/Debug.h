/*-------------------------------------------------------------------
 * Purpose:
 *         Lise Debug class 这个类使用静态成员不是很好，我们还是改一下吧
 * Time:
 *         2011年11月30日 16:04:20
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _EFDEBUG_H_2011_11_30_lisency
#define _EFDEBUG_H_2011_11_30_lisency

#include <iostream>
#include <string>
#include <fstream>

#include "Misc.h"

EF_NAMESPACE_BEGIN

/**
 *  调试类
 * 一再的更正这个类……
 * 也许选择bridge模式比较好
 * 但现在只能舍弃……等以后看能设计好不
 **/
class EfDebug
{
public:
    /**
    *  构造函数设置输出环境
    **/
    EfDebug(std::ostream &ost1)
        :ost1(&ost1),
        ost2(NULL)
    {
        return;
    }
    EfDebug(std::ostream &ost1,std::ostream &ost2)
        :ost1(&ost1),
        ost2(&ost2)
    {
        return;
    }
    ~EfDebug()
    {
        return;
    }
    EfDebug& operator << (std::string str)
    {
        outbegin();
        *ost1 << str;
        if (ost2 != NULL)
        {
            *ost2 << str;
        }
        outend();
        return *this;
    }
    EfDebug& operator << (uint32_t value)
    {
        outbegin();
        *ost1 << value;
        if (ost2 != NULL)
        {
            *ost2 << value;
        }
        outend();
        return *this;
    }
    EfDebug& operator << (int32_t value)
    {
        outbegin();
        *ost1 << value;
        if (ost2 != NULL)
        {
            *ost2 << value;
        }
        outend();
        return *this;
    }
protected:
    std::ostream *ost1;    //第一个输出环境
    std::ostream *ost2;    //第二个输出环境
    /**
    *  设置默认开始输出
    **/
    void outbegin()
    {
        return;
    }
    /**
    *  设置默认结束输出
    **/
    void outend()
    {
        return;
    }
private:
};
/**
 *  我们就先不要说这中设计方案的好坏了……
 **/
class Debug
    :public EfDebug
{
public:
    Debug();
    ~Debug();
protected:
    
private:
};
class Log
    :public EfDebug
{
public:
    Log();
    ~Log();
protected:
    
private:
};
class Error
    :public EfDebug
{
public:
    Error();
    ~Error();
protected:
    
private:
};
class Info
    :public EfDebug
{
public:
    Info();
    ~Info();
protected:
    
private:
};
/**
 *  d:debug信息，即向屏幕输出，又向DEBUG文件输出
 * l:log信息，只向log文件输出
 * e:error信息，向屏幕和log文件输出
 * i:information,仅向屏幕输出
 **/
extern EfDebug d;
extern EfDebug l;
extern EfDebug e;
extern EfDebug i;

extern std::fstream log_stream;
extern std::fstream debug_stream;

#ifdef EF_DEBUG

#define D(message) std::cout << message << std::endl; \
    debug_stream << "[" << curTimeBuffer() << "]\t" \
    << message << std::endl;
#define L(message) log_stream << "[" << curTimeBuffer() << "]\t" \
    << message << std::endl;
#define E(message) std::cout << message << std::endl; \
    log_stream << "[" << curTimeBuffer() << "]\t" \
    << message << std::endl;
#define I(message) std::cout << message << std::endl;

#else

#define D(message)
#define L(message)
#define E(message)
#define I(message)

#endif
EF_NAMESPACE_END


#endif // _EFDEBUG_H_2011_11_30_lisency

