#ifndef _IE_SIMPLE_RASTER_INFO_H
#define _IE_SIMPLE_RASTER_INFO_H
#pragma once
#include "stdafx.h"
#include "ieSimpleStandardMetaData.h"

IE_SIMPLE_RASTER_EXT_CLASS typedef enum tagRasterPosEnum
{	
	RasterPosEnum_Unknown	= -1,
	RasterPosEnum_LeftTop_Corner	= 0,
	RasterPosEnum_LeftTop_Center	= 1,
	RasterPosEnum_LeftBottom_Corner	= 2,
	RasterPosEnum_LeftBottom_Center	= 3,
}RasterPosEnum;

class IE_SIMPLE_RASTER_EXT_CLASS ieSimpleRasterInfo
{
public:
	ieSimpleRasterInfo(){};
	~ieSimpleRasterInfo(){
		m_vPyramidRates.clear();
		m_vecColorInterp.clear();
	};

public:

	std::string            m_strRasterDataPath;    //栅格数据全路径名
	std::string            m_strMetaDataPath;      //栅格数据辅助信息全路径名
	std::string            m_strFormat;            //格式说明如“GTIFF,TIFF,HFA,ARCINFO/BIL”
	int             m_nWidth;               //宽
	int             m_nHeight;              //高
	int             m_nBandCount;           //波段数
	GDALDataType     m_eDataType;            //数据类型
	//	gwDouble            m_dResolutionX;         //X方向地面分辨率
	//	gwDouble            m_dResolutionY;         //Y方向地面分辨率
	int             m_nPalCount;            //带有的调色板色表的项数
	GDALColorInterp		    m_eImageMode;
	double		    m_dDPIX;
	double		    m_dDPIY;
	/** Tile */
	bool			m_bIsTileModel;
	int             m_nTileWidth;
	int             m_nTileHeight;

	/**Pyramidal**/
	int             m_nPyramidalLevel;		/** 金字塔级数 */
	bool			m_bExistPyramid;		/** 是否存在金字塔 */
	bool			m_bExistPyramidFile;	/** 是否存在金字塔文件 */
	bool			m_bPyramidCompressed;	/** 金字塔是否压缩存储 */
	double			m_dPyramidRate;			/** 金字塔采样比率 */
	std::vector<double>	m_vPyramidRates;	/** 金字塔相邻层级之间采样比率 目前只有GDAL支持*/

	double m_vecParamRaster2Geo[6];
	//其他属性
	//std::map<std::string, std::string> m_mapTagValue;
	RasterPosEnum     m_eRasterOrgPos;
	/** TFW属性 */
	/*gwRasterPosEnum		m_eTfwPosEnum;
	gwTiffExportType	m_eTiffExportType;
	gwBoolean           m_bCompressed;*/

	/**空间参考属性*/
	std::string            m_strProjectionRef;       /**空间参考信息*/

	/** 像方坐标属性*/
	/** DEM属性 */
	/** DEM属性 */
	bool           m_bHavingInvalidValue;    /**是否有无效值*/
	double            m_dInvalidValue;          /**无效值*/
	int			    m_nDataOffset;            /**偏移量*/
	int		        m_nHZoom;                 /**放大倍数*/
	bool	        m_bDemIsXYZ;              /**数据是否是按（XYZ)存储*/
	//gwDemType           m_eDemType;               /**DEM数据类型*/
	/** 波段的色彩设置*/
	std::vector<GDALColorInterp> m_vecColorInterp;  /**波段所属色调设置*/

	double	left;
	double	right;
	double	top;
	double	bottom;

	ieSimpleStandardMetaData m_MetaData;
	//std::vector<GDALColorEntry*> m_pGDALColorEntry;
	GDALPaletteInterp m_ePaletteInterp;
	bool m_bCompressed;
};
#endif