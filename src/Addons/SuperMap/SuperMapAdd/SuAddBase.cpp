
#include "StdAfx.h"
#include "SuAddBase.h"

#include "xercesc/framework/LocalFileInputSource.hpp"

SuAddonBase::SuAddonBase(void)
{

}


SuAddonBase::~SuAddonBase(void)
{

}

char*  SuAddonBase::ToUTF8(const char* src)
{
	int wlen = MultiByteToWideChar(CP_ACP,0,src,-1,NULL,0);  
	wchar_t* tbuf = (wchar_t*)CPLCalloc(sizeof(wchar_t),wlen+1);
	tbuf[wlen] = 0;
	MultiByteToWideChar( CP_ACP, 0, src, -1, tbuf, wlen+1 );

	int len;  
	len = WideCharToMultiByte(CP_UTF8, 0, tbuf, -1, NULL, 0, NULL, NULL);  
	char* pszResult = (char*)CPLCalloc(sizeof(char),len+1);


	WideCharToMultiByte(CP_UTF8, 0, tbuf, -1, pszResult, len, NULL,NULL); 
	CPLFree(tbuf);
	return pszResult;
}

char*  SuAddonBase::FromUTF8(const char* src)
{
	wchar_t* wc = CPLRecodeToWChar(src,CPL_ENC_UTF8,"WCHAR_T");

	int Namelen = 0;  
	Namelen = WideCharToMultiByte(CP_ACP, 0, wc, -1, NULL, 0, NULL, NULL);  
	char* pszName = (char*)CPLCalloc(sizeof(char),Namelen+1);


	WideCharToMultiByte(CP_ACP, 0, wc, -1, pszName, Namelen, NULL,NULL); 
	return pszName;
}

//===================================================
//! \brief  打开数据源
//! \param  nType     [I]数据源类型
//! \param  strServer [I] 服务名
//! \param  strUser   [I]用户名
//! \param  strPasswd [I]密码
//! \return 打开成功返回true，否则返回false  
//! \remarks 
//! \attention
UGDataSource* SuAddonBase::OpenDS(UGEngineType nType, const UGString& strServer, const UGString& strUser = _U(""), const UGString& strPasswd = _U(""))
{
	UGDataSource *pDs =  UGDataSourceManager::CreateDataSource(nType);
	if (NULL == pDs)
	{
		return NULL;
	}

	UGDsConnection &dscn = pDs->GetConnectionInfo();
	dscn.m_strServer   = strServer;
	dscn.m_strUser     = strUser;
	dscn.m_strPassword = strPasswd;

	if (pDs->Open())
	{
		return pDs;
	}

	delete pDs;
	pDs = NULL;

	return NULL;
}

UGDataSource* SuAddonBase::OpenDSNew(UGEngineType nType, const UGString& strServer, const UGString& strUser = _U(""), const UGString& strPasswd = _U(""))
{
	UGDataSource* pDs = UGDataSourceManager::CreateDataSource(UGEngineType::UDB);
	UGDsConnection& connection = pDs->GetConnectionInfo();
	// connection.m_strServer = _U(":memory:"); // 设置为内存数据源，在内存占用较多时，会自动写到系统临时目录的文件中
	connection.m_strServer = strServer;//_U("Import.udb");

	// 如果存在，删除之，确保每次创建数据源都能成功
	if(UGFile::IsExist(connection.m_strServer))
	{
		UGFile::Delete(connection.m_strServer);
		UGString uddFile = UGFile::GetDir(connection.m_strServer);
		uddFile +=UGFile::GetTitle(connection.m_strServer);
		uddFile += _U(".udd");

		UGFile::Delete(uddFile);
	}

	pDs->Create();
	//UGDataSource *pDs =  UGDataSourceManager::CreateDataSource(nType);
	//if (NULL == pDs)
	//{
	//	return NULL;
	//}

	UGDsConnection &dscn = pDs->GetConnectionInfo();
	dscn.m_strServer   = strServer;
	dscn.m_strUser     = strUser;
	dscn.m_strPassword = strPasswd;

	if (pDs->Open())
	{
		return pDs;
	}

	delete pDs;
	pDs = NULL;

	return NULL;
}

char* SuAddonBase::WcharToChar(const wchar_t* wc)   
{      
	if(wc==NULL)
		return NULL;
	int len= WideCharToMultiByte(CP_ACP,0,wc,wcslen(wc),NULL,0,NULL,NULL);   
	char* m_char=new char[len+1];  
	memset(m_char, 0, (len+1)*sizeof(char));  
	WideCharToMultiByte(CP_ACP,0,wc,wcslen(wc),m_char,len,NULL,NULL);   
	m_char[len]='\0';   
	return m_char;   
}  

wchar_t* SuAddonBase::CharToWchar(const char* c)   
{   
	if(c==NULL)
		return NULL;
	int len = MultiByteToWideChar(CP_ACP,0,c,strlen(c),NULL,0);   
	wchar_t* m_wchar=new wchar_t[len+1];   
	memset(m_wchar, 0, (len+1)*sizeof(wchar_t));  
	MultiByteToWideChar(CP_ACP,0,c,strlen(c),m_wchar,len);   
	m_wchar[len]='\0';   
	return m_wchar;   
} 

DOMDocument* SuAddonBase::ParseByContent(const string& strContent)
{

	wchar_t* contents = CharToWchar(strContent.data());

	MemBufInputSource source(
		(XMLByte*)contents,  //NOLINT
		wcslen(contents) * sizeof(wchar_t), "string");

	const XMLCh* pEncoding = L"UTF-16"; //NOLINT
	source.setEncoding(pEncoding);
	auto_ptr<XercesDOMParser> pParser(new XercesDOMParser());
	pParser->parse(source);
	delete[] contents;
	return pParser->adoptDocument();
}

DOMDocument* SuAddonBase::Parse(const string& strFile)
{
	auto_ptr<XercesDOMParser> pParser(new XercesDOMParser());
	wchar_t* szPath = CharToWchar(strFile.data());
	LocalFileInputSource* pFileSource = new LocalFileInputSource(szPath);
	pParser->parse(*pFileSource);
	DOMDocument* dom = pParser->adoptDocument();
	delete[] szPath;
	delete pFileSource;
	return dom;
}

//判断是否为目录 0 目录，1 文件，2 gdb，3 grid
int IsDirectory1(const char *pszName,const string& FileFilter)
{
	FILE* pFile = fopen(pszName,"rb");
	if(pFile == NULL)
	{
		if(FileFilter == "*")
		{
			string strFile = pszName;
			//判断是否为GRID数据
			strFile = strFile + "\\w001001.adf";
			pFile = fopen(strFile.data(),"rb");
			if (pFile == NULL)
				return 0;
			else
			{
				fclose(pFile);
				return 3;
			}
		}
		if(FileFilter == "*.gdb")
		{
			string strFile = pszName;
			//判断是否为gdb数据
			strFile = strFile + "\\a00000000.gdbtable";
			pFile = fopen(strFile.data(),"rb");
			if (pFile == NULL)
				return 0;
			else
			{
				fclose(pFile);
				return 2;
			}
		}

	}
	else
	{
		fclose(pFile);
		return 1;
	}
}

int SuAddonBase::GetDirectChildren(std::vector<string>& vChildren,std::vector<string>& vChildFileNames,
									   const string& strFileFilter,  const string& strPath)
{	
	if(IsDirectory1(strPath.data(),strFileFilter)!=0)
	{
		vChildren.push_back(strPath);
		return 1;
	}

	struct _wfinddata_t c_file;
	intptr_t hFile;
	string strFind = strPath;
	string strFinds = "";
	if(strPath.find_last_of("/") == strPath.length() - 1||
		strPath.find_last_of("\\") == strPath.length() - 1)
	{
		strFinds =strPath+ (char*)strFileFilter.data();
	}
	else
	{
		strFinds = strPath + "\\" + (char*)strFileFilter.data();
	}

	wchar_t* wcFind = CharToWchar(strFinds.data());
	if( (hFile = _wfindfirst(wcFind, &c_file )) == -1L )
		return 0;
	delete[] wcFind;
	wcFind = NULL;
	do
	{
		//排除"."和".."
		if(wcscmp(L".", c_file.name) == 0 || wcscmp(L"..", c_file.name)==0)
			continue;
		string strFile = "";
		string strFileName = "";
		strFind = strPath;
		if(strPath.find_last_of("/") == strPath.length() - 1||
			strPath.find_last_of("\\") == strPath.length() - 1)
		{
			char* FileName = SuAddonBase::WcharToChar(c_file.name);
			strFileName = FileName;
			strFile = strFind.append(FileName) ;
			delete[] FileName;
			FileName = NULL;
		}
		else
		{
			strFile = strFind.append("\\");
			char* FileName = SuAddonBase::WcharToChar(c_file.name);
			strFileName = FileName;
			strFile = strFile.append(FileName) ;
			delete[] FileName;
			FileName = NULL;
		}
		int nType = IsDirectory1(strFile.data(),strFileFilter);
		if( nType != 0 )
		{
			if((nType == 3 && strFileFilter == "*"))
			{
				vChildFileNames.push_back(strFileName);
				vChildren.push_back( strFile );
			}
			else if(strFileFilter != "*")
			{
				vChildFileNames.push_back(strFileName);
				vChildren.push_back( strFile );
			}
		}
	} while( _wfindnext( hFile, &c_file ) == 0 );

	_findclose(hFile);
	return vChildren.size();
}
bool SuAddonBase::CreateDir(const string& strPath)
{

	string strAbsolutePath = strPath;
	wchar_t* szPath = CharToWchar(strAbsolutePath.data());

	int nSize = strAbsolutePath.size();
	for(int i = 0; i < nSize; i++)
	{
		if( (i == nSize-1)
			|| (i > 0 && i < nSize-1 && ('/' == szPath[i] || '\\' == szPath[i])) )
		{   
			if(i != nSize-1)
				szPath[i]   =   '\0';   

			if( _waccess(szPath, 0) !=0  ) 
			{
				if(_wmkdir(szPath) != 0)
				{
					delete[] szPath;
					szPath = NULL;
					return false;
				}
			}
			if(i != nSize-1)
				szPath[i]   =   '\\';
		} //end of if
	} //end of for
	delete[] szPath;
	szPath = NULL;
	return true;
}

