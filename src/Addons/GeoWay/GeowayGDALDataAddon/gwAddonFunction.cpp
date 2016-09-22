#include "stdafx.h"
#include "gwAddonFunction.h"
#include "gwStandardMetaDataAnalysis.h"
#include "gwStandardMetaDataFactory.h"
#include <map>
#include <memory>
#include "xercesc/framework/LocalFileInputSource.hpp"
#include "OpenThreads/ScopedLock"
#include "OpenThreads/Mutex"
#include <fstream>  
#include <string>  
#include <iostream>  
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/stat.h>
#include <io.h>
//#include "D:/gdal-1.11.2/gcore/rasterio.cpp"
//char *w2c(char *pcstr,const wchar_t *pwstr, size_t len)
//{
//	int nlength=wcslen(pwstr);
//	int nbytes = WideCharToMultiByte( 0, 0,pwstr, nlength,NULL,0,NULL,NULL );    // we don't want to know if a character didn't make it through the translation
//	if(nbytes>len)   nbytes=len;
//	WideCharToMultiByte( 0, 0,pwstr,nlength,pcstr,nbytes,NULL,NULL );
//	return pcstr ;
//
//}

char* gwAddonFunction::ToUTF8(const char* src)
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

char* gwAddonFunction::FromUTF8(const char* src)
{
	wchar_t* wc = CPLRecodeToWChar(src,CPL_ENC_UTF8,"WCHAR_T");

	int Namelen = 0;  
	Namelen = WideCharToMultiByte(CP_ACP, 0, wc, -1, NULL, 0, NULL, NULL);  
	char* pszName = (char*)CPLCalloc(sizeof(char),Namelen+1);


	WideCharToMultiByte(CP_ACP, 0, wc, -1, pszName, Namelen, NULL,NULL); 
	return pszName;
}

char* gwAddonFunction::WcharToChar(const wchar_t* wc)   
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

wchar_t* gwAddonFunction::CharToWchar(const char* c)   
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
DOMDocument* gwAddonFunction::ParseByContent(const string& strContent)
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
string gwAddonFunction::SaveXML(const XERCES_CPP_NAMESPACE::DOMNode* pNode, bool bPrettyPrint)
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
bool gwAddonFunction::WriteToTraget(XMLFormatTarget* pTarget, const DOMNode* pNode, const char* szEncoding/* = "UTF-8"*/)
{
	try 
	{
		DOMImplementation* m_pImpl = DOMImplementation::getImplementation();
		DOMLSSerializer* pSerializer = m_pImpl->createLSSerializer();// new DOMLSSerializer(m_pImpl->createLSSerializer());
		DOMLSOutput* pLSOutput =m_pImpl->createLSOutput();
		pLSOutput->setByteStream(pTarget);

		bool bIncludeEncoding = XMLString::isValidEncName((wchar_t*)"UTF-8");
		if(bIncludeEncoding)
			pLSOutput->setEncoding((wchar_t*)(szEncoding));
		bool bRet = pSerializer->write(pNode, pLSOutput);
		//delete pSerializer;
		//delete pLSOutput;
		return bRet;
	}
	catch (xercesc::XMLException& error)
	{
		
	}
	catch (xercesc::SAXException& error)
	{
		
	}
	catch (xercesc::DOMException& error)
	{
		
	}

	return false;
}

DOMDocument* gwAddonFunction::Parse(const string& strFile)
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

void gwAddonFunction::getVectorImportParams(const char* strParameter,string& strProvider,string& strInPath,string& strOutPath,bool& bIsimport)
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
			/*if(strstr(strInPath.data(),".."))
			{
				char cInPath[246];
				sprintf(cInPath,"%ls//%ls",)
				strInPath = gwPath::Combine(gwPath::GetApplicationDir(),strInPath);
			}*/
		}
		if(stricmp(szdata,IN_GPKGPATH)==0 ||
			stricmp(szdata,OUT_GPKGPATH)==0 )
		{
			if(stricmp(szdata,IN_GPKGPATH)==0)
				bIsimport = false;
			char* szout = WcharToChar(pValueNode->getTextContent());
			strTempOut = szout;
			delete[] szout;
			/*if(!gwPath::IsAbsolutePath(strOutPath))
			{
				strOutPath = gwPath::Combine(gwPath::GetApplicationDir() , strOutPath);
			}*/
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
		if(stricmp(strExt.data(),".mdb")==0)
		{
			strProvider = "PGeo";
		}
		if(stricmp(strExt.data(),".gdb")==0)
		{
			strProvider = "FileGDB";
		}
		if(stricmp(strExt.data(),".shp")==0||
			strExt == "")
		{
			strProvider = "ESRI Shapefile";
		}
		if(stricmp(strExt.data(),".gwdb")==0)
		{
			strProvider = "SQLite";
		}
	}
} 


