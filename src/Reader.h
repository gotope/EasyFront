/*-------------------------------------------------------------------
 * Purpose:
 *         Reader类负责对字符串及文件内容的读取
 * Time:
 *         2011年8月13日 9:00:09
 * Author:
 *         张彦升
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

#define READ_END            0    //由Reader读入时，到末尾或字符流没有内容

/**
 * 好的接口应该尽量减小其耦合度
 * ReaderBase将提供读取一行与一个字符的接口，
 * 这个类接口很像FactoryPattern
 * 每个Reader维护着一个缓冲区
 * 待留问题    :
 * 1,设置双缓存
 * 2,reader假设是在完全没有读入错误的情况下，
 *   这需要更多的考虑
 * 3,读的异常返回状态难道只有READ_END这一个吗？
 *   究竟需不需要加更多的状态?
 * 4,发现偶尔需要从当前位置向前查找一个字符，
 *   这需要一个查找函数
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
    * 由min和max控制向start中读入字符
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
    *  得到当前读取路径
    **/
    virtual std::string get_path();
protected:

private:
};

/**
 *   命令行输入模式
 *  若需其它字符，而缓存中读完了，哦哦，对不起，需要
 *  双缓存
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
    *   拷贝构造
    **/
    StdinReader(const StdinReader &copy_item);

    /**
    *   这个是最主要的一个函数
    **/
    virtual uint32_t read(const char*& start, uint32_t min, uint32_t max);
    /**
    *   返回缓冲区的位置
    **/
    virtual uint32_t position() const;
    /**
    *   重新设置缓存的位置
    **/
    virtual uint32_t reset(uint32_t to= 0);
    /**
    *   移动缓存的位置
    **/
    virtual uint32_t skip(int32_t ntoskip);
    /**
    *   返回缓存的大小
    **/
    virtual size_t size() const;
    /**
    *  得到当前读取路径
    **/
    virtual std::string get_path();
};

/**
 *   对文件读取来说，照样也需要个双缓存
 **/
class FileReader
    : public Reader
{//从文件中读取
public:
    static const int DEFAULT_BUFFER_SIZE = 4096;

    /**
    *   构造函数
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
    *  得到当前读取路径
    **/
    virtual std::string get_path();
protected:

private:
    /**
    *   拷贝构造
    **/
    FileReader(const FileReader& nocopy);
    //这个类将不允许被拷贝
    FileReader& operator=(const FileReader& nocopy);
    std::fstream fs;
    std::string file_path;
    //在后需要文件名（如词法或语法分析中的错误提示）

    uint32_t buffer_size;    //buffer所存数据的长度
    uint32_t pos;        //read position
    char *buffer;
};

EF_NAMESPACE_END

#endif // _READER_H_2011_8_12_lisency

