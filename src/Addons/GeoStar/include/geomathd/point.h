// point.h: interface for the point class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT_H__4BECF1C3_5A80_4AD0_8147_C4BC7089450D__INCLUDED_)
#define AFX_POINT_H__4BECF1C3_5A80_4AD0_8147_C4BC7089450D__INCLUDED_

#include "safeptr.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

struct point;
struct pnode;
struct line;
struct circle;
struct arc;
struct range;
struct envelope;
struct bezier;
class polynomial;

struct GEO_DLL range
{
    double _min,_max;

    range():_min(DBL_MAX),_max(-DBL_MAX){
    }

    range(double a):_min(a),_max(a){
    }

    range(double a,double b):_min(a),_max(b){
    }

    bool operator == (const range &r)const{
        return _min==r._min && _max==r._max;
    }

    bool operator != (const range &r)const{
        return _min!=r._min || _max!=r._max;
    }

    range& operator |= (double r){
        if( r > _max ) _max = r;
        if( r < _min ) _min = r;
        return *this;
    }

    range operator | (double r)const{
        return range(*this) |= r;
    }

    range& operator |= (const range &r){
        if( r._max > _max ) _max = r._max;
        if( r._min < _min ) _min = r._min;
        return *this;
    }

    range operator | (const range &r)const{
        return range(*this) |= r;
    }

    range& operator &= (const range &r){
        if( r._max < _max ) _max = r._max;
        if( r._min > _min ) _min = r._min;
        return *this;
    }

    bool operator && (double r)const{
        return _min <= r && _max >= r;
    }

    bool operator < (const range &r)const{
        return _min==r._min? _max<r._max : _min<r._min;
    }

    bool operator && (const range &r)const{
        return _min <= r._max && _max >= r._min;
    }

    range& operator += (double r){
        _min += r;
        _max += r;
        return *this;
    }

    range operator + (double r)const{
        return range(*this) += r;
    }

    range& operator -= (double r){
        _min -= r;
        _max -= r;
        return *this;
    }

    range operator - (double r)const{
        return range(*this) -= r;
    }

    range& expand(double r){
        _min -= r; _max += r;
        return *this;
    }

    double center()const{
        return (_min+_max)/2;
    }

    double length()const{
        return _max-_min;
    }

    bool is_cover(const range& r)const{
        return _min<=r._min && _max>=r._max;
    }

    bool is_cover(double r)const{
        return _min<=r && _max>=r;
    }

    //描述：得到v和区间的距离
    double dis(double v)const{
        if (v<=_max && v>=_min)
            return 0;
        double a,b;
        a = v>_min?v-_min:_min-v;
        b = v>_max?v-_max:_max-v;
        return a>b?b:a;
    }

    range& normalize(){
        if(_min>_max){
            double a = _min;
            _min = _max;
            _max = a;
        }
        return *this;
    }
};

struct GEO_DLL point
{
    double x,y;

    point(){
    };

    point(double X,double Y):x(X),y(Y){
    }

    bool operator == (const point &a)const{
        return x==a.x && y==a.y;
    }

    bool operator != (const point &a)const{
        return x!=a.x || y!=a.y;
    }

    bool operator < (const point &a)const{
        return x==a.x ? y<a.y : x<a.x;
    }

    bool operator <= (const point &a)const{
        return x==a.x ? y<=a.y : x<a.x;
    }

    bool operator > (const point &a)const{
        return x==a.x ? y>a.y : x>a.x;
    }

    bool operator >= (const point &a)const{
        return x==a.x ? y>=a.y : x>a.x;
    }

    point& operator += (const point &a){
        x += a.x; y += a.y; return *this;
    }

    point& operator -= (const point &a){
        x -= a.x; y -= a.y; return *this;
    }

    point& operator *= (double a){
        x *= a; y *= a; return *this;
    };

    point& operator /= (double a){
        x /= a; y /= a; return *this;
    };

    point operator + (const point &a)const{
        return point(*this) += a;
    };

    point operator - (const point &a)const{
        return point(*this) -= a;
    };

    point operator * (double a)const{
        return point(*this) *= a;
    };

    point operator / (double a)const{
        return point(*this) /= a;
    };

    double operator*(const point &a)const{
        return x*a.x + y*a.y;
    }

    //描述：得到this和o的距离的平方
    double dis2(const point &o)const{
        if( 0==&o ) return DBL_MAX;
        double a=x-o.x, b=y-o.y;
        return a*a+b*b;
    }

    //描述：返回this和o的一次距离
    double abs(const point &o)const{
        double a=x-o.x, b=y-o.y;
        if( a<0 ) a = -a;
        if( b<0 ) b = -b;
        return a>b ? a:b;
    }

    //描述：使得this到原点的距离为fabs(r)
    void stand(double r){
		if( x==0 && y==0 )
			return;
        r/=sqrt(x*x+y*y);
        x *= r; y *= r;
    }

