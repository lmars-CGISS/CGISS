#pragma once
#include "../utility/preconfig.h"
#include <utility.h> 
#include <map>
KERNEL_NS   
/// \brief 空间参考数据格式类型
enum GsSpatialReferenceFormat
{
	/// \brief 未知的空间参考定义格式
	eUnknownFormat,
	/// \brief 标准WKT格式
	eWktFormat,
	/// \brief XML格式
	eXMLFormat,
	/// \brief proj.4格式
	eProj4Format,
	/// \brief ESRI的Wkt格式
	eESRIWktFormat,
	/// \brief GeoStar5以逗号分隔的空间参考描述格式。
	eGeoStar5Format,
};

/// \brief 已知常用空间参考
enum GsWellKnownSpatialReference
{
	/// \brief WGS84空间参考
	eWGS84,
	/// \brief CGCS2000空间参考
	eCGCS2000,

	/// \brief web墨卡托空间参考
	eWebMercator,
};
/// \brief 坐标单位
enum  GsUnits
{ 
	/// \brief 未知单位
	eUnknownUnit,
	/// \brief 米
	eMeter,
	/// \brief 度
	eDegree,

	/// \brief 毫米
	eMM,

	/// \brief 英寸
	eInch,
		
	/// \brief 厘米
	eCM,
	/// \brief 千米
	eKM,
};
 
 



/// \brief 空间参考
class GS_API GsSpatialReference:public Utility::GsRefObject
{
	mutable Utility::GsString m_strWkt;
	void* m_SR;  
	Utility::GsString m_strName;
public:
	~GsSpatialReference();
	/// \brief 从已知的空间参考类型构造
	GsSpatialReference(GsWellKnownSpatialReference eWellKnown = eWGS84);
	/// \brief 从字符串和指定类型进行构造
	GsSpatialReference(const char* strData,GsSpatialReferenceFormat eFormat = eWktFormat); 
	/// \brief 从EPSG编号构造
	GsSpatialReference(int nEPSG);
	
	/// \brief 返回内部对象指针
	void* Handle();
	
	/// \brief 空间参考的名称
	Utility::GsString Name() const;
	/// \brief 空间参考的名称
	void Name(const char* strName);

	/// \brief 坐标单位
	GsUnits Units()const;

	/// \brief 坐标单位
	Utility::GsString ExportToWKT(bool bPretty=false)const;
	/// \brief 以XML的格式输出
	Utility::GsString ExportToXml()const;
	/// \brief 以Proj4的格式输出
	Utility::GsString ExportToProj4()const; 

	/// \brief 是否为空
	bool IsNull()const;
	 
	/// \brief 是否是相同的坐标系
	bool IsSame(GsSpatialReference* sr)const;
	/// \brief 是否是相同的投影坐标系
	bool IsSameProjCS(GsSpatialReference* sr)const;
	/// \brief 是否是相同的地理坐标系
	bool IsSameGeogCS(GsSpatialReference* sr)const;
	/// \brief 是否是本地坐标系
	bool IsLocalCS()const;
	/// \brief 是否是地理坐标系
	bool IsGeographic()const;
	/// \brief 是否是投影坐标系
	bool IsProjected()const;
	  
	
	/// \brief 椭球长半轴(公里 km)
	double EquatorialRadiusA()const; 

	/// \brief 椭球短半轴(公里 km)
	double PolarRadiusB()const; 

	/// \brief 椭球扁率的倒数
	double FlattenInverseF()const; 

	/// \brief 椭球平均半径(公里 km)
	double MeanRadius()const; 
	
	/// \brief EPSG
	int EPSG()const; 

	/// \brief 椭球名称
	Utility::GsString Ellipsoid()const;

	/// \brief 投影名称
	Utility::GsString Projection()const;


};
/// \brief GsSpatialReferencePtr
GS_SMARTER_PTR(GsSpatialReference);



/// \brief 空间参考管理对象。
/// \details 枚举现有的空间参考，增加新空间参考等等能力。
class GS_API GsSpatialReferenceManager
{
public:
	
