#pragma once

#include "Addon.h" 
class ExportCSV:public GIS::AddonBase
{
public:
	ExportCSV(void);
	virtual ~ExportCSV(void);
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

