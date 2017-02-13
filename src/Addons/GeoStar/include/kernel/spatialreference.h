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

/// \brief 坐标轴方向
enum GsAxisOrientation{
	/// \brief 不确定方向
    eOther=0,
	/// \brief 朝北
    eNorth=1,
	/// \brief 朝南
    eSouth=2,
	/// \brief 朝东
    eEast=3,
	/// \brief 朝西
    eWest=4,
	/// \brief 朝上
    eUp=5,
	/// \brief 朝下
    eDown=6
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
	/// \details 使用全局配置项Kernel/SpatialRererence/EPSG设置EPSG.txt所在的路径
	/// \code{.cpp}
	///  GsGlobeConfig::Instance().Child("Kernel/SpatialRererence/EPSG").Value("...SpatialReferenceDataFolder\\EPSG.txt");
	/// 
	/// GsSpatialReferencePtr ptrSR = new GsSpatialReference(4326);
	/// {....}
	/// \endcode
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
	/// \brief 是否是相同的空间参数，可以作为空间参考是否相同的依据，但不绝对
	bool IsSameParameter(GsSpatialReference* sr) const;
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

	/// \brief 获取坐标轴的方向信息
	/// \param i 坐标轴的顺序（0或者1） 
	/// \param peOrientation 输出坐标轴的方向
	/// \return  返回坐标轴的名称或者空字符串
	Utility::GsString  Axis(int i,GsAxisOrientation* peOrientation);


};
/// \brief GsSpatialReferencePtr
GS_SMARTER_PTR(GsSpatialReference);


/// \brief 大地线，计算两个经纬度坐标的测地线长度，或称为大圆距离、球面距离
class GS_API GsGeodesic
{ 
protected:
  struct geodesic {
    double a;                   /**< the equatorial radius */
    double f;                   /**< the flattening */
    /**< @cond SKIP */
    double f1, e2, ep2, n, b, c2, etol2;
    double A3x[6], C3x[15], C4x[21];
    /**< @endcond */
  };
  geodesic m_gd;

public:
	/// \brief 从空间参考初始化
	GsGeodesic(GsSpatialReference* sr);
	
	/// \brief 从地球半径和扁率构造
	/// \param a 赤道半径 
	/// \param f 扁率
	GsGeodesic(double a,double f);

	/// \brief 拷贝构造函数
	GsGeodesic(const GsGeodesic& rhs);
	/// \brief 赋值操作符
	GsGeodesic& operator = (const GsGeodesic& rhs);


	/// \brief 计算测地线长度、大圆距离、球面距离
	/// \param fromLongitude 开始点经度
	/// \param fromLatitude 开始点纬度度
	/// \param toLongitude 结束点经度
	/// \param toLatitude 结束点纬度度
	/// \param fromAzimuth 输出开始点的方向角
	/// \param toAzimuth 输出结束点的方向角
	/// \return 测地线长度，单位米
	double Inverse(double fromLongitude,double fromLatitude,double toLongitude,double toLatitude,double* fromAzimuth,double* toAzimuth);

	
	/// \brief 根据起点经纬度坐标和方位角沿测试线前进一定长度到终点
	/// \param fromLongitude 开始点经度
	/// \param fromLatitude 开始点纬度度
	/// \param fromAzimuth 开始点方位角（以正北为0顺时针旋转的角度，单位度）
	/// \param lenth12 沿测地线前进的距离（单位米）
	/// \param toLongitude 输出终点的经度
	/// \param toLatitude 输出终点的纬度
	/// \param toLatitude 输出终点的方位角
	void Direct(double fromLongitude,double fromLatitude,double fromAzimuth,double length12,
				double* toLongitude,double* toLatitude,double* toAzimuth);


