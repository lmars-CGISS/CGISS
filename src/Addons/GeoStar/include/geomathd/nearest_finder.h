// nearest_finder.h: interface for the nearest_finder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEAREST_FINDER_H__191FE7D5_AE70_4B09_8EC1_194F1D298280__INCLUDED_)
#define AFX_NEAREST_FINDER_H__191FE7D5_AE70_4B09_8EC1_194F1D298280__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

/******** nearest_finder类用来加快多个点和一个path的最近点和距离的计算。***********
***********************************************************************************/

class nearest_finder_base;

class GEO_DLL point_nearest_finder
{
    nearest_finder_base*    m_base;
    static bool add_fun(void*,point* p);
    static double dis2_fun(const point& pt,const void*p);
public:
    point_nearest_finder(envelope env,int deep=8);
    ~point_nearest_finder();

    void add(const path* l);
    void add(const point* p);
    
    //注意：传入的pt必须在构造函数的env内部，否则会返回0
    const point* nearest(point pt)const;

    //注意：传入的pt必须在构造函数的env内部，否则会返回DBL_MAX
    double dis2(point pt)const;
};

class GEO_DLL seg_nearest_finder
{
    nearest_finder_base*    m_base;
    envelope                m_env;
    static bool add_fun(void*,point* p);
    static double dis2_fun(const point& pt,const void*p);
public:
    seg_nearest_finder(envelope env,int deep=8);
    ~seg_nearest_finder();

    void add(const path* l);
    void add(const line* p);
    void add(const pnode* p);

    //注意：传入的pt必须在构造函数的env内部，否则会返回0
    const point* nearest(point pt)const;

    //注意：传入的pt必须在构造函数的env内部，否则会返回DBL_MAX
    double dis2(point pt)const;
};

GEO_NAMESPACE_END

#endif // !defined(AFX_NEAREST_FINDER_H__191FE7D5_AE70_4B09_8EC1_194F1D298280__INCLUDED_)



