#ifndef _GW_IMPORT_RASTER_H_
#define _GW_IMPORT_RASTER_H_
#pragma once
#include "stdafx.h"
#include "Addon.h" 
class  gwImportRaster:public GIS::AddonBase
{
	/*std::string m_strName,m_strDescription;
	std::string m_strResult;*/
public:
	gwImportRaster(void);
	gwImportRaster(const std::string& strDescription);
	virtual ~gwImportRaster(void);

	/*/// \brief �������
	virtual const char* Name();
	/// \brief �������
	virtual const char* Description();
	/// \brief �������
	virtual GIS::AddonType Type();*/
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);

	//static void getParams(const char* strParameter,gwString& strProvider,gwString& strPath,gwString& strOutPath);
};
#endif