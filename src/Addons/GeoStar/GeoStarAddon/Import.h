#pragma once
#include <string>
#include "GeoStarDLGAddonBase.h"
class ImportFCS:public GeoStarDLGAddonBase
{ 
public:
	ImportFCS(void);
	virtual ~ImportFCS(void); 
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

//导入GeoPackage
class ImportGPKG:public GeoStarDLGAddonBase
{
public:
	ImportGPKG(void);
	virtual ~ImportGPKG(void); 
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};


//导如DOM
class ImportDOM:public GIS::AddonBase
{
public:
	ImportDOM(void);
	virtual ~ImportDOM(void); 
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

