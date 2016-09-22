// path.h: interface for the path class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATH_H__885D267D_7ED2_411E_B1BE_44E149DBCD5D__INCLUDED_)
#define AFX_PATH_H__885D267D_7ED2_411E_B1BE_44E149DBCD5D__INCLUDED_

#include "point.h" 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHeap;

GEO_NAMESPACE_BEGIN

class path;
    class polyline;
    class curve;
    class multi_path;
struct path_ptr;
struct subpath;


template<class type>
struct cmp_ptr : std::binary_function<type,type,bool>
{
	bool operator()(const type *a,const type *b){ return *a<*b; }
};

inline int safe_release(const path *l);
inline int safe_addref(const path *l);

struct GEO_DLL path_ptr
{
    path *m_ptr;

    path_ptr():m_ptr(0){}
    ~path_ptr(){ safe_release(m_ptr); }
    int addref(){ return safe_addref(m_ptr); }
    int release(){ return safe_release(m_ptr); }

    inline path_ptr& reve_ptr();

    operator path*(){ return m_ptr; }
    operator const path*()const{ return m_ptr; }

    path* operator ->(){ return safe_ptr(m_ptr); }
    path* operator ->()const{ return safe_ptr(m_ptr); }

    path_ptr(path *ptr):m_ptr(ptr){ addref(); }
    path_ptr(path *ptr,int):m_ptr(ptr){}
    path_ptr& operator = (path *ptr){ safe_addref(ptr); release(); m_ptr=ptr; return *this;}
    bool operator == (const path *ptr)const{ return m_ptr==ptr; }
    bool operator != (const path *ptr)const{ return m_ptr!=ptr; }
    bool operator < (const path *ptr)const { return m_ptr<ptr; }
    bool operator <= (const path *ptr)const{ return m_ptr<=ptr; }
    bool operator > (const path *ptr)const { return m_ptr>ptr; }
    bool operator >= (const path *ptr)const{ return m_ptr>=ptr; }

	bool operator == (path *ptr)const{ return m_ptr==ptr; }
    bool operator != (path *ptr)const{ return m_ptr!=ptr; }
    bool operator < (path *ptr)const { return m_ptr<ptr; }
    bool operator <= (path *ptr)const{ return m_ptr<=ptr; }
    bool operator > (path *ptr)const { return m_ptr>ptr; }
    bool operator >= (path *ptr)const{ return m_ptr>=ptr; }

    path_ptr(const path_ptr& ptr):m_ptr( (path*)ptr.m_ptr ){ addref(); }
    path_ptr& operator = (const path_ptr ptr){ safe_addref((path*)ptr.m_ptr); release(); m_ptr = (path*)ptr.m_ptr; return *this; }
    bool operator == (const path_ptr ptr)const{ return m_ptr==ptr.m_ptr; }
    bool operator != (const path_ptr ptr)const{ return m_ptr!=ptr.m_ptr; }
    bool operator < (const path_ptr ptr)const { return m_ptr<ptr.m_ptr; }
    bool operator <= (const path_ptr ptr){ return m_ptr<=ptr.m_ptr; }
    bool operator > (const path_ptr ptr)const { return m_ptr>ptr.m_ptr; }
    bool operator >= (const path_ptr ptr)const{ return m_ptr>=ptr.m_ptr; }
};

struct GEO_DLL subpath
{
    subpath*        m_next;
    const path*     m_path;
    double          m_star,m_end;

    subpath(const path *L=0,double star=0,double end=0)
        :m_path(L),m_star(star),m_end(end),m_next(0){
    }
    void destroy();
    void simplify();
    path_ptr get_path()const;
};

class GEO_DLL path
{
    void*   m_prop_head;
    friend class path_prop;
public:
    //描述：增加引用计数
    virtual int         addref();

    //描述：减少引用计数
    virtual int         release();

    //描述：得到oracle的解释串
    virtual const int* ora_interpret()const=0;
    
    //描述：得到oracle的坐标串
    virtual const double* ora_coordinate()const=0;

	//描述：得到oracle的解释串
	virtual const int* ora_interpret(std::vector<int>& out)const=0;
    
    //描述：得到oracle的坐标串
    virtual const double* ora_coordinate(std::vector<double>& out)const=0;

    //描述：得到path的类型
    virtual int         get_type()const=0;

    //描述：判断是否是单线
    virtual bool        is_single()const;

    //描述：判断是否封闭
    virtual bool        is_close()const=0;

    //描述：判断是否纯粹由polyline组成
    virtual bool        is_polyline()const=0;

    //描述：判断this在参数t处是否反向引用单线
    virtual bool        is_reve_at(double t)const;

    //描述：在线的语义下判断是否和env相离
    virtual bool        is_disjoin(const envelope &env)const=0;

    //描述：得到最大参数
    virtual double      max_para()const=0;

    //描述：得到长度
    virtual double      length()const=0;

    //描述：得到积分面积
    virtual double      area()const=0;
    
    //描述：将this在x轴上的范围扩充到r
    virtual void    	x_range(range &r)const=0;

    //描述：将this在y轴上的范围扩充到r
    virtual void    	y_range(range &r)const=0;

    //描述：根据参数计算点的坐标
    virtual point       point_at(double t)const=0;

    //描述：如果p是this的节点，返回其在this上的参数，否则返回-1
    virtual double      find_point(const point* p)const=0;

    //描述：根据参数返回切线的角度
    virtual point       tangent_at(double t,double tol2)const=0;

    //描述：得到起点处的坐标和角度
    virtual double      get_front(point& pt)const=0;

    //描述：得到终点处的坐标和角度
    virtual double      get_back(point& pt)const=0;

    //描述：得到起点的坐标地址
    virtual point*      front_ptr()const=0;

    //描述：得到终点的坐标地址
    virtual point*      back_ptr()const=0;

