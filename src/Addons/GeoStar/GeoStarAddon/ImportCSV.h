#pragma once
#include <string>
#include "Addon.h" 
class ImportCSV:public GIS::AddonBase
{ 
public:
	ImportCSV(void);
	virtual ~ImportCSV(void); 
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};