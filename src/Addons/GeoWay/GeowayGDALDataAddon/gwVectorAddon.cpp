#include "StdAfx.h"
#include "gwVectorAddon.h"
#include "gwAddonFunction.h"


gwImportData::gwImportData(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;
	//shape支持中文字段与字段值
	//CPLSetConfigOption( "SHAPE_ENCODING", "" );
	//支持中文路径
	//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
}
//gwImportData::gwImportData(const std::string& strDescription)
//{
//	m_strName = strDescription;
//	m_strDescription = strDescription;
//}

gwImportData::~gwImportData(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}

///// \brief 插件名称
//const char* gwImportData::Name()
//{
//	return m_strName.c_str();
//}
///// \brief 插件描述
//const char* gwImportData::Description()
//{
//	return m_strDescription.c_str();
//}
///// \brief 插件类型
//GIS::AddonType gwImportData::Type()
//{
//	return GIS::eImport;
//}

const char* gwImportData::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "转换失败";
	string strProvier;
	string strPath;
	string strOutPath;
	bool bIsUTF8 = true;
	bool bIsImport = false;
	bool bIsOutGDB = false;
	std::vector<string> vChields;
	gwAddonFunction::getVectorImportParams(strParameter,strProvier,strPath,strOutPath,bIsImport);
	
	bool bCopiedDataset = gwAddonFunction::copyDataset(strPath,strOutPath,strProvier,nProgress);
	if(bCopiedDataset)
	{
		m_strResult = "转换成功";
		return m_strResult.data();
	}
	else
		return m_strResult.data();
}