    //描述：返回复数this和复数a的乘积
    point mul(const point &a)const{
        return point(x*a.x-y*a.y,x*a.y+y*a.x);
    }
};

struct GEO_DLL envelope
{
    range x,y;

    envelope(){}

    envelope(double minx,double miny,double maxx,double maxy)
        :x(minx,maxx),y(miny,maxy){
    }

    envelope(const point &minxy,const point &maxxy)
        :x(minxy.x,maxxy.x),y(minxy.y,maxxy.y){
    }

    explicit envelope(const point &pt):x(pt.x),y(pt.y){
    }

    envelope& operator += (const point& a){
        x += a.x;  y += a.y; return *this;
    }

    envelope& operator -= (const point& a){
        x -= a.x;  y -= a.y; return *this;
    }

    envelope& operator |= (const point& a){
        x |= a.x;  y |= a.y;
        return *this;
    }

    envelope& operator |= (const envelope& a){
        x |= a.x;  y |= a.y;
        return *this;
    }

    envelope& operator &= (const envelope& a){
        x &= a.x;  y &= a.y;
        return *this;
    }
    
    envelope operator + (const point& a)const{
        return envelope(*this) += a;
    }

    envelope operator - (const point& a)const{
        return envelope(*this) -= a;
    }

    envelope operator | (const point &a)const{
        return envelope(*this) |= a;
    }

    envelope operator | (const envelope &a)const{
        return envelope(*this) |= a;
    }

    envelope operator & (const envelope& a){
        return envelope(*this) &= a;
    }

    bool operator == (const envelope &a)const{
        return x==a.x && y==a.y;
    }

    bool operator != (const envelope &a)const{
        return x!=a.x || y!=a.y;
    }

    bool operator && (const envelope &a)const{
        return (x&&a.x) && (y&&a.y);
    }

    bool operator && (const point &a)const{
        return (x&&a.x) && (y&&a.y);
    }

	envelope& expand(double dx,double dy){
        x.expand(dx); y.expand(dy);
		return *this;
	}

    envelope& expand(double d){
        x.expand(d); y.expand(d);
		return *this;
	}

	envelope& expand(point pt){
		return expand(pt.x,pt.y);
	}

    double width()const{
        return x.length();
    }

    double height()const{
        return y.length();
    }

    void x_range(range &r)const{
        r |= x;
    }

    void y_range(range &r)const{
        r |= y;
    }

    void xy_range(envelope &env)const{
        env |= *this;
    }

    void center(point &pt)const{
        pt.x = x.center();
        pt.y = y.center();
    }

    point center()const{
        return point( x.center(),y.center() );
    }

    point get_min()const{
        return point(x._min,y._min);
    }

    point get_max()const{
        return point(x._max,y._max);
    }

    envelope& set_min(const point &pt){
        x._min = pt.x; y._min = pt.y;
        return *this;
    }

    envelope& set_max(const point &pt){
        x._max = pt.x; y._max = pt.y;
        return *this;
    }

    bool is_cover(const envelope& r)const{
        return x.is_cover(r.x) && y.is_cover(r.y);
    }

    bool is_cover(const point& pt)const{
        return x.is_cover(pt.x) && y.is_cover(pt.y);
    }

    void split(envelope& e1,envelope& e2,double tol=0)const{
        e1 = e2 = *this;
        if( width()>height() )
        {
            e1.x._max = e2.x._min = x.center();
            e1.x._max -= tol; e2.x._min += tol;
        }
        else
        {
            e1.y._max = e2.y._min = y.center();
            e1.y._max -= tol; e2.y._min += tol;
        }
    }

    //描述：得到pt和矩形(面语义)的距离的平方
    double dis2(const point& pt)const{
        double a,b;
        a = x.dis(pt.x);
        b = y.dis(pt.y);
        return a*a+b*b;
    }

    envelope& normalize(){
        x.normalize();
        y.normalize();
        return *this;
    }
};

struct GEO_DLL line
{
    point me[2];

    line(){}
    line(const point&a,const point &b){
        me[0] = a; me[1] = b; 
    }
    inline line(const arc *L);

    //描述：根据x得到y值
    double get_y(double x)const;

    //描述：根据y得到x值
    double get_x(double y)const;

    //描述：得到斜率
    point tangent_at(double t)const;

    //描述：将this的x轴的范围扩充到r中
    void    x_range(range &r)const{
        r |= me[0].x;
        r |= me[1].x;
    }

    //描述：将this的y轴的范围扩充到r中
    void    y_range(range &r)const{
        r |= me[0].y;
        r |= me[1].y;
    }

    //描述：返回this的取值区间
    double  max_para()const{ return 1; }
    
    //描述：求this的长度
    double  length()const;
    
