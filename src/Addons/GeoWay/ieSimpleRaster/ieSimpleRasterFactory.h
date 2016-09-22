#ifndef _IE_SIMPLE_RASTER_FACTORY_H
#define _IE_SIMPLE_RASTER_FACTORY_H
#pragma once
#include "stdafx.h"
#include "ieSimpleRaster.h"
//class ieSimpleRaster;

class IE_SIMPLE_RASTER_EXT_CLASS ieSimpleRasterFactory
{
public:
	static ieSimpleRasterFactory* Instance()
	{
		static ieSimpleRasterFactory s_factory;
		return &s_factory;
	}

	/*!
	* \brief 打开Raster
	* \param strFilePath : const gwString & raster的绝对路径
	* \param pRaster : gwRefPtr<gwRaster> & raster对象
	* \param bReadOnly : gwBoolean 是否只读打开
	* \returns gwBoolean: 
	* \throws <exception class>: 
	* \remarks 
	* \see 
	*/
	ieSimpleRaster* OpenRaster(const std::string& strFilePath,
						/*ieSimpleRaster** pRaster,*/bool bReadOnly);	
	
	bool CreateRaster(const std::string& strFilePath,const ieSimpleRasterInfo& ieInfo,
		ieSimpleRaster** pRaster);

protected:
	ieSimpleRasterFactory(){};
	~ieSimpleRasterFactory(){};

};
#endif