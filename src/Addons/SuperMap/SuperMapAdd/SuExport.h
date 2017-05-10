
#pragma once
#include <string>
#include "SuAddBase.h"

//������GeoPackage
class ExportGPKG:public SuAddonBase
{
public:
	ExportGPKG(void);

	virtual ~ExportGPKG(void); 

	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

class ExportGTIFF:public SuAddonBase
{ 
public:
	ExportGTIFF(void);

	virtual ~ExportGTIFF(void); 

	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};