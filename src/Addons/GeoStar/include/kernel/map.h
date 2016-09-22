#pragma once
#include "../utility/preconfig.h"
#include <utility.h> 
#include <geometry.h>
#include <geodatabase.h>
#include <paintdevice.h>
#include <label.h>

#include <symbol.h>
#include <pointsymbol.h>
#include <linesymbol.h>
#include <fillsymbol.h>
#include <spatialreference.h>

#include <list>
#include <map>
#include <memory>
class AggGraphics;
KERNEL_NS 
/// \brief 显示对象
/// \details 代表地图的显示设备
class GS_API GsDisplay:public Utility::GsRefObject
{
protected:
	/// \brief 背景颜色
	GsColor						m_BackGroundColor;
	/// \brief 显示坐标转换
	GsDisplayTransformationPtr	m_ptrDT;
	/// \brief 绘制的画布
	GsCanvasPtr					m_ptrCanvas; 

	/// \brief 标注避让容器
	GsLabelContainerPtr			m_ptrLabelContainer;
protected:
	/// \brief 激发OnAfterStartDrawing事件
	virtual void FireAfterStartDrawing();
	/// \brief 激发OnBeforeEndDrawing事件
	virtual void FireBeforeEndDrawing();
	/// \brief 激发OnAfterEndDrawing事件
	virtual void FireAfterEndDrawing();

	
	/// \brief 缺省构造
	GsDisplay(); 
public:
	/// \brief 事件，在Display的StartDrawing方法之后激发
	Utility::GsDelegate<void(GsDisplay*)> OnAfterStartDrawing;
	/// \brief 在Display结束之前激发
	/// \details 响应此事件向Display上绘制数据不会记录到Cache中
	Utility::GsDelegate<void(GsDisplay*)> OnBeforeEndDrawing;
	/// \brief 在Display结束之前激发
	/// \details 响应此事件向Display上绘制数据不会记录到Cache中
	Utility::GsDelegate<void(GsDisplay*)> OnAfterEndDrawing;

public:
	GsDisplay(GsCanvas* pCanvas,GsDisplayTransformation* pDT);
	virtual ~GsDisplay(); 

	/// \brief 获取自动标注避让容器
	GsLabelContainer* LabelContainer();
	/// \brief 获取自动标注避让容器
	void LabelContainer(GsLabelContainer* con);

	/// \brief 当前显示的地理范围
	/// \return 返回显示地物范围的Box 
	virtual GsBox ClipEnvelope();

	/// \brief 获取绘制的背景颜色
	/// \return 返回背景颜色
	virtual GsColor  BackColor();

	/// \brief 设置绘制的背景颜色
	/// \param c 背景颜色
	virtual void BackColor(const GsColor& c);

	/// \brief 开始绘制
	virtual void StartDrawing();
	/// \brief 结束绘制
	virtual void EndDrawing(); 

	/// \brief 提交绘制内容
	virtual void Flush();
	
	/// \brief 获取绘制用的画布
	virtual GsCanvas* Canvas();
	
	/// \brief 获取坐标转换对象
	/// \return 返回坐标转换对象指针
	virtual GsDisplayTransformation* DisplayTransformation();
};
/// \brief GsDisplayPtr
GS_SMARTER_PTR(GsDisplay);


/// \brief 取消追踪
class GS_API GsTrackCancel:public Utility::GsRefObject
{
	volatile long long m_Tick,m_StartTick;
	volatile unsigned int m_nInterval ;
	volatile bool m_bCanced;
	Utility::GsString m_strName;
public:
	/// \brief 缺省构造
	GsTrackCancel();
	virtual ~GsTrackCancel();

	/// \brief 获取名称
	Utility::GsString  Name();
	/// \brief 设置名称
	void Name(const char* strName);

	/// \brief 开始计时
	/// \param  nMilliseconds 计时周期，单位毫秒，缺省200毫秒
	virtual void StartTimer(unsigned int nMilliseconds = 200);
	
	/// \brief 结束计时
	virtual long long FinishTimer();
	/// \brief 是否到达一个计时周期
	virtual bool TimerFired();
	/// \brief 重置取消状态
	virtual void Reset();
	/// \brief 取消
	virtual void Cancel();

	/// \brief 可否继续
	/// \details 是否调用Cancel进行取消
	/// \return 返回是否处于取消状态
	virtual bool Continue();

	/// \brief 导致计时器立刻被激发
	virtual void FireTimer();
	
public:
	/// \brief 事件，当外部调用Cancel方法时发生
	Utility::GsDelegate<void(GsTrackCancel*,const char*)> OnCancel;
	
	/// \brief 事件，当调用StartTimer时发生
	Utility::GsDelegate<void(GsTrackCancel*,const char*)> OnStartTimer;
	/// \brief 事件，FinishTimer时发生
	Utility::GsDelegate<void(GsTrackCancel*,const char*,long long)> OnFinishTimer;
};
/// \brief GsTrackCancelPtr
GS_SMARTER_PTR(GsTrackCancel);

/// \brief 屏幕显示对象
/// \details 将可绘制设备封装成为屏幕绘制显示对象
class GS_API GsScreenDisplay:public GsDisplay
{
	GsCanvasPtr m_ptrWindowCanvas;
	GsPaintDevicePtr m_ptrDevice; 
	
	/// \brief 是否处于记录状态
	volatile bool m_bRecording;
	/// \brief 是否处于漫游状态
	volatile bool m_bPaning;

	/// \brief 漫游的开始位置和正在漫游的位置。
	GsRawPoint m_PanStart,m_PanMove;
	Utility::GsLock m_Lock;
	/// \brief 漫游的开始位置和正在漫游的位置。
	Utility::GsPT	m_PanStartPt,m_PanMovePt; 

