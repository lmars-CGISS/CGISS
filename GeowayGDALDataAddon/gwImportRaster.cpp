#include "StdAfx.h"
#include "gwImportRaster.h"
#include "gwAddonFunction.h"
#include "gwStandardMetaDataAnalysis.h"
#include "gwStandardMetaDataFactory.h"
gwImportRaster::gwImportRaster(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "�����ⲿ�ļ���ʽ";
	m_strDescription = "�����ⲿ�ļ���ʽ";
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

///// \brief �������
//const char* gwImportRaster::Name()
//{
//	return m_strName.c_str();
//}
///// \brief �������
//const char* gwImportRaster::Description()
//{
//	return m_strDescription.c_str();
//}
///// \brief �������
//GIS::AddonType gwImportRaster::Type()
//{
//	return GIS::eImport;
//}
//����XML�ַ����Ĳ���

/// \brief ִ�в��
const char* gwImportRaster::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "ת��ʧ��";
	string strInFormat;
	string strPath;
	string strOutPath;
	
	bool bIsImport = true;
	gwAddonFunction::getRasterImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);
	bool bCopiedRaster = gwAddonFunction::copyRaster(strPath,strOutPath,strInFormat,nProgress);
	if(!bCopiedRaster)
	{
		if(nProgress != NULL)
			nProgress->OnLog("ת��ʧ��",GIS::eError);
		else
			std::cout<<"ת��ʧ��"<<std::endl;
		return m_strResult.data();
	}
	m_strResult = "��ȡ�ɹ�";
	if(nProgress != NULL)
		nProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return m_strResult.c_str();
}
