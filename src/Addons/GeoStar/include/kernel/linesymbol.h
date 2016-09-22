#pragma once
#include "canvas.h" 
#include "pointsymbol.h"
using namespace std;

KERNEL_NS    
	
/// \brief 简单线符号
class GS_API GsSimpleLineSymbol:public GsLineSymbol
{
	GsPenPtr m_ptrPen;
	GsPenStyle m_pLineStyle;
protected: 
	/// \brief 绘制Canvas的path
	virtual void OnDraw(GsGraphicsPath* pPath,SPATIALANALYSIS_NS::path* pGeoPath);

	virtual void OnStartDrawing();
	virtual void OnEndDrawing();
public:
	GsSimpleLineSymbol();
	/// \brief 从颜色和线宽构造
	GsSimpleLineSymbol(const GsColor& color,double dblWidth = 0.1);
	virtual ~GsSimpleLineSymbol(); 

	/// \brief 获取线的类型
	GsPenStyle LineStyle();
	/// \brief 设置线的类型
	void LineStyle(GsPenStyle eStyle);
	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	virtual bool IsValid();
};
GS_SMARTER_PTR(GsSimpleLineSymbol);
DECLARE_CLASS_CREATE(GsSimpleLineSymbol);

struct GS_API GsPattern
{
	GsPattern()
	{
		fMark	= 0;
		fGap	= 0;
	}
	GsPattern(int mark, int gap)
	{
		fMark	= mark;
		fGap	= gap;
	}
	int fMark;
	int fGap;
};

/// \brief 
class GS_API GsSymbolTemplate:public std::vector<GsPattern>
{
	/// \brief 线头方向的偏移量
	float m_fOffset;
	float m_fInterval;
public:
	/// \brief 构造函数  
	GsSymbolTemplate(); 
	GsSymbolTemplate(float offset,float interval);
	GsSymbolTemplate(const GsSymbolTemplate& rhs);
	/// \brief 析构函数
	virtual ~GsSymbolTemplate();
	 
	/// \brief 获得线的偏移量
	float Offset();
	/// \brief 设置线的偏移量
	void Offset(float offset); 

	/// \brief 获得线的倍率
	float Interval();
	/// \brief 设置线的倍率
	void Interval(float interval); 

	/// \brief 加入一个线模板
	void Add(const GsPattern& pattern); 
	/// \brief 加入一个线模板
	void Add(float mark, float gap);
	/// \brief 重置线模板
	void Reset();
	 
	/// \brief 返回模板序列的首地址
	float* MakePattern();
};
class TemplateParser;
class GS_API GsTemplateLineSymbol: public GsLineSymbol
{
protected:
	GsSymbolTemplate m_template;
	double m_dblOffset;
	double m_dblMapOffset;
	TemplateParser* m_Parser;
protected:  
	/// \brief 几何数据操作
	/// \details 子类通过覆盖此函数实现绘制前对几何数据的处理，例如计算平行线
	virtual SpatialAnalysis::path_ptr GeometryOperator(SpatialAnalysis::path* pPath);
	
	/// \brief 以Geomathd的path进行绘制
	/// \details 线、或者面的子类符号可以覆盖此方法进行绘制。此方法在GeometryOperator方法之后被调用
	virtual void OnDraw(SpatialAnalysis::path* pPath);
	
	virtual void OnDrawSub(GsPoint* pPoint,double a){}
	
	virtual void OnStartDrawing();

	GsTemplateLineSymbol(); 

public:  
	/// \brief 析构函数
	virtual ~GsTemplateLineSymbol(); 

	/// \brief 获取线符号模版属性
	GsSymbolTemplate SymbolTemplate();
	
	/// \brief 获取线符号模版的指针
	/// \return 返回线符号模版的指针
	GsSymbolTemplate* SymbolTemplatePtr();

	/// \brief 设置线符号模版属性
	/// \param pTemplate 模版对象的指针
	void SymbolTemplate(const GsSymbolTemplate& pTemplate);

	/// \brief 设置线模板的偏移量
	/// \param offset 线模板的偏移量
	void Offset(double offset);

