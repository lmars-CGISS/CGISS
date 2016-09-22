#ifndef _STD_AFX_H
#define _STD_AFX_H
#pragma once

#include "targetver.h"
#define BUFFER_MAX_SIZE 1024*1024*1024*10 //10M

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>
//#include <string>
#include <iostream>
#include <string>
#include <tchar.h>
#include <fstream>  
#include <functional>   // std::not1
#include <algorithm>    // std::count_if

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#define DATA_TYPE "datatype"
#define PATH "path"
#define OUT_GPKGPATH "output"
#define IN_GPKGPATH "input"
#define FILE_TYPE "file"
#include "GDAL/include/ogrsf_frmts.h"
#include "gdal\include\ogr_srs_api.h"
#include "gdal\include\ogr_openfilegdb.h"
#include "gdal_pam.h"

#include "..\ieSimpleRaster\ieSimpleRasterIO.h"

#include "../../../extension/sqlite3/sqlite3.h"
#ifdef _DEBUG
#pragma comment(lib, "sqlite3d.lib")
#else
#pragma comment(lib, "sqlite3.lib")
#endif

#include "hdf5.h"
#include "hdf5_hl.h"
//#include "gdal_priv.h"


#include "Altova.h"
#include "SchemaTypes.h"
#include "AltovaException.h"

#include "xercesc/dom/DOMNode.hpp"
#include "xercesc/dom/DOMDocument.hpp"
#include "xercesc/dom/DOMElement.hpp"
#include "xercesc/dom/DOMNodeList.hpp"
#include "xercesc/util/XMLString.hpp"
#include "xercesc/util/XMLString.hpp"
#include "xercesc/dom/DOMImplementation.hpp"
#include "xercesc/dom/DOMImplementationRegistry.hpp"
#include "xercesc/dom/DOMDocument.hpp"
#include "xercesc/dom/DOMLSSerializer.hpp"
#include "xercesc/framework/MemBufFormatTarget.hpp"
#include "xercesc/framework/MemBufInputSource.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/dom/DOM.hpp"

#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/framework/LocalFileFormatTarget.hpp"

#include "XmlException.h"
#include "Node.h"

#include "gie-typeinfo.h"
#include "gie.h"
#include "type_gie2.Cgie.h"

using namespace altova;
using namespace gie;
#define LOG_CAT "geowayaddon"
using namespace std;
using namespace xercesc;
#endif