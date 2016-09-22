#pragma once

#include "Addon.h" 
#include <string>
#include "GeoStarDLGAddonBase.h"
#include <VCTRW.h>


/// \brief ����VCT��ʽ
class ImportVCT:public GIS::AddonBase
{
	/// \brief ����һ���ļ�
	virtual bool ImportOne(GeoStar::Utility::GsFile& file,gpkg::database_ptr& db,GIS::Progress * nProgress);
	/// \brief �����ļ��е�һ��������
	virtual bool ImportOne(VCTParser &parser,VCTFeatureCode& code,gpkg::database_ptr& db,GIS::Progress * nProgress);

public:
	ImportVCT(void);
	~ImportVCT(void);
	
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);

};