    //描述：根据参数计算子线
    virtual path_ptr    path_at(double star,double end)const=0;

    //描述：将参数点内插为节点，返回后p中每个值修改为原来参数点在新的this中的参数
    virtual void        insert_at(double *p,int n)=0;
    virtual void        insert_at(std::vector<double> &para);

    //描述：得到参数t处引用的单线
    virtual const path* single_at(double &t)const{ return this; }
    void                single_at(double &t,path_ptr &l);

    //描述：返回点在this的左边还是右边，返回0表示在直线上，返回1表示左边，返回2表示右边
    virtual int         left_right(const point &pt,double tol2)const=0;

    //描述：计算pt和this的穿越数
    virtual int         across(const point &pt)const=0;

    //描述：计算pt到this最近点在this上的参数
    virtual double      nearest(const point &pt)const=0;

    //描述：计算pt和this距离的平方
    virtual double      dis2(const point &pt)const=0;
	
    //描述：删除一些结构上几何上无效的东西，返回删除后this是否是一条有效的path
    virtual bool        remove_invalid(double tol2)=0;

    //描述：改变this的坐标，使得this变成一条方向相反的path
    virtual void        reverse(void *map_=0)=0;

    //描述：深度克隆一个和this一样的对象
    virtual path_ptr    clone(void* map_=0)const=0;

    //描述：将this或this引用的非折线的对象内插成折线
    virtual void        interpolate(int num)=0;

    //描述：将this内插成折线，内插后的折线和this之间的最大距离平方不超过tol2
    virtual void        interpolate2(double tol2)=0;

    //描述：取出this每个节点到起点的长度
    virtual void        push_length(std::vector<double>& array)const=0;

    //描述：返回节点的个数
    virtual int         point_num()const=0;

    //描述：得到this和env的交点在this上的参数
	//		程序清除A中原有的数据，返回的参数按照从小到大的方式排序
    virtual int         break_by_env(const envelope& env,std::vector<double>& A)const=0;

    //描述：计算平行线，dis大于0返回的平行线在左边，dis小于0返回的平行线在右边
    virtual path_ptr    parallel(double dis)const{ return 0; }

    //描述：将this平移off
    virtual void        offset(point off)=0;

    //描述：采用dauglas压缩法压缩一条线
    virtual void        dauglas(double tol2)=0;

    //描述：保留的虚函数，用在Geometry上
//    virtual void        update(){};

public:
    enum { polyline_type,curve_type,multi_path_type };
    volatile unsigned int    m_ref;
    long long m_id;
    unsigned int    m_prop;
    union{
        double  m_dblVal;
        float   m_fltVal[2];
        int    m_lVal[2];
        short   m_iVal[4];
        char    m_cVal[8];
    };

    path();
    path(const path& l);    
    path& operator=(const path&);
    virtual ~path();
    
    //描述：得到对象维数
    int dimension()const{ return m_prop>>30; }

    //描述：设置对象维数
    void dimension(unsigned int d){ m_prop&=0x3fffffff; m_prop|=(d<<30); }

    //描述：得到连续性属性
    bool b_continue()const{ return m_prop&(1<<29)?true:false; }

    //描述：设置连续性属性
    void b_continue(bool b){ if(b)m_prop|=(1<<29);else m_prop&=~(1<<29); }

    //描述：得到封闭性属性
    bool b_close()const{ return m_prop&(1<<28)?true:false; }

    //描述：设置封闭性属性
    void b_close(bool b){ if(b)m_prop|=(1<<28);else m_prop&=~(1<<28); }

    //描述：判断this是否连续
    bool is_continue()const;

    //描述：判断是否几何封闭
    bool is_geo_close()const;

    //描述：判断this是否强封闭
    bool is_strong_close()const;

    //功能：强迫this几何上封闭
    bool force_geo_close(double tol);

    //描述：判断是一个面对象
    bool is_surface()const{ return dimension()>=2 && is_close(); }

    //描述：得到标志点
    bool get_label(point &pt,double tol)const;
    bool get_label(point &pt)const;

    //描述：根据端点参数，将this打断成多个path
    void break_at(const std::vector<double> &A,std::vector<path_ptr> &out)const;

    //描述：节点聚合
    void point_aggregate(double tol);

    //描述：将this的外接矩形扩充到env中
    void expand_envelope(envelope &env){
        x_range( env.x );
        y_range( env.y );
    }

    //描述：判断this是否和L相穿
    bool is_cross(const path *L,double tol)const;

    //描述：判断this是否覆盖pt
    bool is_cover(point pt,double tol)const;

    //描述：判断this是否覆盖L
    bool is_cover(const path *L,double tol)const;

    //描述：判断this是否满足方向良好性
    bool is_good_direct()const;

    //描述：判断this是否和env相交
    bool is_intersect(const envelope& env)const;

    //描述：判断this是否和L相交
    bool is_intersect(const path* L,double tol)const;

    //描述：判断L是否被this覆盖
    bool is_contain(const path*L, double tol)const;

    //描述：判断L和this是否有重叠(相交并且交在内部)
    //说明：根据this和L的对象维数，此函数有不同的判断语义
    bool is_overlap(const path* L,double tol)const;

    //描述：判断L和this是否相触(相交并且交在边界)
    //说明：根据this和L的对象维数，此函数有不同的判断语义
    bool is_touch(const path* L,double tol)const;

    //描述：判断L和this是否在线的语义上相等
    bool is_equal(const path*L, double tol)const;

    //描述：强迫this是否满足方向良好性
    void force_good_direct();

    //描述：计算this和L的交点在L上的参数
    void break_path(const path *L,double tol,std::vector<double> &A)const;
    
    //描述：将L用this打断，打断的各个部分写入out
    void break_path(const path *L,double tol,std::vector<path_ptr> &out)const;

    //描述：求出面L被this切割成的部分，每部分写入out中
    //参数：out中原有的数据不删除      
    void break_surface(const path* L,std::vector<path_ptr>& out)const;

