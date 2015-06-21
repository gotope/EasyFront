/*-------------------------------------------------------------------
 * Purpose:
 *         Scanner.cpp
 * Time:
 *         2011年12月1日 17:49:40
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "Scanner.h"
#include "Exception.h"

EF_NAMESPACE_BEGIN

static const ChFlags ERRORCH = (ChFlags) 0;         //错误字符
static const ChFlags NEEDNEXTCH = (ChFlags) 1;      //需下一字符才能判断
static const ChFlags READEND = (ChFlags) 2;         //文件结束
static const ChFlags ANNOTATION = (ChFlags) 3;      //注释
static const ChFlags NEXTLINE = (ChFlags) 4;        //新行
static const ChFlags IDENTIFIERSTART = (ChFlags) 5; //可能是关键字的开头符[a-zA-Z_]
static const ChFlags IDENTIFIER = (ChFlags) 6;      //是个关键字
static const ChFlags INVOKEDOT = (ChFlags) 7;       //函数调用符
static const ChFlags DIGIT = (ChFlags) 8;           //数字[0-9]
static const ChFlags STRINGFLAG = (ChFlags) 9;      //字符串
static const ChFlags BACKSLASHFLAG = (ChFlags) 10;  //反斜线
static const ChFlags PUNCTATION = (ChFlags) 11;     //标点

/**
 * 词法分析器
 */
