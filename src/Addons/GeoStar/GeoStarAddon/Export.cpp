#include "StdAfx.h"
#include "Export.h"


ExportFCS::ExportFCS(void)
{
	m_strName = "����GeoStar FCSʸ�������ļ���ʽ";
	m_strDescription = "����GeoStar FCSʸ�������ļ���ʽ";
	
	m_eType = GIS::eExport;
}


ExportFCS::~ExportFCS(void)
{
} 
/// \brief ִ�в��
const char* ExportFCS::Execute(const char* strParameter,GIS::Progress * pProgress)
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
	//�����geopackage�ļ���
	std::string strInput = kvp.Value("Input");
	if(strInput.empty())
	{
		pProgress->OnLog("û����������·����",GIS::LogLevel::eError);
		return NULL;
	}

	//���FCS�ļ���
	std::string strOutFile = kvp.Value("Path");
	if(strOutFile.empty())
	{
		pProgress->OnLog("û����������ļ�",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "ת����׼ʸ������ΪGeoStar FCSʸ�����ݴ�";
	strLog+=strInput;
	strLog+="��";
	strLog+=strOutFile;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

	GeoStar::Kernel::GsGeoPackageGeoDatabaseFactory fac;
	GeoStar::Kernel::GsConnectProperty conn;
	conn.Server = strInput;
	//��GeoPackage����Դ
	GeoStar::Kernel::GsGeoDatabasePtr ptrGPKDB = fac.Open(conn);
	if(!ptrGPKDB)
	{
		pProgress->OnLog("�����������ļ�ʧ�ܡ�",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("�����������ļ��ɹ���",GIS::LogLevel::eInfo);

	GeoStar::Kernel::GsSqliteGeoDatabaseFactory facSqlite;
	conn.Server = strOutFile;
	//��Sqlite����Դ
	GeoStar::Kernel::GsGeoDatabasePtr ptrFCSDB = facSqlite.Open(conn);
	if(!ptrFCSDB)
	{
		pProgress->OnLog("����������ļ�ʧ�ܡ�",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("����������ļ��ɹ���",GIS::LogLevel::eInfo);

	
	//��Դ���ݿ�ת����Ŀ�����ݿ�
	ExecuteTranslate(ptrGPKDB,ptrFCSDB,pProgress);
	 
	return m_strResult.c_str(); 
}





ExportDOM::ExportDOM(void)
{
	m_strName = "����GeoStar DOMդ�������ļ���ʽ";
	m_strDescription = "����GeoStar DOMդ�������ļ���ʽ";
	m_eType = GIS::eImport;
}


ExportDOM::~ExportDOM(void)
{
} 
/// \brief ִ�в��
const char* ExportDOM::Execute(const char* strParameter,GIS::Progress * pProgress)
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
	std::string strOuputFolder = kvp.Value("Path");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("û���������·��",GIS::LogLevel::eError);
		return NULL;
	}

	//���롣
	std::string strInputFile = kvp.Value("Input");
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
