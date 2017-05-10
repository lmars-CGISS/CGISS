#pragma once

namespace geostar {
struct geo_object;
};

typedef const char* string_t;

//\brief reader定义的回调函数 
//\param user 用户定义的参数
//\param i 要读取的第i个对象
//\return 返回的结果
//\details 这个回掉函数，可以帮助用户实现geo_reader接口,参考geo_factory::new_reader
//\details 参数i从1开始，如果i=0表示要释放geo_reader对象，用户代码应该释放user中的资源
typedef geostar::geo_object* (*reader_callback)(void* user,unsigned int i);

//writer定义的回调函数
typedef void (*writer_callback)(void* user,geostar::geo_object* );

typedef geostar::geo_object* (*open_callback)(string_t format,string_t filename);

namespace geostar {

//基础的对象接口
struct geo_object
{
    virtual ~geo_object(){};
    virtual string_t type_info()const=0;         //得到类型描述符
    virtual void* type_cast(string_t)=0;         //类型转换

    virtual int addref()=0;                         //添加引用计数
    virtual int release()=0;                        //减少引用计数
    
    virtual int i4_get(int i)=0;                    //得到属性
    virtual bool i4_set(int i,int v)=0;             //设置属性
};

//\brief geo_reader的读取接口
struct geo_reader : geo_object
{
    virtual geo_object* read()=0;
};

//geo_reader的读取接口
struct geo_writer : geo_object
{
    //\brief xxxx
    //\details  
    //\param in xxxxx

    virtual void write(geo_object* in)=0;
};

//读写接口
struct geo_reader2 : geo_reader,geo_writer
{	
	//得到对象数
	virtual unsigned int count()=0;

	//得到下标
	virtual unsigned int get_pos()=0;

	//设置下标
	virtual void set_pos(unsigned int i)=0;

	//创建一个副本
	virtual geo_reader2* duplicate()=0; 
};

//数据变换的接口
struct geo_trans : geo_object
{
    virtual geo_object* trans(geo_object*)=0;
	virtual bool setpara(string_t name,void* para)=0;
};

//数据比较接口
struct geo_compare : geo_object
{
	//a<b返回-1；a=b返回0；a>b返回1
    virtual int compare(geo_object* a,geo_object* b)=0;
};

//一维矩阵的接口 这是一个相对"简单"和"不安全"的接口
//本接口不限定每个子元素的类型必须一致，也就是说vector中第0个可以是int，而第1个可以是string_t，第2个可以是geo_object*
//每个元素的具体类型由接口的实现者和调用者自己约定，若约定不符则容易导致程序错误
//本接口约定的具体类型只有指针类型和值类型两种，指针类型目前只定义string_t,wstring_t,geo_object*三种，值类型调用者和实现者必须约定好数值的sizeof
//geo_vector一个突出的特点是约定get函数返回的对象外部程序不应该销毁，也就是说在已知get返回的是geo_object*的情况下，外部函数只需强制转换，使用完后无需调用release
struct geo_vector : geo_object
{
	//矩阵中元素的个数
	virtual int count()=0;
	
	//获取第i个元素
	//ptr为接受数据的外部指针，如果第i个元素是数值类型，那么给的ptr必须具有该数值类型sizeof的空间
	//如果第i个元素是指针类型，那么ptr可以忽略，而从返回值中得到元素指针，外部程序再转换为string_t或wstring_t或geo_object*
	//如果返回值是geo_object*，由于不是geo_object*的形式，本设计约定外部程序没有必要release掉返回值
	virtual const void* get(int i,void* ptr)=0;
	
	//修改第i个元素
	//ptr为传入数据的外部指针，调用者和实现者必须对其实际的类型有一致的约定
	//如果第i个元素是数值类型，那么给的ptr必须具有该数值类型sizeof的空间
	//如果第i个元素是指针类型，那么ptr必须是与之匹配的string_t,wstring_t或geo_object*
	virtual bool set(int i,const void* ptr)=0;

