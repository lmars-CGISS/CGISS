#pragma once
#include "Addon.h" 
#include <string>
#include "GeoStarDLGAddonBase.h"
class ExportFCS:public GeoStarDLGAddonBase
{ 
public:
	ExportFCS(void);
	virtual ~ExportFCS(void);
	 
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};



//导如DOM
class ExportDOM:public GIS::AddonBase
{
public:
	ExportDOM(void);
	virtual ~ExportDOM(void); 
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};