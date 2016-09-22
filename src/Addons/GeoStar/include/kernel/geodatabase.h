#pragma once
#include "../utility/preconfig.h"
#include <utility.h> 
#include <geometry.h>
#include <spatialreference.h>
#include <pyramid.h> 

KERNEL_NS 

//前向声明
class GsGeoDatabase;
class GsFeatureClass; 
class GsRasterClass; 
class GsRowClass; 
class GsDataRoomFolder;  

/// \brief 数据源类型
enum GsDataSourceType
{
	/// \brief 未知数据源类型
	eUnknownDataSource,
	/// \brief Sqlite文件数据源
	eSqliteFile,
	/// \brief ESRI Shape文件数据源
	eShapeFile,
	/// \brief OGC GeoPakcage数据源
	eGeoPackage,
	/// \brief OracleSpatial数据源
	eOracleSpatial,
	/// \brief MySQL数据源
	eMySQL,
	/// \brief PostgreSQL数据源
	ePostgreSQL,
    /// \brief 所有文件类型的数据源
    eFile,

    /// \brief 达梦数据源
    eDameng,
	
};

/// \brief 空间数据库支持的能力
enum GsGeoDatabaseCapbility
{
	/// \brief 数据库是否支持事务
	eSupportTransaction,

	/// \brief 数据库是否支持矢量地物类的存储
	eSupportStoreFeatureClass,

	/// \brief 数据库是否支持普通二维表的存储
	eSupportStoreRowClass,

	/// \brief 数据库是否支持瓦片类的存储
	eSupportStoreTileClass,

	/// \brief 数据库是数据集目录
	eSupportDataRoomFolder,

	/// \brief 数据库是数据集目录多级递归
	/// \details 数据集目录下是否还可以支持数据集目录。
	eSupportRecursiveDataRoomFolder,

	/// \brief 数据源是否支持栅格数据存储
	eSupportStoreRasterClass,

	/// \brief 数据源是否支持镶嵌栅格数据存储
	eSupportStoreMosaicRasterClass,
};


////\class GsConnectProperty
///\brief 数据库连接信息
///\details 定义数据库连接的各类信息以及数据库类型等
struct GS_API GsConnectProperty
{
	///\brief 数据库连接信息版本。
	int						Version;
	///\brief 数据服务地址或者文件路径
	Utility::GsString				Server;
	///\brief 数据库名称
	Utility::GsString				Database;
	///\brief 用户名
	Utility::GsString				User;
	///\brief 密码
	Utility::GsString				Password;
	///\brief 端口号
	int						Port;
	///\brief 数据源类型
	GsDataSourceType		DataSourceType;

	 
	///\brief 缺省构造函数. 
	GsConnectProperty();
	/// \brief 拷贝构造函数
	///\param other 需要拷贝的对象
    GsConnectProperty(const GsConnectProperty& other);
	
	/// \brief 根据服务地址、文件路径、url地址构造
	///\param strServer 服务、文件、url地址
    GsConnectProperty(const char* strServer);
	/// \brief 根据服务地址、文件路径、url地址和数据库名称构造
	///\param strServer 服务、文件、url地址
	///\param strDatabase 数据库名称
    GsConnectProperty(const char* strServer,const char* strDatabase);
	/// \brief 根据服务器地址、数据库和用户名密码构造
	///\param strServer 服务、文件、url地址
	///\param strDatabase 数据库名称
	///\param strUser 用户名
	///\param strPwd 密码
    GsConnectProperty(const char* strServer,const char* strDatabase,const char* strUser,const char* strPwd);
	/// \brief 根据服务器地址、数据库和用户名密码、端口构造
	///\param strServer 服务、文件、url地址
	///\param strDatabase 数据库名称
	///\param strUser 用户名
	///\param strPwd 密码
	///\param nPort 端口
	GsConnectProperty(const char* strServer,const char* strDatabase,const char* strUser,const char* strPwd,int nPort);
	/// \brief 根据服务器地址、数据库和用户名密码、端口、数据源类型构造
	///\param strServer 服务、文件、url地址
	///\param strDatabase 数据库名称
	///\param strUser 用户名
	///\param strPwd 密码
	///\param nPort 端口
	///\param sourceType 数据源类型
    GsConnectProperty(const char* strServer,const char* strDatabase,const char* strUser,const char* strPwd,int nPort,GsDataSourceType sourceType);
};

/// \brief 数据集对象类型
enum GsFeatureType
{
	/// \brief 矢量地物类
	eSimpleFeature,
	/// \brief 瓦片类
	eAnnotationFeature,
	/// \brief 矢量瓦片
	eVectorTileFeature,
	/// \brief 影像瓦片
	eImageTileFeature,
	/// \brief 地形瓦片
	eTerrainTileFeature,
};


 
/// \brief 数据集对象类型
enum GsDataRoomType
{
	/// \brief 矢量地物类
	eFeatureClass,
	/// \brief 瓦片类
	eTileClass,
	/// \brief 二维表
	eRowClass,
	/// \brief 数据集的集合
	eDataRoomFolder,
	/// \brief 栅格类
	eRasterClass,
};

/// \brief 选择集操作类型
enum GsSelectionSetOperation
{
	/// \brief 选择集求并
	eSelectionSetUnion,
	/// \brief 选择集求交
	eSelectionSetIntersection,
	/// \brief 选择集求差
    eSelectionSetDifference,
	/// \brief 选择集求对称差
    eSelectionSetSymDifference,
};
 
/// \brief 数据集对象基类
class GS_API GsDataRoom:public Utility::GsRefObject
{
protected:
	
	Utility::GsSmarterPtr<GsGeoDatabase> m_ptrGDB;
	Utility::GsString m_strName;
	Utility::GsSmarterPtr<GsDataRoomFolder> m_ptrFolder;
	GsDataRoom();
public:
	virtual ~GsDataRoom();

	/// \brief 打断正在运行中的操作
	/// \return 不支持打断操作的能力则返回false，成功打断或者无须打断都返回true
	virtual bool Interrupt();


	/// \brief 数据集所在的目录
	///\return 返回数据集所在的目录，如果为空则标识数据集在GeoDatabase下
	virtual GsDataRoomFolder* Folder();


	/// \brief 数据集名称
	///\return 返回数据集对象的名称
	virtual Utility::GsString Name();
	/// \brief 数据集类型
	///\return 返回数据集对象的类型
	virtual GsDataRoomType Type() = 0;

	/// \brief 数据集所在的数据库对象
	///\return 返回数据库对象指针
	virtual GsGeoDatabase* GeoDatabase();

	/// \brief 删除
	///\return 返回是否删除成功
	virtual bool Delete() = 0;

	/// \brief 是否处于事务中
	///\return 返回是否处于事务中
	virtual bool IsTransaction();

	/// \brief 启动事务
	///\return 返回是否成功启动
	virtual bool StartTransaction();

	/// \brief 提交事务
	///\return 返回是否提交成功
	virtual bool CommitTransaction();