	//添加一个新元素
	//ptr为传入数据的外部指针，调用者和实现者必须对其实际的类型有一致的约定
	//如果可以add的数据是数值类型，那么ptr必须具有该数值类型sizeof的空间
	//如果可以add的数据是指针类型，那么ptr必须是与之匹配的string_t,wstring_t或geo_object*
	//如果返回值是geo_object*，由于不是geo_object*的形式，本设计约定外部程序没有必要release掉返回值
	virtual const void* add(const void* ptr)=0;

	//删除[i,i+n)元素
	virtual bool remove(int i,int n)=0;

	//得到遍历this的一个geo_reader
	virtual geo_reader* reader()=0;

	//得到往this添加数据的writer
	virtual geo_writer* writer()=0;
};

//显示GDI对象接口
//本设计约定graphics对象不需要支持多线程并发
struct geo_graphics : geo_object
{
	//保存GDI状态
	virtual geo_object* gsave()=0;

	//恢复GDI状态
	virtual void grestor(geo_object* gs)=0;

	//创建gid对象
	virtual geo_object* new_gdi(string_t paras)=0;

	//设置gdi对象，返回老的gdi对象
	virtual void set_gdi(geo_object* gdi)=0;

	//画一条path
	//mode&1表示要画线mode&2表示要填充
	//p是一个以-1为结尾的串，用来描述xy的结构 xy存放节点坐标
	//例如p={5,10,-1}表示xy描述了 两条线，第一条线有5个节点，第二条线有10个节点
	virtual void draw_path(int mode,const int* p,const double* xy)=0;
	
	//在矩形[x,y,x+w,y+h]处显示文字
	virtual void draw_text(geo_object* font,double x,double y,double w,double h,wchar_t* text)=0;
};

//符号分为原子符号和组合符号两种，客户程序绝不该直接使用原子符号，而是该通过geo_draw的new_symbol函数创建
//组合符号来显示对象，在符号的draw函数中有返回值，对组合符合而言此返回值永远为0，
//这个返回值的接口是为原子符号设计预留的

//symbol用来显示 geometry 对象
struct geo_symbol : geo_object
{
	//senv是附带的显示参数，当前只约定给出[s,x,y,w,h]5个值，今后可能添加,
	//[x,y,w,h)为显示窗口的矩形,s为一个象素的逻辑单位,也就是说将传入的path的x,y乘与s将得到变换前path的大小
	virtual void perpare(geo_graphics* dc,const double* senv)=0;

	//执行该符号的动作
	virtual geo_object* run(geo_graphics* dc,geo_object* para)=0;

	//将path显示到dc中
	void draw(geo_graphics* dc,geo_object* path){ run(dc,path); }
};

//这个接口用来创建原子符号
struct geo_sym_fac : geo_object
{
	//函数名
	virtual string_t name()=0;

	//创建符号对象
	virtual geo_symbol* create(string_t* paras,string_t* dc,string_t* path)=0;
};

//draw封装了显示用的方法
struct geo_draw : geo_object
{
	//设置精度属性值为value，返回老的精度值
	//precision值缺省为1，它用来控制数据的压缩率
	virtual double precision(double value)=0;

	//注册一个原子符号的类厂对象
	virtual void regist_sym_fac(geo_sym_fac* fac)=0;

	//创建一个symbol对象,type为对象的类型,scrip为此symbol的详细信息
	virtual geo_symbol* new_symbol(string_t type,string_t scrip)=0;

	//设置窗口大小(env)和 逻辑坐标到屏幕坐标的 变换参数假如(x,y)为一个逻辑坐标
	//那么它的屏幕坐标为 tx[0]*x+tx[1]*y+tx[2],ty[0]*x+ty[1]*y+ty[2]
	//env={x,y,w,h}为窗口的矩形
	virtual void prepare(const double* env,const double* tx,const double* ty)=0;
	