	/// \brief 记录队列。
	std::list<GsImageCanvasPtr> m_RecordingQueue;
public:
	/// \brief 根据可绘制设备以及坐标转换对象构造
	/// \param  pDevice 可绘制对象
	/// \param  pDT 设备坐标转换对象
	GsScreenDisplay(GsPaintDevice* pDevice,GsDisplayTransformation* pDT);
	GsScreenDisplay(GsDisplayTransformation* pDT);
	GsScreenDisplay();

	virtual ~GsScreenDisplay();
	
	/// \brief 绑定设备
	void BindDevice(GsPaintDevice* pDevice);

	/// \brief 开始记录。
	GsImageCanvas* BeginRecording();
	
	/// \brief 正用于记录的画布
	GsImageCanvas* RecordingCanvas();
	 

	/// \brief 结束记录
	void EndRecording();

	/// \brief 从地理坐标开始漫游
	/// \param  x 地理x坐标
	/// \param  y 地理y坐标
	virtual void PanStart(double x,double y);

	/// \brief 漫游到地理坐标
	/// \param  x 地理x坐标
	/// \param  y 地理y坐标
	virtual void PanMoveTo(double x,double y);

	/// \brief 停止漫游
	/// \return 返回漫游结束时应该实现的地理范围
	virtual GsBox PanStop();

	virtual bool HasStartPan();
	
	/// \brief 将缓存的内容绘制到设备上
	/// \param  pt 绘制偏移的像素坐标
	virtual void Paint(const Utility::GsPT& pt = Utility::GsPT());

	/// \brief 当绘制设备发生变化时
	virtual void OnSizeChanged();
	/// \brief 开始绘制
	virtual void StartDrawing();
	/// \brief 结束绘制
	virtual void EndDrawing();
	/// \brief 提交绘制结果到屏幕
	virtual void Flush();
	 

};
/// \brief GsScreenDisplayPtr
GS_SMARTER_PTR(GsScreenDisplay);


/// \brief 绘制的阶段
enum GsDrawPhase
{
	/// \brief 通用绘制
	eDrawNormal = 1,
    /// \brief 绘制选择集
	eDrawSelectionSet = 2,
};

/// \brief 图形的抽象基类
class GS_API GsLayer:public Utility::GsRefObject
{
protected:
	/// \brief 图层的名称
	Utility::GsString m_strName;
	
	/// \brief 图层的别名
	Utility::GsString m_strAliasName;

	/// \brief 图层是否可见
	volatile bool m_bVisible;
	/// \brief 最小可见比例尺
	volatile double m_dblMinScale;
	/// \brief 最大可见比例尺
	volatile double m_dblMaxScale;

	/// \brief 参考比例尺
	volatile double m_dblReferenceScale;

	/// \brief 用户附加数据。
	Utility::GsAny m_Tag;

	/// \brief 内部绘制入口
	/// \details 子类通过覆盖此函数实现绘制。
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);
	
	GsLayer();
public:
	
	virtual ~GsLayer();
	
	
	/// \brief 图层的名称
	virtual Utility::GsString Name();
	/// \brief 设置图层的名称
	virtual void Name(const char* strName);

	/// \brief 图层的别名
	virtual Utility::GsString AliasName();
	/// \brief 设置图层的别名
	virtual void AliasName(const char* strName);

	/// \brief 图层是否可见
	virtual bool Visible();
	/// \brief 设置图层是否可见
	virtual void Visible(bool bVisible);

	/// \brief 参考比例尺
	virtual double ReferenceScale();
	/// \brief 参考比例尺
	virtual void ReferenceScale(double dblScale);

	/// \brief 图层最小可见比例尺
	virtual double MinScale();
	/// \brief 设置图层最小可见比例尺
	virtual void MinScale(double dblScale);

	/// \brief 图层最大可见比例尺
	virtual double MaxScale();
	/// \brief 设置图层最大可见比例尺
	virtual void MaxScale(double dblScale);
	
	/// \brief 图层的名称
	virtual Utility::GsAny Tag();
	/// \brief 设置图层的名称
	virtual void Tag(const Utility::GsAny& any);

	/// \brief 是否有效
	virtual bool IsValid();

	/// \brief 图层的最大范围,以图层的空间参考显示
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0) = 0;
	
	/// \brief 图层是否存在选择集
	virtual bool HasSelection() = 0;

	/// \brief 图层的空间参考
	virtual GsSpatialReference* SpatialReference();

	/// \brief 图形绘制入口
	/// \param pDislay 绘制对象
	/// \param pCancel 绘制取消对象
	virtual bool Draw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);

	
};
/// \brief GsLayerPtr
GS_SMARTER_PTR(GsLayer);

/// \brief 复合图层
class GS_API GsMultiLayer:public GsLayer
{
	/// \brief 图形列表
	std::vector<GsLayerPtr> m_lstLayers;
protected:
	/// \brief 内部绘制入口
	/// \details 子类通过覆盖此函数实现绘制。
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);
public:
	GsMultiLayer();
	virtual ~GsMultiLayer();
	/// \brief 获取图层列表对象指针
	GsVector<GsLayerPtr >* Layers();
	
	/// \brief 图层的最大范围
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);
	/// \brief 图层是否存在选择集
	virtual bool HasSelection();
	/// \brief 图层的空间参考
	virtual GsSpatialReference* SpatialReference();
	
	/// \brief 是否有效
	virtual bool IsValid();


};
/// \brief GsMultiLayerPtr
GS_SMARTER_PTR(GsMultiLayer);

/// \brief 地图对象
/// \details 多个图层绘制
class GS_API GsMap:public Utility::GsRefObject,private Utility::GsWorkThread
{
	volatile bool m_bIsValid; 
	Utility::GsSignaler m_FinishSignaler;
	volatile bool m_bDrawing;	
private:
	virtual bool Execute();
protected:
	/// \brief 图形列表
	std::vector<GsLayerPtr > m_lstLayers;
	
