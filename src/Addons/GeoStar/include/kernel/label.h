#pragma once
#include "../utility/preconfig.h" 
#include<utility.h>
#include<geodatabase.h>
#include<geometry.h>
#include<symbol.h>
#include <list>
#include <queue>
KERNEL_NS  
/// \brief 标注对象
class GS_API GsLabel:public Utility::GsRefObject
{
protected:
	GsTextSymbolPtr m_ptrSymbol;
	long long m_nID;
	long long m_nOrder;
	double m_nPriority;
	Utility::GsString m_strText;
	GsGeometryBlob m_GeometryBlob;
	GsRawPoint m_Point;
	GsLabel();
public:
	
	virtual  ~GsLabel();
	
	/// \brief 标准绘制的Geometry
	GsGeometryBlob* Geometry();
	
	/// \brief 标注的点
	void LabelPoint(double x,double y);

	/// \brief 标注的点
	GsRawPoint LabelPoint();

	/// \brief 重置标注为初始状态
	void Reset();

	/// \brief 获取标注的优先级
	double Priority()const;
	/// \brief 设置标注的优先级
	void Priority(double n);

	
	/// \brief 获取标注的顺序
	long long Order()const ;
	/// \brief 获取标注的顺序
	void Order(long long n);

	/// \brief 标注的唯一id
	long long ID()const;
	/// \brief 标注的唯一id
	void ID(long long id);

	/// \brief 标注绘制的符号
	GsTextSymbol* Symbol();
	/// \brief 标注绘制的符号
	void Symbol(GsTextSymbol* sym);

	/// \brief 标注的文本
	const char* Text()const;
	/// \brief 标注的文本
	void Text(const char* str);
	
	
	/// \brief 是否和另外一个label堆叠
	virtual bool IsIntersects(GsLabel* rhs) const = 0;

	/// \brief 绘制标注
	virtual void Draw(GsDisplayTransformation* pDT,GsCanvas* pCanvas)  = 0;


};
/// \brief GsLabelPtr
GS_SMARTER_PTR(GsLabel);

/// \brief 自动标注避让容器抽象基类
class GS_API GsLabelContainer:public Utility::GsRefObject
{
protected:
	/// \brief 已经安排位置的标注
	std::list<GsLabelPtr> m_lstPlaced;
	/// \brief 未能安排位置的标注
	std::list<GsLabelPtr> m_lstUnPlaced;

	/// \brief 标注对象池
	std::queue<GsLabelPtr> m_LabelPool;
	
	/// \brief 最大存储的标注
	int m_nMax;

	/// \brief 是否允许自动标注
	bool m_bEnabled;

	/// \brief 回收标注
	void Recovery(std::list<GsLabelPtr>& lst);
	void Recovery(GsLabel* label);

	/// \brief 准备避让
	virtual void OnBegin();

	/// \brief 增加一个标注到容器
	virtual bool OnAdd(GsLabel* label);

	/// \brief 结束必避让
	virtual void OnEnd();

public:
	GsLabelContainer();
	virtual ~GsLabelContainer();

	/// \brief 是否允许自动标注
	bool Enabled();
	/// \brief 是否允许自动标注
	void Enabled(bool b);

	/// \brief 最大存储的标注
	int MaxLabel();
	/// \brief 最大存储的标注
	void MaxLabel(int n);

	/// \brief 创建或者复用一个Label对象。
	GsLabelPtr CreateLabel();

	/// \brief 准备避让
	virtual void Begin();

	/// \brief 增加一个标注到容器
	virtual bool Add(GsLabel* label);

	/// \brief 结束避让
	virtual void End();

	/// \brief 绘制标注
	virtual void DrawLabel(GsDisplayTransformation* pDT,GsCanvas* pCanvas);
};
/// \brief GsLabelContainerPtr
GS_SMARTER_PTR(GsLabelContainer);


class GS_API GsSimpleLabelContainer:public GsLabelContainer
{
protected:
	/// \brief 准备避让
	virtual void OnBegin();

	/// \brief 增加一个标注到容器
	virtual bool OnAdd(GsLabel* label);

	/// \brief 结束必避让
	virtual void OnEnd();

public:
	GsSimpleLabelContainer();
	virtual ~GsSimpleLabelContainer();
};
/// \brief GsSimpleLabelContainerPtr
GS_SMARTER_PTR(GsSimpleLabelContainer);

/// \brief 进阶版标注容器，采用更为复杂的避让规则
class GS_API GsAdvancedLabelContainer:public GsSimpleLabelContainer
{
protected:
	/// \brief 准备避让
	virtual void OnBegin();

	/// \brief 增加一个标注到容器
	virtual bool OnAdd(GsLabel* label);

	/// \brief 结束必避让
	virtual void OnEnd();
public:
	GsAdvancedLabelContainer();
	virtual ~GsAdvancedLabelContainer();

};
/// \brief GsAdvancedLabelContainerPtr
GS_SMARTER_PTR(GsAdvancedLabelContainer);