    int break_by_node(std::vector<std::vector<double> > &out)const;

    //描述：得到this的所有节点地址，返回的节点按照它们在this上的参数大小排序
    void push_nodes(std::vector<point*> &A);

    //描述：得到this的所有单线的端点
    void push_port(std::vector<point*> &A);

    //描述：得到对象和点之间的距离
    double distance(point pt)const;

	//描述：得到this在env的内部区间
	//返回：A是得到的区间数组，每相邻的两个double表示一个区间
	//		程序清除A中原有的数据，返回的区间按照从小到大的方式排序
	//返回值：返回A中区间的个数
    int select_by_env(const envelope& env,std::vector<double>& A)const;

    //描述：返回一个和this几何上相同，结构上尽可能简单的path
    path_ptr make_single();

    //描述：this的所有属性设置为other一样的值(包括id,m_prop,m_dblVal等等)
    void set_prop(const path& other);

    //描述：让L的坐标都变成granularity的整数
    bool set_granularity(double granularity);

    path_ptr clean(double granularity);

    path_ptr remove_narrow_ring(double tol);
};

class GEO_DLL  path_prop
{
    path_prop(path_prop&){}
    void operator=(const path_prop&){}
protected:  
    struct item
    {
        item*               m_next;     //下一个属性单元
        path_prop*          m_parent;   //属性单元所属于的属性对象
    };
    CHeap*      m_heap;     //分配属性的堆对象

    //描述：将p所指向的变量设置为p所指向变量的值
    virtual void assign(void* p,const void* q)=0;

    //描述：如果属性元素有构造函数，请重载这个函数
    virtual void construct(void* p)=0;

    //描述：如果属性元素有析构函数，请重载这个函数
    virtual void deconstruct(void* p)=0;

    //描述：将target的属性设置为source
    void copy_prop(const path* source,path* target);

    //描述：得到item所在的const path*
    const path* get_path(item* it)const;
    
    //描述：删除v的属性单元
    bool remove_item(const path* v);

    //描述：添加一个属性单元
    item* add_item(const path* prop);

    //描述：得到obj的属性的地址
    item* find_item(const path* obj)const;

    //描述：和其它的path_prop交换
    void swap(path_prop& prop);

    //描述：删除所有的单元
    void clear();

    path_prop(int prop_size);
    virtual ~path_prop();

    friend class path;
public:

    //描述：得到所有有值的path
    std::vector<const path*> all()const;

    //描述：得到所有有值的path的个数
    int size()const;
};

template<class type>
class path_propT : public path_prop
{
    void construct(void* p){
        new (p) type(m_def); 
    }
    void deconstruct(void* p){
        ((type*)p)->~type(); 
    }
    void assign(void* p,const void* q){
        *((type*)p) = *((type*)q);
    }
    type    m_def;
public:
    path_propT(type x=type())
        :path_prop( sizeof(type) ),m_def(x){
    }
    ~path_propT(){
        clear();
    }

    const type* find(const path* v)const{
        item* x = find_item(v);
        return x?(type*)(x+1):0;
    }

    bool erase(const path* v){
        return remove_item(v);
    }

    type& operator[](const path* v)
    {
        item* x = find_item(v);
        if( x==0 )
            x = add_item( (path*)v );
        return x?*((type*)(x+1)):m_def;
    }

    const type& get(const path* v)const
    {
        const type* x = find(v);
        if( x==0 )
            return m_def;
        return *x;
    }

    void swap(path_propT<type>& X)
    {
        path_prop::swap(X);
    }
};

class GEO_DLL polyline : public path,public std::vector<point>
{
public:
    //描述：得到oracle的解释串
    virtual const int* ora_interpret()const;
    
    //描述：得到oracle的坐标串
    virtual const double* ora_coordinate()const;
	
		//描述：得到oracle的解释串
	virtual const int* ora_interpret(std::vector<int>& out)const;
    
    //描述：得到oracle的坐标串
    virtual const double* ora_coordinate(std::vector<double>& out)const;


    //描述：得到path的类型
    virtual int         get_type()const;

    //描述：判断是否纯粹由polyline组成
    virtual bool        is_polyline()const;

    //描述：判断是否封闭
    virtual bool        is_close()const;

    //描述：在线的语义下判断是否和env相离
    virtual bool        is_disjoin(const envelope &env)const;

    //描述：得到最大参数
    virtual double      max_para()const;

    //描述：得到长度
    virtual double      length()const;

    //描述：得到积分面积
    virtual double      area()const;
    
    //描述：将this在x轴上的范围扩充到r
    virtual void    	x_range(range &r)const;

    //描述：将this在y轴上的范围扩充到r
    virtual void    	y_range(range &r)const;

    //描述：如果p是this的节点，返回其在this上的参数，否则返回-1
    virtual double      find_point(const point* p)const;

    //描述：根据参数计算点的坐标
    virtual point       point_at(double t)const;

    //描述：得到起点处的坐标和角度
    virtual double      get_front(point& pt)const;

    //描述：得到终点处的坐标和角度
    virtual double      get_back(point& pt)const;

    //描述：得到起点的坐标地址
    virtual point*      front_ptr()const;

    //描述：得到终点的坐标地址
    virtual point*      back_ptr()const;

    //描述：根据参数计算子线
    virtual path_ptr    path_at(double star,double end)const;

	//描述：根据参数返回切线的角度
    virtual point       tangent_at(double t,double tol2)const;

    //描述：将参数点内插为节点，返回后p中每个值修改为原来参数点在新的this中的参数
    virtual void        insert_at(double *p,int n);

    //描述：返回点在this的左边还是右边，返回0表示在直线上，返回1表示左边，返回2表示右边
    virtual int         left_right(const point &pt,double tol2)const;

    //描述：计算pt和this的穿越数
    virtual int         across(const point &pt)const;

