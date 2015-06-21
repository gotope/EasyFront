/*-------------------------------------------------------------------
 * Purpose:
 *         Token.h , this file include nonterminal symbol of predefined
 * Time:
 *         2011��11��13�� 11:50:55
 * Author:
 *         ������
--------------------------------------------------------------------*/

#ifndef _TOKEN_H_2011_11_13_lisency
#define _TOKEN_H_2011_11_13_lisency

#include <string>
#include <stdint.h>
#include <ostream>
#include <iomanip>

#include "Util.h"

EF_NAMESPACE_BEGIN

/* Special definitions for cooperation with parser */

enum TokenFlag{
    ENDMARKER          =    0,    //������־
    IF_MARKER          =    1,    //if
    ELIF_MARKER        =    2,    //elif
    WHILE_MARKER       =    3,    //while
    FOR_MARKER         =    4,    //for
    IN_MARKER          =    5,    //in
    TRY_MARKER         =    6,    //try
    FINALLY_MARKER     =    7,    //finally
    CATCH_MARKER       =    8,    //catch
    FUN_MARKER         =    9,    //fun
    CLASS_MARKER       =    10,    //class
    DEL_MARKER         =    11,    //del
    IMPORT_MARKER      =    12,    //import
    NULL_MARKER        =    13,    //null
    TRUE_MARKER        =    14,    //true
    FALSE_MARKER       =    15,   //false
    LAMBDA_MARKER      =    16,   //lambda���ʽ
    NOT_MARKER         =    17,   //not
    OR_MARKER          =    18,   //or
    AND_MARKER         =    19,   //and
    NAME               =    20,   //����
    NUMBER             =    21,   //����
    STRING             =    22,   //�ַ���
    NEWLINE            =    23,   //���з�
    INDENT             =    24,   //������
    DEDENT             =    25,   //������
    LPAR               =    26,   //��Բ����
    RPAR               =    27,   //��Բ����
    LSQB               =    28,   //������
    RSQB               =    29,   //�ҷ�����
                                  //30����
    COLON              =    31,   //ð��
    COMMA              =    32,   //����
    SEMI               =    33,   //�ֺ�;
    PLUS               =    34,   //�Ӻ�
    MINUS              =    35,   //����
    STAR               =    36,   //�˺ţ��Ǻ�
    SLASH              =    37,   //б�� /
    VBAR               =    38,   // |
    AMPER              =    39,   // &
    LESS               =    30,   //С�ڣ�<
    GREATER            =    41,   //���ڣ�>
    EQUAL              =    42,   //���ڣ�=
    DOT                =    43,   //�� .
    PERCENT            =    44,   //�ٷֺ� %
    BACKQUOTE          =    45,   //�ڶ�������
    LBRACE             =    46,   //�������
    RBRACE             =    47,   //�Ҽ�����
    EQEQUAL            =    48,   //==
    NOTEQUAL           =    49,   //!=
    LESSEQUAL          =    40,   //<=
    GREATEREQUAL       =    51,   //>=
    TILDE              =    52,   //~���˺�
    CIRCUMFLEX         =    53,   //���
    LEFTSHIFT          =    54,   //<<
    RIGHTSHIFT         =    55,   //>>
    DOUBLESTAR         =    56,   //**
    PLUSEQUAL          =    57,   //+=
    MINEQUAL           =    58,   //-=
    STAREQUAL          =    59,   //*=
    SLASHEQUAL         =    50,   ///=
    PERCENTEQUAL       =    61,   //%=
    AMPEREQUAL         =    62,   //&=
    VBAREQUAL          =    63,   //|=
    CIRCUMFLEXEQUAL    =    64,   //^=
    LEFTSHIFTEQUAL     =    65,   //<<=
    RIGHTSHIFTEQUAL    =    66,   //>>=
    DOUBLESTAREQUAL    =    67,   //**=
    DOUBLESLASH        =    68,   // //
    DOUBLESLASHEQUAL   =    69,   // //=
    AT                 =    60,   //@
    RARROW             =    71,   //#
    ELLIPSIS           =    72,   //...ʡ�Է�
    OP                 =    73,   //�ȽϷ�
    ERRORTOKEN         =    74,   //�����־
    EMPTY              =    75,   //��
    ELSE_MARKER        =    76,   //else,I am forget
};

#define N_TOKENS        76    // ����

static const short TERMINAL_SIZE = 100;    //�ս���ŵĸ���

#define NT_OFFSET        256

#define ISTERMINAL(x)        ((x) < NT_OFFSET)
#define ISNONTERMINAL(x)    ((x) >= NT_OFFSET)

/**
 * ��ÿ�����ص����ͼ�λ����Ϣ
 **/