void gwAddonFunction::getRasterImportParams(const char* strParameter,string& strInFormat,string& strInPath,string& strOutPath,bool& bIsimport)
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
		/*string strdata = szdata;
		transform(szdata.begin(), szdata.end(), szdata.begin(), tolower); */
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
			/*if(strstr(strInPath.data(),".."))
			{
				char cInPath[246];
				sprintf(cInPath,"%ls//%ls",)
				strInPath = gwPath::Combine(gwPath::GetApplicationDir(),strInPath);
			}*/
		}
		if(stricmp(szdata,IN_GPKGPATH)==0 ||
			stricmp(szdata,OUT_GPKGPATH)==0 )
		{
			if(stricmp(szdata,IN_GPKGPATH)==0)
				bIsimport = false;
			char* szout = WcharToChar(pValueNode->getTextContent());
			strTempOut = szout;
			delete[] szout;
			/*if(!gwPath::IsAbsolutePath(strOutPath))
			{
				strOutPath = gwPath::Combine(gwPath::GetApplicationDir() , strOutPath);
			}*/
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
			/*	
	string strExt = strInPath.substr(strInPath.find_last_of("."),strInPath.length()-strInPath.find_last_of("."));
		string stroutExt = strOutPath.substr(strOutPath.find_last_of("."),strOutPath.length()-strOutPath.find_last_of("."));*/

		if (stricmp(strExt.data(),".img")==0)
		{
			strInFormat = "HFA";
		}
		if(stricmp(strExt.data(),".tif") == 0)
		{
			strInFormat = "GTiff";
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
	}
}
bool gwAddonFunction::WriteDEM(const char* inFile,const char* outFile,const ieSimpleRasterInfo& eInfo )
{
	ifstream in(inFile);  
	ofstream out(outFile);  
	string filename;  
	string line;  

	if(in) // 有该文件  
	{  
		int nLineIdx = 1;
		while (getline (in, line)) // line中不包括每行的换行符  
		{   
			if(line.find_first_of("[")==-1)
			{
				out << line << endl; // 输入到2.txt中
				nLineIdx++;
				continue;
			}
			int nFirstIdx = line.find_first_of("[");
			int nLastIdx  = line.find_first_of("]");
			if(nLineIdx == 4 || nLineIdx == 20 ||nLineIdx == 26||nLineIdx == 77||nLineIdx == 88||nLineIdx == 91||nLineIdx == 121)
				line.replace(nFirstIdx,nLastIdx,"国家基础地理信息中心");
			
			if(nLineIdx == 6)
			{
				time_t t = time(0); 
				char tmp[64]; 
				memset(tmp,64,64*sizeof(char));
				strftime( tmp, sizeof(tmp), "%Y%m%d",localtime(&t) ); 
				line.replace(nFirstIdx,nLastIdx,tmp);
			}
			if(nLineIdx == 12)
			{
				line.replace(nFirstIdx,nLastIdx,"一斗泉乡, J50E001001");
			}
			if(nLineIdx == 15)
			{
				line.replace(nFirstIdx,nLastIdx,"2015/11/12");
			}
			if(nLineIdx == 16)
				line.replace(nFirstIdx,nLastIdx,"2015版");
			if(nLineIdx == 17)
			{
				int nLast = line.find_last_of("]");
				line.replace(nFirstIdx,nLast,"199910完成生产，由国家基础地理信息中心于20110530进行了质量检查与验收，结论为合格");
			}
			if(nLineIdx == 23)
				line.replace(nFirstIdx,nLastIdx,"国家测绘地理信息局");
			if(nLineIdx == 29)
				line.replace(nFirstIdx,nLastIdx,"一斗泉乡, 1:50000数字高程模型, 国家1:50000数据库更新工程");
			if(nLineIdx == 32)
				line.replace(nFirstIdx,nLastIdx,"机密");
			if(nLineIdx == 33)
				line.replace(nFirstIdx,nLastIdx,"GB/T 13923-2006");
			if(nLineIdx == 35 ||nLineIdx == 117)
				line.replace(nFirstIdx,nLastIdx,"GRID");
			if(nLineIdx == 37)
				line.replace(nFirstIdx,nLastIdx,"3.1");
			if(nLineIdx == 38)
				line.replace(nFirstIdx,nLastIdx,"10");
			if(nLineIdx == 39)
				line.replace(nFirstIdx,nLastIdx,"高山地");
			if(nLineIdx == 40)
				line.replace(nFirstIdx,nLastIdx,"等高线构TIN后内插");
			if(nLineIdx == 41)
				line.replace(nFirstIdx,nLastIdx,"线性内插");
			if(nLineIdx == 42)
				line.replace(nFirstIdx,nLastIdx,"775*886");
			if(nLineIdx == 43)
				line.replace(nFirstIdx,nLastIdx,"1");
			if(nLineIdx == 45||nLineIdx==46||nLineIdx == 47 || nLineIdx == 48)
				line.replace(nFirstIdx,nLastIdx,"已接");
			if(nLineIdx == 53)
				line.replace(nFirstIdx,nLastIdx,"25");
			if(nLineIdx == 59)
			{
				char left[20];
				memset(left,20,20*sizeof(char));
				sprintf_s(left,20*sizeof(char),"%0.5f",eInfo.left);
				line.replace(nFirstIdx,nLastIdx,left);
			}
			if(nLineIdx == 60)
			{
				char left[20];
				memset(left,20,20*sizeof(char));
				sprintf_s(left,20*sizeof(char),"%0.5f",eInfo.right);
				line.replace(nFirstIdx,nLastIdx,left);
			}
			if(nLineIdx == 61)
			{
				char left[20];
				memset(left,20,20*sizeof(char));
				sprintf_s(left,20*sizeof(char),"%0.5f",eInfo.bottom);
				line.replace(nFirstIdx,nLastIdx,left);
			}
			if(nLineIdx == 62)
			{
				char left[20];
				memset(left,20,20*sizeof(char));
				sprintf_s(left,20*sizeof(char),"%0.5f",eInfo.top);
				line.replace(nFirstIdx,nLastIdx,left);
			}
			if(nLineIdx == 64)
				line.replace(nFirstIdx,nLastIdx,"1:5万更新地形要素数据");
			if(nLineIdx == 65)
				line.replace(nFirstIdx,nLastIdx,"2006-08");
			//处理空间参考
			std::string strWKT = eInfo.m_strProjectionRef;
			OGRSpatialReference oSRS;
			char* szWKT = (char*)strWKT.data();
			OGRErr err = oSRS.importFromWkt(&szWKT);
			bool bPro = true;
			char *pszGeoSRSName = "2000国家大地坐标系";
			char *pszPROSRSName = "2000国家大地坐标系";
			char *pszProjection = "高斯-克吕格投影";
			char *pszSPHEROID = "2000国家大地坐标系椭球体";
			char meridian[20];
			memset(meridian,20,20*sizeof(char));
			string degree = "6";
			char zone[10];
			memset(zone,10,10*sizeof(char));
		
			char Major[20];
			memset(Major,20,20*sizeof(char));
			char szRatio[20];
			memset(szRatio,20,20*sizeof(char));
			OGRSpatialReference *poGeogSRS = NULL;
			if(err != OGRERR_NONE)
				bPro = false;
			else
			{
				if(oSRS.IsProjected() == true)
				{
					poGeogSRS = oSRS.CloneGeogCS();
					pszGeoSRSName= (char*)poGeogSRS->GetAttrValue("GEOGCS");
					pszPROSRSName= (char*)oSRS.GetAttrValue("PROJCS");


					/*string strProName = pszPROSRSName;
					int ntempIdx = strProName.find_first_of("-");
					string degree = strProName.substr(ntempIdx-1,ntempIdx);*/

					pszProjection= (char*)oSRS.GetAttrValue("PROJECTION");
					double dmeriDian = oSRS.GetProjParm(SRS_PP_CENTRAL_MERIDIAN); 
					double dzone = oSRS.GetProjParm(SRS_PP_ZONE); 
					sprintf_s(zone,20,"%d",dzone);
					sprintf_s(meridian,20,"%0.1f",dmeriDian);
					pszSPHEROID = (char*)poGeogSRS->GetAttrValue( "GEOGCS|DATUM|SPHEROID" );

					double dMajor =	poGeogSRS->GetSemiMajor();
					sprintf_s(Major,20,"%0.1f",dMajor);

					double dMinor =	poGeogSRS->GetSemiMinor();
					sprintf_s(szRatio,20,"%0.1f",dMinor);
				}
				else	
				{
					poGeogSRS = oSRS.CloneGeogCS();
					pszGeoSRSName= (char*)poGeogSRS->GetAttrValue("GEOGCS");
			
					string strProName = pszPROSRSName;
					int ntempIdx = strProName.find_first_of("-");
					string degree = strProName.substr(ntempIdx-1,ntempIdx);

					pszProjection= (char*)poGeogSRS->GetAttrValue("PROJECTION");
					double dmeriDian = oSRS.GetProjParm(SRS_PP_CENTRAL_MERIDIAN); 
					double dzone = oSRS.GetProjParm(SRS_PP_ZONE); 
					sprintf_s(zone,20,"%d",dzone);
					sprintf_s(meridian,20,"%0.1f",dmeriDian);
					pszSPHEROID = (char*)poGeogSRS->GetAttrValue( "GEOGCS|DATUM|SPHEROID" );

					double dMajor =	poGeogSRS->GetSemiMajor();
					sprintf_s(Major,20,"%0.1f",dMajor);

					double dMinor =	poGeogSRS->GetSemiMinor();
					sprintf_s(szRatio,20,"%0.1f",dMinor);
				}
				

			}
			
			if(nLineIdx == 66)
				line.replace(nFirstIdx,nLastIdx,pszGeoSRSName);
			if(nLineIdx == 67)
				line.replace(nFirstIdx,nLastIdx,pszProjection);
			if(nLineIdx == 68)
				line.replace(nFirstIdx,nLastIdx,meridian);
			if(nLineIdx == 69)
				line.replace(nFirstIdx,nLastIdx,degree.data());
			if(nLineIdx == 70)
				line.replace(nFirstIdx,nLastIdx,"米");
			if(nLineIdx == 71 ||nLineIdx == 110)
				line.replace(nFirstIdx,nLastIdx,"正常高");
			if(nLineIdx == 72 ||nLineIdx == 109)
				line.replace(nFirstIdx,nLastIdx,"1985国家高程基准");
			if(nLineIdx == 73)
				line.replace(nFirstIdx,nLastIdx,"一斗泉乡");
			if(nLineIdx == 74)
				line.replace(nFirstIdx,nLastIdx,"J50E001001");
			if(nLineIdx == 75)
				line.replace(nFirstIdx,nLastIdx,"1140000-1141500");
			if(nLineIdx == 76)
				line.replace(nFirstIdx,nLastIdx,"0395000-0400000");
			if(nLineIdx == 78)
				line.replace(nFirstIdx,nLastIdx,"地貌要素、水系要素");
			if(nLineIdx == 79)
				line.replace(nFirstIdx,nLastIdx,"TERL、TERP、HYDA");
			if(nLineIdx == 84)
				line.replace(nFirstIdx,nLastIdx,"0.1");
			if(nLineIdx == 85)
				line.replace(nFirstIdx,nLastIdx,"接边达到精度要求");
			if(nLineIdx == 86)
				line.replace(nFirstIdx,nLastIdx,"201009");
			if(nLineIdx == 87||nLineIdx == 90)
				line.replace(nFirstIdx,nLastIdx,"合格");
			if(nLineIdx == 89)
				line.replace(nFirstIdx,nLastIdx,"20110606");
			if(nLineIdx == 92)
				line.replace(nFirstIdx,nLastIdx,"20110530");
			if(nLineIdx == 97||nLineIdx == 107)
				line.replace(nFirstIdx,nLastIdx,pszPROSRSName);
			if(nLineIdx == 99)
				line.replace(nFirstIdx,nLastIdx,degree.data());
			if(nLineIdx == 100)
				line.replace(nFirstIdx,nLastIdx,zone);
			if(nLineIdx == 101)
				line.replace(nFirstIdx,nLastIdx,meridian);
			if(nLineIdx == 102)
				line.replace(nFirstIdx,nLastIdx,pszSPHEROID);
			if(nLineIdx == 104)
				line.replace(nFirstIdx,nLastIdx,Major);
			if(nLineIdx == 105 || nLineIdx == 108)
				line.replace(nFirstIdx,nLastIdx,"米");
			if(nLineIdx == 106)
				line.replace(nFirstIdx,nLastIdx,szRatio);
			if(nLineIdx == 119)
				line.replace(nFirstIdx,nLastIdx,"DVD-ROM");
			if(nLineIdx == 124)
				line.replace(nFirstIdx,nLastIdx,"海淀区莲花池西路28号");
			if(nLineIdx == 125)
				line.replace(nFirstIdx,nLastIdx,"北京市");
			if(nLineIdx == 126)
				line.replace(nFirstIdx,nLastIdx,"100830");
			if(nLineIdx == 127)
				line.replace(nFirstIdx,nLastIdx,"xinxi@nsdi.gov.cn");
			if(nLineIdx == 129)
				line.replace(nFirstIdx,nLastIdx,"http://ngcc.sbsm.gov.cn");
			if(nLineIdx == 130)
				line.replace(nFirstIdx,nLastIdx,"(010)63880127");
			if(nLineIdx == 131)
				line.replace(nFirstIdx,nLastIdx,"(010)63880132");

			out << line << endl; // 输入到2.txt中

			nLineIdx++;
		}  
	}  
	else // 没有该文件  
	{  
		return false;
	}  

	return true;  
}
bool gwAddonFunction::WriteDOM(const char* inFile,const char* outFile,const ieSimpleRasterInfo& eInfo )
{
	ifstream in(inFile);  
	ofstream out(outFile);  
	string filename;  
	string line;  

	if(in) // 有该文件  
	{  
		int nLineIdx = 1;
		while (getline (in, line)) // line中不包括每行的换行符  
		{   
			if(line.find_first_of("[")==-1)
			{
				out << line << endl; // 输入到2.txt中
				nLineIdx++;
				continue;
			}
			int nFirstIdx = line.find_first_of("[");
			int nLastIdx  = line.find_first_of("]");
			if(nLineIdx == 4 || nLineIdx == 20 )
				line.replace(nFirstIdx,nLastIdx,"黑龙江测绘局");
			
			if(nLineIdx == 6)
			{
				time_t t = time(0); 
				char tmp[64]; 
				memset(tmp,64,64*sizeof(char));
				strftime( tmp, sizeof(tmp), "%Y%m%d ",localtime(&t) ); 
				line.replace(nFirstIdx,nLastIdx,tmp);
			}
			if(nLineIdx == 12)
			{
				line.replace(nFirstIdx,nLastIdx,"J49E001001");
			}
			if(nLineIdx == 15)
			{
				line.replace(nFirstIdx,nLastIdx,"200904");
			}
			if(nLineIdx == 16)
				line.replace(nFirstIdx,nLastIdx,"国家1:50000数字正射影像更新数据");
			if(nLineIdx == 17)
			{
				int nLast = line.find_last_of("]");
				line.replace(nFirstIdx,nLast,"1米数字正射影像图，由黑龙江测绘局于200904完成生产，数据量为410");
			}
			if(nLineIdx == 23)
				line.replace(nFirstIdx,nLastIdx,"国家测绘地理信息局");
			if(nLineIdx == 26)
				line.replace(nFirstIdx,nLastIdx,"国家1:50000数据库更新工程, 1:50000数据库更新数字正射影像");
			if(nLineIdx == 29)
				line.replace(nFirstIdx,nLastIdx,"秘密");
			if(nLineIdx == 31 ||nLineIdx == 107)
				line.replace(nFirstIdx,nLastIdx,"TIFF");
			if(nLineIdx == 33)
				line.replace(nFirstIdx,nLastIdx,"410");
			if(nLineIdx == 34)
				line.replace(nFirstIdx,nLastIdx,"灰度");
			if(nLineIdx == 35)
				line.replace(nFirstIdx,nLastIdx,"8");
			if(nLineIdx == 36)
				line.replace(nFirstIdx,nLastIdx,"100");
			if(nLineIdx == 37)
				line.replace(nFirstIdx,nLastIdx,"19299*22076");
			if(nLineIdx == 41)
				line.replace(nFirstIdx,nLastIdx,"1");
			if(nLineIdx == 42)
				line.replace(nFirstIdx,nLastIdx,"zho");
			if(nLineIdx == 47)
			{
				char left[20];
				memset(left,20,20*sizeof(char));
				sprintf_s(left,20*sizeof(char),"%0.5f",eInfo.left);
				line.replace(nFirstIdx,nLastIdx,left);
			}
			if(nLineIdx == 48)
			{
				char left[20];
				memset(left,20,20*sizeof(char));
				sprintf_s(left,20*sizeof(char),"%0.5f",eInfo.right);
				line.replace(nFirstIdx,nLastIdx,left);
			}
			if(nLineIdx == 49)
			{
				char left[20];
				memset(left,20,20*sizeof(char));
				sprintf_s(left,20*sizeof(char),"%0.5f",eInfo.bottom);
				line.replace(nFirstIdx,nLastIdx,left);
			}
			if(nLineIdx == 50)
			{
				char left[20];
				memset(left,20,20*sizeof(char));
				sprintf_s(left,20*sizeof(char),"%0.5f",eInfo.top);
				line.replace(nFirstIdx,nLastIdx,left);
			}
			if(nLineIdx == 52)
				line.replace(nFirstIdx,nLastIdx,"航片");
			if(nLineIdx == 54)
				line.replace(nFirstIdx,nLastIdx,"32000");
			if(nLineIdx == 55)
				line.replace(nFirstIdx,nLastIdx,"RMK-TOP");
			if(nLineIdx == 56)
				line.replace(nFirstIdx,nLastIdx,"153.038");
			if(nLineIdx == 57)
				line.replace(nFirstIdx,nLastIdx,"中国国土资源航空物探遥感中心");
			if(nLineIdx == 58)
				line.replace(nFirstIdx,nLastIdx,"0707");
			if(nLineIdx == 59)
				line.replace(nFirstIdx,nLastIdx,"200709");
			if(nLineIdx == 60)
				line.replace(nFirstIdx,nLastIdx,"灰度");
			if(nLineIdx == 61)
				line.replace(nFirstIdx,nLastIdx,"合格");
			if(nLineIdx == 62)
				line.replace(nFirstIdx,nLastIdx,"21");
			if(nLineIdx == 63)
				line.replace(nFirstIdx,nLastIdx,"1");
			if(nLineIdx == 64)
				line.replace(nFirstIdx,nLastIdx,"合格");
			if(nLineIdx == 66||nLineIdx == 68||nLineIdx == 69||nLineIdx == 70||nLineIdx == 71||
				nLineIdx == 73||nLineIdx == 74||nLineIdx == 75||nLineIdx ==76||nLineIdx == 77||
				nLineIdx == 79||nLineIdx == 79)
				line.replace(nFirstIdx,nLastIdx,"");
			
			if(nLineIdx == 84)
				line.replace(nFirstIdx,nLastIdx,"合格");
			if(nLineIdx == 85)
				line.replace(nFirstIdx,nLastIdx,"国家测绘局黑龙江测绘产品质量监督检验站");
			if(nLineIdx == 86)
				line.replace(nFirstIdx,nLastIdx,"200912");

			//处理空间参考
			std::string strWKT = eInfo.m_strProjectionRef;
			OGRSpatialReference oSRS;
			char* szWKT = (char*)strWKT.data();
			OGRErr err = oSRS.importFromWkt(&szWKT);
			bool bPro = true;
			char *pszGeoSRSName = "2000国家大地坐标系";
			char *pszPROSRSName = "2000国家大地坐标系";
			char *pszProjection = "高斯-克吕格投影";
			char *pszSPHEROID = "2000国家大地坐标系椭球体";
			char meridian[20];
			memset(meridian,20,20*sizeof(char));
			string degree = "6";
			char zone[10];
			memset(zone,10,10*sizeof(char));
		
			char Major[20];
			memset(Major,20,20*sizeof(char));
			char szRatio[20];
			memset(szRatio,20,20*sizeof(char));
			OGRSpatialReference *poGeogSRS = NULL;
			if(err != OGRERR_NONE)
				bPro = false;
			else
			{
				if(oSRS.IsProjected() == true)
				{
					poGeogSRS = oSRS.CloneGeogCS();
					pszGeoSRSName= (char*)poGeogSRS->GetAttrValue("GEOGCS");
					pszPROSRSName= (char*)oSRS.GetAttrValue("PROJCS");

					/*string strProName = pszPROSRSName;
					int ntempIdx = strProName.find_first_of("-");
					string degree = strProName.substr(ntempIdx-1,ntempIdx);*/

					pszProjection= (char*)oSRS.GetAttrValue("PROJECTION");
					double dmeriDian = oSRS.GetProjParm(SRS_PP_CENTRAL_MERIDIAN); 
					double dzone = oSRS.GetProjParm(SRS_PP_ZONE); 
					sprintf_s(zone,20,"%d",dzone);
					sprintf_s(meridian,20,"%0.1f",dmeriDian);
					pszSPHEROID = (char*)poGeogSRS->GetAttrValue( "GEOGCS|DATUM|SPHEROID" );

					double dMajor =	poGeogSRS->GetSemiMajor();
					sprintf_s(Major,20,"%0.1f",dMajor);

					double dMinor =	poGeogSRS->GetSemiMinor();
					sprintf_s(szRatio,20,"%0.1f",dMinor);
				}
				else	
				{
					poGeogSRS = oSRS.CloneGeogCS();
					pszGeoSRSName= (char*)poGeogSRS->GetAttrValue("GEOGCS");
			
					string strProName = pszPROSRSName;
					int ntempIdx = strProName.find_first_of("-");
					string degree = strProName.substr(ntempIdx-1,ntempIdx);

					pszProjection= (char*)poGeogSRS->GetAttrValue("PROJECTION");
					double dmeriDian = oSRS.GetProjParm(SRS_PP_CENTRAL_MERIDIAN); 
					double dzone = oSRS.GetProjParm(SRS_PP_ZONE); 
					sprintf_s(zone,20,"%d",dzone);
					sprintf_s(meridian,20,"%0.1f",dmeriDian);
					pszSPHEROID = (char*)poGeogSRS->GetAttrValue( "GEOGCS|DATUM|SPHEROID" );

					double dMajor =	poGeogSRS->GetSemiMajor();
					sprintf_s(Major,20,"%0.1f",dMajor);

					double dMinor =	poGeogSRS->GetSemiMinor();
					sprintf_s(szRatio,20,"%0.1f",dMinor);
				}
				

			}
			
			if(nLineIdx == 91||nLineIdx == 101)
				line.replace(nFirstIdx,nLastIdx,pszPROSRSName);
			if(nLineIdx == 93)
				line.replace(nFirstIdx,nLastIdx,degree.data());
			if(nLineIdx == 94)
				line.replace(nFirstIdx,nLastIdx,zone);
			if(nLineIdx == 95)
				line.replace(nFirstIdx,nLastIdx,meridian);
			if(nLineIdx == 96)
				line.replace(nFirstIdx,nLastIdx,pszSPHEROID);
			if(nLineIdx == 98)
				line.replace(nFirstIdx,nLastIdx,Major);
			if(nLineIdx == 99 || nLineIdx == 102)
				line.replace(nFirstIdx,nLastIdx,"米");
			if(nLineIdx == 100)
				line.replace(nFirstIdx,nLastIdx,szRatio);
			if(nLineIdx == 103)
				line.replace(nFirstIdx,nLastIdx,"1985国家高程基准");
			if(nLineIdx == 104)
				line.replace(nFirstIdx,nLastIdx,"正常高");
			if(nLineIdx == 109)
				line.replace(nFirstIdx,nLastIdx,"CD-ROM/DVD-ROM");
			if(nLineIdx == 114)
				line.replace(nFirstIdx,nLastIdx,"海淀区莲花池西路28号");
			if(nLineIdx == 115)
				line.replace(nFirstIdx,nLastIdx,"北京市");
			if(nLineIdx == 116)
				line.replace(nFirstIdx,nLastIdx,"100830");
			if(nLineIdx == 117)
				line.replace(nFirstIdx,nLastIdx,"xinxi@nsdi.gov.cn");
			if(nLineIdx == 119)
				line.replace(nFirstIdx,nLastIdx,"http://ngcc.sbsm.gov.cn");
			if(nLineIdx == 120)
				line.replace(nFirstIdx,nLastIdx,"(010)63880127");
			if(nLineIdx == 121)
				line.replace(nFirstIdx,nLastIdx,"(010)63880132");

			out << line << endl; // 输入到2.txt中

			nLineIdx++;
		}  
	}  
	else // 没有该文件  
	{  
		return false;
	}  

	return true;  
}
int gwAddonFunction::copyLayer(OGRLayer *poSrcLayer, 
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
	int         nSrcFieldCount = poSrcDefn->GetFieldCount();
	int         nDstFieldCount = 0;
	int         iField;
	vector<string> vec_FieldsName;
	if(isGDB)
	{
		if(BuildFielsGDBv10(poSrcLayer,vec_FieldsName)&&vec_FieldsName.size()!=nSrcFieldCount)
		{
			//return false;
		}
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

	/* -------------------------------------------------------------------- */
	/*      Check if the destination layer supports transactions and set a  */
	/*      default number of features in a single transaction.             */
	/* -------------------------------------------------------------------- */
	int nGroupTransactions = 0;
	if( poDstLayer->TestCapability( OLCTransactions ) )
		nGroupTransactions = 10000;

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
		if(nIndex == 3000000)
		{
			nIndex = poFeature->GetFID();
			OGRFeature::DestroyFeature( poFeature );
			
			return 0;
		}
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
		OGRFeature::DestroyFeature( poFeature );
		OGRFeature::DestroyFeature( poDstFeature );
		idx++;
	}
	return 1;
}
OGRErr gwAddonFunction::SetFieldsFrom( OGRFeature * poSrcFeature, OGRFeature* poDestFeature,
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
			if(strName.length() > 10)
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
				//VSIFree(panMap);
				return OGRERR_FAILURE;
			}
		}
	}



	/*if( poSrcFeature == this )
	{
		VSIFree(panMap);
		return OGRERR_FAILURE;
	}*/

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

