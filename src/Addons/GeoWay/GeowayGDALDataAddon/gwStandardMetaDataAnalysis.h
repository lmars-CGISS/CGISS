#ifndef _GW_STANDARD_META_DATA_ANALYSIS_H
#define _GW_STANDARD_META_DATA_ANALYSIS_H
#pragma once
#include "stdafx.h"

class gwStandardMetadataAnalysis 
{
protected:
	string m_strMetaData;
	ieSimpleRasterInfo m_gInfo;
	string m_XMLPath;
	gie::gie2::Cgie m_gie;
public:
	virtual void WriteStandardMetadata(const ieSimpleRasterInfo& rInfo)  = 0;
	virtual void WriteDEMMetadata(const char* strPath)  = 0;
	virtual void WriteDOMMetadata(const char* strPath)  = 0;
	virtual void ReadStanardMetadata()  = 0;
	virtual bool SaveMetaData() = 0;
	virtual void setRasterInfo(const ieSimpleRasterInfo& rInfo) = 0;
	virtual void setStandardMetaDataFilePath(const string& strPath) = 0;
	virtual const ieSimpleRasterInfo getRasterInfo() = 0;
	virtual const string& getMetaData() = 0;
protected:
	gwStandardMetadataAnalysis():m_gie(NULL){};
public:
	~gwStandardMetadataAnalysis(){};
};
#endif