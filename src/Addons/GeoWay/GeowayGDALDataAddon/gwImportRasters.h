#ifndef _GW_IMPORT_RASTERS_H_
#define _GW_IMPORT_RASTERS_H_
#pragma once
#include "stdafx.h"
#include "Addon.h" 
#include "Dir.h"
class  gwImportRasters:public GIS::AddonBase
{
	/*std::string m_strName,m_strDescription;
	std::string m_strResult;*/
public:
	string m_FileFilter;
	gwImportRasters(void);
	gwImportRasters(const std::string& strDescription);
	virtual ~gwImportRasters(void);

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