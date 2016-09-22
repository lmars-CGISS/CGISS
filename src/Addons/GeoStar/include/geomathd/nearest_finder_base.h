// nearest_finder_base.h: interface for the nearest_finder_base class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEAREST_FINDER_BASE_H__142B17FB_7C56_4CA3_9EF4_185F0C3DAC71__INCLUDED_)
#define AFX_NEAREST_FINDER_BASE_H__142B17FB_7C56_4CA3_9EF4_185F0C3DAC71__INCLUDED_

#include "point.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SLIST;
class CHeap;

GEO_NAMESPACE_BEGIN

typedef double (*point_dis2_fun)(const point& pt,const void* p);

class nearest_finder_base  
{
    //node结构描述了一个结点
    //一个结点对应一个矩形env，假如pt在env内，那么它的最近对象一定在这个node中
    //node对应的矩形不保存在成员变量中，由程序在运算的时候给出
    struct node
    {
        //两个子结点如果它们为空，那么所有可能最近对象都保存在data中，否则data必然为0
        //假如this对应的矩形为env，那么child对应的矩形是env.split函数得到的两个矩形
        node*   child[2];   
        
        //所有可能的最近对象
        SLIST*  data;

        //假如this对应的矩形为env，那么dis2为所有对象中和env最大距离的最小值
        //如果一个对象和this对应矩形的最近距离大于dis2，那么可知这个对象不会是env中任何一个点的最近对象
        float   dis2;       

        void update_dis2();

        //描述：找到包含pt的节点，返回其data
        SLIST* find(const envelope& env,point pt);
    };

    friend struct               node;
    static node                 g_node;
    envelope                    m_env;
    node*                       m_root;
    CHeap*                      m_node_heap;
    CHeap*                      m_list_heap;
    int                        m_deep;

    //m_min_dis2是计算点或者线段和矩形最小距离的回调函数
    double                      (*m_min_dis2)(envelope&,const void*);

    //m_max_dis2是计算点或者线段和矩形最大距离的回调函数
    double                      (*m_max_dis2)(envelope&,const void*);
    
    //描述：取出pn->data中的数据放入A中，并且回收pn->data所占有的资源
    void get_data(node* pn,std::vector<const void*>& A);

    //描述：将一个数据p挂到节点pn上
    void   add(node* pn,envelope& env,const void* p,int deep);

    //描述：将多个数据A挂到节点pn上
    void   n_add(node* pn,envelope& env,std::vector<const void*>& A);
public:
	nearest_finder_base(
        envelope env,
        double (*min_dis2)(envelope&,const void*),
        double (*max_dis2)(envelope&,const void*),
        int deep);
	~nearest_finder_base();
    void  add(const void* p);
    const void* nearest(point pt,point_dis2_fun fun)const;
};

GEO_NAMESPACE_END

#endif // !defined(AFX_NEAREST_FINDER_BASE_H__142B17FB_7C56_4CA3_9EF4_185F0C3DAC71__INCLUDED_)
