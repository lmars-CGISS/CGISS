#ifndef _GW_VECTORS_ADDON_H
#define _GW_VECTORS_ADDON_H
#pragma once
#include "stdafx.h"
#include "Addon.h" 
class  gwVectorsAddon:public GIS::AddonBase
{
	/*std::string m_strName,m_strDescription;
	std::string m_strResult;*/
public:
	string m_FileFilter;
	gwVectorsAddon(void);
	//gwImportData(const std::string& strDescription);
	virtual ~gwVectorsAddon(void);
	///// \brief �������
	//virtual const char* Name();
	///// \brief �������
	//virtual const char* Description();
	///// \brief �������
	//virtual GIS::AddonType Type();
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);

	//static void getParams(const char* strParameter,gwString& strProvider,gwString& strPath,gwString& strOutPath);
};
#endif


