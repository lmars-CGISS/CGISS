
#pragma once
#include <string>
#include "SuAddBase.h"

//导出到GeoPackage
class ExportGPKG:public SuAddonBase
{
public:
	ExportGPKG(void);

	virtual ~ExportGPKG(void); 

	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

class ExportGTIFF:public SuAddonBase
{ 
public:
	ExportGTIFF(void);

	virtual ~ExportGTIFF(void); 

	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};