    //描述：求this的积分面积
    double  area()const;

    //描述：返回点pt的最近点在this上的参数，参数在取值区间之内
    double  nearest(const point &pt)const;

    //描述：返回点pt的最近点在this上的参数，参数可能在取值区间之外
    double  nearest_ex(const point &pt)const;

    //描述：返回this和pt距离的平方
    double  dis2(const point &pt)const;

    //描述：返回参数为t的点坐标
    point   point_at(double t)const;

    //描述：计算子线
    void    path_at(double star,double end,point *mem)const;

    //描述：插入参数点，返回的out是this插入t中n个参数点之后的折线
    //      函数返回后t中的值将修改为原来的参数点在out中的参数
    void    insert_at(double *t,int n,std::vector<point> &out)const;
    
    //描述：返回this和pt的穿越数
    int     across(const point &pt)const;

    //描述：求点pt在直线this的左右边，返回1表示左边，返回2表示右边，0表示共线
    int     left_right(const point &pt,double tol2)const;   

    //描述：算出L和this的交点在this上的参数，交点必须是L和this的内点
    //参数：t存放交点参数的地址
    //返回：交点个数+t
    double* intersect(const line *L,double *t)const;
    double* intersect(const arc *L,double *t)const;
    double* intersect(const bezier *L,double *t)const;
    double* intersect(const pnode *L,double *t)const;
    double* intersect(const envelope& env,double *t)const;

    //描述：算出L和this的交点在this上的参数，交点可以是L和this的内点、端点、外点
    //参数：t存放交点参数的地址
    //返回：交点个数+t
    double* intersect_ex(const line *L,double *t)const;
    double* intersect_ex(const arc *L,double *t)const;
    double* intersect_ex(const bezier *L,double *t)const;
    
    //描述：求出this和参数曲线X(t),Y(t)的交点
    //返回：t为返回的参数曲线上的参数
    double* intersect_f(polynomial x,polynomial y,double* t)const;
    
    //描述：判断this是否和L相离
    bool    is_disjoin(const line *L,double tol2)const;
    bool    is_disjoin(const arc *L,double tol2)const;
    bool    is_disjoin(const bezier *L,double tol2)const;
    bool    is_disjoin(const envelope &env)const;
    
    //描述：判断this是否和L相穿
    bool    is_cross(const line *L,double tol)const;
    bool    is_cross(const arc *L,double tol)const;
    bool    is_cross(const bezier *L,double tol)const;

    //描述：判断pt是否和this的端点的距离平方小于tol2
    bool    is_near_port(const point &pt,double tol2)const;

    //描述：判断pt是否是this的内点，并得到内点的参数
    bool    is_inner_point(const point &pt,double tol2,double &t)const;

    //描述：获得多个点和this的相交信息
    //参数：A.size()为点的个数，第一个点是pt，第二个是(pt.x,pt.y+dy)，第三个是(pt.x,pt.y+2*dy)，…………
    //      每个点都当作是以这个点为中心扩展tol的矩形
    //返回：如果第i个点和this相交，那么赋值A[i]为true否则不改变A[i]
    void    n_intersect(point pt,double dy,point tol,std::vector<int> &A)const;

    //描述：获得多个点和this的穿越数
    //参数：A.size()为点的个数，第一个点是pt，第二个是(pt.x,pt.y+dy)，第三个是(pt.x,pt.y+2*dy)，…………
    //返回：将每个点和this的穿越数累加到A中
    void    n_across(point pt,double dy,std::vector<int> &A)const;

    //描述：判断this是否和l重叠，如果是返回重叠部分在this上的参数
    bool    is_lap(const line& l,double tol2,double& t1,double& t2)const;
    bool    is_lap(const pnode* l,double tol2,double& t1,double& t2)const;
    bool    is_lap(const line* l,double tol2,double& t1,double& t2)const{
        return is_lap(*l,tol2,t1,t2);
    }

    //描述：判断this是否完全覆盖l
    bool    is_contain(const line& l,double tol2)const;
    bool    is_contain(const pnode* l,double tol2)const;
    bool    is_contain(const line* l,double tol2)const{
        return is_contain(*l,tol2);
    }

    //描述：得到this的方向，返回0表示退化，返回1表示角度[-PI/4，3PI/4)，否则返回2
    int     direct()const;

    //描述：得到this和env中最近点的距离平方
    double  min_dis2(const envelope& env)const;

    //描述：得到this和env中最远点的距离平方
    double  max_dis2(const envelope& env)const;
};

struct GEO_DLL circle : public point
{
    double r2;

    //描述：判断this是否和c相离
    bool    is_disjoin(const circle &c,double tol2)const;

    //描述：判断this是否和c相离
    bool    is_contain(const circle &c,double tol2)const;

    //描述：角度a是否在角度区间s,e内部
    static bool is_inner(double s,double e,double a);

