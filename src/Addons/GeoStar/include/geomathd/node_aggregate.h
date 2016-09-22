// node_aggregate.h: interface for the node_aggregate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_AGGREGATE_H__8B065186_B137_4907_AFE6_B4234CBDBE36__INCLUDED_)
#define AFX_NODE_AGGREGATE_H__8B065186_B137_4907_AFE6_B4234CBDBE36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "path.h"
#include "spatial_index.h"

GEO_NAMESPACE_BEGIN

//node_aggregate类实现节点聚合的功能，
//节点聚合的时候有两组数据参加聚合，一组称为target，另一组称为source
//聚合算法是将source上的点或线聚合到target上

//使用node_aggregate  的步骤是先调用add_target函数把target加入node_aggregate对象中
//然后调用aggregate函数聚合source

//目前的实现不支持curve类型 

class GEO_DLL node_aggregate  
{
    GEO_NAMESPACE::spatial_index<double>  m_si_pt;
    GEO_NAMESPACE::spatial_index<double>  m_si_line;
	GEO_NAMESPACE::multi_path				m_targets;
public:
    node_aggregate():m_si_pt(2),m_si_line(2){}
    ~node_aggregate(){}

    //描述：加入target对象
    void add_target(const path* l);

    //描述：聚合polyline对象
    void aggregate(polyline* l,double tol);

    //描述：聚合curve对象(目前的行动是无作为)
    void aggregate(curve* l,double tol){} 
    
    //描述：聚合path对象
    void aggregate(path* l,double tol);

	static void aggregate(double tol,const path* target,path* source);
};

GEO_DLL void line_aggregate(path* l,double tol,const path* boud = 0);

GEO_NAMESPACE_END

#endif // !defined(AFX_NODE_AGGREGATE_H__8B065186_B137_4907_AFE6_B4234CBDBE36__INCLUDED_)
