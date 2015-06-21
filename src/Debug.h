/*-------------------------------------------------------------------
 * Purpose:
 *         Lise Debug class �����ʹ�þ�̬��Ա���Ǻܺã����ǻ��Ǹ�һ�°�
 * Time:
 *         2011��11��30�� 16:04:20
 * Author:
 *         ������
--------------------------------------------------------------------*/

#ifndef _EFDEBUG_H_2011_11_30_lisency
#define _EFDEBUG_H_2011_11_30_lisency

#include <iostream>
#include <string>
#include <fstream>

#include "Misc.h"

EF_NAMESPACE_BEGIN

/**
 *  ������
 * һ�ٵĸ�������࡭��
 * Ҳ��ѡ��bridgeģʽ�ȽϺ�
 * ������ֻ�������������Ժ�����ƺò�
 **/
class EfDebug
{
public:
    /**
    *  ���캯�������������
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
    std::ostream *ost1;    //��һ���������
    std::ostream *ost2;    //�ڶ����������
    /**
    *  ����Ĭ�Ͽ�ʼ���
    **/
    void outbegin()
    {
        return;
    }
    /**
    *  ����Ĭ�Ͻ������
    **/
    void outend()
    {
        return;
    }
private:
};
/**
 *  ���Ǿ��Ȳ�Ҫ˵������Ʒ����ĺû��ˡ���
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
 *  d:debug��Ϣ��������Ļ���������DEBUG�ļ����
 * l:log��Ϣ��ֻ��log�ļ����
 * e:error��Ϣ������Ļ��log�ļ����
 * i:information,������Ļ���
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

