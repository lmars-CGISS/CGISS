#include "StdAfx.h"
#include "Import.h"


ImportFCS::ImportFCS(void)
{
	m_strName = "����GeoStar FCSʸ�����ݸ�ʽ";
	m_strDescription = "����GeoStar FCSʸ�����ݸ�ʽ";
	
	m_eType = GIS::eImport;
}


ImportFCS::~ImportFCS(void)
{
} 
/// \brief ִ�в��
const char* ImportFCS::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	pProgress->OnLog("׼�����ݵ���",GIS::LogLevel::eInfo);
	pProgress->OnLog("�����������",GIS::LogLevel::eInfo);

	//�������
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		pProgress->OnLog("���������������",GIS::LogLevel::eError);
		return NULL;
	}
	//�����Ŀ¼
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("û���������·��",GIS::LogLevel::eError);
		return NULL;
	}

	//����
	std::string strInputFile = kvp.Value("Path");
	if(strInputFile.empty())
	{
		pProgress->OnLog("û����������·��",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "ת��";
	strLog+=strInputFile;
	strLog+="����׼ʸ������";
	strLog+=strOuputFolder;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);


	//�������
	KVParameter kvpoutput;
	GeoStar::Kernel::GsSqliteGeoDatabaseFactory vSqliteFac;
	GeoStar::Kernel::GsConnectProperty vConn;
	vConn.Server = strInputFile;
	 
	//�����������
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBInput =  vSqliteFac.Open(vConn);
	if(!ptrGDBInput)
	{
		pProgress->OnLog("�����������ļ�ʧ��",GIS::LogLevel::eError);
		return NULL;
	}

	pProgress->OnLog("�����������ļ��ɹ�",GIS::LogLevel::eInfo);

	//�����������
	GeoStar::Kernel::GsGeoPackageGeoDatabaseFactory vGPKGFac;
	vConn.Server = strOuputFolder;
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBOutput =  vGPKGFac.Open(vConn);
	if(!ptrGDBOutput)
	{
		pProgress->OnLog("����������ļ�ʧ��",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("����������ļ��ɹ���",GIS::LogLevel::eInfo);

	//��Դ���ݿ�ת����Ŀ�����ݿ�
	ExecuteTranslate(ptrGDBInput,ptrGDBOutput,pProgress);

 

	//������
	m_strResult = kvpoutput.ToString();
	return m_strResult.c_str();
}



ImportGPKG::ImportGPKG(void)
{
	m_strName = "�����׼ʸ�����ݸ�ʽ";
	m_strDescription = "�����׼ʸ�����ݸ�ʽ";
	
	m_eType = GIS::eImport;
}


ImportGPKG::~ImportGPKG(void)
{

} 
/// \brief ִ�в��
const char* ImportGPKG::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	pProgress->OnLog("׼�����ݵ���",GIS::LogLevel::eInfo);
	pProgress->OnLog("�����������",GIS::LogLevel::eInfo);

	//�������
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		pProgress->OnLog("���������������",GIS::LogLevel::eError);
		return NULL;
	}
	//�����Ŀ¼
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("û���������·��",GIS::LogLevel::eError);
		return NULL;
	}

	//����
	std::string strInputFile = kvp.Value("Path");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("û���������·��",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "ת��";
	strLog+=strInputFile;
	strLog+="����׼ʸ������";
	strLog+=strOuputFolder;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);


	
	//����Ŀ¼
	GeoStar::Utility::GsDir inputFolder(strInputFile.c_str());
	if(!inputFolder.Exists())
	{
		pProgress->OnLog("����·�������ڡ�",GIS::LogLevel::eError);
		return NULL;
	}
	GsVector<GeoStar::Utility::GsFile> vec = inputFolder.Files("*.gpkg");
	GsVector<GeoStar::Utility::GsFile> vec1 = inputFolder.Files("*.gpkgx");
	if(!vec1.empty())
		vec.insert(vec.end(),vec1.begin(),vec1.end());
	
	if(vec.empty())
	{
		pProgress->OnLog("û�п���ת���ı�׼��׼ʸ�����ݡ�",GIS::LogLevel::eError);
		return NULL;
	}

	//�������
	KVParameter kvpoutput;
	GeoStar::Kernel::GsGeoPackageGeoDatabaseFactory vFac;
	GeoStar::Kernel::GsConnectProperty vConn;
	
	vConn.Server = strOuputFolder;
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBOutput =  vFac.Open(vConn);
	if(!ptrGDBOutput)
	{
		pProgress->OnLog("����������ļ�ʧ��",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("�����������ļ��ɹ�",GIS::LogLevel::eInfo);
	
	GsVector<GeoStar::Utility::GsFile>::iterator it = vec.begin();
	for(;it != vec.end();it++)
	{
		vConn.Server = it->FullPath();
		std::string strLog = "ת���ļ�";
		strLog+=it->FullPath();
	
		//�����������
		GeoStar::Kernel::GsGeoDatabasePtr ptrGDBInput =  vFac.Open(vConn);
		if(!ptrGDBInput)
		{
			strLog+="ʧ��";
			pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
			continue;
		}
		
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);
		//��Դ���ݿ�ת����Ŀ�����ݿ�
		ExecuteTranslate(ptrGDBInput,ptrGDBOutput,pProgress);

	}

	//������
	m_strResult = kvpoutput.ToString();
	return m_strResult.c_str();
}

 
 