    //描述：计算pt到this最近点在this上的参数
    virtual double      nearest(const point &pt)const;

    //描述：计算pt和this距离的平方
    virtual double      dis2(const point &pt)const;
	
    //描述：删除一些结构上几何上无效的东西，返回删除后this是否是一条有效的path
    virtual bool        remove_invalid(double tol2);

    //描述：改变this的坐标，使得this变成一条方向相反的path
    virtual void        reverse(void *map_=0);

    //描述：深度克隆一个和this一样的对象
    virtual path_ptr    clone(void* map_=0)const;

    //描述：将this或this引用的非折线的对象内插成折线
    virtual void        interpolate(int num){ }

    //描述：将this内插成折线，内插后的折线和this之间的最大距离平方不超过tol2
    virtual void        interpolate2(double tol2){}

    //描述：取出this每个节点到起点的长度
    virtual void        push_length(std::vector<double>& array)const;

    //描述：返回节点的个数
    virtual int         point_num()const{ return size(); }

    //描述：得到this和env的交点在this上的参数
	//		程序清除A中原有的数据，返回的参数按照从小到大的方式排序
    virtual int         break_by_env(const envelope& env,std::vector<double>& A)const;

    //描述：计算平行线，dis大于0返回的平行线在左边，dis小于0返回的平行线在右边
    virtual path_ptr    parallel(double dis)const;

    //描述：将this平移off
    virtual void        offset(point off);

    //描述：采用dauglas压缩法压缩一条折线
    virtual void        dauglas(double tol2);

public:
    polyline();
    polyline(const polyline &l);
    virtual ~polyline();

    //描述：构造一个等价于矩形的polyline对象
    void construct_by_envelope(const envelope &env);

    //描述：判断this是否在几何上相当于一个矩形
    bool is_envelope()const;

    //描述：返回参数t所在的线段地址，返回后的参数修改为原参数点在线段上的参数
    point* segment_at(double &t)const;

    //描述：将一条折线添加到this的尾部
    void append(const polyline *l);

    //描述：添加一条线段
    void line_to(const point& pt){ push_back(pt); }

    //描述：找到this中离pt最近的点，返回其地址
    const point* nearest_point(const point& pt)const;

    //描述：得到折线的形状权
    void get_shape_weight(std::vector<int>& weight)const;

	//描述：消除自相交的情况
	void remove_self_cross();

    //描述：让this成为线a和pt的参数为t的中间线
    void midline(const polyline& a,point pt,double t);

    //描述：让this成为a,b的中间线
    //参数：t为中间参数，如果t=0则this将变成a，如果t=1则this将变成b，否则this将变成a,b参数为t的线
    void midline(const polyline& a,const polyline& b,double t);
};

class GEO_DLL curve : public path,public std::vector<pnode>
{
public:
    //描述：得到oracle的解释串
    virtual const int* ora_interpret()const;
    
    //描述：得到oracle的坐标串
    virtual const double* ora_coordinate()const;

		//描述：得到oracle的解释串
	virtual const int* ora_interpret(std::vector<int>& out)const;
    
    //描述：得到oracle的坐标串
    virtual const double* ora_coordinate(std::vector<double>& out)const;


    //描述：得到path的类型
    virtual int         get_type()const;

    //描述：判断是否纯粹由polyline组成
    virtual bool        is_polyline()const;

    //描述：判断是否封闭
    virtual bool        is_close()const;

    //描述：在线的语义下判断是否和env相离
    virtual bool        is_disjoin(const envelope &env)const;

    //描述：得到最大参数
    virtual double      max_para()const;

    //描述：得到长度
    virtual double      length()const;

    //描述：得到积分面积
    virtual double      area()const;
    
    //描述：将this在x轴上的范围扩充到r
    virtual void    	x_range(range &r)const;

    //描述：将this在y轴上的范围扩充到r
    virtual void    	y_range(range &r)const;

    //描述：如果p是this的节点，返回其在this上的参数，否则返回-1
    virtual double      find_point(const point* p)const;

    //描述：根据参数计算点的坐标
    virtual point       point_at(double t)const;

    //描述：根据参数返回切线的角度
    virtual point       tangent_at(double t,double tol2)const;

    //描述：得到起点处的坐标和角度
    virtual double      get_front(point& pt)const;

    //描述：得到终点处的坐标和角度
    virtual double      get_back(point& pt)const;

    //描述：得到起点的坐标地址
    virtual point*      front_ptr()const;

    //描述：得到终点的坐标地址
    virtual point*      back_ptr()const;

    //描述：根据参数计算子线
    virtual path_ptr    path_at(double star,double end)const;

    //描述：将参数点内插为节点，返回后p中每个值修改为原来参数点在新的this中的参数
    virtual void        insert_at(double *p,int n);

    //描述：返回点在this的左边还是右边，返回0表示在直线上，返回1表示左边，返回2表示右边
    virtual int         left_right(const point &pt,double tol2)const;

    //描述：计算pt和this的穿越数
    virtual int         across(const point &pt)const;

    //描述：计算pt到this最近点在this上的参数
    virtual double      nearest(const point &pt)const;

    //描述：计算pt和this距离的平方
    virtual double      dis2(const point &pt)const;
	
    //描述：删除一些结构上几何上无效的东西，返回删除后this是否是一条有效的path
    virtual bool        remove_invalid(double tol2);

    //描述：改变this的坐标，使得this变成一条方向相反的path
    virtual void        reverse(void *map_=0);

    //描述：深度克隆一个和this一样的对象
    virtual path_ptr    clone(void* map_=0)const;

    //描述：将this或this引用的非折线的对象内插成折线
    virtual void        interpolate(int num);

    //描述：将this内插成折线，内插后的折线和this之间的最大距离平方不超过tol2
    virtual void        interpolate2(double tol2);

    //描述：取出this每个节点到起点的长度
    virtual void        push_length(std::vector<double>& array)const;

