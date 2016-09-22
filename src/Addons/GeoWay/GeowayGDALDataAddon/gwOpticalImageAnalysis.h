#ifndef _GW_OPTICAL_IMAGE_ANALYSIS_H
#define _GW_OPTICAL_IMAGE_ANALYSIS_H
#pragma once
#include "stdafx.h"
#include "gwStandardMetaDataAnalysis.h"
#include "gwStandardMetaDataFactory.h"

class gwOpticalImageAnalysis :public gwStandardMetadataAnalysis
{
	friend class gwStandardMetaDataFactory;
protected:
	gie2::CIE_OpticalImage_Type m_ieOpticalImage;
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
	gwOpticalImageAnalysis(xercesc::DOMNode* const& init );
	 gwOpticalImageAnalysis();
public:
	virtual ~gwOpticalImageAnalysis();
};
#endif