	//显示一组path,这个函数从R中读取数据，使用并发，压缩等提速手段将path变换成symbol可画的对象，通过sym画出去
	//R中返回的可以是path对象，也可以是factory的new_sys_path返回的对象，
	//前一种情况函数使用sym画出对象,后一种情况函数使用对象自带的symbol画出对象
	virtual void draw_path(geo_reader* R,geo_graphics* dc,geo_symbol* sym,geo_trans* tpath,geo_trans* tsym)=0;

	virtual void draw_path_2(geo_vector* A,int path_cid,int env_cid,geo_graphics* dc,geo_symbol* sym,geo_trans* tsym)=0;

	//创建一个注记对象 path为注记的几何对象 txt为注记的文本
	//font封装了注记的字体颜色等信息 mode指定注记的排版方式
	//w,h为字体的大小,当mode指定为可拆分的时候w是单个字的宽度，否则是整个文本的宽度
	virtual geo_object* new_text(geo_object* font,geo_object* path,const wchar_t* txt,int mode,int w,int h)=0;

	//显示一组注记,R中返回的对象必须是new_txt函数创建的对象
	virtual void draw_text(geo_reader* R,geo_graphics* dc)=0;

	//显示注记
	virtual void draw_text_2(geo_vector* A,int path_cid,int env_cid,geo_graphics* dc,geo_trans* ttxt)=0;
};

//一个单元个的元数据
struct geo_cell
{
	string_t	name;		//列名称
	string_t	discribe;	//附加的描述信息
	string_t	type;		//数据的类型 目前只能是byte,string,wstring,object
	int			size_of;	//占用的字节数 如果type等于string,wstring,object该值为0，如果type等于byte该值必须大于0
};

// GeomathSE内部实现的二维数组(表)的接口
struct geo_table : geo_object
{	
	//创建一个表 [p,p+n)为列的元信息
	virtual bool create(int n,geo_cell* p)=0;

	//将this保存到文件 filename为文件名
	virtual bool save(string_t filename)=0;

	//从文件中装入表数据 filename为文件名
	virtual bool load(string_t filename)=0;

	//表的附加属性，返回的geo_vect_1是一个string_t类型的 一维数组
	geo_vector* props();

	//列信息 返回的geo_vect_1是一个cell类型的 一维数组
	virtual geo_vector* columns()=0;

	//行信息 返回的geo_vect_1是一个object类型的一维数组 
	//且每个row对象都是geo_vect_1*类型的object，每个row的具体结构可以根据columns获知
	virtual geo_vector* rows()=0;

	//根据row的下标批量删除row
	virtual int del_rows(int n,const int* row_ids)=0;
};

struct geo_factory : geo_object
{
    //得到p的坐标维数 2表平面 3表立体
    virtual int dim_c(geo_object* p)=0;
  
    //得到p的几何维数 0表示点 1表示线 2表示面
    virtual int dim_g(geo_object* p)=0;

    //得到p的子对象个数 如果p是简单对象返回0
    virtual int sub_n(geo_object* p)=0;

    //得到第i个子对象
    virtual geo_object* sub_at(geo_object* p,int i)=0;
    
    //得到点个数
    virtual int point_n(geo_object* p)=0;
    
    //得到第i个点的内部信息 vt=0返回x坐标,vt=1返回y坐标,vt=2返回z坐标vt=4返回曲线描述符
    virtual const void* point_at(geo_object* p,int i,int vt)=0;
    
    //创建简单线
    //gdim指定几何维数 pnum指定点个数 cdim指定坐标维数 xyz指定坐标
    //flag指定是否(&1)引用传入的xyz坐标，以及对曲线的是否(&2)内插
    //vt_p指定曲线描述符=0表示折线
    virtual geo_object* create_single(int gdim,int pnum,int cdim,const double* xyz,
        int flag,const void* vt_p)=0;

    //创建复合线
    //gdim指定几何维数，由于geometry对象是不可修改的 外部程序可以使用一个multi对象对现有的geometry包装得到不同几何维数的新对象
    //snum指定sub的个数 subs为子对象的首地址 flag预留
    virtual geo_object* create_multi(int gdim,int snum,geo_object** subs,int flag)=0;

