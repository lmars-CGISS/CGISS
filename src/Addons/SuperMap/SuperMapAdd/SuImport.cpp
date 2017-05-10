
#include "StdAfx.h"
#include "SuImport.h"
#include "UGDir.h"

ImportGPKG::ImportGPKG(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;
}

ImportGPKG::~ImportGPKG(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}


/// \brief 执行插件
const char* ImportGPKG::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	m_strResult = "转换失败";
	string strInFormat;
	string strPath;
	string strOutPath;

	bool bIsImport = true;
	SuAddonBase::getVectorImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);

	UGString strFileTemp;
	UGString strInpath = strFileTemp.FromStd(strPath);
	UGString strUDB = strFileTemp.FromStd(strOutPath);//_U("");

	//!!从UDB中开始转出
	UGDataSource *pDs = OpenDSNew(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		pProgress->OnLog("打开输出数据文件失败",GIS::LogLevel::eError);
		return 0;
	}
	pProgress->OnLog("打开输出数据文件成功",GIS::LogLevel::eInfo);

	UGbool bImport = Import(pDs, strInpath, UGFileType::GeoPackage);

	delete pDs;
	pDs = NULL;

	if(!bImport)
	{
		if(pProgress != NULL)
			pProgress->OnLog("转换失败",GIS::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return m_strResult.data();
	}
	m_strResult = "读取成功";
	if(pProgress != NULL)
		pProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;
	
	return m_strResult.c_str();
}



ImportGTIFF::ImportGTIFF(void)
{

	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;
}


ImportGTIFF::~ImportGTIFF(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}

/// \brief 执行插件
const char* ImportGTIFF::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	m_strResult = "转换失败";
	string strInFormat;
	string strPath;
	string strOutPath;

	bool bIsImport = true;
	SuAddonBase::getRasterImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);

	UGString strFileTemp;
	UGString strInpath = strFileTemp.FromStd(strPath);
	UGString strUDB = strFileTemp.FromStd(strOutPath);//_U("");

	//!!从UDB中开始转出
	UGDataSource *pDs = OpenDSNew(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		pProgress->OnLog("打开输出数据文件失败",GIS::LogLevel::eError);
		return 0;
	}
	pProgress->OnLog("打开输出数据文件成功",GIS::LogLevel::eInfo);

	UGbool bImport = Import(pDs, strInpath, UGFileType::GTiff);

	delete pDs;
	pDs = NULL;

	if(!bImport)
	{
		if(pProgress != NULL)
			pProgress->OnLog("转换失败",GIS::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return m_strResult.data();
	}
	m_strResult = "读取成功";
	if(pProgress != NULL)
		pProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return m_strResult.c_str();
}


ImportRasters::ImportRasters(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;

}
ImportRasters::ImportRasters(const std::string& strDescription)
{
	xercesc::XMLPlatformUtils::Initialize();
	m_strName = strDescription;
	m_strDescription = strDescription;
	m_eType = GIS::eImport;
}

ImportRasters::~ImportRasters(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}

/// \brief 执行插件
const char* ImportRasters::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "转换失败";
	string strInFormat;
	string strPath;
	string strOutPath;
	std::vector<string> vChields;
	std::vector<string> vChieldFileNames;
	bool bIsImport = true;
	SuAddonBase::getRasterImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);
	int nCount = UGDir::GetFiles(vChields,strPath,m_FileFilter,true);
	
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
			bool bCreateDir = SuAddonBase::CreateDir(strPresentDir);
			if(!bCreateDir)
				continue;
			strFileName = strPresentDir  + strFileName;
		}
		else
		{
			strPresentDir = strOutPath + "\\" + strPresentDir + "\\";
			
			bool bCreateDir = SuAddonBase::CreateDir(strPresentDir);
			if(!bCreateDir)
				continue;
			strFileName = strPresentDir  + strFileName;

			
		}
		bool bCopiedRaster = SuAddonBase::ImportRaster(strInPath,strFileName,strInFormat,nProgress);
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