// delaunay.h: interface for the delaunay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELAUNAY_H__A234B344_5F52_48C9_9373_5D1C2D009C15__INCLUDED_)
#define AFX_DELAUNAY_H__A234B344_5F52_48C9_9373_5D1C2D009C15__INCLUDED_

#include "point.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHeap;

GEO_NAMESPACE_BEGIN

class path;

class GEO_DLL delaunay  
{
public:
    struct edge;
    struct tin;

    struct GEO_DLL edge
    {
        const point*    from;
        const point*    to;
        tin*            left;
        tin*            right;
        int             fix;        //如果fix为true表示这条边是特征边

        int left_right(const point& pt)const{
            return line_left_right(*from,*to,pt);
        }

        //描述：判断this和e是否相邻
        bool is_neighbor(const edge& e)const{
            return from==e.from || from==e.to || to==e.from || to==e.to;
        }

        //描述：计算积分面积
        double area()const {
            return 0.5*(to->x-from->x)*(to->y+from->y);
        }

        //描述：得到this的邻接边
        edge** neighbors(edge** it);

        //描述：设置t为this的left或right
        void set_tin(tin* t);

        void change_tin(tin* old_t,tin* new_t){
            if( left==old_t ) left = new_t;
            else right = new_t;
        }

        point midpoint()const{
            return (*from+*to)/2;
        }

        //描述：将this调整为对角边
        void swap();

        //描述：判断this是否可以swap
        bool swap_able()const;

        //描述：调整this，使得left,right成为delaunay三角形
        //返回：是否需要做调整
        bool adjust();
    };

    struct GEO_DLL tin
    {
        edge*           me[3];
        union{
            int        _l;
            tin*        _t; //构造中心线的时候用到的变量
        };

        //描述：积分面积
        double area()const;

        //描述：得到边对应的顶点
        const point*    vertex(const edge* e)const;
        
        //描述：得到第i条边对应的顶点
        const point*    vertex(int i)const{ return vertex(me[i]); }

        //描述：得到和this共顶点pt的逆时针的第一个tin
        const tin* next(const point* pt)const;

        //描述：得到中心线
        int central(point* pt)const;

        //描述：得到和this相邻的三个tin
        tin** neighbors(tin** p);

        //描述：得到中心点
        point midpoint()const;
    };

	delaunay(envelope env);
	virtual ~delaunay();

    //功能：添加点
	bool add_point(const point* p);
    bool add_point(point pt);
    void add_point(const path* l);

    //功能：添加特征线
	bool add_line(point p,point q);
    bool add_line(const point* l);
    void add_line(const path* l);

    //功能：添加特征线
    void add_line_ex(point p,point q);
    void add_line_ex(const point* p);
    void add_line_ex(const path* l);
    
    //描述：得到所有的edge
    //参数：如果filt为true那么将过滤掉有顶点为m_box的edge
    std::vector<const edge*> edges(bool filt=true)const;

    //描述：得到所有的tin
    //参数：如果filt为true那么将过滤掉有顶点为m_box的tin
    std::vector<const tin*> tins(bool filt=true)const;

    double                          m_tol2;
protected:
    CHeap*                          m_tin_heap;
    CHeap*                          m_edge_heap;
    CHeap*                          m_pt_heap;
    tin*                            m_tmp;
    point                           m_box[4];

    bool  is_help_point(const point* p)const{
        return p >= m_box && p < m_box+4;
    }
    bool  is_help_edge(const edge* e)const{
        return is_help_point(e->from) || is_help_point(e->to);
    }
    bool  is_help_tin(const tin* t)const{
        return is_help_edge(t->me[0]) || is_help_edge(t->me[1]) || is_help_edge(t->me[2]);
    }

    static bool add_line_call_back(void* pThis,point* pt);
    static bool add_line_ex_call_back(void* pThis,point* pt);
    static bool add_point_call_back(void* pThis,point* pt);

    //描述：判断a是否在this的初始化矩形之内
    bool is_cover(const point& a)const;

    //描述：分配tin，设置tin的三边为a,b,c同时维护a,b,c和此tin的关系
    //参数：a,b,c的from,to必须已经设置好，且能够构成一个tin的三边
    tin*  alloc_tin(edge* a,edge* b,edge* c);

    //描述：分配edge，新edge的left,right为0
    edge* alloc_edge(const point* p,const point* q);

    //描述：找到pt所在的tin
    //参数：p是this中任意一个tin，也就是m_tmp
    const tin* find_tin(const tin* p,point pt)const;
};

GEO_NAMESPACE_END

#endif // !defined(AFX_DELAUNAY_H__A234B344_5F52_48C9_9373_5D1C2D009C15__INCLUDED_)
