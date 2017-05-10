
#pragma once
#include <string>
#include "SuAddBase.h"

//����GeoPackage
class ImportGPKG:public SuAddonBase
{
public:
	ImportGPKG(void);

	virtual ~ImportGPKG(void); 

	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

class ImportGTIFF:public SuAddonBase
{ 
public:
	ImportGTIFF(void);

	virtual ~ImportGTIFF(void); 

	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

class  ImportRasters:public GIS::AddonBase
{
	/*std::string m_strName,m_strDescription;
	std::string m_strResult;*/
public:
	string m_FileFilter;
	ImportRasters(void);
	ImportRasters(const std::string& strDescription);
	virtual ~ImportRasters(void);

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