void SuAddonBase::getVectorImportParams(const char* strParameter,string& strProvider,string& strInPath,string& strOutPath,bool& bIsimport)
{
	string strType ="";
	string strTempIn;
	string strTempOut;
	DOMDocument *m_pDoc = ParseByContent(strParameter);
	DOMNodeList* pNodeList = m_pDoc->getElementsByTagName(L"Value");
	int nIDCount = pNodeList->getLength();
	bIsimport = true;
	for(int n = 0; n < nIDCount; n++)
	{
		DOMNode* pValueNode = pNodeList->item(n);
		DOMNode* pNode = pValueNode->getParentNode();
		DOMNamedNodeMap* pMap = pNode->getAttributes();
		DOMNode* pAttrNode = pMap->getNamedItem(L"Key");
		wchar_t* wzdata = (wchar_t*)pAttrNode->getNodeValue();
		char* szdata = WcharToChar(wzdata);
		if(stricmp(szdata,DATA_TYPE) == 0)
		{
			char* szType = WcharToChar(pValueNode->getTextContent());
			strType = szType;
			delete[] szType;
		}

		if(stricmp(szdata,PATH)==0 )
		{
			char* szstrInPath = WcharToChar(pValueNode->getTextContent());
			strTempIn = szstrInPath;
			delete[] szstrInPath;

		}
		if(stricmp(szdata,IN_GPKGPATH)==0 ||
			stricmp(szdata,OUT_GPKGPATH)==0 )
		{
			if(stricmp(szdata,IN_GPKGPATH)==0)
				bIsimport = false;
			char* szout = WcharToChar(pValueNode->getTextContent());
			strTempOut = szout;
			delete[] szout;

		}
		delete[] szdata;

	}
	if(stricmp(strType.data(),FILE_TYPE)==0||
		strType=="")
	{
		string strExt = "";
		if(bIsimport)
		{
			strInPath = strTempIn;
			strOutPath = strTempOut;
			if(strTempOut.find_last_of(".") != -1)
				strExt = strTempOut.substr(strTempOut.find_last_of("."),strTempOut.length()-strTempOut.find_last_of("."));
		}
		else
		{
			strInPath = strTempOut;
			strOutPath = strTempIn;
			if(strTempIn.find_last_of(".") == -1)
				strExt = "";
			else
			{
				strExt = strTempIn.substr(strTempIn.find_last_of("."),strTempIn.length()-strTempIn.find_last_of("."));
			}

		}

		if (stricmp(strExt.data(),".gpkg")==0)
		{
			strProvider = "GPKG";
		}
		if(stricmp(strExt.data(),".udb")==0)
		{
			strProvider = "SuperMap";
		}
		if(stricmp(strExt.data(),".shp")==0||
			strExt == "")
		{
			strProvider = "ESRI Shapefile";
		}
		if(stricmp(strExt.data(),".mdb")==0)
		{
			strProvider = "PGeo";
		}
		if(stricmp(strExt.data(),".gdb")==0)
		{
			strProvider = "FileGDB";
		}
		if(stricmp(strExt.data(),".db")==0)
		{
			strProvider = "SQLite";
		}
		
	}
} 


void SuAddonBase::getRasterImportParams(const char* strParameter,string& strInFormat,string& strInPath,string& strOutPath,bool& bIsimport)
{
	string strType;
	string strTempPath = strParameter;
	string strTempIn;
	string strTempOut;
	transform(strTempPath.begin(), strTempPath.end(), strTempPath.begin(), tolower); 
	DOMDocument *m_pDoc = ParseByContent(strParameter);
	wchar_t*  vn = CharToWchar("Value");
	DOMNodeList* pNodeList = m_pDoc->getElementsByTagName(vn);
	delete[] vn;
	int nIDCount = pNodeList->getLength();
	bIsimport = true;
	for(int n = 0; n < nIDCount; n++)
	{
		DOMNode* pValueNode = pNodeList->item(n);
		DOMNode* pNode = pValueNode->getParentNode();
		DOMNamedNodeMap* pMap = pNode->getAttributes();
		wchar_t* szkey =  CharToWchar("Key");
		DOMNode* pAttrNode = pMap->getNamedItem(szkey);
		wchar_t* data = (wchar_t*)pAttrNode->getNodeValue();
		char* szdata = WcharToChar(data);

		if(stricmp(szdata,DATA_TYPE) == 0)
		{
			char* szType = WcharToChar(pValueNode->getTextContent());
			strType = szType;
			delete[] szType;
		}

		if(stricmp(szdata,PATH)==0 )
		{
			char* szstrInPath = WcharToChar(pValueNode->getTextContent());
			strTempIn = szstrInPath;
			delete[] szstrInPath;

		}
		if(stricmp(szdata,IN_GPKGPATH)==0 ||
			stricmp(szdata,OUT_GPKGPATH)==0 )
		{
			if(stricmp(szdata,IN_GPKGPATH)==0)
				bIsimport = false;
			char* szout = WcharToChar(pValueNode->getTextContent());
			strTempOut = szout;
			delete[] szout;

		}
		delete[] szdata;

	}
	if(stricmp(strType.data(),FILE_TYPE)==0||
		strType=="")
	{
		string strExt = "";
		if(bIsimport)
		{
			strInPath = strTempIn;
			strOutPath = strTempOut;
			if(strTempOut.find_last_of(".") != -1)
				strExt = strTempOut.substr(strTempOut.find_last_of("."),strTempOut.length()-strTempOut.find_last_of("."));
		}
		else
		{
			strInPath = strTempOut;
			strOutPath = strTempIn;
			if(strTempIn.find_last_of(".") != -1)
				strExt = strTempIn.substr(strTempIn.find_last_of("."),strTempIn.length()-strTempIn.find_last_of("."));
		}

		if(stricmp(strExt.data(),".tif") == 0)
		{
			strInFormat = "GTiff";
		}
		if (stricmp(strExt.data(),".udb")==0)
		{
			strInFormat = "SuperMap";
		}
		/*
		if (stricmp(strExt.data(),".img")==0)
		{
			strInFormat = "HFA";
		}
		
		if(stricmp(strExt.data(),".h5") == 0)
		{
			strInFormat = "HDF5";
		}
		if(stricmp(strExt.data(),".jp2") == 0||
			stricmp(strExt.data(),".j2k") == 0)
		{
			strInFormat = "JP2OpenJPEG";
		}
		if(strExt=="")
		{
			strInFormat = "AAIGrid";
		}
		*/
	}
}


//===================================================
//! \brief  数据导入
//! \param  pDs         [I]数据源指针
//! \param  strFilePath [I] 文件路径
//! \param  nType       [I] 文件格式类型
//! \return 打开成功返回true，否则返回false  
//! \remarks 
//! \attention
UGbool SuAddonBase::Import(UGDataSource* pDs, const UGString& strFilePath, UGFileType::EmType nType)
{
	if (NULL == pDs)
	{
		return FALSE;
	}

	UGImportParams *pParams = UGExchangeParamsManager::MakeImportParams(UGint(nType));
	if (NULL == pParams)
	{
		return FALSE;
	}

	pParams->SetFilePathName(strFilePath);
	pParams->SetOverWrite(TRUE);

	UGDataExchange dataEx;
	dataEx.AttachDataSource(pDs);
	UGbool bImport = dataEx.Import(*pParams);

	UGExchangeParamsManager::DestoryImportParams(pParams);
	pParams = NULL;

	return bImport;
}

