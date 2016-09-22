
#include "ieSimpleRasterFactory.h"
ieSimpleRaster* ieSimpleRasterFactory::OpenRaster(const std::string& strPath, 
									   /*ieSimpleRaster** pRaster, */bool bReadOnly)
{
	ieSimpleRaster* pRaster = new ieSimpleRaster();
	ieSimpleRasterInfo ieInfo;
	int nIdx = strPath.find_last_of(".");
	std::string strTempPath = strPath;
	//std::string strext = strPath.substr(nIdx,strPath.size()-nIdx);
	transform(strTempPath.begin(), strTempPath.end(), strTempPath.begin(), toupper);  
	/*if(strstr(strTempPath.data(),".TIF") == 0)
		return false;*/

	//GDAL有bug，暂时不知道该属性为什么有时不起作用
	if( CSLTestBoolean(CPLGetConfigOption( "GDAL_FILENAME_IS_UTF8", "YES" ) ) )
	{
		CPLGetConfigOption("GDAL_FILENAME_IS_UTF8", NULL);
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
	}
	GDALAllRegister();  
	GDALDataset* pDataset = NULL;

	if (bReadOnly)
		pDataset = reinterpret_cast<GDALDataset*>(GDALOpen(strPath.c_str(),GA_ReadOnly));
	else
		pDataset = reinterpret_cast<GDALDataset*>(GDALOpen(strPath.c_str(),GA_Update));

	
	if (NULL == pDataset)
	{
		/*std::string strErr;
		sprintf("error! Open Raster %ls",strErr.data());*/
		return false;
	}
	ieInfo.left = 0.0;
	ieInfo.right = 0.0;
	ieInfo.bottom = 0.0;
	ieInfo.top = 0.0;

	ieInfo.m_nWidth =  pDataset->GetRasterXSize();
	ieInfo.m_nHeight = pDataset->GetRasterYSize();
	ieInfo.m_nBandCount = pDataset->GetRasterCount();

	ieInfo.m_strProjectionRef = pDataset->GetProjectionRef();

	double adfGeoTransform[6];
	std::vector<double> vecParam(6); //

	/*  GetGeoTransform() note
	*	In a north up image, padfTransform[1] is the pixel width, and padfTransform[5] is the pixel height. 
	*  The upper left corner of the upper left pixel is at position (padfTransform[0],padfTransform[3]).
	*/	
	//if( CE_None == pDataset->GetGeoTransform(adfGeoTransform))
	//{
	//	//zbr 20131026 修改 根据GDALGetMetadataItem字段判断坐标时中心点还是左上角点
	//	bool bPixelIsArea = true; //true 左上角 false 中心点

	//	std::string strPixelOrPoint = GDALGetMetadataItem(pDataset, GDALMD_AREA_OR_POINT, NULL);
	//	
	//	if( strPixelOrPoint!=""&& strPixelOrPoint == GDALMD_AOP_POINT )
	//		bPixelIsArea = false;
	//	if(bPixelIsArea)
	//	{
	//		ieInfo.m_eRasterOrgPos = RasterPosEnum_LeftTop_Corner;
	//	}
	//	else
	//	{
	//		ieInfo.m_eRasterOrgPos = RasterPosEnum_LeftTop_Center;
	//		fprintf(stdout,"info! Img Coord Read Center\n");
	//	}
	//	/*ieInfo.m_vecParamRaster2Geo.clear();
	//	ieInfo.m_vecParamRaster2Geo.resize(6);*/
	//	ieInfo.m_vecParamRaster2Geo[0] = adfGeoTransform[0];
	//	ieInfo.m_vecParamRaster2Geo[1] = adfGeoTransform[1];
	//	ieInfo.m_vecParamRaster2Geo[2] = adfGeoTransform[2];
	//	ieInfo.m_vecParamRaster2Geo[3] = adfGeoTransform[3];
	//	ieInfo.m_vecParamRaster2Geo[4] = adfGeoTransform[4];
	//	ieInfo.m_vecParamRaster2Geo[5] = adfGeoTransform[5];
	//}
	//else
	//{	
	//	//扫描原点的坐标位置
	//	ieInfo.m_eRasterOrgPos = RasterPosEnum_LeftTop_Corner;
	//	//ieInfo.setGeoInfo(ieInfo.m_nWidth,ieInfo.m_nHeight,1,1,0,0,gwRasterPosEnum_LeftBottom_Corner);
	//}
	GDALRasterBand* poBand0 = pDataset->GetRasterBand(1);
	if (!poBand0)
	{
		//gError(LOG_CAT,"error! poBand0 == NULL");
		return false;
	}

	GDALDataType eGDALDataType;
	eGDALDataType = poBand0->GetRasterDataType();
	ieInfo.m_eDataType = eGDALDataType;
	//if(ieInfo.m_eDataType == gwPixelDataType_Unknown)
	//{
	//	gError(LOG_CAT,"error! DataType == Unknown");
	//	return gwFALSE;// 暂时不支持的位深度
	//}
	//获取金子塔的等级
	int nOverviewCount = GDALGetOverviewCount(poBand0);
	ieInfo.m_nPyramidalLevel = nOverviewCount;
	ieInfo.m_bExistPyramid = false;
	//获取金字塔比率
	if (nOverviewCount > 0)
	{
		ieInfo.m_bExistPyramid = true;
		GDALRasterBand* poOverviewBand;
		int nOViewSize;
		int nPreViewSize = ieInfo.m_nWidth;

		for (int i = 0; i < nOverviewCount; i++)
		{
			poOverviewBand = poBand0->GetOverview(i);
			nOViewSize = poOverviewBand->GetXSize();
			//目前Raster创建的金字塔只可能是整倍数CreatePyramid
			int dRate = static_cast<int>((static_cast<double>(nPreViewSize)/nOViewSize + 0.5));

			ieInfo.m_vPyramidRates.push_back(dRate);

			nPreViewSize = nOViewSize;
		}

		ieInfo.m_dPyramidRate = ieInfo.m_vPyramidRates[0]; 
	}


	// 获取无效值
	int bGetValue = 0;
	ieInfo.m_dInvalidValue = poBand0->GetNoDataValue(&bGetValue);
	//因为统计接口用到了是否存在无效值，暂时针对bil做判断
	if(bGetValue)
	{
		ieInfo.m_bHavingInvalidValue = true;
	}

	int iBlockSizeX = 0;
	int iBlockSizeY = 0;
	poBand0->GetBlockSize(&iBlockSizeX,&iBlockSizeY);
	if(iBlockSizeX < ieInfo.m_nWidth)
	{
		ieInfo.m_bIsTileModel = true;
		ieInfo.m_nTileWidth = iBlockSizeX;
		ieInfo.m_nTileHeight = iBlockSizeY;
	}
	else
	{
		ieInfo.m_bIsTileModel = false;
		ieInfo.m_nTileWidth = ieInfo.m_nWidth;
		ieInfo.m_nTileHeight = 1;
	}


	//以下代码是暂时性的，需要斟酌
	////////////////////////////////////////////////////////////////////////////////////
	GDALColorInterp eColorInterp = poBand0->GetColorInterpretation();
	ieInfo.m_eImageMode = eColorInterp;
	
	ieInfo.m_vecColorInterp.push_back(eColorInterp);
	//获取波段的色调设置
	int i;
	for( i = 1 ; i < ieInfo.m_nBandCount ; i++ )
	{
		GDALRasterBand* poBand1 = pDataset->GetRasterBand(1+i);
		GDALColorInterp eColorInterp1 = poBand1->GetColorInterpretation();
		ieInfo.m_vecColorInterp.push_back(eColorInterp1);
	}

	//调色板初始化
	GDALColorTable* pColorTable = poBand0->GetColorTable();
	if (pColorTable)
	{
		int lColorEntryCount = pColorTable->GetColorEntryCount();
		ieInfo.m_nPalCount = lColorEntryCount;
		
		
		GDALPaletteInterp ePaletteInterp = pColorTable->GetPaletteInterpretation();
		ieInfo.m_ePaletteInterp = ePaletteInterp;
		/*for (int i = 0 ; i < lColorEntryCount ; ++i)
		{
			const GDALColorEntry* pGDALColorEntry = pColorTable->GetColorEntry(i);
			if (pGDALColorEntry)
			{
				ieInfo.m_pGDALColorEntry.push_back((GDALColorEntry*)pGDALColorEntry);

			}
		}*/
	}
	//Debug_zbr 2015年03月17日 TIF格式 获取扫描分辨率
	const char* szDPIX = GDALGetMetadataItem(pDataset, "TIFFTAG_XRESOLUTION", NULL);
	std::string strDPIX = "";
	if(szDPIX != NULL)
		strDPIX = szDPIX;
	const char* szDPIY = GDALGetMetadataItem(pDataset, "TIFFTAG_YRESOLUTION", NULL);
	std::string strDPIY = "";
	if(szDPIY != NULL)
		strDPIY = szDPIY;
	std::string strUnitDPI = "";
	const char* szUnitDPI = GDALGetMetadataItem(pDataset, "TIFFTAG_RESOLUTIONUNIT", NULL);
	if(szUnitDPI != NULL)
		strUnitDPI =  szUnitDPI;
	if(strDPIX !="" )
	{
		ieInfo.m_dDPIX  = (double)atof(strDPIX.data());
		
	}
	if(!strDPIY.empty())
		ieInfo.m_dDPIY = (double)atof(strDPIY.data());
	if( strUnitDPI == "2" )  //像素/英寸
	{
		;
	}
	else  if( strUnitDPI == "3") //像素/厘米
	{
		ieInfo.m_dDPIX  /=2.54;
		ieInfo.m_dDPIY  /=2.54;
	}


	//LK_DEBUG 2011/10/10 增加读TFW测试
	//ieInfo.m_eTiffExportType = gwTiffExportType_Tfw;

	//gwString strRasterExt = gwPath::GetExtension(ieInfo.m_strRasterDataPath);
	//if(strRasterExt.Compare(".tif",gwCaseSensitivity_Insensitive) == 0 
	//	|| strRasterExt.Compare(".tiff",gwCaseSensitivity_Insensitive) == 0)
	//{
	//	gwString gwTfw = GetTfwPathName();
	//	//如果存在tfw,以tfw优先
	//	if(!ReadTfw(vecParam))
	//	{
	//		ieInfo.m_eTiffExportType = gwTiffExportType_GTiff;
	//	}
	//	else
	//	{
	//		ieInfo.setParamRaster2Geo(vecParam);	
	//	}
	//}
	////	ieInfo.m_dResolutionX = ieInfo.getResolutionX();
	////	m_gdalRstInfo.m_dResolutionY = m_gdalRstInfo.getResolutionY();
	//m_bIsOpen = gwTRUE;


	
	ieInfo.m_MetaData.setXMLContent(pDataset->GetMetadataItem(GW_SimpleMetaDataItemName,GW_SimpleMetaDataItemName));
	//*pRaster = new ieSimpleRaster;
	pRaster->setRasterInfo(ieInfo);
	GDALClose(pDataset);
	//pRaster->ConnectRasterSource(pDataset);
	return pRaster;
}

