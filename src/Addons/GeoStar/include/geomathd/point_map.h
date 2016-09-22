// point_map.h: interface for the point_map class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT_MAP_H__5ABA9E91_C3BE_402D_97C4_C3334E2176D1__INCLUDED_)
#define AFX_POINT_MAP_H__5ABA9E91_C3BE_402D_97C4_C3334E2176D1__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

/* 
    point_map 的作用是提供根据节点的指针找到它所在的path有关的信息
*/

class point_map  
{
    typedef std::pair<point*,path*> point_path;
    typedef std::pair<path*,__int3264>    path_int;

    std::vector<point_path>         m_point_single;
    std::vector<path_int>           m_single_id;
    std::vector<path_int>           m_remove;

    bool                            m_update;
    void                            update();
public:

	point_map();
	virtual ~point_map();

    //描述：添加L的相关信息到this中
    //注意：可以用相同的L多次调用add，不同调用之间传递的id可以相同也可以不同
    //      一个L在add入this后remove之前外部不能修改，否则将引发point_map内部的错误
    void add(const path *L,__int3264 id);

    //描述：从this中移除L的相关信息
    void remove(const path*L,__int3264 id);

    //描述：根据点的指针得到它所在的单线的地址
    const path* get_single(const point* pt)const;

    //描述：得到path的id
    //参数：传入的l必须是单线的指针，out为存放id的数组，函数不删除out中原有的数据只是往后追加
    //返回：函数返回out中新增数据的个数
    int get_id(const path* l,std::vector<__int3264> &out)const;
    int get_id(const point* pt,std::vector<__int3264> &out)const{
        return get_id( get_single(pt),out );
    }

    //描述：判断l是否有一个id
    bool have_id(const path* l,__int3264 id)const;
    bool have_id(const point* pt,__int3264 id)const{
        return have_id( get_single(pt),id );
    }
    //描述：判断[pp,pp+n)中有多少有id
    int  n_have_id(point** pp,int n,__int3264 id)const;

    //描述：判断l是否被反向引用
    bool is_reve(const path* l)const;
    bool is_reve(const point* pt)const{
        return is_reve( get_single(pt) );
    }

    //描述：判断l是否被反向引用
    bool is_reve(const path* l,__int3264 id)const;
    bool is_reve(const point* pt,__int3264 id)const{
        return is_reve( get_single(pt),id );
    }
};

GEO_NAMESPACE_END

#endif // !defined(AFX_POINT_MAP_H__5ABA9E91_C3BE_402D_97C4_C3334E2176D1__INCLUDED_)
