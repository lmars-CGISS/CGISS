#pragma once
#include "Addon.h" 
#include <string>
#include "GeoStarDLGAddonBase.h"
#include <VCTRW.h>

class ExportVCT:public GIS::AddonBase
{
	//输出到VCT文件中。
	void WriteTo(VCTWriter& w,gpkg::content& content,gpkg::database_ptr db,GIS::Progress * nProgress,VCTID& id);

public:
	ExportVCT(void);
	virtual ~ExportVCT(void);
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