//===================================================
//! \brief  数据导出
//! \param  pDs         [I]数据源指针
//! \param  strFilePath [I] 文件路径
//! \param  nType       [I] 文件格式类型
//! \return 打开成功返回true，否则返回false  
//! \remarks 
//! \attention
UGbool SuAddonBase::Export(UGDataSource* pDs, const UGString& strFilePath, UGFileType::EmType nType, const UGString& strDtName)
{
	if (NULL == pDs)
	{
		return FALSE;
	}

	UGExportParams *pParams = UGExchangeParamsManager::MakeExportParams(UGint(nType));
	if (NULL == pParams)
	{
		return FALSE;
	}

	UGVectorExportParams *pVetParams = (UGVectorExportParams*)pParams;
	pVetParams->SetFilePathName(strFilePath);
	pVetParams->SetOverWrite(TRUE);
	pVetParams->SetDtNameToBeExported(strDtName);

	UGDataExchange dataEx;
	dataEx.AttachDataSource(pDs);
	UGbool bExport =  dataEx.Export(*pParams);

	UGExchangeParamsManager::DestoryExportParams(pParams);
	pParams = NULL;

	return bExport;
}

bool SuAddonBase::ImportRaster(const string& strPath1,const string& strOutPath, 
								 const string& strProvier,GIS::Progress * nProgress)
{
	string strPath = strPath1;
	string m_strResult = "转换失败";
	bool bIsImport = true;
	string strOutExt = "";
	if(strOutPath.find_last_of(".")!=-1)
		strOutExt = strOutPath.substr(strOutPath.find_last_of("."),strOutPath.length()-strOutPath.find_last_of("."));
	string strInExt = "";
	if(strPath.find_last_of(".")!=-1)
		strInExt = strPath.substr(strPath.find_last_of("."),strPath.length()-strPath.find_last_of("."));

	if(nProgress != NULL)
		nProgress->OnLog("开始转换",GIS::eInfo);
	else
		std::cout<<"开始转换"<<std::endl;

	///!
	UGString  strPathTemp;

	UGString strUDB = strPathTemp.FromStd(strOutPath);
	UGString strFilePath = strPathTemp.FromStd(strPath);

	UGDataSource *pDs = OpenDS(UGC::UDB, strUDB,_U(""),_U(""));
	if (NULL == pDs)
	{
		nProgress->OnLog("打开输出数据文件失败",GIS::LogLevel::eError);
		return 0;
	}
	nProgress->OnLog("打开输入数据文件成功",GIS::LogLevel::eInfo);

	UGbool bImport = Import(pDs, strFilePath, UGFileType::GTiff);

	string strLog = "";
	if (!bImport)
	{
		strLog+="失败";
		nProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
	}
	else
	{
		strLog+="成功！";
		nProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

	}
	delete pDs;
	pDs = NULL;

	return true;
}

UGbool SuAddonBase::ExportRaster(UGDataSource* pDs, const UGString& strFilePath, UGFileType::EmType nType, const UGString& strDtName)
{
	if (NULL == pDs)
	{
		return FALSE;
	}

	UGExportParams *pParams = UGExchangeParamsManager::MakeExportParams(UGint(nType));
	if (NULL == pParams)
	{
		return FALSE;
	}

	UGRasterExportParams *pRasParams = (UGRasterExportParams*)pParams;
	pRasParams->SetFilePathName(strFilePath);
	pRasParams->SetOverWrite(TRUE);
	pRasParams->SetDtNameToBeExported(strDtName);

	UGDataExchange dataEx;
	dataEx.AttachDataSource(pDs);
	UGbool bExport =  dataEx.Export(*pParams);

	UGExchangeParamsManager::DestoryExportParams(pParams);
	pParams = NULL;

	return bExport;
}

OGRLayer* SuAddonBase::CreateSymbolLayer(OGRDataSource* pDestSource,OGRSpatialReference* pSpatial)
{
	OGRLayer* poSymLayer = pDestSource->CreateLayer( "symbol", pSpatial,
		wkbUnknown, NULL );
	if(poSymLayer == NULL)
		return NULL;
	
	OGRFieldDefn oTypeDef("",OFTString) ;
	oTypeDef.SetName("Type");
	//oTypeDef.SetNullable(false);
	oTypeDef.SetType(OFTString);
	poSymLayer->CreateField(&oTypeDef);

	OGRFieldDefn oNameDef("",OFTString) ;
	oNameDef.SetName("Name");
	//oNameDef.SetNullable(true);
	oNameDef.SetType(OFTString);
	poSymLayer->CreateField(&oNameDef);

	OGRFieldDefn oDescriptionDef("",OFTString) ;
	oDescriptionDef.SetName("description");
	//oDescriptionDef.SetNullable(true);
	oDescriptionDef.SetType(OFTString);
	poSymLayer->CreateField(&oDescriptionDef);

	OGRFieldDefn oUriDef("",OFTString) ;
	oUriDef.SetName("sd_standard_uri");
	//oUriDef.SetNullable(true);
	oUriDef.SetType(OFTString);
	poSymLayer->CreateField(&oUriDef);

	OGRField oField ;
	oField.String = "text/xml";
	OGRFieldDefn oMimeDef("",OFTString);
	oMimeDef.SetName("mime_type");
	//oMimeDef.SetNullable(false);
	oMimeDef.SetDefault(&oField);
	oMimeDef.SetType(OFTString);
	poSymLayer->CreateField(&oMimeDef);

	OGRFieldDefn oSymbolDef("",OFTString) ;
	oSymbolDef.SetName("symboldata");
	//oSymbolDef.SetNullable(false);
	oSymbolDef.SetType(OFTString);
	poSymLayer->CreateField(&oSymbolDef);

	return poSymLayer;

}



OGRErr  SuAddonBase::SetFieldsFrom( OGRFeature * poSrcFeature, OGRFeature* poDestFeature,
								 int bForgiving,enCodeTrans enCode )

