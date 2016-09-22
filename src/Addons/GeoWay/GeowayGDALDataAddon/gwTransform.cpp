#include "stdafx.h"
#include "gwTransform.h"
#include "gwImportRaster.h"
#include "gwImportRasters.h"
#include "gwVectorAddon.h"
#include "gwVectorsAddon.h"
#include "gwStandardMetaDataAnalysis.h"
#include "gwStandardMetaDataFactory.h"
/// \brief ����Geoway db�ļ�������
GEOWAYADDON_API GIS::Addon*  ImportGeowayDB(void)
{
	//return new gwImportData("����Geoway db�ļ���ʽ");
	return new gwImportData();
}

/// \brief ������Geoway db�ļ�������
GEOWAYADDON_API GIS::Addon*  ExportGeowayDB(void)
{
	return new gwImportData();
	//return new gwExportData("����Geoway db�ļ���ʽ");
}
/// \brief ����AE fgdb�ļ�������
GEOWAYADDON_API GIS::Addon*  ImportFgdb(void)
{
	//return new gwImportData("����AE Fgdb�ļ���ʽ");
	return new gwImportData();
}

/// \brief ������AE fgdb�ļ�������
GEOWAYADDON_API GIS::Addon*  ExportFgdb(void)
{
	//return new gwExportData("����AE fgdb�ļ���ʽ");
	return new gwImportData();
}

/// \brief ����AE mdb�ļ�������
GEOWAYADDON_API GIS::Addon*  ImportMdb(void)
{

	GIS::Addon* addon = new gwImportData();
	
	//return new gwImportData("����AE mdb�ļ���ʽ");
	return addon;
}

/// \brief ������AE mdb�ļ�������
//GEOWAYADDON_API GIS::Addon*  ExportMdb(void)
//{
//	//return new gwExportData("����AE mdb�ļ���ʽ");
//	return new gwImportData();
//}

/// \brief ����AE mdb�ļ�������
GEOWAYADDON_API GIS::Addon*  ImportShp(void)
{
	return  new gwImportData();
}

/// \brief ������AE mdb�ļ�������
GEOWAYADDON_API GIS::Addon*  ExportShp(void)
{
	return new gwImportData();
}
//
///// \brief ����AE mdb�ļ�������
//GEOWAYADDON_API GIS::Addon*  ImportIMG(void)
//{
//	return new gwImportRaster("����IMG�ļ���ʽ");
//}
//
///// \brief ������AE mdb�ļ�������
//GEOWAYADDON_API GIS::Addon*  ExportIMG(void)
//{
//	return new gwExportRaster("����IMG�ļ���ʽ");
//}
/// \brief ����AE mdb�ļ�������
GEOWAYADDON_API GIS::Addon*  ImportRaster(void)
{
	return new gwImportRaster("����IMG�ļ���ʽ");
}

/// \brief ������AE mdb�ļ�������
GEOWAYADDON_API GIS::Addon*  ExportRaster(void)
{
	return new gwImportRaster("����IMG�ļ���ʽ");
}

/// \brief ������AE mdb�ļ�������
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