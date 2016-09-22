#include "StdAfx.h"
#include "Import.h"


ImportFCS::ImportFCS(void)
{
	m_strName = "导入GeoStar FCS矢量数据格式";
	m_strDescription = "导入GeoStar FCS矢量数据格式";
	
	m_eType = GIS::eImport;
}


ImportFCS::~ImportFCS(void)
{
} 
/// \brief 执行插件
const char* ImportFCS::Execute(const char* strParameter,GIS::Progress * pProgress)
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
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("没有设置输出路径",GIS::LogLevel::eError);
		return NULL;
	}

	//导入
	std::string strInputFile = kvp.Value("Path");
	if(strInputFile.empty())
	{
		pProgress->OnLog("没有设置输入路径",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "转换";
	strLog+=strInputFile;
	strLog+="到标准矢量数据";
	strLog+=strOuputFolder;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);


	//输出参数
	KVParameter kvpoutput;
	GeoStar::Kernel::GsSqliteGeoDatabaseFactory vSqliteFac;
	GeoStar::Kernel::GsConnectProperty vConn;
	vConn.Server = strInputFile;
	 
	//打开输入地物类
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBInput =  vSqliteFac.Open(vConn);
	if(!ptrGDBInput)
	{
		pProgress->OnLog("打开输入数据文件失败",GIS::LogLevel::eError);
		return NULL;
	}

	pProgress->OnLog("打开输入数据文件成功",GIS::LogLevel::eInfo);

	//打开输出地物类
	GeoStar::Kernel::GsGeoPackageGeoDatabaseFactory vGPKGFac;
	vConn.Server = strOuputFolder;
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBOutput =  vGPKGFac.Open(vConn);
	if(!ptrGDBOutput)
	{
		pProgress->OnLog("打开输出数据文件失败",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("打开输出数据文件成功。",GIS::LogLevel::eInfo);

	//从源数据库转换到目标数据库
	ExecuteTranslate(ptrGDBInput,ptrGDBOutput,pProgress);

 

	//输出结果
	m_strResult = kvpoutput.ToString();
	return m_strResult.c_str();
}



ImportGPKG::ImportGPKG(void)
{
	m_strName = "导入标准矢量数据格式";
	m_strDescription = "导入标准矢量数据格式";
	
	m_eType = GIS::eImport;
}


ImportGPKG::~ImportGPKG(void)
{

} 
/// \brief 执行插件
const char* ImportGPKG::Execute(const char* strParameter,GIS::Progress * pProgress)
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
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("没有设置输出路径",GIS::LogLevel::eError);
		return NULL;
	}

	//导入
	std::string strInputFile = kvp.Value("Path");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("没有设置输出路径",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "转换";
	strLog+=strInputFile;
	strLog+="到标准矢量数据";
	strLog+=strOuputFolder;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);


	
	//输入目录
	GeoStar::Utility::GsDir inputFolder(strInputFile.c_str());
	if(!inputFolder.Exists())
	{
		pProgress->OnLog("输入路径不存在。",GIS::LogLevel::eError);
		return NULL;
	}
	GsVector<GeoStar::Utility::GsFile> vec = inputFolder.Files("*.gpkg");
	GsVector<GeoStar::Utility::GsFile> vec1 = inputFolder.Files("*.gpkgx");
	if(!vec1.empty())
		vec.insert(vec.end(),vec1.begin(),vec1.end());
	
	if(vec.empty())
	{
		pProgress->OnLog("没有可以转换的标准标准矢量数据。",GIS::LogLevel::eError);
		return NULL;
	}

	//输出参数
	KVParameter kvpoutput;
	GeoStar::Kernel::GsGeoPackageGeoDatabaseFactory vFac;
	GeoStar::Kernel::GsConnectProperty vConn;
	
	vConn.Server = strOuputFolder;
	GeoStar::Kernel::GsGeoDatabasePtr ptrGDBOutput =  vFac.Open(vConn);
	if(!ptrGDBOutput)
	{
		pProgress->OnLog("打开输出数据文件失败",GIS::LogLevel::eError);
		return NULL;
	}
	pProgress->OnLog("打开输入数据文件成功",GIS::LogLevel::eInfo);
	
	GsVector<GeoStar::Utility::GsFile>::iterator it = vec.begin();
	for(;it != vec.end();it++)
	{
		vConn.Server = it->FullPath();
		std::string strLog = "转入文件";
		strLog+=it->FullPath();
	
		//打开输入地物类
		GeoStar::Kernel::GsGeoDatabasePtr ptrGDBInput =  vFac.Open(vConn);
		if(!ptrGDBInput)
		{
			strLog+="失败";
			pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
			continue;
		}
		
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);
		//从源数据库转换到目标数据库
		ExecuteTranslate(ptrGDBInput,ptrGDBOutput,pProgress);

	}

	//输出结果
	m_strResult = kvpoutput.ToString();
	return m_strResult.c_str();
}

 
 



ImportDOM::ImportDOM(void)
{
	m_strName = "导入GeoStar DOM栅格数据文件格式";
	m_strDescription = "导入GeoStar DOM栅格数据文件格式";
	m_eType = GIS::eImport;
}


ImportDOM::~ImportDOM(void)
{
} 
/// \brief 执行插件
const char* ImportDOM::Execute(const char* strParameter,GIS::Progress * pProgress)
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
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("没有设置输出路径",GIS::LogLevel::eError);
		return NULL;
	}

	//输入。
	std::string strInputFile = kvp.Value("Path");
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

		//只转出geotiff的。
		GeoStar::Utility::GsString strFormat = ptrRasterClass->Format();
		if(stricmp(strFormat.c_str(),"GTiff") != 0)
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