{
	int         iField;// *panMap;
	OGRErr      eErr;
	vector<int> panMap;
	panMap.resize(poSrcFeature->GetFieldCount());
	//panMap = (int *) VSIMalloc( sizeof(int) * poSrcFeature->GetFieldCount() );
	for( iField = 0; iField < poSrcFeature->GetFieldCount(); iField++ )
	{
		string strFieldName = poSrcFeature->GetFieldDefnRef(iField)->GetNameRef();
		char* szName = NULL;// (char*)strFieldName.data();
		if(stricmp(strFieldName.data(),"TestString")==0 )
		{
			strFieldName = "annotaionValue";
		}

		switch (enCode)
		{
		case UTF8ToUTF8:
		case GBKToGBK:
			{
				int len = strFieldName.length();
				szName =new char[len+1];
				strcpy(szName,strFieldName.c_str());
			}
			break;
		case UTF8ToGBK:
			szName = FromUTF8(strFieldName.data());
			break;
		case GBKToUTF8:
			szName = ToUTF8(strFieldName.data());
			break;
		}
		/*if(!bIsUTF8)
			szName = ToUTF8(strFieldName.data());*/
		int nIdx = poDestFeature->GetFieldIndex(szName );
		if(nIdx == -1)
		{
			string strName = szName;
			if(stricmp(strName.data(),"annotaionValue")==0)
			{
				strName = "TestString";
			}
			nIdx = poDestFeature->GetFieldIndex(strName.data() );
			
			if(nIdx == -1 && strName.length() > 10)
			{
				strName = strName.substr(0,10);
				nIdx = poDestFeature->GetFieldIndex(strName.data() );
			}
		}
		panMap[iField] = nIdx;
		if(enCode == GBKToUTF8||
			enCode == UTF8ToGBK)
			CPLFree(szName);
		else
			delete[] szName;

		szName = NULL;
		if( panMap[iField] == -1 )
		{
			
			if( bForgiving )
				continue;
			else
			{
				
				return OGRERR_FAILURE;
			}
		}
	}

	poDestFeature->SetFID( OGRNullFID );

	/* -------------------------------------------------------------------- */
	/*      Set the geometry.                                               */
	/* -------------------------------------------------------------------- */
	if( poDestFeature->GetGeomFieldCount() == 1 )
	{
		OGRGeomFieldDefn* poGFieldDefn = poDestFeature->GetGeomFieldDefnRef(0);

		int iSrc = poSrcFeature->GetGeomFieldIndex(
			poGFieldDefn->GetNameRef());
		if( iSrc >= 0 )
			poDestFeature->SetGeomField( 0, poSrcFeature->GetGeomFieldRef(iSrc) );
		else
			/* whatever the geometry field names are. For backward compatibility */
			poDestFeature->SetGeomField( 0, poSrcFeature->GetGeomFieldRef(0) );
	}
	else
	{
		int i;
		for(i = 0; i < poDestFeature->GetGeomFieldCount(); i++)
		{
			OGRGeomFieldDefn* poGFieldDefn = poDestFeature->GetGeomFieldDefnRef(i);

			int iSrc = poSrcFeature->GetGeomFieldIndex(
				poGFieldDefn->GetNameRef());
			if( iSrc >= 0 )
				poDestFeature->SetGeomField( i, poSrcFeature->GetGeomFieldRef(iSrc) );
			else
				poDestFeature->SetGeomField( i, NULL );
		}
	}

	/* -------------------------------------------------------------------- */
	/*      Copy feature style string.                                      */
	/* -------------------------------------------------------------------- */
	poDestFeature->SetStyleString( poSrcFeature->GetStyleString() );


	int          iDstField;

	for( iField = 0; iField < poSrcFeature->GetFieldCount(); iField++ )
	{
		iDstField = panMap[iField];

		if( iDstField < 0 )
			continue;

		if( poDestFeature->GetFieldCount() <= iDstField )
		{
			//VSIFree(panMap);
			return OGRERR_FAILURE;
		}

		if( !poSrcFeature->IsFieldSet(iField) )
		{
			poDestFeature->UnsetField( iDstField );
			continue;
		}
		
		switch( poSrcFeature->GetFieldDefnRef(iField)->GetType() )
		{
		case OFTInteger:

			poDestFeature->SetField( iDstField, poSrcFeature->GetFieldAsInteger( iField ) );
			break;

		case OFTReal:
			poDestFeature->SetField( iDstField, poSrcFeature->GetFieldAsDouble( iField ) );
			break;

		case OFTString:
			{
				string FieldValue = poSrcFeature->GetFieldAsString( iField );
				
				char* szValue = NULL;//(char*)FieldValue.data();
				switch (enCode)
				{
				case UTF8ToUTF8:
				case GBKToGBK:
					{
						int len = FieldValue.length();
						szValue =new char[len+1];
						strcpy(szValue,FieldValue.c_str());
					}
					break;
				case UTF8ToGBK:
					szValue = FromUTF8(FieldValue.data());
					break;
				case GBKToUTF8:
					szValue = ToUTF8(FieldValue.data());
					break;
				}

			/*	if(!bIsUTF8)
					szValue = ToUTF8(FieldValue.data());*/

				poDestFeature->SetField( iDstField, szValue );
				if(enCode == UTF8ToGBK||
					enCode == GBKToUTF8)
					CPLFree(szValue);
				else
					delete[] szValue;
				szValue = NULL;

			}
			
			break;

		case OFTIntegerList:
			{
				if (poDestFeature->GetFieldDefnRef(iDstField)->GetType() == OFTString)
				{
					poDestFeature->SetField( iDstField, poSrcFeature->GetFieldAsString(iField) );
				}
				else
				{
					int nCount;
					const int *panValues = poSrcFeature->GetFieldAsIntegerList( iField, &nCount);
					poDestFeature->SetField( iDstField, nCount, (int*) panValues );
				}
			}
			break;

		case OFTRealList:
			{
				if (poDestFeature->GetFieldDefnRef(iDstField)->GetType() == OFTString)
				{
					poDestFeature->SetField( iDstField, poSrcFeature->GetFieldAsString(iField) );
				}
				else
				{
					int nCount;
					const double *padfValues = poSrcFeature->GetFieldAsDoubleList( iField, &nCount);
					poDestFeature->SetField( iDstField, nCount, (double*) padfValues );
				}
			}
			break;

		case OFTDate:
		case OFTDateTime:
		case OFTTime:
			if (poDestFeature->GetFieldDefnRef(iDstField)->GetType() == OFTDate ||
				poDestFeature->GetFieldDefnRef(iDstField)->GetType() == OFTTime ||
				poDestFeature->GetFieldDefnRef(iDstField)->GetType() == OFTDateTime)
			{
				poDestFeature->SetField( iDstField, poSrcFeature->GetRawFieldRef( iField ) );
			}
			else if (poDestFeature->GetFieldDefnRef(iDstField)->GetType() == OFTString)
			{
				poDestFeature->SetField( iDstField, poSrcFeature->GetFieldAsString( iField ) );
			}
			else if( !bForgiving )
			{
				//VSIFree(panMap);
				return OGRERR_FAILURE;
			}
			break;

		default:
			if( poSrcFeature->GetFieldDefnRef(iField)->GetType()
				== poDestFeature->GetFieldDefnRef(iDstField)->GetType() )
			{
				poDestFeature->SetField( iDstField, poSrcFeature->GetRawFieldRef(iField) );
			}
			else if (poDestFeature->GetFieldDefnRef(iDstField)->GetType() == OFTString)
			{
				string FieldValue = poSrcFeature->GetFieldAsString( iField );
				char* szValue = NULL;// (char*)FieldValue.data();
				switch (enCode)
				{
				case UTF8ToUTF8:
				case GBKToGBK:
					{
						int len = FieldValue.length();
						szValue =new char[len+1];
						strcpy(szValue,FieldValue.c_str());
					}
					break;
				case UTF8ToGBK:
					szValue = FromUTF8(FieldValue.data());
					break;
				case GBKToUTF8:
					szValue = ToUTF8(FieldValue.data());
					break;
				}

			/*	if(!bIsUTF8)
					szValue = ToUTF8(FieldValue.data());*/

				poDestFeature->SetField( iDstField, szValue );
				if(enCode == UTF8ToGBK||
					enCode == GBKToUTF8)
					CPLFree(szValue);
				else
					delete[] szValue;
				szValue = NULL;
				/*string FieldValue = poSrcFeature->GetFieldAsString( iField );
				char* szValue = ToUTF8(FieldValue.data());
				poDestFeature->SetField( iDstField, szValue );
				CPLFree(szValue);*/
			}
			else if( !bForgiving )
			{
				//VSIFree(panMap);
				return OGRERR_FAILURE;
			}
			break;
		}
	}
	//VSIFree(panMap);
	//int s = panMap[0];
	//panMap = NULL;
	panMap.clear();
	return OGRERR_NONE;
}

OGRLayer*  CreateSymbolReferenceLayer(OGRDataSource* pDestSource,OGRSpatialReference* pSpatial)
{
	OGRLayer* poSymLayer = pDestSource->CreateLayer( "symbol_reference", NULL,
		wkbUnknown, NULL );
	if(poSymLayer == NULL)
		return NULL;

	OGRField oField;
	oField.String = "featureclass";
	OGRFieldDefn oScopeDef("",OFTString) ;
	oScopeDef.SetName("reference_scope");
	//oScopeDef.SetNullable(false);
	oScopeDef.SetType(OFTString);
	oScopeDef.SetDefault(&oField);
	poSymLayer->CreateField(&oScopeDef);

	OGRFieldDefn oTableDef("",OFTString) ;
	oTableDef.SetName("table_name");
	//oTableDef.SetNullable(true);
	oTableDef.SetType(OFTString);
	poSymLayer->CreateField(&oTableDef);

	OGRFieldDefn oRowidDef("",OFTString) ;
	oRowidDef.SetName("row_id");
	//oRowidDef.SetNullable(true);
	oRowidDef.SetType(OFTInteger);
	poSymLayer->CreateField(&oRowidDef);

	OGRFieldDefn oUriDef("",OFTString) ;
	oUriDef.SetName("sd_standard_uri");
	//oUriDef.SetNullable(true);
	oUriDef.SetType(OFTString);
	poSymLayer->CreateField(&oUriDef);

	OGRFieldDefn oFilterDef("",OFTString) ;
	oFilterDef.SetName("filter");
	//oFilterDef.SetNullable(false);
	oFilterDef.SetType(OFTString);
	poSymLayer->CreateField(&oFilterDef);

	OGRFieldDefn oSymbolIDDef("",OFTString) ;
	oSymbolIDDef.SetName("symbol_id");
	//oSymbolIDDef.SetNullable(false);
	oSymbolIDDef.SetType(OFTString);
	poSymLayer->CreateField(&oSymbolIDDef);

	return poSymLayer;

}

