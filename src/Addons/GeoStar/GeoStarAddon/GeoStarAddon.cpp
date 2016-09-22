// GeoStarAddon.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "GeoStarAddon.h"
#include "Import.h" 
#include "Export.h" 
#include "ImportVCT.h" 
#include "ExportVCT.h" 
/// \brief ����VCT��ʽ�ļ�
GEOSTARADDON_API GIS::Addon*  ExportGPKG2VCT(void)
{
	return new ExportVCT();
}
/// \brief ����VCT��ʽ�ļ�
GEOSTARADDON_API GIS::Addon*  ImportVCT2GPKG(void)
{
	return new ImportVCT();
}


/// \brief ����GeoStar�ļ�������
GEOSTARADDON_API GIS::Addon*  ImportGeoStarFCS(void)
{
	return new ImportFCS();
}

/// \brief ������GeoStar�ļ�������
GEOSTARADDON_API GIS::Addon*  ExportGeoStarFCS(void)
{
	return new ExportFCS();
}
/// \brief ����GeoPackage��ʽ�ļ�
GEOSTARADDON_API GIS::Addon*  ImportGPKG2GPKG(void)
{
	return new ImportGPKG();
}




/// \brief ����GeoStar�ļ�������
GEOSTARADDON_API GIS::Addon*  ImportGeoStarDOM(void)
{
	return new ImportDOM();
}

/// \brief ������GeoStar�ļ�������
GEOSTARADDON_API GIS::Addon*  ExportGeoStarDOM(void)
{
	return new ExportDOM();
}


