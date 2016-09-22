// spatial_index.h: interface for the spatial_index class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_spatial_index_H__009726A6_4EDE_4B7C_8E61_58424A84DAFE__INCLUDED_)
#define AFX_spatial_index_H__009726A6_4EDE_4B7C_8E61_58424A84DAFE__INCLUDED_

#include "geomacro.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class bank;

GEO_NAMESPACE_BEGIN

/*
    空间索引
*/

template<class type>
class GEO_DLL spatial_index
{
    bank*           m_bank;    
    mutable int*   m_tmp;
    spatial_index(const spatial_index&);
    void operator = (const spatial_index&);
public:
    int (*m_filter_fun)(void *filter,int n,void* p); 
    void* m_filter;

    //描述：利用m_filter_fun过滤查询的结果
    int filter(int n,void *p,int space)const{
        if( m_filter_fun==0 || p==0 || space<n )
            return n;
        return m_filter_fun(m_filter,n,p);
    }

    GEO_DLL_CMF spatial_index(int dimension);
    GEO_DLL_CMF ~spatial_index();

    GEO_DLL_CMF void set_unique(bool b_unique);
    GEO_DLL_CMF void add(const void *obj,const type *o,const type *r);
    GEO_DLL_CMF bool remove(const void *obj,const type *o,const type *r);
    GEO_DLL_CMF int query(const type *o,const type *r,void *p,int space)const;

    GEO_DLL_CMF void Add(const void *obj,const type *_min,const type *_max);
    GEO_DLL_CMF bool Remove(const void *obj,const type *_min,const type *_max);
    GEO_DLL_CMF int Query(const type *_min,const type *_max,void *p,int space)const;
    
	//依据正方形框选取
    template<class array_type>
    int query(const type *o,const type *r,array_type &A)const
    {
		int n = query(o,r,m_tmp,1024);
		if(n==0){ A.clear(); return 0; }
		A.resize(n);
		if( A.size() < 1024 ) memcpy( &A[0],m_tmp,A.size()*(sizeof(A[0])) );
	    else A.resize( query(o,r,&A.front(),A.size() ) );
	    return A.size();
    }

    template<class array_type>
    int Query(const type *_min,const type *_max,array_type &A)const
    {
		int n = Query(_min,_max,m_tmp,1024);
		if(n==0){ A.clear(); return 0; }
	    A.resize(n);
	    if( A.size() < 1024 ) memcpy( &A[0],m_tmp,A.size()*(sizeof(A[0])) );
	    else A.resize( Query(_min,_max,&A[0],A.size() ) );
	    return A.size();
    }
};

struct envelope;

//描述：利用envelope到空间索引中查询数据
template<class T>
int SpatialQuery(const spatial_index<double> &Q,const envelope &E,std::vector<T> &A){
    point minpt = E.get_min();
	point maxpt = E.get_max();
	return Q.Query( &minpt.x,&maxpt.x,A );
}

//描述：利用对象的外接矩形到空间索引中查询数据
template<class P,class T>
int SpatialQuery(const spatial_index<double> &Q,const P *L,double tol,std::vector<T> &A){
    return SpatialQuery( Q,xy_range(L).expand(tol),A );
}

//描述：利用外接矩形将对象添加到空间索引中
template<class T>
void SpatialAdd(spatial_index<double> &Q,const envelope &E,const T *L){
	point minpt = E.get_min();
	point maxpt = E.get_max();
	Q.Add( L,&minpt.x,&maxpt.x );
}

//描述：利用对象的外接矩形将对象添加到空间索引中
template<class T>
void SpatialAdd(spatial_index<double> &Q,const T *L){
    envelope E; xy_range(L,E);
	point minpt = E.get_min();
	point maxpt = E.get_max();
	Q.Add( L,&minpt.x,&maxpt.x );
}

//描述：利用外接矩形将对象从空间索引中删除
template<class T>
void SpatialRemove(spatial_index<double> &Q,const envelope &E,const T *L){
	point minpt = E.get_min();
	point maxpt = E.get_max();
	Q.Remove( L,&minpt.x,&maxpt.x);
}

//描述：利用对象的外接矩形将对象从空间索引中删除
template<class T>
bool SpatialRemove(spatial_index<double> &Q,const T *L){
    envelope E; xy_range(L,E);
	point minpt = E.get_min();
	point maxpt = E.get_max();
	return Q.Remove( L,&minpt.x,&maxpt.x );
}

GEO_NAMESPACE_END


#endif // !defined(AFX_spatial_index_H__009726A6_4EDE_4B7C_8E61_58424A84DAFE__INCLUDED_)