    //描述：返回角度a在角度区间s,e的参数
    static double parameter(double a,double s,double e);

    //描述：返回pt在角度区间s,e的参数
    double parameter(point pt,double s,double e);

    //描述：将this的x轴范围扩充到r中
    void    x_range(range &r)const;

    //描述：将this的y轴范围扩充到r中
    void    y_range(range &r)const;

    //描述：计算两个圆的交点,pt为交点坐标返回交点个数
    //返回：交点的个数+pt，pt存放交点坐标(pt必须能够容纳2个点)
    point*  intersect(const circle& c,point *pt);

    //描述：计算this和envelope的交点
    //返回：交点的个数+pt，pt存放交点坐标(pt必须能够容纳8个点)
    point*  intersect(const envelope& e,point *pt);

    //描述：计算this和l的交点，在l上的参数
    double* intersect(const line& l,double *t)const;

    //描述：计算圆和纵轴为y为横轴[r.min,r.max]的线段的交点，x为交点坐标返回交点个数
    int intersect_x(double y,const range& r,double *x);

    //描述：计算圆和横轴为x纵轴为[r.min,r.max]的线段的交点，y为交点坐标返回交点个数
    int intersect_y(double x,const range& r,double *y);

    //描述：求出this和参数曲线X(t),Y(t)的交点
    //返回：t为返回的参数曲线上的参数
    double* intersect_f(polynomial x,polynomial y,double* t)const;

    //描述：返回pt到弧上的距离
    double dis(const point &pt)const;

    //描述：得到点pt到圆上的切点，结果写入p
    //返回：切点的个数，如果pt在圆的内部返回0，如果在圆上返回1，如果在圆外返回2
    int get_tangent_pt(point pt,point* p)const;
};

struct GEO_DLL arc
{
    point me[3];

    arc(){}
    arc(const point&a,const point&b,const point&c){
        me[0] = a; me[1] = b; me[2] = c;
    }
    arc(double r,double start_a,double end_a);

    //描述：得到弓高，正数表示逆时针圆弧，负数表示顺时针圆弧
    double  sagitta()const;

    //描述：设置弓高，正数表示逆时针圆弧，负数表示顺时针圆弧
    void    sagitta(double t);

    //描述：得到this的时针方向，如果逆时针返回2，顺时针返回1，共线返回0
    int     direct()const;

    //描述：平移
    arc&    offset(point pt);

    //描述：得到圆心
    bool    center(point &o)const;

    //描述：得到圆心和半径平方
    bool    center(circle &o)const;

    //描述：得到圆心、半径平方和起始终止角度
    bool    center(circle &o,double &s,double &e)const;

    //描述：得到半径的平方，如果共线返回DBL_MAX
    double  radius2()const;

    //描述：根据圆心获得this的起始终止角度
    void    angle(const point &o,double &s,double &e)const;

    //描述：判断this是否三点共线
    bool    is_line(double tol2=0)const;

    //描述：判断圆上的点在圆弧的内部
    bool    is_inner(const point &pt)const;

    //描述：返回this的取值区间
    double  max_para()const{ return 2; }

    //描述：判断this是否是几何上有效的

    //描述：将this的x轴范围扩充到r中
    void    x_range(range &r)const;

    //描述：将this的y轴范围扩充到r中
    void    y_range(range &r)const;

    //描述：得到斜率
    point   tangent_at(double t)const;
    
    //描述：求this的长度
    double  length()const;
    
    //描述：求this的积分面积
    double  area()const;

    //描述：返回点pt和this的最近点在this上的参数
    double  nearest(const point &pt)const;

    //描述：返回点pt和this的最近点在this上的参数
    double  nearest_ex(const point &pt)const;

    //描述：返回this和pt的距离的平方
    double  dis2(const point &pt)const;

    //描述：返回参数为t的内点坐标
    point   point_at(double t)const;

    //描述：计算子线
    void    path_at(double star,double end,point *p)const;

    //描述：插入参数点，返回的out是this插入t中n个参数点之后的多段圆弧线
    //      函数返回后t中的值将修改为原来的参数点在out中的参数
    void    insert_at(double *t,int n,std::vector<point> &out)const;
    
    //描述：返回this和pt的穿越数
    int     across(const point &pt)const;

    //描述：求点pt在直线this的左右边，返回1表示左边，返回2表示右边，0表示共线
    int     left_right(const point &pt,double tol2)const;   

    //描述：算出L和this的交点在this上的参数，交点必须是L和this的内点
    //参数：t存放交点参数的地址
    //返回：交点个数+t
    double* intersect(const line *L,double *t)const;
    double* intersect(const arc *L,double *t)const;
    double* intersect(const bezier *L,double *t)const;
    double* intersect(const envelope& env,double *t)const;

