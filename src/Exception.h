/*-------------------------------------------------------------------
 * Purpose:
 *         �����쳣�����
 * Time:
 *         2011��11��30�� 15:32:56
 * Author:
 *         ������
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
 *  ��������࣬�����Ա�ʵ����
 * NOTE!��Ȼ�ǻ��࣬���м̳й�ϵ�����ʹ������ʹ��
 **/
class EFExc
    : public Base
{
public:
    /**
    *  �쳣��Ĺ��캯���������Ҵ������������
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
    *  �쳣�಻������������ʱ���׳��쳣
    **/
    virtual ~EFExc() throw()
    {
    }
    /**
    *  û�з���std::string��Ϊ�����׼exceptionһ��
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
     * �õ���������
     */
    const char* get_message(int32_t error_id) const
    {
        switch (error_id)
        {
        case ERROR_FILE_READFAILD:
            return "�ļ���ʧ��";
        case ERROR_FILE_END_NOFORMOR:
            return "�ļ��ļ��Է�������־����";
        case ERROR_NO_NEWLINE:
            return "δƥ�䵽���з�";
        case ERROR_REDUNDANT_EQUAL:
            return "δʹ�õȺ�";
        case ERROR_KEY_MARKER:
            return "��ʶ������Ƿ��ַ�";
        case ERROR_STMT_END_NOFORMOR:
            return "������������";
        case ERROR_NO_USE_WORD:
            return "δʹ�÷���";
        case ERROR_STACK_OVER_FLOW:
            return "ջ���";
        case ERROR_ERRORTOKEN:
            return "�������";
        case ERROR_NO_RPAR:
            return "δƥ�䵽������";
        case ERROR_NO_SUITE:
            return "δʶ��suite";
        case ERROR_NO_MEMORY:
            return "�ڴ����ʧ��";
        case ERROR_STMT_EMPTY:
            return "stmt���ƥ��ʧ��";
        case ERROR_NO_FOUND_SYMBOL:
            return "û���ҵ�����";
        case ERROR_NO_BINOP:
            return "����ʱ�̶�Ԫ������û���ҵ�";
        case ERROR_NO_NUMBER:
            return "ʵ�ͻ����Ͳ���δ�ҵ�";
        case ERROR_NO_STRING:
            return " û���ҵ��ַ�����������";
        case ERROR_NO_OBJECT:
            return "û���ҵ��ֽ������";
        case ERROR_WRONG_TYPE:
            return "Ԫ�����Ͳ�ͬ";
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

