// path_index.h: interface for the path_index class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATH_INDEX_H__E33495E4_0687_44E9_92AB_054065615A06__INCLUDED_)
#define AFX_PATH_INDEX_H__E33495E4_0687_44E9_92AB_054065615A06__INCLUDED_

#include "path.h"
#include "spatial_index.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class reve_port_across;
class point_index;
class point_map;

class GEO_DLL path_index  
{
protected:
    path_propT<envelope>        m_path;                     //add进来的path
    path_propT<int>             m_singles;                  //所有单线的指针
    spatial_index<double>       m_segment_index;            //segment的索引
    spatial_index<double>       m_path_index;               //path*的索引
    point_index*                m_node_index;               //节点索引
    point_map*                  m_point_map;                //           
    reve_port_across*           m_port;                     //反向引用的穿越数
    const path*                 m_current;
    
    static int g_filter(void *This,int n,void *p);

    //描述：判断pt是否被当前的path反向引用
    bool is_reve(const point *pt)const;

    //描述：得到L和this的完全在L和this线段内部的交点在L上的参数
    void break_on_inner(const polyline *L,double off,std::vector<double> &para)const;
    void break_on_inner(const curve *L,double off,std::vector<double> &para)const;
    void break_on_inner(const multi_path *L,double off,std::vector<double> &para)const;
    void break_on_inner(const path *L,double off,std::vector<double> &para)const;

    //描述：判断p是否和this中某条线段或segment距离小于tol并且不在它的端点
    bool is_break_node(const point &pt,double tol)const;

    //描述：求出is_break_node的节点，将其在L上的参数加上off加入para中
    void break_on_node(const polyline *L,double tol,double off,std::vector<double> &para)const;
    void break_on_node(const curve *L,double tol,double off,std::vector<double> &para)const;
    void break_on_node(const multi_path *L,double tol,double off,std::vector<double> &para)const;
    void break_on_node(const path *L,double tol,double off,std::vector<double> &para)const;

    //描述：算出this中在L内部的线段、圆弧将它们连接成path放入out中
    void select_inner(path *L,double tol,std::vector<path_ptr> &out)const;

    //描述：store_current 构造的时候设置一个path_index的current为0，析构的时候恢复原来的设置
    struct store_current {
        const path* m_old; path_index* m_segment_index;
        store_current(path_index* L):m_segment_index(L),m_old( L->set_current(0) ){ }
        ~store_current(){ m_segment_index->set_current(m_old); }
    };

    void add_single(path *l);
    void remove_single(path *l);
    void get_current(multi_path& l)const;

    bool is_geo_close()const;

public:

    int m_dimension;

	path_index();
	virtual ~path_index();

    //描述：添加L到this中
    void add(const path *L);

    //描述：从this中删除L
    void remove(const path *L);

    //描述：计算pt和this的穿越数
    int  across(const point &pt)const;

    //描述：判断this和L是否相穿
    bool is_cross(const path *L,double tol)const;
	
    //描述：判断this是否覆盖点
    bool is_cover(const point &pt,double tol)const;
    bool is_cover(double x,double y,double tol)const{
        return is_cover(point(x,y),tol);
    }

    //描述：判断this是否和env相离，this永远是线的语义
    bool is_disjoin(const envelope& env)const;

    //描述：判断this是否和env相交，dimension是this的对象维数
    bool is_intersect(const envelope& env)const;
    
    //描述：判断this是否和L相交，dimension是this的对象维数
    bool is_intersect(const path* L,double tol)const;

    //描述：判断this是否和L相交
    bool is_intersect(const line& L,double tol)const;

    //描述：判断this是否和L相交
    bool is_intersect(const arc& L,double tol)const;

    //描述：判断this是否和L相交
    bool is_intersect(const bezier& L,double tol)const;

    //描述：判断this是否和L相交
    bool is_intersect(const pnode* L,double tol)const;

    //描述：判断this是否包含L
    bool is_cover(const path* L,double tol)const;

    //描述：判断this是否被L覆盖，dimension为this的维数
    bool is_covered(const path* L,double tol)const;

    //描述：判断L是否在线的语义上被this覆盖
    bool is_contain(const path* L,double tol)const;

    //描述：判断L是否在线的语义上和this有重叠
    bool is_lap(const path* L,double tol)const;

    //描述：求出this和L的交点在L上的参数
    int break_path(const path* L,double tol,std::vector<double>& para)const;

    //描述：用this将L打断，打断的结果存入out中
    int break_path(const path* L,double tol,std::vector<path_ptr>& out)const;

    //描述：用this将点群分块
    int break_point(const path* L,double tol,std::vector<path_ptr>& para)const;

    //描述：移动pt使得它变成this的内部点
    bool moveto_inner(point &pt,double tol)const;

    //描述：求出面L被this切割成的部分，每部分写入out中
    //参数：out中原有的数据不删除      
    int break_surface(const path *L,double tol,std::vector<path_ptr> &out)const;

    //描述：用this将L分开(根据L的对象维数调用break_path、break_point、break_surface)
    int split(const path* L,double tol,std::vector<path_ptr>& para)const;
    
    //描述：打断path并将被打断的每部分按照和this的关系放入inner、outer、border中
    //参数：inner中放入在this内部subpath，outer放入在this外部的subpath，border放入和this的边界重叠的path
    void separate_path(const path *L,double tol,
        std::vector<subpath>* inner,std::vector<subpath>* outer,std::vector<subpath>* border)const;

    //描述：设置当前的对象为L，如果传入的L不为空那么所有的查询函数都将只是计算和L的空间关系
    //      如果L为空那么又是计算和所有add进入的path的空间关系
    const path* set_current(const path *L);

    //描述：找出所有包含pt的path，将其指针放入out中
    int  n_cover(point pt,std::vector<const path*> &out)const;

    //描述：找出所有在容差tol下包含pt的path，将其指针放入out中
    int  n_cover(point pt,double tol,std::vector<const path*> &out)const;

    //描述：找出所有和env不相离的path，将其指针放入out中，这里this中的path当作线使用
    int  n_intersect(envelope env,std::vector<const path*> &out)const;

    //描述：找出所有和L不相离的path，将其指针放入out中。dimension指定this中path的维数
    int  n_intersect(const path *L,double tol,std::vector<const path*> &out)const;

    //描述：找出所有完全包含L的path，将其指针放入out中。
    int  n_cover(const path *L,double tol,std::vector<const path*> &out)const;

    //描述：找出所有被L包含的path，将其指针放入out中。dimension指定this中path的维数
    int  n_covered(const path *L,double tol,std::vector<const path*> &out)const;

    //描述：找出所有和L相穿的path，将其将其指针放入out中。
    int  n_cross(const path *L,double tol,std::vector<const path*> &out)const;
};

GEO_NAMESPACE_END


#endif // !defined(AFX_PATH_INDEX_H__E33495E4_0687_44E9_92AB_054065615A06__INCLUDED_)

