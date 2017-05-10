
#ifndef _SU_ADDON_BASE_H
#define _SU_ADDON_BASE_H

#pragma once

#include "stdafx.h"
#include "Addon.h"

#include "Stream/ugdefs.h"
#include "FileParser/UGExchangeParamsManager.h"
#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"
#include "DataExchange/UGDataExchange.h"
#include "Engine/UGDataSourceManager.h"

using namespace OGDC;
using namespace UGC;

typedef enum tagenCodeTrans
{
	UTF8ToGBK = 0,
	UTF8ToUTF8,
	GBKToUTF8,
	GBKToGBK
}enCodeTrans;

class SuAddonBase:public GIS::AddonBase
{
public:
	//static UGDataSource* OpenDS(UGEngineType nType,  UGString& strServer,  UGString& strUser ,  UGString& strPasswd)
public:
	SuAddonBase(void);

	~SuAddonBase(void);

	static char* ToUTF8(const char* src);

	static char* FromUTF8(const char* src);

	static wchar_t* CharToWchar(const char* c) ;

	static char* WcharToChar(const wchar_t* wc)  ;

	static DOMDocument* ParseByContent(const string& strContent);

	static int GetDirectChildren(std::vector<string>& vChildren,std::vector<string>& vChildFileNames, 
		const string& strFileFilter, const string& strPath);

	static bool CreateDir(const string& strPath);

	static DOMDocument* Parse(const string& strFile);

	static void getRasterImportParams(const char* strParameter,string& strInFormat,string& strInPath,string& strOutPath,bool& bIsimport);

	static void getVectorImportParams(const char* strParameter,string& strProvider,string& strInPath,string& strOutPath,bool& bIsimport);

	static UGDataSource* OpenDS(UGEngineType nType, const UGString& strServer, const UGString& strUser , const UGString& strPasswd );

	static UGDataSource* OpenDSNew(UGEngineType nType, const UGString& strServer, const UGString& strUser , const UGString& strPasswd );


	static UGbool Import(UGDataSource* pDs, const UGString& strFilePath, UGFileType::EmType nType);

	static UGbool Export(UGDataSource* pDs, const UGString& strFilePath, UGFileType::EmType nType, const UGString& strDtName);
	
	static UGbool ExportRaster(UGDataSource* pDs, const UGString& strFilePath, UGFileType::EmType nType, const UGString& strDtName);

	static string SaveXML(const XERCES_CPP_NAMESPACE::DOMNode* pNode, bool bPrettyPrint);

	static bool  CopyOtherLayers(OGRDataSource* pSrcSource, OGRDataSource* pDestSource,const string& strAnnoName,int nAnnoIdx ,enCodeTrans enCode, bool isGDB);

	static OGRLayer*  CreateMetadataReferenceLayer(OGRDataSource* pDestSource,OGRSpatialReference* pSpatial);
	
	static OGRLayer* CreateSymbolLayer(OGRDataSource* pDestSource,OGRSpatialReference* pSpatial);
	
	static int copyLayer(OGRLayer *poSrcLayer, OGRLayer * pDestLayer,
		OGRDataSource* pDestSource,
		enCodeTrans enCode, bool isGDB,int& nIndex,int& OID);

	static OGRErr SetFieldsFrom( OGRFeature * poSrcFeature, OGRFeature* poDestFeature,
		int bForgiving ,enCodeTrans enCode);

	
	static bool RegisterTable(sqlite3* hDB,const string& strTableName);

	static bool CreateTable(sqlite3* hDB);

	static bool InnitMetadataTable(const string& strGPKGPath,const string& strPath);

	static bool copyDataset(const string& strPath,const string& strOutPath,
		const string& strProvier,GIS::Progress * nProgress);

	static bool ImportRaster(const string& strPath,const string& strOutPath,
		const string& strProvier,GIS::Progress * nProgress);

};
#endif