bool  SuAddonBase::CopyOtherLayers(OGRDataSource* pSrcSource, OGRDataSource* pDestSource,const string& strAnnoName,int nAnnoIdx ,enCodeTrans enCode, bool isGDB)
{
	if(strAnnoName.empty())
		return false;
	if(pSrcSource == NULL || pDestSource == NULL)
		return false;
	//char* szGBK = FromUTF8(strAnnoName.data());
	OGRLayer* poSrcLayer = pSrcSource->GetLayer(nAnnoIdx);
	if(pSrcSource == NULL)
		return false;
//	CPLFree(szGBK);
	OGRLayer* pSymbolLayer = CreateSymbolLayer(pDestSource,poSrcLayer->GetSpatialRef());
	OGRLayer* pReferLayer = CreateSymbolReferenceLayer(pDestSource,poSrcLayer->GetSpatialRef());
	
	OGRLayer* poDstLayer = pDestSource->CreateLayer( strAnnoName.data(), NULL, wkbPolygon, NULL );

	OGRFeatureDefn *poSrcDefn = poSrcLayer->GetLayerDefn();
	int         nSrcFieldCount = poSrcDefn->GetFieldCount();
	int         nDstFieldCount = 0;
	int         iField;
	vector<string> vec_FieldsName;
	
	// Initialize the index-to-index map to -1's

	/* Caution : at the time of writing, the MapInfo driver */
	/* returns NULL until a field has been added */
	OGRFeatureDefn* poDstFDefn = poDstLayer->GetLayerDefn();
	if (poDstFDefn)
		nDstFieldCount = poDstFDefn->GetFieldCount();    
	for( iField = 0; iField < nSrcFieldCount; iField++ )
	{
		OGRFieldDefn* poSrcFieldDefn = poSrcDefn->GetFieldDefn(iField);
		string strFieldName = poSrcFieldDefn->GetNameRef();
		char* szName = (char*)strFieldName.data();
		if(stricmp(strFieldName.data(),"TestString")==0 )
		{
			strFieldName = "annotaionValue";
		}
		if(isGDB)
		{
			if(iField < vec_FieldsName.size())
				strFieldName = vec_FieldsName[iField];
			else
			{
				char* czName = FromUTF8(strFieldName.data());
				strFieldName = czName;
				CPLFree(czName);
			}
		}

		switch (enCode)
		{
		case UTF8ToUTF8:
			break;
		case GBKToGBK:
			break;
		case UTF8ToGBK:
			szName = FromUTF8(strFieldName.data());
			break;
		case GBKToUTF8:
			szName = ToUTF8(strFieldName.data());
			break;
		}
		
		OGRFieldDefn oFieldDefn( poSrcFieldDefn );
		
		if(isGDB )
		{
			poSrcFieldDefn->SetName(szName);
		}
		oFieldDefn.SetName(szName);
		if(enCode == UTF8ToGBK ||
			enCode == GBKToUTF8)
			CPLFree(szName);
		/* The field may have been already created at layer creation */
		int iDstField = -1;
		if (poDstFDefn)
			iDstField = poDstFDefn->GetFieldIndex(oFieldDefn.GetNameRef());
		if (iDstField >= 0)
		{
			
		}
		else if (poDstLayer->CreateField( &oFieldDefn ) == OGRERR_NONE)
		{
			/* now that we've created a field, GetLayerDefn() won't return NULL */
			if (poDstFDefn == NULL)
				poDstFDefn = poDstLayer->GetLayerDefn();

			/* Sanity check : if it fails, the driver is buggy */
			if (poDstFDefn != NULL &&
				poDstFDefn->GetFieldCount() != nDstFieldCount + 1)
			{
				CPLError(CE_Warning, CPLE_AppDefined,
					"The output driver has claimed to have added the %s field, but it did not!",
					oFieldDefn.GetNameRef() );
			}
			else
			{
				
				nDstFieldCount ++;
			}
			
		}
	}

	/* -------------------------------------------------------------------- */
	/*      Create geometry fields.                                         */
	/* -------------------------------------------------------------------- */
	if( poSrcDefn->GetGeomFieldCount() > 1 &&
		pDestSource->TestCapability(ODsCCreateGeomFieldAfterCreateLayer) )
	{
		int nSrcGeomFieldCount = poSrcDefn->GetGeomFieldCount();
		for( iField = 0; iField < nSrcGeomFieldCount; iField++ )
		{
			poDstLayer->CreateGeomField( poSrcDefn->GetGeomFieldDefn(iField) );
		}
	}
	OGRFeature  *poFeature;
	
	poSrcLayer->ResetReading();
	
	int idx = 0;
	while((poFeature = poSrcLayer->GetNextFeature())!=NULL)
	{
		OGRFeature      *poDstFeature = NULL;
		if( poFeature == NULL )
			break;
		CPLErrorReset();
		poDstFeature = OGRFeature::CreateFeature( poDstLayer->GetLayerDefn() );
		OGRFeature* pSymbolFea = OGRFeature::CreateFeature( pSymbolLayer->GetLayerDefn() );
		OGRFeature* pReferenceFea = OGRFeature::CreateFeature( pReferLayer->GetLayerDefn());
		if( SetFieldsFrom(poFeature,poDstFeature,true,enCode) != OGRERR_NONE )
		{
			OGRFeature::DestroyFeature( poFeature );
			continue;
			//return poDstLayer;
		}
		pSymbolFea->SetFID(poFeature->GetFID());
		pSymbolFea->SetField("type","Text");
		pSymbolFea->SetField("sd_standard_uri","http://schemas.opengeospatial.net/se");
		pSymbolFea->SetField("mime_type","application/octet-stream");
		int nIdx = poFeature->GetFieldIndex("Element");
		if(nIdx == -1)
			nIdx = poFeature->GetFieldIndex("gw_symbol");
		if(nIdx != -1)
			pSymbolFea->SetField("symboldata",poFeature->GetFieldAsString(nIdx));
		if(pSymbolLayer->CreateFeature(pSymbolFea) != OGRERR_NONE)
		{
			
			OGRFeature::DestroyFeature(pSymbolFea);
			OGRFeature::DestroyFeature(pReferenceFea);
			OGRFeature::DestroyFeature( poFeature );
			OGRFeature::DestroyFeature( poDstFeature );
			continue;
		}


		pReferenceFea->SetField("reference_scope","row");
		pReferenceFea->SetField("table_name",strAnnoName.data());
		/*if(enCode == UTF8ToGBK || enCode == GBKToUTF8)
			CPLFree(szValue);*/
		pReferenceFea->SetField("row_id",poFeature->GetFID());
		pReferenceFea->SetField("symbol_id",poFeature->GetFID());
		if(pReferLayer->CreateFeature(pReferenceFea) != OGRERR_NONE)
		{
			OGRFeature::DestroyFeature(pSymbolFea);
			OGRFeature::DestroyFeature(pReferenceFea);
			OGRFeature::DestroyFeature( poFeature );
			OGRFeature::DestroyFeature( poDstFeature );
			continue;
		}
		//poFeature->GetFieldAsString("Element");
		//pSymbolFea->SetFID()
		
		poDstFeature->SetFID( poFeature->GetFID() );
		CPLErrorReset();
		if( poDstLayer->CreateFeature( poDstFeature ) != OGRERR_NONE )
		{
			OGRFeature::DestroyFeature(pSymbolFea);
			OGRFeature::DestroyFeature(pReferenceFea);
			OGRFeature::DestroyFeature( poFeature );
			OGRFeature::DestroyFeature( poDstFeature );
			continue;
		}
		OGRFeature::DestroyFeature(pSymbolFea);
		OGRFeature::DestroyFeature(pReferenceFea);
		OGRFeature::DestroyFeature( poFeature );
		OGRFeature::DestroyFeature( poDstFeature );
	
	}

	return true;
}

OGRLayer*  SuAddonBase::CreateMetadataReferenceLayer(OGRDataSource* pDestSource,OGRSpatialReference* pSpatial)
{
	OGRLayer* poSymLayer = pDestSource->CreateLayer( "Meatadata_Reference", pSpatial,
		wkbNone, NULL );
	if(poSymLayer == NULL)
		return NULL;

	OGRFieldDefn oScopeDef("",OFTString) ;
	oScopeDef.SetName("reference_scope");
	//oTypeDef.SetNullable(false);
	oScopeDef.SetType(OFTString);
	poSymLayer->CreateField(&oScopeDef);

	OGRFieldDefn oNameDef("",OFTString) ;
	oNameDef.SetName("table_Name");
	//oNameDef.SetNullable(true);
	oNameDef.SetType(OFTString);
	poSymLayer->CreateField(&oNameDef);

	OGRFieldDefn oColDef("",OFTString) ;
	oColDef.SetName("column_name");
	//oNameDef.SetNullable(true);
	oColDef.SetType(OFTString);
	poSymLayer->CreateField(&oColDef);

	OGRFieldDefn oRowIDDef("",OFTString) ;
	oRowIDDef.SetName("row_id_value");
	//oNameDef.SetNullable(true);
	oRowIDDef.SetType(OFTInteger);
	poSymLayer->CreateField(&oRowIDDef);

	OGRFieldDefn oTimeDef("",OFTString) ;
	oTimeDef.SetName("timestamp");
	//oNameDef.SetNullable(true);
	oTimeDef.SetType(OFTString);
	poSymLayer->CreateField(&oTimeDef);

	OGRFieldDefn oMDDef("",OFTString);
	oMDDef.SetName("md_file_id");
	//oMimeDef.SetNullable(false);
	oMDDef.SetType(OFTInteger);
	poSymLayer->CreateField(&oMDDef);

	OGRFieldDefn oParentDef("",OFTString) ;
	oParentDef.SetName("md_parent_id");
	//oSymbolDef.SetNullable(false);
	oParentDef.SetType(OFTInteger);
	poSymLayer->CreateField(&oParentDef);

	return poSymLayer;

}

