#ifndef _IE_SIMPLE_RASTER_H
#define _IE_SIMPLE_RASTER_H
#pragma once
#include "stdafx.h"
#include "ieSimpleRasterInfo.h"
//#include "ieSimpleRasterFactory.h"
//class ieSimpleRasterFactory;
class IE_SIMPLE_RASTER_EXT_CLASS ieSimpleRaster
{
	friend class ieSimpleRasterFactory;
private:
	GDALDataset*	   m_pDataset;
	ieSimpleRasterInfo m_RasterInfo;
public:
	bool ConnectRasterSource(GDALDataset* pNewDataSource);
	void setRasterInfo(const ieSimpleRasterInfo& ieInfo);
	void GetRasterInfo(ieSimpleRasterInfo& gInfo);
	const ieSimpleRasterInfo& GetRasterInfo();
	bool SaveMetaData();
protected:
	ieSimpleRaster();
public:
	
	~ieSimpleRaster();
};
#endif