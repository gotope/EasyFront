/*-------------------------------------------------------------------
 * Purpose:
 *         reader class 
 * Time:
 *         2011年8月13日 11:57:03
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "Reader.h"
#include "Debug.h"

EF_NAMESPACE_BEGIN

ReaderBase::ReaderBase()
{
    return;
}
ReaderBase::~ReaderBase()
{
    return;
}
/**
 * 这个函数只读取一个character的内容
 * 将读取到的一个字符转换成一个int型的数值返回
 **/
int32_t ReaderBase::getch()
{
    const char* buffer = NULL;
    const int32_t nread = read(buffer,1, 1);
    if ( nread == READ_END )
    {
        return READ_END;
    }
    else
    {
        return buffer[0];
    }
}
/**
 * 读取当前缓存中的一行
 * @buffer这个引用型的string类型保存了所有读到的内容
 * 如果@buffer并不是空的，函数会清空它
 * 返回读到的character的个数
 **/
uint32_t ReaderBase::readLine(std::string &buffer)
{
    if (buffer.empty() == false)
    {
        D("buffer is not empty,now clear it");
        buffer.clear();
    }

    int32_t b = 0;

    while ((b = getch()) != READ_END)
    {
        if (b == '\n')
        {//判断一行是否结束
            buffer += b;
            break;
        }
        buffer += b;
    }
    std::string::size_type buffer_size = buffer.size();

    if (buffer_size == 0)
    {
        return READ_END;
    }
    else
    {
        return buffer_size;
    }
}
/**
 * 只提供默认实现
 */
uint32_t ReaderBase::read(const char*& start, uint32_t min, uint32_t max)
{
    return READ_END;
}
/**
 * 返回读取位置，由子类实现
 */
uint32_t ReaderBase::position() const
{
    return 0;
}
/**
 * 
 */
size_t ReaderBase::size() const
{
    return 0;
}
/**
 * 
 */
Reader::Reader()
{
    return;
}
/**
 * 
 */
Reader::~Reader()
{
    return;
}
/**
 * 
 */
uint32_t Reader::reset(uint32_t to)
{
    return 0;
}
/**
 * 
 */
uint32_t Reader::skip(int32_t ntoskip)
{
    return 0;
}
/**
 * 
 */
std::string Reader::get_path()
{
    return "";
}
/**
 * 
 */
StdinReader::StdinReader()
{
    D("now construct the StdinReader class");
    this->pos = 0;
}
/**
 * 
 */
StdinReader::~StdinReader()
{
    D("now destructing the StdinReader class");
    return;
}
/**
 * 
 */
StdinReader::StdinReader(const StdinReader &copy_item)
:value(copy_item.value),
pos(copy_item.pos)
{
    D("why are you copy StdinReader? give some reason");
}
/**
 * 
 */
size_t StdinReader::size() const
{
    return value.size();
}
/**
 * 
 */
uint32_t StdinReader::read(const char*& start, uint32_t min, uint32_t max)
{
    if (value.size() == 0)
    {//确保缓存中没有东西，那么我们进行输出
        std::cin.sync();
        std::cin.clear();
        getline(std::cin,value);
    }
    if ( value.size() == pos )
    {
        value.clear();
        pos = 0;
        return READ_END;
    }
    start = value.c_str() + pos;
    uint32_t remain_len = value.size() - pos;
    uint32_t r = (int32_t)get_min(get_max(min,max),remain_len);
    pos += r;
    return r;
}
/**
 * 
 */
uint32_t StdinReader::position() const
{
    return pos;
}
/**
 * 
 */
uint32_t StdinReader::reset(uint32_t pos)
{
    if ( pos >= 0 && pos < this->value.size() )
        this->pos = pos;
    return this->pos;
}
/**
 * 
 */
uint32_t StdinReader::skip(int32_t ntoskip)
{
    int32_t remain_len = value.size()-pos;
    int32_t s = get_min(ntoskip,remain_len);
    this->pos += s;
    return s;
}
/**
 * 
 */
std::string StdinReader::get_path()
{
    return "<stdin>";
}
/**
 * 
 */
FileReader::FileReader( const std::string path, int32_t buflen  )
:file_path(path)
{
    if ( buflen == -1 )
    {
        buflen = DEFAULT_BUFFER_SIZE;
    }

    fs.open(file_path.c_str(),std::ios_base::in | std::ios_base::binary);
    if (!fs)
    {
        EFExc exc(path,0,0,ERROR_FILE_READFAILD);
        throw exc;
    }

    pos = 0;
    buffer_size = 0;
    buffer = new char[buflen];
    memset(buffer,0,buflen);
}
/**
 * 
 */
FileReader::~FileReader()
{
    delete buffer;
}
/**
 * 
 */
size_t FileReader::size() const
{
    return buffer_size;
}
/**
 * 
 */
uint32_t FileReader::read(const char*& start, uint32_t min, uint32_t max)
{//从文件中读入
    if (buffer_size <= 0 || pos >= buffer_size)
    {//如果缓冲区没有读过或已经读完，则从文件中读入
        fs.read(buffer,DEFAULT_BUFFER_SIZE - 1);//4095
        int32_t read_num = fs.gcount();
        buffer[read_num] = 0;
        buffer_size = read_num;
        pos = 0;
    }
    if (buffer_size == 0)
    {
        D("file already read end");
        return READ_END;
    }

    start = this->buffer + pos;
    uint32_t remain_len = buffer_size - pos;
    uint32_t r = (uint32_t)get_min(get_max(min,max),remain_len);
    pos += r;
    return r;
}
/**
 * 
 */
uint32_t FileReader::position() const
{
    return pos;
}
/**
 * 
 */
uint32_t FileReader::reset(uint32_t to)
{
    if ( to >= 0 && to < this->buffer_size)
        this->pos = to;
    return this->pos;
}
/**
 * 
 */
uint32_t FileReader::skip(int32_t ntoskip)
{
    int32_t remain_len = buffer_size-pos;
    int32_t s = get_min(ntoskip,remain_len);
    this->pos += s;
    return s;
}
/**
 * 返回文件路径
 */
std::string FileReader::get_path()
{
    return file_path;
}

EF_NAMESPACE_END

