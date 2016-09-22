#include "StdAfx.h"
#include "ExportCSV.h"
#include <atlpath.h>
#include <fstream>

ExportCSV::ExportCSV(void)
{
	m_strName = "����GeoStar CSV�ļ���ʽ";
	m_strDescription = "����GeoStar CSV�ļ���ʽ";
	m_eType = GIS::eExport;
}


ExportCSV::~ExportCSV(void)
{
}
/// \brief ִ�в��
const char* ExportCSV::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	nProgress->OnLog("׼�����ݵ���",GIS::LogLevel::eInfo);
	nProgress->OnLog("1�������������",GIS::LogLevel::eInfo);

	//�������
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		nProgress->OnLog("���������������",GIS::LogLevel::eError);
		return NULL;
	}
	//�����geopackage�ļ���
	std::string strInput = kvp.Value("Input");
	if(strInput.empty())
	{
		nProgress->OnLog("û����������·����",GIS::LogLevel::eError);
		return NULL;
	}

	//���CSV�ļ���
	std::string strOutFile = kvp.Value("Path");
	if(strOutFile.empty())
	{
		nProgress->OnLog("û����������ļ�",GIS::LogLevel::eError);
		return NULL;
	}

	//���������Geopackage��
	GDALAllRegister();
	OGRRegisterAll();
	
	nProgress->OnLog("��ʸ����׼���ݼ�",GIS::LogLevel::eInfo);
	std::string strT = "GPKG:";
	strT+=strInput;
	GDALDataset *poDS = (GDALDataset*) GDALOpenEx( strInput.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL );
	if( poDS == NULL )
	{ 
		nProgress->OnLog("�򿪱�׼ʸ�����ݼ�ʧ��",GIS::LogLevel::eError);
		return NULL;
	}
	for(int i =0;i<poDS->GetLayerCount();i++)
	{
		OGRLayer* pLyr = poDS->GetLayer(i);
		OGRwkbGeometryType eType =  pLyr->GetGeomType();
		int nType = eType % 1000;
		//Ŀǰֻ�Ե����ת����
		if(nType != wkbPoint)
			continue;

		std::string str = "����ͼ��";
		str+=pLyr->GetName();
		nProgress->OnLog(str.c_str(),GIS::LogLevel::eInfo);

		CPath path(CString(strOutFile.c_str()));
		//���������ļ���
		std::string strFileName= pLyr->GetName();
		strFileName+=".csv";
		path.Append(CString(strFileName.c_str()));
		
		//����CSV�ļ�
		std::ofstream csv(CW2A(path.m_strPath),std::ios::out);

		//�ֶνṹ
		OGRFeatureDefn* pDef = pLyr->GetLayerDefn();
		nProgress->OnLog("׼���ֶ�",GIS::LogLevel::eInfo);
		//�����ֶ�oid��x��y'
		csv<<"oid,x,y";
		for(int i =0;i<pDef->GetFieldCount();i++)
		{
			csv<<","<<pDef->GetFieldDefn(i)->GetNameRef();
		}
		csv<<std::endl;	

		nProgress->OnLog("ת������",GIS::LogLevel::eInfo);
		pLyr->ResetReading();
		OGRFeature* pFea = pLyr->GetNextFeature();
		long long nPos = 0,nMax= pLyr->GetFeatureCount();
		while(NULL != pFea)
		{ 
			//���oid
			csv<<pFea->GetFID()<<",";
			OGRGeometry* pGeo = pFea->GetGeometryRef();
			OGRPoint* pPoint = dynamic_cast<OGRPoint*>(pGeo);
			if(NULL != pPoint)
				csv<<pPoint->getX()<<","<<pPoint->getY();
			else
				csv<<"0,0";
			for(int i =0;i<pDef->GetFieldCount();i++)
			{
				switch(pDef->GetFieldDefn(i)->GetType())
				{
				case OFTInteger:
					csv<<","<<pFea->GetFieldAsInteger(i);
					break;
				case OFTReal:
					csv<<","<<pFea->GetFieldAsDouble(i);
					break;
				case OFTString:
					{
						CComBSTR bstr = CA2W(pFea->GetFieldAsString(i),CP_UTF8);
					csv<<","<<CW2A(bstr);
					}
					break;
				case OFTInteger64:
					csv<<","<<pFea->GetFieldAsInteger64(i);
					break;
				default:
					csv<<","<<"[Invalid]";
					break;
				}
			}
			
			csv<<std::endl;	
			//�׳�����
			nProgress->OnProgress(++nPos,nMax,"��������","");

			pFea = pLyr->GetNextFeature();
		}
		
	}
	//�ر����ݼ�
	GDALClose(poDS); 
	return m_strResult.c_str();
}