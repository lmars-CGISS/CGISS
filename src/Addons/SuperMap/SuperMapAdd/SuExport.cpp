
#include "StdAfx.h"
#include "SuExport.h"

ExportGPKG::ExportGPKG(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "�����ⲿ�ļ���ʽ";
	m_strDescription = "�����ⲿ�ļ���ʽ";
	m_eType = GIS::eImport;
}


ExportGPKG::~ExportGPKG(void)
{

	xercesc::XMLPlatformUtils::Terminate();

}

/// \brief ִ�в��
const char* ExportGPKG::Execute(const char* strParameter,GIS::Progress * pProgress)
{

	m_strResult = "ת��ʧ��";
	string strInFormat;
	string strPath;
	string strGPKGPath;

	bool bIsImport = false;
	SuAddonBase::getVectorImportParams(strParameter,strInFormat,strPath,strGPKGPath,bIsImport);


	UGString strFileTemp;
	UGString strUDB = strFileTemp.FromStd(strPath);//_U("");

	OGRRegisterAll();



	//!!��UDB�п�ʼת��

	UGDataSource *pDs = OpenDS(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		pProgress->OnLog("����������ļ�ʧ��",GIS::LogLevel::eError);
		return 0;
	}
	pProgress->OnLog("����������ļ��ɹ�",GIS::LogLevel::eInfo);

	UGbool bExport = false;

	int nCount = pDs->GetDatasetCount();
	UGString strTemp;
	UGString strOutFilePath = strTemp.FromStd(strGPKGPath);

	UGString strPathFile = UGFile::GetDir(strOutFilePath);

	for (int i=0; i<nCount;i++)
	{
		UGDataset* pDataSet = pDs->GetDataset(i);

		if (pDataSet->IsVector())
		{
			
			UGString strDtName = pDataSet->GetName();
			UGString strShpFile= strPathFile + strDtName;	
			string str = ".shp";
			strTemp = strTemp.FromStd(str);
			strShpFile+= strTemp;

			bExport = Export(pDs, strShpFile, UGFileType::Shape, strDtName);
			//////////////////////////////////////////////////////////////////////////
			string strOutPath = strShpFile.ToStd(str);
			string strProvier = "GPKG";
			bool bImport= copyDataset(strOutPath,strGPKGPath,strProvier,pProgress);

			// ������ڣ�ɾ��֮��ȷ������ת���ɹ�
			if(UGFile::IsExist(strShpFile))
			{
				UGFile::Delete(strShpFile);
				UGString uPathFile = UGFile::GetDir(strShpFile);
				uPathFile +=UGFile::GetTitle(strShpFile);
				UGString dbfFile = uPathFile+ _U(".dbf");
				UGString prjFile = uPathFile+ _U(".prj");
				UGString shxFile = uPathFile+ _U(".shx");
				UGFile::Delete(dbfFile);
				UGFile::Delete(prjFile);
				UGFile::Delete(shxFile);
			}
			//
		}
		else
		{
			continue;
		}
	}

	delete pDs;
	pDs = NULL;

	if(!bExport)
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



ExportGTIFF::ExportGTIFF(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "�����ⲿ�ļ���ʽ";
	m_strDescription = "�����ⲿ�ļ���ʽ";
	m_eType = GIS::eImport;
}


ExportGTIFF::~ExportGTIFF(void)
{
	xercesc::XMLPlatformUtils::Terminate();

}


/// \brief ִ�в��
const char* ExportGTIFF::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	m_strResult = "ת��ʧ��";
	string strInFormat;
	string strPath;
	string strOutPath;

	bool bIsImport = false;
	SuAddonBase::getRasterImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);


	UGString strFileTemp;
	UGString strUDB = strFileTemp.FromStd(strPath);//_U("");


	//!!��UDB�п�ʼת��

	UGDataSource *pDs = OpenDS(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		pProgress->OnLog("����������ļ�ʧ��",GIS::LogLevel::eError);
		return 0;
	}
	pProgress->OnLog("����������ļ��ɹ�",GIS::LogLevel::eInfo);

	UGbool bExport = false;

	int nCount = pDs->GetDatasetCount();
	UGString strTemp;
	UGString strOutFilePath = strTemp.FromStd(strOutPath);
	int nnCount = 0;
	for (int i=0; i<nCount;i++)
	{
		UGDataset* pDataSet = pDs->GetDataset(i);

		if (pDataSet->IsRaster())
		{
			if (nnCount>0)
			{//����ֻת����һ��դ�����ݼ�������
				continue;
			}
			nnCount++;
			UGString strDtName = pDataSet->GetName();
			strOutFilePath += strDtName;	
			string str = ".tif";
			strTemp = strTemp.FromStd(str);
			strOutFilePath+= strTemp;

			bExport = ExportRaster(pDs, strOutFilePath, UGFileType::GTiff, strDtName);

		}
		else
		{
			continue;
		}
	}

	string strLog ;
	if (!bExport)
	{
		strLog+="ʧ��";
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
	}
	else
	{
		strLog+="�ɹ���";
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

	}
	delete pDs;
	pDs = NULL;

	if(!bExport)
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