    //描述：返回节点的个数
    virtual int         point_num()const{ return size(); }

    //描述：得到this和env的交点在this上的参数
	//		程序清除A中原有的数据，返回的参数按照从小到大的方式排序
    virtual int         break_by_env(const envelope& env,std::vector<double>& A)const;

    //描述：计算平行线，dis大于0返回的平行线在左边，dis小于0返回的平行线在右边
    virtual path_ptr    parallel(double dis)const;

    //描述：将this平移off
    virtual void        offset(point off);

    //描述：采用dauglas压缩法压缩一条折线
    virtual void        dauglas(double tol2);

public:
    curve();
    curve(const curve &l);
    curve(const polyline &l);
    virtual ~curve();

    //描述：返回参数t所在的线段地址，返回后的参数修改为原参数点在线段上的参数
    pnode* segment_at(double &t)const;

    //描述：将一条线添加到this的尾部
    void append(const polyline *l);
    void append(const curve *l);
    void append(const path *l);
    void append(const pnode *l);    

    //描述：构造一个描述圆的curve
    void construct_by_circle(point o,double r);
    void construct_by_circle(point a,point b,point c);

    //描述：构造一个椭圆
    //参数：radius是椭圆的x轴和y轴的半径，angle是椭圆的旋转角度，
    //      tol2是拟合的贝赛尔曲线和椭圆的容差，小于等于0则使用四段贝赛尔曲线拟合
    //返回：一个用贝赛尔曲线拟合的以原点为圆心的椭圆。
    void construct_by_ellipse(point radius,double angle=0,double tol2=0);

    //描述：在this的尾部添加一条折线 (n是此polyline的点的个数)
    void add_polyline(const point *p,int n);

    //描述：在this的尾部添加一条多段圆弧 (n是此polyarc的点的个数)
    void add_polyarc(const point *p,int n);

    //描述：在this的尾部添加一条多段贝赛尔曲线 (n是此polybezier的点的个数)
    void add_polybezier(const point *p,int n);

    //描述：判断this是否完全由圆弧组成
    bool is_polyarc()const;
    
    //描述：判断this是否完全由贝赛尔曲线组成
    bool is_polybezier()const;

    //描述：判断每个pnode的m_type是否正确
    bool is_good_pnode_sequence()const;

    //描述：添加一条线段
    void line_to(point pt);

    //描述：添加一条圆弧
    void arc_to(point a,point b);

    //描述：添加一条贝赛尔曲线
    void bezier_to(point a,point b,point c);

    //描述：添加一条B样条曲线(实际上使用贝赛尔曲线拟合B样条曲线)
    //参数：拟合的曲线和真实曲线距离平方不超过tol2，如果tol2小于等于0，那么每个样条分段固定使用一条贝赛尔曲线
    void spline_to(const point* it,int n,double tol2=0);

    //描述：将this中的贝赛尔曲线内插成圆弧
    //参数：tol2用来控制内插的精度，也就是内插前后两条线之间最大距离平方(如果tol2给的过小，程序不保证内插前后的最大距离小于tol2)
    void bezier_to_arc(double tol2);

    //描述：将this中的圆弧贝内插成赛尔曲线
    //参数：tol2用来控制内插的精度，也就是内插前后两条线之间最大距离平方(如果tol2给的过小，程序不保证内插前后的最大距离小于tol2)
    void arc_to_bezier(double tol2);

    //描述：拟合一条光滑曲线
    //算法：拟合出来的曲线经过it中各个点
    void smooth1(const point* it,int n);

    //描述：拟合一条光滑曲线
    //算法：拟合出来的曲线经过it中各个线段的终点
    void smooth2(const point* it,int n);
};

class GEO_DLL multi_path : public path,public std::vector<path_ptr>
{
    std::vector<double>     m_map_para; //如果这个变量被正确设置，可以大大加快sub_at,single_at的执行速度
public:
    //描述：得到oracle的解释串
    virtual const int* ora_interpret()const;
    
    //描述：得到oracle的坐标串
    virtual const double* ora_coordinate()const;

		//描述：得到oracle的解释串
	virtual const int* ora_interpret(std::vector<int>& out)const;
    
    //描述：得到oracle的坐标串
    virtual const double* ora_coordinate(std::vector<double>& out)const;


    //描述：得到path的类型
    virtual int         get_type()const{ return multi_path_type; }

    //描述：判断是否是单线
    virtual bool        is_single()const{ return false; }

    //描述：判断是否封闭
    virtual bool        is_close()const;

    //描述：判断this在参数t处是否反向引用单线
    virtual bool        is_reve_at(double t)const;

    //描述：判断是否纯粹由polyline组成
    virtual bool        is_polyline()const;

    //描述：在线的语义下判断是否和env相离
    virtual bool        is_disjoin(const envelope &env)const;

    //描述：得到最大参数
    virtual double      max_para()const;

    //描述：得到长度
    virtual double      length()const;

    //描述：得到积分面积
    virtual double      area()const;
    
    //描述：将this在x轴上的范围扩充到r
    virtual void    	x_range(range &r)const;

    //描述：将this在y轴上的范围扩充到r
    virtual void    	y_range(range &r)const;

    //描述：如果p是this的节点，返回其在this上的参数，否则返回-1
    virtual double      find_point(const point* p)const;

    //描述：根据参数计算点的坐标
    virtual point       point_at(double t)const;

    //描述：根据参数返回切线的角度
    virtual point       tangent_at(double t,double tol2)const;

    //描述：得到起点处的坐标和角度
    virtual double      get_front(point& pt)const;

    //描述：得到终点处的坐标和角度
    virtual double      get_back(point& pt)const;

    //描述：得到起点的坐标地址
    virtual point*      front_ptr()const;

    //描述：得到终点的坐标地址
    virtual point*      back_ptr()const;

