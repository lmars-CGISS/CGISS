// analysis.h: interface for the analysis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSIS_H__04155CA8_5917_4335_A422_804A321FBB16__INCLUDED_)
#define AFX_ANALYSIS_H__04155CA8_5917_4335_A422_804A321FBB16__INCLUDED_

#include "path.h"
#include "spatial_index.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class progress;
class path_index;

//线段文件：一个文件如果它以(x1,y1,x2,y2),(x1,y1,x2,y2),…的方式保存线段，那么我们称此文件的格式为线段文件
//利用线段文件也可以保存点，方法是里面的线段的第二个点精确的等于第一个点

//analysis提供海量数据的空间分析功能
class GEO_DLL analysis  
{
    static int mm;

    class BR;
    class BS;
    class CONNECT;
    class CONNECT_EX;
    class SORT;
    class UNION;
    class SPLIT;
    class CLEAN;
    class QUERY;
    class HUGE_UNION;
    class GET_OVERLAP;
    class GET_NEAR_LINE;
    class GET_BREAK_POINT;

    friend class BR;
    friend class BS;
    friend class CLEAN;
    friend class QUERY;
    friend class SPLIT;
    friend class CONNECT;
    friend class CONNECT_EX;
    friend class UNION;
    friend class HUGE_UNION;
    friend class GET_OVERLAP;
    friend class GET_NEAR_LINE;
    friend class GET_BREAK_POINT;

	//描述：去除l的单线每个单线继承l的m_id
	static void fetch_single(path* l,std::vector<path_ptr>& A);

	//描述：对A中的每一个multi_path，取出它的单线替换为原来的multi_path
	static void remove_multi(std::vector<path_ptr>& A);

    //描述：对A中的每一个path设置它的dimension为d
	static void set_dimension(std::vector<path_ptr>& A,int d);
    
    //描述：从文件中读取path到A中
    static bool read_pathA(FILE* fn,std::vector<path_ptr>& A,progress prg);

    //描述：对in中的line，如果被env包含则写入f1中，否则写入f2中
    static bool apart_line(FILE *in,FILE* f1,FILE* f2,envelope env,progress prg);

    //描述：对in中的path，如果被env包含则写入f1中，否则写入f2中
    static bool apart_by_env(FILE *in,FILE* f1,FILE* f2,envelope env,progress prg);

    //描述：对in中的path，如果和env[i]相交写入out[i]中
    static bool apart_by_env2(FILE* in,int n,FILE** out,envelope* env,progress prg);

    //描述：对in中的path，取出它们的single写入out中
    static bool write_single(FILE* in,FILE* out,progress prg);

    //描述：得到文件中所有几何对象的env的并
    static bool get_env(FILE *in,envelope& env);

    //描述：根据udv值的大小对A中的path_path排序
    void sort_mem(multi_path& A,progress prg);

    //描述：根据udv值的大小对in中的path_path排序结果输出到out，min_v,max_v是in中udv最大和最小的值
    bool sort_file(FILE* in,FILE* out,double min_v,double max_v,progress prg);

    //描述：将path文件中的线段写入到线段文件中
    //参数：env是所有path外接矩形的并
    //注意：函数返回的时候会fclose(pathfile)而不会fclose(linefile)
    bool write_line(FILE* pathfile,FILE* linefile,envelope& env,progress prg);

public:
    typedef void (*prg_callback_type)(void* hint,double per);
    prg_callback_type       m_prg;
    void*                   m_prg_data;
	
	typedef bool (*cancel_callback_type)(void* hint);
	cancel_callback_type	m_cancel;
    void*                   m_cancel_data;

    typedef void (*set_path_callback_type)(path* l,void* hint);
    set_path_callback_type  m_set_path;
    void*                   m_set_path_data;

    typedef double (*udv_callback_type)(const path* l,void* hint);
    udv_callback_type       m_udv;
    void*                   m_udv_data;

    double                  m_tolerance;

	analysis();
	virtual ~analysis();

    virtual void    on_progress(double per);
	virtual bool    is_cancel();
    virtual void    set_path(path* l);
    virtual double  udv(const path* l);

    //描述：线构圈
    bool build_ring(const char* in,const char* out);
    
    //描述：圈构面
    bool build_surface(const char* in,const char* out);
    
    //描述：线构面
    bool build_all(const char* in,const char* out);

    //描述：内存中的线构面
    bool build_all(std::vector<path_ptr>& in,std::vector<path_ptr>& out);

    //描述：带容差的构面
    bool safe_build(const path* in,std::vector<path_ptr>& out,double connect_tol);

    //描述：数据清理
    bool clean(const char* in,const char* out);
    bool clean(const path* in,std::vector<path_ptr>& out);
      
