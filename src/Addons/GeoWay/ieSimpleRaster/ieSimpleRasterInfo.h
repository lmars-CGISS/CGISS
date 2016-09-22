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

	std::string            m_strRasterDataPath;    //դ������ȫ·����
	std::string            m_strMetaDataPath;      //դ�����ݸ�����Ϣȫ·����
	std::string            m_strFormat;            //��ʽ˵���硰GTIFF,TIFF,HFA,ARCINFO/BIL��
	int             m_nWidth;               //��
	int             m_nHeight;              //��
	int             m_nBandCount;           //������
	GDALDataType     m_eDataType;            //��������
	//	gwDouble            m_dResolutionX;         //X�������ֱ���
	//	gwDouble            m_dResolutionY;         //Y�������ֱ���
	int             m_nPalCount;            //���еĵ�ɫ��ɫ�������
	GDALColorInterp		    m_eImageMode;
	double		    m_dDPIX;
	double		    m_dDPIY;
	/** Tile */
	bool			m_bIsTileModel;
	int             m_nTileWidth;
	int             m_nTileHeight;

	/**Pyramidal**/
	int             m_nPyramidalLevel;		/** ���������� */
	bool			m_bExistPyramid;		/** �Ƿ���ڽ����� */
	bool			m_bExistPyramidFile;	/** �Ƿ���ڽ������ļ� */
	bool			m_bPyramidCompressed;	/** �������Ƿ�ѹ���洢 */
	double			m_dPyramidRate;			/** �������������� */
	std::vector<double>	m_vPyramidRates;	/** ���������ڲ㼶֮��������� Ŀǰֻ��GDAL֧��*/

	double m_vecParamRaster2Geo[6];
	//��������
	//std::map<std::string, std::string> m_mapTagValue;
	RasterPosEnum     m_eRasterOrgPos;
	/** TFW���� */
	/*gwRasterPosEnum		m_eTfwPosEnum;
	gwTiffExportType	m_eTiffExportType;
	gwBoolean           m_bCompressed;*/

	/**�ռ�ο�����*/
	std::string            m_strProjectionRef;       /**�ռ�ο���Ϣ*/

	/** ����������*/
	/** DEM���� */
	/** DEM���� */
	bool           m_bHavingInvalidValue;    /**�Ƿ�����Чֵ*/
	double            m_dInvalidValue;          /**��Чֵ*/
	int			    m_nDataOffset;            /**ƫ����*/
	int		        m_nHZoom;                 /**�Ŵ���*/
	bool	        m_bDemIsXYZ;              /**�����Ƿ��ǰ���XYZ)�洢*/
	//gwDemType           m_eDemType;               /**DEM��������*/
	/** ���ε�ɫ������*/
	std::vector<GDALColorInterp> m_vecColorInterp;  /**��������ɫ������*/

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