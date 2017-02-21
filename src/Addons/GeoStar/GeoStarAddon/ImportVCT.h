#pragma once

#include "Addon.h" 
#include <string>
#include "GeoStarDLGAddonBase.h"
#include <VCTRW.h>

//缓存符号的信息。
class VCTContext
{
	std::string m_VCTFile;
	gpkg::database_ptr m_DB;
	gpkg::symbol_table* m_pSymbols;
	gpkg::symbol_reference_table* m_pSymbolRef;
	//记录已经存储到符号表的符号的id和style对应关系。
	std::map<std::string,long long> m_SymbolID;
	long long						m_MetadataID;

	//存储外部的符号库。
	std::map<std::string,std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> > m_CacheExtLib;

	std::string SymbolToString(GeoStar::Kernel::GsSymbol* pSym);
	std::string ToPointSymbol(VCTStyle& style);
	std::string ToLineSymbol(VCTStyle& style);
	std::string ToFillSymbol(VCTStyle& style);
	std::string ToTextSymbol(VCTStyle& style);
	
	std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> SymbolLib(const char* libName);
	
public:
	VCTContext();

	void Attach(gpkg::database_ptr &db);
	//绑定VCT文件
	void BindVCT(const char* vctFile);
	//返回VCT文件的元数据，如果存在的话
	std::string MetadataFile();
	long long MetaDataID();
	long long StoreMetadata();
	//存储元数据的引用
	void StoreMetadataReference(const char* table_name);


	//根据VCT的style查询记录到符号库的符号id。如果没有则返回0
	long long SymbolIDFromStyle(const char* style);
	//将一个VCT的style存储为符号，并返回符号的存储id
	long long StoreStyleToSymbol(VCTStyle& style,VCT_GEOMETRY_TYPE eType);
	//存储地物和符号的关系
	void StoreSymbolRelation(const char* fcsname,long long fid,long long sid,const char* filter = NULL);

};


/// \brief 导入VCT格式
class ImportVCT:public GIS::AddonBase
{
	//符号缓存。
	VCTContext m_VCTContext;

	/// \brief 导入一个文件
	virtual bool ImportVCTFile(GeoStar::Utility::GsFile& file,gpkg::database_ptr& db,GIS::Progress * nProgress);
	/// \brief 导入文件中的一个地物类
	virtual bool ImportFeatureCode(VCTParser &parser,
									VCTFeatureCode& code,
									gpkg::database_ptr& db,
									GIS::Progress * nProgress);

public:
	ImportVCT(void);
	~ImportVCT(void);
	
	/// \brief 执行插件
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);

};

