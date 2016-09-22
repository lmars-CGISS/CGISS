#include "StdAfx.h"
#include "ImportCSV.h"
#include <atlpath.h>
#include <fstream>
#include <string>
#include <vector>

/// \brief ���ַ����ָ�Ϊ�����Ӵ�
std::vector<std::string> Split(const char* ss,const char* strSep)
{
	if(NULL == ss || strlen(ss) ==0)
		return std::vector<std::string>();

	std::vector<std::string> ret_;
	if(NULL == strSep || strlen(strSep) ==0)
	{
		ret_.push_back(std::string(ss));
		return ret_;
	}

	std::string sep = strSep;
	std::string str = ss;
    std::string tmp;
    std::string::size_type pos_begin = str.find_first_not_of(sep);
    std::string::size_type comma_pos = 0;

    while (pos_begin != std::string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != std::string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
            ret_.push_back(tmp);
            tmp.clear();
        }
    }
    return ret_; 
}


ImportCSV::ImportCSV(void)
{
	m_strName = "����GeoStar CSV�ļ���ʽ";
	m_strDescription = "����GeoStar CSV�ļ���ʽ";
	m_eType = GIS::eImport;
}


ImportCSV::~ImportCSV(void)
{
} 
/// \brief ִ�в��
const char* ImportCSV::Execute(const char* strParameter,GIS::Progress * nProgress)
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
	//�����Ŀ¼
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		nProgress->OnLog("û���������·��",GIS::LogLevel::eError);
		return NULL;
	}

	//�����ļ���
	std::string strInputFile = kvp.Value("Path");
	if(strInputFile.empty())
	{
		nProgress->OnLog("û�����������ļ�",GIS::LogLevel::eError);
		return NULL;
	}

	//���������Geopackage��
	GDALAllRegister();
	OGRRegisterAll();
	
	nProgress->OnLog("����ʸ����׼���ݼ�",GIS::LogLevel::eInfo);

	const char *pszDriverName = "GPKG";
    GDALDriver *poDriver; 
    poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName );
    if( poDriver == NULL )
    {
		nProgress->OnLog("�޷���ȡGeoPackage������",GIS::LogLevel::eError);
		return NULL;
    }
	
	
	GDALDataset *poDS = poDriver->Create(strOuputFolder.c_str(), 0, 0, 0, GDT_Unknown, NULL );
	if( poDS == NULL )
	{ 
		nProgress->OnLog("������׼ʸ�����ݼ�ʧ��",GIS::LogLevel::eError);
		return NULL;
	}
	
	CPath path(CString(strInputFile.c_str()));
	path.RemoveExtension();
	CString str = path.m_strPath.Mid(path.FindFileName());
	nProgress->OnLog("CSV�޿ռ�ο�֧�֣�ȱʡΪCGCS2000",GIS::LogLevel::eWarning);
	OGRSpatialReference sr;
	char* wkt = "GEOGCS[\"China Geodetic Coordinate System 2000 \",DATUM[\"China 2000\",SPHEROID[\"CGCS2000\",6378137,298.257222101,AUTHORITY[\"EPSG\",\"1024\"]],AUTHORITY[\"EPSG\",\"6610\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4490\"]]";
	OGRErr e = sr.importFromWkt(&wkt);

	nProgress->OnLog("����ͼ��",GIS::LogLevel::eInfo);
	OGRLayer *poLayer = poDS->CreateLayer(CW2A(str), &sr, wkbPoint, NULL );
	if( poLayer == NULL )
	{
		nProgress->OnLog("������׼ͼ��ʧ��",GIS::LogLevel::eError);
		return NULL;
	}
	//��ʼ��CSV�ļ�����ȡCSV�ļ��е�ÿ����¼��
	std::ifstream csv(strInputFile.c_str(),std::ios::in);
	//����10k�Ļ��������洢һ�е����ݡ�
	char buff[10240];
	nProgress->OnLog("��ȡ��һ����Ϊ�ֶ�����",GIS::LogLevel::eInfo);
	//��ȡ��һ����Ϊ�ֶ�����
	csv.getline(buff,10240);
	std::vector<std::string> vec = Split(buff,",");
	//����oid��x��yդ���ֶΡ�
	std::vector<std::string>::iterator it = vec.begin() + 3;
	//���ֶ�һ��һ������ӽ�ȥ��
	for(;it != vec.end();it++)
	{
		OGRFieldDefn f(it->c_str(),OGRFieldType::OFTString);
		poLayer->CreateField(&f);
	}
	nProgress->OnLog("��ʼ��ȡʸ������",GIS::LogLevel::eInfo);
	nProgress->OnLog("�޷���ȡ����������˳���ȡ",GIS::LogLevel::eInfo);

	//������Ϣ����Ϊ�޷���ȡ���ļ�¼������nMax����-1
	long long nPos = 0,nMax=-1;
	OGRPoint point;
	long long nOID;
	OGRFeature pFea(poLayer->GetLayerDefn());
	poLayer->StartTransaction();
	while(!csv.eof())
	{
		//��ȡ��һ����Ϊ�ֶ�����
		csv.getline(buff,10240);
		vec = Split(buff,",");
		if(vec.empty())
			continue;

		it = vec.begin();
		//��ȡoid
		nOID = atoi(it->c_str());
		
		//���õ����OID����Ҫ�𣿻�����Feature�Լ�������
		pFea.SetFID(nOID);
		//���õ����x��y����
		it++;
		point.setX(atof(it->c_str()));
		it++;
		point.setY(atof(it->c_str()));
		
		//���õ����Geometry
		pFea.SetGeometry(&point);

		//�������е��ֶΣ�ֻ��Ϊ�ַ����ֶΡ�
		it++;
		int i =0;
		for(;it != vec.end();it++)
		{
			//��utf8���ַ�����д��
			CComBSTR bstr = it->c_str();
			pFea.SetField(i++,CW2A(bstr,CP_UTF8));
		}

		//�׳�����
		nProgress->OnProgress(++nPos,nMax,"�������","");

		//����layer����Feature���洢���Feature��
		poLayer->CreateFeature(&pFea);
	}
	poLayer->CommitTransaction();

	//�ر����ݼ�
	GDALClose(poDS);
	
	//�������
	KVParameter kvpoutput;
	nProgress->OnLog("�������",GIS::LogLevel::eInfo);

	//������
	m_strResult = kvpoutput.ToString();
	return m_strResult.c_str();
}