	/// \brief 取消事务
	///\return 返回是否取消成功
	virtual bool RollbackTransaction();
};
/// \brief  声明GsDataRoomPtr智能指针
GS_SMARTER_PTR(GsDataRoom);

/// \brief 具备地理特性的数据集对象抽象基类
class GS_API GsGeoDataRoom:public GsDataRoom
{
public:
	virtual ~GsGeoDataRoom();

	/// \brief 获取最大外接矩形范围
	///\param bForce 是否强制获取，强制获取将会从数据表中统计最大范围
	///\return 返回矩形对象
	virtual GsBox Extent(bool bForce = false) = 0;

	
	/// \brief 获取数据集的空间参考
	///\return 返回空间参考对象的指针
	virtual GsSpatialReference* SpatialReference() = 0;

	/// \brief 修改数据集的空间参考
	///\return 返回修改是否成功
	virtual bool ChangeSpatialReference(GsSpatialReference* pSR) = 0;

};
/// \brief GsGeoDataRoomPtr
GS_SMARTER_PTR(GsGeoDataRoom);

/// \brief 属性条件查询
class GS_API GsQueryFilter:public Utility::GsRefObject
{
protected:
	/// \brief where子句
	Utility::GsString  m_strWhereClause;
	GsGeometrySimplifierPtr	m_ptrSimplifier;
public:
	/// \brief 从where子句构造
	///\param strWhere SQL查询的where子句
	GsQueryFilter(const char* strWhere = NULL);
	virtual ~GsQueryFilter();
	
	/// \brief 设置几何简化的方法
	void Simplifier(GsGeometrySimplifier* method);
	
	/// \brief 获取几何简化的方法
	GsGeometrySimplifier* Simplifier() const;

	/// \brief 获取where子句
	///\return 返回where子句字符串
	virtual Utility::GsString WhereClause();

	/// \brief 设置where子句查询条件
	///\param strWhere SQL查询的where子句
	virtual void WhereClause(const char* strWhere);

	/// \brief 以And合并两个过滤条件
	///\param pOther 另外一个合并的条件
	///\return 返回合并是否成功
	virtual bool And(GsQueryFilter* pOther);

	/// \brief 以Or合并两个过滤条件
	///\param pOther 另外一个合并的条件
	///\return 返回合并是否成功
	virtual bool Or(GsQueryFilter* pOther);

	/// \brief 复制过滤条件对象
	virtual Utility::GsSmarterPtr<GsQueryFilter> Clone();

};
/// \brief GsQueryFilterPtr
GS_SMARTER_PTR(GsQueryFilter);

/// \brief 空间属性查询条件
class GS_API GsSpatialQueryFilter:public GsQueryFilter
{
	/// \brief 空间查询几何对象
	GsGeometryPtr m_ptrGeo;
	/// \brief 过滤方式
	Utility::GsString  m_strFilterType;
	
	/// \brief 过滤索引对象，
	void* m_pFilterIndex;

public:
	/// \brief 从几何对象构造
	///\param pGeo 查询的几何对象指针
	GsSpatialQueryFilter(GsGeometry* pGeo = NULL);
	/// \brief 从几何对象和where子句构造
	///\param pGeo 查询的几何对象指针
	///\param strWhere 查询SQL语句where子句
	GsSpatialQueryFilter(GsGeometry* pGeo,const char* strWhere);
	/// \brief 从几何对象,where子句和查询方式字符串构造
	///\param pGeo 查询的几何对象指针
	///\param strWhere 查询SQL语句where子句
	///\param strFilterType 查询方式
	GsSpatialQueryFilter(GsGeometry* pGeo,const char* strWhere, const char *strFilterType);
	~GsSpatialQueryFilter();

	/// \brief 获取空间查询几何对象
	///\return 返回查询的几何对象指针
	GsGeometry* Geometry();

	/// \brief 设置空间查询几何对象
	///\param pGeo 查询的几何对象指针
	void Geometry(GsGeometry* geo);

	/// \brief 获取查询方式
	///\return 返回查询方式字符串
	virtual Utility::GsString FilterType();

	/// \brief 设置查询方式
	///\param strFilterType 查询方式字符串表达式
	virtual void FilterType(const char* strFilterType);

	
	/// \brief 判断一个传入的Geometry是否符合几何过滤条件。
	///\param pGeo 要判断的几何对象
	///\return 返回是否匹配几何过滤条件。
	virtual bool IsMatch(GsGeometry* pGeo);

	/// \brief 判断一个传入的Geometry是否符合几何过滤条件。
	///\param pGeo 要判断的几何对象
	///\return 返回是否匹配几何过滤条件。
	virtual bool IsMatch(GsGeometryBlob* pBlob);


	/// \brief 以And合并两个过滤条件
	///\param pOther 另外一个合并的条件
	///\return 返回合并是否成功
	virtual bool And(GsQueryFilter* pOther);

	/// \brief 以Or合并两个过滤条件
	///\param pOther 另外一个合并的条件
	///\return 返回合并是否成功
	virtual bool Or(GsQueryFilter* pOther);

	/// \brief 复制过滤条件对象
	virtual Utility::GsSmarterPtr<GsQueryFilter> Clone();

};
/// \brief GsSpatialQueryFilterPtr
GS_SMARTER_PTR(GsSpatialQueryFilter);

///\brief 字段
struct GS_API GsField
{	
	///\brief 字段名称
	Utility::GsString				Name;
	
	///\brief 字段类型
	Utility::Data::GsFieldType		Type;

	///\brief 字段精度
	int								Precision;
	///\brief 小数位
	int								Scale;
	///\brief 是否允许为空
	bool							IsNullable;

	///\brief 拷贝构造函数
	GsField(const GsField& rhs);

	///\brief 从名称和类型构造
	///\param strName 字段名称
	///\param eType 字段类型
	GsField(const char* strName,Utility::Data::GsFieldType eType);

	///\brief 从名称和类型、精度和小数位构造
	///\param strName 字段名称
	///\param eType 字段类型
	///\param nPrecision 字段精度
	///\param nScale 字段小数位长度
	GsField(const char* strName,Utility::Data::GsFieldType eType,int nPrecision,int nScale=0);

	
	///\brief 将字段信息序列化为xml字符串
	Utility::GsString ToXml() const;
};
///\brief 字段集合
struct GS_API GsFields
{
	GsVector<GsField> Fields;

	///\brief 寻找字段的索引
	int FindField(const char* strFieldName)const;
	
	///\brief 将字段信息序列化为xml字符串
	Utility::GsString ToXml()const;

}; 

///\brief 几何字段信息
struct GS_API GsGeometryColumnInfo
{
	///\brief 是否存在Z维度
	bool			HasZ; 
	///\brief 几何类型
	GsGeometryType  GeometryType;
	///\brief 地物类型
	GsFeatureType	FeatureType;
	///\brief 比例尺
	double			MapScale;
	///\brief X，Y维度范围
	GsBox			XYDomain;
	///\brief Z维度范围
	double			ZMin,ZMax;
	///\brief 缺省构造
	GsGeometryColumnInfo();
	///\brief 拷贝构造
	GsGeometryColumnInfo(const GsGeometryColumnInfo& rhs);
	///\brief 从几何类型，地物类型和xy维度范围构造
	GsGeometryColumnInfo(GsGeometryType  gType,GsFeatureType fType,const GsBox& xydomain);
	///\brief 从几何类型，地物类型和xy维度范围，z维度范围构造
	GsGeometryColumnInfo(GsGeometryType  gType,GsFeatureType fType,const GsBox& xydomain,double zmin,double zmax);
};