Scanner::Scanner(Reader &reader)
    :reader(reader),
    row(1),//初始行号为1
    col(0),//初始列号为0
    indent_index(0),
    pendin(0)
{
    //缩进栈全部初始化为1
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
 * 下一词素
 */
Token* Scanner::nextToken()
{
    ch = nextch();

    buffer.clear();
spaces:
    procspaces();    //处理空白
    if (READ_END == ch)
    {//读到了末尾
        buffer.clear();
        return new_token(ENDMARKER);
    }

    //pendin始终会被平衡到0，也就是说当为-1时它表示dedent
    //进入if语句后又自增，回到了0，下次又接着用
    if (0 != pendin)
    {//缩进,没有为这个留个接口，也不知道会在其他地方用不
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
    {//是注释
        procannotation();//注释中的新行不返回NEWLINE
        goto spaces;    //重新处理空白
    }
    //Linux环境下
    if (0x0D == ch)
    {
        ch = nextch();

        if (0x0A == ch)
        {
            increaserow();        //递增行号
            procnewline();

            buffer.clear();
            return new_token(NEWLINE);
        }
        //如果不等于，只是简单的略过
    }
    //windows环境下
    else if ('\n' == ch)
    {
        increaserow();        //递增行号
        procnewline();

        buffer.clear();
        return new_token(NEWLINE);
    }

    //获取完关键字之后并没有检查空格，这与先前考虑的不同
    //将关键字相连的这种错误放在文法错误上面
    if (isidentifierstart(ch) == true)
    {//是关键字
        while (isidentifier(ch) == true)
        {
            backupch(ch);
            ch = nextch();
        }
        //验证这是一个关键字，将其返回
        //将最后一个不是关键字的字符存储
        back_look_char.push_back(ch);
        return proc_keyword();
    }
    if ('.' == ch)
    {//判断是否是函数调用符号
        ch = nextch();
        if (isdigit(ch) == true)
        {
            buffer.clear();
            backupch(ch);
            for (;isdigit(ch) == true;backupch(ch))
            {
                ch = nextch();
            }
            //将最后一个不是数字的字符存储
            back_look_char.push_back(ch);
            return new_token(NUMBER);
        }
        else
        {//若不是数字，那么它就是函数调用符
            back_look_char.push_back(ch);
            return new Token(DOT,".",row,get_prev_col());
        }
    }
    if (isdigit(ch) == true)
    {//是数字,目前只支持10进制,不支持指数,不允许有正负号
        bool dot_have = false;//只允许有一个点号

        buffer.clear();

        while (isdigit(ch) == true)
        {
            backupch(ch);
            ch = nextch();
            if ('.' == ch)
            {//是点号
                if (dot_have == true)
                {
                    EFExc exc(get_path(),row,col,ERROR_ERRORTOKEN);
                    throw exc;
                }
                dot_have = true;
                backupch(ch);
                ch = nextch();
                if (isdigit(ch) == false)
                {//点号后面不是数字，那就肯定是拼写错了
                    EFExc exc(get_path(),row,col,ERROR_ERRORTOKEN);
                    throw exc;
                }
            }
        }
        //因为最后一个字符刚好不是数字，所以我们样将其存起来
        back_look_char.push_back(ch);
        return new_token(NUMBER);
    }
    if (isstringstart(ch) == true)
    {//是字符串,即单引号或双引号开头
        buffer.clear();
        int32_t start_ch = ch;
        //还是在这里清空吧…如果抛出了异常，并没有清空，那就糟糕了
        bool has_escape_ch = false;
        //当has_escape_ch为真时不用判断该字符是否是"
        while (1)
        {//若找到了下一个"号则跳出循环
            has_escape_ch = false;
            ch = nextch();
            if ('\n' == ch || READ_END == ch || 0x0d == ch)
            {//结尾不正确
                EFExc exc(get_path(),row,col,ERROR_ERRORTOKEN);
                throw exc;
            }
            if ('\\' == ch)
            {//要考虑是否存在转义符,所以向前看一个字符
                has_escape_ch = true;
                ch = nextch();
            }
            //找到了下一个结束标志，并跳出循环
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
    //对括号，存在更多的问题，诸如作用域等…
    //不得不暂留
    //对多个字符操作符做处理
    buffer.clear();
    backupch(ch);
    char ch2 = nextch();
    char ch3 = nextch();
    //开始处理两个字符的操作符 
    TokenFlag token_flag;
    token_flag = procthreechars(ch,ch2,ch3);

    //如果不为空，说明匹配成功
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
        back_look_char.push_back(ch3);//将留下的一个字符保存
        return new_token(token_flag);
    }
    //到这里就剩下一个符号的了

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
 * 是不是关键字起始标志
 */
bool Scanner::isidentifierstart(int32_t ch)
{
    if ((ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z')
        || (ch == '_')
        )
    {//关键字[a-zA-Z_]
        return true;
    }
    return false;
}
/**
 * 是关键字
 */
bool Scanner::isidentifier(int32_t ch)
{
    if ((ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z')
        || (ch >= '0' && ch <= '9')
        || (ch == '_')
        )
    {//关键字[a-zA-Z0-9_]
        return true;
    }
    return false;
}
/**
 * 是数字
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
 * 是字符串
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
 *  处理由三个字符组成的词素
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
 * 默认实现返回假
 */
bool Scanner::isannotation(int32_t ch)
{
    return false;
}
/**
 * 处理注释
 */
void Scanner::procannotation()
{
    return;
}
/**
 * 得到缩进，一般不用
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
 * 以单引号开头
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
 * 是否是空白符
 */
int32_t RegScanner::procspaces()
{
    while (1)
    {
        if (' ' == ch || '\t' == ch)
        {//空格的这一位已经在nextch里面加上了
            ch = nextch();
        }else
        {
            break;
        }
    }
    return 0;
}
/**
 * 缩进无关紧要
 */
int32_t RegScanner::procindent()
{//do nothing,so don't warry about it
    return 0;
}
/**
 * 处理新行
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
 * 注释以#号开头
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
 * 处理注释,它是行注释
 */
void RegScanner::procannotation()
{
    ch = nextch();
    while ('\n' != ch)
    {
        //将注释全部过滤掉
    }
    increaserow();
    procannotation();//递归将所有行注释都删除
    return;
}
/**
 * 处理关键字,暂时没有关键字
 */
Token* RegScanner::proc_keyword()
{
    return NULL;
}

//EF scanner begin
/**
 * 传入reader
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
 * 单引号或双引号
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
 * 处理空白
 */
int32_t EFScanner::procspaces()
{
    if (1 == col)
    {//在行首,得到缩进值
        while (1)
        {
            if (' ' == ch || 0x0b == ch || 0x0c == ch)
            {//空格的这一位已经在nextch里面加上了
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
        {//如果是空格和tab则跳过
            ch = nextch();
        }
        return 1;
    }
    if ('#' == ch)
    {//如果是是因为注释而退出的，那么没必要压栈
        //procannotation();
        return 1;
    }
    /*在Linux下面的换行符*/
    if (0x0d == ch)
    {
        ch = nextch();
        if (ch == 0x0A)
        {
            increaserow();    //递增行号
            ch = nextch();
            procspaces();    //递归调用
            return 1;
        }
        //若没有按照0x0D 0x0A这个顺序，那么将0x0d略过，继续以后的
    }
    /*在windows下面*/
    if ('\n' == ch)
    {//如果是因为换行，则说明是个空行
        increaserow();    //递增行号
        ch = nextch();
        //假若这里得到的是一个非空白字符，那么下一次调用，直接会
        //到缩进处理函数，而再次从该函数中出来的时候，就不用再调用了
        //所以在这个if语句的后面直接return
        procspaces();    //递归调用
        return 1;
    }
    //等到递归调用完成之后，这里遇到的是非空白字符，对其计算缩进
    //该字符不能丢失，所以存储起来
    int32_t t_pendin = procindent();    //处理缩进

    if (t_pendin == 1 || pendin != 0)
    {
        back_look_char.push_back(ch);
    }
    return 1;
}
/**
 * 处理缩进
 * 最后我们将返回值压缩到这里
 */
int32_t EFScanner::procindent()
{
    //栈的第一个元素未使用
    int32_t t_col = get_prev_col();

    if (t_col == indent_stack[indent_index])
    {//缩进没有变
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
 * 处理新行
 */
void EFScanner::procnewline()
{
    //procspaces();
    //procindent();
    return;
}
/**
 * 是否是注释
 */
bool EFScanner::isannotation(int32_t ch)
{
    if ('#' == ch)
    {//#号开头以后的字符都为注释
        return true;
    }
    return false;
}
/**
 * 处理注释
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
        //将注释全部过滤掉
    }
    /*
    increaserow();
    ch = nextch();

    procannotation();//递归将所有行注释都删除
    */
    return;
}
/**
 * 构造关键字词素并返回
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
    buffer.clear();//用完了我们就把它清理掉

    return token;
}

EF_NAMESPACE_END