    enum query_mode{
        equal_mode = 1,
        contain_mode = 2,
        contained_mode = 4,
        cover_mode = 8,
        covered_mode = 16,
        cross_mode = 32,
        overlap_mode = 64,
        intersect_mode = 128,
        use_label_mode = 0x80000000,
    };

    //描述：数据查询，
    //返回：查询的结果文件中保存结构为(id1,id2,query_mode)的信息
    bool query(const char* f1,const char* f2,int mode,const char* out);

    //描述：分割
    bool split(const char* knife,const char* cake,const char* out);

    //描述：分割
    bool split(const path* knife,const multi_path& cake,multi_path& out);

	//描述：根据udv的大小将in中的path输出到out
    bool sort_by_udv(const char* in,const char* out);

    //描述：根据udv合并对象
    bool union_by_udv(const char* in,const char* out);

    //描述：将in中的面根据几何上是否连通把它们连接起来
    //参数：in是输入的面的数据，里面每个直接引用都必须是面
    //      out是输出的连接信息，每个直接引用都是new出来的multi_path
    //      假如a是out中的一个直接引用，那么a中的每个直接引用都是in中的path
    //      并且a中的这些path在几何上是连通的，同时a中的每个path都不和in中非a中的path连通
    void surface_connect(std::vector<path_ptr>& in,std::vector<path_ptr>& out);

    //描述：遍历in中的每一个path执行回调函数fun
    bool travel_file(const char* in,bool (*fun)(void*,path*),void* data);

    //描述：遍历in中的每一个path执行回调函数fun
    //注意：函数返回后会close掉fin
    bool travel_file(FILE* fin,bool (*fun)(void*,path*),void* data); 

    //描述：得到中心线
    //参数：in是传入的path必须是一个面，out是输出的中心线
    bool central_line(const path* in,multi_path& out,double tol=0.1);

    //描述：很多面的求并
    //参数：in输入数据的文件名，程序只关心文件中的面数据
    //      out输出面的文件名，out中的每个path都是简单的封闭的线，内圈顺时针，外圈逆时针
    bool huge_union(const char* in,const char* out);

    //描述：用ptA中的点将in中的每个单线打断，打断结果输出到out
    bool break_by_point(const polyline& ptA,const path* in,std::vector<path_ptr>& out);

    //描述：得到in中线的打断信息
    //参数：in是输入的path文件，out是输出的交点
    //注意：函数返回的时候会fclose(in)而不会fclose(out)
    bool get_break_point(FILE* in,polyline& ptA);
    bool get_break_point(const char* in,polyline& ptA);

    //描述：得到in中重叠的线
    //参数：in是输入的path文件，out是输出的重叠线(格式也是path文件)
    //注意：函数返回的时候会fclose(in)而不会fclose(out)
    bool get_overlap(FILE* in,FILE* out);
    bool get_overlap(const char* in,const char* out);

    //描述：得到in中重叠的线
    //参数：in是输入的path文件，out是输出的重叠线(格式也是path文件)
    //注意：函数返回的时候会fclose(in)而不会fclose(out)
    //说明：get_near_line和get_overlap功能类似，不同的是get_near_line不会把精确相同的
    //      线输出到out
    bool get_near_line(FILE* in,FILE* out);
    bool get_near_line(const char* in,const char* out);

    //描述：消除悬挂点
    //      此函数只会修改in中每个单线的端点，如果某端点是悬挂点，
    //      但是在tol附近有其它的端点或者线的情况下此函数会将此端点修移动到附近的端点或者线上
    //      ptA是返回的移动到线上的端点坐标，一般情况下用户需要再次调用break_by_point函数将in打断
    bool remove_suspension(path* in,double tol,std::vector<point>& ptA);

    //描述：连线
    //      in是输入的线段文件，格式为(x1,y1,x2,y2),(x1,y1,x2,y2),…
    //      out是输出的geopath文件，每个path是in中线段连接成的结果
    //      mode表示是否反向敏感
    //注意：函数返回的时候会fclose(fin)而不会fclose(fout)
    bool connect(FILE* in,FILE* out,int mode=0);
    bool connect(const char* in,const char* out,int mode=0);

    //描述：连线
    //      in是输入的线段文件，格式为(z,x1,y1,x2,y2),(z,x1,y1,x2,y2),…
    //      out是输出的geopath文件，每个path是in中线段连接成的结果
    //      in中只有z只相同的线才能参与连接，连接成的path的m_dblVal将保存这个z值
    //      mode表示是否反向敏感
    //注意：函数返回的时候会fclose(fin)而不会fclose(fout)
    //      函数保证out中的path按照z值从小到大排序
    bool connect_ex(FILE* in,FILE* out,int mode=0);
    bool connect_ex(const char* in,const char* out,int mode=0);

