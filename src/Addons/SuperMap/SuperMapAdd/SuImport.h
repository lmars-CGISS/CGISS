
#pragma once
#include <string>
#include "SuAddBase.h"

//导入GeoPackage
class ImportGPKG:public SuAddonBase
{
public:
	ImportGPKG(void);

	virtual ~ImportGPKG(void); 

	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

class ImportGTIFF:public SuAddonBase
{ 
public:
	ImportGTIFF(void);

	virtual ~ImportGTIFF(void); 

	/// \brief 执行插件
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

	/*/// \brief 插件名称
	virtual const char* Name();
	/// \brief 插件描述
	virtual const char* Description();
	/// \brief 插件类型
	virtual GIS::AddonType Type();*/
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);

	//static void getParams(const char* strParameter,gwString& strProvider,gwString& strPath,gwString& strOutPath);
};