	/// \brief 获取线模板的偏移量
	double Offset();

};
GS_SMARTER_PTR(GsTemplateLineSymbol);



class GS_API GsPointLineSymbol:public GsTemplateLineSymbol
{
	GsPointSymbolPtr m_ptrPointSymbol;
	double m_dblSymAngle;

protected:
	/// \brief 绘制点
	virtual void OnDrawSub(GsPoint* pPoint,double a);

	/// \brief 判断是否可以绘制，SymbolTemplate和PointSymbol非空
	virtual bool IsValid();

	virtual void OnStartDrawing();
	virtual void OnEndDrawing();
public:
	/// \brief 默认构造函数
	GsPointLineSymbol();

	/// \brief 传入点符号构建
	GsPointLineSymbol(GsPointSymbol *pPointSymbol);

	/// \brief 传入点符号和模板构建
	GsPointLineSymbol(GsPointSymbol *pPointSymbol,GsSymbolTemplate symTemplate);

	/// \brief 析构函数
	virtual ~GsPointLineSymbol(); 
	
	/// \brief 设置点线符号中的点符号
	/// \param pPointSymbol 点符号的指针
	void PointSymbol(GsPointSymbol *pPointSymbol);

	/// \brief 获取点线符号中的点符号
	GsPointSymbol* PointSymbol();
};
GS_SMARTER_PTR(GsPointLineSymbol);
DECLARE_CLASS_CREATE(GsPointLineSymbol);

/// \brief 图框线图片方向
enum GsFramePicDirection
{
	ePicDirectionUp = 1,
	ePicDirectionDown = 2,
	ePicDirectionLeft = 3,
	ePicDirectionRight = 4
};

/// \brief 图框线符号
class GS_API GsFrameLineSymbol:public GsLineSymbol
{
	/// \brief 定义图框线的8个位置
	enum GsFrameElement
	{
		eLeftBottom,
		eRightBottom,
		eRightTop,
		eLeftTop,
		eBottom,
		eRight,
		eTop,
		eLeft,
	};
	/// \brief 记录8个元素位置的方向
	std::vector<GsFramePicDirection> m_ElementDirection;
	
	/// \brief 线的偏移
	double m_dblOffset;
	
	/// \brief 角落的图片和边上的图片内存块
	Utility::GsGrowByteBuffer m_CornerImage,m_SideImage;
	
	/// \brief 角落和边的的图片。
	Utility::GsImagePtr m_ptrCorner,m_ptrSide;
	
	/// \brief 透明色，背景色
	GsColor m_pTransparentColor,m_pBackColor;

	GsPenPtr m_ptrPen;
	GsTextureBrushPtr m_ptrBrush;
	/// \brief 是否使用线宽属性
	bool m_bUseWidth;
	/// \brief X、Y方向比例因子
	double m_XScale, m_YScale; 

	GsMatrix ComputerMatrix(double w, double h,float* l,int d,double sx=1.0,double sy = 1.0);
private:
	virtual void DrawSide(double* pSide,int nPointCount,int nIndex);
	virtual void DrawCorner(double* pCorner,int nIndex);


	virtual void DrawSingle(SpatialAnalysis::polyline* p);
	virtual void DrawSingle(SpatialAnalysis::path* p);
protected:	
	/// \brief 以Geomathd的path进行绘制
	/// \details 线、或者面的子类符号可以覆盖此方法进行绘制。此方法在GeometryOperator方法之后被调用
	virtual void OnDraw(SPATIALANALYSIS_NS::path* pPath);
	/// \brief 几何数据操作
	/// \details 子类通过覆盖此函数实现绘制前对几何数据的处理，例如计算平行线
	virtual SPATIALANALYSIS_NS::path_ptr GeometryOperator(SPATIALANALYSIS_NS::path* pPath);
	virtual void OnStartDrawing();
	virtual void OnEndDrawing();

public:
	GsFrameLineSymbol();
	GsFrameLineSymbol(const GsColor& color,double dblWidth = 0.1);
	virtual ~GsFrameLineSymbol(); 

