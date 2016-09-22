#include "gwVectorsAddon.h"
#include "StdAfx.h"
#include "gwAddonFunction.h"
#include "Dir.h"

gwVectorsAddon::gwVectorsAddon(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;
	
}
gwVectorsAddon::~gwVectorsAddon(void)
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

const char* gwVectorsAddon::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "转换失败";
	string strProvier;
	string strPath;
	string strOutPath;
	bool bIsUTF8 = true;
	bool bIsImport = false;
	bool bIsOutGDB = false;
	std::vector<string> vChields;
	std::vector<string> vChieldFileNames;
	gwAddonFunction::getVectorImportParams(strParameter,strProvier,strPath,strOutPath,bIsImport);
	//int nCount = gwAddonFunction::GetDirectChildren(vChields,vChieldFileNames,m_FileFilter,strPath);
	int nCount = gwDir::GetFiles(vChields,strPath,m_FileFilter,true);
	strProvier = "GPKG";
	if(strOutPath.find_last_of(".") > strOutPath.find_last_of("\\"))
	{

		strOutPath = strOutPath.substr(0,strOutPath.find_last_of("\\"));
	}
	bool bCreateDir = gwAddonFunction::CreateDir(strOutPath);
	
	for(int i = 0;i<nCount;i++)
	{
		string strInPath = vChields[i];
		string strFileName = strInPath.substr(strInPath.find_last_of("\\") + 1,strInPath.length()-strInPath.find_last_of("\\"));

		string strDes = "开始拷贝 "+strFileName;
		if(nProgress != NULL)
			nProgress->OnLog(strDes.data(),GIS::LogLevel::eInfo);
		else
			std::cout<<strDes.data()<<std::endl;

		if(strFileName.find_last_of(".") != -1)
			strFileName = strFileName.replace(strFileName.find_last_of("."),strFileName.length()-strFileName.find_last_of("."),".gpkg");
		else
			continue;
		string strOutPut = "";
		string strFind = strOutPath;
		if(strOutPath.find_last_of("/") == strOutPath.length() - 1||
			strOutPath.find_last_of("\\") == strOutPath.length() - 1)
		{
			strOutPut = strFind.append(strFileName) ;
		}
		else
		{
			strOutPut = strFind.append("\\");
			strOutPut = strFind.append(strFileName) ;
		}



		bool bCopiedDataset = gwAddonFunction::copyDataset(strInPath,strOutPut,strProvier,nProgress);
		if(bCopiedDataset)
		{
			string mes = strFileName + "转换成功";
			if(nProgress != NULL)
				nProgress->OnLog(mes.data(),GIS::eInfo);
			else
				std::cout<<mes<<std::endl;
		}
		else
		{
			string mes = strFileName + "转换失败";
			if(nProgress != NULL)
				nProgress->OnLog(mes.data(),GIS::eError);
			else
				std::cout<<mes<<std::endl;
		}	
	}
	m_strResult = "转换成功";
	return m_strResult.data();
	
}