	/// \brief 寻找起点终点大圆上的t对应的点
	/// \param fromLongitude 开始点经度
	/// \param fromLatitude 开始点纬度度
	/// \param toLongitude 终点经度
	/// \param toLatitude 终点维度
	/// \param t 参数0~1标示起点和终点，可以小于0或者大于1
	/// \param Longitude 插值点的经度
	/// \param Latitude 插值点的维度
	/// \param Azimuth 插值点的方向角
	void Interpolation(double fromLongitude,double fromLatitude,double toLongitude,double toLatitude,double t,
				double* Longitude,double* Latitude,double* Azimuth);


};
/// \brief 一根测地线，已经确定了起点终点的大地线
class GS_API GsGeodesicLine:public GsGeodesic
{
	struct geodesicline {
	double lat1;                /**< the starting latitude */
	double lon1;                /**< the starting longitude */
	double azi1;                /**< the starting azimuth */
	double a;                   /**< the equatorial radius */
	double f;                   /**< the flattening */
	/**< @cond SKIP */
	double b, c2, f1, salp0, calp0, k2,
		salp1, calp1, ssig1, csig1, dn1, stau1, ctau1, somg1, comg1,
		A1m1, A2m1, A3c, B11, B21, B31, A4, B41;
	double C1a[6+1], C1pa[6+1], C2a[6+1], C3a[6], C4a[6];
	/**< @endcond */
	unsigned caps;              /**< the capabilities */
	};
	geodesicline m_L;
	
public:
	 /**
   * mask values for the \e caps argument to geod_lineinit().
   **********************************************************************/
  enum GeoDMask {
    eGEOD_NONE         = 0U,                     /**< Calculate nothing */
    eGEOD_LATITUDE     = 1U<<7  | 0U,            /**< Calculate latitude */
    eGEOD_LONGITUDE    = 1U<<8  | 1U<<3,         /**< Calculate longitude */
    eGEOD_AZIMUTH      = 1U<<9  | 0U,            /**< Calculate azimuth */
    eGEOD_DISTANCE     = 1U<<10 | 1U<<0,         /**< Calculate distance */
    eGEOD_DISTANCE_IN  = 1U<<11 | 1U<<0 | 1U<<1, /**< Allow distance as input  */
    eGEOD_REDUCEDLENGTH= 1U<<12 | 1U<<0 | 1U<<2, /**< Calculate reduced length */
    eGEOD_GEODESICSCALE= 1U<<13 | 1U<<0 | 1U<<2, /**< Calculate geodesic scale */
    eGEOD_AREA         = 1U<<14 | 1U<<4,         /**< Calculate reduced length */
    eGEOD_ALL          = 0x7F80U| 0x1FU          /**< Calculate everything */
  };
public:
	/// \brief 根据空间参考，起点的经纬度和方向角确定一根测地线
	GsGeodesicLine(GsSpatialReference* sr,double fromLongitude,double fromLatitude,double fromAzimuth,GeoDMask mask);
	/// \brief 拷贝构造函数
	GsGeodesicLine(const GsGeodesicLine& rhs);
	/// \brief 赋值操作符
	GsGeodesicLine& operator = (const GsGeodesicLine& rhs);

	/// \brief 根据距离获得测地线上的点坐标
	/// \param distance 距离起点的距离，单位米
	/// \param toLatitude 终点的经度
	/// \param toLongitude 终点的纬度
	/// \param toAzimuth 终点的方位角
	void Position(double distance,double* toLatitude, double* toLongitude, double* toAzimuth);

};

/// \brief 测地线多边形，以测地线构成的多边形
class GS_API GsGeodesicPolygon:public GsGeodesic
{ 
  struct GeoDPolygon {
    double lat;                 /**< the current latitude */
    double lon;                 /**< the current longitude */
    /**< @cond SKIP */
    double lat0;
    double lon0;
    double A[2];
    double P[2];
    int polyline;
    int crossings;
    /**< @endcond */
    unsigned num;               /**< the number of points so far */
  };
  GeoDPolygon m_PG;
public:
	/// \brief 构造一个多边形或者Polyline
	GsGeodesicPolygon(GsSpatialReference* sr,bool bPolyline = false);

	/// \brief 拷贝构造
	GsGeodesicPolygon(const GsGeodesicPolygon& rhs);
	/// \brief 赋值操作符
	GsGeodesicPolygon& operator=(const GsGeodesicPolygon& rhs);


	/// \brief 增加一个边界点
	/// \param lon 经度
	/// \param lat 纬度
	void AddPoint(double lon,double lat);

	/// \brief 以方位角、长度增加一条边
	void AddEdge(double dblAzimuth,double dblLen);

	/// \brief 计算多边形的球面面积以及周长
	/// \param bReverse 是否反向，如果为true（反向）则认为逆时针多边形得到负的面积值。(标准积分面积逆时针方向的点返回正面积）
	/// \param bSign  是否带符号返回面积，如果时则在方向正确时返回正面积不正确时返回负面积， 否则将返回多边形外的地球面积。
	/// \param pArea  当构造时使用非Polyline参数则返回球面面积，否则不返回
	/// \param pPerimeter    返回多边形或者polyline的周长
	/// \return 返回多边形或者折线有多少个点
	unsigned int Compute(bool bReverse,bool bSign,double* pArea,double *pPerimeter);

};