	/// \brief 设置四角的图片
	void CornerPicture(Utility::GsImagePtr pImage);
	/// \brief 获取四角的图片
	Utility::GsImagePtr CornerPicture();
	/// \brief 设置四边的图片
	void SidePicture(Utility::GsImagePtr pImage);
	/// \brief 获取四边的图片
	Utility::GsImagePtr SidePicture();

	/// \brief 线的偏移
	double Offset();
	/// \brief 线的偏移
	void Offset(double off);

	/// \brief 设置透明色
	void TransparentColor (const GsColor& color);
	/// \brief 获取透明色
	GsColor TransparentColor ();
	/// \brief 设置背景色
	void BackColor (const GsColor& color);
	/// \brief 获取背景色
	GsColor BackColor ();

	/// \brief 设置X方向比例因子
	void XScale(double XScale);
	/// \brief 获取X方向比例因子
	double XScale();
	/// \brief 设置Y方向比例因子
	void YScale(double YScale);
	/// \brief 获取Y方向比例因子
	double YScale();

	/// \brief 设置是否使用线宽属性
	void UseWidth (bool bUseWidth);
	/// \brief 获取是否使用线宽属性
	bool UseWidth ();

	/// \brief 获取左上角图片方向
	GsFramePicDirection LeftTopDirection();
	/// \brief 设置左上角图片方向
	void LeftTopDirection(GsFramePicDirection LTDir);
	/// \brief 获取右上角图片方向
	GsFramePicDirection RightTopDirection();
	/// \brief 设置右上角图片方向
	void RightTopDirection(GsFramePicDirection RTDir);
	/// \brief 获取左下角图片方向
	GsFramePicDirection LeftBottomDirection();
	/// \brief 设置左下角图片方向
	void LeftBottomDirection(GsFramePicDirection LBDir);
	/// \brief 获取右下角图片方向
	GsFramePicDirection RightBottomDirection();
	/// \brief 设置右下角图片方向
	void RightBottomDirection(GsFramePicDirection RBDir);
	/// \brief 获取左边图片方向
	GsFramePicDirection LeftSideDirection();
	/// \brief 设置左边图片方向
	void LeftSideDirection(GsFramePicDirection LSideDir);
	/// \brief 获取上边图片方向
	GsFramePicDirection TopSideDirection();
	/// \brief 设置上边图片方向
	void TopSideDirection(GsFramePicDirection TSideDir);
	/// \brief 获取右边图片方向
	GsFramePicDirection RightSideDirection();
	/// \brief 设置右边图片方向
	void RightSideDirection(GsFramePicDirection RSideDir);
	/// \brief 获取下边图片方向
	GsFramePicDirection BottomSideDirection();
	/// \brief 设置下边图片方向
	void BottomSideDirection(GsFramePicDirection BSideDir);

	/// \brief 加载四角图片
	bool LoadCornerPicture(const char* strFileName);
	/// \brief 加载四边图片
	bool LoadSidePicture(const char* strFileName);
	  
};
GS_SMARTER_PTR(GsFrameLineSymbol);
DECLARE_CLASS_CREATE(GsFrameLineSymbol);

/// \brief 点符号方向
enum GsSymbolLocateDirectionType
{
	/// \brief 正北方向
	eDirectionNorth,
	/// \brief 左侧
	eDirectionLeft,
	/// \brief 右侧
    eDirectionRight,
	/// \brief 双侧
	eDirectionBidirectional,
	/// \brief 角平分线
	eDirectionBisector,
};

/// \brief 端点类型
enum GsSymbolLocateEndsType
{
	/// \brief 不绘端点
	eLocateNone,
	/// \brief 仅绘起点
	eLocateBegin,
	/// \brief 仅绘终点
	eLocateEnd,
	/// \brief 绘两端点
	eLocateBoth,
};

/// \brief 定位点线符号
class GS_API GsLocatePointLineSymbol:public GsLineSymbol
{
	GsPointSymbolPtr                m_ptrPointSymbol;
	GsSymbolLocateDirectionType     m_eDirType;
	GsSymbolLocateEndsType          m_eEndsType;
	Utility::GsImagePtr             m_ptrImage;

