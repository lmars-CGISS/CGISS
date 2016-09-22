#include "StdAfx.h"
#include "ExportCSV.h"
#include <atlpath.h>
#include <fstream>

ExportCSV::ExportCSV(void)
{
	m_strName = "导出GeoStar CSV文件格式";
	m_strDescription = "导出GeoStar CSV文件格式";
	m_eType = GIS::eExport;
}


ExportCSV::~ExportCSV(void)
{
}
/// \brief 执行插件
const char* ExportCSV::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	nProgress->OnLog("准备数据导出",GIS::LogLevel::eInfo);
	nProgress->OnLog("1、解析输入参数",GIS::LogLevel::eInfo);

	//输入参数
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		nProgress->OnLog("解析输入参数错误",GIS::LogLevel::eError);
		return NULL;
	}
	//输入的geopackage文件。
	std::string strInput = kvp.Value("Input");
	if(strInput.empty())
	{
		nProgress->OnLog("没有设置输入路径。",GIS::LogLevel::eError);
		return NULL;
	}

	//输出CSV文件。
	std::string strOutFile = kvp.Value("Path");
	if(strOutFile.empty())
	{
		nProgress->OnLog("没有设置输出文件",GIS::LogLevel::eError);
		return NULL;
	}

	//创建输出的Geopackage。
	GDALAllRegister();
	OGRRegisterAll();
	
	nProgress->OnLog("打开矢量标准数据集",GIS::LogLevel::eInfo);
	std::string strT = "GPKG:";
	strT+=strInput;
	GDALDataset *poDS = (GDALDataset*) GDALOpenEx( strInput.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL );
	if( poDS == NULL )
	{ 
		nProgress->OnLog("打开标准矢量数据集失败",GIS::LogLevel::eError);
		return NULL;
	}
	for(int i =0;i<poDS->GetLayerCount();i++)
	{
		OGRLayer* pLyr = poDS->GetLayer(i);
		OGRwkbGeometryType eType =  pLyr->GetGeomType();
		int nType = eType % 1000;
		//目前只对点进行转换。
		if(nType != wkbPoint)
			continue;

		std::string str = "创建图层";
		str+=pLyr->GetName();
		nProgress->OnLog(str.c_str(),GIS::LogLevel::eInfo);

		CPath path(CString(strOutFile.c_str()));
		//组成输出的文件名
		std::string strFileName= pLyr->GetName();
		strFileName+=".csv";
		path.Append(CString(strFileName.c_str()));
		
		//创建CSV文件
		std::ofstream csv(CW2A(path.m_strPath),std::ios::out);

		//字段结构
		OGRFeatureDefn* pDef = pLyr->GetLayerDefn();
		nProgress->OnLog("准备字段",GIS::LogLevel::eInfo);
		//基本字段oid和x，y'
		csv<<"oid,x,y";
		for(int i =0;i<pDef->GetFieldCount();i++)
		{
			csv<<","<<pDef->GetFieldDefn(i)->GetNameRef();
		}
		csv<<std::endl;	

		nProgress->OnLog("转换数据",GIS::LogLevel::eInfo);
		pLyr->ResetReading();
		OGRFeature* pFea = pLyr->GetNextFeature();
		long long nPos = 0,nMax= pLyr->GetFeatureCount();
		while(NULL != pFea)
		{ 
			//输出oid
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
			//抛出进度
			nProgress->OnProgress(++nPos,nMax,"导出地物","");

			pFea = pLyr->GetNextFeature();
		}
		
	}
	//关闭数据集
	GDALClose(poDS); 
	return m_strResult.c_str();
}