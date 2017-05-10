
#include "StdAfx.h"
#include "SuImport.h"
#include "UGDir.h"

ImportGPKG::ImportGPKG(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "�����ⲿ�ļ���ʽ";
	m_strDescription = "�����ⲿ�ļ���ʽ";
	m_eType = GIS::eImport;
}

ImportGPKG::~ImportGPKG(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}


/// \brief ִ�в��
const char* ImportGPKG::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	m_strResult = "ת��ʧ��";
	string strInFormat;
	string strPath;
	string strOutPath;

	bool bIsImport = true;
	SuAddonBase::getVectorImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);

	UGString strFileTemp;
	UGString strInpath = strFileTemp.FromStd(strPath);
	UGString strUDB = strFileTemp.FromStd(strOutPath);//_U("");

	//!!��UDB�п�ʼת��
	UGDataSource *pDs = OpenDSNew(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		pProgress->OnLog("����������ļ�ʧ��",GIS::LogLevel::eError);
		return 0;
	}
	pProgress->OnLog("����������ļ��ɹ�",GIS::LogLevel::eInfo);

	UGbool bImport = Import(pDs, strInpath, UGFileType::GeoPackage);

	delete pDs;
	pDs = NULL;

	if(!bImport)
	{
		if(pProgress != NULL)
			pProgress->OnLog("ת��ʧ��",GIS::eError);
		else
			std::cout<<"ת��ʧ��"<<std::endl;
		return m_strResult.data();
	}
	m_strResult = "��ȡ�ɹ�";
	if(pProgress != NULL)
		pProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;
	
	return m_strResult.c_str();
}



ImportGTIFF::ImportGTIFF(void)
{

	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "�����ⲿ�ļ���ʽ";
	m_strDescription = "�����ⲿ�ļ���ʽ";
	m_eType = GIS::eImport;
}


ImportGTIFF::~ImportGTIFF(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}

/// \brief ִ�в��
const char* ImportGTIFF::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	m_strResult = "ת��ʧ��";
	string strInFormat;
	string strPath;
	string strOutPath;

	bool bIsImport = true;
	SuAddonBase::getRasterImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);

	UGString strFileTemp;
	UGString strInpath = strFileTemp.FromStd(strPath);
	UGString strUDB = strFileTemp.FromStd(strOutPath);//_U("");

	//!!��UDB�п�ʼת��
	UGDataSource *pDs = OpenDSNew(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		pProgress->OnLog("����������ļ�ʧ��",GIS::LogLevel::eError);
		return 0;
	}
	pProgress->OnLog("����������ļ��ɹ�",GIS::LogLevel::eInfo);

	UGbool bImport = Import(pDs, strInpath, UGFileType::GTiff);

	delete pDs;
	pDs = NULL;

	if(!bImport)
	{
		if(pProgress != NULL)
			pProgress->OnLog("ת��ʧ��",GIS::eError);
		else
			std::cout<<"ת��ʧ��"<<std::endl;
		return m_strResult.data();
	}
	m_strResult = "��ȡ�ɹ�";
	if(pProgress != NULL)
		pProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return m_strResult.c_str();
}


ImportRasters::ImportRasters(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "�����ⲿ�ļ���ʽ";
	m_strDescription = "�����ⲿ�ļ���ʽ";
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

/// \brief ִ�в��
const char* ImportRasters::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "ת��ʧ��";
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
		string strDes = "��ʼ���� "+strFileName;
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
			string mes = strFileName + "ת��ʧ��";
			if(nProgress != NULL)
				nProgress->OnLog(mes.data(),GIS::eError);
			else
				std::cout<<mes<<std::endl;
		}
		else
		{
			string mes = strFileName + "ת���ɹ�";
			if(nProgress != NULL)
				nProgress->OnLog(mes.data(),GIS::eInfo);
			else
				std::cout<<mes<<std::endl;
		}
	}
	m_strResult = "��ȡ�ɹ�";
	if(nProgress != NULL)
		nProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return m_strResult.c_str();
}