    //描述：将in中的单线分类成边界线、内部线、和悬挂线
    //输入：in必须是适合构面的线，(也就是说没有相交，没有重叠，几何相相同的端点坐标精确相同)
    //输出：border是外轮廓线，inner是两个面的边界线，sus是不能参与构面的悬挂线
    bool get_border_inner_sus(const path* in,multi_path& border,multi_path& inner,multi_path& sus);

	//描述：去除重叠线
	//参数：in输入的具有重叠线段的path,out输入的没有重叠线段的path
	//		mode处理重叠的方式,mode=0表示如果有重叠线段那么out中不出现重叠线，否则out中出现一条重叠线
	//说明：处理的重叠线不考虑线的方向，也就是说线段(a,b)和(b,a)也认为是重叠的		
	void remove_overlap(const path* in,multi_path& out,int mode=0);

	//描述：面的差异性检查
	//输入：in是输入的面的文件
    //输出：out是输出的差异面
	void surface_diff_query(const char* in,multi_path& out);

	void sdq_build(multi_path& inout);
    
    //描述：设置进度条(这个方法用在构造一个子进度的analysis)
    void set_progress(progress* prg);

	//描述：两个图层的数据参与clean的方法
	//参数：A图层1的path集合(程序假定此图层数据是规范的)
	//      B图层2的path集合(程序假定此图层数据是规范的)
	//		out图层1和图层2的clean的结果(如果A,B满足规范则out也是规范的)
	//		bound是处理节点的范围，默认为空
	void clean2(path* A,path* B,multi_path& out,const path* bound = 0);

	//描述：clean2的简化版本
	void clean1(path* A,multi_path& out);

	//描述：两个面图层做叠置
	//参数：A图层1的path集合(程序假定此图层数据是规范的)
	//      B图层2的path集合(程序假定此图层数据是规范的)
	//		out图层1和图层2的overlay的结果(如果A,B满足规范则out也是规范的)
	void overlay(path* A,path* B,multi_path& out);

	//描述：两个面图层做叠置
	//说明：参见overlay的说明
	void overlay_file(const char* A,const char* B,const char* out);


	//获取图斑的边线
	//参数：inA参数输入的图斑,outA输出的线
	static void borderline_pick(const multi_path& inA,multi_path& outA);

	//检查出是否被图斑包含的线
	//source是图斑，borderA是边线，mode设置检查的是包含还是不包含
	//
	static void borderline_query(const path* source,multi_path& borderA,int mode =1);

	//描述：点坐标修改
	//参数：l参数修改的path,keyA要修改的点集合,value要修改为的点集合
	//说明：对l中任意一个pt，如果存在i使得pt==keyA[i]，那么修改pt为valueA[i]
	static void replace_point(path* l,const std::vector<point>& keyA,const std::vector<point>& valueA);

	//描述：生成聚合关系表
	//参数：sbl短线集合,所有短线应该被聚合掉
	//      fix不动点，所有邻近不动点的点，应该向不动点聚合
	//		keyA参与替换的点
	//		valueA需要替换的目标,如果valueA[i]==keyA[i]表示第i个点是不动点，否则第i个点是可动点
	static void create_rp_map(const path* sbl,const path* fix,
		std::vector<point>& keyA,std::vector<point>& valueA);

	//描述：保证plA里，所有ployline都是与其他ployline在端点处相接，主要是处理与其他ployline有交点的线圈
	//参数：plA 需要修改的数据的集合，只能装polyline
	static void set_ports(multi_path& plA);
};

//描述：得到文件的大小
GEO_DLL long long  file_size(const char* fn);
GEO_DLL long long file_size(FILE* pf);

//描述：将path写入文件中
GEO_DLL void write_path(FILE* file,const path* p);

//描述：从文件中读取path
GEO_DLL path_ptr read_path(FILE* file);

//描述：走到下一个path的位置
GEO_DLL bool goto_next_path(FILE* pf);

//描述：得到文件中path的个数
GEO_DLL int path_num(FILE* pf);

GEO_DLL void cerr_path(const path* a);

//描述：将l中的线段写入file中，file的格式是线段文件
//参数：tol是容查，当l中含有圆弧或者贝赛尔曲线的时候使用这个容查内插
GEO_DLL void write_line(FILE* file,const path* l,double tol);

template<class type>
void remove_vector(std::vector<type>& A,type a)
{
    A.erase( std::remove(A.begin(),A.end(),a),A.end() );
}

GEO_NAMESPACE_END

#endif // !defined(AFX_ANALYSIS_H__04155CA8_5917_4335_A422_804A321FBB16__INCLUDED_)
