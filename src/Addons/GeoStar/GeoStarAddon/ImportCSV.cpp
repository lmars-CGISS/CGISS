#include "StdAfx.h"
#include "ImportCSV.h"
#include <atlpath.h>
#include <fstream>
#include <string>
#include <vector>

/// \brief 将字符串分割为若干子串
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
	m_strName = "导入GeoStar CSV文件格式";
	m_strDescription = "导入GeoStar CSV文件格式";
	m_eType = GIS::eImport;
}


ImportCSV::~ImportCSV(void)
{
} 
/// \brief 执行插件
const char* ImportCSV::Execute(const char* strParameter,GIS::Progress * nProgress)
{
	nProgress->OnLog("准备数据导入",GIS::LogLevel::eInfo);
	nProgress->OnLog("1、解析输入参数",GIS::LogLevel::eInfo);

	//输入参数
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		nProgress->OnLog("解析输入参数错误",GIS::LogLevel::eError);
		return NULL;
	}
	//输出的目录
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		nProgress->OnLog("没有设置输出路径",GIS::LogLevel::eError);
		return NULL;
	}

	//输入文件。
	std::string strInputFile = kvp.Value("Path");
	if(strInputFile.empty())
	{
		nProgress->OnLog("没有设置输入文件",GIS::LogLevel::eError);
		return NULL;
	}

	//创建输出的Geopackage。
	GDALAllRegister();
	OGRRegisterAll();
	
	nProgress->OnLog("创建矢量标准数据集",GIS::LogLevel::eInfo);

	const char *pszDriverName = "GPKG";
    GDALDriver *poDriver; 
    poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName );
    if( poDriver == NULL )
    {
		nProgress->OnLog("无法获取GeoPackage的驱动",GIS::LogLevel::eError);
		return NULL;
    }
	
	
	GDALDataset *poDS = poDriver->Create(strOuputFolder.c_str(), 0, 0, 0, GDT_Unknown, NULL );
	if( poDS == NULL )
	{ 
		nProgress->OnLog("创建标准矢量数据集失败",GIS::LogLevel::eError);
		return NULL;
	}
	
	CPath path(CString(strInputFile.c_str()));
	path.RemoveExtension();
	CString str = path.m_strPath.Mid(path.FindFileName());
	nProgress->OnLog("CSV无空间参考支持，缺省为CGCS2000",GIS::LogLevel::eWarning);
	OGRSpatialReference sr;
	char* wkt = "GEOGCS[\"China Geodetic Coordinate System 2000 \",DATUM[\"China 2000\",SPHEROID[\"CGCS2000\",6378137,298.257222101,AUTHORITY[\"EPSG\",\"1024\"]],AUTHORITY[\"EPSG\",\"6610\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4490\"]]";
	OGRErr e = sr.importFromWkt(&wkt);

	nProgress->OnLog("创建图层",GIS::LogLevel::eInfo);
	OGRLayer *poLayer = poDS->CreateLayer(CW2A(str), &sr, wkbPoint, NULL );
	if( poLayer == NULL )
	{
		nProgress->OnLog("创建标准图层失败",GIS::LogLevel::eError);
		return NULL;
	}
	//开始打开CSV文件，读取CSV文件中的每条记录。
	std::ifstream csv(strInputFile.c_str(),std::ios::in);
	//分配10k的缓冲区，存储一行的内容。
	char buff[10240];
	nProgress->OnLog("获取第一行作为字段名称",GIS::LogLevel::eInfo);
	//获取第一行作为字段名称
	csv.getline(buff,10240);
	std::vector<std::string> vec = Split(buff,",");
	//跳开oid，x和y栅格字段。
	std::vector<std::string>::iterator it = vec.begin() + 3;
	//将字段一个一个的添加进去。
	for(;it != vec.end();it++)
	{
		OGRFieldDefn f(it->c_str(),OGRFieldType::OFTString);
		poLayer->CreateField(&f);
	}
	nProgress->OnLog("开始读取矢量数据",GIS::LogLevel::eInfo);
	nProgress->OnLog("无法获取地物总数，顺序读取",GIS::LogLevel::eInfo);

	//进度信息，因为无法获取最大的记录数量，nMax采用-1
	long long nPos = 0,nMax=-1;
	OGRPoint point;
	long long nOID;
	OGRFeature pFea(poLayer->GetLayerDefn());
	poLayer->StartTransaction();
	while(!csv.eof())
	{
		//获取第一行作为字段名称
		csv.getline(buff,10240);
		vec = Split(buff,",");
		if(vec.empty())
			continue;

		it = vec.begin();
		//获取oid
		nOID = atoi(it->c_str());
		
		//设置地物的OID？需要吗？还是有Feature自己决定。
		pFea.SetFID(nOID);
		//设置地物的x，y坐标
		it++;
		point.setX(atof(it->c_str()));
		it++;
		point.setY(atof(it->c_str()));
		
		//设置地物的Geometry
		pFea.SetGeometry(&point);

		//设置所有的字段，只能为字符串字段。
		it++;
		int i =0;
		for(;it != vec.end();it++)
		{
			//以utf8的字符串填写。
			CComBSTR bstr = it->c_str();
			pFea.SetField(i++,CW2A(bstr,CP_UTF8));
		}

		//抛出进度
		nProgress->OnProgress(++nPos,nMax,"导入地物","");

		//调用layer创建Feature，存储这个Feature。
		poLayer->CreateFeature(&pFea);
	}
	poLayer->CommitTransaction();

	//关闭数据集
	GDALClose(poDS);
	
	//输出参数
	KVParameter kvpoutput;
	nProgress->OnLog("导入完成",GIS::LogLevel::eInfo);

	//输出结果
	m_strResult = kvpoutput.ToString();
	return m_strResult.c_str();
}