	/// \brief 屏幕显示对象
	GsScreenDisplayPtr m_ptrDisplay;
	/// \brief 绘制取消对象
	GsTrackCancelPtr m_TrackCancel;
public:
	/// \brief 根据屏幕显示对象构造
	GsMap(GsScreenDisplay* pDisplay);
	virtual ~GsMap();

	/// \brief 取消对象指针
	GsTrackCancel* TrackCancel();

	/// \brief 获取屏幕显示对象
	GsScreenDisplay* ScreenDisplay();
	
	/// \brief 取消当前绘制
	virtual void Cancel();
	/// \brief 地图是否处于绘制状态
	virtual bool IsDrawing();

	/// \brief 获取图层列表对象指针
	GsVector<GsLayerPtr >* Layers();
	/// \brief 强制刷新地图
	/// \details 使地图失效，强制刷新
	virtual void Update();
	/// \brief 绘制地图
	/// \details 如果地图数据未失效，则直接绘制缓冲的位图，反之则重新绘制
	virtual void Paint(GsDrawPhase eReason = eDrawNormal);

	/// \brief 使地图失效
	virtual void Invalidate();

	/// \brief 判断是否是否已经失效
	virtual bool IsValid();

	/// \brief 全图范围
	/// \details 所有图层的范围合并的范围
	GsBox FullExtent();
	
	/// \brief 设置当前显示范围
	/// \details 会取消当前地图绘制，同时使得地图失效，但不会立刻刷新地图，需要额外调用Paint或者Update刷新地图
	void ViewExtent(const GsBox& extent);

	/// \brief 获取当前显示范围
	/// \details 相当于调用方法Display()->DisplayTransformation()->MapExtent();
	GsBox ViewExtent();

	
	/// \brief 将地图数据绘制到输入的Display上。
	/// \details 调用者需要在外部输入启动Display的StartDraw，并在输出结束后调用EndDraw。
	/// \param pDisp 需要输出数据的Display
	bool Output(GsDisplay* pDisp,GsTrackCancel* pCancel);

};
/// \brief GsMapPtr
GS_SMARTER_PTR(GsMap);


/// \brief 渲染器，实现数据的渲染。
class GS_API GsRendition:public Utility::GsRefObject
{
protected:
	GsRendition();
	GsDisplayPtr m_ptrDisplay;
public:
	virtual ~GsRendition();
	/// \brief 开始渲染
	virtual void Begin(GsDisplay* pDisplay);
	
	/// \brief 结束渲染
	virtual void End();
};
/// \brief GsRenditionPtr
GS_SMARTER_PTR(GsRendition);
/// \brief 矢量数据渲染器
class GS_API GsFeatureRendition:public GsRendition
{
protected:
	GsFeatureRendition();
public:
	virtual ~GsFeatureRendition();
	/// \brief 渲染一个地物
	virtual bool Render(GsFeature* pFea,GsSymbol* pSym);
};

/// \brief GsFeatureRenditionPtr
GS_SMARTER_PTR(GsFeatureRendition);
/// \brief 标注渲染器
class GS_API GsLabelRendition:public GsFeatureRendition
{
	GsLabelPropertyPtr m_ptrLabelProperty;
public:
	GsLabelRendition(GsLabelProperty* pLabelProperty);
	virtual ~GsLabelRendition();
	/// \brief 开始渲染
	virtual void Begin(GsDisplay* pDisplay);
	
	/// \brief 结束渲染
	virtual void End();
	/// \brief 渲染一个地物
	virtual bool Render(GsFeature* pFea,GsSymbol* pSym);

	/// \brief 返回 LabelProperty
	virtual GsLabelPropertyPtr LabelProperty();
};
/// \brief GsLabelRenditionPtr
GS_SMARTER_PTR(GsLabelRendition);


/// \brief 地物渲染器抽象基类
class GS_API GsFeatureRenderer:public Utility::GsRefObject
{
protected:
	/// \brief 显示对象
	GsDisplayPtr m_ptrDisplay;
	/// \brief 当前会绘制的游标
	GsFeatureCursorPtr m_ptrFeaCursor;
	
	/// \brief 坐标变换对象
	GsCoordinateTransformationPtr m_ptrTrans;
	
	/// \brief 渲染器
	GsFeatureRenditionPtr m_ptrRendition;
protected:
	/// \brief 渲染器开始绘制游标时发生
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
public:
	GsFeatureRenderer();
	~GsFeatureRenderer();
	
	/// \brief 获取渲染器
	GsFeatureRendition* Rendition();
	/// \brief 设置渲染器
	void Rendition(GsFeatureRendition* pRen);


	/// \brief 绘制一个地物游标中的数据
	virtual void DrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay,GsTrackCancel* pCancel);

	/// \brief 获取坐标转换对象
	GsCoordinateTransformation* CoordinateTransformation();
	/// \brief 设置坐标转换对象
	void CoordinateTransformation(GsCoordinateTransformation* trans);



public:
	/// \brief 事件,当开始绘制的时候发生
	Utility::GsDelegate<void(GsFeature*,GsFeatureCursor*,GsDisplay*)> OnBegin;
	Utility::GsDelegate<void(GsFeature*,GsDisplay*,bool*)> OnFeature;
	Utility::GsDelegate<void(GsFeatureCursor*,GsDisplay*)> OnEnd;
};
/// \brief GsFeatureRendererPtr
GS_SMARTER_PTR(GsFeatureRenderer);

/// \brief 将任意的颜色转换为RGBA32位位图。
/// \details RasterRenderer的二次开发可以扩展一个ColorToRGBA子类；或者直接重写GsRasterRenderer::DrawCursor，以获得更大的灵活性
class GS_API GsColorToRGBA
{
protected:
	/// \brief 透明度
	double m_dblTrans;
public:
	GsColorToRGBA();
	virtual ~GsColorToRGBA();