    //描述：根据Oracle定义的解释串坐标串 创建一个path对象
    //      flag参数决定path对象是否(&1)引用c_p坐标
    virtual geo_object* ora_create(int i_n,const int *i_p,int c_n,int cdim,const double *c_p,int flag)=0;

    //描述：得到Oracle定义的解释串坐标串 ora参数必须是ora_create_info返回的结果
    virtual bool ora_get_info(geo_object* obj,int* i_n,int** i_p,int* c_n,int* cdim,double **c_p)=0;

    //创建基于回调函数的geo_reader
    virtual geo_reader* new_reader(void* user,reader_callback func)=0;

    //创建多个geo_reader的组合geo_reader
    virtual geo_reader* new_reader_n(int n,geostar::geo_reader** ppr)=0;

	//创建一个过滤的geo_reader
    virtual geo_reader* new_reader_trans(geo_reader* R,int n,geo_trans** tt)=0;
    
    //创建基于回调函数的geo_writer
    virtual geo_writer* new_writer(void* user,writer_callback func)=0;

    //根据格式和文件名打开一个geo_reader
    virtual geo_reader* open_reader(string_t format,string_t filename)=0;

    //根据格式和文件名创建一个geo_writer
    virtual geo_writer* open_writer(string_t format,string_t filename)=0;
	
	//根据描述符合参数创建一个geo_trans
	//scrip="cut" 返回单个裁剪的trans 需要设置类型为面的"knife"参数,trans函数返回在knife内部的裁切结果
	//scrip="clip" 返回矩形裁剪的trans 此trans 需要设置"x0","y0","dx","dy","tx","ty" 六个参数
	//		clip trans返回的path一定是multi类型，multi中的每个子path一定有长度为2的i4属性
	//scrip="simplify_toint" 返回整数版的简化trans 此trans 需要设置 pricesion 参数
	//scrip="simplify_dauglas", 返回dauglas版的简化trans 此trans需要设置 tol 参数
	//scrip="parallel" 返回平行线的trans 此trans需要设置 radius 参数, 还可以设置narc参数(缺省值为6)
	//scrip="buffer" 返回缓冲区的trans 此trans需要设置 radius 参数, 还可以设置narc参数(缺省值为6)
    virtual geo_trans* create_trans(string_t scrip)=0;
	
	//根据格式和文件名打开一个geo_reader2
    virtual geo_reader2* open_reader2(string_t format,string_t filename)=0;

	//注册一个打开文件的函数,type=0是打开reader,否则是打开writer
	virtual void regist_open(open_callback func,int type)=0;

	//创建一个draw对象
	virtual geo_draw* new_draw()=0;

	//创建一个geo_table对象
	virtual geo_vector* new_obj_vect()=0;

	//创建一个geo_table对象
	virtual geo_table* new_table()=0;

	//输出single path的信息
	//single必须是一个single path
	//cdim输出坐标维数,gdim输出几何维数,pnum输出点的个数
	//xyz输出(x,y,z)的值,vt输出曲线描述符,(xyz和vt外部都不能删除和更改)
	virtual bool out_single(geo_object* single,int* cdim,int* gdim,int* pnum,double** xyz,char** vt)=0;
};

struct geo_algorithm : geo_object
{
    //容差
    virtual double tolerance(double tol)=0;

    //计算对象的数值属性
    //mode 可以指定 长度、面积、体积、
    virtual double prop_value(geo_object* obj,int mode)=0;

    //计算对象的几何属性
    //mode 可以指定 clone 中心、重心、Label点 
    //外接矩形(正斜)、内接矩形(正斜)、内接外接(圆)、凸包 等等
    virtual geo_object* prop_geo(geo_object* obj,int mode)=0;

	//计算对象的几何属性
    //mode 可以指定 clone 中心、重心、Label点 
    //外接矩形(正斜)、内接矩形(正斜)、内接外接(圆)、凸包 等等
    virtual bool prop_geo_2(geo_object* obj,int mode,double* paras)=0;