/// \brief 空间参考管理对象。
/// \details 枚举现有的空间参考，增加新空间参考等等能力。
class GS_API GsSpatialReferenceManager
{
public:
	/// \brief 特殊分类
	enum GsSpecialCategory
	{
		/// \brief 标准EPSG分类
		eStandardEPSG,
		/// \brief EPSG别名分类
		eAliasOfEPSG,
	};

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

	GsVector<GsSpatialReferenceCategory*> m_Categorys;

public:
	/// \brief 指定特定目录构造空间参考管理对象
	GsSpatialReferenceManager(const char* strSRDataFolder = NULL);
	~GsSpatialReferenceManager();

	/// \brief 获取空间参考数据目录。
	Utility::GsString  DataFolder();

	/// \brief 空间参考的分类数量
	int CategoryCount();

	/// \brief 获取空间参考的一个分类
	GsSpatialReferenceCategory*  Category(int i );

	/// \brief 获取特殊的空间参考分类。
	GsSpatialReferenceCategory*  SpecialCategory(GsSpecialCategory eType );

};


/// \brief 坐标转换基类
class GS_API GsCoordinateTransformation:public Utility::GsRefObject
{
public:
	~GsCoordinateTransformation();
	/// \brief 对x数组和y数组以及Z数组分别转换
	virtual bool Transformation(double* pX,double *pY,double *pZ,int nPointCount,int nPointOff) = 0;
	virtual bool Transformation(double* pX,double *pY,int nPointCount,int nPointOff);
	/// \brief 对x，y，或者z构成的坐标数组进行转换
	virtual bool Transformation(double* pCoord,int nPointCount,int nDim);
};
/// \brief GsCoordinateTransformationPtr
GS_SMARTER_PTR(GsCoordinateTransformation);

/// \brief 投影坐标转换
class GS_API GsProjectCoordinateTransformation:public GsCoordinateTransformation
{
protected:
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


/// \brief 坐标换换方法
enum GsCoordinateTransformationMethod
{
	/// \brief 位置矢量法
	///\details 七参数赫尔默特（Helmert）转换法，依据布尔莎（Bursa-Wolf）公式
	///\details 由国际大地测量协会（IAG）通过ISO19111标准定义
    ///\details 与坐标框架法不同的是7参数中三个旋转参数的方向相反。
	ePositionVector,

	/// \brief 坐标框架法
	///\details 七参数赫尔默特（Helmert）转换法，依据布尔莎（Bursa-Wolf）公式
	///\details 由EPSG（欧洲石油勘探组织）定义
	///\details 与位置矢量法不同的是7参数中三个旋转参数的方向相反。
    eCoordinateFrame,

	/// \brief 基于地心的三参数转换法。
	eGeocentricTranslation,
};

/// \brief 参数化的投影坐标转换
/// \details 定义不同投影间的转换方法和转换参数
/// \details 从一个大地经纬度坐标系变换到另一个大地经纬度坐标系一般需要经过三个环节：大地经纬度坐标系到空间直角坐标系>空间直角坐标系到空间直角坐标系>空间直角坐标系到大地经纬度坐标系。
/// \details 其中的中间环节，空间直角坐标到空间直角坐标采用七参数赫尔默特（Helmert）转换法，其转换矩阵为著名的布尔沙-沃尔夫（Bursa-Wolf）公式,或者三参数等不同的转换方法
class GS_API GsParameterProjectCoordinateTransformation:public GsProjectCoordinateTransformation
{
	/// \brief 转换参数。
	GsVector<double> m_vecParam;
	/// \brief 转换参数。
	GsCoordinateTransformationMethod m_eMethod;
public:
	/// \brief 从转换方法和转换参数构造
	GsParameterProjectCoordinateTransformation(GsSpatialReference* pSource,GsSpatialReference* pTarget,
							GsCoordinateTransformationMethod eMethod,double* pParam);
	
	/// \brief 获取数据转换的方法
	GsCoordinateTransformationMethod Method();
	