///\brief 瓦片类基本信息
struct GS_API GsTileColumnInfo
{
	///\brief 地物类型
	GsFeatureType	FeatureType; 
	///\brief X，Y维度范围
	GsBox			XYDomain;
	
	///\brief 有效的顶层级别
	int				ValidTopLevel;
	///\brief 有效的底层级别
	int				ValidBottomLevel;

	///\brief 缺省构造
	GsTileColumnInfo();
	///\brief 拷贝构造
	GsTileColumnInfo(const GsTileColumnInfo& rhs);

	///\brief 从地物类型和范围构造
	GsTileColumnInfo(GsFeatureType fType,const GsBox& xydomain);

};


class GS_API GsRow:public Utility::GsRefObject
{
protected:
	/// \brief 矢量地物对象唯一ID
	long long m_nOID;
	GsRow();
public:
	virtual ~GsRow();

	/// \brief 获取对象唯一ID
	///\return 返回唯一ID，如果ID小于0则表示对象为新的未存储对象
	virtual long long OID();

	/// \brief 设置对象的id
	/// \details 通过设置地物的id为-1改变对象为新对象
	///\param oid 对象唯一ID
	void OID(long long oid);
	
	/// \brief 获取整形值
	///\param nColumn 列索引
	///\return 返回32位整数值
	virtual int ValueInt(int nColumn);
	/// \brief 获取无符号整形值
	///\param nColumn 列索引
	///\return 返回32位无符号整数值
	virtual unsigned int ValueUInt(int nColumn);
	
	/// \brief 获取64位整数值
	///\param nColumn 列索引
	///\return 返回64位整数值
	virtual long long ValueInt64(int nColumn);
	/// \brief 获取64位无符号整数值
	///\param nColumn 列索引
	///\return 返回64位无符号整数值
	virtual unsigned long long ValueUInt64(int nColumn);

	/// \brief 获取单精度浮点值
	///\param nColumn 列索引
	///\return 返回单精度浮点值
	virtual float ValueFloat(int nColumn);
	/// \brief 获取双精度浮点值
	///\param nColumn 列索引
	///\return 返回双精度浮点值
	virtual double ValueDouble(int nColumn);

	/// \brief 获取字符串值
	///\param nColumn 列索引
	///\return 返回字符串值
	virtual Utility::GsString ValueString(int nColumn);
	/// \brief 获取二进制块
	///\param nColumn 列索引
	///\return 返回二进制块
	virtual Utility::GsString ValueBlob(int nColumn);

	/// \brief 获取值的指针
	///\param nColumn 列索引
	///\return 返回值的指针
	virtual unsigned char* ValuePtr(int nColumn) = 0;
	/// \brief 获取值的字节长度
	///\param nColumn 列索引
	///\return 返回值的字节长度
	virtual unsigned int ValueSize(int nColumn) = 0;
	/// \brief 获取列的数据类型
	///\param nColumn 列索引
	///\return 返回列的数据类型枚举
	virtual Utility::Data::GsFieldType ValueType(int nColumn) = 0;

	/// \brief 设置32位整数值
	///\param nColumn 列索引
	///\param nValue 整数值
	virtual void Value(int nColumn,int nValue);
	/// \brief 设置无符号32位整数值
	///\param nColumn 列索引
	///\param value 整数值
	virtual void Value(int nColumn,unsigned int value);

	/// \brief 设置字符串值
	///\param nColumn 列索引
	///\param value 字符串值
	virtual void Value(int nColumn,const char* value);
	/// \brief 设置单精度浮点值
	///\param nColumn 列索引
	///\param value 单精度浮点值
	virtual void Value(int nColumn,float value);
	/// \brief 设置双精度浮点值
	///\param nColumn 列索引
	///\param value 双精度浮点值
	virtual void Value(int nColumn,double value);
	/// \brief 设置二进制值
	///\param nColumn 列索引
	///\param value 二进制值
	///\param nSize 二进制值长度
	virtual void Value(int nColumn,const unsigned char* value,int nSize);
	/// \brief 设置64位整数
	///\param nColumn 列索引
	///\param value 64位整数值
	virtual void Value(int nColumn,long long  value);
	/// \brief 设置无符号64位整数
	///\param nColumn 列索引
	///\param value 无符号64位整数值
	virtual void Value(int nColumn,unsigned long long  value);

	/// \brief 根据字段类型设置任意值
	///\param nColumn 列索引
	///\param value 无符号64位整数值
	///\param nSize 值长度
	///\param eType 字段类型
	virtual void Value(int nColumn,const unsigned char* value,int nSize,Utility::Data::GsFieldType eType) = 0;

	
	/// \brief 保存对象到数据库或文件
	///\return 返回保存是否成功
	virtual bool Store() = 0;

	/// \brief 从数据库或者文件删除对象
	///\return 返回删除是否成功
	virtual bool Delete() = 0;
};
/// \brief GsRowPtr
GS_SMARTER_PTR(GsRow);


/// \brief 瓦片对象
class GS_API GsTile:public GsRow
{
protected:
	GsTile();
public:
	virtual ~GsTile();

	/// \brief 获取级别
	virtual int Level();
	/// \brief 设置级别
	virtual void Level(int nLevel);
	/// \brief 获取行
	virtual int Row();
	/// \brief 设置行
	virtual void Row(int r);
	/// \brief 获取列
	virtual int Col();
	/// \brief 设置列
	virtual void Col(int c);

	/// \brief 获取瓦片类型
	virtual GsFeatureType TileType() = 0;
	/// \brief 设置瓦片类型
	virtual void TileType(GsFeatureType eType) = 0;

	/// \brief 设置瓦片数据
	virtual void TileData(const unsigned char* pData,int nLen) = 0;
	
	/// \brief 获取瓦片数据指针
	virtual unsigned char* TileDataPtr() = 0;
	
	/// \brief 获取瓦片数据长度。
	virtual int TileDataLength() = 0;

};
/// \brief GsTilePtr
GS_SMARTER_PTR(GsTile);



/// \brief 矢量地物对象
class GS_API GsFeature:public GsRow
{
protected: 

	/// \brief 矢量地物几何数据
	GsGeometryPtr m_ptrGeo;

	/// \brief 矢量地物所在的地物类
	Utility::GsSmarterPtr<GsFeatureClass> m_ptrFeaClass;
	
	/// \brief 几何对象
	GsGeometryBlob		m_OGS;

	GsFeature();
public:
	virtual ~GsFeature();

	/// \brief 获取几何数据
	///\return 返回几何对象的指针
	virtual GsGeometry* Geometry();

