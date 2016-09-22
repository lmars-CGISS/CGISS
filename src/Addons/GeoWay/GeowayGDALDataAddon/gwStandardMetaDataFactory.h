#ifndef _GW_STANDARD_META_DATA_FACTORY_H
#define _GW_STANDARD_META_DATA_FACTORY_H
#pragma once

#include "stdafx.h"
#include "gwStandardMetaDataAnalysis.h"
class gwStandardMetaDataFactory
{
public:
	static gwStandardMetaDataFactory* Instance()
	{
		static gwStandardMetaDataFactory s_factory;
		return &s_factory;
	}

	bool CreateMetaData(const string& strType,gwStandardMetadataAnalysis** pAnalysis);
};
#endif