    //描述：算出L和this的交点在this上的参数，交点可以是L和this的内点、端点、外点
    //参数：t存放交点参数的地址
    //返回：交点个数+t
    double* intersect_ex(const line *L,double *t)const;
    double* intersect_ex(const arc *L,double *t)const;
    double* intersect_ex(const bezier *L,double *t)const;

    //描述：求出this和参数曲线X(t),Y(t)的交点
    //返回：t为返回的参数曲线上的参数
    double* intersect_f(polynomial x,polynomial y,double* t)const;
    
    //描述：判断this是否和L相离
    bool    is_disjoin(const line *L,double tol2)const;
    bool    is_disjoin(const arc *L,double tol2)const;
    bool    is_disjoin(const bezier *L,double tol2)const;
    bool    is_disjoin(const envelope &env)const;
    
    //描述：判断this是否和L相穿
    bool    is_cross(const line *L,double tol)const;
    bool    is_cross(const arc *L,double tol)const;
    bool    is_cross(const bezier *L,double tol)const;

    //描述：判断pt是否和this的端点的距离平方小于tol2
    bool    is_near_port(const point &pt,double tol2)const;

    //描述：判断pt是否是this的内点，并得到内点的参数
    bool    is_inner_point(const point &pt,double tol2,double &t)const;

    //描述：将this内插成折线，保证每PI/num的角度变化就内插一个点
    void    interpolate(int num,std::vector<point> &out)const;

    //描述：将this内插成折线，内插后的折线和this之间的最大距离平方不超过tol2
    void    interpolate2(double tol2,std::vector<point> &out)const;

    //描述：判断this是否和l重叠，如果是返回重叠部分在this上的参数
    bool    is_lap(const arc& l,double tol2,double& t1,double& t2)const;
    
    //描述：判断this是否完全覆盖l
    bool    is_contain(const arc& l,double tol2)const;

    //描述：得到this和env中最近点的距离平方
    double  min_dis2(const envelope& env)const;

    //描述：得到this和env中最远点的距离平方
    double  max_dis2(const envelope& env)const;

    //描述：判断this是否为小弧
    bool    is_minor()const;

    //描述：用bezier拟合this
    //返回：返回值是拟合的精度
    double  bezier_fit(point* pt)const;

    //描述：将this分割成两个圆弧
    void    split2(arc* s1,arc* s2)const;

    //描述：返回圆弧的弧角
    double  angle()const;

    //描述：得到圆弧的中点(需要圆心半径)
    point   middle(const point& o,double r)const;

    //描述：保证起始终止点不变的情况下，修改圆弧使得起点处的切线为t
    void    set_star_tangent(point t);

    //描述：保证起始终止点不变的情况下，修改圆弧使得终点处的切线为t
    void    set_end_tangent(point t);
};

struct GEO_DLL bezier
{
    point me[4];

    bezier(){}
    bezier(const point&a,const point &b,const point &c,const point &d){
        me[0] = a; me[1] = b; me[2] = c; me[3] = d; 
    }

    //描述：在保持起点终点起点方向和终点方向不变的情况下
    //      让this变成一条二次贝赛尔曲线
    bool    to_bezier2();

    //描述：在保持起点终点和它们切线不变的情况下，使得中点为pt
    void    set_middle(point pt);

    //描述：将this的x轴的范围扩充到r中
    void    x_range(range &r)const;

    //描述：将this的y轴的范围扩充到r中
    void    y_range(range &r)const;

    //描述：返回this的取值区间
    double  max_para()const{ return 3; }
    
    //描述：求this的长度
    double  length()const;
    
    //描述：求this的积分面积
    double  area()const;

    //描述：返回点pt的最近点在this上的参数，参数在取值区间之内
    double  nearest(const point &pt)const;

    //描述：返回点pt的最近点在this上的参数，参数可能在取值区间之外
    double  nearest_ex(const point &pt)const;

    //描述：返回this和pt距离的平方
    double  dis2(const point &pt)const;

    //描述：返回参数为t的点坐标
    point   point_at(double t)const;

    //描述：计算子线
    void    path_at(double star,double end,point *mem)const;

    //描述：得到斜率
    point   tangent_at(double t)const;

    //描述：插入参数点，返回的out是this插入t中n个参数点之后的折线
    //      函数返回后t中的值将修改为原来的参数点在out中的参数
    void    insert_at(double *t,int n,std::vector<point> &out)const;
    
    //描述：返回this和pt的穿越数
    int     across(const point &pt)const;

    //描述：求点pt在直线this的左右边，返回1表示左边，返回2表示右边，0表示共线
    int     left_right(const point &pt,double tol2)const;   

    //描述：算出L和this的交点在this上的参数，交点必须是L和this的内点
    //参数：t存放交点参数的地址
    //返回：交点个数+t
    double* intersect(const line *L,double *t)const;
    double* intersect(const arc *L,double *t)const;
    double* intersect(const bezier *L,double *t)const;
    double* intersect(const pnode *L,double *t)const;
    double* intersect(const envelope& env,double *t)const;

