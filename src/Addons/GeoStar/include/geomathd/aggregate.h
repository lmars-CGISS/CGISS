// aggregate.h: interface for the aggregate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGGREGATE_H__2C887899_742D_4F44_8AA4_7B5491C8F38E__INCLUDED_)
#define AFX_AGGREGATE_H__2C887899_742D_4F44_8AA4_7B5491C8F38E__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

/*
    aggregate用来做节点聚合
*/
class connect_component;

class GEO_DLL aggregate  
{
    //描述：将L中所有的节点指针push到A中
    void  add(path *L,std::vector<point*> &A);
public:
    typedef std::pair<point*,point*> pt_pt;

    double m_min_tol,m_max_tol;
    std::vector<point*>     m_target;
    std::vector<point*>     m_source;
    std::vector<pt_pt>  m_source_target;
    std::vector<pt_pt>  m_target_source;
    
	aggregate(double min_tol,double max_tol);
	virtual ~aggregate();

	//描述：得到聚合信息
	//参数：s2s表示是否允许m_source中的点聚合到m_source中的点
	//返回：函数将得到的聚合信息写入m_source_target和m_target_source中
    void get_aggregate_info(int s2s=1);

    //描述：将所有的source聚合到它的target
    void do_aggregate();

    //描述：得到pt的聚合目标
    //      如果返回false表示pt不聚合到任何点
    point* get_target(point *pt)const;

    //描述：得到所有聚合到pt的点
    int  get_source(point *pt,std::vector<point*> &source)const;

    //描述：得到下一个有source聚合到它的point
    //      用户可以传入0得到第一个有聚合的point*，如果返回-1表示已经没有比pt更大的下一个target
    point* next_target(point *pt)const;

    void  add_target(const path *L){
        add( (path*)L,m_target );
    }

    void add_target(point* pt){
        m_target.push_back(pt);
    }

    void add_source(point* pt){
        m_source.push_back(pt);
    }
        
    void  add_source(path *L){
        add( (path*)L,m_source);
    }

    static void map_point(const point* p,int n,std::vector<int> &K);
    static void map_point(point** p,int n,std::vector<int> &K);
    static void quick_aggregate(std::vector<point*> &A,double tol);
    static void quick_aggregate(point* p,int n,double tol);

	//描述：得到聚合信息
	static void get_aggregate_component(double   tol2,       //距离容差的平方
		point**                             begin,      //参与聚合的第一个点
		std::pair<point**,point**>*         p_nears,    //距离小于容差的点对的首地址
		int                                 n_nears,    //距离小于容差的点对的个数
		connect_component                   &C) ;

	//描述：得到pts中距离小于容差的点对。
	//参数：pts输入的点指针数组，tol给定的容差，out是返回的所有距离小于容差的点对
	//      假如A是out中某个元素，i,j分别是A.first和A.second，那么**i和**j的距离必然小于tol，并且i,j是pts中元素的地址
	static void get_near_pair(const std::vector<point*> &pts,double tol,
		std::vector< std::pair<point**,point**> > &out);
};

GEO_NAMESPACE_END

#endif // !defined(AFX_AGGREGATE_H__2C887899_742D_4F44_8AA4_7B5491C8F38E__INCLUDED_)
