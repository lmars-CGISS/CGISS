#pragma once
#include "preconfig.h" 
#include "object.h"
#include "memorymanager.h"
#include <fstream>
#include "vectorhelp.h"

UTILITY_NS 

/// \brief 创建一个int类型的点结构体
struct GS_API GsPT
{
	int X,Y;
	GsPT();
	GsPT(const GsPT& rhs);
	GsPT(int x,int y);
	
	/// \brief 点Offset点
	GsPT operator +(const GsPT & pt) const;
	
	/// \brief offset自身
	GsPT& operator +=(const GsPT & pt);

	/// \brief 点Offset点
	GsPT operator -(const GsPT & pt) const;
	
	/// \brief offset自身
	GsPT& operator -=(const GsPT & pt);


};

/// \brief 创建一个float类型的点结构体
struct GS_API GsPTF
{
	float X,Y;

	/// \brief 缺省构造函数
	GsPTF();
	/// \brief 重载构造函数
	GsPTF(const GsPT& rhs);
	/// \brief 重载构造函数
	GsPTF(const GsPTF& rhs);
	/// \brief 重载构造函数
	GsPTF(int x,int y);
	/// \brief 重载构造函数
	GsPTF(float x,float y);

	/// \brief 点Offset点
	GsPTF operator +(const GsPTF & pt) const;
	
	/// \brief offset自身
	GsPTF& operator +=(const GsPTF & pt);
	
	/// \brief 点Offset点
	GsPTF operator -(const GsPTF & pt) const;
	
	/// \brief offset自身
	GsPTF& operator -=(const GsPTF & pt);
};

/// \brief 设置int型宽度和高度
struct GS_API GsSize
{
	int Width,Height;
	/// \brief 缺省构造函数
	GsSize();
	/// \brief 重载构造函数
	GsSize(const GsSize& s);
	/// \brief 从点构造
	GsSize(const GsPT& p);
	/// \brief 重载构造函数
	GsSize(int w,int h);
	
	/// \brief 是否相等
	bool operator == (const GsSize& s)const;
	/// \brief 复制
	GsSize &operator = (const GsSize& s);
	/// \brief 是否不等
	bool operator != (const GsSize& s)const;

};

/// \brief 设置float型宽度和高度
struct GS_API GsSizeF
{
	float Width,Height;
	/// \brief 缺省构造函数
	GsSizeF();
	/// \brief 重载构造函数
	GsSizeF(const GsSize& s);
	/// \brief 重载构造函数
	GsSizeF(const GsSizeF& s);
	/// \brief 重载构造函数
	GsSizeF(int w,int h);
};

/// \brief 创建一个int类型的矩形
struct GS_API GsRect
{
	int Left,Right,Top,Bottom;
	/// \brief 缺省构造函数
	GsRect();
	/// \brief 重载构造函数
	GsRect(const GsPT& pt,const GsSize& s);
	/// \brief 重载构造函数
	GsRect(const GsRect& rhs);
	/// \brief 重载构造函数
	GsRect(int x,int y,int w,int h);
	/// \brief 设置宽度
	int Width()const;
	/// \brief 设置高度
	int Height()const;
	/// \brief 偏移一个位置
	GsRect& Offset(const GsPT& pt);

	/// \brief 中心点
	GsPT Center()const;

	/// \brief 是否相交
	bool IsIntersects(const GsRect& rhs)const;

	/// \brief 计算两个相交的部分
	GsRect Intersects(const GsRect& rhs) const;

	/// \brief 是否和线相离
	bool IsDisjoin(int x1,int y1,int x2,int y2)const;

	/// \brief 是否相离
	bool IsDisjoin(const GsRect& rhs)const;

	/// \brief 是否包含
	bool IsContain(int x,int y)const;

	/// \brief 是否包含
	bool IsContain(const GsPT& pt)const;

	/// \brief 是否包含
	bool IsContain(const GsRect& rhs)const;

	/// \brief 定位点
	GsPT Location()const;
	
	/// \brief 大小
	GsSize Size() const;

	/// \brief 左上角
	GsPT LeftTop()const;
	
	/// \brief 右上角
	GsPT RightTop()const;
	
	/// \brief 左下角
	GsPT LeftBottom()const;
	
	/// \brief 右下角
	GsPT RightBottom()const;

	/// \brief 矩形偏移
	GsRect operator + (const GsPT& pt)const;

	/// \brief 矩形偏移
	GsRect operator - (const GsPT& pt)const;

	/// \brief 矩形偏移返回新的偏移后的矩形
	GsRect OffsetTo(const GsPT& pt)const;

	/// \brief 矩形合并
	GsRect operator + (const GsRect& rect)const;
	/// \brief 合并到自身
	GsRect& operator += (const GsRect& rect);
	
	/// \brief 矩形合并
	GsRect& Union(const GsRect& rect);

};

/// \brief 创建一个float类型的矩形
struct GS_API GsRectF
{
	float Left,Right,Top,Bottom;

	/// \brief 缺省构造函数
	GsRectF();
	/// \brief 构造函数重载
	GsRectF(const GsPTF& pt,const GsSizeF& s);
	/// \brief 构造函数重载
	GsRectF(const GsPT& pt,const GsSize& s);
	/// \brief 构造函数重载
	GsRectF(const GsRect& rhs);
	/// \brief 构造函数重载
	GsRectF(const GsRectF& rhs);
	/// \brief 构造函数重载
	GsRectF(int x,int y,int w,int h);
	/// \brief 构造函数重载
	GsRectF(float x,float y,float w,float h);
	/// \brief 设置宽度
	float Width()const;
	/// \brief 设置高度
	float Height()const;

	GsRectF& Offset(const GsPTF& pt);