	GsTrackCancel* m_pCancel;
	virtual bool Translate(GsRaster* pRaster,Utility::GsImage* pImg);
	
	/// \brief 设置透明度，取值从0到1
	void Transparency(double dblTrans);
};

/// \brief 栅格数据渲染器抽象基类
class GS_API GsRasterRenderer:public Utility::GsRefObject
{
protected:
	/// \brief 显示对象
	GsDisplayPtr m_ptrDisplay;
	/// \brief 当前会绘制的游标
	GsRasterCursorPtr m_ptrRasterCursor;
	/// \brief 用于绘制的位图对象
	Utility::GsSimpleBitmapPtr m_ptrImage;
	/// \brief 像素转换
	std::auto_ptr<GsColorToRGBA> m_ptrTrans;
	/// \brief 透明度
	double m_dblTrans;
public:
	GsRasterRenderer();
	virtual ~GsRasterRenderer();

	/// \brief 绘制一个地物游标中的数据
	virtual void DrawCursor(GsRasterCursor* pRasterCursor,GsDisplay* pDisplay,GsTrackCancel* pCancel);

	/// \brief 设置透明度，取值从0到1
	void Transparency(double dblTrans);

protected:
	/// \brief 创建颜色绘制对象
	virtual void CreateColorTrans(GsTrackCancel* pCancel){}
};
/// \brief GsRasterRendererPtr
GS_SMARTER_PTR(GsRasterRenderer);

/// \brief RGBA渲染器
/// \details 游标中所有的像素统一使用RGBA值进行绘制
class GS_API GsRGBARasterRenderer:public GsRasterRenderer
{
	int m_nRed;
    int m_nGreen;
    int m_nBlue;
    int m_nAlpha;
public:
	GsRGBARasterRenderer(int r, int g, int b, int a=3);
	GsRGBARasterRenderer();
	~GsRGBARasterRenderer();

	/// \brief 创建颜色绘制对象
	virtual void CreateColorTrans(GsTrackCancel* pCancel);

	/// \brief Red通道序号
	int Red();
	void Red(int r);

	/// \brief Green通道序号
	int Green();
	void Green(int g);

	/// \brief Blue通道序号
	int Blue();
	void Blue(int b);
};
/// \brief GsRGBARasterRenderer
GS_SMARTER_PTR(GsRGBARasterRenderer);

/// \brief 灰度影像渲染器
class GS_API GsGrayIndexRasterRenderer : public GsRasterRenderer
{
	short m_sMin;
	short m_sMax;
	short m_sNoData;
	bool  m_bSwap;
	bool  m_bUseNoData;
public:
	GsGrayIndexRasterRenderer(short minVal,short maxVal,short nNoData);
	~GsGrayIndexRasterRenderer(){}

	/// \brief 创建颜色绘制对象
	virtual void CreateColorTrans(GsTrackCancel* pCancel);

	/// \brief 交换黑色和白色
	void SwapWhiteBlack(bool bSwap);

	/// \brief 是否使用无效值
	void UseNoDataValue(bool bUse);
	bool UseNoDataValue();

	/// \brief 无效值
	short NoDataValue();
	void NoDataValue(short nNoData);
};
/// \brief GsGrayIndexRasterRenderer
GS_SMARTER_PTR(GsGrayIndexRasterRenderer);

/// \brief 调色板真彩色渲染器
class GS_API GsPaletteRasterRenderer : public GsRasterRenderer
{
	GsColorTable m_cTable;
public:
	GsPaletteRasterRenderer(GsColorTable &table);
	~GsPaletteRasterRenderer();

	/// \brief 创建颜色绘制对象
	virtual void CreateColorTrans(GsTrackCancel* pCancel);
	/// \brief 返回调色板
	GsColorTable &ColorTable();
};
/// \brief GsPaletteRasterRenderer
GS_SMARTER_PTR(GsPaletteRasterRenderer);

/// \brief 简单地物渲染器
/// \details 游标中所有的地物统一使用一种符号进行绘制
class GS_API GsSimpleFeatureRenderer:public GsFeatureRenderer
{
protected:
	/// \brief 渲染的符号
	GsSymbolPtr m_ptrSymbol;
protected:
	/// \brief 渲染器开始绘制游标时发生
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
public:
	/// \brief 缺省构造
	GsSimpleFeatureRenderer();
	/// \brief 根据符号构造
	GsSimpleFeatureRenderer(GsSymbol* pSym);
	virtual ~GsSimpleFeatureRenderer();

	/// \brief 设置渲染的符号
	virtual void Symbol(GsSymbol* pSym);
	/// \brief 获取渲染的符号指针
	virtual GsSymbol* Symbol();
};
/// \brief GsSimpleFeatureRendererPtr
GS_SMARTER_PTR(GsSimpleFeatureRenderer);

/// \brief 质底填充渲染器
/// \details 游标中根据指定的属性值，过滤出各个地物，使用不同符号进行绘制
class GS_API GsUniqueValueRenderer:public GsFeatureRenderer
{
protected:
	/// \brief 默认渲染符号
	GsSymbolPtr m_ptrDefaultSymbol;
	
	/// \brief 要过滤的字段名
	std::string m_strFieldName;
	/// \brief 要过滤的字段名的位置
	int m_nFieldPos;

	/// \brief 记录是否使用默认符号进行绘制
	bool m_bUseDefaultSymbol;

	/// \brief 绘制时描述Feature字段值，声明为成员减少构造次数
	Utility::GsAny m_anyEachFeature;

	/// \brief 渲染符号相关信息
	struct SymbolUnit
	{
		GsSymbolPtr ptrSymbol;
		std::string strLabel;
		SymbolUnit(GsSymbol *pSym, const char* srtInLabel)
		{
			ptrSymbol = pSym;
			strLabel = srtInLabel;
		}
	};

