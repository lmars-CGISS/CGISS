#pragma once
#include <string>
#include "GeoStarDLGAddonBase.h"
class ImportFCS:public GeoStarDLGAddonBase
{ 
public:
	ImportFCS(void);
	virtual ~ImportFCS(void); 
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

//����GeoPackage
class ImportGPKG:public GeoStarDLGAddonBase
{
public:
	ImportGPKG(void);
	virtual ~ImportGPKG(void); 
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};


//����DOM
class ImportDOM:public GIS::AddonBase
{
	
	//�ж�һ��·���Ƿ�folder
	bool IsFolder(const char* path);
public:
	ImportDOM(void);
	virtual ~ImportDOM(void); 
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