/// \brief 自动标注计算基类
class GS_API GsLabelProperty:public Utility::GsRefObject
{
protected:
	/// \brief 标注绘制的符号
	GsTextSymbolPtr m_ptrSymbol;
	/// \brief 标注符号的Clone，用于计算标注范围
	GsTextSymbolPtr m_ptrSymbolClone;
	
	/// \brief 缓存一个Label的位置
	std::vector<Utility::GsRectF> m_vecLabelRects;
	
	/// \brief 当前DT
	GsDisplayTransformationPtr m_ptrDT;
	/// \brief 当前画布
	GsCanvasPtr			m_ptrCanvas;
	/// \brief 计算标注内容
	GsCanvasPtr			m_ptrTextCanvas;

	/// \brief 标注容器
	GsLabelContainerPtr m_ptrContainer;
	/// \brief 标注的字段名
	Utility::GsString m_strFieldName;
	/// \brief 标注字段索引
	int m_nFieldIndex;
	/// \brief 标注字段类型
	Utility::Data::GsFieldType m_eType;
	
	/// \brief 从地物中计算要标注的文本
	Utility::GsString LabelText(GsFeature* pFea);

	/// \brief 计算标注点的位置
	GsRawPoint LabelPoint(GsGeometryBlob* blob,double& dblPri);
public:
	GsLabelProperty();
	virtual ~GsLabelProperty();
	
	/// \brief 准备开始标注计算
	virtual void Begin(GsDisplayTransformation* pDT,GsCanvas* pCanvas,GsLabelContainer* pContainer);
	/// \brief 结束标注计算
	virtual void End();


	/// \brief 要标注的字段名称
	Utility::GsString LabelField();
	/// \brief 要标注的字段名称
	void LabelField(const char* strField);
	
	/// \brief 标注绘制的符号
	GsTextSymbol* Symbol();
	/// \brief 标注绘制的符号
	void Symbol(GsTextSymbol* sym);
	
	/// \brief 计算标注
	virtual bool CalculateLabel(GsFeature* pFea,GsSymbol* pSym) = 0;
};

/// \brief GsLabelPropertyPtr
GS_SMARTER_PTR(GsLabelProperty);

/// \brief 点标注九宫格位置
///        ４２５
///        １★０
///        ６３７
enum GsPointLabelPlace
{
	///\brief 标注位于符号右边
	///
	///         ★Label
	///        
	eRight,
	///\brief 标注位于符号左边
	///
	///       Label★
	///        
	eLeft,
	///\brief 标注位于符号顶部
	///        Label
	///         ★
	///
	eTop,
	///\brief 标注位于符号底部
	///
	///         ★
	///        Label
	eBottom,
	
	///\brief 标注位于符号左上
	///    Label
	///         ★
	///        
	eTopLeft,
	///\brief 标注位于符号右上
	///           Label
	///         ★
	///        
	eTopRight,
	///\brief 标注位于符号左下
	///           
	///         ★
	///    Label   
	eBottomLeft,
	///\brief 标注位于符号右下
	///           
	///         ★
	///           Label   
	eBottomRight,
};

/// \brief 点标注位置优先级别
enum GsPlaceOrderPriority
{
	/// \brief 放弃
	eAbandonPriority,
	/// \brief 高优先级
	eHighPriority,
	/// \brief 中等优先级
	eMiddlePriority,
	/// \brief 低先级
	eLowPriority,
};

/// \brief 点自动标注计算类
class GS_API GsPointLabelProperty:public GsLabelProperty
{
	std::vector<std::pair<GsPointLabelPlace,GsPlaceOrderPriority> > m_PlaceOrder;
public:
	GsPointLabelProperty();
	/// \brief 获取标注位置的优先级
	GsPlaceOrderPriority PlaceOrder(GsPointLabelPlace e);
	/// \brief 设置标注位置的优先级
	void PlaceOrder(GsPointLabelPlace e,GsPlaceOrderPriority order);

	/// \brief 计算标注
	virtual bool CalculateLabel(GsFeature* pFea,GsSymbol* pSym) ;
};
/// \brief GsPointLabelPropertyPtr
GS_SMARTER_PTR(GsPointLabelProperty);

/// \brief 线自动标注计算类
class GS_API GsLineLabelProperty:public GsLabelProperty
{
public:
	//计算标注
	virtual bool CalculateLabel(GsFeature* pFea,GsSymbol* pSym) ;

};
/// \brief GsLineLabelPropertyPtr
GS_SMARTER_PTR(GsLineLabelProperty);

/// \brief 面自动标注计算类
class GS_API GsSurfaceLabelProperty:public GsLabelProperty
{
public:
	/// \brief 计算标注
	virtual bool CalculateLabel(GsFeature* pFea,GsSymbol* pSym) ;
};
/// \brief GsSurfaceLabelPropertyPtr
GS_SMARTER_PTR(GsSurfaceLabelProperty);


KERNEL_ENDNS