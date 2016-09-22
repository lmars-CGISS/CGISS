// GeoStarAddon.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "GeoStarAddon.h"
#include "Import.h" 
#include "Export.h" 
#include "ImportVCT.h" 
#include "ExportVCT.h" 
/// \brief 导出VCT格式文件
GEOSTARADDON_API GIS::Addon*  ExportGPKG2VCT(void)
{
	return new ExportVCT();
}
/// \brief 导入VCT格式文件
GEOSTARADDON_API GIS::Addon*  ImportVCT2GPKG(void)
{
	return new ImportVCT();
}


/// \brief 导入GeoStar文件地物类
GEOSTARADDON_API GIS::Addon*  ImportGeoStarFCS(void)
{
	return new ImportFCS();
}

/// \brief 导出到GeoStar文件地物类
GEOSTARADDON_API GIS::Addon*  ExportGeoStarFCS(void)
{
	return new ExportFCS();
}
/// \brief 导入GeoPackage格式文件
GEOSTARADDON_API GIS::Addon*  ImportGPKG2GPKG(void)
{
	return new ImportGPKG();
}




/// \brief 导入GeoStar文件地物类
GEOSTARADDON_API GIS::Addon*  ImportGeoStarDOM(void)
{
	return new ImportDOM();
}

/// \brief 导出到GeoStar文件地物类
GEOSTARADDON_API GIS::Addon*  ExportGeoStarDOM(void)
{
	return new ExportDOM();
}


