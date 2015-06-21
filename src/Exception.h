/*-------------------------------------------------------------------
 * Purpose:
 *         这是异常最基类
 * Time:
 *         2011年11月30日 15:32:56
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _EFEXCEPTION_H_2011_11_30_lisency
#define _EFEXCEPTION_H_2011_11_30_lisency

#include "Util.h"
#include "Base.h"

#include <stdio.h>
#include <exception>
#include <string>
#include <map>

EF_NAMESPACE_BEGIN

#define ERROR_FILE_READFAILD        1
#define ERROR_FILE_END_NOFORMOR     2
#define ERROR_NO_NEWLINE            3
#define ERROR_REDUNDANT_EQUAL       4
#define ERROR_KEY_MARKER            5
#define ERROR_STMT_END_NOFORMOR     6
#define ERROR_NO_USE_WORD           7
#define ERROR_STACK_OVER_FLOW       8
#define ERROR_ERRORTOKEN            9
#define ERROR_NO_RPAR               10
#define ERROR_NO_SUITE              11
#define ERROR_NO_MEMORY             12
#define ERROR_STMT_EMPTY            13
#define ERROR_NO_FOUND_SYMBOL       14
#define ERROR_NO_BINOP              15
#define ERROR_NO_NUMBER             16
#define ERROR_NO_OBJECT             17
#define ERROR_NO_STRING             18
#define ERROR_WRONG_TYPE            19
/**
 *  这是最基类，但可以被实例化
 * NOTE!既然是基类，又有继承关系，务必使用引用使用
 **/
class EFExc
    : public Base
{
public:
    /**
    *  异常类的构造函数往往给我带来了许多困惑
    **/
    explicit EFExc(std::string t_file_path,
        int32_t t_row,int32_t t_col,int32_t t_error_id)
        : file_path(t_file_path),
        row(t_row),
        col(t_col),
        error_id(t_error_id)
    {
    }
    /**
    *  异常类不允许在析构的时候抛出异常
    **/
    virtual ~EFExc() throw()
    {
    }
    /**
    *  没有返回std::string是为了与标准exception一致
    **/
    virtual const std::string what() throw()
    {
        std::string exc_massage = file_path;

        char message[1000] = "0";
        sprintf_s(message,1000,"\t%s at row:%d column:%d",
            get_message(error_id),row,col);
        exc_massage += message;
        return exc_massage;
    }
    /**
     * 得到错误内容
     */
    const char* get_message(int32_t error_id) const
    {
        switch (error_id)
        {
        case ERROR_FILE_READFAILD:
            return "文件打开失败";
        case ERROR_FILE_END_NOFORMOR:
            return "文件文件以非正常标志结束";
        case ERROR_NO_NEWLINE:
            return "未匹配到新行符";
        case ERROR_REDUNDANT_EQUAL:
            return "未使用等号";
        case ERROR_KEY_MARKER:
            return "标识符后跟非法字符";
        case ERROR_STMT_END_NOFORMOR:
            return "语句非正常结束";
        case ERROR_NO_USE_WORD:
            return "未使用符号";
        case ERROR_STACK_OVER_FLOW:
            return "栈溢出";
        case ERROR_ERRORTOKEN:
            return "错误符号";
        case ERROR_NO_RPAR:
            return "未匹配到右括号";
        case ERROR_NO_SUITE:
            return "未识别suite";
        case ERROR_NO_MEMORY:
            return "内存分配失败";
        case ERROR_STMT_EMPTY:
            return "stmt语句匹配失败";
        case ERROR_NO_FOUND_SYMBOL:
            return "没有找到符号";
        case ERROR_NO_BINOP:
            return "运行时刻二元操作符没有找到";
        case ERROR_NO_NUMBER:
            return "实型或整型参数未找到";
        case ERROR_NO_STRING:
            return " 没有找到字符串常量对象";
        case ERROR_NO_OBJECT:
            return "没有找到字节码对象";
        case ERROR_WRONG_TYPE:
            return "元素类型不同";
        default:
            return "error";
        }
    }
protected:
    const std::string file_path;
    const int32_t row;
    const int32_t col;
    const int32_t error_id;
private:
};

EF_NAMESPACE_END

#endif // _EFEXCEPTION_H_2011_11_30_lisency

