// path_set.h: interface for the path_set class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATH_SET_H__416D6B30_27CC_4322_B521_0B8128F663BD__INCLUDED_)
#define AFX_PATH_SET_H__416D6B30_27CC_4322_B521_0B8128F663BD__INCLUDED_

#include "path.h"
#include "spatial_index.h"
#include <deque>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

//path_set的作用是为大数据量的path对象提供内存调度、空间查询等方法
class querist;
class single_surface_index;

class GEO_DLL path_set
{
protected:
    bool                                m_own;      //是否在析构的时候fclose(m_file)
    FILE*                               m_file;     //引用的文件
    std::vector<fpos_t>                 m_posA;     //各个path在m_file中的位置
    multi_path                          m_all;      //所有的path对象，它们中最多只能有m_n_cache个同时不为0
    int                                m_n_cache;  //允许最多同时在内存中path的个数
    std::deque<int>                    m_cache;    //在内存中的path的序号
    spatial_index<double>               m_spi;      //m_spi以每个path的外接矩形索引着所有对象的序号(无论此对象是否在内存中)
    std::vector<envelope>               m_envA;     //每个path对象的外接矩形
    std::vector<single_surface_index*>  m_ssiA;     //每个path对象的索引
    std::vector<point>                  m_labelA;   //每个path的标志点

    //描述：将在内存中的一部分path写入到m_file中
    //保证有足够的空间用于添加或装入新的path
    void perpare_memory();

    //描述：保证所有数据都在m_spi中有索引
    void perpare_spi();

    //描述：得到第i个path的索引
    single_surface_index* ssi_at(int i);

    //描述：空间查询判断
    bool is_equal(int i,const querist& Q,double tol);
    bool is_cover(int i,const querist& Q,double tol);
    bool is_covered(int i,const querist& Q,double tol);
    bool is_touch(int i,const querist& Q,double tol);
    bool is_intersect(int i,const querist& Q,double tol);
    bool is_overlap(int i,const querist& Q,double tol);
    bool is_cross(int i,const querist& Q,double tol);

    typedef bool (path_set::*query_fun)(int i,const querist& Q,double tol);
    
    //描述：得到this中一个和Q有某种关系的对象
    //返回：有这种关系的对象的序号,如果返回-1表示不存在这种对象
    int query(const querist& Q,double tol,query_fun fun);

    //描述：得到this中所有和Q有某种关系的对象
    //返回：out是有这种关系的对象的序号
    void query(const querist& Q,double tol,std::vector<int>& A,query_fun fun);
public:
    enum query_mode
    {
        use_path=0,
        use_envelope=1,
        use_label=2
    }m_query_mode;

    //构造path_set对象必须指定一个path文件
    //开始的时候对象会把文件中的所有path对象索引起来
    path_set(FILE* file,bool own=true);
	virtual ~path_set();

    FILE* get_file(){ return m_file; }

    //设置fclose(m_file)的权利
    bool own()const{ return m_own; }
    void own(bool b){ m_own=b; }

    int n_cache()const{ return m_n_cache; }
    void n_cache(int n){ m_n_cache=n; }

    //描述：添加一个path对象
    void add(const path* l);

    //描述：返回总共的path的个数
    int size()const{ return m_all.size(); }

    //描述：根据序号得到path
    virtual path_ptr path_at(int i);

    //描述：根据序号得到path的外接矩形
    const envelope* env_at(int i);

    //描述：根据序号得到path的标志点
    const point*    label_at(int i);

    //描述：得到this中一个和Q有某种关系的对象
    //返回：有这种关系的对象的序号,如果返回-1表示不存在这种对象
    int equal(const querist& Q,double tol){ return query(Q,tol,&GEO_NAMESPACE::path_set::is_equal); }
    int cross(const querist& Q,double tol){ return query(Q,tol,&GEO_NAMESPACE::path_set::is_cross); }
    int touch(const querist& Q,double tol){ return query(Q,tol,&GEO_NAMESPACE::path_set::is_touch); }
    int overlap(const querist& Q,double tol){ return query(Q,tol,&GEO_NAMESPACE::path_set::is_overlap); }
    int cover(const querist& Q,double tol){ return query(Q,tol,&GEO_NAMESPACE::path_set::is_cover); }
    int covered(const querist& Q,double tol){ return query(Q,tol,&GEO_NAMESPACE::path_set::is_covered); }
    int intersect(const querist& Q,double tol){ return query(Q,tol,&GEO_NAMESPACE::path_set::is_intersect); }

    //描述：得到this中所有和Q有某种关系的对象
    //返回：out是有这种关系的对象的序号
    void equal(const querist& Q,double tol,std::vector<int>& out){ query(Q,tol,out,&GEO_NAMESPACE::path_set::is_equal); }
    void cross(const querist& Q,double tol,std::vector<int>& out){ query(Q,tol,out,&GEO_NAMESPACE::path_set::is_cross); }
    void touch(const querist& Q,double tol,std::vector<int>& out){ query(Q,tol,out,&GEO_NAMESPACE::path_set::is_touch); }
    void overlap(const querist& Q,double tol,std::vector<int>& out){ query(Q,tol,out,&GEO_NAMESPACE::path_set::is_overlap); }
    void cover(const querist& Q,double tol,std::vector<int>& out){ query(Q,tol,out,&GEO_NAMESPACE::path_set::is_cover); }
    void covered(const querist& Q,double tol,std::vector<int>& out){ query(Q,tol,out,&GEO_NAMESPACE::path_set::is_covered); }
    void intersect(const querist& Q,double tol,std::vector<int>& out){ query(Q,tol,out,&GEO_NAMESPACE::path_set::is_intersect); }
};

GEO_NAMESPACE_END

#endif // !defined(AFX_PATH_SET_H__416D6B30_27CC_4322_B521_0B8128F663BD__INCLUDED_)
