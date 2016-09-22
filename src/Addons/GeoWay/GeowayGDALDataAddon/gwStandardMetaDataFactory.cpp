#include "gwStandardMetaDataFactory.h"
#include "gwOpticalImageAnalysis.h"
bool gwStandardMetaDataFactory::CreateMetaData(const string& strType,gwStandardMetadataAnalysis** pAnalysis)
{
	if(strType=="")
		return NULL;
	
	if(strstr(strType.data(),"IE_OpticalImage"))
	{
		*pAnalysis = new gwOpticalImageAnalysis;
	}
	return *pAnalysis != NULL;
}