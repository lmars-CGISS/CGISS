#pragma once

#include "Addon.h" 
#include <string>
#include "GeoStarDLGAddonBase.h"
#include <VCTRW.h>


/// \brief 导入VCT格式
class ImportVCT:public GIS::AddonBase
{
	/// \brief 导入一个文件
	virtual bool ImportOne(GeoStar::Utility::GsFile& file,gpkg::database_ptr& db,GIS::Progress * nProgress);
	/// \brief 导入文件中的一个地物类
	virtual bool ImportOne(VCTParser &parser,VCTFeatureCode& code,gpkg::database_ptr& db,GIS::Progress * nProgress);

public:
	ImportVCT(void);
	~ImportVCT(void);
	
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);

};