	/// \brief 设置坐标转换的方法和参数值。
	void Parameter(GsCoordinateTransformationMethod method,double* pParam);

};
/// \brief GsParameterProjectCoordinateTransformationPtr
GS_SMARTER_PTR(GsParameterProjectCoordinateTransformation);


/// \brief 仿射坐标转换
/// \details 推导过程 
///  XL = A0 + A1 * XD + A2 * YD
///  YL = B0 + B1 * XD + B2 * YD
class GS_API GsAffineCoordinateTransformation:public GsCoordinateTransformation
{
	std::vector<double> m_Source;
	std::vector<double> m_Target;
	double m_Matrix[6];
public:
	/// \brief 根据源和目标同名点组构成仿射变换参数
	/// \details 最低需要3个点的坐标,即nLen为6。
	GsAffineCoordinateTransformation(double* pSourcePoint,double* pTargetPoint,int nLen =  6);

	/// \brief 根据访射变换矩阵构造
	/// \details 访射变换矩阵为6个double 每个元素的意义如下：[a1][b1][a2][b2][a0][b0]
	GsAffineCoordinateTransformation(double* pMatirx);

	/// \brief 设置同名点参数
	bool Parameter(double* pSourcePoint,double* pTargetPoint,int nLen =  6);
	
	/// \brief 获取仿射变换矩阵的值。
	/// \param m 用于输出矩阵值得数组，长度6
	/// \details 访射变换矩阵为6个double 每个元素的意义如下：[a1][b1][a2][b2][a0][b0]
	bool Elements(double* m);

	/// \brief 获取访射变换矩阵指针
	/// \details 访射变换矩阵为6个double 每个元素的意义如下：[a1][b1][a2][b2][a0][b0]
	double* Matrix();

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

/// \brief 从WGS84坐标系转GCJ02(火星）坐标系。
/// \details https://en.wikipedia.org/wiki/Restrictions_on_geographic_data_in_China
class GS_API GsWGS84ToGCJ02CoordinateTransformation:public GsCoordinateTransformation
{
public:
	/// \brief 对x数组和y数组以及Z数组分别转换
	virtual bool Transformation(double* pX,double *pY,double *pZ,int nPointCount,int nPointOff);
};
/// \brief GsWGS84ToGCJ02CoordinateTransformationPtr
GS_SMARTER_PTR(GsWGS84ToGCJ02CoordinateTransformation);


/// \brief 转从GCJ02(火星）坐标系反转为WGS84
/// \details https://en.wikipedia.org/wiki/Restrictions_on_geographic_data_in_China
class GS_API GsGCJ02ToWGS84CoordinateTransformation:public GsCoordinateTransformation
{
protected:
	double m_dblPrecision;
public:
	/// \brief 从转换精度构造
	/// \param dblPrecision 反转的精确度，单位米
	GsGCJ02ToWGS84CoordinateTransformation(double dblPrecision);

	/// \brief 对x数组和y数组以及Z数组分别转换
	virtual bool Transformation(double* pX,double *pY,double *pZ,int nPointCount,int nPointOff);
};

/// \brief GsGCJ02ToWGS84CoordinateTransformationPtr
GS_SMARTER_PTR(GsGCJ02ToWGS84CoordinateTransformation);

/// \brief 从WGS84坐标系转BD09(百度）坐标系。
/// \details https://en.wikipedia.org/wiki/Restrictions_on_geographic_data_in_China
class GS_API GsWGS84ToBD09CoordinateTransformation:public GsWGS84ToGCJ02CoordinateTransformation
{
public:
	/// \brief 对x数组和y数组以及Z数组分别转换
	virtual bool Transformation(double* pX,double *pY,double *pZ,int nPointCount,int nPointOff);
};
/// \brief GsWGS84ToGCJ02CoordinateTransformationPtr
GS_SMARTER_PTR(GsWGS84ToBD09CoordinateTransformation);


/// \brief 转从BD09(百度）坐标系反转为WGS84
/// \details https://en.wikipedia.org/wiki/Restrictions_on_geographic_data_in_China
class GS_API GsBD09ToWGS84CoordinateTransformation:public GsGCJ02ToWGS84CoordinateTransformation
{
	
public:
	/// \brief 从转换精度构造
	/// \param dblPrecision 反转的精确度，单位米
	GsBD09ToWGS84CoordinateTransformation(double dblPrecision);

	/// \brief 对x数组和y数组以及Z数组分别转换
	virtual bool Transformation(double* pX,double *pY,double *pZ,int nPointCount,int nPointOff);
};
/// \brief GsBD09ToWGS84CoordinateTransformationPtr
GS_SMARTER_PTR(GsBD09ToWGS84CoordinateTransformation);

KERNEL_ENDNS