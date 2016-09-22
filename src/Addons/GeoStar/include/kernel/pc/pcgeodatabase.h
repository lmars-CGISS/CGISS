#pragma once 
#include <geodatabase.h> 
#include "../../utility/preconfig.h"

KERNEL_NS 
	 
/// \brief OracleSptial数据库类厂
class GS_API GsOracleSpatialGeoDatabaseFactory:public GsGeoDatabaseFactory
{
	Utility::GsRefObject*  m_ptrInnterHandle; 
public:
	GsOracleSpatialGeoDatabaseFactory();
	virtual ~GsOracleSpatialGeoDatabaseFactory();

	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty);

	/// \brief 初始化GeoStar5的元表
	///\param connProperty Oracle数据库中GeoStar用户连接信息
	///\return 初始化是否成功。
	virtual bool InitializeGeoStar5Metatable(const GsConnectProperty& connProperty);

	/// \brief 判断一个空间数据库是否是GeoStar5的数据库
	///\param connProperty Oracle数据库中
	///\return 返回数据库连接的数据库是否是geostar5版本的数据库。
	virtual bool IsGeoStar5SpatialDatabase(const GsConnectProperty& connProperty);

};

/// \brief GsOracleSpatialGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsOracleSpatialGeoDatabaseFactory);
 

/// \brief MySql数据库类厂
class GS_API GsMySqlGeoDatabaseFactory:public GsGeoDatabaseFactory
{
public:
	GsMySqlGeoDatabaseFactory();
	virtual ~GsMySqlGeoDatabaseFactory();

	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty);
};

/// \brief GsMySqlGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsMySqlGeoDatabaseFactory);
 


/// \brief PostGIS数据库类厂
class GS_API GsPostGISGeoDatabaseFactory:public GsGeoDatabaseFactory
{
public:
	GsPostGISGeoDatabaseFactory();
	virtual ~GsPostGISGeoDatabaseFactory();

	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty);
};

/// \brief GsPostGISGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsPostGISGeoDatabaseFactory);
 


/// \brief 达梦数据库类厂
class GS_API GsDamengGeoDatabaseFactory:public GsGeoDatabaseFactory
{
	Utility::GsRefObject*  m_ptrInnterHandle;
public:
	GsDamengGeoDatabaseFactory();
	virtual ~GsDamengGeoDatabaseFactory();

	/// \brief 根据数据库连接信息打开一个空间数据库
	///\param connProperty 数据库连接信息
	///\return 返回空间数据库对象实例或者空
	virtual GsGeoDatabasePtr Open(const GsConnectProperty& connProperty);
};

/// \brief GsDamengGeoDatabaseFactoryPtr
GS_SMARTER_PTR(GsDamengGeoDatabaseFactory);
 

KERNEL_ENDNS
