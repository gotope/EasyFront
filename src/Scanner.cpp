/*-------------------------------------------------------------------
 * Purpose:
 *         Scanner.cpp
 * Time:
 *         2011��12��1�� 17:49:40
 * Author:
 *         ������
--------------------------------------------------------------------*/

#include "Scanner.h"
#include "Exception.h"

EF_NAMESPACE_BEGIN

static const ChFlags ERRORCH = (ChFlags) 0;         //�����ַ�
static const ChFlags NEEDNEXTCH = (ChFlags) 1;      //����һ�ַ������ж�
static const ChFlags READEND = (ChFlags) 2;         //�ļ�����
static const ChFlags ANNOTATION = (ChFlags) 3;      //ע��
static const ChFlags NEXTLINE = (ChFlags) 4;        //����
static const ChFlags IDENTIFIERSTART = (ChFlags) 5; //�����ǹؼ��ֵĿ�ͷ��[a-zA-Z_]
static const ChFlags IDENTIFIER = (ChFlags) 6;      //�Ǹ��ؼ���
static const ChFlags INVOKEDOT = (ChFlags) 7;       //�������÷�
static const ChFlags DIGIT = (ChFlags) 8;           //����[0-9]
static const ChFlags STRINGFLAG = (ChFlags) 9;      //�ַ���
static const ChFlags BACKSLASHFLAG = (ChFlags) 10;  //��б��
static const ChFlags PUNCTATION = (ChFlags) 11;     //���

/**
 * �ʷ�������
 */
Scanner::Scanner(Reader &reader)
    :reader(reader),
    row(1),//��ʼ�к�Ϊ1
    col(0),//��ʼ�к�Ϊ0
    indent_index(0),
    pendin(0)
{
    //����ջȫ����ʼ��Ϊ1
    for (int i = 0;i < MAXINDENTSIZE;i++)
    {
        indent_stack[i] = 1;
    }
    return;
}
/**
 * do nothing
 */
Scanner::~Scanner()
{
    return;
}
/**
 * ��һ����
 */