class Token 
{
public:
    TokenFlag id;        //ÿ��token��id
    std::string str;    //��token������
    int32_t row;        //�к�
    int32_t col;        //��ʼ�к�

public:
    Token(TokenFlag t_id,std::string t_str,
        int32_t t_row,int32_t t_col)
        :id(t_id),
        str(t_str),
        row(t_row),
        col(t_col)
    {
        return;
    }
    /**
    * �ж�����token�Ƿ�Ϊ��ͬtoken
    **/
    bool operator ==(const Token &right)
    {
        if (id == right.id)
        {
            return true;
        }
        return false;
    }
#ifdef EF_DEBUG
    /**
     * ��ӡ
     */
    void print(std::ostream& cout)
    {
        const std::string flag_name = get_flag_name(id);

        cout << std::left << std::setw(20) << flag_name;
        cout << std::setw(20) << str ;
        cout << std::setw(5) << row << "\t";
        cout << col << std::endl;
        return;
    }
    /**
     * ͷ��
     */
    inline void print_head(std::ostream& cout)
    {
        cout << std::left << std::setw(20) << "TOKENFLAG"
            << std::setw(20) << "�ַ���"
            << std::setw(5) << "row\t"
            << "col"<< std::endl;
    }
    /**
     * �õ�tokenflag�����ƣ������ӡ
     */
    const std::string get_flag_name(TokenFlag token_flag)
    {
        switch (token_flag)
        {
        case ENDMARKER:          return "ENDMARKER";
        case IF_MARKER:          return "IF_MARKER";
        case ELIF_MARKER:        return "ELIF_MARKER";
        case WHILE_MARKER:       return "WHILE_MARKER";
        case FOR_MARKER:         return "FOR_MARKER";
        case IN_MARKER:          return "IN_MARKER";
        case TRY_MARKER:         return "TRY_MARKER";
        case FINALLY_MARKER:     return "FINALLY_MARKER";
        case CATCH_MARKER:       return "CATCH_MARKER";
        case FUN_MARKER:         return "FUN_MARKER";
        case CLASS_MARKER:       return "CLASS_MARKER";
        case DEL_MARKER:         return "DEL_MARKER";
        case IMPORT_MARKER:      return "IMPORT_MARKER";
        case NULL_MARKER:        return "NULL_MARKER";
        case TRUE_MARKER:        return "TRUE_MARKER";
        case FALSE_MARKER:       return "FALSE_MARKER";
        case LAMBDA_MARKER:      return "LAMBDA_MARKER";
        case NOT_MARKER:         return "NOT_MARKER";
        case OR_MARKER:          return "OR_MARKER";
        case AND_MARKER:         return "AND_MARKER";
        case NAME:               return "NAME";
        case NUMBER:             return "NUMBER";
        case STRING:             return "STRING";
        case NEWLINE:            return "NEWLINE";
        case INDENT:             return "INDENT";
        case DEDENT:             return "DEDENT";
        case LPAR:               return "LPAR";
        case RPAR:               return "RPAR";
        case LSQB:               return "LSQB";
        case RSQB:               return "RSQB";
        case COLON:              return "COLON";
        case COMMA:              return "COMMA";
        case SEMI:               return "SEMI";
        case PLUS:               return "PLUS";
        case MINUS:              return "MINUS";
        case STAR:               return "STAR";
        case SLASH:              return "SLASH";
        case VBAR:               return "VBAR";
        case AMPER:              return "AMPER";
        case LESS:               return "LESS";
        case GREATER:            return "GREATER";
        case EQUAL:              return "EQUAL";
        case DOT:                return "DOT";
        case PERCENT:            return "PERCENT";
        case BACKQUOTE:          return "BACKQUOTE";
        case LBRACE:             return "LBRACE";
        case RBRACE:             return "RBRACE";
        case EQEQUAL:            return "EQEQUAL";
        case NOTEQUAL:           return "NOTEQUAL";
        case LESSEQUAL:          return "LESSEQUAL";
        case GREATEREQUAL:       return "GREATEREQUAL";
        case TILDE:              return "TILDE";
        case CIRCUMFLEX:         return "CIRCUMFLEX";
        case LEFTSHIFT:          return "LEFTSHIFT";
        case RIGHTSHIFT:         return "RIGHTSHIFT";
        case DOUBLESTAR:         return "DOUBLESTAR";
        case PLUSEQUAL:          return "PLUSEQUAL";
        case MINEQUAL:           return "MINEQUAL";
        case STAREQUAL:          return "STAREQUAL";
        case SLASHEQUAL:         return "SLASHEQUAL";
        case PERCENTEQUAL:       return "PERCENTEQUAL";
        case AMPEREQUAL:         return "AMPEREQUAL";
        case VBAREQUAL:          return "VBAREQUAL";
        case CIRCUMFLEXEQUAL:    return "CIRCUMFLEXEQUAL";
        case LEFTSHIFTEQUAL:     return "LEFTSHIFTEQUAL";
        case RIGHTSHIFTEQUAL:    return "RIGHTSHIFTEQUAL";
        case DOUBLESTAREQUAL:    return "DOUBLESTAREQUAL";
        case DOUBLESLASH:        return "DOUBLESLASH";
        case DOUBLESLASHEQUAL:   return "DOUBLESLASHEQUAL";
        case AT:                 return "AT";
        case RARROW:             return "RARROW";
        case ELLIPSIS:           return "ELLIPSIS";
        case OP:                 return "OP";
        case ERRORTOKEN:         return "ERRORTOKEN";
        case EMPTY:              return "EMPTY";
        };

        return "";
    }
    #endif  //EF_DEBUG
};

enum ChFlags
{
    _dummy_val = 1,    //Don't ask
};
EF_NAMESPACE_END

#endif // _TOKEN_H_2011_11_13_lisency