	/// \brief 设置几何数据
	///\param Geo 几何对象指针，内部不会拷贝
	virtual void Geometry(GsGeometry* Geo);

	/// \brief 设置几何数据
	///\param Geo 几何Blob数据
	virtual void Geometry(GsGeometryBlob* Geo);

	/// \brief 获得Geometry的Blob数据指针
	virtual GsGeometryBlob* GeometryBlob();


	/// \brief 获取地物所在的地物类
	///\return 返回所在的地物类指针
	virtual GsFeatureClass* FeatureClass();
};
/// \brief GsFeaturePtr
GS_SMARTER_PTR(GsFeature);

/// \brief 地物游标
/// \code{.cpp}
///  GsFeaturePtr ptrFea = ptrCursor->Next();
///  do{
///     DoSomeThing(ptrFea);
///	  }while(ptrCursor->Next(ptrFea.p);
/// \endcode
class GS_API GsFeatureCursor:public Utility::GsRefObject
{
public:
	/// \brief 获取下一个地物对象
	/// \details 每次回生成一个新的地物对象
	///\return 返回下一个地物对象的实例或者空
	virtual GsFeaturePtr Next() = 0;
	
	/// \brief 获取下一个地物对象数据而不用产生新的对象
	/// \details 性能更高的方法，以访问者模式将下一个地物的数据设置到传入的地物对象内部。
	///\param pFea 一个非空地物对象的指针
	///\return 返回是否存在下一个地物，如果传入地物对象为空则一定范围false
	virtual bool Next(GsFeature* pFea) = 0;
};
/// \brief GsFeatureCursorPtr
GS_SMARTER_PTR(GsFeatureCursor);

class GS_API GsRowCursor:public Utility::GsRefObject
{
	
public:
	/// \brief 获取下一个行对象
	/// \details 每次回生成一个新的行对象
	///\return 返回下一个行对象的实例或者空
	virtual GsRowPtr Next() = 0;
	
	/// \brief 获取下一个行对象数据而不用产生新的对象
	/// \details 性能更高的方法，以访问者模式将下一个地物的数据设置到传入的行对象内部。
	///\param pFea 一个非空行对象的指针
	///\return 返回是否存在下一个行，如果传入行对象为空则一定范围false
	virtual bool Next(GsRow* pRow) = 0;
};

/// \brief GsRowCursorPtr
GS_SMARTER_PTR(GsRowCursor);



/// \brief 瓦片游标
/// \code{.cpp}
///  GsTilePtr ptrTile = ptrCursor->Next();
///  do{
///     DoSomeThing(ptrTile);
///	  }while(ptrCursor->Next(ptrTile.p);
/// \endcode
class GS_API GsTileCursor:public Utility::GsRefObject
{
	
public:
	/// \brief 获取下一个瓦片对象
	/// \details 每次回生成一个新的瓦片对象
	///\return 返回下一个瓦片对象的实例或者空
	virtual GsTilePtr Next() = 0;
	
	/// \brief 获取下一个瓦片对象数据而不用产生新的对象
	/// \details 性能更高的方法，以访问者模式将下一个地物的数据设置到传入的瓦片对象内部。
	///\param pFea 一个非空瓦片对象的指针
	///\return 返回是否存在下一个行，如果传入行对象为空则一定返回false
	virtual bool Next(GsTile* pRow) = 0;
};

/// \brief GsTileCursorPtr
GS_SMARTER_PTR(GsTileCursor);

/// \brief 地物类OID枚举器
class GS_API GsEnumIDs:public Utility::GsRefObject
{
public:
	/// \brief 获取下一个地物的OID
	/// \details 每次得到下一个地物的OID
	///\return 返回下一个地物的OID
	virtual long long Next() = 0;

	/// \brief 重置枚举器
	/// \details 调用Reset后，下次调用Next会得到第一个OID
	virtual void Reset() = 0;
};
/// \brief GsEnumIDsPtr
GS_SMARTER_PTR(GsEnumIDs);

/// \brief 选择集
class GS_API GsSelectionSet:public Utility::GsRefObject
{
public:
	/// \brief 获得选择集中地物的数量
	/// \details 获得选择集中地物的数量
	///\return 返回包含的地物数量
	virtual unsigned int Count() = 0;

	/// \brief 获取地物OID枚举器
	/// \details 获取选择集中地物OID的集合
	///\return 返回地物OID枚举器
	virtual GsEnumIDsPtr EnumIDs() = 0;

	/// \brief 往选择集中添加一个OID
	///\param OID 要添加的OID值
	virtual void Add (long long OID) = 0;

	/// \brief 往选择集中添加多个OID
	///\param pOID 要添加的多个OID的首地址
	///\param nOIDCount 要添加的OID的数量
	virtual void Add(long long* pOID, unsigned int nOIDCount) = 0;

	/// \brief 清除所有的OID
	virtual void Clear() = 0;

	/// \brief 在选择集中删除多个OID
	///\param pOID 要删除的多个OID的首地址
	///\param nOIDCount 要删除的OID的数量
	virtual void Remove(long long* pOID, unsigned int nOIDCount) = 0;

	/// \brief 在选择集中查询地物
	///\param pFilter 检索过滤条件
	///\return 返回地物游标
	virtual GsFeatureCursorPtr Search (GsQueryFilter* pFilter = 0) = 0;
	
	/// \brief 获得选择集所属的地物类
	///\return 返回地物类
	virtual GsFeatureClass* Target () = 0;

	/// \brief 根据过滤条件并且在当前选择集范围里查询选择集对应的地物类,得到一个新的选择集
	///\param pFilter 检索过滤条件
	///\return 返回新的选择集
	virtual Utility::GsSmarterPtr<GsSelectionSet> Select (GsQueryFilter * pFilter) = 0;

	/// \brief 根据条件将当前 OID 选择集和另一个 OID 选择集进行集合操作，并得到新的 OID 选择集对象
	///\param pSrcSet 需要合并操作的选择集
	///\param eOperation 合并操作类型 
	///\return 返回新的选择集
	virtual Utility::GsSmarterPtr<GsSelectionSet> Combine (GsSelectionSet * pSrcSet, GsSelectionSetOperation eOperation) = 0;

};
/// \brief GsSelectionSetPtr
GS_SMARTER_PTR(GsSelectionSet);

/// \brief 瓦片数据集
/// \code{.cpp}
///  GsTilePtr ptrTile = ptrTileClass->CreateTile();
///  ptrTile->Row(r);
///	 ptrTile->Level(l);
///	 ptrTile->Col(c);
///  ptrTile->Store();
///  GsTileCursorPtr ptrCursor=ptrTileClass->Search();
///  GsTilePtr ptrTile = ptrCursor->Next();
///  do{
///     DoSomeThing(ptrTile);
///	  }while(ptrCursor->Next(ptrTile.p);
/// \endcode
class GS_API GsTileClass:public GsGeoDataRoom
{ 
protected:
	GsTileClass();
public:
	virtual ~GsTileClass();
	
	/// \brief 创建一个新的Tile对象
	/// \return 返回Tile对象的指针
	virtual GsTilePtr CreateTile()=0;

