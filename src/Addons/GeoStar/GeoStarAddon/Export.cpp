#include "StdAfx.h"
#include "Export.h"


ExportFCS::ExportFCS(void)
{
	m_strName = "导出GeoStar FCS矢量数据文件格式";
	m_strDescription = "导出GeoStar FCS矢量数据文件格式";
	
	m_eType = GIS::eExport;
}


ExportFCS::~ExportFCS(void)
{
} 
/// \brief 执行插件
const char* ExportFCS::Execute(const char* strParameter,GIS::Progress * pProgress)
{

	pProgress->OnLog("准备数据导出",GIS::LogLevel::eInfo);
	pProgress->OnLog("解析输入参数",GIS::LogLevel::eInfo);

	//输入参数
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		pProgress->OnLog("解析输入参数错误",GIS::LogLevel::eError);
		return NULL;
	}
	//输入的geopackage文件。
	std::string strInput = kvp.Value("Input");
	if(strInput.empty())
	{
		pProgress->OnLog("没有设置输入路径。",GIS::LogLevel::eError);
		return NULL;
	}

	//输出FCS文件。
	std::string strOutFile = kvp.Value("Path");
	if(strOutFile.empty())
	{
		pProgress->OnLog("没有设置输出文件",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "转换标准矢量数据为GeoStar FCS矢量数据从";
	strLog+=strInput;
	strLog+="到";
	strLog+=strOutFile;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

	GeoStar::Kernel::GsGeoPackageGeoDatabaseFactory fac;
	GeoStar::Kernel::GsConnectProperty conn;
	conn.Server = strInput;
	//打开GeoPackage数据源
	GeoStar::Kernel::GsGeoDatabasePtr ptrGPKDB = fac.Open(conn);
	if(!ptrGPKDB)
	{
		pProgress->OnLog("打开输入数据文件失败。",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("打开输入数据文件成功。",GIS::LogLevel::eInfo);

	GeoStar::Kernel::GsSqliteGeoDatabaseFactory facSqlite;
	conn.Server = strOutFile;
	//打开Sqlite数据源
	GeoStar::Kernel::GsGeoDatabasePtr ptrFCSDB = facSqlite.Open(conn);
	if(!ptrFCSDB)
	{
		pProgress->OnLog("打开输出数据文件失败。",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("打开输出数据文件成功。",GIS::LogLevel::eInfo);

	
	//从源数据库转换到目标数据库
	ExecuteTranslate(ptrGPKDB,ptrFCSDB,pProgress);
	 
	return m_strResult.c_str(); 
}





ExportDOM::ExportDOM(void)
{
	m_strName = "导出GeoStar DOM栅格数据文件格式";
	m_strDescription = "导出GeoStar DOM栅格数据文件格式";
	m_eType = GIS::eImport;
}


ExportDOM::~ExportDOM(void)
{
} 
/// \brief 执行插件
const char* ExportDOM::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	
	pProgress->OnLog("准备数据导入",GIS::LogLevel::eInfo);
	pProgress->OnLog("解析输入参数",GIS::LogLevel::eInfo);

	//输入参数
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		pProgress->OnLog("解析输入参数错误",GIS::LogLevel::eError);
		return NULL;
	}

	//输出的目录
	std::string strOuputFolder = kvp.Value("Path");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("没有设置输出路径",GIS::LogLevel::eError);
		return NULL;
	}

	//输入。
	std::string strInputFile = kvp.Value("Input");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("没有设置输入路径",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "转换";
	strLog+=strInputFile;
	strLog+="到标准栅格数据";
	strLog+=strOuputFolder;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);


	//输出参数
	KVParameter kvpoutput;
	GeoStar::Kernel::GsFileGeoDatabaseFactory vFacInput;
	GeoStar::Kernel::GsConnectProperty vConn;
	vConn.Server = strInputFile;
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBInput = vFacInput.Open(vConn);
	if(!ptrGDBInput)
	{
		pProgress->OnLog("打开输入数据源失败",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("打开输入数据源成功",GIS::LogLevel::eInfo);

	vConn.Server = strOuputFolder;
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBOutput = vFacInput.Open(vConn);
	if(!ptrGDBOutput)
	{
		pProgress->OnLog("打开输出数据源失败",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("打开输出数据源成功",GIS::LogLevel::eInfo);

	GsVector<GeoStar::Utility::GsString> vecNames;
	ptrGDBInput->DataRoomNames(GeoStar::Kernel::eRasterClass,vecNames);
	GsVector<GeoStar::Utility::GsString>::iterator it =  vecNames.begin();
	for(;it != vecNames.end();it++)
	{
		GeoStar::Kernel::GsRasterClassPtr ptrRasterClass = ptrGDBInput->OpenRasterClass(it->c_str());
		if(!ptrRasterClass)
			continue;
		
		strLog =  "准备转换";
		strLog+=*it;
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

		GeoStar::Kernel::GsRasterClassPtr ptrRasterClassOut = ptrGDBOutput->CreateRasterClass(it->c_str(),
			GeoStar::Kernel::GsRasterCreateableFormat::eGTiff,ptrRasterClass->RasterColumnInfo(),
			ptrRasterClass->SpatialReference());

		if(!ptrRasterClassOut)
		{
			strLog =  "创建输出";
			strLog+=*it;
			strLog+="失败";
			pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
			continue;
		}
		//总的像素数量。
		__int64 nTotal = ptrRasterClass->Width() * ptrRasterClass->Height();
		__int64 nNow = 0;
		GeoStar::Kernel::GsRasterCursorPtr ptrCursor = ptrRasterClass->Search(
			GeoStar::Utility::GsRect(0,0,ptrRasterClass->Width() , ptrRasterClass->Height()));

		strLog =  "转换";
		strLog+=*it;
		GeoStar::Kernel::GsRasterPtr ptrRaster = new GeoStar::Kernel::GsRaster();
		while(ptrCursor->Next(ptrRaster))
		{
			//写入Raster
			ptrRasterClassOut->WriteRaster(ptrRaster);
			
			nNow+= ptrRaster->Width() * ptrRaster->Height();
			pProgress->OnProgress(nNow,nTotal,strLog.c_str(),"转换");
		}

		strLog =  "写入元数据";
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

		//列举所有的元数据类别名称。
		std::vector<GeoStar::Utility::GsString> vecDomain = ptrRasterClass->MetadataDomain();
		std::vector<GeoStar::Utility::GsString>::iterator itDomain = vecDomain.begin();
		for(;itDomain != vecDomain.end();itDomain++)
		{
			//列举一个类别的元数据名称
			std::vector<GeoStar::Utility::GsString> vecMetaNames = ptrRasterClass->MetadataName(itDomain->c_str());
			std::vector<GeoStar::Utility::GsString>::iterator itName = vecMetaNames.begin();
			for(;itName != vecMetaNames.end();itName++)
			{
				//获取一个元数据。
				std::string strValue = ptrRasterClass->MetadataItem(itDomain->c_str(),itName->c_str());
				ptrRasterClassOut->MetadataItem(itDomain->c_str(),itName->c_str(),strValue.c_str());
			}
		}

	}
	return NULL;
}
