#pragma once
#include "../utility/preconfig.h"
#include <utility.h> 
#include <geometry.h> 
#include <geodatabase.h> 
#include <map>
#include <vector>

KERNEL_NS   

/// \brief 属性合并方法
enum GsJoinAttributeType
{
    /// \brief 合并所有属性
	eJoinAll,
	/// \brief 不合并OID
	eJoinNoOID,
	/// \brief 仅仅合并OID
	eJoinOnlyOID,
}; 
/// \brief 分析数据封装。
class GS_API GsAnalysisData  
{
protected:
	GsGeometryBlob m_Blob;
	std::vector<Utility::GsAny> m_Attributes;
public:
	GsAnalysisData();
	virtual ~GsAnalysisData();
	
	/// \brief 从地物读取数据
	bool ReadFromFeature(GsFeature* pFea);
	
	/// \brief 写入数据到地物
	bool WriteToFeature(GsFeature* pFea);


	/// \brief 数据的唯一ID
	long long ID();
	/// \brief 数据的唯一ID
	void ID(long long id);
	
	/// \brief 直接设置坐标内容
	/// \param nInterCount 解释串长度
	/// \param pInter 解释串数组
	/// \param nDim 几何维度，0=点，1=线，2=面
	/// \param nCDim 坐标维度，2,3
	/// \param nCoordLen 坐标长度
	/// \param pCoord 坐标数组
	virtual void SetGeometry(int nInterCount,int* pInter,int nDim,int nCDim,int nCoordLen,double* pCoord);
	
	/// \brief 设置Geometry对象
	virtual void SetGeometry(GsGeometry* pGeo);
	
	/// \brief 用Geometry数据设置Geometry对象
	virtual void SetGeometry(GsGeometryBlob* pBlob);


	/// \brief 解释串长度
	virtual int InterpretLength();
	/// \brief 解释串指针
	virtual int* Interpret();
	/// \brief 拷贝解释串到输入的数组中
	virtual int  Interpret(int* pInter,int nBuffLen);
	/// \brief 坐标串长度
	virtual int CoordinateLength();
	/// \brief 坐标串
	virtual double* Coordinate();
	/// \brief 拷贝坐标串到输入的数组中
	virtual int Coordinate(double* pCoord,int nBuffLen);
	
	/// \brief 几何对象的子对象数量，如果几何对象为简单对象则返回1
	virtual int GeometrySubCount();
	
	/// \brief 获取子Geometry的解释串
	virtual int SubInterpret(int n ,int* pInter,int nBuffLen);
	virtual int SubInterpretLength(int n);
	/// \brief 获取子Geometry的解释串
	virtual int SubCoordinate(int n ,double* pCoord,int nBuffLen);
	virtual int SubCoordinateLength(int n );


	/// \brief 坐标维度
	virtual int CoordinateDimension();
	/// \brief 几何维度，0=点，1=线，2=面
	virtual int GeometryDimension();

	/// \brief 属性值的长度
	virtual int AttributeLength();
	
	/// \brief 重置属性
	virtual void ResetAttribute();

	/// \brief 根据列索引获得列类型。
	virtual Utility::Data::GsFieldType ValueType(int nColIndex);
	
	/// \brief 获取整数值
	virtual int IntValue(int nColIndex);
	/// \brief 获取整数值
	virtual long long Int64Value(int nColIndex);
	/// \brief 获取字符串值
	virtual const char* StringValue(int nColIndex);
	/// \brief 获取浮点值
	virtual double DoubleValue(int nColIndex);

	/// \brief 获取Blob值
	virtual const unsigned char* BlobValue(int nColIndex);
	virtual int BlobValue(int nColIndex,unsigned char* buff,int nLen);

	/// \brief 获取Blob值长度
	virtual int BlobValueLength(int nColIndex);


	/// \brief 设置整数值
	virtual void SetValue(int nColIndex,int val);
	/// \brief 设置64位整数值
	virtual void SetValue(int nColIndex,long long val);
	/// \brief 设置字符串
	virtual void SetValue(int nColIndex,const char* val);
	/// \brief 设置浮点值
	virtual void SetValue(int nColIndex,double val);
	/// \brief 设置Blob
	virtual void SetValue(int nColIndex,const unsigned char* val,int nLen);
	/// \brief 设置空值
	virtual void SetValue(int nColIndex);

};

/// \brief 分析数据读写，通过继承此类以实现
class GS_API GsAnalysisDataIO
{
public:
	virtual ~GsAnalysisDataIO() {  }

	/// \brief 获取数据源的几何维度，0=点，1=线，2=面
	virtual int GeometryDimension(){return 0;};

    /// \brief 向空间分析模块输入或者空间数据
	/// \return ,当输入空间数据时返回0标示正常输入一条数据，否则为错误或者输入完成。
	virtual int OnData(GsAnalysisData* pData) = 0;
};

/// \brief 大数据叠置分析
class GS_API GsOverlayAnalysis:public Utility::GsRefObject
{
	/// \brief 叠置分析容差
	double m_Tolerance;
	/// \brief 叠置分析容差相对于叠置分析的比率
	double m_InvalidToleranceScale;
public:
	GsOverlayAnalysis(double tol);
	
	/// \brief 叠置分析容差相对于叠置分析的比率
	double InvalidToleranceScale();
	/// \brief 叠置分析容差相对于叠置分析的比率
	void InvalidToleranceScale(double scale);

	virtual ~GsOverlayAnalysis();
	
	/// \brief 合并N个地物类
	bool Union(GsAnalysisDataIO**  vInputArray,int nInputCount,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut);
    /// \brief 合并2个地物类
	bool Union(GsAnalysisDataIO* vInputA,GsAnalysisDataIO* vInputB,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut);
    
	/// \brief 擦除
	bool Erase(GsAnalysisDataIO* pInput,GsAnalysisDataIO* pErase,GsAnalysisDataIO* pOut );
	/// \brief 相交
	bool Intersect(GsAnalysisDataIO**  vInputArray,int nInputCount,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut );
	/// \brief 相交
	bool Intersect(GsAnalysisDataIO* vInputA,GsAnalysisDataIO* vInputB,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut );
	
	/// \brief 标记
	bool Identity(GsAnalysisDataIO* pInput,GsAnalysisDataIO* pIdentity,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut );
	
	/// \brief 更新
	bool Update(GsAnalysisDataIO* pInput,GsAnalysisDataIO* pUpdate,GsAnalysisDataIO* pOut );

	/// \brief 对称差
	bool SymmetricalDifference(GsAnalysisDataIO* vInputA,GsAnalysisDataIO* vInputB,GsJoinAttributeType eJoinType,GsAnalysisDataIO* pOut );
};

KERNEL_ENDNS