	//修改几何对象
	//mode可以指定 反向 去除重复点 折线压缩(dauglas) 调整方向(force_good_dir) 等等
	virtual int gmodify(geo_object* obj,int mode,void* para)=0;

	//返回点在A的左右边，如果(x,y)和p的距离小于容差返回0，左边返回1，右边返回2
	virtual int left_right(geo_object* p,double x,double y)=0;

    //返回（a,b)间最近的两个点
    //返回的geo_object是一个线段
    virtual geo_object* nearest(geo_object* a,geo_object* b)=0;

    //坐标参数化函数
    //传入的p可以是一个geometry也可以是一个索引对象
    //函数在p中寻找与x,y最近的线段，如果在容差返回内没找到则返回0
    //否则返回线段所在的单线s，t是(x,y)在s上最近点在s上的参数
    virtual geo_object* xy2t(geo_object* p,const double* xy,double* t)=0;

    //参数坐标化
    //传入的s必须是一个简单线,函数计算s上参数为t的点坐标
    virtual bool t2xy(geo_object* s,double t,double* xy)=0;
	
    //查询(a,b)是否满足mode关系
    //a,b可以是几何对象，也可以是索引对象
	//mode参见spr_is_*** 定义的模式
    virtual bool spr_query_is(geo_object* a,geo_object* b,int mode)=0;

    //查询a,b的空间关系spr
	//返回值spr描述了a,b的空间关系，直接使用spr不是很方便
	//用户可以调用spr_is来测试spr是否满足某模式
    virtual int spr_query(geo_object* a,geo_object* b)=0;

	//测试spr是否满足某mode给定的模式
	//spr是spr_query或者spr_query_n2n返回的值
	//mode是spr_is_***定义的模式
	virtual bool spr_is(int spr,int mode)=0;
    
    //查询两组数据P,Q的空间关系，结果写入R
    virtual void spr_query_n2n(geo_reader* P,geo_reader* Q,geo_writer* R,int mode)=0;

    //创建空间索引对象 
    //在处理split或查询1对n的情况时 为1的数据准备空间索引有助于提高效率
    virtual geo_object* spi_create(geo_object* obj,int mode)=0;

    //两个几何对象的组合运算
    //mode可以指定组合方式 交、并、差、对称差
    virtual geo_object* gcombine(geo_object* a,geo_object* b,int mode)=0;
    
    //几何切割K可以是单个几何对象或索引对象
    //x可以是单个几何对象，也可以是一个geo_reader
    virtual void gsplit(geo_object* K,geo_object* x,geo_writer* W)=0;

    //多面对象合并 写入W的每个对象都是单外圈的对象
    //函数只处理面忽略R中的线、点
    virtual void n_union(geo_reader* R,geo_writer* W)=0;

    //检查单个对象的几何正确性
    //mode指定检查内容 可以是 自相交 线段重叠 方向正确 是否封闭
	//返回0表示没有错误，否则返回错误情况
    virtual int gcheck_1(geo_object* obj,int mode)=0;

	//检查悬挂点、容错点、伪节点、内交点
	//孤立线，重复线
	//检查出来的点和线通过W输出
	virtual void gcheck_2(geo_object* R,geo_writer* W,int mode)=0;

    //构造R的缓冲区
    //narc指定圆由几条线段组成
	//这个函数将R中的所有对象当作线看待，输出到W的所有对象是面
    virtual void line_buffer(geo_object* R,double radius,int narc,geo_writer* W)=0;

    //数据清理 清理输出到W的几何对象都是线对象
    //且都不自相交、互相之间不相交
    //R可以是单个几何对象，也可以是geo_reader
    virtual void line_clean(geo_object* R,geo_writer* W)=0;

    //构面
	//mode&1表示R中的每条线都要当作正反两条来使用
	//mode&2表示R中的线已经是圈了,不需要再构圈了
	//mode&4表示只构圈不构面，否则要构面
    virtual void build(geo_reader* R,geo_writer* W,int mode)=0;