	/// \brief 渲染符号容器
	std::map<unsigned long long, SymbolUnit> m_mapSymbols;

protected:
	/// \brief 渲染器开始绘制游标时发生
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);

public:
	/// \brief 缺省构造
	GsUniqueValueRenderer();
	/// \brief 根据默认符号构造
	GsUniqueValueRenderer(GsSymbol* pDefaultSym);
	virtual ~GsUniqueValueRenderer();

	/// \brief 设置默认符号
	void DefaultSymbol(GsSymbol* pSym);
	/// \brief 获取默认符号
	GsSymbol *DefaultSymbol();

	/// \brief 设置过滤字段名
	void FieldName(const char* strFieldName);
	/// \brief 获取过滤字段
	Utility::GsString FieldName();

	/// \brief 根据双精度型属性值设置符号
	void Symbol(double dblValue, GsSymbol* pSym);
	/// \brief 根据单精度型属性值设置符号
	void Symbol(float fValue, GsSymbol* pSym);
	/// \brief 根据整型属性值设置符号
	void Symbol(int nValue, GsSymbol* pSym);
	/// \brief 根据字符串型属性值设置符号
	void Symbol(const char* strValue, GsSymbol* pSym);

	/// \brief 根据双精度型属性值获取符号
	GsSymbol* Symbol(double dblValue);
	/// \brief 根据单精度型属性值获取符号
	GsSymbol* Symbol(float fValue);
	/// \brief 根据整型属性值获取符号
	GsSymbol* Symbol(int nValue);
	/// \brief 根据字符串型属性值获取符号
	GsSymbol* Symbol(Utility::GsString &strValue);

	/// \brief 设置是否使用默认符号进行绘制
	void IsUseDefaultSymbol(bool bUse);
	/// \brief 返回是否使用默认符号进行绘制
	bool IsUseDefaultSymbol();

protected:
	/// \brief 所有符号准备绘制
	void AllSymbolsBeginDraw(GsDisplay* pDisplay);
	/// \brief 所有符号结束绘制
	void AllSymbolsEndDraw();
	/// \brief 根据key值查找符号，没有找到返回空指针
	GsSymbol *FindSymbolByKey(unsigned long long nKey);
};
/// \brief GsSimpleFeatureRendererPtr
GS_SMARTER_PTR(GsUniqueValueRenderer);

/// \brief 用于渲染注记地物
class GS_API GsTextFeatureRenderer:public GsFeatureRenderer
{
	bool m_bUnified;
	GsTextSymbolPtr m_ptrTextSymbol;
	GsTextSymbolPtr m_ptrRenderSymbol;

	int m_nTextFieldPos;
protected:
	/// \brief 渲染器开始绘制游标时发生
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
public:
	/// \brief 缺省构造
	GsTextFeatureRenderer();
	/// \brief 根据符号构造
	GsTextFeatureRenderer(GsTextSymbol* pSym);
	virtual ~GsTextFeatureRenderer();

	/// \brief 设置渲染的符号
	virtual void Symbol(GsTextSymbol* pSym);
	/// \brief 获取渲染的符号指针
	virtual GsTextSymbol* Symbol();

	/// \brief 是否统一使用一种符号渲染
	bool Unified();
	/// \brief 是否统一使用一种符号渲染
	void Unified(bool b);

};
/// \brief GsTextFeatureRendererPtr
GS_SMARTER_PTR(GsTextFeatureRenderer);



/// \brief 用于分级渲染
class GS_API GsGraduatedRenderer:public GsFeatureRenderer
{
	/// \brief 默认渲染符号
	GsSymbolPtr m_ptrDefaultSymbol;
	/// \brief 是否用缺省符号
	bool m_bIsUseDefaultSymbol; 

	/// \brief 分级符号
	GsVector<GsSymbolPtr> m_vSymbols;
	
	/// \brief 是否为分级颜色
	bool m_bIsGradeColor;

	/// \brief 分级点
	GsVector<double> m_vBreakValues;
	/// \brief 级别数
	int m_nBreakCount;
	
	//字段索引号
	int	 m_nFieldPos;	
	//字段名
	Utility::GsString m_strFieldName;
	//正规化字段索引号
	int	 m_nNormFieldPos; 


protected:
	/// \brief 渲染器开始绘制游标时发生
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);


	/// \brief 获取字段值
	bool FieldValue(GsFeature* pFea, int pos, double &dValue);
	/// \brief 计算字段值的分级
	int FieldGrade(GsFeature* pFea);

public:
	/// \brief 缺省构造
	GsGraduatedRenderer();
	virtual ~GsGraduatedRenderer();

	/// \brief 设置符号
	void Symbol(GsSymbol* pSymbol);
	/// \brief 根据级别值获取符号
	GsSymbol* Symbol(int nIndex);

	/// \brief 设置默认符号
	void DefaultSymbol(GsSymbol* pSymbol);
	/// \brief 获取默认符号
	GsSymbol* DefaultSymbol();

	/// \brief 设置是否使用默认符号
	void IsUseDefaultSymbol(bool bIsUseDefaultSymbol);
	/// \brief 获取是否使用默认符号
	bool IsUseDefaultSymbol();


	/// \brief 判断是否分级颜色
	bool GradeTypeColor();
	/// \brief 设置是否分级颜色
	void GradeTypeColor(bool bIsGradeColor);

	/// \brief 设置字段位置
	void FieldPos(int nPos);
	/// \brief 返回字段位置
	int FieldPos();

	void FieldName(const char* strFieldName);
	Utility::GsString FieldName();
	/// \brief 设置正规化字段位置
	void NormalFieldPos(int nPos);
	/// \brief 返回正规化字段位置
	int NormalFieldPos();

	/// \brief 设置分级值
	void BreakValue(double dValue);
	/// \brief 返回分级值
	double BreakValue(int nIndex);
	/// \brief 设置分级数量
	void BreakCount(int nCount);
	/// \brief 返回分级数量
	int BreakCount();

};
/// \brief GsGraduatedRendererPtr
GS_SMARTER_PTR(GsGraduatedRenderer);




	/// \brief 点值法