    //描述：算出L和this的交点在this上的参数，交点可以是L和this的内点、端点、外点
    //参数：t存放交点参数的地址
    //返回：交点个数+t
    double* intersect_ex(const line *L,double *t)const;
    double* intersect_ex(const arc *L,double *t)const;
    double* intersect_ex(const bezier *L,double *t)const;

    //描述：求出this和L的交点
    void    intersect(const bezier *L,std::vector<point>& out)const;

    //描述：判断this是否和L相离
    bool    is_disjoin(const line *L,double tol2)const;
    bool    is_disjoin(const arc *L,double tol2)const;
    bool    is_disjoin(const bezier *L,double tol2)const;
    bool    is_disjoin(const envelope &env)const;    
    
    //描述：判断this是否和L相穿
    bool    is_cross(const line *L,double tol)const;
    bool    is_cross(const arc *L,double tol)const;
    bool    is_cross(const bezier *L,double tol)const;

    //描述：判断pt是否和this的端点的距离平方小于tol2
    bool    is_near_port(const point &pt,double tol2)const;

    //描述：判断pt是否是this的内点，并得到内点的参数
    bool    is_inner_point(const point &pt,double tol2,double &t)const;

    //描述：将this内插成折线，保证每PI/num的角度变化就内插一个点
    void    interpolate(int num,std::vector<point> &out)const;

    //描述：将this内插成折线，内插后的折线和this之间的最大距离平方不超过tol2
    void    interpolate2(double tol2,std::vector<point> &out)const;

    //描述：判断this是否和l重叠，如果是返回重叠部分在this上的参数
    bool    is_lap(const bezier& l,double tol2,double& t1,double& t2)const;
    
    //描述：判断this是否完全覆盖l
    bool    is_contain(const bezier& l,double tol2)const;

    //描述：得到参数方程
    void    function(polynomial* x,polynomial* y)const;

    //描述：得到拐点参数
    //返回：拐点的个数，三次贝塞耳曲线可能有2个拐点
    int     inflect_point(double* t)const;

    //描述：设置起点处的切线
    void    set_star_tangent(point t){ me[1] = me[0]+t; }

    //描述：设置终点处的切线
    void    set_end_tangent(point t){ me[2] = me[3]-t; }

    //描述：判断this是否四点共线
    bool    is_line(double tol2=0)const;

    //描述：用多个三点圆弧拟合贝塞耳曲线
    //参数：tol2控制拟合曲线和this的最大距离
    //返回：返回的vector描述了一个polyarc
    std::vector<point> polyarc(double tol2)const;

    //描述：得到this和env中最近点的距离平方
    double  min_dis2(const envelope& env)const;

    //描述：得到this和env中最远点的距离平方
    double  max_dis2(const envelope& env)const;
};

struct GEO_DLL pnode : point
{
    enum{ line_type,
        ctr_type,
        arc_type,
        bezier_type,
        err_type };

    union {
        unsigned char   m_type;         //this的类型 
        double          m_reserve;    //对齐8字节之用
    };
    
    pnode():m_type(0){m_reserve=0;}
    pnode(const point &pt):point(pt),m_reserve(0){}
    pnode(const point &pt,int type):point(pt),m_reserve(0){m_type=type;}
    
    line _line()const{ return line(this[0],this[1]); }
    arc _arc()const{ return arc(this[0],this[1],this[2]); }
    bezier _bezier()const{ return bezier(this[0],this[1],this[2],this[3]); }

    bool is_line()const{ return m_type==line_type; }
    bool is_arc()const{ return m_type==arc_type; }
    bool is_bezier()const{ return m_type==bezier_type; }
    bool is_ctr()const{ return m_type==ctr_type; }

    pnode& operator=(const point&a){ x=a.x; y=a.y; return *this;}

    //描述：返回this的取值区间
    double  max_para()const;

    //描述：求this的长度
    double  length()const;
    
    //描述：求this的积分面积
    double  area()const;

    //描述：返回this(不可扩充的)和点pt的最近点在this上的参数
    double  nearest(const point &pt)const;

    //描述：返回this(可扩充的)和点pt的最近点在this上的参数
    double  nearest_ex(const point &pt)const;

    //描述：得到this和点pt距离的平方
    double  dis2(const point &pt)const;

    //描述：返回参数为t的内点坐标
    point   point_at(double t)const;

    //描述：计算子线
    void    path_at(double star,double end,pnode *L)const;

    //描述：计算子线，返回的out是this插入t中n个参数点之后的曲线
    //      函数返回后t中的值将修改为原来的参数点在out中的参数
    void    insert_at(double *t,int n,std::vector<pnode> &out)const;
    
