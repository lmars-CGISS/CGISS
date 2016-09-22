#include "StdAfx.h"
#include "gwImportRaster.h"
#include "gwAddonFunction.h"
#include "gwStandardMetaDataAnalysis.h"
#include "gwStandardMetaDataFactory.h"
gwImportRaster::gwImportRaster(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;

}
gwImportRaster::gwImportRaster(const std::string& strDescription)
{
	xercesc::XMLPlatformUtils::Initialize();
	m_strName = strDescription;
	m_strDescription = strDescription;
	m_eType = GIS::eImport;
}

gwImportRaster::~gwImportRaster(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}

///// \brief 插件名称
//const char* gwImportRaster::Name()
//{
//	return m_strName.c_str();
//}
///// \brief 插件描述
//const char* gwImportRaster::Description()
//{
//	return m_strDescription.c_str();
//}
///// \brief 插件类型
//GIS::AddonType gwImportRaster::Type()
//{
//	return GIS::eImport;
//}
//解析XML字符串的参数

/// \brief 执行插件
const char* gwImportRaster::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "转换失败";
	string strInFormat;
	string strPath;
	string strOutPath;
	
	bool bIsImport = true;
	gwAddonFunction::getRasterImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);
	bool bCopiedRaster = gwAddonFunction::copyRaster(strPath,strOutPath,strInFormat,nProgress);
	if(!bCopiedRaster)
	{
		if(nProgress != NULL)
			nProgress->OnLog("转换失败",GIS::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return m_strResult.data();
	}
	m_strResult = "读取成功";
	if(nProgress != NULL)
		nProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return m_strResult.c_str();
}