class GS_API GsDotDensityRenderer:public GsFeatureRenderer
{
public:
	/// \brief 缺省构造
	GsDotDensityRenderer();
	virtual ~GsDotDensityRenderer();

	/// \brief 设置字段位置
	void FieldIndex(int nIndex);
	/// \brief 返回字段位置
	int FieldIndex();
	
	/// \brief 设置点的尺寸
	void DotSize(double dDotSize);
	/// \brief 返回点尺寸
	double DotSize();

	/// \brief 设置点值
	void DotValue(double dDotValue);
	/// \brief 返回点值
	double DotValue();

	/// \brief 设置点符号
	void PointSymbol(GsPointSymbol* pPointSymbol);
	/// \brief 获取点符号
	GsPointSymbol* PointSymbol();

	/// \brief 设置背景面符号
	void BackGroundSymbol(GsFillSymbol* pFillSymbol);
	/// \brief 获取背景面符号
	GsFillSymbol* BackGroundSymbol();

	/// \brief 设置是否绘制背景
	void IsDrawBackGround(bool bVal);
	/// \brief 获取是否绘制背景
	bool IsDrawBackGround();
protected:
	/// \brief 渲染器开始绘制游标时发生
	virtual bool OnBeginDrawCursor(GsFeature* pFeaFirst,GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);
	/// \brief 渲染器每渲染一个地物时发生
	virtual bool OnDrawFeature(GsFeature* pFea,GsDisplay* pDisplay);
	/// \brief 渲染器结束绘制时发生。
	virtual bool OnEndDrawCursor(GsFeatureCursor* pFeaCursor,GsDisplay* pDisplay);

	//用以计算字段值
	bool FieldValue(GsFeature* pFea, int pos, double &dValue);
	//计算随机数
	double RandomNumber(double minNum,double maxNum);

private:
	// 字段索引
	int m_nFieldIndex;
	// 点的大小
	double m_dDotSize ;
	// 点代表的值
	double m_dDotValue ; 
	// 字段的名称	
	Utility::GsString m_FieldName ; 

	bool m_bIsDirty ;
	bool m_bIsDrawBackGound ; 

	std::auto_ptr<SpatialAnalysis::path_index> m_ptrKnife; 

	GsPoint* m_vPoints;

	GsFillSymbolPtr m_ptrFillSymbol;  //面符号  
	GsSymbolPtr m_ptrSymbol; // 指向当前的点符号     
	GsPointSymbolPtr m_ptrPointSymbol;//用来存储绘图使用的点符号		 


};
/// \brief GsDotDensityRendererPtr
GS_SMARTER_PTR(GsDotDensityRenderer);


/// \brief 动态投影的方法
enum GsProjectionStyle
{
	/// \brief 不论什么情况下不做动态投影
	eDoNotProjection,

	/// \brief 自动动态投影
	/// \details 仅在当前图层和地图参考不一致的时候进行动态投影
	eDoProjectionAuto,

	/// \brief 强制动态投影
	/// \details 不论当前图层和地图空间参考是否一致都进行投影。
	eDoProjectionForce,
};

/// \brief 地物类图层
class GS_API GsFeatureLayer:public GsLayer
{ 
	GsFeatureClassPtr m_ptrFeaClass;
	GsFeatureRendererPtr m_ptrRenderer;
	GsFeatureRendererPtr m_ptrSelectionRenderer;
	GsSelectionSetPtr m_ptrSelectionSet;
	
	
	/// \brief 动态投影的方法
	GsProjectionStyle m_eProjectionStyle;
	
	/// \brief 进行强制投影变换是源投影
	GsSpatialReferencePtr m_ptrSource;
	
	
	/// \brief 事件，当外部调用Cancel方法时发生
	void OnCancel(GsTrackCancel*,const char*);
protected:
	/// \brief 绘制方法入口
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);
public:
	/// \brief 从一个地物类构造
	GsFeatureLayer(GsFeatureClass* vFeaClass);
	/// \brief 缺省构造
	GsFeatureLayer();
	virtual ~GsFeatureLayer();

	/// \brief 图层的地理范围
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);
	
	/// \brief 图层的空间参考
	virtual GsSpatialReference* SpatialReference();
	
	/// \brief 获取地物类对象指针
	GsFeatureClass* FeatureClass();
	/// \brief 设置地物类
	void FeatureClass(GsFeatureClass* vFeaClass);

	/// \brief 获取Renderer对象
	GsFeatureRenderer* Renderer();
	/// \brief 设置Renderer对象
	void Renderer(GsFeatureRenderer* pRender);

	/// \brief 选择地物
	/// \param pFilter 查询条件
	/// \return 返回内部的选择集
	GsSelectionSet* Select(GsQueryFilter* pFilter =  0);

	/// \brief 获取选择集
	/// \return 返回内部的选择集指针
	GsSelectionSet* SelectionSet();

	/// \brief 清空选择集
	void ClearSelection();

	
	/// \brief 图层是否存在选择集
	virtual bool HasSelection();

	/// \brief 获取投影变换类型
	GsProjectionStyle ProjectionStyle();
	/// \brief 设置投影变换类型
	void ProjectionStyle(GsProjectionStyle eStyle);
	
	/// \brief 获取强制投影时源空间参考
	GsSpatialReference* SourceSpatialReference();
	/// \brief 设置强制投影时源空间参考
	void SpatialReference(GsSpatialReference* soruce);
	
	/// \brief 是否有效
	virtual bool IsValid();


};
/// \brief GsFeatureLayerPtr
GS_SMARTER_PTR(GsFeatureLayer);