int gwAddonFunction::BuildFielsGDBv10(OGRLayer* pSrcLayer,vector<string>& vec_FieldNames)
{
	OGROpenFileGDBLayer *pGDBLayer = dynamic_cast<OGROpenFileGDBLayer*>(pSrcLayer);
	//pGDBLayer->BuildLayerDefinition();
	string m_osDefinition = pGDBLayer->GetXMLDefinition();

	CPLXMLNode* psTree = CPLParseXMLString(m_osDefinition.c_str());
	if( psTree == NULL )
	{
		return FALSE;
	}

	CPLStripXMLNamespace( psTree, NULL, TRUE );
	/* CPLSerializeXMLTreeToFile( psTree, "/dev/stderr" ); */
	CPLXMLNode* psInfo = CPLSearchXMLNode( psTree, "=DEFeatureClassInfo" );
	if( psInfo == NULL )
		psInfo = CPLSearchXMLNode( psTree, "=DETableInfo" );
	if( psInfo == NULL )
	{
		CPLDestroyXMLNode(psTree);
		return FALSE;
	}
	
	CPLXMLNode* psFieldsInfo = CPLSearchXMLNode( psInfo, "=GPFieldInfoExs" );
	CPLXMLNode* psFieldInfos = psFieldsInfo->psChild;
	CPLXMLNode* psFieldInfo = NULL; 
	while((psFieldInfos = psFieldInfos->psNext) != NULL)
	{
		string FieldName = CPLGetXMLValue(psFieldInfos, "Name", NULL);
		string strTyope = CPLGetXMLValue(psFieldInfos, "FieldType", NULL);
		if(stricmp(strTyope.data(),"esriFieldTypeOID")==0||
			stricmp(strTyope.data(),"esriFieldTypeGeometry")==0)
			continue;
		vec_FieldNames.push_back(FieldName);
	}
	CPLDestroyXMLNode(psTree);
	return TRUE;
}