OGRLayer*  CreateMetadataLayer(OGRDataSource* pDestSource,OGRSpatialReference* pSpatial)
{
	OGRLayer* poSymLayer = pDestSource->CreateLayer( "Meatadata", pSpatial,
		wkbNone, NULL );
	if(poSymLayer == NULL)
		return NULL;

	OGRFieldDefn oScopeDef("",OFTString) ;
	oScopeDef.SetName("md_scope");
	//oTypeDef.SetNullable(false);
	oScopeDef.SetType(OFTString);
	poSymLayer->CreateField(&oScopeDef);

	OGRFieldDefn oURIDef("",OFTString) ;
	oURIDef.SetName("md_standard_URI");
	//oNameDef.SetNullable(true);
	oURIDef.SetType(OFTString);
	poSymLayer->CreateField(&oURIDef);

	OGRField oField ;
	oField.String = "text/xml";
	OGRFieldDefn oMimeDef("",OFTString);
	oMimeDef.SetName("mime_type");
	//oMimeDef.SetNullable(false);
	oMimeDef.SetDefault(&oField);
	oMimeDef.SetType(OFTString);
	poSymLayer->CreateField(&oMimeDef);

	OGRFieldDefn ometadataDef("",OFTString) ;
	ometadataDef.SetName("metadata");
	//oSymbolDef.SetNullable(false);
	ometadataDef.SetType(OFTString);
	ometadataDef.SetWidth(10240);
	poSymLayer->CreateField(&ometadataDef);

	return poSymLayer;

}

OGRwkbGeometryType  GetGeometryType(OGRLayer* pSrc)
{
	if(pSrc == NULL)
		return wkbNone;

	pSrc->ResetReading();
	OGRFeature  *poFeature;
	while((poFeature = pSrc->GetNextFeature())!=NULL)
	{
		OGRGeometry* Geometry = poFeature->GetGeometryRef();
		if(Geometry == NULL)
			continue;
		OGRwkbGeometryType eOGRType = Geometry->getGeometryType();
		int Dimension = Geometry->getCoordinateDimension();
		/*if(Dimension == 3 || Dimension > 3)
		{
			eOGRType = (OGRwkbGeometryType)(((int) eOGRType) | wkb25DBit);
			return eOGRType;
		}
		else
		{*/
			return eOGRType;
		//}
	}
	return wkbNone;
}

bool  SuAddonBase::RegisterTable(sqlite3* hDB,const string& strTableName)
{
	CPLString osCommand;

	char *pszErrMsg = NULL;
	sqlite3_stmt* pStmt = NULL;
	const char* pszTail = NULL;
	int rc = 0;
	if (SQLITE_OK != rc)
	{
		if(hDB != NULL)
			sqlite3_close(hDB);
		return false;
	}
	char * pszSQL = sqlite3_mprintf(
		"INSERT INTO gpkg_contents "
		"(table_name,data_type,identifier,last_change,srs_id)"
		" VALUES "
		"('%q','features','%q',strftime('%%Y-%%m-%%dT%%H:%%M:%%fZ',CURRENT_TIMESTAMP),%d)",
		strTableName.data(), strTableName.data(), 0);
	rc = sqlite3_exec( hDB, pszSQL, NULL, NULL, &pszErrMsg );
	if( rc != SQLITE_OK )
	{

		sqlite3_free( pszErrMsg );
		return false;
	}
	pszSQL = sqlite3_mprintf(
		"INSERT INTO gpkg_geometry_columns "
		"(table_name,column_name,geometry_type_name,srs_id,z,m)"
		" VALUES "
		"('%q','%q','%q',%d,%d,%d)",
		strTableName.data(),"","",
		0,0,0);
	rc = sqlite3_exec( hDB, pszSQL, NULL, NULL, &pszErrMsg );
	if( rc != SQLITE_OK )
	{

		sqlite3_free( pszErrMsg );
		return false;
	}
	sqlite3_free(pszSQL);
	sqlite3_free( pszErrMsg );

	return true;
}

bool   SuAddonBase::CreateTable(sqlite3* hDB)
{
	CPLString osCommand;
	char *pszErrMsg = NULL;
	sqlite3_stmt* pStmt = NULL;
	const char* pszTail = NULL;
	int rc = 0;

	if (SQLITE_OK != rc)
	{
		if(hDB != NULL)
			sqlite3_close(hDB);
		return false;
	}
	osCommand =
		"CREATE TABLE Metadata ("
		"     fid INTEGER PRIMARY KEY AUTOINCREMENT, "
		"     md_scope VARCHAR, "
		"     md_standard_URI VARCHAR, "
		"     mime_type VARCHAR, "
		"     metadata TEXT)";
	rc = sqlite3_exec( hDB, osCommand, NULL, NULL, &pszErrMsg );
	if( rc != SQLITE_OK )
	{

		sqlite3_free( pszErrMsg );
		return false;
	}
	sqlite3_free( pszErrMsg );
	osCommand =
		"CREATE TABLE Meatadata_Reference ("
		"     fid INTEGER PRIMARY KEY AUTOINCREMENT, "
		"     reference_scope VARCHAR, "
		"     table_Name VARCHAR, "
		"     column_name VARCHAR, "
		"     row_id_value INTEGER,"
		"     timestamp VARCHAR,"
		"     md_file_id  INTEGER,"
		"     md_parent_id INTEGER)";
	rc = sqlite3_exec( hDB, osCommand, NULL, NULL, &pszErrMsg );
	if( rc != SQLITE_OK )
	{
		sqlite3_free( pszErrMsg );
		return false;
	}
	sqlite3_free( pszErrMsg );
	return true;
}


string  SuAddonBase::SaveXML(const XERCES_CPP_NAMESPACE::DOMNode* pNode, bool bPrettyPrint)
{
	DOMLSSerializer* pSerializer = DOMImplementation::getImplementation()->createLSSerializer();
	if (bPrettyPrint && pSerializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
	{
		pSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
	}
	else
	{
		pSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, false);
	}

	XMLCh* pValue = pSerializer->writeToString(pNode);  
	char* pcstr = WcharToChar((wchar_t*)pValue);

	string strResult = pcstr;
	delete[] pcstr;
	return strResult;
}

bool  SuAddonBase::InnitMetadataTable(const string& strGPKGPath,const string& strPath)
{
	char *pszErrMsg = NULL;
	sqlite3* hDB = NULL;
	std::string strGPKG = strGPKGPath;
	char* szUtf8Conn = ToUTF8(strGPKG.data());
	int rc = sqlite3_open_v2(szUtf8Conn, &hDB, SQLITE_OPEN_READWRITE, NULL);
	delete[] szUtf8Conn;
	RegisterTable(hDB,"Metadata");
	RegisterTable(hDB,"Meatadata_Reference");
	CreateTable(hDB);
	string strXMLPath = strPath;

	DOMDocument *m_pDoc = Parse(strXMLPath);
	if(m_pDoc == NULL)
	{
		
		std::cout<<"转换失败"<<std::endl;
		return false;
	}
	std::string strMeta = SaveXML(m_pDoc,true);
	char * pszSQL = sqlite3_mprintf(
		"INSERT INTO Metadata "
		"(md_scope,md_standard_URI,mime_type,metadata)"
		" VALUES "
		"('dataset','http://schemas.opengeospatial.net/se','xml/text','%s')",
		strMeta.data());
	char* szSQL = ToUTF8(pszSQL);
	rc = sqlite3_exec( hDB, szSQL, NULL, NULL, &pszErrMsg );
	CPLFree(szSQL);
	if( rc != SQLITE_OK )
	{

		sqlite3_free( pszErrMsg );
		return false;
	}
	sqlite3_free(pszSQL);
	pszSQL = sqlite3_mprintf(
		"INSERT INTO Meatadata_Reference "
		"(reference_scope,md_file_id)"
		" VALUES "
		"('dataset','1')");

	 rc = sqlite3_exec( hDB, pszSQL, NULL, NULL, &pszErrMsg );
	if( rc != SQLITE_OK )
	{

		sqlite3_free( pszErrMsg );
		return false;
	}
	sqlite3_free(pszSQL);
	if(hDB != NULL)
		sqlite3_close(hDB);
}

