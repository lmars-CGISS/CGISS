// path_connect.h: interface for the path_connect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATH_CONNECT_H__FDB954EF_A6E0_4FB0_BFC3_36D21F847C6D__INCLUDED_)
#define AFX_PATH_CONNECT_H__FDB954EF_A6E0_4FB0_BFC3_36D21F847C6D__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class connect_component;

class GEO_DLL path_connect  
{
	std::vector<point>			m_line;
	std::vector<point>		    m_arc;
    std::vector<point>		    m_bezier;
	std::vector<int>			m_pt_key;
	std::vector<int>			m_tmp;
	int prepare();
    //描述：根据上connect函数返回的index[i]构造出这些线段连接的顺序
    void get_connect_info(const std::vector<int> &I,std::vector<int> &O);
    int** _connect(int mode,int **it,connect_component &c);

    //描述：如果m_tol大于0聚合m_line和m_arc中的点
    void _aggregate();
public:
    void clean();

    double m_tol; //如果m_tol大于0那么函数在在运算之前使用m_tol进行聚合

    double m_altitude; //跟踪等高线时候的给定的高程

    path_connect(double tol=0);
	virtual ~path_connect();

    typedef std::vector<int> connect_info;

    //描述：添加一条线段到this
    void add_line(const point& a,const point& b){
        m_line.push_back(a);
        m_line.push_back(b);
    }

    //描述：添加一条圆弧到this
    void add_arc(const point& a,const point& b,const point &c);

    //描述：添加一条beizer到this
    void add_bezier(const point& a,const point& b,const point &c,const point &d);

    //描述：添加一个分隔点，以后在pt处任何两条线段或圆弧都不能相连
    void add_break(point pt){
        add_line(pt,pt);
    }

    //描述：算出z轴等于m_altitude的平面和空间三角形的交线，将此线add入this
    //作用：这个函数用来做等高线跟踪
    void add_tin(const point& a,double ha,const point& b,double hb,const point& c,double hc);

    //描述：算出z轴等于m_altitude的平面和空间四边角形的交线，将此线add入this
    //作用：这个函数用来做等高线跟踪
    void add_square(const point& a,double ha,const point& b,double hb,const point& c,double hc,const point& d,double hd);

    //描述：得到等高线
    path_ptr get_contour();

    //描述：添加一条线段或圆弧
    void add(const line *l){ 
        add_line(l->me[0],l->me[1]);
    }
    void add(const arc *l){
        add_arc(l->me[0],l->me[1],l->me[2]);
    }
    void add(const bezier *l){
        add_bezier(l->me[0],l->me[1],l->me[2],l->me[3]);
    }
    void add(const pnode *l);
    void add(const path* l);

    //描述：根据线号生成pnode
    void get_segment(int l,pnode *pt)const;

    //描述：将l的起点终点当作线段添加入this
    void add_path(const path *l){
        add_line( *safe_front_ptr(l),*safe_back_ptr(l) );
    }

    //描述：去除重复的线段(一定会留一条)
	//参数：care_direct异向的线段是否认为重复
	//care_direct=>true则认为只有同向的是重复
	//           =>false不管同向、异向，都认为是重复。
	void remove_overlap(bool care_direct);
	//描述：获取重复的线段
	//参数：care_direct异向的线段是否认为重复,result返回被去除的重叠部分(不分方向)
	void get_overlap(bool care_direct,std::vector<path_ptr> &result);

	//描述：去除成对线段
	//参数： 如果dir=0则方向相同的认为是成对线段,否则方向相反的认为是成对线段
	void remove_pairline(int dir);
	
    //描述：得到所有连接信息
    //参数：mode为连接方式，mode&1表示方向敏感，mode&2表示重叠敏感
    //      out为返回的所有连接信息
	int connect(int mode,std::vector<connect_info> &out);

    int connect_ex(int mode,std::vector<path_ptr> &result);

    //描述：根据connect_info构造出path对象
    path_ptr construct(const connect_info &I)const;
};

GEO_NAMESPACE_END


#endif // !defined(AFX_PATH_CONNECT_H__FDB954EF_A6E0_4FB0_BFC3_36D21F847C6D__INCLUDED_)
