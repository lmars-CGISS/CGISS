#include "StdAfx.h"
#include "gwVectorAddon.h"
#include "gwAddonFunction.h"


gwImportData::gwImportData(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "�����ⲿ�ļ���ʽ";
	m_strDescription = "�����ⲿ�ļ���ʽ";
	m_eType = GIS::eImport;
	//shape֧�������ֶ����ֶ�ֵ
	//CPLSetConfigOption( "SHAPE_ENCODING", "" );
	//֧������·��
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

const char* gwImportData::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	m_strResult = "ת��ʧ��";
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
		m_strResult = "ת���ɹ�";
		return m_strResult.data();
	}
	else
		return m_strResult.data();
}