    //描述：得到参数t处引用的单线
    virtual const path* single_at(double &t)const;

    //描述：根据参数计算子线
    virtual path_ptr    path_at(double star,double end)const;

    //描述：将参数点内插为节点，返回后p中每个值修改为原来参数点在新的this中的参数
    virtual void        insert_at(double *p,int n);

    //描述：返回点在this的左边还是右边，返回0表示在直线上，返回1表示左边，返回2表示右边
    virtual int         left_right(const point &pt,double tol2)const;

    //描述：计算pt和this的穿越数
    virtual int         across(const point &pt)const;

    //描述：计算pt到this最近点在this上的参数
    virtual double      nearest(const point &pt)const;

    //描述：计算pt和this距离的平方
    virtual double      dis2(const point &pt)const;
	
    //描述：删除一些结构上几何上无效的东西，返回删除后this是否是一条有效的path
    virtual bool        remove_invalid(double tol2);

    //描述：改变this的坐标，使得this变成一条方向相反的path
    virtual void        reverse(void *map_=0);

    //描述：深度克隆一个和this一样的对象
    virtual path_ptr    clone(void* map_=0)const;

    //描述：将this或this引用的非折线的对象内插成折线
    virtual void        interpolate(int num);

    //描述：将this内插成折线，内插后的折线和this之间的最大距离平方不超过tol2
    virtual void        interpolate2(double tol2);

    //描述：取出this每个节点到起点的长度
    virtual void        push_length(std::vector<double>& array)const;

    //描述：返回节点的个数
    virtual int         point_num()const;

    //描述：得到this和env的交点在this上的参数
	//		程序清除A中原有的数据，返回的参数按照从小到大的方式排序
    virtual int         break_by_env(const envelope& env,std::vector<double>& A)const;

    //描述：计算平行线，dis大于0返回的平行线在左边，dis小于0返回的平行线在右边
    virtual path_ptr    parallel(double dis)const;

    //描述：将this平移off
    virtual void        offset(point off);

    //描述：采用dauglas压缩法压缩一条折线
    virtual void        dauglas(double tol2);

public:
    multi_path();
    multi_path(const multi_path &l);
    virtual ~multi_path();

    //描述：得到参数t在this上的引用序号
    int                 sub_at(double &t)const;

    //描述：将this中的单线按照是否完全重叠分类
    //返回：假如x是this中的一个直接引用，如果x是一个multi_path
    //那么x中的子path将都是单线，并且这些单线都互相精确重叠
    void                group_by_equal();

    //描述：消除结构上的分段
    void                remove_break();

    //描述：对this的每个multi_path的直接引用调用remove_break
    void                remove_break1();

    //描述：连接排序，使得相连的引用排在一起
    void                connect(bool care_direct,double tol=0);

    //描述：强制this强封闭
    bool                force_strong_close(double tol);

    //描述：使得this
    int                 make_simply_surface();

    //描述：清除悬挂线
    void                clear_suspension(std::vector<path_ptr> *A=0);

    //描述：将this分离成多个单外圈的面，this必须满足封闭性，否则立即返回0
    //      调用此函数之前this可能包含多个外圈，这些外圈和它们内部的内圈的排列可能没有规则
    //      调用此函数之后，this将被组织成多个单外圈的面的集合
    //返回：this可以被分离成的单外圈面的个数
    int                 surface_isolate();

    //描述：生成m_map_para中的数据
    void                map_para_create();

    //描述：清除m_map_para中的数据
    void                map_para_clear(){ m_map_para.clear(); }

    void                append(const std::vector<const path*>& A);
    void                append(const std::vector<path_ptr>& A);
};

inline path_ptr& path_ptr::reve_ptr(){
	m_ptr = GEO_NAMESPACE::reve_ptr(m_ptr);
    return *this;
}

inline bool safe_cmp_ptr(const void *a,const void *b){    
    return a<b;
}

inline int safe_addref(const path *l){
    if( 0==(l=safe_ptr(l)) )
        return 0;
    return ((path*)l)->addref();
}

inline int safe_release(const path *l){
    if( 0==(l=safe_ptr(l)) )
        return 0;
    return ((path*)l)->release();
}

inline bool safe_equal_ptr(const void *a,const void *b){
    return (((long long)a)^((long long)b))<2;
}

inline bool safe_is_single(const path *l){
    return l? safe_ptr(l)->is_single():true;
}

inline void safe_x_range(const path *l,range &r){
    if( l=safe_ptr(l) ) l->x_range(r);
}

inline void safe_y_range(const path *l,range &r){
    if( l=safe_ptr(l) ) l->y_range(r);
}

inline int safe_get_type(const path *l){
    return l? safe_ptr(l)->get_type() : path::polyline_type;
}

inline bool safe_is_polyline(const path *l){
    return l? safe_ptr(l)->is_polyline():true;
}

inline int safe_point_num(const path *l){
    return l? safe_ptr(l)->point_num():0;
}

inline bool safe_is_continue(const path *l){
    return l? safe_ptr(l)->is_continue():true;
}

inline bool safe_is_close(const path *l){
    return l? safe_ptr(l)->is_close():true;
}

inline bool safe_is_disjoin(const path *l,const envelope &env){
    return l? safe_ptr(l)->is_disjoin(env):true;
}

inline double safe_max_para(const path *l){
    return l? safe_ptr(l)->max_para():0;
}

inline double safe_length(const path *l){
    return l? safe_ptr(l)->length():0;
}

inline double safe_area(const path *l){
    if( is_marked(l) ) return -safe_ptr(l)->area();
    return l? l->area():0;
}

inline double safe_dis2(const path *l,const point &pt){
    return l? safe_ptr(l)->dis2(pt):DBL_MAX;
}

inline bool safe_remove_invalid(path *l,double tol2){
    if( 0==(l=safe_ptr(l)) ) return false;
    return l->remove_invalid(tol2);
}

