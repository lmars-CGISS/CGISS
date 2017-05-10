
#include "StdAfx.h"
#include "SuExport.h"

ExportGPKG::ExportGPKG(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;
}


ExportGPKG::~ExportGPKG(void)
{

	xercesc::XMLPlatformUtils::Terminate();

}

/// \brief 执行插件
const char* ExportGPKG::Execute(const char* strParameter,GIS::Progress * pProgress)
{

	m_strResult = "转换失败";
	string strInFormat;
	string strPath;
	string strGPKGPath;

	bool bIsImport = false;
	SuAddonBase::getVectorImportParams(strParameter,strInFormat,strPath,strGPKGPath,bIsImport);


	UGString strFileTemp;
	UGString strUDB = strFileTemp.FromStd(strPath);//_U("");

	OGRRegisterAll();



	//!!从UDB中开始转出

	UGDataSource *pDs = OpenDS(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		pProgress->OnLog("打开输出数据文件失败",GIS::LogLevel::eError);
		return 0;
	}
	pProgress->OnLog("打开输出数据文件成功",GIS::LogLevel::eInfo);

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

			// 如果存在，删除之，确保数据转换成功
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
			pProgress->OnLog("转换失败",GIS::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return m_strResult.data();
	}
	m_strResult = "读取成功";
	if(pProgress != NULL)
		pProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return m_strResult.c_str(); 
}



ExportGTIFF::ExportGTIFF(void)
{
	xercesc::XMLPlatformUtils::Initialize();;
	m_strName = "导入外部文件格式";
	m_strDescription = "导入外部文件格式";
	m_eType = GIS::eImport;
}


ExportGTIFF::~ExportGTIFF(void)
{
	xercesc::XMLPlatformUtils::Terminate();

}


/// \brief 执行插件
const char* ExportGTIFF::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	m_strResult = "转换失败";
	string strInFormat;
	string strPath;
	string strOutPath;

	bool bIsImport = false;
	SuAddonBase::getRasterImportParams(strParameter,strInFormat,strPath,strOutPath,bIsImport);


	UGString strFileTemp;
	UGString strUDB = strFileTemp.FromStd(strPath);//_U("");


	//!!从UDB中开始转出

	UGDataSource *pDs = OpenDS(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		pProgress->OnLog("打开输出数据文件失败",GIS::LogLevel::eError);
		return 0;
	}
	pProgress->OnLog("打开输出数据文件成功",GIS::LogLevel::eInfo);

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
			{//控制只转出第一个栅格数据集，即可
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
		strLog+="失败";
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
	}
	else
	{
		strLog+="成功！";
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

	}
	delete pDs;
	pDs = NULL;

	if(!bExport)
	{
		if(pProgress != NULL)
			pProgress->OnLog("转换失败",GIS::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return m_strResult.data();
	}
	m_strResult = "读取成功";
	if(pProgress != NULL)
		pProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return m_strResult.c_str();
	
}