OGRwkbGeometryType gwGeometryTypeToOGRGeometryType(int eGeoType ,int bHasZ)
{
	OGRwkbGeometryType eRetType = wkbUnknown;
	if (bHasZ)
	{
		switch(eGeoType)
		{
		case 1://point
			eRetType = wkbPoint25D;
			break;
		case 3://SimpleLineString:
			eRetType = wkbLineString25D;
			break;
		case 5://gwGeometryType_SimpleLinearRing:
			eRetType = wkbLinearRing ;
			break;
		case 6://gwGeometryType_SimplePolygon:
			eRetType = wkbPolygon25D;
			break;
		case 2://gwGeometryType_SimpleMultiPoint:
			eRetType = wkbMultiPoint25D;
			break;
		case 4://gwGeometryType_SimplePolyline:
			eRetType = wkbMultiLineString25D;
			break;
		case 7://gwGeometryType_SimpleMultiPolygon:
			eRetType = wkbMultiPolygon25D;
			break;
		default:
			break;
		}
	}
	else
	{
		switch(eGeoType)
		{
		case 1://gwGeometryType_SimplePoint:
			eRetType = wkbPoint;
			break;
		case 3://gwGeometryType_SimpleLineString:
			eRetType = wkbLineString;
			break;
		case 5://gwGeometryType_SimpleLinearRing:
			eRetType = wkbLinearRing ;
			break;
		case 6://gwGeometryType_SimplePolygon:
			eRetType = wkbPolygon;
			break;
		case 2://gwGeometryType_SimpleMultiPoint:
			eRetType = wkbMultiPoint;
			break;
		case 4://gwGeometryType_SimplePolyline:
			eRetType = wkbMultiLineString;
			break;
		case 7://gwGeometryType_SimpleMultiPolygon:
			eRetType = wkbMultiPolygon;
			break;
		default:
			break;
		}
	}

	return eRetType;

	
}