bool ieSimpleRasterFactory::CreateRaster(const std::string& strFilePath,
										 const ieSimpleRasterInfo& ieInfo,
										 ieSimpleRaster** pRaster)
{

	
	std::string strPath = strFilePath;

	
	int nIdx = strPath.find_last_of(".");
	std::string strTempPath = strPath;
	//std::string strext = strPath.substr(nIdx,strPath.size()-nIdx);
	transform(strTempPath.begin(), strTempPath.end(), strTempPath.begin(), toupper);  
	if(strstr(strTempPath.data(),".TIF") == 0)
		return false;	
	
	std::string sFormat;
	bool bPix = false;

	//gwPath::IsFile不能判断不存在的文件，所以无法判断传入的路径
	//if (gwPath::IsFile(strPath))
	FILE* pFile = fopen(strFilePath.data(),"rb");
	//删除原始文件
	if(pFile!=NULL)
	{
		fclose(pFile);
		pFile = NULL;
		/*if(std::remove(strFilePath.data()) == -1)
		{*/
			fprintf(stderr,"error! Create File %s can not delete",strPath.c_str());
			return false;
		//}
	}
	/*std::string strAux = strPath.erase(nIdx);
	pFile = fopen(strAux,"rb");
	if(pFile!=NULL)
	{
		fclose(pFile);
		pFile = NULL;
		std::remove(strAux.data())
		
	}*/
	std::string strExt = strPath.substr(nIdx,strPath.length() - nIdx);
	if(strExt.length() <= 5)	
	{
		
		if (strExt.compare(".bmp")==0)
		{
			sFormat = "BMP";
		}
		else if(strExt.compare(".jpg")==0
			|| strExt.compare(".jpeg")==0)
		{
			sFormat = "JPEG";
		}
		else if(strExt.compare(".tif")==0
			|| strExt.compare(".tiff")==0)
		{
			sFormat = "GTiff";
			
			//删除tfw
		}
			else if(strExt.compare(".img")==0)
			{
				sFormat = "HFA";
			}
			else if(strExt.compare(".pix")==0)
			{
				sFormat = "PAux";
				bPix = true;
			}
			else if(strExt.compare(".envi")==0)
			{
				sFormat = "ENVI";
			}
			else if(strExt.compare(".bil")==0)
			{
				sFormat = "EHdr";
				
			}
			else if(strExt.compare(".png")==0)
			{
				sFormat = "PNG";
			}
			else
			{
				//gError(LOG_CAT,"error! Create not support");
				return false;
			}


			if (GDT_Byte == ieInfo.m_eDataType)
			{
				bPix = true;
			}
			else if(GDT_UInt16 == ieInfo.m_eDataType)
			{
				bPix = true;
			}
			else if(GDT_Int16 == ieInfo.m_eDataType)
			{
				bPix = true;
			}
	}
	else
	{
		if (strExt.compare(".gero")==0 && strstr(strPath.data(),"@"))
		{
			sFormat = "GEORASTER";
		}
		else
			return false;
	}

	GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName(sFormat.c_str());

	if (NULL == poDriver)
	{
		//gError(LOG_CAT,"error! Create poDriver == NULL");
		return false;
	}

	char **papszMetadata;
	papszMetadata = poDriver->GetMetadata();
	if(!CSLFetchBoolean( papszMetadata, GDAL_DCAP_CREATE, false ) )
	{
		//gError(LOG_CAT,"error! CSLFetchBoolean");
		return false;//该格式不支持CREATE
	}

	//位深度描述转换
	GDALDataType eGDALDataType = ieInfo.m_eDataType;// PixelDataType2GDALDataType(m_gdalRstInfo.m_eDataType);

	char **papszOptions = NULL;   
	if(ieInfo.m_bIsTileModel == true && 0 == sFormat.compare("GTiff") )
	{
		papszOptions = CSLSetNameValue(papszOptions, "TILED", "YES");  //HFA  格式会报警告
		/*		if(m_gdalRstInfo.nTileWidth == 0) 
		{
		m_gdalRstInfo.nTileWidth = 256;
		m_gdalRstInfo.nTileHeight = 256;
		}
		char szBlock[128];
		sprintf(szBlock,"%d",m_gdalRstInfo.nTileWidth);
		papszOptions = CSLSetNameValue( papszOptions, "BLOCKSIZE", szBlock );*/
	}
	if( 0 == sFormat.compare("GTiff"))
	{
		if (ieInfo.m_nBandCount >= 3)
		{
			papszOptions = CSLSetNameValue(papszOptions, "PHOTOMETRIC", "RGB");
			
		}
	}
	if(ieInfo.m_bCompressed == true && 0 == sFormat.compare("GTiff"))
	{
		papszOptions = CSLSetNameValue(papszOptions, "COMPRESS", "JPEG");
	}

	GDALDataset* pDataset = poDriver->Create(strFilePath.c_str(),
		ieInfo.m_nWidth,
		ieInfo.m_nHeight,
		ieInfo.m_nBandCount,
		eGDALDataType,
		papszOptions);

	if (NULL == pDataset)
	{
		
		return false;// 创建失败
	}
	//zbr 20120109  adfGeoTransform[0]，adfGeoTransform[3]存的就是左上角点的坐标(非中心点)
	double adfGeoTransform[6]; 

	/*adfGeoTransform[0] = m_gdalRstInfo.getGeoStartPosX(gwRasterPosEnum_LeftTop_Corner);
	adfGeoTransform[1] = m_gdalRstInfo.getResolutionX();
	adfGeoTransform[2] = 0;
	adfGeoTransform[3] = m_gdalRstInfo.getGeoStartPosY(gwRasterPosEnum_LeftTop_Corner);
	adfGeoTransform[4] = 0;
	adfGeoTransform[5] = -1 * m_gdalRstInfo.getResolutionY();

	if( fabs(fabs(adfGeoTransform[5]) - fabs(adfGeoTransform[1])) < 1e-8)
	{
		if( fabs(adfGeoTransform[5]) > fabs(adfGeoTransform[1]) )
		{
			if(adfGeoTransform[1] > 0) adfGeoTransform[1] = fabs(adfGeoTransform[5]);
			else adfGeoTransform[1] = - fabs(adfGeoTransform[5]);
		}
		else
		{
			if(adfGeoTransform[5] > 0) adfGeoTransform[5] = fabs(adfGeoTransform[1]);
			else adfGeoTransform[5] = - fabs(adfGeoTransform[1]);
		}
	}
	if(m_gdalRstInfo.m_eTiffExportType == gwTiffExportType_Tfw && 0 == sFormat.compare("GTiff") )
	{
		adfGeoTransform[0] = 0;
		adfGeoTransform[1] = 1;
		adfGeoTransform[2] = 0;
		adfGeoTransform[3] = 0;
		adfGeoTransform[4] = 0;
		adfGeoTransform[5] = 1;
	}*/
	adfGeoTransform[0] = ieInfo.m_vecParamRaster2Geo[0];
	adfGeoTransform[1] = ieInfo.m_vecParamRaster2Geo[1];
	adfGeoTransform[2] = ieInfo.m_vecParamRaster2Geo[2];
	adfGeoTransform[3] = ieInfo.m_vecParamRaster2Geo[3];
	adfGeoTransform[4] = ieInfo.m_vecParamRaster2Geo[4];
	adfGeoTransform[5] = ieInfo.m_vecParamRaster2Geo[5];
	
	if (CE_None != pDataset->SetGeoTransform(adfGeoTransform))
	{
		//gError(LOG_CAT,"error! SetGeoTransform");
		return false;// 设定空间信息失败
	}
	std::string strProjectionRef = ieInfo.m_strProjectionRef;
	if(!ieInfo.m_strProjectionRef.empty() 
		&& (0 == sFormat.compare("GTiff") || 0 == sFormat.compare("HFA") || sFormat.compare("GEORASTER") == 0))
	{
		//strProjectionRef = strProjectionRef.replace("\n","");
		//strProjectionRef = strProjectionRef.replace("   "," ");
		//strProjectionRef = strProjectionRef.replace("  "," ");
		//strProjectionRef = strProjectionRef.replace(", ",",");
		//strProjectionRef = strProjectionRef.replace(" ,",",");
		//strProjectionRef = strProjectionRef.replace("[ ","[");
		//strProjectionRef = strProjectionRef.replace(" [","[");
		//strProjectionRef = strProjectionRef.replace("] ","]");
		//strProjectionRef = strProjectionRef.replace(" ]","]");
		//strProjectionRef = strProjectionRef.replace("\" ","\"");
		//strProjectionRef = strProjectionRef.replace(" \"","\"");
		////wkt需要转换一次，成为GDAL承认的关键字
		//strProjectionRef = strProjectionRef.replace("Transverse Mercator","Transverse_Mercator");
		//strProjectionRef = strProjectionRef.replace("Gauss_Kruger","Transverse_Mercator");
		//strProjectionRef = strProjectionRef.replace("UTM","Transverse_Mercator");
		if(CE_None != pDataset->SetProjection(strProjectionRef.c_str()))
		{	
			
		}
	}

	if (!bPix && ieInfo.m_bHavingInvalidValue) //不是像素信息，才会设置无效值
	{
		poDriver->SetMOFlags(GMO_IGNORE_UNIMPLEMENTED);
		for (int i = 0 ; i < ieInfo.m_nBandCount ; ++i)
		{
			GDALRasterBand* poBand = pDataset->GetRasterBand(1 + i);
			if (!poBand)
			{
				
				return false;
			}

			poBand->SetNoDataValue(ieInfo.m_dInvalidValue);
		}		
	}
	//Debug_zbr 2015年03月17日 TIF格式设置DPI
	if( fabs(ieInfo.m_dDPIX) > 0.9999999 && fabs(ieInfo.m_dDPIY) > 0.9999999 )
	{
		std::string strDPIX,strDPIY;
		char cDPIX[10];
		char cDPIY[10];
		if( fabs(ieInfo.m_dDPIX - int(ieInfo.m_dDPIX+1e-6)) < 1e-6 )
		{
			
			sprintf(cDPIX,"%d",int(ieInfo.m_dDPIX+1e-6));
			sprintf(cDPIY,"%d",int(ieInfo.m_dDPIY+1e-6));
			
		}
		else
		{
			sprintf(cDPIX,"%.2f",int(ieInfo.m_dDPIX+1e-6));
			sprintf(cDPIY,"%.2f",int(ieInfo.m_dDPIY+1e-6));
			
		}
		pDataset->SetMetadataItem("TIFFTAG_XRESOLUTION", cDPIX);
		pDataset->SetMetadataItem("TIFFTAG_YRESOLUTION", cDPIY);
		pDataset->SetMetadataItem("TIFFTAG_RESOLUTIONUNIT", "2");//RESUNIT_INCH
	}
	

	
	pDataset->FlushCache();
	
	*pRaster = new ieSimpleRaster;
	(*pRaster)->setRasterInfo(ieInfo);
	(*pRaster)->ConnectRasterSource(pDataset);
	return true;
}