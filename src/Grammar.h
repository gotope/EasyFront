/*-------------------------------------------------------------------
 * Purpose:
 *         grammar.h 保存所有文法
 * Time:
 *         2011年11月20日 19:59:32
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _GRAMMAR_H_2011_11_20_lisency
#define _GRAMMAR_H_2011_11_20_lisency

#include <string>
#include <bitset>

EF_NAMESPACE_BEGIN

/**
 * description:    Label定义了从状态转移到另外一个状态所经过的边所对应的符号，
 *                可以是非终结符(Non-Terminal)，也可以是终结符(Terminal)。
 *                Label一定依附于一条或者多条边。
 * parameters:    @Lb_type    代表符号的类型，如终结符NAME，代表一个标示符，或者
 *                            非终结符stmt，代表一个语句，等等。
 *                @Lb_str        代表具体符号的内容。比如，label (NAME, “if”)
 *                            表示当parser处于某个状态，如果遇到了’if’这个标示
 *                            符，则移动另外一个状态。
 **/
typedef struct {
    int         lb_type;
    std::string lb_str;
} label;
/*
 */
#define EMPTY 0        //label的0状态定义为一个特殊的状态，即接受状态

/**
 * description:    存所有的lable集合
 * parameters:    @ll_nlables    lable的总数
 *                @ll_lable    状态集合的数组头指针
 **/
typedef struct {
    int         ll_nlabels;
    label    *ll_label;
} labellist;

/**
 * description:    arc代表DFA中一个状态到另一个状态的弧/边
 * parameters:    @A_lbl        arc所对应的Label
 *                @a_arrow    arc的目标状态。因为arc是属于某个状态的，
 *                            因此不用纪录arc的起始状态
 **/
typedef struct {
    short    a_lbl;        /* Label of this arc */
    short    a_arrow;    /* State where this arc goes to */
} arc;
/**
 * description:    State代表着DFA中的状态节点
 * parameters:    @s_narcs     数目
 *                @s_arc         组的头指针,每个state记录了从该state出发的边的集合，
 *                            存放在s_arc中。
 *                @s_lower     速状态,最低状态
 *                @s_upper     高状态
 *                @s_accel     速状态的头指针
 *                @s_accept    接受状态
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
 * description:    存储DFA状态集合
 * parameters:    @d_type        定义在grammarinit.h中的非终结符号标号
 *                @d_name        该非终结符号的名字，调试时用到
 *                @d_initia    初始状态
 *                @d_nstates    状态个数
 *                @d_state    状态数组的头指针
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
 * description:    存储本语言所有的文法规则
 **/
class Grammar
{
public:
    /**
    * description:    通过已知的DFA构造一个语法结构
    *                NOTE!这里没有用C++的vector是因为后面用程序生成grammarini.h
    *                使用C语言的形式会更加灵活
    * parameter:    @dfa_num DFA的个数
    *                @dfas dfa
    *                @lblist 编表
    *                @start 开始状态
    *                @accel 加速状态
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
    * description:    增加一个DFA状态
    * parameter:    @t_dfa 增加一个状态
    * return:        nothing 
    **/
    void adddfa(dfa t_dfa);
    /**
    * description:    添加一个新状态，参数还不定
    * parameter:    
    * return:        
    **/
    int addstate(dfa *t_dfa);
    /**
    * description:    为一个DFA添加一个新的边
    * parameter:    @dfa 索要修改的DFA
    *                @from 其实状态
    *                @to 终止状态
    *                @lbl 转换时用到的边
    * return:        
    **/
    void addarc(dfa *d,int from,int to,int lbl);
    /**
    * description:    通过DFA编号查找一个DFA
    * parameter:    @id DFA编号
    * return:        返回查找到的这个DFA
    **/
    dfa *finddfa(int32_t id);
    /**
    * description:    添加一条新的边
    * parameter:    
    * return:        
    **/
    int addlabel(labellist *ll, int type,std::string str);
    /**
    * description:    查找一条边
    * parameter:    
    * return:        
    **/
    int findlabel(labellist *ll, int type, std::string str);

    /**
    * description:    打印文法，在调试过程中会用到
    * parameter:    
    * return:        
    **/
    void printgrammar();

protected:
private:
    int dfa_num;    //DFA的个数
    dfa *dfas;    //存储所有DFA
    labellist lblist;    //所有边的标号
    int start;                //起始非终结符号标号
    int accel;        //accelerators present
};

/****************************
 * description:    上面的文法是按照正则文法存储的，现在我们重新设计，按照上下文无关文法存储
 **/
/**
 * description:    存储文法的所有规则
 *                每个文法规则都有一个编号
 *                文法无非分为两大类，stmt和expr，stmt中嵌套expr
 **/
extern struct Rule;
/**
 * description:    该类实现文法的调度
 **/
class LiseGrammar
{
public:
    /**
    * description:    destructor
    **/
    ~LiseGrammar();
    /**
    * description:    返回一个语法分析对象，singleton模式
    * parameter:    
    * return:        a constant LiseGrammar instance
    **/
    static const LiseGrammar *getgrammar();
protected:
private:
    /**
    * description:    constructor,不允许构造
    **/
    LiseGrammar();

    short                rule_size;            //文法规则的个数
    static Rule            *rules;                //以静态形式保存所有文法
    static LiseGrammar    *_instance;            //文法在内存中只有一份，应该用singleton模式
}

EF_NAMESPACE_END

#endif // _GRAMMAR_H_2011_11_20_lisency