bool gwAddonFunction::GeowayDB2SQLite(const char* inDir)
{
	 CPLString osCommand;
	 sqlite3* hDB = NULL;
	 char *pszErrMsg = NULL;
	 sqlite3_stmt* pStmt = NULL;
	 const char* pszTail = NULL;

	 char* szUtf8Conn = ToUTF8(inDir);
	 int rc = sqlite3_open_v2(szUtf8Conn, &hDB, SQLITE_OPEN_READWRITE, NULL);
	 if (SQLITE_OK != rc)
	 {
		 if(hDB != NULL)
			 sqlite3_close(hDB);
		 return false;
	 }
	delete[] szUtf8Conn;
	 osCommand =
		 "CREATE TABLE geometry_columns ("
		 "     f_table_name VARCHAR, "
		 "     f_geometry_column VARCHAR, "
		 "     geometry_type INTEGER, "
		 "     coord_dimension INTEGER, "
		 "     srid INTEGER,"
		 "     geometry_format VARCHAR )";
	 rc = sqlite3_exec( hDB, osCommand, NULL, NULL, &pszErrMsg );
	 if( rc != SQLITE_OK )
	 {
		 CPLError( CE_Failure, CPLE_AppDefined,
			 "Unable to create table geometry_columns: %s",
			 pszErrMsg );
		 sqlite3_free( pszErrMsg );
		 if(hDB != NULL)
			 sqlite3_close(hDB);
		 return FALSE;
	 }

	 osCommand =
		 "CREATE TABLE spatial_ref_sys        ("
		 "     srid INTEGER UNIQUE,"
		 "     auth_name TEXT,"
		 "     auth_srid TEXT,"
		 "     srtext TEXT)";
	 rc = sqlite3_exec( hDB, osCommand, NULL, NULL, &pszErrMsg );
	 if( rc != SQLITE_OK )
	 {
		
		 sqlite3_free( pszErrMsg );
		 if(hDB != NULL)
			 sqlite3_close(hDB);
		 return FALSE;
	 }
	 osCommand = "SELECT class_name, feature_type FROM gw_class_metadata ";
	 if (SQLITE_OK != sqlite3_prepare_v2(hDB, 
		 osCommand.c_str(), -1, &pStmt, &pszTail))
	 {
		 sqlite3_finalize(pStmt);
		 if(hDB != NULL)
			 sqlite3_close(hDB);
		 return NULL;
	 }
	 map<string,int> mapGeoTypes ;
	 while (sqlite3_step(pStmt) == SQLITE_ROW)
	 {
		 string class_name = (char*)sqlite3_column_text(pStmt, 0);
		 int featureType = sqlite3_column_int(pStmt,1);
		 mapGeoTypes[class_name] = featureType;
	 }
	sqlite3_finalize(pStmt);

	osCommand = "SELECT class_name,geom_name,srid, hasz FROM gw_geom_metadata ";
	if (SQLITE_OK != sqlite3_prepare_v2(hDB, 
		osCommand.c_str(), -1, &pStmt, &pszTail))
	{
		sqlite3_finalize(pStmt);
		if(hDB != NULL)
			sqlite3_close(hDB);
		return NULL;
	}
	while (sqlite3_step(pStmt) == SQLITE_ROW)
	{
		string class_name = (char*)sqlite3_column_text(pStmt, 0);
		string geom_name = (char*)sqlite3_column_text(pStmt, 1);
		int srid = sqlite3_column_int(pStmt,2);
		int hasz = sqlite3_column_int(pStmt,3);
		int geoType = mapGeoTypes[class_name];
		OGRwkbGeometryType eType = gwGeometryTypeToOGRGeometryType(geoType,hasz);
		int coord = 2;
		if(hasz == 1)
			coord = 3;
		if( srid > 0 )
		{
			osCommand.Printf(
				"INSERT INTO geometry_columns "
				"(f_table_name, f_geometry_column, geometry_format, "
				"geometry_type, coord_dimension, srid) VALUES "
				"('%s','%s','%s', %d, %d, %d)", 
				class_name.data(),
				geom_name.c_str(), "wkb",
				(int) wkbFlatten(eType), coord, srid );
		}
		else
		{
			osCommand.Printf(
				"INSERT INTO geometry_columns "
				"(f_table_name, f_geometry_column, geometry_format, "
				"geometry_type, coord_dimension) VALUES "
				"('%s','%s','%s', %d, %d)",
				class_name.data(),
				geom_name.c_str(), "wkb",
				(int) wkbFlatten(eType), coord );
		}
		rc = sqlite3_exec( hDB, osCommand.data(), NULL, NULL, &pszErrMsg );
		if( rc != SQLITE_OK )
		{
			
			sqlite3_free( pszErrMsg );
			
			continue;
		}
	}
	sqlite3_finalize(pStmt);

	osCommand = "SELECT srid, wkt FROM gw_spatial_ref_metadata ";
	if (SQLITE_OK != sqlite3_prepare_v2(hDB, 
		osCommand.c_str(), -1, &pStmt, &pszTail))
	{
		sqlite3_finalize(pStmt);
		return NULL;
	}
	while (sqlite3_step(pStmt) == SQLITE_ROW)
	{
		int srid = sqlite3_column_int(pStmt, 0);
		const unsigned char* szwkt = sqlite3_column_text(pStmt, 1);
		if(szwkt == NULL)
			continue;
		string wkt = (char*)sqlite3_column_text(pStmt, 1);

		if(wkt!="")
		{
			osCommand.Printf(
				"INSERT INTO spatial_ref_sys "
				"(srid, srtext) VALUES "
				"('%d','%s')",
				srid,
				wkt.c_str());
		}
		else
		{
			osCommand.Printf(
				"INSERT INTO spatial_ref_sys "
				"(srid) VALUES "
				"('%d')",
				srid);
		}
		rc = sqlite3_exec( hDB, osCommand.c_str(), NULL, NULL, &pszErrMsg );
		if( rc != SQLITE_OK )
		{
			
			sqlite3_free( pszErrMsg );
			continue;
		}
	}
	/*if(pszErrMsg != NULL)
		sqlite3_free(pszErrMsg);*/
	if(hDB != NULL)
		sqlite3_close(hDB);
	return true;
}
OGRwkbGeometryType gwAddonFunction::GetGeometryType(OGRLayer* pSrc)
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
hid_t  GDALDataType2PixelDataType(GDALDataType gdaltype)
{
	switch(gdaltype)
	{
	case    GDT_Byte:	
		return H5T_NATIVE_CHAR;
		break;
	case   	GDT_UInt16:	
		return H5T_NATIVE_USHORT;
		break;
	case   	GDT_Int16:	
		return H5T_NATIVE_SHORT;
		break;
	case   	GDT_UInt32:	
		return H5T_NATIVE_UINT;
		break;
	case    GDT_Int32:	
		return H5T_NATIVE_INT;
		break;
	case    GDT_Float32:
		return H5T_NATIVE_FLOAT;
		break;
	case   	GDT_Float64:
		return H5T_NATIVE_DOUBLE;
		break;
	default: 
		return H5T_NATIVE_CHAR;     		
		break;
	}
}