class GS_API GsRasterLayer:public GsLayer
{
	GsRasterClassPtr m_ptrRasterClass;
	//Utility::GsSimpleBitmapPtr m_ptrImage;
	GsRasterResampleAlg m_eResampleAlg;//获取数据时候的插值算法
	GsRasterRendererPtr m_ptrRasterRenderer;
protected:
	
	/// \brief 绘制方法入口
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);
public:
	GsRasterLayer(GsRasterClass* pRasterClass);
	
	/// \brief 获取插值算法
	GsRasterResampleAlg  ResampleAlg();
	/// \brief 设置插值算法
	void ResampleAlg(GsRasterResampleAlg  alg);

	
	/// \brief 图层的地理范围
	/// \param pTargetSR 以该空间参考返回范围
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);
	/// \brief 获取栅格类对象指针
	GsRasterClass* RasterClass();
	/// \brief 设置栅格类
	void RasterClass(GsRasterClass* pRasterClass);
	
	/// \brief 图层是否存在选择集
	virtual bool HasSelection();
	/// \brief 是否有效
	virtual bool IsValid();

	/// \brief 图层的空间参考
	virtual GsSpatialReference* SpatialReference();

	/// \brief 获取Renderer对象
	GsRasterRenderer *Renderer();

	/// \brief 设置Renderer对象
	void Renderer(GsRasterRenderer *pRenderer);
};
/// \brief GsRasterLayerPtr
GS_SMARTER_PTR(GsRasterLayer);


/// \brief 瓦片类图层
class GS_API GsTileLayer:public GsLayer
{
	GsTileClassPtr m_ptrTileClass;
protected:
	/// \brief 绘制方法入口
	virtual bool InnerDraw(GsDisplay* pDisplay,GsTrackCancel* pCancel,GsDrawPhase eDrawPhase);
public:
	GsTileLayer(GsTileClass* pTileClass);
	
	/// \brief 图层的地理范围
	/// \param pTargetSR 以该空间参考返回范围
	virtual GsBox Extent(GsSpatialReference* pTargetSR = 0);
	/// \brief 获取瓦片类对象指针
	GsTileClass* TileClass();
	/// \brief 设置瓦片类
	void TileClass(GsTileClass* vTileClass);
	
	/// \brief 图层是否存在选择集
	virtual bool HasSelection();
	/// \brief 是否有效
	virtual bool IsValid();

	/// \brief 图层的空间参考
	virtual GsSpatialReference* SpatialReference();
};
/// \brief GsTileLayerPtr
GS_SMARTER_PTR(GsTileLayer);

/// \brief 鼠标按钮
enum GsButton
{
	/// \brief 没有按下任何键
	eNoneButton = 0,
	/// \brief 鼠标左键
	eLeftButton = 1,
	/// \brief 鼠标右键
	eRightButton = 2,
	/// \brief 鼠标中键
	eMiddleButton = 4,
};
/// \brief 屏幕绘制
class GS_API GsSymbolTracker:public Utility::GsRefObject 
{
protected:
	GsMapPtr m_ptrMap;
	GsDisplayTransformationPtr m_ptrDT;
	/// \brief tracker绘制函数，子类通过覆盖此函数绘制内容。
	virtual void OnTrackerDraw(GsDisplay* pDisp); 
public: 
	GsSymbolTracker(GsMap* pMap);
	virtual ~GsSymbolTracker();

