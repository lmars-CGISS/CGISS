#include "stdafx.h"
#include "../GeowayGDALDataAddon/Addon.h"
#include "../GeowayGDALDataAddon/gwTransform.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//转换命令行参数
	wchar_t** arr = new wchar_t*[argc];
	bool	bCalc = true;
	if (sizeof(_TCHAR)==1)
	{
		for (gwInt32 i=0; i<argc; i++)
		{
			char* sz  = (char*)argv[i];
			gwInt32 buffer_size = strlen(sz)+1;
			wchar_t* dst_wstr = new wchar_t[buffer_size];
			wmemset(dst_wstr, 0, buffer_size);
			mbstowcs(dst_wstr, sz, buffer_size);

			*(arr+i) = dst_wstr;
		}
	}
	else
	{
		if (arr != NULL)
		{
			delete []arr;
			arr = NULL;
		}
		bCalc = false;
		arr =(wchar_t**) argv;
	}

	gwArgumentParser aParse(&argc,arr);
	aParse.getApplicationUsage()->setCommandLineUsage(L"GdalTest");
	aParse.getApplicationUsage()->AddCommandLineOption(L"-Parameter",L"");
	gwApplicationUsage::Type type;
	gwString strRootPath = L"";
	gwString strCopyPath = L"";
	if ((type = aParse.ReadHelpType()))
	{
		aParse.getApplicationUsage()->Write(std::wcout, type);
		return 0;
	}
	if (aParse.errors())
	{
		aParse.WriteErrorMessages(std::wcout);
		return 0;
	}
	// = "<GIS><Parameter Key=\"DataType\"><Value>File</Value></Parameter><Parameter Key=\"Path\"><Value>d:\\TestData\\db\\10000.db</Value></Parameter><Parameter Key=\"GPKGPath\"><Value>d:\\TestData\\db\\10000.gpkg</Value></Parameter></GIS>";
	gwString strType;
	gwString strPath;
	aParse.Read(L"-P",strPath);
	aParse.Read(L"-Type",strType);
	DOMDocument *m_pDoc = gwXercesHelper::getInstance()->Parse(strPath);
	gwString strPrama =  gwXercesHelper::getInstance()->SaveXML(m_pDoc,true);

	gwStopwatch sGWTime(gwFALSE), sAETime(gwFALSE);
	gwDouble dGWTime = 0;
	sGWTime.Start();
	if(strType.Compare(L"InGRID",gwCaseSensitivity_Insensitive) == 0)
	{
		gwString strE = ImportRaster()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	if(strType.Compare(L"OutGRID",gwCaseSensitivity_Insensitive) == 0)
	{
		ExportRaster()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	if(strType.Compare(L"InIMG",gwCaseSensitivity_Insensitive) == 0)
	{
		ImportRaster()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	if(strType.Compare(L"OutIMG",gwCaseSensitivity_Insensitive) == 0)
	{
		ExportRaster()->Execute(strPrama.ToPlatform().data(),NULL);
	}

	if(strType.Compare(L"Inmdb",gwCaseSensitivity_Insensitive) == 0)
	{
		ImportMdb()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	if(strType.Compare(L"Outmdb",gwCaseSensitivity_Insensitive) == 0)
	{
		//ExportMdb()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	if(strType.Compare(L"Infgdb",gwCaseSensitivity_Insensitive) == 0)
	{
		ImportFgdb()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	if(strType.Compare(L"Outfgdb",gwCaseSensitivity_Insensitive) == 0)
	{
		ExportFgdb()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	if(strType.Compare(L"Indb",gwCaseSensitivity_Insensitive) == 0)
	{
		ImportGeowayDB()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	if(strType.Compare(L"Outdb",gwCaseSensitivity_Insensitive) == 0)
	{
		ExportGeowayDB()->Execute(strPrama.ToPlatform().data(),NULL);
	}
	sGWTime.Stop();
	dGWTime += sGWTime.GetConsumedTime();
	std::cout<<"耗时（ms） "<<dGWTime<<std::endl;
	return 1;
}