	double                          m_dblXmin;
	double                          m_dblYmax;
	long							m_nStartPos;
	long							m_nEndPos;

public:
	/// \brief 默认构造
	GsLocatePointLineSymbol();
	/// \brief 通过点符号构造
	GsLocatePointLineSymbol(GsPointSymbolPtr ptrPointSym);

public:
	/// \brief 设置点符号
	void PointSymbol(GsPointSymbolPtr ptrPointSym);
	/// \brief 获得点符号
	GsPointSymbol* PointSymbol();

	/// \brief 设置点符号方向
	void LocateDirection(GsSymbolLocateDirectionType eType);
	/// \brief 获取点符号方向
	GsSymbolLocateDirectionType LocateDirection();

	/// \brief 设置端点绘制方式
	void LocateEnds(GsSymbolLocateEndsType eType);
	/// \brief 获取端点绘制方式
	GsSymbolLocateEndsType LocateEnds();

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	virtual bool IsValid();

protected:
	/// \brief 以Geomathd的path进行绘制
	/// \details 线、或者面的子类符号可以覆盖此方法进行绘制。此方法在GeometryOperator方法之后被调用
	virtual void OnDraw(SPATIALANALYSIS_NS::path* pPath);

	virtual void OnStartDrawing();
	virtual void OnEndDrawing();
protected:
	/// \brief 点符号生成位图
	bool CreateSymbolBitmap();
	/// \brief 初始化成员
	void InitProp();
	/// \brief 根据GsSymbolLocateEndsType过滤顶点
	void FilterVertex();
	/// \brief 绘制图片
	void DrawBitmap(float fX, float fY);
	/// \brief 根据屏幕坐标计算贴图坐标
	void CalcuBitmapPosition(SPATIALANALYSIS_NS::path* pPath, GsSymbolLocateDirectionType eDirectionType);
	//计算点符号旋转角度
	double RoundAngle(SPATIALANALYSIS_NS::path* pPath, int nCurrentIndex, int nPointCount, GsSymbolLocateDirectionType eDirectionType);
	//根据向量计算角度
	double Angle(GsRawPoint gsPoint);
};
GS_SMARTER_PTR(GsLocatePointLineSymbol);
DECLARE_CLASS_CREATE(GsLocatePointLineSymbol);

/// \brief 图框线符号
class GS_API GsHashLineSymbol:public GsTemplateLineSymbol
{
protected:
	//实际的绘制线
	GsLineSymbolPtr		m_ptrLineSymbol;
	//设置子线和原线的夹角
	double			m_Angle ;
	//子线符号的线宽
	double			m_dblSubLineWidth;


protected:
	/// \brief 开始绘制
	virtual void OnStartDrawing();
	/// \brief 结束绘制
	virtual void OnEndDrawing();

protected:	
	/// \brief 根据点位置和角度来做实际绘制
	virtual void OnDrawSub(GsPoint* pPoint,double a);

public:
	/// \brief 返回线符号
	GsLineSymbol* LineSymbol();
	/// \brief 设置线符号
	void LineSymbol( GsLineSymbol* pLineSymbol);
	/// \brief 获取子线和原线的夹角
	double Angle();
	/// \brief 设置子线和原线的夹角
	void Angle(double Angle);

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	virtual bool IsValid();
	
	

};
GS_SMARTER_PTR(GsHashLineSymbol);
DECLARE_CLASS_CREATE(GsHashLineSymbol);
/// \brief 制图线端套类型
enum GsLineCapStyle
{
	eLineCapButt = 512,
	eLineCapRound = 0,
	eLineCapSquare = 256
};

/// \brief 制图线接合类型
enum GsLineJoinStyle
{
	eLineJoinMiter = 8192,
	eLineJoinRound = 0,
	eLineJoinBevel = 4096
};

/// \brief 制图线符号
class GS_API GsCartographicLineSymbol:public GsTemplateLineSymbol

{
protected: 
	GsLineCapStyle     m_CapStyle;     //符号端套类型
	GsLineJoinStyle    m_JoinStyle;     //线段接头类型
	double               m_dblMiterLimit;	  //线端斜面接合限值属性
	GsPenPtr			m_ptrPen;		//画笔
protected: 
	virtual void OnStartDrawing();
	virtual void OnEndDrawing();
	 