inline void safe_reverse(path *l,void *map_=0){
	if(l!=0) safe_ptr(l)->reverse(map_);
}

inline path_ptr safe_clone(const path *l,void *map_=0){
    if( l==0 ) return 0;
    if( !is_marked(l) ) return l->clone(map_);
    return safe_ptr(l)->clone(map_).reve_ptr();
}

inline void safe_interpolate(path *l,int num){
    if( l=safe_ptr(l) ) l->interpolate(num);
}

inline void safe_offset(path *l,point off){
    if( l=safe_ptr(l) ) l->offset(off);
}

inline void safe_interpolate2(path *l,double tol2){
    if( l=safe_ptr(l) ) l->interpolate2(tol2);
}

inline double safe_get_front(const path *l,point &pt){
    if( l==0 ) return 4*PI;
    if( !is_marked(l) ) return l->get_front(pt);
    return safe_ptr(l)->get_back(pt);
}

inline double safe_get_back(const path *l,point &pt){
    if( l==0 ) return 4*PI;
    if( !is_marked(l) ) return l->get_back(pt);
    return safe_ptr(l)->get_front(pt);
}

inline point* safe_front_ptr(const path *l){
    if( l==0 ) return 0;
    if( !is_marked(l) ) return l->front_ptr();
    return safe_ptr(l)->back_ptr();
}

inline point* safe_back_ptr(const path *l){
    if( l==0 ) return 0;
    if( !is_marked(l) ) return l->back_ptr();
    return safe_ptr(l)->front_ptr();
}
    
inline int safe_across(const path *l,const point &pt){
    if( l==0 ) return 0;
    if( !is_marked(l) ) return l->across(pt);
    return -safe_ptr(l)->across(pt);
}
    
inline double safe_nearest(const path *l,const point &pt){
    if( l==0 ) return 0;
    if( !is_marked(l) ) return l->nearest(pt);
    l = safe_ptr(l);
    return l->max_para() - l->nearest(pt);
}

inline const path* safe_single_at(const path *l,double &t){
    if( l==0 ) return 0;
    if( !is_marked(l) ) return l->single_at(t);
    l = safe_ptr(l);
    t = l->max_para()-t;
    return l->single_at(t);
}

inline double safe_find_point(const path* l,const point* p){
    if( l==0 ) return -1;
    if( !is_marked(l) ) return l->find_point(p);
    l = safe_ptr(l);
    double t = l->find_point(p);
    return t==-1 ? -1:l->max_para()-t;
}

inline bool safe_is_reve_at(const path *l,double t){
    if( l==0 ) return false;
    if( !is_marked(l) ) return l->is_reve_at(t);
    l = safe_ptr(l);
    t = l->max_para()-t;
    return !(l->is_reve_at(t));
}

inline int safe_left_right(const path *l,const point &pt,double tol2){
    if( l==0 ) return 0;
    if( !is_marked(l) ) return l->left_right(pt,tol2);
    l = safe_ptr(l);
    static const int lr[]={0,2,1};
    return lr[l->left_right(pt,tol2)];
}

inline point safe_point_at(const path *l,double t){
    if( l==0 ) return point(0,0);
    if( !is_marked(l) ) return l->point_at(t);
    l = safe_ptr(l);
    return l->point_at( l->max_para()-t );
}

inline point safe_tangent_at(const path *l,double t,double tol2){
    if( l==0 ) return point(0,0);
    if( !is_marked(l) ) return l->tangent_at(t,tol2);
    l = safe_ptr(l);
    return l->tangent_at( l->max_para()-t,tol2 );
}

inline bool safe_get_label(const path *l,point &pt,double tol){
    if( 0==(l=safe_ptr(l)) ) return false;
    return l->get_label(pt,tol);
}

inline void safe_dauglas(path* l,double tol2){
    if( l=safe_ptr(l) )  l->dauglas(tol2);
}

inline bool is_polyline_type(const path *l){ return safe_get_type(l)==path::polyline_type; }
inline bool is_curve_type(const path *l){ return safe_get_type(l)==path::curve_type; }
inline bool is_multi_path_type(const path *l){ return safe_get_type(l)==path::multi_path_type; }

//描述：可以传入反向指针的path_at函数
GEO_DLL path_ptr safe_path_at(const path *l,double star,double end);

//描述：得到L和env的交点在L上的参数
//		程序清除A中原有的数据，返回的参数按照从小到大的方式排序
GEO_DLL int safe_break_by_env(const path*L,const envelope& env,std::vector<double>& A);

//描述：可以传入反向指针的insert_at函数
GEO_DLL void safe_insert_at(path *l,double *p,int n);
inline  void safe_insert_at(path *l,std::vector<double> &t){ safe_insert_at( l,&t[0],t.size() ); }

//描述：可以传入反向指针的push_length函数
GEO_DLL void safe_push_length(const path *l,std::vector<double>& array);

//描述：将l中的贝赛尔曲线内插成圆弧，程序保证内插前后两条线之间最大距离平方不超过tol2
GEO_DLL void safe_bezier_to_arc(path *l,double tol2);

//描述：遍历l中的单线对象
//参数：fun为回调函数，遍历的时候如果发现一个单线对象就调用一次fun，如果fun返回false则结束遍历返回false，否则继续遍历，遍历完之后返回true
//      data为传给fun的信息。
GEO_DLL bool travel_single(path *l,bool (*fun)(void*,path*),void* data);

GEO_DLL bool travel_segment(path *l,bool (*fun)(void*,point*),void* data);

GEO_DLL bool travel_segment_ex(path *l,bool (*fun)(void*,point*,path*),void* data);

GEO_DLL bool travel_point(path *l,bool (*fun)(void*,point*),void* data);

