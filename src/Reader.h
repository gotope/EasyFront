/*-------------------------------------------------------------------
 * Purpose:
 *         Reader�ฺ����ַ������ļ����ݵĶ�ȡ
 * Time:
 *         2011��8��13�� 9:00:09
 * Author:
 *         ������
--------------------------------------------------------------------*/

#ifndef _READER_H_2011_8_12_lisency
#define _READER_H_2011_8_12_lisency


#include "Util.h"
#include "Misc.h"
#include "Exception.h"

#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>

EF_NAMESPACE_BEGIN

#define READ_END            0    //��Reader����ʱ����ĩβ���ַ���û������

/**
 * �õĽӿ�Ӧ�þ�����С����϶�
 * ReaderBase���ṩ��ȡһ����һ���ַ��Ľӿڣ�
 * �����ӿں���FactoryPattern
 * ÿ��Readerά����һ��������
 * ��������    :
 * 1,����˫����
 * 2,reader����������ȫû�ж�����������£�
 *   ����Ҫ����Ŀ���
 * 3,�����쳣����״̬�ѵ�ֻ��READ_END��һ����
 *   �����費��Ҫ�Ӹ����״̬?
 * 4,����ż����Ҫ�ӵ�ǰλ����ǰ����һ���ַ���
 *   ����Ҫһ�����Һ���
 **/
class ReaderBase
    :public Base
{
public:
    /**
    * read only one char
    * return the read char by signed int type
    * if nothing we read return READ_END
    **/
    int32_t getch();
    /**
    * read a line string,mean that split with the '\n'
    * @buffer    (reference type,but if it is not NULL,
    * we will clear it),save the read value
    * if nothing we read return READ_END
    **/
    uint32_t readLine(std::string &buffer);
    /**
    * ��min��max������start�ж����ַ�
    * read the get_min(@min,@max) number character
    * @start,a reference pointer to store the read character
    * @min and @max control the read number
    * the read character number;
    **/
    virtual uint32_t read(const char*& start,uint32_t min, uint32_t max) = 0;
    /**
    * return the current read offset position
    **/
    virtual uint32_t position() const = 0;
    /**
    * return the buffer size 
    **/
    virtual size_t size() const = 0;
    /**
    *  
    **/
    //virtual int32_t thisId() = 0;
protected:
    ReaderBase();
    virtual ~ReaderBase() = 0;
private:
};

class Reader
    :public ReaderBase
{
public:
    Reader();
    virtual ~Reader();
    /**
    *   reset the read offset position 
    * @to the position value,@to must within the limit[0,this->size()]
    *  if out of the range,do nothing,just return current position
    *  however it return current position
    **/
    virtual uint32_t reset(uint32_t to= 0);
    /**
    *   at any time you want to skip some position without read it,you can use this method
    * @ntoskip,n number of position you will skip,is equivalent to 
    *  this->pos = this->pos + @ntoskip
    *  the real skiped number,only if @ntoskip is greater than this->size() - @ntoskip,it
    *  set the position to the end and return the end position
    **/
    virtual uint32_t skip(int32_t ntoskip);
    /**
    *  �õ���ǰ��ȡ·��
    **/
    virtual std::string get_path();
protected:

private:
};

/**
 *   ����������ģʽ
 *  ���������ַ����������ж����ˣ�ŶŶ���Բ�����Ҫ
 *  ˫����
 **/
class StdinReader
    : public Reader
{
protected:
    std::string value;
    uint32_t pos;        //read position
public:
    /**
    *  
    **/
    StdinReader();
    /**
    *  
    **/
    virtual ~StdinReader();
    /**
    *   ��������
    **/
    StdinReader(const StdinReader &copy_item);

    /**
    *   ���������Ҫ��һ������
    **/
    virtual uint32_t read(const char*& start, uint32_t min, uint32_t max);
    /**
    *   ���ػ�������λ��
    **/
    virtual uint32_t position() const;
    /**
    *   �������û����λ��
    **/
    virtual uint32_t reset(uint32_t to= 0);
    /**
    *   �ƶ������λ��
    **/
    virtual uint32_t skip(int32_t ntoskip);
    /**
    *   ���ػ���Ĵ�С
    **/
    virtual size_t size() const;
    /**
    *  �õ���ǰ��ȡ·��
    **/
    virtual std::string get_path();
};

/**
 *   ���ļ���ȡ��˵������Ҳ��Ҫ��˫����
 **/
class FileReader
    : public Reader
{//���ļ��ж�ȡ
public:
    static const int DEFAULT_BUFFER_SIZE = 4096;

    /**
    *   ���캯��
    **/
    FileReader ( const std::string path, int32_t buflen = -1 );
    /**
    *   destructor 
    **/
    virtual ~FileReader ();

    /**
    *  
    **/
    virtual uint32_t read(const char*& start, uint32_t min, uint32_t max);
    /**
    *   as well
    **/
    virtual uint32_t position() const ;
    /**
    *  
    **/
    virtual uint32_t reset(uint32_t to= 0);
    /**
    *   skip n position
    **/
    virtual uint32_t skip(int32_t ntoskip);
    /**
    *   total size
    **/
    virtual size_t size() const ;
    /**
    *  �õ���ǰ��ȡ·��
    **/
    virtual std::string get_path();
protected:

private:
    /**
    *   ��������
    **/
    FileReader(const FileReader& nocopy);
    //����ཫ����������
    FileReader& operator=(const FileReader& nocopy);
    std::fstream fs;
    std::string file_path;
    //�ں���Ҫ�ļ�������ʷ����﷨�����еĴ�����ʾ��

    uint32_t buffer_size;    //buffer�������ݵĳ���
    uint32_t pos;        //read position
    char *buffer;
};

EF_NAMESPACE_END

#endif // _READER_H_2011_8_12_lisency