	//图层的叠置
	//mode的最低2位表示输出对象的几何维数
	//mode&4表示输出对象要带A图层的关系
	//mode&8表示输出对象要带B图层的关系
	//mode&16表示输出对象在一个图层中可以带多个关系
	//A、B两个图层可以是线也可以是面，但在一个图层中必须只有一种类型
    //min_width用来控制狭长面的产生，一个面其面积除于长度称之为平均宽度，如果平均宽度小于min_width
    //那么这个面将会融合到附近的面中，而不会输出
	virtual void overlay(geo_reader* A,geo_reader* B,geo_writer* W,double min_width,int mode)=0;
	
	//创建point_pool对象，此对象可以用来修正path的点坐标
	virtual geo_trans* point_pool(geo_object* R,int mode)=0;

	//创建line_pool对象，(此函数暂时没用)
	virtual geo_trans* line_pool(geo_object* R,int mode)=0;

	//根据属性对path排序
	virtual geo_reader* sort_by_prop(geo_reader* A,geo_compare* cmp)=0;

	//在一个对象数组中执行空间查询
	virtual geo_vector* geo_query(geo_vector* A,int path_cid,int env_cid,geo_object* geo,int mode)=0;

    //保拓扑的简化
    //env如果不为空那么指向一个[x0,y0,x1,y1]的矩形，凡不在此矩形内部的点都不会被简化
    //[pp,pp+n)是要简化的path数组，程序只会简化其内部的点，而不会改变对象以及其属性
    virtual void top_reserve_simplify(int n,geo_object** pp,double tol,double* env)=0;

    //根据参数区间返回一段子path
    virtual geo_object* t2path(geo_object* p,double t0,double t1)=0;
	
    //文字布局函数 p是一个几何对象 env[x,y,x1,y1]是窗口的可视范围(可以为null) font[w，h]是字体大小(可以为null)
    //n是文字的个数,xy是输出的每个文字的左下角坐标
    virtual bool layout(geo_object* p,const double* env,const double* font,int n,double* xy)=0;
	//virtual geo_reader* difference_n2n(geo_reader* A,geo_reader* B,geo_writer* dA,geo_writer* dB,int mode)=0;
};

};

/* 预留的接口设计
namespace geostar {

struct geo_keymap : geo_object
{
    virtual int keylen()=0;
    virtual geo_object* get(const void* key)=0;
};

struct galgorithm2_ex : geo_algorithm
{
    //线构面
    //mode指定 线构圈 圈构面 线构面
    virtual geo_object* build_by_point(geo_keymap* db,int n,const void* keys,const double* envs,double x,double y)=0;
}; } */

