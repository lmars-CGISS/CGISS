#include "ieSimpleRaster.h"

ieSimpleRaster::ieSimpleRaster()
{
	m_pDataset = NULL;
}
ieSimpleRaster::~ieSimpleRaster()
{
	if(m_pDataset)
	{
		GDALClose(m_pDataset);
		m_pDataset = NULL;
	}
}
const ieSimpleRasterInfo& ieSimpleRaster::GetRasterInfo()
{
	return m_RasterInfo;
}
void ieSimpleRaster::setRasterInfo(const ieSimpleRasterInfo& ieInfo)
{
	m_RasterInfo = ieInfo;
}
void ieSimpleRaster::GetRasterInfo(ieSimpleRasterInfo& gInfo)
{
	gInfo = m_RasterInfo;
}
bool ieSimpleRaster::ConnectRasterSource(GDALDataset* pNewDataSource)
{
	m_pDataset = pNewDataSource;
	if(m_pDataset!=NULL)
		return true;
	return false;
}
bool ieSimpleRaster::SaveMetaData()
{
	CPLErr cErr = m_pDataset->SetMetadataItem(GW_SimpleMetaDataItemName,m_RasterInfo.m_MetaData.getXMLContent(),GW_SimpleMetaDataItemName);
	return cErr == CE_None;
}