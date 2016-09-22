// querist.h: interface for the querist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERIST_H__E6ECB8C6_4B45_4620_9C64_9B21A443CE34__INCLUDED_)
#define AFX_QUERIST_H__E6ECB8C6_4B45_4620_9C64_9B21A443CE34__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class single_surface_index;

class GEO_DLL querist  
{
    struct q_base
    {
        virtual ~q_base(){};
        virtual int dimension()const=0;
        virtual void x_range(range&)const=0;
        virtual void y_range(range&)const=0;
        virtual const path*  get_path()const=0;

        virtual bool is_equal(point pt,double tol)const=0;
        virtual bool is_equal(envelope env,double tol)const=0;
        virtual bool is_equal(const path* l,double tol)const=0;

        virtual bool is_cover(point pt,double tol)const=0;
        virtual bool is_cover(envelope env,double tol)const=0;
        virtual bool is_cover(const path* l,double tol)const=0;

        virtual bool is_covered(envelope env,double tol)const=0;
        virtual bool is_covered(const path* l,double tol)const=0;
        virtual bool is_covered(const single_surface_index* l,double tol)const=0;

        virtual bool is_overlap(envelope env,double tol)const=0;
        virtual bool is_overlap(const path* l,double tol)const=0;

        virtual bool is_touch(envelope env,double tol)const=0;
        virtual bool is_touch(const path* l,double tol)const=0;

        virtual bool is_cross(envelope env,double tol)const=0;
        virtual bool is_cross(const path* l,double tol)const=0;

        virtual bool is_intersect(point pt,double tol)const=0;
        virtual bool is_intersect(envelope env,double tol)const=0;
        virtual bool is_intersect(const path* l,double tol)const=0;
    };
    struct q_point;     //点
    struct q_envelope;  //矩形
    struct q_path0;     //点群
    struct q_path1;     //线
    struct q_path2;     //面
    friend struct q_point;
    friend struct q_envelope;  //矩形
    friend struct q_path0;     //点群
    friend struct q_path1;     //线
    friend struct q_path2;     //面
    q_base*     m_query;
    querist(const querist&);
    void operator=(const querist&);
public:
	querist(point pt);
    querist(envelope env);
    querist(const path* l);
    ~querist();

    int  dimension()const{
        return m_query?m_query->dimension():-1;
    }
    void x_range(range& r)const{
        if( m_query )
            m_query->x_range(r);
    }
    void y_range(range& r)const{
        if( m_query )
            m_query->y_range(r);
    }
    const path* get_path()const{
        return m_query?m_query->get_path():0;
    }

    bool is_equal(point pt,double tol)const{
        return m_query?m_query->is_equal(pt,tol):false;
    }
    bool is_equal(envelope env,double tol)const{
        return m_query?m_query->is_equal(env,tol):false;
    }
    bool is_equal(const path* l,double tol)const{
        return m_query?m_query->is_equal(l,tol):false;
    }

    bool is_cover(point pt,double tol)const{
        return m_query?m_query->is_cover(pt,tol):false;
    }
    bool is_cover(envelope env,double tol)const{
        return m_query?m_query->is_cover(env,tol):false;
    }
    bool is_cover(const path* l,double tol)const{
        return m_query?m_query->is_cover(l,tol):false;
    }

    bool is_covered(envelope env,double tol)const{
        return m_query?m_query->is_covered(env,tol):false;
    }
    bool is_covered(const path* l,double tol)const{
        return m_query?m_query->is_covered(l,tol):false;
    }
    bool is_covered(const single_surface_index* l,double tol)const{
        return m_query?m_query->is_covered(l,tol):false;
    }

    bool is_overlap(envelope env,double tol)const{
        return m_query?m_query->is_overlap(env,tol):false;
    }
    bool is_overlap(const path* l,double tol)const{
        return m_query?m_query->is_overlap(l,tol):false;
    }

    bool is_touch(envelope env,double tol)const{
        return m_query?m_query->is_touch(env,tol):false;
    }
    bool is_touch(const path* l,double tol)const{
        return m_query?m_query->is_touch(l,tol):false;
    }

    bool is_cross(envelope env,double tol)const{
        return m_query?m_query->is_cross(env,tol):false;
    }
    bool is_cross(const path* l,double tol)const{
        return m_query?m_query->is_cross(l,tol):false;
    }

    bool is_intersect(point pt,double tol)const{
        return m_query?m_query->is_intersect(pt,tol):false;
    }
    bool is_intersect(envelope env,double tol)const{
        return m_query?m_query->is_intersect(env,tol):false;
    }
    bool is_intersect(const path* l,double tol)const{
        return m_query?m_query->is_intersect(l,tol):false;
    }
};

GEO_NAMESPACE_END

#endif // !defined(AFX_QUERIST_H__E6ECB8C6_4B45_4620_9C64_9B21A443CE34__INCLUDED_)
