#include "StdAfx.h"
#include "gwImportRasters.h"
#include "gwAddonFunction.h"
#include "gwStandardMetaDataAnalysis.h"
#include "gwStandardMetaDataFactory.h"
gwImportRasters::gwImportRasters(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;

}
gwImportRasters::gwImportRasters(const std::string& strDescription)
{
	xercesc::XMLPlatformUtils::Initialize();
	m_strName = strDescription;
	m_strDescription = strDescription;
	m_eType = GIS::eImport;
}

gwImportRasters::~gwImportRasters(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}

/// \brief 执行插件
const char* gwImportRasters::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "转换失败";
	string strInFormat;
	string strPath;
	string strOutPath;
	std::vector<string> vChields;
	std::vector<string> vChieldFileNames;
	bool bIsImport = true;
	gwAddonFunction::getRasterImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);
	int nCount = gwDir::GetFiles(vChields,strPath,m_FileFilter,true);
	
	//int nCount = gwAddonFunction::GetDirectChildren(vChields,vChieldFileNames,m_FileFilter,strPath);
	strInFormat = "GTiff";
	if(strOutPath.find_last_of(".") > strOutPath.find_last_of("\\"))
	{
		
		strOutPath = strOutPath.substr(0,strOutPath.find_last_of("\\"));
	}
	
	
		/*if(bCreateDir == false)
			return m_strResult.data();*/

	for(int i = 0;i<nCount;i++)
	{
		string strInPath = vChields[i];
		string strPresentDir = "";
		if(strstr(strInPath.data(),"w001001")!=NULL)
		{
			strInPath = strInPath.substr(0,strInPath.find_last_of("\\"));
			strPresentDir = strInPath;
			strPresentDir = strPresentDir.substr(0,strPresentDir.find_last_of("\\"));
			strPresentDir = strPresentDir.substr(strPresentDir.find_last_of("\\") + 1,strPresentDir.length()-strPresentDir.find_last_of("\\"));

		}
		
		string strFileName = strInPath.substr(strInPath.find_last_of("\\") + 1,strInPath.length()-strInPath.find_last_of("\\"));
		string strDes = "开始拷贝 "+strFileName;
		if(nProgress != NULL)
			nProgress->OnLog(strDes.data(),GIS::LogLevel::eInfo);
		else
			std::cout<<strDes.data()<<std::endl;

		if(strFileName.find_last_of(".") != -1)
			strFileName = strFileName.replace(strFileName.find_last_of("."),strFileName.length()-strFileName.find_last_of("."),".tif");
		else
			strFileName = strFileName +".tif";

		if(strOutPath.find_last_of("/") == strOutPath.length() - 1||
			strOutPath.find_last_of("\\") == strOutPath.length() - 1)
		{
			strPresentDir = strOutPath + strPresentDir + "\\" ;
			/*struct _stat fileStat;
			if ((_stat(strPresentDir.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))
			{
				
			}
			else
			{
				 if(_mkdir( strPresentDir.data() ) != 0)
					 continue;
			}*/
			bool bCreateDir = gwAddonFunction::CreateDir(strPresentDir);
			if(!bCreateDir)
				continue;
			strFileName = strPresentDir  + strFileName;
		}
		else
		{
			strPresentDir = strOutPath + "\\" + strPresentDir + "\\";
			/*struct _stat fileStat;
			if ((_stat(strPresentDir.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))
			{

			}
			else
			{
				if(_mkdir( strPresentDir.data() ) != 0)
					continue;
			}*/
			bool bCreateDir = gwAddonFunction::CreateDir(strPresentDir);
			if(!bCreateDir)
				continue;
			strFileName = strPresentDir  + strFileName;

			
		}
		bool bCopiedRaster = gwAddonFunction::copyRaster(strInPath,strFileName,strInFormat,nProgress);
		if(!bCopiedRaster)
		{
			string mes = strFileName + "转换失败";
			if(nProgress != NULL)
				nProgress->OnLog(mes.data(),GIS::eError);
			else
				std::cout<<mes<<std::endl;
		}
		else
		{
			string mes = strFileName + "转换成功";
			if(nProgress != NULL)
				nProgress->OnLog(mes.data(),GIS::eInfo);
			else
				std::cout<<mes<<std::endl;
		}
	}
	m_strResult = "读取成功";
	if(nProgress != NULL)
		nProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return m_strResult.c_str();
}