	/// \brief 检索所有的瓦片
	/// \return 返回瓦片游标
	virtual GsTileCursorPtr Search() = 0;

	/// \brief 检索某个级别到某个级别的瓦片
	/// \param nStartLevel 开始的级别
	/// \param nEndLevel 结束的级别
	/// \return 返回瓦片游标
	virtual GsTileCursorPtr Search(int nStartLevel,int nEndLevel) = 0;

	/// \brief 检索某个级别某个行列范围的瓦片
	/// \param nLevel 检索的级别
	/// \param nStartRow 开始行
	/// \param nStartCol 开始列
	/// \param nEndRow 结束行
	/// \param nEndCol 开始列
	/// \return 返回瓦片游标
	virtual GsTileCursorPtr Search(int nLevel,int nStartRow,int nStartCol,int nEndRow,int nEndCol) = 0;

	/// \brief 获取瓦片类的金字塔。
	/// \return 返回金字塔对象指针
	virtual GsPyramid* Pyramid() = 0;

	/// \brief 修改瓦片类的金字塔
	/// \param pPyramid 要修改的金字塔对象
	/// \return 返回修改是否成功
	virtual bool ChangePyramid(GsPyramid* pPyramid) = 0;

	
	
	/// \brief 获取瓦片基本元信息
	///\return 返回原信息对象
	virtual GsTileColumnInfo TileColumnInfo() = 0;

	
	/// \brief 获取所有瓦片的数量
	///\return 返回瓦片总数
	virtual long long TileCount() = 0;

	/// \brief 获取某个级别瓦片的数量
	/// \param nStartLevel 开始级别
	/// \param nEndLevel 结束级别
	///\return 返回该级别瓦片总数
	virtual long long TileCount(int nStartLevel,int nEndLevel) = 0;

	/// \brief 检索某个级别某个行列范围的瓦片
	/// \param nLevel 检索的级别
	/// \param nStartRow 开始行
	/// \param nStartCol 开始列
	/// \param nEndRow 结束行
	/// \param nEndCol 开始列
	///\return 返回该级别瓦片总数
	virtual long long TileCount(int nLevel,int nStartRow,int nStartCol,int nEndRow,int nEndCol) = 0;

	
	/// \brief 根据瓦片行列号检索一个瓦片
	/// \param nLevel 瓦片的级别
	/// \param nRow 瓦片的行
	/// \param nCol 瓦片的列
	///\return 返回该瓦片或者空
	virtual GsTilePtr Tile(int nLevel,int nRow,int nCol);

	/// \brief 根据瓦片行列号检索一个瓦片
	/// \param nLevel 瓦片的级别
	/// \param nRow 瓦片的行
	/// \param nCol 瓦片的列
	/// \param pTile 瓦片
	///\return 返回瓦片是否存在
	virtual bool Tile(int nLevel,int nRow,int nCol,GsTile* pTile);



};
/// \brief GsTileClassPtr
GS_SMARTER_PTR(GsTileClass);

/// \brief 二维表数据集
class GS_API GsRowClass:public GsDataRoom
{
protected:
	GsRowClass();
public:
	~GsRowClass();
	/// \brief 根据查询过滤条件查询
	///\param pFilter 检索过滤条件
	///\return 返回检索结果的行游标对象
	virtual GsRowCursorPtr Search(GsQueryFilter* pFilter = 0) = 0;

	/// \brief 根据Where子句进行查询
	///\param strWhere 要检索的where子句
	///\return 返回检索结果的行游标对象
	virtual GsRowCursorPtr Search(const char* strWhere);

	/// \brief 获取二维表的字段信息
	///\return 字段信息
	virtual GsFields Fields() = 0;

	/// \brief 创建的一个新的属性对象
	///\return 返回新建的属性对象指针
	virtual GsRowPtr  CreateRow() = 0;

	/// \brief 根据输入的oid获取属性对象
	///\return 返回属性对象
	virtual GsRowPtr  Row(long long nOID) = 0;
	
	/// \brief 根据输入的oid获取属性对象
	/// \param nOID 输入的OID
	/// \param pRow 传入属性对象指针，用于接收属性数据，不能为空
	///\return 返回是否成功获取属性对象。
	virtual bool Row(long long nOID,GsRow* pRow) = 0;

	/// \brief 根据查询条件获取属性的数量
	/// \param pFilter 空间或者属性的查询条件
	///\return 返回满足查询条件的属性的数量
	virtual long long RowCount(GsQueryFilter* pFilter = 0) = 0;
};
/// \brief GsRowClassPtr
GS_SMARTER_PTR(GsRowClass);

/// \brief 矢量地物类
/// \details GIS点、线、面、注记类型的矢量数据读写对象
class GS_API GsFeatureClass:public GsGeoDataRoom
{
public:
	virtual ~GsFeatureClass();

	/// \brief 获取地物类的字段信息
	///\return 字段信息
	virtual GsFields Fields() = 0;

	/// \brief 创建的一个新的地物对象
	///\return 返回新建的地物对象指针
	virtual GsFeaturePtr  CreateFeature() = 0;

	/// \brief 根据输入的oid获取地物对象
	///\return 返回地物对象
	virtual GsFeaturePtr  Feature(long long nOID) = 0;
	
	/// \brief 根据输入的oid获取地物对象
	/// \param nOID 输入的OID
	/// \param pFea 传入地物对象指针，用于接收地物数据，不能为空
	///\return 返回是否成功获取地物对象。
	virtual bool Feature(long long nOID,GsFeature* pFea) = 0;
	

	/// \brief 根据查询过滤条件粗查
	///\param pFilter 检索过滤条件可以是GsSpatialQueryFilter或者GsQueryFilter类型
	///\return 返回检索结果的地物游标对象
	virtual GsFeatureCursorPtr Search(GsQueryFilter* pFilter = 0) = 0;
	/// \brief 根据几何空间范围进行粗查
	///\param pGeo 要检索的几何空间范围
	///\return 返回检索结果的地物游标对象
	virtual GsFeatureCursorPtr Search(GsGeometry* pGeo);
	/// \brief 根据Where子句进行粗查
	///\param strWhere 要检索的where子句
	///\return 返回检索结果的地物游标对象
	virtual GsFeatureCursorPtr Search(const char* strWhere);
	/// \brief 根据where子句和几何空间范围进行粗查
	///\param pGeo 要检索的空间范围
	///\param strWhere 要检索的where子句
	///\return 返回检索结果的地物游标对象
	virtual GsFeatureCursorPtr Search(GsGeometry* pGeo,const char* strWhere);
	
	/// \brief 地物类的几何类型
	///\return 返回地物类的几何类型
	virtual GsGeometryType GeometryType() = 0;

	/// \brief 创建空间索引
	///\return 返回创建索引是否成功
	virtual bool CreateSpatialIndex() = 0;
	/// \brief 删除空间索引
	///\return 返回删除索引是否成功
	virtual bool DeleteSpatialIndex() = 0;