int SuAddonBase::copyLayer(OGRLayer *poSrcLayer, 
								OGRLayer * poDstLayer,OGRDataSource* pDestSource, 
								enCodeTrans enCode,bool isGDB,int& nIndex,int& OID)
{
	OGRFeatureDefn *poSrcDefn = poSrcLayer->GetLayerDefn();
	if( poDstLayer == NULL )
		return false;

	/* -------------------------------------------------------------------- */
	/*      Add fields.  Default to copy all fields, and make sure to       */
	/*      establish a mapping between indices, rather than names, in      */
	/*      case the target datasource has altered it (e.g. Shapefile       */
	/*      limited to 10 char field names).                                */
	/* -------------------------------------------------------------------- */
	if(OID == 0)
	{
		int         nSrcFieldCount = poSrcDefn->GetFieldCount();
		int         nDstFieldCount = 0;
		int         iField;
		vector<string> vec_FieldsName;
		if(isGDB)
		{
			
		}
		
		// Initialize the index-to-index map to -1's

		/* Caution : at the time of writing, the MapInfo driver */
		/* returns NULL until a field has been added */
		OGRFeatureDefn* poDstFDefn = poDstLayer->GetLayerDefn();
		if (poDstFDefn)
			nDstFieldCount = poDstFDefn->GetFieldCount();    
		for( iField = 0; iField < nSrcFieldCount; iField++ )
		{
			OGRFieldDefn* poSrcFieldDefn = poSrcDefn->GetFieldDefn(iField);
			string strFieldName = poSrcFieldDefn->GetNameRef();
			char* szName = (char*)strFieldName.data();
			if(isGDB)
			{
				if(iField < vec_FieldsName.size())
					strFieldName = vec_FieldsName[iField];
				else
				{
					char* czName = FromUTF8(strFieldName.data());
					strFieldName = czName;
					CPLFree(czName);
				}
			}

			switch (enCode)
			{
			case UTF8ToUTF8:
				break;
			case GBKToGBK:
				break;
			case UTF8ToGBK:
				szName = FromUTF8(strFieldName.data());
				break;
			case GBKToUTF8:
				szName = ToUTF8(strFieldName.data());
				break;
			}
			
			
			/*if(!bIsUTF8)
				szName = ToUTF8(strFieldName.data());*/
			//poSrcFieldDefn->SetName(szName);
			OGRFieldDefn oFieldDefn( poSrcFieldDefn );
			if(isGDB )
			{
				poSrcFieldDefn->SetName(szName);
			}
			oFieldDefn.SetName(szName);
			if(enCode == UTF8ToGBK ||
				enCode == GBKToUTF8)
				CPLFree(szName);
			/* The field may have been already created at layer creation */
			int iDstField = -1;
			if (poDstFDefn)
				iDstField = poDstFDefn->GetFieldIndex(oFieldDefn.GetNameRef());
			if (iDstField >= 0)
			{
				
			}
			else if (poDstLayer->CreateField( &oFieldDefn ) == OGRERR_NONE)
			{
				/* now that we've created a field, GetLayerDefn() won't return NULL */
				if (poDstFDefn == NULL)
					poDstFDefn = poDstLayer->GetLayerDefn();

				/* Sanity check : if it fails, the driver is buggy */
				if (poDstFDefn != NULL &&
					poDstFDefn->GetFieldCount() != nDstFieldCount + 1)
				{
					CPLError(CE_Warning, CPLE_AppDefined,
						"The output driver has claimed to have added the %s field, but it did not!",
						oFieldDefn.GetNameRef() );
				}
				else
				{
					
					nDstFieldCount ++;
				}
				/*if (poDstFDefn)
					iDstField = poDstFDefn->GetFieldIndex(oFieldDefn.GetNameRef());
				if(iDstField == -1)
				{
					string strName = oFieldDefn.GetNameRef();
					if(strName.length() > 10)
					{
						strName = strName.substr(0,10);
						poSrcFieldDefn->SetName(strName.data());
					}
				}*/
			}
		}

		/* -------------------------------------------------------------------- */
		/*      Create geometry fields.                                         */
		/* -------------------------------------------------------------------- */
		if( poSrcDefn->GetGeomFieldCount() > 1 &&
			pDestSource->TestCapability(ODsCCreateGeomFieldAfterCreateLayer) )
		{
			int nSrcGeomFieldCount = poSrcDefn->GetGeomFieldCount();
			for( iField = 0; iField < nSrcGeomFieldCount; iField++ )
			{
				poDstLayer->CreateGeomField( poSrcDefn->GetGeomFieldDefn(iField) );
			}
		}
	}


	/* -------------------------------------------------------------------- */
	/*      Check if the destination layer supports transactions and set a  */
	/*      default number of features in a single transaction.             */
	/* -------------------------------------------------------------------- */
	

	/* -------------------------------------------------------------------- */
	/*      Transfer features.                                              */
	/* -------------------------------------------------------------------- */
	OGRFeature  *poFeature;

	
	if(OID == 0)
		poSrcLayer->ResetReading();
	else
	{
		string OIDName = poSrcLayer->GetFIDColumn();
		char czFilter[100];
		memset(czFilter,'\0',100*sizeof(char));
		sprintf_s(czFilter,20*sizeof(char),"fid > %d",OID);
	    OGRErr err = poSrcLayer->SetAttributeFilter(czFilter);

		//poSrcLayer->SetNextByIndex(OID);
	}
	int idx = 0;
	while((poFeature = poSrcLayer->GetNextFeature())!=NULL)
	{
		
		nIndex++;
		OGRFeature      *poDstFeature = NULL;
		if( poFeature == NULL )
			break;
		CPLErrorReset();
		poDstFeature = OGRFeature::CreateFeature( poDstLayer->GetLayerDefn() );

		if( SetFieldsFrom(poFeature,poDstFeature,true,enCode) != OGRERR_NONE )
		{
			OGRFeature::DestroyFeature( poFeature );
			continue;
			//return poDstLayer;
		}

		poDstFeature->SetFID( poFeature->GetFID() );
		CPLErrorReset();
		if( poDstLayer->CreateFeature( poDstFeature ) != OGRERR_NONE )
		{
			OGRFeature::DestroyFeature( poDstFeature );
			//CPLFree(panMap);
			continue;
			//return poDstLayer;
		}
		/*if(idx % nGroupTransactions == 0)
		{
			poDstLayer->CommitTransaction();
			poDstLayer->StartTransaction();
		}*/
		if(nIndex == 500000)
		{
			nIndex = poFeature->GetFID();
			OGRFeature::DestroyFeature( poFeature );
			OGRFeature::DestroyFeature( poDstFeature );
		//	poDstLayer->CommitTransaction();
			return 0;
		}
		OGRFeature::DestroyFeature( poFeature );
		OGRFeature::DestroyFeature( poDstFeature );
		idx++;
	}
	return 1;
}

