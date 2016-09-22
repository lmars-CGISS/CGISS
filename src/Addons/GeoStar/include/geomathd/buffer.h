// buffer.h: interface for the buffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFER_H__C00A062C_1B18_4AEC_8107_19A5F98FD29B__INCLUDED_)
#define AFX_BUFFER_H__C00A062C_1B18_4AEC_8107_19A5F98FD29B__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class surface_unions;

class GEO_DLL buffer  
{
    surface_unions*         m_union;
    std::vector<point>      m_port;

    static path_ptr         _buffer_point(point pt,double r,int arc);
    static path_ptr         _buffer_line(point a,point b,double r,int arc);
    static path_ptr         _buffer_line(point a,point b,double r);
    static path_ptr         _buffer_arc(arc a,double r);
    static path_ptr         _buffer_ex(point a,point b,double radius);
    static path_ptr         _buffer_ex(point a,point b,point c,double radius);
    
    void                    get_single_port();

    void                    remove_arc(polyline* L,point pt);
    void                    remove_arc(curve* L,point pt);
    void                    remove_arc(path* L,point pt);

public:
    int                     m_arc;
    double                  m_radius;

    buffer(int a=4);

    virtual ~buffer();

    double radius(double r);

    void add(point pt);
    void add(const polyline *l);
    void add(const curve *l);
    void add(const path *l);

    //描述：清除add入this的缓冲区
    void clear();

    //描述：得到普通的缓冲区
    path_ptr get_buffer();

    //描述：得到去除圆弧的buffer
    path_ptr get_buffer_ex();

    //描述：得到平行线
    path_ptr get_paraval();
};

//描述：得到缓冲区
//参数：L是输入的path对象，如果L的对象维数为0那么计算点群的buffer；如果L的对象维数为1那么计算线的buffer；
//      如果L的对象维数大于1那么计算面的buffer，此时当radius大于0时返回buf和L的并，当radius小于0时返回L减去buf
//      radius是buffer的半径，当L为面的时候radius的正负将决定结果是外缓冲还是内缓冲，当L不是面的时候radius的正负值无区别
//      compress是压缩比率，如果compress不为0，程序会在运算前将L压缩一下
GEO_DLL path_ptr get_buffer(const path* L,double radius,int arc=4,double compress=0.1);

//描述：得到平头缓冲区
//参数：此函数忽略L的对象维数永远把L当作线看待，同时忽略radius的正负值
GEO_DLL path_ptr get_buffer_ex(const path* L,double radius,int arc=4,double compress=0.1);

//描述：得到单侧缓冲区
//参数：L是输入的path对象，程序忽略L的对象维数永远把L当做线看待；L必须连续否则返回0
//      radius是buffer的半径，当radius>0的时候得到左侧缓冲区，否则得到右侧缓冲区
GEO_DLL path_ptr get_single_buffer(const path* L,double radius,int arc=4,double compress=0.1);

GEO_NAMESPACE_END


#endif // !defined(AFX_BUFFER_H__C00A062C_1B18_4AEC_8107_19A5F98FD29B__INCLUDED_)
