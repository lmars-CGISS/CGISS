// SuperMapAddon.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "SuperMapAddon.h"

#include "SuImport.h"
#include "SuExport.h"

/// \brief 导入到SuperMap UDB
SUPERMAPADDON_API GIS::Addon*  ImportGPKGToUDB(void)
{
	return new ImportGPKG();
}

/// \brief 导出到SuperMap UDB
SUPERMAPADDON_API GIS::Addon*  ExportGPKGFromUDB(void)
{
	return new ExportGPKG();	
}

/// \brief 导入
SUPERMAPADDON_API GIS::Addon*  ImportGTIFFToUDB(void)
{
	return  new ImportGTIFF();
}

/// \brief 导出到AE mdb文件地物类
SUPERMAPADDON_API GIS::Addon*  ExportGTIFFFromUDB(void)
{
	return new ExportGTIFF();
}