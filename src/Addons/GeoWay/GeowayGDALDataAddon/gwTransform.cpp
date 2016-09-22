#include "stdafx.h"
#include "gwTransform.h"
#include "gwImportRaster.h"
#include "gwImportRasters.h"
#include "gwVectorAddon.h"
#include "gwVectorsAddon.h"
#include "gwStandardMetaDataAnalysis.h"
#include "gwStandardMetaDataFactory.h"
/// \brief 导入Geoway db文件地物类
GEOWAYADDON_API GIS::Addon*  ImportGeowayDB(void)
{
	//return new gwImportData("导入Geoway db文件格式");
	return new gwImportData();
}

/// \brief 导出到Geoway db文件地物类
GEOWAYADDON_API GIS::Addon*  ExportGeowayDB(void)
{
	return new gwImportData();
	//return new gwExportData("导出Geoway db文件格式");
}
/// \brief 导入AE fgdb文件地物类
GEOWAYADDON_API GIS::Addon*  ImportFgdb(void)
{
	//return new gwImportData("导入AE Fgdb文件格式");
	return new gwImportData();
}

/// \brief 导出到AE fgdb文件地物类
GEOWAYADDON_API GIS::Addon*  ExportFgdb(void)
{
	//return new gwExportData("导出AE fgdb文件格式");
	return new gwImportData();
}

/// \brief 导入AE mdb文件地物类
GEOWAYADDON_API GIS::Addon*  ImportMdb(void)
{

	GIS::Addon* addon = new gwImportData();
	
	//return new gwImportData("导入AE mdb文件格式");
	return addon;
}

/// \brief 导出到AE mdb文件地物类
//GEOWAYADDON_API GIS::Addon*  ExportMdb(void)
//{
//	//return new gwExportData("导出AE mdb文件格式");
//	return new gwImportData();
//}

/// \brief 导入AE mdb文件地物类
GEOWAYADDON_API GIS::Addon*  ImportShp(void)
{
	return  new gwImportData();
}

/// \brief 导出到AE mdb文件地物类
GEOWAYADDON_API GIS::Addon*  ExportShp(void)
{
	return new gwImportData();
}
//
///// \brief 导入AE mdb文件地物类
//GEOWAYADDON_API GIS::Addon*  ImportIMG(void)
//{
//	return new gwImportRaster("导入IMG文件格式");
//}
//
///// \brief 导出到AE mdb文件地物类
//GEOWAYADDON_API GIS::Addon*  ExportIMG(void)
//{
//	return new gwExportRaster("导出IMG文件格式");
//}
/// \brief 导入AE mdb文件地物类
GEOWAYADDON_API GIS::Addon*  ImportRaster(void)
{
	return new gwImportRaster("导入IMG文件格式");
}

/// \brief 导出到AE mdb文件地物类
GEOWAYADDON_API GIS::Addon*  ExportRaster(void)
{
	return new gwImportRaster("导出IMG文件格式");
}

/// \brief 导出到AE mdb文件地物类
GEOWAYADDON_API GIS::Addon*  ImportMDBS(void)
{
	gwVectorsAddon* mdsAddon = new gwVectorsAddon();
	mdsAddon->m_FileFilter = "*.mdb";
	return mdsAddon;
}

GEOWAYADDON_API GIS::Addon*  ImportGTIFFS(void)
{
	gwImportRasters* Addons = new gwImportRasters();
	Addons->m_FileFilter = "*.tif";
	return Addons;
}
GEOWAYADDON_API GIS::Addon*  ImportIMGS(void)
{
	gwImportRasters* Addons = new gwImportRasters();
	Addons->m_FileFilter = "*.img";
	return Addons;
}
GEOWAYADDON_API GIS::Addon*  ImportGRIDS(void)
{
	gwImportRasters* Addons = new gwImportRasters();
	Addons->m_FileFilter = "w001001.adf";
	return Addons;
}