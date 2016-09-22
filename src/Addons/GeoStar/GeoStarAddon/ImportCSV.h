#pragma once
#include <string>
#include "Addon.h" 
class ImportCSV:public GIS::AddonBase
{ 
public:
	ImportCSV(void);
	virtual ~ImportCSV(void); 
	/// \brief Ö´ÐÐ²å¼þ
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};