#include "StdAfx.h"
#include "PEParser.h"
#include <atlbase.h>
#include <atlcom.h>

PEParser::PEParser(const char* file)
{
	m_hMod = NULL;
	m_hMod =  LoadLibraryEx(CComBSTR(file), NULL, DONT_RESOLVE_DLL_REFERENCES );

}


PEParser::~PEParser(void)
{
	if(m_hMod)
		FreeLibrary (m_hMod);
}
bool PEParser::EnumExport(std::vector<std::string>& vec)
{
	if(!m_hMod)
		return false;

	IMAGE_DOS_HEADER* IDH = (IMAGE_DOS_HEADER*)m_hMod;
	IMAGE_OPTIONAL_HEADER* IOH = (IMAGE_OPTIONAL_HEADER*)((BYTE*)m_hMod + IDH->e_lfanew + 24);
	_IMAGE_EXPORT_DIRECTORY* pExportDescriptor = 
		(_IMAGE_EXPORT_DIRECTORY*)((BYTE*)m_hMod + IOH->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
 
	
	if( IsBadReadPtr((BYTE*)m_hMod +  pExportDescriptor->Name,1))
		return false;

	int  nSize = pExportDescriptor->Name;
	const char* pName = NULL;
	for(int i =0;i<=pExportDescriptor->NumberOfFunctions ;i++)
	{
		pName = (const char*)m_hMod + nSize;
		nSize +=(strlen(pName)+1);
		if(i ==0)
			continue;
		vec.push_back(pName);

	}
	return true;
}