	/// \brief 是否存在空间索引
	///\return 返回空间索引是否存在
	virtual bool HasSpatialIndex() = 0;

	/// \brief 根据根据where子句和几何空间范围进行选择
	///\return 返回删除索引是否成功
	virtual GsSelectionSetPtr Select(GsQueryFilter* pFilter = 0) = 0;


	/// \brief 获取基本几何信息
	///\return 返回基本几何信息对象
	virtual GsGeometryColumnInfo GeometryColumnInfo() = 0;

	
	/// \brief 根据查询条件获取地物的数量
	/// \param pFilter 空间或者属性的查询条件
	///\return 返回满足查询条件的地物的数量
	virtual long long FeatureCount(GsQueryFilter* pFilter = 0) = 0;


};
/// \brief GsFeatureClassPtr
GS_SMARTER_PTR(GsFeatureClass);


/// \brief 波段类型
enum GsRasterBandType
{
	/// \brief 未定义波段
	eUndefinedBand=0,
    /// \brief Greyscale灰度索引
	eGrayIndexBand=1,
    /// \brief Paletted 调色板索引波段
	ePaletteIndexBand=2,
    /// \brief RGBA 红色波段
	eRedBand=3,
    /// \brief RGBA 绿色波段
	eGreenBand=4,
	/// \brief RGBA 蓝色波段
	eBlueBand=5,
    /// \brief RGBA 透明波段，0标示透明，255标示不透明
	eAlphaBand=6,
    /// \brief HLS Hue波段
	eHueBand=7,
    /// \brief HLS Saturation波段
	eSaturationBand=8,
    /// \brief HLS Lightness波段
	eLightnessBand=9,
    /// \brief CMYK Cyan波段
	eCyanBand=10,
    /// \brief CMYK Magenta波段
	eMagentaBand=11,
    /// \brief CMYK Yellow波段
	eYellowBand=12,
    /// \brief CMLY Magenta波段
	eBlackBand=13,
    /// \brief YCbCr Y亮度波段
	eYCbCr_YBand=14,
    /// \brief YCbCr Cb蓝色偏移量波段
	eYCbCr_CbBand=15,
    /// \brief YCbCr Cr红色偏移量波段
	eYCbCr_CrBand=16,
};
 
// \brief 支持创建的栅格格式类型
enum GsRasterCreateableFormat
{
	// \brief DOM数据格式
	eNSDTF_DOM,
	// \brief GeoTiff数格式
	eGTiff,
};

// \brief 栅格数据类型
// \details 每个波段具有不同的数据类型
enum GsRasterDataType
{
	// \brief 未知栅格数据类型
	eUnknownRDT= 0,
    // \brief 8位无符号整数
	eByteRDT = 1,
    // \brief 16位无符号整数
	eUInt16RDT = 2,
    // \brief 16位整数
	eInt16RDT = 3,
    // \brief 32位无符号整数
	eUInt32RDT = 4,
    // \brief 32位整数
	eInt32RDT = 5,
    // \brief 32位单精度浮点数
	eFloat32RDT = 6,
    // \brief 64位双精度浮点数
	eFloat64RDT = 7,
    // \brief  16位复合整数
	eCInt16RDT = 8,
    // \brief  32位复合整数
	eCInt32RDT = 9,
    // \brief  32位复合浮点数
	eCFloat32RDT = 10,
    // \brief  64位复合浮点数
	eCFloat64RDT = 11,
};
 


// \brief 栅格颜色类型
enum GsRasterColorType
{
	// \brief  灰度颜色
	eGrayColorType,
	// \brief  RGB颜色，顺序RGBA
	eRGBColorType,
	
	// \brief CMYK颜色，顺序Cyan, Magenta, Yellow , Black
	eCMYKColorType,
	// \brief HLS颜色，顺序Hue, Lightness and Saturation
	eHLSColorType, 
};
// \brief 栅格重采样算法
enum GsRasterResampleAlg
{
	// \brief 最临近点采样
	eNearestNeighbour = 0,
    // \brief 双线性插值，2x2像素范围
	eBilinear = 1,
    // \brief 三次卷积插值，4x4像素范围
	eCubic = 2,
    // \brief 三次样条插值，4x4像素范围
	eCubicSpline = 3,
	// \brief 将对称矩阵通过正交相似变换变成对称三对角矩阵的插值算法，6x6像素范围
	eLanczos = 4,
    // \brief 平均值插值
	eAverage = 5,
    // \brief 模式插值，取采样数据中最常出现的值
	eMode = 6,
	// \brief 高斯模糊插值
	eGauss = 7
};

/// \brief 调色板
/// \details 调色板颜色每2个字节(short)标识一个颜色波段
struct GsColorTable
{
	/// \brief 调色板的颜色类型
	GsRasterColorType ColorType;
	/// \brief 调色板颜色
	GsVector<unsigned long long> ColorTable;
	
	/// \brief 是否是有效的颜色表
	bool IsValid(){return !ColorTable.empty();}

};

///\brief 栅格类基本信息
struct GS_API GsRasterColumnInfo
{
	///\brief X，Y维度范围
	GsBox			XYDomain;
	///\brief 像素宽度
	int				Width;
	///\brief 像素高度
	int				Height;

	///\brief 数据存储块宽度大小
	int				BlockWidth;
	///\brief 数据存储块高度大小
	int				BlockHeight;

	///\brief 波段数据类型
	GsRasterDataType DataType;
	
	///\brief 波段的名称
	GsVector<GsRasterBandType> BandTypes;
	
	///\brief 缺省构造函数
	GsRasterColumnInfo();
	///\brief 拷贝构造函数
	GsRasterColumnInfo(const GsRasterColumnInfo& rhs);
	///\brief 全部构造
	GsRasterColumnInfo(const GsBox &extent,int width,int height,GsRasterDataType dataType,GsRasterBandType* pBand,int nBandCount);
	
	///\brief 是否有效
	bool IsValid() const;

};

/// \brief 栅格波段
class GS_API GsRasterBand:public Utility::GsRefObject
{
public:
	virtual ~GsRasterBand(){}
	/// \brief 波段所属的栅格类
	virtual GsRasterClass* RasterClass() = 0;

	/// \brief 波段的名称、类型或者为用途
	virtual GsRasterBandType BandType() = 0;
	
	/// \brief 最小值
	virtual double Minimum()  = 0;
	/// \brief 最大值
	virtual double Maximum()  = 0;

	/// \brief 无效值
	virtual double NoDataValue() = 0;

	/// \brief 波段的的索引号
	virtual int Index() = 0;

	/// \brief 波段的数据类型
	virtual GsRasterDataType BandDataType() = 0;

	/// \brief 波段的数类型bit位大小
	static int RasterDataTypeBitSize(GsRasterDataType t);

	/// \brief 获取调色板、颜色表
	virtual GsColorTable ColorTable()=0;

};
/// \brief GsRasterBandPtr
GS_SMARTER_PTR(GsRasterBand);

