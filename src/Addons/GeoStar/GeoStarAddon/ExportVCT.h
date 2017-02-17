#pragma once
#include "Addon.h" 
#include <string>
#include "GeoStarDLGAddonBase.h"
#include <VCTRW.h>

//缓存存储到vect中的式样。
class StyleCache
{
	VCTWriter* m_Writer;
	int m_nIndex;
	std::map<long long,std::string> m_StyleName;
	std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> m_ptrSymLib;
	void SaveStyle(GeoStar::Kernel::GsPointSymbol* pSym,const std::string& name);
	void SaveStyle(GeoStar::Kernel::GsLineSymbol* pSym,const std::string& name);
	void SaveStyle(GeoStar::Kernel::GsFillSymbol* pSym,const std::string& name);
	void SaveStyle(GeoStar::Kernel::GsTextSymbol* pSym,const std::string& name);
	std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> SymbolLib();
public:
	StyleCache();
	void Commit();
	void Attach(VCTWriter* w);
	//根据符号id查询style的名称
	std::string StyleName(long long symID);
	//存储一个符号为style，返回sytle的明恒
	std::string SaveStyle(gpkg::symbol &sym);


};

class ExportVCT:public GIS::AddonBase
{
	StyleCache m_StyleCache;
	//输出到VCT文件中。
	void WriteTo(VCTWriter& w,gpkg::content& content,gpkg::database_ptr db,GIS::Progress * nProgress,VCTID& id);

public:
	ExportVCT(void);
	virtual ~ExportVCT(void);
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

