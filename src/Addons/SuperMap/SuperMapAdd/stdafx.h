// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息

// Windows 头文件:
#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
//#include <string>
#include <tchar.h>
#include <fstream>  
#include <functional>   // std::not1
#include <algorithm>    // std::count_if
#include <vector>

//#include "Engine/Engine.h"
#include "FileParser/UGFileParse.h"
#include "Toolkit/UGToolkit.h"
#include "OGDC/UGOGDC.h"
#include "Stream/Stream.h"
#include "DataExchange/DataExchange.h"


#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

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

#define DATA_TYPE "datatype"
#define PATH "path"
#define OUT_GPKGPATH "output"
#define IN_GPKGPATH "input"
#define FILE_TYPE "file"

#include "sqlite3.h"
#include "ogrsf_frmts.h"

using namespace std;
using namespace xercesc;

// TODO: 在此处引用程序需要的其他头文件