/// \brief 栅格数据块
class GS_API GsRaster:public Utility::GsRefObject
{
protected:
	/// \brief 栅格数据指针
	unsigned char * m_pDataPtr;
	/// \brief 栅格数据的宽度
	int			m_nWidth;
	/// \brief 栅格数据的高度
	int			m_nHeight;
	/// \brief 数据位置在数据集上的X偏移
	int			m_nOffsetX;
	/// \brief 数据位置在数据集上的Y偏移
	int			m_nOffsetY;

	/// \brief 栅格对象所属于的栅格类
	Utility::GsSmarterPtr<GsRasterClass> m_ptrRasterClass;
public:
	GsRaster();
	virtual ~GsRaster();
	
	/// \brief 获取栅格数据指针
	virtual unsigned char * DataPtr();
	/// \brief 设置栅格数据指针
	virtual void DataPtr(unsigned char * pHead);

	/// \brief 根据栅格类属性计算的栅格数据长度
	virtual int DataLength();


	/// \brief 获取栅格数据宽度
	virtual int Width();
	/// \brief 设置栅格数据宽度
	virtual void Width(int n);

	/// \brief 获取栅格数据高度
	virtual int Height();
	/// \brief 设置栅格数据高度
	virtual void Height(int n);

	/// \brief 获取栅格数据X偏移
	virtual int OffsetX();
	/// \brief 设置栅格数据X偏移
	virtual void OffsetX(int n);

	/// \brief 获取栅格数据Y偏移
	virtual int OffsetY();
	/// \brief 设置栅格数据Y偏移
	virtual void OffsetY(int n);

	/// \brief 获取关联的栅格类
	virtual GsRasterClass* RasterClass();
	/// \brief 关联栅格类
	virtual void RasterClass(GsRasterClass* rastercls);
};
/// \brief GsRasterPtr
GS_SMARTER_PTR(GsRaster);

/// \brief 栅格查询游标
class GS_API GsRasterCursor:public Utility::GsRefObject
{
protected:
	GsRasterCursor(){}
public:
	/// \brief 游标的数据宽度
	virtual int Width() = 0;
	/// \brief 游标的数据高度
	virtual int Height() = 0;
	
	/// \brief 游标数据开始数据X偏移
	virtual int X() = 0;
	/// \brief 游标数据开始数据Y偏移
	virtual int Y() = 0;

	/// \brief 重置游标位置
	virtual void Reset() = 0;

	/// \brief 获取下一块栅格对象
	virtual bool Next(GsRaster* raster) = 0;
	
	/// \brief 获取关联的栅格类
	virtual GsRasterClass* RasterClass()=0;
};
/// \brief GsRasterCursorPtr
GS_SMARTER_PTR(GsRasterCursor);

/// \brief 栅格类，存储影像、地形等网格数据
class GS_API GsRasterClass:public GsGeoDataRoom
{
protected:
	GsRasterClass(){}
public:
	virtual ~GsRasterClass(){}
	/// \brief 像素宽度
	virtual int Width()  = 0;
	/// \brief 像素高度
	virtual int Height() = 0;
	
	/// \brief 栅格的编码格式
	virtual Utility::GsString Format() = 0;
	
	/// \brief 获取波段的数量
	virtual int BandCount() = 0;

	/// \brief 根据索引获得波段，索引从0开始
	virtual GsRasterBand* RasterBand(int n) = 0;
	
	/// \brief 计算地理范围在栅格中的像素范围
	virtual Utility::GsRect ExtentToRange(const GsBox& extent);
	/// \brief 计算地理范围对应的像素范围
	virtual GsBox RangeToExtent(const Utility::GsRect& range);

	/// \brief 查询一块原始数据。
	virtual GsRasterCursorPtr Search(const Utility::GsRect&  range) = 0;
	/// \brief 采样一块数据。
	/// \param range 要采样的原始数据
	/// \param s 采样后的大小
	/// \param alg 采样算法
	virtual GsRasterCursorPtr Search(const Utility::GsRect&  range,const Utility::GsSize& s,GsRasterResampleAlg alg) = 0;

	/// \brief 将一块栅格数据写入到数据集中
	virtual bool WriteRaster(GsRaster* pRaster);

	/// \brief 是否存在金字塔
	virtual bool ExistsPyramid() = 0;

	/// \brief 创建金字塔
	/// \param alg 采样算法
	/// \param nLevel 创建金字塔的级别，金字塔级别以1/2,1/4,1/8 ...递增
	virtual bool CreatePyramid(GsRasterResampleAlg alg,int nLevel);
	/// \brief 创建金字塔
	/// \param alg 采样算法
	/// \param nCount
	/// \param pLevels
	virtual bool CreatePyramid(GsRasterResampleAlg alg,int nCount,int* pLevels) = 0;

	/// \brief 元数据的分类名称
	virtual GsVector<Utility::GsString> MetadataDomain();
	
	/// \brief 获取元数据分类下的元数据名称
	virtual GsVector<Utility::GsString> MetadataName(const char* strDomainName);

	/// \brief 获取某个分类下的元数据值
	virtual Utility::GsString MetadataItem(const char* strDomainName,const char* strName);

	/// \brief 设置某个分类下的元数据值
	virtual void MetadataItem(const char* strDomainName,const char* strName,const char* strValue);

	
	/// \brief 获取基本几何信息
	///\return 返回基本几何信息对象
	virtual GsRasterColumnInfo RasterColumnInfo() = 0;


public:
	/// \brief 发生长事务执行的时候进度信息，例如创建金字塔
	Utility::GsDelegate<bool(const char*,double)> OnProgress;

};
/// \brief GsRasterClassPtr
GS_SMARTER_PTR(GsRasterClass);





/// \brief 支持数据集存储、打开的抽象基类
template<class T>
class GS_API GsDataRoomHouse:public T
{
protected:
	GsDataRoomHouse(){}
public:
	virtual ~GsDataRoomHouse(){}

	/// \brief 枚举数据库数据集的名称 
	///\param eDRType 要枚举的数据集的类型
	///\param vecName 要枚举类型数据集的名称
	virtual void DataRoomNames(GsDataRoomType eDRType,GsVector<Utility::GsString>& vecName) = 0;

	/// \brief 打开矢量地物类对象
	///\param strName 矢量地物的名称
	///\return 返回矢量地物类的指针或者NULL
	virtual Utility::GsSmarterPtr<GsFeatureClass> OpenFeatureClass(const char* strName)
	{
		return OpenDataRoom(strName,eFeatureClass);
	}
	/// \brief 创建一个地物类
	///\param strName 地物类的名称
	///\param fs 地物类的字段
	///\param oColumnInfo 地物类的基本信息
	///\param pSR 地物类的空间参考
	///\return 如果名称存在则返回已经存在的地物类，否则返回新建的地物类对象或者为空
	virtual Utility::GsSmarterPtr<GsFeatureClass>  CreateFeatureClass(const char* strName,const GsFields&  fs,const GsGeometryColumnInfo& oColumnInfo,GsSpatialReference* pSR)
	{
		return 0;
	}