template<class A,class B> void parse_data(void* p,A&a,B&b){ a=((A*)p)[0]; b=((B*)p)[1]; }
template<class A,class B,class C> void parse_data(void* p,A&a,B&b,C&c){ a=((A*)p)[0]; b=((B*)p)[1]; c=((C*)p)[2]; }
template<class A,class B,class C,class D> void parse_data(void* p,A&a,B&b,C&c,D&d){ a=((A*)p)[0]; b=((B*)p)[1]; c=((C*)p)[2]; d=((D*)p)[3]; }
template<class A,class B,class C,class D,class E> void parse_data(void* p,A&a,B&b,C&c,D&d,E&e){ a=((A*)p)[0]; b=((B*)p)[1]; c=((C*)p)[2]; d=((D*)p)[3]; e=((E*)p)[4]; }

GEO_DLL void get_single(const path *l,std::vector<const path*> &out);
GEO_DLL void get_single(path *l,std::vector<path_ptr> &out);
GEO_DLL void get_segment(path *l,std::vector<point*> &out);

//描述：计算解释串中有效三元组的个数
//参数：interpret必须是SDO_TYPE以0为结尾的解释串
GEO_DLL int ora_interpret_num(const int *interpret);

//描述：计算解释串中蕴涵的坐标个数
//参数：interpret必须是SDO_TYPE以0为结尾的解释串
GEO_DLL int ora_coordinate_num(const int *interpret);

//描述：根据解释串和相应的坐标串创建一个path对象
//参数：interpret必须是SDO_TYPE以0为结尾的解释串
GEO_DLL path_ptr ora_create_path(const int *interpret,const double *coordinate);

//描述：根据解释串和相应的坐标串创建一个path对象
//参数：interpret可以不是SDO_TYPE以0为结尾的解释串，interpret_num给出这个解释串的长度，coordinate_num给出坐标串的长度
GEO_DLL path_ptr ora_create_path(int interpret_num,const int *interpret,int coordinate_num,const double *coordinate);

//描述：得到l生成oracle格式时，坐标串中蕴涵的点的个数
GEO_DLL int ora_point_num(const path *l);

//描述：得到l的解释串，传入的l可以是反向指针
GEO_DLL const int* safe_ora_interpret(const path *l);

//描述：得到l的坐标串，传入的l可以是反向指针
GEO_DLL const double* safe_ora_coordinate(const path *l);

//描述：得到l的解释串，传入的l可以是反向指针
const int* safe_ora_interpret(const path *l,std::vector<int>& v);

//描述：得到l的坐标串，传入的l可以是反向指针
const double* safe_ora_coordinate(const path *l,std::vector<double>& v);

template<class type> void push_back(std::vector<type> *A,type a){ if(0!=A) A->push_back(a); }
template<class type> void append(std::vector<type> &A,const std::vector<type> &B){ A.insert( A.end(),B.begin(),B.end() ); }

//描述：根据push_length得到的信息将参数换算成长度
GEO_DLL double para_to_length(const std::vector<double> &A,double t);

//描述：根据push_length得到的信息将长度换算成参数
GEO_DLL double length_to_para(const std::vector<double> &A,double l);

inline path_ptr subpath::get_path()const{ return safe_path_at(m_path,m_star,m_end); }

//描述：将path保存到一段内存中
//参数：mem保存的内存，space是mem中可以存放的字节数
//返回：保存l需要用的字节数目
GEO_DLL int save(path_ptr l,void* mem,int space);

//描述：从内存中恢复path
GEO_DLL void load(path_ptr& l,void* mem,int space);

//在进行面的相交、相异运算时，是否将计算结果中的狭长面、线忽略掉  shiyj
GEO_DLL void surface_operator_ignore_narrow(bool *bIsIgnoer);
//

GEO_DLL bool surface_union(const path *a,const path *b,std::vector<subpath> &para);
GEO_DLL bool surface_intersect(const path *a,const path *b,std::vector<subpath> &para);
GEO_DLL bool surface_difference(const path *a,const path *b,std::vector<subpath> &para);
GEO_DLL bool surface_sym_difference(const path *a,const path *b,std::vector<subpath> &para);

GEO_DLL path_ptr surface_construct(std::vector<subpath> &para);
GEO_DLL path_ptr surface_union(const path *a,const path *b);
GEO_DLL path_ptr surface_intersect(const path *a,const path *b);
GEO_DLL path_ptr surface_difference(const path *a,const path *b);
GEO_DLL path_ptr surface_sym_difference(const path *a,const path *b);

GEO_DLL bool set_surface_prop(path *L,bool b_surface=true);

//描述：根据三维的坐标串解释串创建path对象
//返回：返回丢弃z值的path对象
GEO_DLL path_ptr ora_create_path_3d(int interpret_num,const int *interpret,int coordinate_num,const double *coordinate);

//描述：将二维的解释串转成三维的解释串
GEO_DLL void ora_3d_interpret(int interpret_num,int *interpret);

//描述：将二维坐标串转成三维的坐标串
//参数：ptn点的个数
//		xy二维的坐标串(double的个数为2*ptn)
//		xyz三维的坐标串(double的个数为3*ptn)
//		此参数即是输出参数，又是输入的参数，作为输入它的xyz保留了原始的xyz信息
GEO_DLL void ora_3d_coordinate(int ptn,const double* xy,double* xyz);

//描述: 设置面拓扑运算时的容差值和规则
//参数: *mode容差规则,1使用user,2使用min(auto,user),3使用max(auto,user),缺省使用auto
//		函数返回后*mode得到之前的设置
//		*user是用户设置的容差值,函数返回后*user得到之前的设置
//      auto是程序根据面的外接矩形的周长乘与0.1^7的到的值
GEO_DLL void surface_top_tol_set(int* mode,double* user);


GEO_DLL const point** convex_hull(const point** F,const point** L);

GEO_NAMESPACE_END


#endif // !defined(AFX_PATH_H__885D267D_7ED2_411E_B1BE_44E149DBCD5D__INCLUDED_)
 