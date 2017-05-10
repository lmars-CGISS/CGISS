// SuperMapAddon.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

#include "SuperMapAddon.h"

#include "SuImport.h"
#include "SuExport.h"

/// \brief ���뵽SuperMap UDB
SUPERMAPADDON_API GIS::Addon*  ImportGPKGToUDB(void)
{
	return new ImportGPKG();
}

/// \brief ������SuperMap UDB
SUPERMAPADDON_API GIS::Addon*  ExportGPKGFromUDB(void)
{
	return new ExportGPKG();	
}

/// \brief ����
SUPERMAPADDON_API GIS::Addon*  ImportGTIFFToUDB(void)
{
	return  new ImportGTIFF();
}

/// \brief ������AE mdb�ļ�������
SUPERMAPADDON_API GIS::Addon*  ExportGTIFFFromUDB(void)
{
	return new ExportGTIFF();
}