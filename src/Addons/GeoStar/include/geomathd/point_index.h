// point_index.h: interface for the point_index class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT_INDEX_H__0E3BD9C8_CDE1_42D6_97B3_093354A624E3__INCLUDED_)
#define AFX_POINT_INDEX_H__0E3BD9C8_CDE1_42D6_97B3_093354A624E3__INCLUDED_

#include "path.h"
#include "spatial_index.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class GEO_DLL point_index  
{
public:
	spatial_index<double>              m_index;
public:
	point_index();
	~point_index();

    //描述：将L的端节点添加到m_index中
    void add_port(const polyline *L);
    void add_port(const curve *L);
    void add_port(const multi_path *L);
    void add_port(const path *L);

    //描述：将L的内节点添加到m_index中
    void add_inner(const polyline *L);
    void add_inner(const curve *L);
    void add_inner(const multi_path *L);
    void add_inner(const path *L);

    //描述：将L的端节点从m_index中删除
    void remove_port(const polyline *L);
    void remove_port(const curve *L);
    void remove_port(const multi_path *L);
    void remove_port(const path *L);

    //描述：将L的内节点从m_index中删除
    void remove_inner(const polyline *L);
    void remove_inner(const curve *L);
    void remove_inner(const multi_path *L);
    void remove_inner(const path *L);

    //描述：将L的所有节点添加到m_index中
    void add(const path *L){
        add_port(L);
        add_inner(L);
    }

    //描述：将L的所有节点从m_index中删除
    void remove(const path *L){
        remove_port(L);
        remove_inner(L);
    }

    //描述：添加单个点
    void add(const point *pt){
        m_index.add( (void*)(((long long)pt)|3),(double*)pt,0 );
    }

    //描述：删除单个点
    void remove(const point *pt){
        m_index.remove( (void*)(((long long)pt)|3),(double*)pt,0 );
    }

    //描述：得到this和L的交点在L上的参数
    //参数：off为参数的偏移值，也就是说如果某个交点在L上的参数为t，那么push_back入out的值为t+off
    void break_path(const polyline *L,double tol,double off,std::vector<double> &out)const;
    void break_path(const curve *L,double tol,double off,std::vector<double> &out)const;
    void break_path(const multi_path *L,double tol,double off,std::vector<double> &out)const;
    void break_path(const path *L,double tol,double off,std::vector<double> &out)const;

    //描述：将L打断打断的结果放入out中，函数会清除out原有的数据
    //      如果L根本没有被打断则返回false，out不会有任何内容
    bool break_segment(const line *L,double tol,std::vector<line> &out)const;
    bool break_segment(const arc *L,double tol,std::vector<arc> &out)const;

    //描述：判断是否this中的所有点都和pt相离
    bool is_intersect(const point& pt,double tol)const;

    //描述：判断this中是否有点和env相交
    bool is_intersect(const envelope& env)const;

    //描述：判断this中是否有点和L相交
    bool is_intersect(const path* L,double tol)const;

	//描述：判断this中是否有点和L相穿
	bool is_cross(const path* L,double tol)const;
	bool is_cross(point a,point b,point c,double tol)const;

    //描述：选出所有在env内部或边界上的点到out中
    void query_by_env(const envelope& env,std::vector<point*>& out)const;

    //描述：将pt聚合到this中离它最近的点
    //参数：tol是容查，如果最近点的距离大于容查或者两者精确相等则不聚合
    bool aggregate(point& pt,double tol)const;

    //描述：将l中的点聚合到this
    bool aggregate(path* l,double tol)const;

    //描述：用this打断l打断结果写入A(没有打断的情况下A中会加入l)
    //返回：如果l没有被this打断的必要则返回false否则返回true
    //注意：程序不会删除A中原来的数据
    bool separate(path* l,double tol,std::vector<path_ptr>& A);
};  

GEO_NAMESPACE_END


#endif // !defined(AFX_POINT_INDEX_H__0E3BD9C8_CDE1_42D6_97B3_093354A624E3__INCLUDED_)