//各种常量
namespace geostar {

const int prop_cancel = -100;	//取消的属性

//ga_i4打头的用量设置几个全局变量
const int ga_i4_clockwise = 0;		//设置时针规则i4_set(ga_i4_clockwise,0)表示逆时针规则，i4_set(ga_i4_clockwise,1)表示顺时针规则，确省为0
const int ga_i4_narc = 1;			//设置圆变成折线的线段数目i4_set(ga_i4_narc,num),缺省num=24
const int ga_i4_max_pt_in_mem = 2;  //设置内部对象最多允许在内存中的点数目i4_set(ga_i4_max_pt_in_mem,num)，缺省num=1024*1024*8 (每个点16个字节相当于128M内存)
									//这个值一定不能设置太小，否则会引发用文件缓存严重影响性能，外部把虚拟内存调大一些会比设小这个变量好很多

const int geometry_i4_gdim = -2;	//Geometry对象通过这个i4_set(geometry_i4_gdim,gdim)得到或设置几何维数
const int geometry_i4_prop_len = -1;//Geometry对象通过这个i4_set(geometry_i4_prop_len,len)得到或设置属性长度

const int prop_value_length = 11;		//长度
const int prop_value_width =  21;		//宽度
const int prop_value_height = 31;		//高度
const int prop_value_area =	  12;		//面积

const int prop_geo_clone =   0;		    //克隆
const int prop_geo_clone_mem0 = 1;		//只对没有真实内存的path克隆

const int prop_geo_label =   10;		//标志点
const int prop_geo_center =  20;		//中心	
const int prop_geo_centroid = 30;		//重心
const int prop_geo_maxline = 11;		//最长线
const int prop_geo_env =	 12;		//外接矩形
const int prop_geo_hull = 22;			//凸壳
const int prop_geo_env_nstd = 32;		//斜外接矩形
const int prop_geo_env_circle = 42;		//外接外接圆
const int prop_geo_inner_rect = 52;		//内接矩形
const int prop_geo_inner_square = 62;	//内接矩形
const int prop_geo_inner_circle = 72;	//内接矩形
const int prop_geo_simplify = 13;		//简化对象
const int prop_geo_boundary = 23;		//简化对象

const int gmodify_remove_repeat = 1;	//删除重复的点 para为距离平方
const int gmodify_dauglas = 2;			//道格拉斯压缩 para为距离
const int gmodify_reverse = 3;			//反向         para为null
const int gmodify_force_good_dir = 4;	//force_good_dir para为null
const int gmodify_force_geo_close = 5;	//force_geo_close para为null

const int gcombine_union = 1;			//面求并
const int gcombine_intersect = 2;		//面求交
const int gcombine_diffrence = 3;		//面求差
const int gcombine_sym_diffrence = 4;	//面求对称差

const int gcheck_1_e_simple = 0;		//是否是简单对象
const int gcheck_1_e_close_2 = 1;		//强封闭检查
const int gcheck_1_e_close = 2;			//封闭检查
const int gcheck_1_e_dir = 4;			//方向是否正确
const int gcheck_1_e_cross = 8;			//自相交
const int gcheck_1_e_lap = 16;			//线重叠
const int gcheck_1_e_repeat = 32;       //点重叠

const int gc2_pt_repeat = 0x01;			//重复点
const int gc2_pt_isolate = 0x02;		//悬挂点
const int gc2_pt_endp_x = 0x04;			//伪端点
const int gc2_pt_tol_x = 0x08;			//容错点 在容差范围内但不精确相同
const int gc2_pt_nodal = 0x10;			//相交的节点 一个必须是节点
const int gc2_pt_cross = 0x20;			//相穿点

const int gc2_l_1 = 0x100;				//孤立线
const int gc2_l_n = 0x200;				//重叠线

const int gc2_a_0 = 0x1000;				//楼空的面
const int gc2_a_1 = 0x2000;				//只被一个包含的面
const int gc2_a_n = 0x4000;				//被多个包含的面

// spr_is的模式
const int spr_is_disjion = 1;
const int spr_is_intersect = 2;
const int spr_is_cross = 3;
const int spr_is_equal = 4;   //大致相等(线段可以拆分)
const int spr_is_equal_2 = 5; //精确相等(线段不可以拆分)

const int spr_is_touch = 6; //点在线的端点；点是面的节点或边界线上点；线与线仅相交于端点且不是相穿；线与面在节点处相交且不相穿不在面内部；面与面在节点处相交且不重叠
const int spr_is_overlap = 7; //相同维度之间才存在重叠

const int spr_is_contain = 8;
const int spr_is_within = 16;
const int spr_is_cross_l = 32;

const int spr_no_touch = 0x10000000;  //当两个几何对象的边界相交的时候认为它们没有is关系
const int spr_can_touch = 0x20000000; //当两个几何对象的边界相交的时候不影响它们的is关系

const int pp_ipt_create = 0x01; //point_pool函数的mode&pp_ipt_create时对输入的线段间的交点也会计算出来
const int pp_ipt_trans = 0x02;  //point_pool函数的mode&pp_ipt_trans时返回的geo_trans在trans时候会在线段间内插节点
const int pp_use_line = 0x04;  //point_pool函数的mode&pp_use_line时返回的geo_trans在trans时候会对点进行线段意义上的贴靠

const int draw_txt_nocover = 1; //显示文本不能压盖对象
const int draw_txt_split = 2;   //显示文本可以拆分成单个字

};

