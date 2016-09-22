#pragma once
#include "Addon.h" 
class GeoStarDLGAddonBase:public GIS::AddonBase
{
protected:
	void ExecuteTranslate(GeoStar::Kernel::GsGeoDatabase* pInput,
		GeoStar::Kernel::GsGeoDatabase* pOutput,GIS::Progress * nProgress);

public:
	GeoStarDLGAddonBase(void);
	~GeoStarDLGAddonBase(void);
	
};

