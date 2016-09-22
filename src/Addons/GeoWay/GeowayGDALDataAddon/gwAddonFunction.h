#ifndef _GW_ADDON_FUNCTION_H
#define _GW_ADDON_FUNCTION_H

#pragma once
#include "stdafx.h"
#include "Addon.h"
typedef enum tagenCodeTrans
{
	UTF8ToGBK = 0,
	UTF8ToUTF8,
	GBKToUTF8,
	GBKToGBK
}enCodeTrans;

class gwAddonFunction
{
public:
	 //static enCodeTrans enCode;
	 static char* ToUTF8(const char* src);
	 static char* FromUTF8(const char* src);
	 static void getRasterImportParams(const char* strParameter,string& strInFormat,string& strInPath,string& strOutPath,bool& bIsimport);
	 static void getVectorImportParams(const char* strParameter,string& strProvider,string& strInPath,string& strOutPath,bool& bIsimport);
	 static int copyLayer(OGRLayer *poSrcLayer, OGRLayer * pDestLayer,
		 OGRDataSource* pDestSource,
		 enCodeTrans enCode, bool isGDB,int& nIndex,int& OID);
	 static OGRErr SetFieldsFrom( OGRFeature * poSrcFeature, OGRFeature* poDestFeature,
		 int bForgiving ,enCodeTrans enCode);
	 static bool copyDataset(const string& strPath,const string& strOutPath,
		 const string& strProvier,GIS::Progress * nProgress);
	 static bool copyRaster(const string& strPath,const string& strOutPath,
		 const string& strProvier,GIS::Progress * nProgress);
	 static DOMDocument* Parse(const string& strFile);
	 static DOMDocument* ParseByContent(const string& strContent);
	 static string SaveXML(const XERCES_CPP_NAMESPACE::DOMNode* pNode, bool bPrettyPrint);
	 static bool WriteToTraget(XERCES_CPP_NAMESPACE::XMLFormatTarget* pTarget, const DOMNode* pNode, const char* szEncoding );
	 static wchar_t* CharToWchar(const char* c) ;
	 static char* WcharToChar(const wchar_t* wc)  ;
	 static bool WriteDEM(const char* inFile,const char* outFile,const ieSimpleRasterInfo& eInfo )  ;
	 static bool WriteDOM(const char* inFile,const char* outFile,const ieSimpleRasterInfo& eInfo )  ;
	 static int BuildFielsGDBv10(OGRLayer* pSrcLayer,vector<string>& vec_FieldNames);
	 static bool GeowayDB2SQLite(const char* inDir);
	 static OGRwkbGeometryType GetGeometryType(OGRLayer* pSrc);
	 static bool writeHDF5(const char * dstHDF5FileName, GDALDataset *dataset);
	 static int GetDirectChildren(std::vector<string>& vChildren,std::vector<string>& vChildFileNames, 
		 const string& strFileFilter, const string& strPath);
	 static bool CreateDir(const string& strPath);
};
#endif