bool SuAddonBase::copyDataset(const string& strPath,const string& strOutPath, 
								  const string& strProvier,GIS::Progress * nProgress)
{
	string m_strResult = "转换失败";
	bool bIsUTF8 = true;
	bool bIsImport = false;
	bool bIsOutGDB = false;

	if(nProgress != NULL)
		nProgress->OnLog("开始转换",GIS::LogLevel::eInfo);
	else
		std::cout<<"开始转换"<<std::endl;
	OGRRegisterAll();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");

	enCodeTrans  enCode = UTF8ToUTF8;
	string strExt = "";
	if(strPath.find_last_of(".")!=-1)
		strExt = strPath.substr(strPath.find_last_of("."),strPath.length()-strPath.find_last_of("."));

	
	OGRSFDriver* pDriver1 = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName("SQLite");
	string strOutExt = "";
	if(strOutPath.find_last_of(".")!=-1)
		strOutExt = strOutPath.substr(strOutPath.find_last_of("."),strOutPath.length()-strOutPath.find_last_of("."));


	if(stricmp(strOutExt.data(),".shp")==0||
		stricmp(strOutExt.data(),"")==0)
	{
		CPLSetConfigOption( "SHAPE_ENCODING", "" );
		enCode = UTF8ToGBK;
	}
	if(stricmp(strOutExt.data(),".gdb")==0)
	{
		bIsOutGDB = true;
		CPLSetConfigOption( "LAUNDER_RESERVED_KEYWORDS", "" );
	}
	if(stricmp(strExt.data(),".mdb")==0 /*&&
		stricmp(strExt.data(),".shp")!=0 && strExt != ""*/)
	{
		enCode = GBKToUTF8;
		bIsUTF8 = false;
	}
	
	OGRSFDriver*	m_poDriver  = NULL;
	OGRDataSource*	m_poDS = NULL;
	bool isGDB = false;
	/*OGRSFDriver* pDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName("FileGDB");
	m_poDS = pDriver->Open(strPath.c_str(), false);*/
	
	string strInPath = "";
	if(stricmp(strExt.data(),".gdb")==0 ||
		stricmp(strExt.data(),".shp")==0 ||
		stricmp(strExt.data(),"")==0 ||
		stricmp(strExt.data(),".gpkg")==0||
		stricmp(strExt.data(),".db")==0||
		stricmp(strExt.data(),".gwdb")==0)
	{
		if(stricmp(strExt.data(),".gdb")==0)
			isGDB = true;
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","YES");
		char* szPath = ToUTF8(strPath.c_str());
		strInPath = szPath;
		CPLFree(szPath);
	}
	else
	{
		strInPath = strPath;
		
	}
	
	m_poDS = OGRSFDriverRegistrar::Open(strInPath.c_str(), false); //true时才能写操作
	
	

	//m_poDS = OGRSFDriverRegistrar::Open(strPath.c_str(), false); //true时才能写操作
	if(m_poDS == NULL)
	{
		if(nProgress != NULL)
			nProgress->OnLog("转换失败",GIS::LogLevel::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return m_strResult.data();
	}
	
	m_poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(strProvier.data());
	if(m_poDriver == NULL)
	{
		if(nProgress != NULL)
			nProgress->OnLog("该格式不支持",GIS::LogLevel::eError);
		else
			std::cout<<"该格式不支持"<<std::endl;
		return m_strResult.data();
	}
//	m_poDriver->CopyDataSource(m_poDS,strOutPath.data(),NULL);
	OGRDataSource* poODS = NULL;
	OGRLayer* pLastLayer = NULL;
	bool bInTrans = false;
	string strAnnoName = "";
	int nDestLayerIdx = -1;
	int nAnnoLayerIdx = -1;
	try
	{
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","YES");
		char* szPath = ToUTF8(strOutPath.data());

		//先尝试打开，如果没有就创建
		poODS = m_poDriver->Open( szPath, true);
		if( poODS == NULL )
		{
			poODS = m_poDriver->CreateDataSource( szPath, NULL);
			if (poODS == NULL)
			{
				CPLFree(szPath);
				if(nProgress != NULL)
					nProgress->OnLog("转换失败",GIS::LogLevel::eError);
				else
					std::cout<<"转换失败"<<std::endl;
				return false;
			}
		}
		/*
		
		poODS = m_poDriver->CreateDataSource( szPath, NULL);
		CPLFree(szPath);
		if( poODS == NULL )
		{
			if(nProgress != NULL)
				nProgress->OnLog("转换失败",GIS::LogLevel::eError);
			else
				std::cout<<"转换失败"<<std::endl;
			return false;
		}
		*/
		int nIndex = 0;
		int OID = 0;
		int nCount =  m_poDS->GetLayerCount();
		for( int iLayer = 0; iLayer < nCount; iLayer++ )
		{
			
			OGRLayer        *poLayer = m_poDS->GetLayer(iLayer);
			
			string strName =  poLayer->GetLayerDefn()->GetName();
#if 1
			string strSkip = "";
			if(strName.find_last_of("_")!=-1)
				strSkip = strName.substr(0,strName.find_first_of("_"));
			if(stricmp(strSkip.data(),"DELTA")==0)
			{
				continue;
			}

#endif
			string GBKName = strName;
			if(stricmp(strExt.data(),".mdb")!=0)
			{
				char* cName = FromUTF8(strName.data());
				GBKName = cName;
				CPLFree(cName);
			}
			
			string strDebug = "数据表 ";
			strDebug = strDebug + GBKName;

			string strDes = "开始拷贝 "+GBKName;
			if(nProgress != NULL)
				nProgress->OnLog(strDes.data(),GIS::LogLevel::eInfo);
			else
				std::cout<<strDes.data()<<std::endl;

			if( poLayer == NULL )
				continue;
			char* szName = (char*)strName.data();
			
			if(!bIsUTF8)
			{
				szName = ToUTF8(strName.data());
			}
			
			if(strstr(strupr((char*)(GBKName.data())),"注记") ||
				strstr(strupr((char*)(GBKName.data())),"anno"))
			{
				nAnnoLayerIdx = iLayer;
				strAnnoName = szName;
				continue;
			}
			OGRFeatureDefn *poSrcDefn = poLayer->GetLayerDefn();
			OGRLayer *poDstLayer = NULL;

			/* -------------------------------------------------------------------- */
			/*      Create the layer.                                               */
			/* -------------------------------------------------------------------- */
			if( !poODS->TestCapability( ODsCCreateLayer ) )
			{
				CPLError( CE_Failure, CPLE_NotSupported, 
					"This datasource does not support creation of layers." );
				return false;
			}

			
			CPLErrorReset();
			if( poSrcDefn->GetGeomFieldCount() > 1 &&
				poODS->TestCapability(ODsCCreateGeomFieldAfterCreateLayer) )
			{
				strAnnoName = szName;
				continue;
			//	poDstLayer = poODS->CreateLayer( szName, NULL, wkbNone, NULL );
			}
			else
			{
				OGRwkbGeometryType GeoType = poSrcDefn->GetGeomType();
				if(GeoType == wkbNone || GeoType == wkbUnknown)
				{
					GeoType = GetGeometryType(poLayer);
				}
				if(bIsOutGDB)
				{
					poDstLayer = poODS->CreateLayer( szName, NULL,
						GeoType, NULL );
				}
				else
				{
					poDstLayer = poODS->CreateLayer( szName, poLayer->GetSpatialRef(),
						GeoType, NULL );
				}
				
			}
			if(!bIsUTF8)
				CPLFree(szName);
			int bCopied = -1;// gwAddonFunction::copyLayer(poLayer,poDstLayer,poODS,enCode,isGDB,nIndex,OID);
			if(poDstLayer!=NULL)
			{

				nDestLayerIdx++;
				if(bInTrans == false)
				{
					bInTrans = true;
					poDstLayer->StartTransaction();
				}
				OID = 0;
				
				while(bCopied != 1)
				{
					if(bCopied == -1)
						bCopied = copyLayer(poLayer,poDstLayer,poODS,enCode,isGDB,nIndex,OID);
					else if(bCopied == 0)
					{
						OGRDataSource::DestroyDataSource(m_poDS);
						//OGRDataSource::DestroyDataSource(poODS);
						//bInTrans = false;
						m_poDS = NULL;
					//	poODS = NULL;
						m_poDS = OGRSFDriverRegistrar::Open(strInPath.c_str(), false); //true时才能写操作
						//char* szPath1 = gwAddonFunction::ToUTF8(strOutPath.data());
						//poODS = m_poDriver->Open( szPath1, 1);
						//CPLFree(szPath1);
						OGRLayer* poLayer1 = m_poDS->GetLayer(iLayer);
						poDstLayer = poODS->GetLayer(nDestLayerIdx);
						/*if(poDstLayer != NULL)
						{
							bInTrans = true;
							poDstLayer->StartTransaction();
						}*/
						OID = nIndex;
						nIndex = 0;
						bCopied = copyLayer(poLayer1,poDstLayer,poODS,enCode,isGDB,nIndex,OID);
						/*if(bCopied == 0)
							bInTrans = false;
						else
						{
							bInTrans = true;
							pLastLayer = poDstLayer;
						}*/
					}
					
				}
				/*OGRLayer* pDesLayer = poODS->CopyLayer( poLayer, poLayer->GetLayerDefn()->GetName(), 
					NULL );*/
				if(bCopied)
				{
					strDebug = strDebug + " 转换成功!";
					if(nProgress != NULL)
						nProgress->OnLog(strDebug.data(),GIS::LogLevel::eInfo);
					else
						std::cout<<strDebug.data()<<std::endl;
				}
				else
				{
					strDebug = strDebug + " 转换失败!";
					if(nProgress != NULL)
						nProgress->OnLog(strDebug.data(),GIS::LogLevel::eError);
					else
						std::cout<<strDebug.data()<<std::endl;
				}
				
				pLastLayer = poDstLayer;
				/*if(iLayer == nCount - 1)
					poDstLayer->CommitTransaction();*/

			}
			else
			{
				strDebug = strDebug + " 创建失败！";
				if(nProgress != NULL)
					nProgress->OnLog(strDebug.data(),GIS::LogLevel::eError);
				else
					std::cout<<strDebug.data()<<std::endl;
			}
			
		}

		//pDesSource = m_poDriver->CopyDataSource(m_poDS,strOutPath.data());
	}
	catch (std::exception* e)
	{
	}
	if(stricmp(strExt.data(),".gpkg"))
	{
		CopyOtherLayers(m_poDS,poODS,strAnnoName,nAnnoLayerIdx,enCode,isGDB);

		string strXMLPath = strPath;

		if(strPath.find_last_of(".") != -1)
			strXMLPath = strXMLPath.replace(strXMLPath.find_last_of("."),strXMLPath.length() - strXMLPath.find_last_of("."),".xml");
		else
		{
			strXMLPath = strXMLPath + ".xml";
		}

		if(pLastLayer != NULL && bInTrans)
			pLastLayer->CommitTransaction();

		//InnitMetadataTable(strOutPath,strXMLPath);
	}
	OGRDataSource::DestroyDataSource(m_poDS);
	OGRDataSource::DestroyDataSource(poODS);
	
	m_strResult = "读取成功";
	if(nProgress != NULL)
		nProgress->OnLog(m_strResult.data(),GIS::LogLevel::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return true;
}
