#ifndef _IMPORT_H_
#define _IMPORT_H_
#pragma once
#include "stdafx.h"
#include "Addon.h" 
class  gwImportData:public GIS::AddonBase
{
	/*std::string m_strName,m_strDescription;
	std::string m_strResult;*/
public:
	gwImportData(void);
	//gwImportData(const std::string& strDescription);
	virtual ~gwImportData(void);
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


