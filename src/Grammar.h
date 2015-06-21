/*-------------------------------------------------------------------
 * Purpose:
 *         grammar.h ���������ķ�
 * Time:
 *         2011��11��20�� 19:59:32
 * Author:
 *         ������
--------------------------------------------------------------------*/

#ifndef _GRAMMAR_H_2011_11_20_lisency
#define _GRAMMAR_H_2011_11_20_lisency

#include <string>
#include <bitset>

EF_NAMESPACE_BEGIN

/**
 * description:    Label�����˴�״̬ת�Ƶ�����һ��״̬�������ı�����Ӧ�ķ��ţ�
 *                �����Ƿ��ս��(Non-Terminal)��Ҳ�������ս��(Terminal)��
 *                Labelһ��������һ�����߶����ߡ�
 * parameters:    @Lb_type    ������ŵ����ͣ����ս��NAME������һ����ʾ��������
 *                            ���ս��stmt������һ����䣬�ȵȡ�
 *                @Lb_str        ���������ŵ����ݡ����磬label (NAME, ��if��)
 *                            ��ʾ��parser����ĳ��״̬����������ˡ�if�������ʾ
 *                            �������ƶ�����һ��״̬��
 **/
typedef struct {
    int         lb_type;
    std::string lb_str;
} label;
/*
 */
#define EMPTY 0        //label��0״̬����Ϊһ�������״̬��������״̬

/**
 * description:    �����е�lable����
 * parameters:    @ll_nlables    lable������
 *                @ll_lable    ״̬���ϵ�����ͷָ��
 **/
typedef struct {
    int         ll_nlabels;
    label    *ll_label;
} labellist;

/**
 * description:    arc����DFA��һ��״̬����һ��״̬�Ļ�/��
 * parameters:    @A_lbl        arc����Ӧ��Label
 *                @a_arrow    arc��Ŀ��״̬����Ϊarc������ĳ��״̬�ģ�
 *                            ��˲��ü�¼arc����ʼ״̬
 **/
typedef struct {
    short    a_lbl;        /* Label of this arc */
    short    a_arrow;    /* State where this arc goes to */
} arc;
/**
 * description:    State������DFA�е�״̬�ڵ�
 * parameters:    @s_narcs     ��Ŀ
 *                @s_arc         ���ͷָ��,ÿ��state��¼�˴Ӹ�state�����ıߵļ��ϣ�
 *                            �����s_arc�С�
 *                @s_lower     ��״̬,���״̬
 *                @s_upper     ��״̬
 *                @s_accel     ��״̬��ͷָ��
 *                @s_accept    ����״̬
 **/
typedef struct {
    int         s_narcs;
    arc        *s_arc;        /* Array of arcs */
    
    /* Optional accelerators */
    int         s_lower;    /* Lowest label index */
    int         s_upper;    /* Highest label index */
    int        *s_accel;    /* Accelerator */
    int         s_accept;    /* Nonzero for accepting state */
} state;

/**
 * description:    �洢DFA״̬����
 * parameters:    @d_type        ������grammarinit.h�еķ��ս���ű��
 *                @d_name        �÷��ս���ŵ����֣�����ʱ�õ�
 *                @d_initia    ��ʼ״̬
 *                @d_nstates    ״̬����
 *                @d_state    ״̬�����ͷָ��
 **/
typedef struct {
    int         d_type;    /* Non-terminal this represents */
    std::string d_name;    /* For printing */
    int         d_initial;    /* Initial state */
    int         d_nstates;
    state    *d_state;    /* Array of states */
    bitset     d_first;
} dfa;
/**
 * description:    �洢���������е��ķ�����
 **/
class Grammar
{
public:
    /**
    * description:    ͨ����֪��DFA����һ���﷨�ṹ
    *                NOTE!����û����C++��vector����Ϊ�����ó�������grammarini.h
    *                ʹ��C���Ե���ʽ��������
    * parameter:    @dfa_num DFA�ĸ���
    *                @dfas dfa
    *                @lblist ���
    *                @start ��ʼ״̬
    *                @accel ����״̬
    * return:        nothing
    **/
    Grammar(int dfa_num,dfa dfas,labellist lblist,int start,int accel = 0);
    /**
    * description:    nothing!just realese
    * parameter:    
    * return:        none
    **/
    ~Grammar();
    /**
    * description:    ����һ��DFA״̬
    * parameter:    @t_dfa ����һ��״̬
    * return:        nothing 
    **/
    void adddfa(dfa t_dfa);
    /**
    * description:    ���һ����״̬������������
    * parameter:    
    * return:        
    **/
    int addstate(dfa *t_dfa);
    /**
    * description:    Ϊһ��DFA���һ���µı�
    * parameter:    @dfa ��Ҫ�޸ĵ�DFA
    *                @from ��ʵ״̬
    *                @to ��ֹ״̬
    *                @lbl ת��ʱ�õ��ı�
    * return:        
    **/
    void addarc(dfa *d,int from,int to,int lbl);
    /**
    * description:    ͨ��DFA��Ų���һ��DFA
    * parameter:    @id DFA���
    * return:        ���ز��ҵ������DFA
    **/
    dfa *finddfa(int32_t id);
    /**
    * description:    ���һ���µı�
    * parameter:    
    * return:        
    **/
    int addlabel(labellist *ll, int type,std::string str);
    /**
    * description:    ����һ����
    * parameter:    
    * return:        
    **/
    int findlabel(labellist *ll, int type, std::string str);

    /**
    * description:    ��ӡ�ķ����ڵ��Թ����л��õ�
    * parameter:    
    * return:        
    **/
    void printgrammar();

protected:
private:
    int dfa_num;    //DFA�ĸ���
    dfa *dfas;    //�洢����DFA
    labellist lblist;    //���бߵı��
    int start;                //��ʼ���ս���ű��
    int accel;        //accelerators present
};

/****************************
 * description:    ������ķ��ǰ��������ķ��洢�ģ���������������ƣ������������޹��ķ��洢
 **/
/**
 * description:    �洢�ķ������й���
 *                ÿ���ķ�������һ�����
 *                �ķ��޷Ƿ�Ϊ�����࣬stmt��expr��stmt��Ƕ��expr
 **/
extern struct Rule;
/**
 * description:    ����ʵ���ķ��ĵ���
 **/
class LiseGrammar
{
public:
    /**
    * description:    destructor
    **/
    ~LiseGrammar();
    /**
    * description:    ����һ���﷨��������singletonģʽ
    * parameter:    
    * return:        a constant LiseGrammar instance
    **/
    static const LiseGrammar *getgrammar();
protected:
private:
    /**
    * description:    constructor,��������
    **/
    LiseGrammar();

    short                rule_size;            //�ķ�����ĸ���
    static Rule            *rules;                //�Ծ�̬��ʽ���������ķ�
    static LiseGrammar    *_instance;            //�ķ����ڴ���ֻ��һ�ݣ�Ӧ����singletonģʽ
}

EF_NAMESPACE_END

#endif // _GRAMMAR_H_2011_11_20_lisency