	/// \brief 打开瓦片类对象
	///\param strName 瓦片类的名称
	///\return 返回瓦片类的指针或者NULL
	virtual Utility::GsSmarterPtr<GsTileClass> OpenTileClass(const char* strName)
	{
		return OpenDataRoom(strName,eTileClass);
	}
	/// \brief 创建一个瓦片类
	///\param strName 瓦片类的名称
	///\param pSR 瓦片类的空间参考
	///\param pPyramid 瓦片类的金字塔
	///\return 如果名称存在则返回已经存在的瓦片类，否则返回新建的瓦片类对象或者为空
	virtual Utility::GsSmarterPtr<GsTileClass>  CreateTileClass(const char* strName,GsSpatialReference* pSR,GsPyramid* pPyramid,const GsTileColumnInfo& oColumnInfo)
	{
		return 0;
	}

	/// \brief 打开栅格类对象
	///\param strName 栅格类的名称
	///\return 返回栅格类的指针或者NULL
	virtual Utility::GsSmarterPtr<GsRasterClass> OpenRasterClass(const char* strName)
	{
		
		return OpenDataRoom(strName,eRasterClass);
	}
	/// \brief 打开栅格类对象
	///\param strName 栅格类的名称
	///\param oColumnInfo 栅格类基本信息
	///\param pSR 空间参考
	///\param strOptions 参数选项
	///\return 返回栅格类的指针或者NULL
	virtual Utility::GsSmarterPtr<GsRasterClass> CreateRasterClass(const char* strName,GsRasterCreateableFormat eFormat,const GsRasterColumnInfo& oColumnInfo,GsSpatialReference* pSR,const char* strOptions = NULL)
	{
		return 0;
	}
	/// \brief 打开二维表对象
	///\param strName 二维表的名称
	///\return 返回二维表的指针或者NULL
	virtual Utility::GsSmarterPtr<GsRowClass> OpenRowClass(const char* strName)
	{
		return OpenDataRoom(strName,eRowClass);
	}
	/// \brief 创建一个二维表
	///\param strName 二维表的名称
	///\param fs 二维表的字段
	///\return 如果名称存在则返回已经存在的二维表，否则返回新建的二维表对象或者为空
	virtual Utility::GsSmarterPtr<GsRowClass> CreateRowClass(const char* strName, const GsFields&  fs)
	{
		return 0;
	}

	/// \brief 打开已经存在的数据集
	///\param strName 地物类的名称
	///\param eDRType 数据集的类型
	///\return 返回数据集对象
	virtual Utility::GsSmarterPtr<GsDataRoom> OpenDataRoom(const char* strName,GsDataRoomType eDRType)
	{
		switch(eDRType)
		{
		case eFeatureClass:
			return OpenFeatureClass(strName);
		case eTileClass:
			return OpenTileClass(strName);
		case eRasterClass:
			return OpenRasterClass(strName);
		case eRowClass:
			return OpenRowClass(strName);
		case eDataRoomFolder:
			break;
		}
		return 0;
	}
};


/// \brief 数据集目录
class GS_API GsDataRoomFolder:public GsDataRoomHouse<GsDataRoom>
{
protected:
public:
	virtual ~GsDataRoomFolder();
	 
	/// \brief 数据集类型
	///\return 返回数据集对象的类型
	virtual GsDataRoomType Type();
	
	
};

/// \brief GsDataRoomFolderPtr
GS_SMARTER_PTR(GsDataRoomFolder);

/// \brief 空间数据库对象
/// \details 代表一个能够存储GIS空间数据的数据库、文件（数据源）实体。
class GS_API GsGeoDatabase:public GsDataRoomHouse<Utility::GsRefObject>
{
protected:
	/// \brief 数据库的连接信息
	GsConnectProperty m_ConnectProperty; 
	GsGeoDatabase(){}
public:
	virtual ~GsGeoDatabase(); 
	
	/// \brief 数据库连接属性 
	///\return 返回数据库连接属性 
	virtual GsConnectProperty ConnectProperty();

	/// \brief 测试数据库能力
	///\param eCap 数据库能力类型
	///\return 能力类型的值，通常情况下1为支持能力，0为不支持。
	virtual long long TestCapbility(GsGeoDatabaseCapbility eCap);
};
/// \brief GsGeoDatabasePtr
GS_SMARTER_PTR(GsGeoDatabase);
 
/// \brief 空间数据库类厂
/// \details 通过空间数据库类厂创建空间数据库对象实例。
/// \code{.cpp}
/// GsOracleSpatialGeoDatabaseFactory fac;
/// GsGeoDatabasePtr ptrGDB = fac.Open(connProperty);
/// \endcode
class GS_API GsGeoDatabaseFactory:public Utility::GsRefObject
{
protected:
	GsGeoDatabaseFactory(){}
public:
	virtual ~GsGeoDatabaseFactory(); 

	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty) = 0;
};
/// \brief GsGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsGeoDatabaseFactory);
 

 
/// \brief Sqlite数据库工厂
/// \details GeoStar文件格式
class GS_API GsSqliteGeoDatabaseFactory:public GsGeoDatabaseFactory
{
public:
	GsSqliteGeoDatabaseFactory();
	virtual ~GsSqliteGeoDatabaseFactory();

	/// \brief 根据数据库连接信息打开一个空间数据库
	/// \code{.cpp}
	/// GeoStar::Kernel::GsSqliteGeoDatabaseFactory vFac;
	/// GeoStar::Kernel::GsConnectProperty vConn;
	/// vConn.Server = GeoStar::Utility::GsFileSystem::Combine(CurrentFolder().c_str(),strpath)
	/// GeoStar::Kernel::GsGeoDatabasePtr ptrGDB = vFac.Open(vConn);
	/// \endcode
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty);
};
/// \brief GsSqliteGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsSqliteGeoDatabaseFactory);


/// \brief ShapeFile数据库工厂
/// \details ESRI ShapeFile文件格式
class GS_API GsShpGeoDatabaseFactory:public GsGeoDatabaseFactory
{ 
public:
	GsShpGeoDatabaseFactory();
	virtual ~GsShpGeoDatabaseFactory();

	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty); 
};
/// \brief GsShpGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsShpGeoDatabaseFactory);

/// \brief 文件类型数据库工厂
/// \details 包含Sqlite，SHP，GeoPackage以及文件栅格数据的类型识别。
class GS_API GsFileGeoDatabaseFactory:public GsGeoDatabaseFactory
{
public:
	GsFileGeoDatabaseFactory();
	virtual ~GsFileGeoDatabaseFactory();

	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty); 
};
/// \brief GsShpGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsShpGeoDatabaseFactory);



/// \brief OGC GeoPackage标准数据库工厂
/// \details 基于OGC GeoPackage标准文件格式http://www.geopackage.org/
class GS_API GsGeoPackageGeoDatabaseFactory:public GsGeoDatabaseFactory
{ 
public:
	GsGeoPackageGeoDatabaseFactory();
	virtual ~GsGeoPackageGeoDatabaseFactory();

	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty); 
};
/// \brief GsGeoPackageGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsGeoPackageGeoDatabaseFactory);

KERNEL_ENDNS