	/// \details 线、或者面的子类符号可以覆盖此方法进行绘制。此方法在GeometryOperator方法之后被调用
	virtual void OnDraw(SPATIALANALYSIS_NS::path* pPath);
	
	/// \brief 绘制Canvas的path
	virtual void OnDraw(GsGraphicsPath* pPath,SPATIALANALYSIS_NS::path* pGeoPath);

public:
	GsCartographicLineSymbol();
	GsCartographicLineSymbol(const GsColor& color,double dblWidth = 0.1);
	virtual ~GsCartographicLineSymbol(); 

	/// \brief 获取端套类型
	GsLineCapStyle	CapStyle();
	/// \brief 设置端套类型
	void CapStyle(GsLineCapStyle Style );

	/// \brief 获取接头类型
	GsLineJoinStyle JoinStyle();
	/// \brief 设置接头类型
	void JoinStyle(GsLineJoinStyle Style );

    /// \brief 获取制图线的线端斜面接合限值
	double MiterLimit();
	/// \brief 设置制图线的线端斜面接合限值
	void MiterLimit(double Limit );

	/// \brief 符号是否有效
	/// \details 符号是否会在画布上绘制内容，如果符号不会在画布上绘制任何的内容则不需要执行绘制过程。
	virtual bool IsValid();
};



GS_SMARTER_PTR(GsCartographicLineSymbol);
DECLARE_CLASS_CREATE(GsCartographicLineSymbol);


class GS_API GsLeadConnectedLineSymbol:public GsLineSymbol
{
protected:
	double m_dblInterval;	//单线之间的间隔
	GsLineSymbolPtr m_ptrLineSymbol; //绘制的线型符号

public:
	/// \brief 构造函数，无参构造函数使用简单线符号进行导线的绘制
	GsLeadConnectedLineSymbol();
	/// \brief 构造函数，使用给定的颜色和宽度构造简单线符号进行导线的绘制
	GsLeadConnectedLineSymbol(const GsColor& color,double dblWidth = 0.1);
	/// \brief 构造函数，使用给定的线符号进行导线的绘制
	GsLeadConnectedLineSymbol(GsLineSymbol* ptrLineSymbol);
	/// \brief 析构函数
	virtual ~GsLeadConnectedLineSymbol();
	/// \brief 获取单线之间的间隔
	double Interval();
	/// \brief 设置单线之间的间隔
	void Interval(double interval);
	/// \berif 获取线型符号
	GsLineSymbolPtr LineSymbol();
	/// \brief 设置线型符号
	void LineSymbol(GsLineSymbol* ptrLineSymbol);

	/// \brief 重写父类方法。获取线符号的宽度,单位毫米
	virtual double Width();
	/// \brief 重写父类方法。设置线符号的宽度,单位毫米
	virtual void Width(double dblWidth);

	/// \brief 重写父类方法。获取线符号颜色
	virtual GsColor Color();
	/// \brief 重写父类方法。设置线符号颜色
	virtual void Color(const GsColor& c);

protected:
	
	/// \brief 当绘制的时候发生
	/// \details 子类通过覆盖此方法实现实际的绘制
	virtual void OnDraw(GsGeometryBlob* pBuffer);

	/// \brief 当开始绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据准备
	virtual void OnStartDrawing();
	/// \brief 当结束绘制的时候发生
	/// \details 子类通过覆盖此方法实现自定义的数据回收过程
	virtual void OnEndDrawing();


private:
	/// \brief 根据间隔处理单条path（直线或弧线）
	/// \param ptrPath 需要使用Interval间隔打断的path
	/// \return 返回劈裂的path集合
	void SplitPath(SpatialAnalysis::path* ptrPath, SpatialAnalysis::multi_path* multipath);
	void Process(SpatialAnalysis::curve* pCurve, SpatialAnalysis::multi_path* multiPath);
	void Process(SpatialAnalysis::polyline* pPolyline, SpatialAnalysis::multi_path* multiPath);
};

GS_SMARTER_PTR(GsLeadConnectedLineSymbol);
DECLARE_CLASS_CREATE(GsLeadConnectedLineSymbol);

KERNEL_ENDNS