	/// \brief 接收鼠标按下消息
	virtual void OnMouseDown(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标弹起消息
	virtual void OnMouseUp(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标移动消息
	virtual void OnMouseMove(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标滚轮消息
	virtual void OnMouseWheel(GsButton eButton,int nDelta,int nKeyboard,const Utility::GsPT& pt);
public:
	
	/// \brief Tracker绘制的反馈。
	enum GsTrackerFeedBack
	{
		/// \brief 通知Tracker什么也不做，相当于结束Tracker
		eDoNothing,
		/// \brief 通知Tracker重新启动
		eRestartTracker,
		/// \brief 通知Tracker结束
		eEndTracker,
	};
	 
	 
	 
	/// \brief Geometry绘制完成
	Utility::GsDelegate<GsTrackerFeedBack(GsGeometry*)> OnGeometryTracked;  

};
/// \brief GsSymbolTrackerPtr
GS_SMARTER_PTR(GsSymbolTracker);


/// \brief 屏幕绘制
class GS_API GsNewEnvelopeTracker:public GsSymbolTracker
{
	GsSimpleFillSymbolPtr m_ptrFillSymbol;
	Utility::GsLock m_Lock;
	GsEnvelopePtr m_ptrEnvelope;
	/// \brief tracker绘制函数，子类通过覆盖此函数绘制内容。
	virtual void OnTrackerDraw(GsDisplay* pDisp);
	volatile bool m_bStart,m_bMouseMove;
	GsRawPoint m_First,m_Second;
public:
	GsNewEnvelopeTracker(GsMap* pMap);
	virtual ~GsNewEnvelopeTracker();
	
	/// \brief 接收鼠标按下消息
	virtual void OnMouseDown(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标弹起消息
	virtual void OnMouseUp(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
	/// \brief 接收鼠标移动消息
	virtual void OnMouseMove(GsButton eButton,int nKeyboard,const Utility::GsPT& pt);
};
/// \brief GsNewEnvelopeTrackerPtr
GS_SMARTER_PTR(GsNewEnvelopeTracker);

/// \brief 基于内存的影像画布
class GS_API GsMemoryImageCanvas:public GsImageCanvas
{
protected:
	AggGraphics* m_pAggGraphics;
protected:
	GsMemoryImageCanvas();

public:
	/// \brief 根据宽和高构建RGBA32位色的画布
	GsMemoryImageCanvas(int w, int h, float dpi=96);
	virtual ~GsMemoryImageCanvas();
	 
	/// \brief 设置绘制起算的原点
	virtual void RenderingOrigin(const Utility::GsPT pt);

	/// \brief 创建一个裁切范围
	virtual GsRegionPtr CreateRegion(GsGraphicsPath*  path);
	/// \brief 创建一个裁切范围
	virtual GsRegionPtr CreateRegion(const Utility::GsRect& rect);
	/// \brief 设置path作为的裁切范围
    virtual void Clip(GsRegion *  region);
    /// \brief 清除裁切范围
    virtual void ClearClip();

	/// \brief 获取绘制的位图
	virtual Utility::GsImage* Image();
	
	/// \brief 创建一个和当前画布兼容的Image画布
	/// \param width　画布的高度
	/// \param height  画布的宽度
	virtual GsImageCanvasPtr CreateCompatibleImageCanvas(int width,int height);

	/// \brief 创建画笔对象
	/// \param color 画笔的颜色
	/// \param  fWidth 画笔的宽度，像素单位
    /// \returns 返回创建的画笔对象指针
	virtual GsPenPtr CreatePen(const GsColor& color,float fWidth = 1.0f);

	/// \brief 从画刷创建画笔对象
	/// \param brush 画刷
	/// \param  fWidth 画笔的宽度，像素单位
    /// \returns 返回创建的画笔对象指针
	virtual GsPenPtr CreatePen(GsBrush* pBrush,float fWidth = 1.0f);

	/// \brief 绘制多个点连续的线 
	/// \param pCoord 坐标数组指针，以X，Y坐标连续存储
	/// \param nPointCount 坐标点的数量
	/// \param pPen 绘制的画笔
	/// \returns 返回绘制是否成功
	virtual bool DrawLine(float* pCoord,int nPointCount,GsPen* pPen);
	 

	/// \brief 绘制Pie轮廓
	/// \param rect Pie所在椭圆的外接矩形范围
	/// \param start_angle 饼的开始角度
	/// \param sweepAngle 饼的旋转角度
	/// \param pPen 绘制的画笔
	/// \returns 返回绘制是否成功
	virtual bool DrawPie(const Utility::GsRectF  &rect,float start_angle,float sweepAngle,GsPen* pPen);

	/// \brief 填充Pie
	/// \param rect Pie所在椭圆的外接矩形范围
	/// \param start_angle 饼的开始角度
	/// \param sweepAngle 饼的旋转角度
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillPie(const Utility::GsRectF  &rect,float start_angle,float sweepAngle,GsBrush* pBrush);

	virtual bool DrawRectangle(const Utility::GsRectF& rect, GsPen* pPen);
	virtual bool FillRectangle(const Utility::GsRectF& rect, GsBrush* pBrush);

	virtual bool DrawEllipse(const Utility::GsRectF& rect, GsPen* pPen);
	virtual bool FillEllipse(const Utility::GsRectF& rect, GsBrush* pBrush);

	/// \brief 绘制图片的特定部分到特定范围 
	/// \param pImg 要绘制的图片
	/// \param source 图片要绘制的范围 
	/// \param target 要绘制到的目标范围
	/// \returns 返回绘制是否成功
	virtual bool DrawImage(Utility::GsImage* pImg,const Utility::GsRect& source,const Utility::GsRectF& target);

	
	/// \brief 从内存块直接创建图像对象
	/// \param strData　图像的内存块
	/// \param nLen  内存块的长度
	/// \return 返回图像对象
	virtual Utility::GsImagePtr CreateImage(const unsigned char* strData,int nLen);
	
	/// \brief 创建路径对象 
    /// \returns 返回创建的路径对象指针
	virtual GsGraphicsPathPtr CreatePath();

	/// \brief 绘制路径 
	/// \param pPath 要绘制的路径
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawPath(GsGraphicsPath* pPath,GsPen* pPen) ;

	
	/// \brief 填充路径 
	/// \param pPath 要填充的路径
	/// \param pBrush 填充的画刷 
	/// \returns 返回绘制是否成功
	virtual bool FillPath(GsGraphicsPath* pPath,GsBrush* pBrush);

	/// \brief 绘制圆弧
	/// \param pPath 要绘制的路径
	/// \param pPen 绘制的画笔 
	/// \returns 返回绘制是否成功
	virtual bool DrawArc(const Utility::GsRectF& rect, float dblStartAngle, float dblEndAngle, GsPen* pPen);

	/// \brief 用特定颜色清空整个画布  
	/// \param color 要清空的颜色  
	/// \returns 返回绘制是否成功 
	virtual bool Clear(const GsColor& color);
	 
	/// \brief 提交未提交的绘制数据   
	/// \returns 返回提交是否成功 
	virtual  bool Flush();

	/// \brief 绘制字符串
	/// \returns 返回提交是否成功 
	virtual bool DrawString(const char* strText,int nLen,GsBrush* pBrush,const Utility::GsRectF& eLayout,GsStringFormat* pFormat);
	virtual bool MeasureString(const char* strText,int nLen, Utility::GsRectF &eLayout,GsStringFormat* pFormat);
};
/// \brief GsMemoryImageCanvasPtr
GS_SMARTER_PTR(GsMemoryImageCanvas);

/// \brief 基于文件的影像画布
/// \details 基于文件的影像画布可以实现超过内存存储限制的画布，画布通过和文件直接IO实现超大画布的绘制能力。性能上到低于基于内存的画布。 
class GS_API GsFileImageCanvas:public GsMemoryImageCanvas
{
public:
	/// \brief 根据文件名和宽高构建RGBA32位色的画布
	GsFileImageCanvas(const char* strFile,int w,int h,int nMaxMemoryCache=0x100000);
	virtual ~GsFileImageCanvas();
};
/// \brief GsFileImageCanvasPtr
GS_SMARTER_PTR(GsFileImageCanvas);


KERNEL_ENDNS