ImportDOM::ImportDOM(void)
{
	m_strName = "����GeoStar DOMդ�������ļ���ʽ";
	m_strDescription = "����GeoStar DOMդ�������ļ���ʽ";
	m_eType = GIS::eImport;
}


ImportDOM::~ImportDOM(void)
{
} 
/// \brief ִ�в��
const char* ImportDOM::Execute(const char* strParameter,GIS::Progress * pProgress)
{

	pProgress->OnLog("׼�����ݵ���",GIS::LogLevel::eInfo);
	pProgress->OnLog("�����������",GIS::LogLevel::eInfo);

	//�������
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		pProgress->OnLog("���������������",GIS::LogLevel::eError);
		return NULL;
	}

	//�����Ŀ¼
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("û���������·��",GIS::LogLevel::eError);
		return NULL;
	}

	//���롣
	std::string strInputFile = kvp.Value("Path");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("û����������·��",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "ת��";
	strLog+=strInputFile;
	strLog+="����׼դ������";
	strLog+=strOuputFolder;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);


	//�������
	KVParameter kvpoutput;
	GeoStar::Kernel::GsFileGeoDatabaseFactory vFacInput;
	GeoStar::Kernel::GsConnectProperty vConn;
	vConn.Server = strInputFile;
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBInput = vFacInput.Open(vConn);
	if(!ptrGDBInput)
	{
		pProgress->OnLog("����������Դʧ��",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("����������Դ�ɹ�",GIS::LogLevel::eInfo);

	vConn.Server = strOuputFolder;
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBOutput = vFacInput.Open(vConn);
	if(!ptrGDBOutput)
	{
		pProgress->OnLog("���������Դʧ��",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("���������Դ�ɹ�",GIS::LogLevel::eInfo);

	GsVector<GeoStar::Utility::GsString> vecNames;
	ptrGDBInput->DataRoomNames(GeoStar::Kernel::eRasterClass,vecNames);
	GsVector<GeoStar::Utility::GsString>::iterator it =  vecNames.begin();
	for(;it != vecNames.end();it++)
	{
		GeoStar::Kernel::GsRasterClassPtr ptrRasterClass = ptrGDBInput->OpenRasterClass(it->c_str());
		if(!ptrRasterClass)
			continue;

		//ֻת��geotiff�ġ�
		GeoStar::Utility::GsString strFormat = ptrRasterClass->Format();
		if(stricmp(strFormat.c_str(),"GTiff") != 0)
			continue;

		strLog =  "׼��ת��";
		strLog+=*it;
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

		GeoStar::Kernel::GsRasterClassPtr ptrRasterClassOut = ptrGDBOutput->CreateRasterClass(it->c_str(),
			GeoStar::Kernel::GsRasterCreateableFormat::eGTiff,ptrRasterClass->RasterColumnInfo(),
			ptrRasterClass->SpatialReference());

		if(!ptrRasterClassOut)
		{
			strLog =  "�������";
			strLog+=*it;
			strLog+="ʧ��";
			pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
			continue;
		}
		//�ܵ�����������
		__int64 nTotal = ptrRasterClass->Width() * ptrRasterClass->Height();
		__int64 nNow = 0;
		GeoStar::Kernel::GsRasterCursorPtr ptrCursor = ptrRasterClass->Search(
			GeoStar::Utility::GsRect(0,0,ptrRasterClass->Width() , ptrRasterClass->Height()));

		strLog =  "ת��";
		strLog+=*it;
		GeoStar::Kernel::GsRasterPtr ptrRaster = new GeoStar::Kernel::GsRaster();
		while(ptrCursor->Next(ptrRaster))
		{
			//д��Raster
			ptrRasterClassOut->WriteRaster(ptrRaster);
			
			nNow+= ptrRaster->Width() * ptrRaster->Height();
			pProgress->OnProgress(nNow,nTotal,strLog.c_str(),"ת��");
		}

		strLog =  "д��Ԫ����";
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

		//�о����е�Ԫ����������ơ�
		std::vector<GeoStar::Utility::GsString> vecDomain = ptrRasterClass->MetadataDomain();
		std::vector<GeoStar::Utility::GsString>::iterator itDomain = vecDomain.begin();
		for(;itDomain != vecDomain.end();itDomain++)
		{
			//�о�һ������Ԫ��������
			std::vector<GeoStar::Utility::GsString> vecMetaNames = ptrRasterClass->MetadataName(itDomain->c_str());
			std::vector<GeoStar::Utility::GsString>::iterator itName = vecMetaNames.begin();
			for(;itName != vecMetaNames.end();itName++)
			{
				//��ȡһ��Ԫ���ݡ�
				std::string strValue = ptrRasterClass->MetadataItem(itDomain->c_str(),itName->c_str());
				ptrRasterClassOut->MetadataItem(itDomain->c_str(),itName->c_str(),strValue.c_str());
			}
		}

	}
	return NULL;
}