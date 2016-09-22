
#include "stdafx.h"
#include "gwThematicGriddedData.h"
#include "gwAddonFunction.h"
#include <string>  
#include <iostream>  
#include <fstream>  
gwThematicGriddedData::gwThematicGriddedData()
:m_ieOpticalImage(NULL)
{
	xercesc::XMLPlatformUtils::Initialize();
	m_strMetaData = "";
}
gwThematicGriddedData::gwThematicGriddedData(xercesc::DOMNode* const& init )
:m_ieOpticalImage(init)
{
	xercesc::XMLPlatformUtils::Initialize();
	m_strMetaData = "";
}
gwThematicGriddedData::~gwThematicGriddedData()
{
	xercesc::XMLPlatformUtils::Terminate();
}
void gwThematicGriddedData::WriteStandardMetadata(const ieSimpleRasterInfo& m_gInfo)
{
	
	
	
}
void gwThematicGriddedData::WriteDEMMetadata(const char* strPath)
{
	
	
}
void gwThematicGriddedData::WriteDOMMetadata(const char* strPath)
{
	
	
	
}
bool gwThematicGriddedData::SaveMetaData()
{
	return false;
}
void gwThematicGriddedData::ReadStanardMetadata()
{

}
const string& gwThematicGriddedData::getMetaData()
{
	return m_strMetaData;
}
const ieSimpleRasterInfo gwThematicGriddedData::getRasterInfo()
{
	ieSimpleRasterInfo s;
	return s;
}
void gwThematicGriddedData::setRasterInfo(const ieSimpleRasterInfo& rInfo)
{
	//m_gInfo = rInfo;
}
void gwThematicGriddedData::setStandardMetaDataFilePath(const string& strPath)
{
	m_XMLPath = strPath;
}