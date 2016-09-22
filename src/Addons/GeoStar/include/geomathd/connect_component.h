// connect_component.h: interface for the connect_component class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECT_component_H__57147D56_B7CC_4F4E_AEC4_9A3CFA746B41__INCLUDED_)
#define AFX_CONNECT_component_H__57147D56_B7CC_4F4E_AEC4_9A3CFA746B41__INCLUDED_

#include "geomacro.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

/*
    connect_component是一个专门用来分析图的连同性的类
*/

class GEO_DLL connect_component  
{
protected:
    int*        m_key;          //m_key[i]表示第i个点所属图的第一个点

    int*        m_connect;      //m_connect存放属于同一个连通图的点的序号信息，
                                //格式为：g0=i,g1=m_connect[g0],g2=m_connect[g1]，…,gn=m_connect[gn-1]，
                                //这里i是子图的第一个点，如果m_connect[j]==j，表示j是子图的最后一个点

    int*        m_end;          //存放图的最后一个点，假如i是某个子图的第一个点，j=m_end[i]，那么j就是此子图的最后一个点
                                //如果i!=j，那么m_end[j]就是此子图中点的个数

    int         m_n_graph;      //子图的个数
        
    int         m_n_point;      //点的个数
public:
    connect_component();
	connect_component(int size);
	~connect_component();

    //描述：返回第i个点所属于的图的第一个点的序号
    int operator[](int i)const{
        return m_key[i];
    }

    //描述：判断两个点i,j是否连通
    bool is_connect(int i,int j)const{
        return m_key[i]==m_key[j];
    }

    //描述：返回子图的个数
    int g_num()const{
        return m_n_graph;
    }

    //描述：返回第i个点所属的子图的点的个数
    int  c_num(int i)const{
        i = m_key[i];
        if( m_end[i]==i )
            return 1;
        return m_end[m_end[i]];
    }

    //描述：删除某个子图
    void remove_graph(int i);
    
    //描述：添加一条边
    void add_edge(int i,int j);

    //描述：得到第i个点所属的图的所有点
    int  get_graph(int i,std::vector<int> &out)const;

    //描述：得到所有的子图，返回子图的个数
    int  all_graphs(std::vector<std::vector<int> > &out)const;
};

GEO_NAMESPACE_END


#endif // !defined(AFX_CONNECT_component_H__57147D56_B7CC_4F4E_AEC4_9A3CFA746B41__INCLUDED_)