Token* Scanner::nextToken()
{
    ch = nextch();

    buffer.clear();
spaces:
    procspaces();    //����հ�
    if (READ_END == ch)
    {//������ĩβ
        buffer.clear();
        return new_token(ENDMARKER);
    }

    //pendinʼ�ջᱻƽ�⵽0��Ҳ����˵��Ϊ-1ʱ����ʾdedent
    //����if�������������ص���0���´��ֽ�����
    if (0 != pendin)
    {//����,û��Ϊ��������ӿڣ�Ҳ��֪�����������ط��ò�
        if (0 > pendin)
        {
            pendin ++;
            buffer.clear();
            return new_token(DEDENT);
        }else
        {
            pendin --;
            buffer.clear();
            return new_token(INDENT);
        }
    }

    if (isannotation(ch) == true)
    {//��ע��
        procannotation();//ע���е����в�����NEWLINE
        goto spaces;    //���´���հ�
    }
    //Linux������
    if (0x0D == ch)
    {
        ch = nextch();

        if (0x0A == ch)
        {
            increaserow();        //�����к�
            procnewline();

            buffer.clear();
            return new_token(NEWLINE);
        }
        //��������ڣ�ֻ�Ǽ򵥵��Թ�
    }
    //windows������
    else if ('\n' == ch)
    {
        increaserow();        //�����к�
        procnewline();

        buffer.clear();
        return new_token(NEWLINE);
    }

    //��ȡ��ؼ���֮��û�м��ո�������ǰ���ǵĲ�ͬ
    //���ؼ������������ִ�������ķ���������
    if (isidentifierstart(ch) == true)
    {//�ǹؼ���
        while (isidentifier(ch) == true)
        {
            backupch(ch);
            ch = nextch();
        }
        //��֤����һ���ؼ��֣����䷵��
        //�����һ�����ǹؼ��ֵ��ַ��洢
        back_look_char.push_back(ch);
        return proc_keyword();
    }
    if ('.' == ch)
    {//�ж��Ƿ��Ǻ������÷���
        ch = nextch();
        if (isdigit(ch) == true)
        {
            buffer.clear();
            backupch(ch);
            for (;isdigit(ch) == true;backupch(ch))
            {
                ch = nextch();
            }
            //�����һ���������ֵ��ַ��洢
            back_look_char.push_back(ch);
            return new_token(NUMBER);
        }
        else
        {//���������֣���ô�����Ǻ������÷�
            back_look_char.push_back(ch);
            return new Token(DOT,".",row,get_prev_col());
        }
    }
    if (isdigit(ch) == true)
    {//������,Ŀǰֻ֧��10����,��֧��ָ��,��������������
        bool dot_have = false;//ֻ������һ�����

        buffer.clear();

        while (isdigit(ch) == true)
        {
            backupch(ch);
            ch = nextch();
            if ('.' == ch)
            {//�ǵ��
                if (dot_have == true)
                {
                    EFExc exc(get_path(),row,col,ERROR_ERRORTOKEN);
                    throw exc;
                }
                dot_have = true;
                backupch(ch);
                ch = nextch();
                if (isdigit(ch) == false)
                {//��ź��治�����֣��ǾͿ϶���ƴд����
                    EFExc exc(get_path(),row,col,ERROR_ERRORTOKEN);
                    throw exc;
                }
            }
        }
        //��Ϊ���һ���ַ��պò������֣��������������������
        back_look_char.push_back(ch);
        return new_token(NUMBER);
    }
    if (isstringstart(ch) == true)
    {//���ַ���,�������Ż�˫���ſ�ͷ
        buffer.clear();
        int32_t start_ch = ch;
        //������������հɡ�����׳����쳣����û����գ��Ǿ������
        bool has_escape_ch = false;
        //��has_escape_chΪ��ʱ�����жϸ��ַ��Ƿ���"
        while (1)
        {//���ҵ�����һ��"��������ѭ��
            has_escape_ch = false;
            ch = nextch();
            if ('\n' == ch || READ_END == ch || 0x0d == ch)
            {//��β����ȷ
                EFExc exc(get_path(),row,col,ERROR_ERRORTOKEN);
                throw exc;
            }
            if ('\\' == ch)
            {//Ҫ�����Ƿ����ת���,������ǰ��һ���ַ�
                has_escape_ch = true;
                ch = nextch();
            }
            //�ҵ�����һ��������־��������ѭ��
            if (start_ch == ch)
            {
                if (has_escape_ch == false)
                {
                    break;
                }
            }
            backupch(ch);
        }
        return new_token(STRING);
    }
    //�����ţ����ڸ�������⣬����������ȡ�
    //���ò�����
    //�Զ���ַ�������������
    buffer.clear();
    backupch(ch);
    char ch2 = nextch();
    char ch3 = nextch();
    //��ʼ���������ַ��Ĳ����� 
    TokenFlag token_flag;
    token_flag = procthreechars(ch,ch2,ch3);

    //�����Ϊ�գ�˵��ƥ��ɹ�
    if (token_flag != EMPTY)
    {
        backupch(ch2);
        backupch(ch3);

        return new_token(token_flag);
    }

    token_flag = proctwochars(ch,ch2);

    if (token_flag != EMPTY)
    {
        backupch(ch2);
        back_look_char.push_back(ch3);//�����µ�һ���ַ�����
        return new_token(token_flag);
    }
    //�������ʣ��һ�����ŵ���

    token_flag = proconechars(ch);
    if (token_flag == ERRORTOKEN)
    {
        EFExc exc(get_path(),row,col,ERROR_ERRORTOKEN);
        throw exc;
    }
    back_look_char.push_back(ch2);
    back_look_char.push_back(ch3);
    return new_token(token_flag);
}
/**
 * �ǲ��ǹؼ�����ʼ��־
 */
