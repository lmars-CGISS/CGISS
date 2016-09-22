// single_surface_index.h: interface for the single_surface_index class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SINGLE_SURFACE_INDEX_H__3D8CB075_CCA7_4EAC_8394_ED10E8E97DDD__INCLUDED_)
#define AFX_SINGLE_SURFACE_INDEX_H__3D8CB075_CCA7_4EAC_8394_ED10E8E97DDD__INCLUDED_

#include "path.h"
#include "spatial_index.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class reve_port_across;

class GEO_DLL single_surface_index
{
	spatial_index<double>            m_index;
    reve_port_across*                m_port;

public:
	single_surface_index();
	virtual ~single_surface_index();

    //描述：将L加入this
	void add(const path *l);

    //描述：将L从this中删除
	void remove(const path *l);

    //描述：得到穿越数
	int across(const point &pt)const;
    int across(double x,double y)const{ return across(point(x,y)); }

    //描述：判断env是否和this相离
	bool is_disjoin(const envelope &env)const;

    //描述：判断this是否包含pt
	bool is_cover(const point &pt,double tol=0)const;
    bool is_cover(double x,double y,double tol=0)const{ return is_cover(point(x,y),tol); }

    //描述：得到内部点
    bool get_inner(const envelope &env,point &pt,double tol)const;

    //描述：移入到内部点
    bool moveto_inner(point &pt,double tol)const;

    //描述：获得多个点和this的穿越数
    //参数：A.size()为点的个数，第一个点是pt，第二个是(pt.x,pt.y+dy)，第三个是(pt.x,pt.y+2*dy)，…………
    //返回：将每个点和this的穿越数保存在A中
	void n_across(point pt,double dy,std::vector<int> &A)const;

    //描述：获得多个点和this的相交信息
    //参数：A.size()为点的个数，第一个点是pt，第二个是(pt.x,pt.y+dy)，第三个是(pt.x,pt.y+2*dy)，…………
    //      每个点都当作是以这个点为中心扩展tol的矩形
    //返回：如果第i个点和this相交那么A[i]为true否则A为false
    void n_intersect(point pt,double dy,point tol,std::vector<int> &A)const;

    //描述：获得多个点和this的包含信息
    //参数：A.size()为点的个数，第一个点是pt，第二个是(pt.x,pt.y+dy)，第三个是(pt.x,pt.y+2*dy)，…………
    //      每个点都当作是以这个点为中心扩展tol的矩形
    void n_cover(point pt,double dy,point tol,std::vector<int>& A)const;

    //描述：随机的找出在env和this内部的若干个点
    //参数：V点之间的间隔，tol点和this的距离
    //返回：out是返回的结果，函数事先清除out中原有的数据
    void nn_select(envelope env,point V,point tol,std::vector<point>& out)const;
};

GEO_NAMESPACE_END


#endif // !defined(AFX_SINGLE_SURFACE_INDEX_H__3D8CB075_CCA7_4EAC_8394_ED10E8E97DDD__INCLUDED_)