    //描述：将this的x轴的范围扩充到r中
    void    x_range(range &r)const;

    //描述：将this的x轴的范围扩充到r中
    void    y_range(range &r)const;

    //描述：得到斜率
    point   tangent_at(double t)const;
    
    //描述：返回this和pt的穿越数
    int     across(const point &pt)const;

    //描述：求点pt在直线this的左右边，返回1表示左边，返回2表示右边，0表示共线
    int     left_right(const point &pt,double tol2)const;

    //描述：算出L和this的交点在this上的参数，交点必须是L和this的内点
    //参数：t存放交点参数的地址
    //返回：交点个数+t
    double* intersect(const line *L,double *t)const;
    double* intersect(const arc *L,double *t)const;
    double* intersect(const bezier *L,double *t)const;
    double* intersect(const pnode *L,double *t)const;
    double* intersect(const envelope& env,double *t)const;

    //描述：算出L和this的交点在this上的参数，交点可以是L和this的内点、端点、外点
    //参数：t存放交点参数的地址
    //返回：交点个数+t
    double* intersect_ex(const line *L,double *t)const;
    double* intersect_ex(const arc *L,double *t)const;
    double* intersect_ex(const bezier *L,double *t)const;
    double* intersect_ex(const pnode *L,double *t)const;
    
    //描述：判断this是否和L相离
    bool    is_disjoin(const envelope &env)const;

    //描述：判断this是否和L相离
    bool    is_disjoin(const line *L,double tol2)const;
    bool    is_disjoin(const arc *L,double tol2)const;
    bool    is_disjoin(const bezier *L,double tol2)const;
    bool    is_disjoin(const pnode *L,double tol2)const;
        
    //描述：判断this是否和L相穿
    bool    is_cross(const line *L,double tol)const;
    bool    is_cross(const arc *L,double tol)const;
    bool    is_cross(const bezier *L,double tol)const;
    bool    is_cross(const pnode *L,double tol)const;

    //描述：判断pt是否和this的端点的距离平方小于tol2
    bool    is_near_port(const point &pt,double tol2)const;

    //描述：判断pt是否是this的内点，并得到内点的参数
    bool    is_inner_point(const point &pt,double tol2,double &t)const;

    //描述：得到下一条segment的地址
    pnode* next()const;

    //描述：得到上一条segment的地址
    pnode* prev()const;

    //描述：删除一些结构上几何上无效的东西
    pnode*   remove_invalid(double tol2);

    //描述：将this内插成折线
    void interpolate(int num,std::vector<point> &out)const;

    //描述：将this内插成折线，内插后的折线和this之间的最大距离平方不超过tol2
    void    interpolate2(double tol2,std::vector<point> &out)const;

    //描述：判断this是否和l重叠，如果是返回重叠部分在this上的参数
    bool    is_lap(const line& l,double tol2,double& t1,double& t2)const;
    bool    is_lap(const arc& l,double tol2,double& t1,double& t2)const;
    bool    is_lap(const bezier& l,double tol2,double& t1,double& t2)const;
    bool    is_lap(const pnode* l,double tol2,double& t1,double& t2)const;
    bool    is_lap(const line* l,double tol2,double& t1,double& t2)const{
        return is_lap(*l,tol2,t1,t2);
    }

    //描述：判断this是否完全覆盖l
    bool    is_contain(const line& l,double tol2)const;
    bool    is_contain(const arc& l,double tol2)const;
    bool    is_contain(const bezier& l,double tol2)const;
    bool    is_contain(const pnode* l,double tol2)const;
    bool    is_contain(const line* l,double tol2)const{
        return is_contain(*l,tol2);
    }

    //描述：判断this是否是一个好的segment的起点(判断的依据是m_type) 
    //注意：this后面必须有足够的空间否则会引起非法的内存读错误
    bool    is_good_segment()const;

    //描述：得到this和env中最近点的距离平方
    double  min_dis2(const envelope& env)const;

    //描述：得到this和env中最远点的距离平方
    double  max_dis2(const envelope& env)const;
};

inline bool is_zero(double t){ 
    return t<FLT_MIN && t>-FLT_MIN; 
}

inline bool is_equal(double a,double b,double tol){
    return a >= b-tol && a <= b+tol;
}

static inline int sign(double a){ 
    return a?a>0?1:-1:0; 
}
 

inline line::line(const arc* L){
    me[0] = L->me[0];
    me[1] = L->me[2];
}

//描述：计算以b为顶点a,b为两边的角度，返回值在[0,PI]之间
GEO_DLL double clip_angle(const point& a,const point& b,const point& c);

//描述：求解方程组a[0]*x+b[0]*y+c[0]=0; a[1]*x+b[1]*y+c[1]=0;
GEO_DLL bool solve(const double a[2],const double b[2],const double c[2],double &x,double &y);

