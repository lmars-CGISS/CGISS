// build.h: interface for the build class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUILD_H__E0B844CE_C086_470C_AE5B_54B33F99A79E__INCLUDED_)
#define AFX_BUILD_H__E0B844CE_C086_470C_AE5B_54B33F99A79E__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

struct GEO_DLL build_ring_base
{
    virtual int path_count()=0;
    virtual double get_front(int j,point &pt)=0;
    virtual double get_back(int j,point &pt)=0;
    
    //功能：找出所有的圈。
    //参数：out为返回的圈集合，一个圈用整数数组A表示。
    //      A[i]为rings的第i条折线，取值从0到2*count()
    //      如果A[i]为2*j那么表示第j条折线，如果为2*j+1那么表示反方向的折线
    int build_ring(std::vector< std::vector<int> > &out );

    //功能：找到所有的悬挂点
    int get_suspension(std::vector<point> &out);

    //描述：找到在面l内部的悬挂点
    int get_suspension(const path* l,std::vector<point> &out);
};

struct GEO_DLL build_surface_base
{
    virtual int ring_count()=0;
    virtual double get_area(int i)=0;
    virtual bool get_label(int j,double &x,double &y)=0;
    virtual void get_minmax(int j,double *Min,double *Max)=0;
    virtual void select_inner(int j,std::vector<double*> &A)=0;

    //功能：找出所有的面。
    //参数：out为返回的面集合
    int build_surface(std::vector< std::vector<int> > &out);
};

class GEO_DLL build : public build_ring_base,public build_surface_base
{
protected:
	virtual int path_count();
    virtual double get_front(int j,point &pt);
    virtual double get_back(int j,point &pt);

	virtual int ring_count();
    path_ptr    ring_at(int i);
    virtual double get_area(int i);
    virtual bool get_label(int j,double &x,double &y);
    virtual void get_minmax(int j,double *Min,double *Max);
    virtual void select_inner(int j,std::vector<double*> &A);

public:
	virtual int count();
	virtual path_ptr get_at(int i);

    //用线的标号描述的圈
    typedef std::vector<int>        ring_path;

    //用线的标号描述的面
    typedef std::vector<int>        surface_path;

    //用圈的序号描述的面
    typedef std::vector<int>        surface_ring;

    //用圈描述的面
    typedef std::vector<ring_path>  surface_ring_path;

	std::vector<ring_path>*         m_rings;	
	multi_path                      m_paths;

	void add(path *l){ m_paths.push_back(l); }

	build();
	~build();

    //描述：计算圈或者面的积分面积
    double area(const ring_path &I);
    double area(const surface_ring_path &I);

    //描述：从surface_path提出圈的信息
    bool     get_ring_info(surface_path in,surface_ring_path &out);

    //描述：利用各种信息构造path对象
    path_ptr construct_ring(const ring_path &I);
	path_ptr construct_surface(const std::vector<ring_path> *R,const surface_ring &I);
    path_ptr construct_surface(const surface_ring_path &I);
    path_ptr construct_surface(const surface_path &I);

    //描述：build出所有的面和圈
	int      build_all(std::vector<ring_path> *R,std::vector<surface_ring> *S);
    
    //描述：build出所有的面和圈每个面用surface_path
    int      build_min(std::vector<surface_path> &surfaces);

    //描述：根据id相同的规则将S中的面并起来
    int      union_by_id(std::vector<int>& ids,std::vector<surface_path> &S);

    //描述：在S中选择出包含label中的面
    void     select_surface(const std::vector<point>& label,std::vector<surface_path> &S);

    //描述：选点构面
    //返回：返回值为构造出来的面，如果返回空那么pt值将被修改到出错点的位置。
    path_ptr build_by_point(point &pt);

    //描述：删除S中对同一条线的引用，这是union_by_id和get_ring_info使用的内部函数
    static   void     remove_overlap(surface_path &S);
};

GEO_NAMESPACE_END


#endif // !defined(AFX_BUILD_H__E0B844CE_C086_470C_AE5B_54B33F99A79E__INCLUDED_)