	/// \brief 中心点
	GsPTF Center()const;

	/// \brief 是否相交
	bool IsIntersects(const GsRectF& rhs)const;
	/// \brief 计算两个相交的部分
	GsRectF Intersects(const GsRectF& rhs) const;

	/// \brief 是否和线相离
	bool IsDisjoin(float x1,float y1,float x2,float y2)const;

	/// \brief 是否相离
	bool IsDisjoin(const GsRectF& rhs)const;

	/// \brief 是否包含
	bool IsContain(float x,float y)const;

	/// \brief 是否包含
	bool IsContain(const GsPTF& pt)const;

	/// \brief 是否包含
	bool IsContain(const GsRectF& rhs)const;

	/// \brief 定位点
	GsPTF Location();
	
	/// \brief 大小
	GsSizeF Size();

	/// \brief 左上角
	GsPTF LeftTop();
	
	/// \brief 右上角
	GsPTF RightTop();
	
	/// \brief 左下角
	GsPTF LeftBottom();
	
	/// \brief 右下角
	GsPTF RightBottom();

	/// \brief 矩形合并
	GsRectF operator + (const GsRectF& rect)const;
	/// \brief 合并到自身
	GsRectF& operator += (const GsRectF& rect);
	
	/// \brief 矩形合并
	GsRectF& Union(const GsRectF& rect);


	/// \brief 矩形偏移
	GsRectF operator + (const GsPTF& pt)const;

	/// \brief 矩形偏移
	GsRectF operator - (const GsPTF& pt)const;

	/// \brief 矩形偏移返回新的偏移后的矩形
	GsRectF OffsetTo(const GsPTF& pt)const;


	/// \brief 矩形偏移
	GsRectF operator + (const GsPT& pt)const;

	/// \brief 矩形偏移
	GsRectF operator - (const GsPT& pt)const;

	/// \brief 矩形偏移返回新的偏移后的矩形
	GsRectF OffsetTo(const GsPT& pt)const;


};

/// \brief 影像对象
class GS_API GsImage:public GsRefObject
{
public:
	/// \brief 析构函数
	virtual ~GsImage();
	/// \brief 设置宽度
	virtual unsigned int Width() = 0;
	/// \brief 设置高度
	virtual unsigned int Height() = 0;
	
	/// \brief 获取图像的字节数组，并非所有图像都能够成功
	virtual const unsigned char* Bit() = 0;

	/// \brief 图像一行的字节长度
	virtual unsigned int Stride();

	/// \brief 获取某行的首指针
	virtual const unsigned char* Row(int r);

	/// \brief 保存图像为PNG格式文件
	virtual bool SavePNG(const char* strFile);
	
	/// \brief 保存图像为PNG格式的内存块。
	virtual bool SavePNG(GsByteBuffer* pBuffer);

	/// \brief 保存图像为JPEG格式文件
	virtual bool SaveJPEG(const char* strFile,int nQuality=75);
	
	/// \brief 保存图像为JPEG格式的内存块。
	virtual bool SaveJPEG(GsByteBuffer* pBuffer,int nQuality=75);

	/// \brief 从文件载入生成图像
	static GsSmarterPtr<GsImage> LoadFrom(const char* strFile);

	/// \brief 从内存块载入生成图像对象
	static GsSmarterPtr<GsImage> LoadFrom(const unsigned char *pBlob,int nLen);
};
GS_SMARTER_PTR(GsImage);

/// \brief 内存中存储的简单位图对象
class GS_API GsSimpleBitmap:public GsImage
{
protected:
	GsGrowByteBuffer m_Buffer;
	int m_nWidth;
	int m_nHeight;
	int m_nBpp;
public :
	/// \brief 重载构造函数
	GsSimpleBitmap(unsigned int nWidth,unsigned int nHeight,int nBpp = 32); 
	
	/// \brief 解码文件格式的图像
	GsSimpleBitmap(const char* strFile); 
	/// \brief 解码内存中的图像
	GsSimpleBitmap(const unsigned char* blob,int nLen); 

	/// \brief 析构函数
	virtual ~GsSimpleBitmap();
	/// \brief 设置宽度
	virtual unsigned int Width();
	/// \brief 设置高度
	virtual unsigned int Height() ;
	/// \brief 获取图像的字节数组，并非所有图像都能够成功
	virtual const unsigned char* Bit() ;
	
	/// \brief 图像一行的字节长度
	virtual unsigned int Stride();
};
GS_SMARTER_PTR(GsSimpleBitmap);
 

/// \brief 基于NetPbm的PAM格式文件影像
/// \details http://netpbm.sourceforge.net/
class GS_API GsPAMBitmap:public GsImage
{
	int m_nWidth;
	int m_nHeight;
	int m_nBpp;
	GsVector<unsigned char> m_RowData;
	std::fstream m_fStream;
	mutable std::fstream::pos_type m_nPixelBegin; 
public:
	GsPAMBitmap(const char* strFile);
	GsPAMBitmap(const char* strFile,int w,int h);

	/// \brief 设置宽度
	virtual unsigned int Width();
	/// \brief 设置高度
	virtual unsigned int Height() ;
	/// \brief 获取图像的字节数组，并非所有图像都能够成功
	virtual const unsigned char* Bit() ;
	
	/// \brief 图像一行的字节长度
	virtual unsigned int Stride();

	/// \brief 获取某行的首指针
	virtual const unsigned char* Row(int r);

	/// \brief 获取某行的首指针
	virtual const unsigned char* Row(int r,GsVector<unsigned char> *vec);

	/// \brief 写入某行的数据
	virtual void Row(int r,const unsigned char* pRowData,int nLen);
};
GS_SMARTER_PTR(GsPAMBitmap);
UTILITY_ENDNS