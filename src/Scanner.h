/*-------------------------------------------------------------------
 * Purpose:
 *         Scanner.h �ִ�
 * Time:
 *         2011��12��1�� 18:15:36
 * Author:
 *         ������
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
 * �ִ�������������ײ��ܵ���Щ�඼�����˽ӿ�
 **/
class Scanner
    :public Base
{
public:
    /**
    * ���캯��
    **/
    Scanner(Reader &reader);
    /**
    * ����
    **/
    virtual ~Scanner() = 0;
    /**
    * ��ȡ��һ�ַ���
    * 
    * the token have read,���ļ�ĩβ����NULL
    * Ԥ������1,���������з�
    *         2,������������������
    *         3,�ַ���û�д���'�����,ֻ��"
    *         4,�һ�������֧��UTF8��������GBK����˵
    **/
    virtual Token* nextToken();
    /**
    *�õ�����  //notation anded [2/17/2012 ������] 
    **/
    int32_t getpendin();
    /**
    *�õ���ǰ�ʷ���������·��
    **/
    virtual std::string get_path() const
    {
        return reader.get_path();
    }
protected:
    static const int32_t MAXINDENTSIZE = 30;
    //�������ֵ
    Reader &reader;

    int32_t ch;             //��ǰ������ַ�
    int32_t row;           //ά���к�
    int32_t col;           //ά���к�
    std::string buffer;     //����
    int32_t indent_stack[MAXINDENTSIZE];
    int32_t indent_index;   //��ջ������ֵ
    int32_t pendin;         //�ɴ˵������뷴����
    std::deque<char> back_look_char;
    //�����������������๲���

    /**
    * �鿴�Ƿ��ǹؼ��ֿ�ʼ�ַ�
    * @ch Ҫ��֤���ַ�
    * ��Ϊ�棬��Ϊ��
    **/
    virtual bool isidentifierstart(int32_t ch);
    /**
    * ��֤�Ƿ��ǹؼ���
    *  @ch Ҫ��֤���ַ�
    * EF_NAMESPACE_BEGIN��Ϊtrue��Ϊfalse
    **/
    virtual bool isidentifier(int32_t ch);
    /**
    * �ж��Ƿ������֣���ʵ������ʹ����ܼ̳�
    *                Ҳû�ж�������
    *  @ch Ҫ�жϵ��ַ�
    * ��Ϊtrue��Ϊfalse
    **/
    virtual bool isdigit(int32_t ch);
    /**
    * ��֤�Ƿ����ַ�����ʼ��־����' "
    *  @ch Ҫ��֤���ַ�
    *��Ϊtrue��Ϊfalse
    **/
    virtual bool isstringstart(int32_t ch);
    /**
    * ����հף�����tab
    **/
    virtual int32_t procspaces();
    /**
    * ��������
    **/
    virtual int32_t procindent();
    /**
    * ��������
    **/
    virtual void procnewline();
    /**
    * ��һ���ַ������������
    *  @c1 ��һ���ַ�
    * ������Token.h�еĳ�����
    **/
    virtual TokenFlag proconechars(int32_t c1);
    /**
    * �������ַ������������
    * @c1 ��һ���ַ�
    * @c2 �ڶ����ַ�
    * ������Token.h�еĳ�����
    **/
    virtual TokenFlag proctwochars(int32_t c1,int32_t c2);
    /**
    * �������ַ������������
    * @c1 ��һ���ַ�
    * @c2 �ڶ����ַ�
    * @c3 �������ַ�
    * ������Token.h�еĳ�����
    **/
    virtual TokenFlag procthreechars(int32_t c1,int32_t c2,int32_t c3);
    /**
    * �ж��Ƿ���ע��,������ע�͵Ŀ�ͷ
    * ����ǣ���ô����ע�ʹ�����
    * @ch Ҫ�жϵ��ַ�
    **/
    virtual bool isannotation(int32_t ch);
    /**
    * ����ע��
    **/
    virtual void procannotation();
    /**
    * �����к�
    **/
    inline void increaserow()
    {
        row++;    //�кŵ���
        col = 0;    //�к���Ϊ��ʼֵ
        return;
    }
    /**
    * ����ؼ���
    * @ch ������ַ�
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
    * �õ���һ�ַ�,�������к�
    * ���صõ����ַ�
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
            //���ض��׵�ֵ���Ҳ����к�
            ch = back_look_char.front();
            back_look_char.pop_front();
        }

        return ch;
    }
    /**
     * ����Ԥ����buffer������ֵ����token
     */
    inline Token* new_token(TokenFlag token_flag)
    {
        return new Token(token_flag,buffer,row,get_prev_col());
    }
    /**
     * ����ؼ���
     */
    virtual Token* proc_keyword();
    /**
     * �õ���һ���ط��غ�����ʼ�к�
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
 * ������grammrinit.h��grammarinit.cpp��ʱ����õ�
 * �����ѷ�������
 * ���������Ҫ���������ʱ��˵��������
 **/
class RegScanner
    :public Scanner
{
public:
    /**
    * ������ֱ�Ӵ������࣬�Լ�������
    *  @reader ��ȡ���ݣ������ļ��еģ�����Stdin
    **/
    RegScanner(Reader &reader);
    /**
    * I'm do nothing at here
    **/
    virtual ~RegScanner();
protected:
    /**
    * �����Լ���չ
    * 
    * EF_NAMESPACE_BEGIN
    **/
    //virtual bool isidentifierstart(int32_t ch);
    /**
    * �ж��Ƿ��ǹؼ��֣������Լ���չ
    **/
    //virtual bool isidentifier(int32_t ch);
    /**
    * �Ա�������ʽ�Ĺ����е����Ű�Χ�����ַ���
    *  @ch Ҫ��֤���ַ�
    * ��Ϊtrue��Ϊfalse
    **/
    virtual bool isstringstart(int32_t ch);
    /**
    * ��������ʽ�Ĵ�����ֻҪ���ո��tabɾ������
    * �������հ�ʱ����ǰ����һλ�ַ������Ҹպ�Ҫ����
    * indent��dedent���������ĳ���û��ʲôӰ�죬����
    * �����������ǰһ����������ͬ��ƫ�ƣ���ô��һ����ǰ
    * ���ַ��Ʊػ�Ӱ�����Ǻ���ĳ���Ϊ�ˣ�����һ����
    * ־���Ƿ���Ԥ���ַ�
    **/
    virtual int32_t procspaces();
    /**
    * ������û��Ҫ��ȫ����ɾ��
    **/
    virtual int32_t procindent();
    /**
    * RegScanner�������в����ϸ�
    **/
    virtual void procnewline();
    /**
    * ��һ���ַ������������
    *                ������ʽ�������ַ���[]{}|^$?����������չ
    * @c1 ��һ���ַ�
    *������Token.h�еĳ�����
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
    * �ж��Ƿ���ע��,������ע�͵Ŀ�ͷ
    *                ����ǣ���ô����ע�ʹ�����
    *  @ch Ҫ�жϵ��ַ�
    **/
    virtual bool isannotation(int32_t ch);
    /**
    * ����ע��
    *�ݽ�ע�Ͷ�Ϊ#����ȫ���Ը���
    **/
    virtual void procannotation();
    /**
     * ����ؼ���
     */
    virtual Token* proc_keyword();
private:
};
/**
 * ����ִ���
 **/
class EFScanner
    :public Scanner
{
public:
    /**
    * ͬ�������������������
    *  @reader ��ȡ������
    **/
    EFScanner(Reader &reader);
    /**
    * has none special
    **/
    virtual ~EFScanner();
protected:
    /**
    * [a-zA-Z_]ʹ��ʡȱ����
    * @ch Ҫ��֤���ַ�
    * ��Ϊ�棬��Ϊ��
    **/
    //virtual bool isidentifierstart(int32_t ch);
    /**
    * [a-zA-Z0-9_]ʹ��ʡȱ����
    * @ch Ҫ��֤���ַ�
    * ��Ϊtrue��Ϊfalse
    **/
    //virtual bool isidentifier(int32_t ch);
    /**
    * ��֤�Ƿ����ַ�����ʼ��־����' "
    ������������п�����չ��һ���������Ժ��п��ܻ�����չ
    * @ch Ҫ��֤���ַ�
    * ��Ϊtrue��Ϊfalse
    **/
    virtual bool isstringstart(int32_t ch);
    /**
    * ����հף�����tab
    **/
    virtual int32_t procspaces();
    /**
    * ������������Ҫ����ϸ���Щ��������Ӱ�죺
    * ���е�����������tab����ʼ��������ո�
    **/
    virtual int32_t procindent();
    /**
    * �Ա�������˵���������У���������Ҫ
    **/
    virtual void procnewline();
    /**
    * ��һ���ַ������������,ʹ��ʡȱ����
    * @c1 ��һ���ַ�
    * ������Token.h�еĳ�����
    **/
    //virtual TokenFlag proconechars(int32_t c1);
    /**
    * ʹ��ʡȱ��������ʱû��Ҫ��չ
    **/
    //virtual TokenFlag proctwochars(int32_t c1,int32_t c2);
    /**
    *  ʹ��ʡȱ����
    **/
    //virtual TokenFlag procthreechars(int32_t c1,int32_t c2,int32_t c3);
    /**
    * ������ע����#�ſ�ͷ��û�ж���ע��
    * ���Դ���������Լ�
    * @ch Ҫ�жϵ��ַ�
    * ������ַ���ע�͵ı�־�������棬��Ϊ��
    **/
    virtual bool isannotation(int32_t ch);
    /**
    * ����ע��
    **/
    virtual void procannotation();
    /**
     * ����ؼ���
     */
    virtual Token* proc_keyword();
private:
};

EF_NAMESPACE_END

#endif // _SCANNER_H_2011_12_1_lisency