bool Scanner::isidentifierstart(int32_t ch)
{
    if ((ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z')
        || (ch == '_')
        )
    {//�ؼ���[a-zA-Z_]
        return true;
    }
    return false;
}
/**
 * �ǹؼ���
 */
bool Scanner::isidentifier(int32_t ch)
{
    if ((ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z')
        || (ch >= '0' && ch <= '9')
        || (ch == '_')
        )
    {//�ؼ���[a-zA-Z0-9_]
        return true;
    }
    return false;
}
/**
 * ������
 */
bool Scanner::isdigit(int32_t ch)
{
    if ('0' <= ch && '9' >= ch)
    {
        return true;
    }
    return false;
}
/**
 * ���ַ���
 */
bool Scanner::isstringstart(int32_t ch)
{
    if ('"' == ch)
    {
        return true;
    }
    return false;
}
/**
 * 
 */
int32_t Scanner::procspaces()
{
    return 0;
}
/**
 * 
 */
int32_t Scanner::procindent()
{
    return 0;
}
/**
 * 
 */
void Scanner::procnewline()
{
    return;
}
/**
 * 
 */
TokenFlag Scanner::proconechars(int32_t c1)
{
    switch (c1) 
    {
    case '(':            return LPAR;
    case ')':            return RPAR;
    case '[':            return LSQB;
    case ']':            return RSQB;
    case ':':            return COLON;
    case ',':            return COMMA;
    case ';':            return SEMI;
    case '+':            return PLUS;
    case '-':            return MINUS;
    case '*':            return STAR;
    case '/':            return SLASH;
    case '|':            return VBAR;
    case '&':            return AMPER;
    case '<':            return LESS;
    case '>':            return GREATER;
    case '=':            return EQUAL;
    case '.':            return DOT;
    case '%':            return PERCENT;
    case '{':            return LBRACE;
    case '}':            return RBRACE;
    case '^':            return CIRCUMFLEX;
    case '~':            return TILDE;
    default:            return ERRORTOKEN;
    }
}
/**
 * 
 */
TokenFlag Scanner::proctwochars(int32_t c1,int32_t c2)
{
    switch (c1)
    {
    case '=':
        switch (c2)
        {
        case '=':               return EQEQUAL;
        }
        break;
    case '!':
        switch (c2)
        {
        case '=':               return NOTEQUAL;
        }
        break;
    case '<':
        switch (c2)
        {
        case '>':               return NOTEQUAL;
        case '=':               return LESSEQUAL;
        case '<':               return LEFTSHIFT;
        }
        break;
    case '>':
        switch (c2)
        {
        case '=':               return GREATEREQUAL;
        case '>':               return RIGHTSHIFT;
        }
        break;
    case '+':
        switch (c2)
        {
        case '=':               return PLUSEQUAL;
        }
        break;
    case '-':
        switch (c2)
        {
        case '=':               return MINEQUAL;
        case '>':               return RARROW;
        }
        break;
    case '*':
        switch (c2)
        {
        case '*':               return DOUBLESTAR;
        case '=':               return STAREQUAL;
        }
        break;
    case '/':
        switch (c2)
        {
        case '/':               return DOUBLESLASH;
        case '=':               return SLASHEQUAL;
        }
        break;
    case '|':
        switch (c2)
        {
        case '=':               return VBAREQUAL;
        }
        break;
    case '%':
        switch (c2)
        {
        case '=':               return PERCENTEQUAL;
        }
        break;
    case '&':
        switch (c2)
        {
        case '=':               return AMPEREQUAL;
        }
        break;
    case '^':
        switch (c2)
        {
        case '=':               return CIRCUMFLEXEQUAL;
        }
        break;
    }
    return EMPTY;
}
/**
 *  �����������ַ���ɵĴ���
 */
TokenFlag Scanner::procthreechars(int32_t c1,int32_t c2,int32_t c3)
{
    switch (c1)
    {
    case '<':
        switch (c2)
        {
        case '<':
            switch (c3)
            {
            case '=':
                return LEFTSHIFTEQUAL;
            }
            break;
        }
        break;
    case '>':
        switch (c2)
        {
        case '>':
            switch (c3)
            {
            case '=':
                return RIGHTSHIFTEQUAL;
            }
            break;
        }
        break;
    case '*':
        switch (c2)
        {
        case '*':
            switch (c3)
            {
            case '=':
                return DOUBLESTAREQUAL;
            }
            break;
        }
        break;
    case '/':
        switch (c2)
        {
        case '/':
            switch (c3)
            {
            case '=':
                return DOUBLESLASHEQUAL;
            }
            break;
        }
        break;
    case '.':
        switch (c2)
        {
        case '.':
            switch (c3)
            {
            case '.':
                return ELLIPSIS;
            }
            break;
        }
        break;
    }
    return EMPTY;
}
/**
 * Ĭ��ʵ�ַ��ؼ�
 */
bool Scanner::isannotation(int32_t ch)
{
    return false;
}
/**
 * ����ע��
 */
void Scanner::procannotation()
{
    return;
}
/**
 * �õ�������һ�㲻��
 */
int32_t Scanner::getpendin()
{
    return pendin;
}
/**
 * 
 */
Token* Scanner::proc_keyword()
{
    return NULL;
}

//begin regex scanner
RegScanner::RegScanner(Reader &reader)
    :Scanner(reader)
{
    return;
}
/**
 * 
 */
RegScanner::~RegScanner()
{
    return;
}
/*bool RegScanner::isidentifierstart(int32_t ch)
{
    return false;
}
bool RegScanner::isidentifier(int32_t ch)
{
    return false;
}*/
/**
 * �Ե����ſ�ͷ
 */
bool RegScanner::isstringstart(int32_t ch)
{
    if ('\'' == ch)
    {
        return true;
    }
    return false;
}
/**
 * �Ƿ��ǿհ׷�
 */
int32_t RegScanner::procspaces()
{
    while (1)
    {
        if (' ' == ch || '\t' == ch)
        {//�ո����һλ�Ѿ���nextch���������
            ch = nextch();
        }else
        {
            break;
        }
    }
    return 0;
}
/**
 * �����޹ؽ�Ҫ
 */
int32_t RegScanner::procindent()
{//do nothing,so don't warry about it
    return 0;
}
/**
 * ��������
 */
void RegScanner::procnewline()
{//do nothing
    return;
}
/*nt32_t RegScanner::proconechars(int32_t c1)
{
    return -1;
}
int32_t RegScanner::proctwochars(char c1,char c2)
{
    return -1
}
int32_t RegScanner::procthreechars(char c1,char c2,char c3)
{
    return -1;
}*/
/**
 * ע����#�ſ�ͷ
 */
bool RegScanner::isannotation(int32_t ch)
{
    if ('#' == ch)
    {
        return true;
    }
    return false;
}
/**
 * ����ע��,������ע��
 */
void RegScanner::procannotation()
{
    ch = nextch();
    while ('\n' != ch)
    {
        //��ע��ȫ�����˵�
    }
    increaserow();
    procannotation();//�ݹ齫������ע�Ͷ�ɾ��
    return;
}
/**
 * ����ؼ���,��ʱû�йؼ���
 */
Token* RegScanner::proc_keyword()
{
    return NULL;
}

//EF scanner begin
/**
 * ����reader
 */
EFScanner::EFScanner(Reader &reader)
    :Scanner(reader)
{
    return;
}
/**
 * do nothing 
 */
EFScanner::~EFScanner()
{
    return;
}
/**
 * �����Ż�˫����
 */
bool EFScanner::isstringstart( int32_t ch )
{
    if ('\'' == ch || '\"' == ch)
    {
        return true;
    }
    return false;
}
/**
 * ����հ�
 */
int32_t EFScanner::procspaces()
{
    if (1 == col)
    {//������,�õ�����ֵ
        while (1)
        {
            if (' ' == ch || 0x0b == ch || 0x0c == ch)
            {//�ո����һλ�Ѿ���nextch���������
            }else if ('\t' == ch)
            {
                int32_t tabsize = 4;
                col = (col/tabsize + 1) * tabsize;
            }else
            {
                break;
            }
            ch = nextch();
        }
    }else
    {
        while (' ' == ch || '\t' == ch
            || 0x0b == ch || 0x0c == ch)
        {//����ǿո��tab������
            ch = nextch();
        }
        return 1;
    }
    if ('#' == ch)
    {//���������Ϊע�Ͷ��˳��ģ���ôû��Ҫѹջ
        //procannotation();
        return 1;
    }
    /*��Linux����Ļ��з�*/
    if (0x0d == ch)
    {
        ch = nextch();
        if (ch == 0x0A)
        {
            increaserow();    //�����к�
            ch = nextch();
            procspaces();    //�ݹ����
            return 1;
        }
        //��û�а���0x0D 0x0A���˳����ô��0x0d�Թ��������Ժ��
    }
    /*��windows����*/
    if ('\n' == ch)
    {//�������Ϊ���У���˵���Ǹ�����
        increaserow();    //�����к�
        ch = nextch();
        //��������õ�����һ���ǿհ��ַ�����ô��һ�ε��ã�ֱ�ӻ�
        //�����������������ٴδӸú����г�����ʱ�򣬾Ͳ����ٵ�����
        //���������if���ĺ���ֱ��return
        procspaces();    //�ݹ����
        return 1;
    }
    //�ȵ��ݹ�������֮�������������Ƿǿհ��ַ��������������
    //���ַ����ܶ�ʧ�����Դ洢����
    int32_t t_pendin = procindent();    //��������

    if (t_pendin == 1 || pendin != 0)
    {
        back_look_char.push_back(ch);
    }
    return 1;
}
/**
 * ��������
 * ������ǽ�����ֵѹ��������
 */
int32_t EFScanner::procindent()
{
    //ջ�ĵ�һ��Ԫ��δʹ��
    int32_t t_col = get_prev_col();

    if (t_col == indent_stack[indent_index])
    {//����û�б�
        return 0;
    }
    else if (t_col > indent_stack[indent_index])
    {//indent
        if (indent_index + 1 >= MAXINDENTSIZE)
        {
            EFExc exc(get_path(),row,t_col,ERROR_ERRORTOKEN);
            throw exc;
        }
        indent_index ++;
        pendin ++;
        indent_stack[indent_index] = t_col;
    }
    else
    {
        while (indent_index > 0
            && t_col < indent_stack[indent_index])
        {
            indent_index --;
            pendin --;
        }
    }
    return 1;
}
/**
 * ��������
 */
void EFScanner::procnewline()
{
    //procspaces();
    //procindent();
    return;
}
/**
 * �Ƿ���ע��
 */
bool EFScanner::isannotation(int32_t ch)
{
    if ('#' == ch)
    {//#�ſ�ͷ�Ժ���ַ���Ϊע��
        return true;
    }
    return false;
}
/**
 * ����ע��
 */
void EFScanner::procannotation()
{
    if (isannotation(ch) == false)
    {
        return;
    }
    while ('\n' != ch)
    {
        ch = nextch();
        //��ע��ȫ�����˵�
    }
    /*
    increaserow();
    ch = nextch();

    procannotation();//�ݹ齫������ע�Ͷ�ɾ��
    */
    return;
}
/**
 * ����ؼ��ִ��ز�����
 */
Token* EFScanner::proc_keyword()
{
    Token* token = NULL;

    int col = this->col - buffer.size();
    if (buffer == "if")
    {
        token = new Token(IF_MARKER,"if",row,col);
    }
    else if (buffer == "elif")
    {
        token = new Token(ELIF_MARKER,"elif",row,col);
    }
    else if (buffer == "else")
    {
        token = new Token(ELSE_MARKER,"else",row,col);
    }
    else if (buffer == "while")
    {
        token = new Token(WHILE_MARKER,"while",row,col);
    }
    else if (buffer == "for")
    {
        token = new Token(FOR_MARKER,"for",row,col);
    }
    else if (buffer == "in")
    {
        token = new Token(IN_MARKER,"in",row,col);
    }
    else if (buffer == "try")
    {
        token = new Token(TRY_MARKER,"try",row,col);
    }
    else if (buffer == "finally")
    {
        token = new Token(FINALLY_MARKER,"finally",row,col);
    }
    else if (buffer == "catch")
    {
        token = new Token(CATCH_MARKER,"catch",row,col);
    }
    else if (buffer == "fun")
    {
        token = new Token(FUN_MARKER,"fun",row,col);
    }
    else if (buffer == "class")
    {
        token = new Token(CLASS_MARKER,"class",row,col);
    }
    else if (buffer == "del")
    {
        token = new Token(DEL_MARKER,"del",row,col);
    }
    else if (buffer == "import")
    {
        token = new Token(IMPORT_MARKER,"import",row,col);
    }
    else if (buffer == "null")
    {
        token = new Token(NULL_MARKER,"null",row,col);
    }
    else if (buffer == "true")
    {
        token = new Token(TRUE_MARKER,"true",row,col);
    }
    else if (buffer == "false")
    {
        token = new Token(FALSE_MARKER,"false",row,col);
    }
    else if (buffer == "lambda")
    {
        token = new Token(LAMBDA_MARKER,"lambda",row,col);
    }
    else if (buffer == "not")
    {
        token = new Token(NOT_MARKER,"not",row,col);
    }
    else if (buffer == "or")
    {
        token = new Token(OR_MARKER,"or",row,col);
    }
    else if (buffer == "and")
    {
        token = new Token(AND_MARKER,"and",row,col);
    }
    else
    {
        token = new Token(NAME,buffer,row,col);
    }
    buffer.clear();//���������ǾͰ��������

    return token;
}

EF_NAMESPACE_END