	/// \brief 空间参考的分类。
	class GS_API GsSpatialReferenceCategory
	{
	public:
		virtual ~GsSpatialReferenceCategory();

		/// \brief 类别的名称
		virtual Utility::GsString Name() = 0;
		
		/// \brief 空间参考的数量
		virtual int Count() = 0;
		
		/// \brief根据索引获取空间参考对象
		virtual GsSpatialReferencePtr SpatialReference(int i) = 0;
	};
private:
	Utility::GsString m_DataFolder;

	std::vector<GsSpatialReferenceCategory*> m_Categorys;

public:
	/// \brief 指定特定目录构造空间参考管理对象
	GsSpatialReferenceManager(const char* strSRDataFolder = NULL);

	/// \brief 获取空间参考数据目录。
	Utility::GsString  DataFolder();

	/// \brief 空间参考的分类数量
	int CategoryCount();

	/// \brief 获取空间参考的一个分类
	GsSpatialReferenceCategory*  Category(int i );

};


/// \brief 坐标转换基类
class GS_API GsCoordinateTransformation:public Utility::GsRefObject
{
public:
	~GsCoordinateTransformation();
	/// \brief 对x数组和y数组以及Z数组分别转换
	virtual bool Transformation(double* pX,double *pY,double *pZ,int nPointCount,int nPointOff) = 0;
	/// \brief 对x，y，或者z构成的坐标数组进行转换
	virtual bool Transformation(double* pCoord,int nPointCount,int nDim);
};
/// \brief GsCoordinateTransformationPtr
GS_SMARTER_PTR(GsCoordinateTransformation);

/// \brief 投影坐标转换
class GS_API GsProjectCoordinateTransformation:public GsCoordinateTransformation
{
	void* m_pTrans;
	GsSpatialReferencePtr m_ptrSource;
	GsSpatialReferencePtr m_ptrTarget;
	void CreateHandle();
public:
	GsProjectCoordinateTransformation(GsSpatialReference* pSource,GsSpatialReference* pTarget);
	~GsProjectCoordinateTransformation();

	/// \brief 对x数组和y数组以及Z数组分别转换
	virtual bool Transformation(double* pX,double *pY,double *pZ,int nPointCount,int nPointOff);
	/// \brief 投影转换源空间参考
	GsSpatialReference* Source();
	/// \brief 设置投影转换源空间参考
	void Source(GsSpatialReference* pSR);

	/// \brief 投影转换目标空间参考
	GsSpatialReference* Target();
	/// \brief 设置投影转换目标空间参考
	void Target(GsSpatialReference* pSR);
};
/// \brief GsProjectCoordinateTransformationPtr
GS_SMARTER_PTR(GsProjectCoordinateTransformation);



/// \brief 仿射坐标转换
class GS_API GsAffineCoordinateTransformation:public GsCoordinateTransformation
{
	std::vector<double> m_Source;
	std::vector<double> m_Target;
	double m_Matrix[6];
public:
	/// \brief 根据源和目标同名点组构成仿射变换参数
	/// \details 最低需要3个点的坐标。
	GsAffineCoordinateTransformation(double* pSourcePoint,double* pTargetPoint,int nLen =  6);
	/// \brief 设置同名点参数
	bool Parameter(double* pSourcePoint,double* pTargetPoint,int nLen =  6);
	
	/// \brief 获取仿射变换矩阵的值。
	/// \param m 用于输出矩阵值得数组，长度6
	bool Elements(double* m);

	/// \brief 同名点数量
	int IdenticalPointCount();

	/// \brief 源的同名点坐标
	double* SourcePoint();
	/// \brief 目标的同名点坐标
	double* TargetPoint();
	/// \brief 对x数组和y数组以及Z数组分别转换
	virtual bool Transformation(double* pX,double *pY,double *pZ,int nPointCount,int nPointOff);

};
/// \brief GsAffineCoordinateTransformationPtr
GS_SMARTER_PTR(GsAffineCoordinateTransformation);


KERNEL_ENDNS