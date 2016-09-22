#ifndef _GW_THEMATIC_GRIDDED_DATA_H
#define _GW_THEMATIC_GRIDDED_DATA_H
#pragma once
#include "stdafx.h"
#include "gwStandardMetaDataAnalysis.h"
#include "gwStandardMetaDataFactory.h"

class gwThematicGriddedData :public gwStandardMetadataAnalysis
{
	friend class gwStandardMetaDataFactory;
protected:
	gie2::CIE_ThematicGriddedData_Type m_ieOpticalImage;
public:
	virtual void WriteStandardMetadata(const ieSimpleRasterInfo& rInfo);
	virtual void WriteDEMMetadata(const char* strPath);
	virtual void WriteDOMMetadata(const char* strPath);
	virtual void ReadStanardMetadata();
	virtual bool SaveMetaData();
	virtual void setRasterInfo(const ieSimpleRasterInfo& rInfo) ;
	virtual void setStandardMetaDataFilePath(const string& strPath) ;
	virtual const ieSimpleRasterInfo getRasterInfo() ;
	virtual const string& getMetaData() ;
protected:
	gwThematicGriddedData(xercesc::DOMNode* const& init );
	gwThematicGriddedData();
public:
	virtual ~gwThematicGriddedData();
};
#endif