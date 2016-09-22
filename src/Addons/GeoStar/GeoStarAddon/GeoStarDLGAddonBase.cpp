#include "StdAfx.h"
#include "GeoStarDLGAddonBase.h"


GeoStarDLGAddonBase::GeoStarDLGAddonBase(void)
{
}


GeoStarDLGAddonBase::~GeoStarDLGAddonBase(void)
{
}
void GeoStarDLGAddonBase::ExecuteTranslate(GeoStar::Kernel::GsGeoDatabase* pInput,
		GeoStar::Kernel::GsGeoDatabase* pOutput,GIS::Progress * pProgress)
{
	//��ȡGeoPackage�����е�����Դ
	std::vector<std::string> vecNames;
	pInput->DataRoomNames(GeoStar::Kernel::eFeatureClass,vecNames);
	std::vector<std::string>::iterator it = vecNames.begin();
	std::string strLog;
	for(;it != vecNames.end();it++)
	{
		GeoStar::Kernel::GsFeatureClassPtr ptrSource = pInput->OpenFeatureClass(it->c_str());
		if(!ptrSource)
		{
			strLog = "��Դ������";
			strLog+=it->c_str();
			strLog+="ʧ��";
			
			pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
			continue;
		}
		GeoStar::Kernel::GsFields fs = ptrSource->Fields();
		fs.Fields.erase(fs.Fields.begin());
		fs.Fields.erase(fs.Fields.begin());
		
		GeoStar::Kernel::GsFeatureClassPtr ptrTarget = pOutput->CreateFeatureClass(it->c_str(),fs,
																	ptrSource->GeometryColumnInfo(),
																	ptrSource->SpatialReference());

		if(!ptrTarget)
		{
			strLog = "����Ŀ�������";
			strLog+=it->c_str();
			strLog+="ʧ��";
			
			pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eError);
			continue;
		} 
		ptrTarget->DeleteSpatialIndex();
		

		__int64 nCount = ptrSource->FeatureCount();
		__int64  nPos = 0;
		GeoStar::Kernel::GsFeatureCursorPtr ptrCursor = ptrSource->Search();
		GeoStar::Kernel::GsFeaturePtr ptrFea = ptrTarget->CreateFeature();
		strLog="ת��������"; 
		
		pProgress->OnProgress(nPos,nCount,strLog.c_str(),it->c_str());
		int nCommit =0;
		ptrTarget->StartTransaction();
		while(ptrCursor->Next(ptrFea))
		{
			nCommit++; 
			nPos++;
			pProgress->OnProgress(nPos,nCount,strLog.c_str(),it->c_str());
			ptrFea->OID(-1);
			ptrFea->Store();
			if(nCommit >1000)
			{
				ptrTarget->CommitTransaction();
				ptrTarget->StartTransaction();
				nCommit = 0;
			}
			
		}
		if(nCommit >0)
			ptrTarget->CommitTransaction();
		
		strLog="�����ռ�����"; 
		
		pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);
		ptrTarget->CreateSpatialIndex();

	}
}