//描述：判断三点是否在容差范围内共线
//参数：tol2是距离平方
GEO_DLL bool is_colinearity(const point &a,const point &b,const point &c,double tol2);

//描述：求点pt在直线se的左右边，返回1表示左边，返回2表示右边，0表示共线
inline int line_left_right(const point &s,const point &e,const point &pt)
{ double t = (s.x-pt.x)*(e.y-pt.y)-(e.x-pt.x)*(s.y-pt.y); return t>0 ? 1 : t<0? 2:0; }

//描述：计算a,b两点和直线se的左右关系的或，如果这个函数返回的值等于3，那么可以确信直线se和线段ab相交
inline int line_left_right2(const point &s,const point &e,const point &a,const point &b)
{ return line_left_right(s,e,a) | line_left_right(s,e,b); }

//描述：得到相反的左右关系
inline int reve_left_right(int r){ static int a[]={0,2,1,3}; return a[3&r]; }

//描述：得到segment的穿越数
inline int seg_across(const point* l,const point& pt){
    if( !is_marked(l) ) return ((line*)l)->across(pt);
    return ((pnode*)safe_ptr(l))->across(pt);
}

//描述：得到segment的穿越数
inline bool seg_is_disjoin(const point* l,const envelope& env){
    if( !is_marked(l) ) return ((line*)l)->is_disjoin(env);
    return ((pnode*)safe_ptr(l))->is_disjoin(env);
}

//描述：扩展对象l的外接矩形到env中
template<class type> inline
envelope& xy_range(const type *l,envelope &env){
    if( 0==(l=safe_ptr(l)) ) return env;
    l->x_range(env.x);
    l->y_range(env.y);
    return env;
} 
//描述：扩展对象l的外接矩形到env中
template<> inline
envelope& xy_range(const pnode *l,envelope &env){
	if( !is_marked(l) ) l=safe_ptr(l);
    l->x_range(env.x);
    l->y_range(env.y);
    return env;
}
//描述：扩展对象l的外接矩形到env中
template<> inline
envelope& xy_range(const line *l,envelope &env){
    if( !is_marked(l) ) l=safe_ptr(l);
	l->x_range(env.x);
    l->y_range(env.y);
    return env;
}
//描述：扩展对象l的外接矩形到env中
template<> inline
envelope& xy_range(const arc *l,envelope &env){
    if( !is_marked(l) ) l=safe_ptr(l);
	l->x_range(env.x);
    l->y_range(env.y);
    return env;
}
//描述：扩展对象l的外接矩形到env中
template<> inline
envelope& xy_range(const bezier *l,envelope &env){
    if( !is_marked(l) ) l=safe_ptr(l);
	l->x_range(env.x);
    l->y_range(env.y);
    return env;
}
//描述：得到对象的外接矩形
template<class type> inline
envelope xy_range(const type *l){ 
	envelope env;
	return xy_range( l,env); }

template<class type> inline
double x_length(const type *l){
    if( 0==(l=safe_ptr(l)) ) return 0;
    range r; l->x_range(r);
    return r.length();
}

template<class type> inline
double y_length(const type *l){
    if( 0==(l=safe_ptr(l)) ) return 0;
    range r; l->y_range(r);
    return r.length();
}

template<class type> inline
double xy_length(const type *l){
    double x = x_length(l), y = y_length(l);
    return x>y ? x:y;
}

//描述：分离A中的指针到B，C中
//参数：B中保留普通指针，C中保留反向指针
template<class type1,class type2,class type3>
void apart_ptr(const std::vector<type1> &A,std::vector<type2> &B,std::vector<type3> &C)
{
	if(A.empty()) return;
    type1* it = (type1*)&A.front();
    for(int i=A.size(); --i>=0; ++it)
    {
        if( is_marked(*it) ) C.push_back( (type3)safe_ptr(*it) );
        else B.push_back( (type2)(*it) );
    }
}

//描述：指针的单步前进或者后退
//说明：当n大于0的时候前进，当n小于0的时候后退
template<class type>
bool step_over(type& F,int& n)
{
	if( n==0 ) return false;
	if( n>0 ) --n,++F;
	else ++n,--F;
	return true;
}

inline envelope seg_env(point* l)
{
    if( !is_marked(l) )
        return envelope(l[0],l[1]).normalize();
    l = safe_ptr(l);
    return xy_range((pnode*)l);
}

//描述：返回两条线段夹角sin值的平方 2012.12.18 by fzn
GEO_DLL double line_sin2(const line& a,const line& b);

//描述：设置线段是否平行的容差(夹角sin值的平方) 2012.12.18 by fzn
GEO_DLL double set_line_paraval_tol(double val);

GEO_NAMESPACE_END


#endif // !defined(AFX_POINT_H__4BECF1C3_5A80_4AD0_8147_C4BC7089450D__INCLUDED_)
