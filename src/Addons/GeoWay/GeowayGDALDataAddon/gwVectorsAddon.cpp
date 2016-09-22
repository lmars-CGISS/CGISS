#include "gwVectorsAddon.h"
#include "StdAfx.h"
#include "gwAddonFunction.h"
#include "Dir.h"

gwVectorsAddon::gwVectorsAddon(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "�����ⲿ�ļ���ʽ";
	m_strDescription = "�����ⲿ�ļ���ʽ";
	m_eType = GIS::eImport;
	
}
gwVectorsAddon::~gwVectorsAddon(void)
{
	xercesc::XMLPlatformUtils::Terminate();
}

///// \brief �������
//const char* gwImportData::Name()
//{
//	return m_strName.c_str();
//}
///// \brief �������
//const char* gwImportData::Description()
//{
//	return m_strDescription.c_str();
//}
///// \brief �������
//GIS::AddonType gwImportData::Type()
//{
//	return GIS::eImport;
//}

const char* gwVectorsAddon::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "ת��ʧ��";
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

		string strDes = "��ʼ���� "+strFileName;
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
			string mes = strFileName + "ת���ɹ�";
			if(nProgress != NULL)
				nProgress->OnLog(mes.data(),GIS::eInfo);
			else
				std::cout<<mes<<std::endl;
		}
		else
		{
			string mes = strFileName + "ת��ʧ��";
			if(nProgress != NULL)
				nProgress->OnLog(mes.data(),GIS::eError);
			else
				std::cout<<mes<<std::endl;
		}	
	}
	m_strResult = "ת���ɹ�";
	return m_strResult.data();
	
}