bool gwAddonFunction::writeHDF5(const char * dstHDF5FileName, GDALDataset *dataset)
{
	
	if (dataset == NULL)
	{
		return false;
	}
	int nx = dataset->GetRasterXSize();
	int ny = dataset->GetRasterYSize();
	int nz = dataset->GetRasterCount();

	GDALRasterBand * band = dataset->GetRasterBand(1);
	GDALDataType dataType = band->GetRasterDataType();

	int nBandSpace = (GDALGetDataTypeSize(dataType) / 8);
	int nPixSapce = nBandSpace * nz;
	int nLineSpace = nPixSapce * nx;
	
CPLErr eErr = CE_None;
	if (1) //多波段数据的写入
	{
		unsigned char * data = new unsigned char[nx * ny * nPixSapce];

		int *panBandMap = new int[nz];
		for (int i = 0; i < nz; i++)
		{
			panBandMap[i] = i + 1;     //按照RGB波段存储方式读取
		}

		

		//从数据集读取数据，此时根据原始数据中像素存储顺序进行调整组最终data需要变成RGB存储顺序
		dataset->RasterIO(GF_Read, 0, 0, nx, ny, data, nx, ny, dataType, nz, panBandMap, 0,0,0);

		/* 定义hdf5文件句柄 */
		hid_t file_id;
		/* 定义数据空间维度，如果为三波段影像对应{Rows, Cols, BandCount} */
		hsize_t dims[3] = {nz,ny, nx};
		/* 返回状态 */
		herr_t status;
hid_t h5DataType = GDALDataType2PixelDataType(dataType);
		 
		/* 创建hdf5文件 */
		file_id = H5Fcreate(dstHDF5FileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
		/* 创建并写入数据集：file_id为hdf5文件句柄，/SUB_DATASET为数据集名称，3表示数据空间维度为三维，
		dims表示数据空间各个维度的大小，H5T_NATIVE_UCHAR为对应的数据类型，data为对应的数据指针 */
		status = H5LTmake_dataset(file_id, "/SUB_DATASET", 3, dims,
							  h5DataType, data);
		
		assert(status != -1);
		/* 为数据集增加属性信息 */
		H5LTset_attribute_int(file_id, "/SUB_DATASET", "rows", &ny, 1);
		H5LTset_attribute_int(file_id, "/SUB_DATASET", "cols", &nx, 1);
		H5LTset_attribute_int(file_id, "/SUB_DATASET", "bandCount", &nz, 1);

		/*H5LTset_attribute_double(file_id, "/SUB_DATASET", "Top", &nz, 1);
		H5LTset_attribute_double(file_id, "/SUB_DATASET", "Left", &nz, 1);
		H5LTset_attribute_double(file_id, "/SUB_DATASET", "Right", &nz, 1);
		H5LTset_attribute_double(file_id, "/SUB_DATASET", "Bottom", &nz, 1);*/
		status = H5Fclose (file_id); 
		delete []panBandMap;
		delete []data;

		return true;
	}
	else  //单波段数据只能创建二维的数据空间，否则创建金字塔后拉伸值为0
	{
		unsigned char * data = new unsigned char[nx * ny * nPixSapce];

		//读取波段数据
		band->RasterIO(GF_Read, 0, 0, nx, ny, data, nx, ny, dataType, 0, 0);

		//unsigned char * data = new unsigned char[nx * ny * nPixSapce];

		//int *panBandMap = new int[nz];
		//for (int i = 0; i < nz; i++)
		//{
		//	panBandMap[i] = i + 1;     //按照RGB波段存储方式读取
		//}
		////从数据集读取数据，此时根据原始数据中像素存储顺序进行调整组最终data需要变成RGB存储顺序
		//dataset->RasterIO(GF_Read, 0, 0, nx, ny, data, nx, ny, dataType, nz, panBandMap, 0, 0, 0);


		/* 定义hdf5文件句柄 */
		hid_t file_id;
		/* 定义数据空间维度，如果为单波段影像对应{Rows, Cols} */
		hsize_t dims[2] = {ny, nx};
		/* 返回状态 */
		herr_t status;
		hid_t h5DataType = GDALDataType2PixelDataType(dataType);
		/* 创建hdf5文件 */
		file_id = H5Fcreate(dstHDF5FileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
		/* 创建并写入数据集：file_id为hdf5文件句柄，/SUB_DATASET为数据集名称，2表示数据空间维度为二维，
		dims表示数据空间各个维度的大小，H5T_NATIVE_UCHAR为对应的数据类型，data为对应的数据指针 */
		status = H5LTmake_dataset(file_id, "/SUB_DATASET", 2, dims,
								  h5DataType, data);
		assert(status != -1);
		/* 为数据集增加属性信息 */
		H5LTset_attribute_int(file_id, "/SUB_DATASET", "rows", &ny, 1);
		H5LTset_attribute_int(file_id, "/SUB_DATASET", "cols", &nx, 1);
		

		status = H5Fclose (file_id); 
		delete []data;

		return true;
	}
	return false;
}

bool gwAddonFunction::copyDataset(const string& strPath,const string& strOutPath, 
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

	if(stricmp(strExt.data(),".db")||
		stricmp(strExt.data(),".gwdb"))
	{
		gwAddonFunction::GeowayDB2SQLite(strPath.data());
	}

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
		char* szPath = gwAddonFunction::ToUTF8(strPath.c_str());
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
//	m_poDriver->CopyDataSource(m_poDS,strOutPath.data(),NULL);
	OGRDataSource* poODS = NULL;
	OGRLayer* pLastLayer = NULL;
	bool bInTrans = false;
	try
	{
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","YES");
		char* szPath = gwAddonFunction::ToUTF8(strOutPath.data());
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
				char* cName = gwAddonFunction::FromUTF8(strName.data());
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
				szName = gwAddonFunction::ToUTF8(strName.data());
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
				
				poDstLayer = poODS->CreateLayer( szName, NULL, wkbNone, NULL );
			}
			else
			{
				OGRwkbGeometryType GeoType = poSrcDefn->GetGeomType();
				if(GeoType == wkbNone || GeoType == wkbUnknown)
				{
					GeoType = gwAddonFunction::GetGeometryType(poLayer);
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
			if(poDstLayer!=NULL)
			{

				if(bInTrans == false)
				{
					bInTrans = true;
					poDstLayer->StartTransaction();
				}
				OID = 0;
				int bCopied = -1;// gwAddonFunction::copyLayer(poLayer,poDstLayer,poODS,enCode,isGDB,nIndex,OID);
				while(bCopied != 1)
				{
					if(bCopied == -1)
						bCopied = gwAddonFunction::copyLayer(poLayer,poDstLayer,poODS,enCode,isGDB,nIndex,OID);
					else if(bCopied == 0)
					{
						OGRDataSource::DestroyDataSource(m_poDS);
						//OGRDataSource::DestroyDataSource(poODS);
						m_poDS = NULL;
						//poODS = NULL;
						m_poDS = OGRSFDriverRegistrar::Open(strInPath.c_str(), false); //true时才能写操作
						/*char* szPath1 = gwAddonFunction::ToUTF8(strOutPath.data());
						poODS = m_poDriver->Open( szPath1, 1);
						CPLFree(szPath1);*/
						OGRLayer* poLayer1 = m_poDS->GetLayer(iLayer);
						//OGRLayer* poDstLayer1 = poODS->GetLayer(iLayer);
						OID = nIndex;
						nIndex = 0;
						bCopied = gwAddonFunction::copyLayer(poLayer1,poDstLayer,poODS,enCode,isGDB,nIndex,OID);
					//	poDstLayer1->StartTransaction();
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
				pLastLayer = poLayer;
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
	if(pLastLayer != NULL && bInTrans)
		pLastLayer->CommitTransaction();
	if(poODS == NULL)
	{
		if(nProgress != NULL)
			nProgress->OnLog("转换失败",GIS::LogLevel::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return false;
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

int gwAddonFunction::GetDirectChildren(std::vector<string>& vChildren,std::vector<string>& vChildFileNames,
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
			char* FileName = gwAddonFunction::WcharToChar(c_file.name);
			strFileName = FileName;
			strFile = strFind.append(FileName) ;
			delete[] FileName;
			FileName = NULL;
		}
		else
		{
			strFile = strFind.append("\\");
			char* FileName = gwAddonFunction::WcharToChar(c_file.name);
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
bool gwAddonFunction::CreateDir(const string& strPath)
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

bool gwAddonFunction::copyRaster(const string& strPath1,const string& strOutPath, 
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
	
	//GDAL有bug，暂时不知道该属性为什么有时不起作用
	if( CSLTestBoolean(CPLGetConfigOption( "GDAL_FILENAME_IS_UTF8", "YES" ) ) )
	{
		CPLGetConfigOption("GDAL_FILENAME_IS_UTF8", NULL);
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
	}
	GDALAllRegister();  
	GDALDataset* pDataset = NULL;
	pDataset = reinterpret_cast<GDALDataset*>(GDALOpen(strPath.c_str(),GA_ReadOnly));


	if (NULL == pDataset)
	{
		if(nProgress != NULL)
			nProgress->OnLog("转换失败",GIS::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return false;;
	}

	GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName(strProvier.c_str());

	char **papszMetadata;
	papszMetadata = poDriver->GetMetadata();
	if(!CSLFetchBoolean( papszMetadata, GDAL_DCAP_CREATECOPY, FALSE ) && 
		stricmp(strOutExt.data(),".h5")!=0 )
	{
		if(nProgress != NULL)
			nProgress->OnLog("error! CSLFetchBoolean GDAL_DCAP_CREATECOPY\n",GIS::eError);
		else
			std::cout<<"转换失败"<<std::endl;

		return false;
	}

	GDALDataset *poDstDS;
	//poDstDS = poDriver->Create(strOutPath.c_str(),pDataset->GetRasterXSize(),pDataset->GetRasterYSize()
	//	,pDataset->GetRasterCount(),pDataset->GetRasterBand(1)->GetRasterDataType(),NULL);

	if(stricmp(strInExt.data(),".h5")==0)
	{
		char **subDatasetList = GDALGetMetadata(pDataset, "SUBDATASETS");
		string subdataset = "";
		if(subDatasetList != NULL)
		{
			subdataset = subDatasetList[1];
			int nidx = subdataset.find_first_of("=");
			if(nidx != -1)
				subdataset = subdataset.substr(nidx+1);

			GDALClose(pDataset);
			pDataset = reinterpret_cast<GDALDataset*>(GDALOpen(subdataset.c_str(),GA_ReadOnly));

		}

	}
	poDstDS = poDriver->CreateCopy(strOutPath.c_str(), pDataset, FALSE, 
		NULL, NULL, NULL);
	if( poDstDS == NULL && stricmp(strOutExt.data(),".h5")!=0)
	{
		if(nProgress != NULL)
			nProgress->OnLog("创建失败",GIS::eError);
		else
			std::cout<<"转换失败"<<std::endl;
		return false;
	}
	if(stricmp(strOutExt.data(),".h5")==0)
	{
		gwAddonFunction::writeHDF5(strOutPath.data(),pDataset);
	}
	else if(stricmp(strInExt.data(),".h5")==0)
	{
		if(poDstDS!=NULL)
			GDALClose(poDstDS);
		poDstDS = NULL;
		poDstDS = reinterpret_cast<GDALDataset*>(GDALOpen(strOutPath.c_str(),GA_ReadOnly));
		GDALRasterBand* pBand = poDstDS->GetRasterBand(1);
		double min = 0;
		double max = 0;
		double mean = 0;
		double dev = 0;
		void* pros;
		pBand->ComputeStatistics(1,&min,&max,&mean,&dev,NULL,pros);
	}

	if(poDstDS!=NULL)
		GDALClose(poDstDS);
	poDstDS = NULL;
	//string strExt = strOutPath.substr(strOutPath.find_last_of("."),strOutPath.length()-strOutPath.find_last_of("."));
	string strXMLPath = strOutPath;
	string strTXT = "";
	if(strXMLPath.find_last_of(".") != -1)
		strXMLPath = strXMLPath.replace(strXMLPath.find_last_of("."),strXMLPath.length()-strXMLPath.find_last_of("."),".IOS19163.XML");
	else
		strXMLPath = strXMLPath + ".IOS19163.XML";
	if(strPath.find_last_of(".") != -1)
		strTXT = strPath.replace(strPath.find_last_of("."),strPath.length()-strPath.find_last_of("."),".txt");
	else
	{
		strTXT = strTXT + ".txt";
	}


	//pieRaster->GetRasterInfo(&ieInfo);

	DOMDocument *pXMLDoc = gwAddonFunction::Parse(strXMLPath);
	string strMetaData;
	if(pXMLDoc == NULL)
	{
		wchar_t* wtTXT = gwAddonFunction::CharToWchar(strTXT.data());
		std::ifstream in(wtTXT);  
		delete[] wtTXT;
		//ofstream out(m_XMLPath);  
		string filename;  
		string line;  
		int nLineIdx = 1;

		gwStandardMetadataAnalysis* pAnalysis =  NULL;
		gwStandardMetaDataFactory::Instance()->CreateMetaData("IE_OpticalImage",&pAnalysis);
		bool bsaved  = false;
		if(in) // 有该文件  
		{  

			while (getline (in, line)) // line中不包括每行的换行符  
			{   
				nLineIdx++;

			}
		}
		else
		{
			ieSimpleRaster* pieRaster = ieSimpleRasterFactory::Instance()->OpenRaster(strOutPath,false);
			if(pieRaster == NULL)
			{
				if(nProgress != NULL)
					nProgress->OnLog("转换失败",GIS::eError);
				else
					std::cout<<"写元数据失败"<<std::endl;
				if(pieRaster!=NULL)
					delete pieRaster;
				return false;
			}
			ieSimpleRasterInfo ieInfo = pieRaster->GetRasterInfo();
			pAnalysis->setRasterInfo(ieInfo);
			pAnalysis->setStandardMetaDataFilePath(strXMLPath);
			pAnalysis->WriteStandardMetadata(ieInfo);
			bsaved = pAnalysis->SaveMetaData();
			delete pieRaster;
			pieRaster = NULL;

		}
		if(nLineIdx > 124)
		{
			//pAnalysis->setRasterInfo(ieInfo);
			//gwAddonFunction::WriteDOM("d:\\dom.txt","d:\\test1.txt",ieInfo);
			pAnalysis->setStandardMetaDataFilePath(strXMLPath);
			pAnalysis->WriteDEMMetadata(strTXT.data());
			bsaved = true;
		}
		else
		{
			//pAnalysis->setRasterInfo(ieInfo);
			//gwAddonFunction::WriteDOM("d:\\dom.txt","d:\\test1.txt",ieInfo);
			pAnalysis->setStandardMetaDataFilePath(strXMLPath);
			pAnalysis->WriteDOMMetadata(strTXT.data());
			bsaved = true;
		}

		if(!bsaved)
		{
			if(nProgress != NULL)
				nProgress->OnLog("转换失败",GIS::eError);
			else
				std::cout<<"转换失败"<<std::endl;
			return false;
		}
		delete pAnalysis;
		pAnalysis = NULL;

	}

	GDALClose(pDataset);
	m_strResult = "读取成功";
	if(nProgress != NULL)
		nProgress->OnLog(m_strResult.data(),GIS::eInfo);
	else
		std::cout<<m_strResult.data()<<std::endl;

	return true;
}