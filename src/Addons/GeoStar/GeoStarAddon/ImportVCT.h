#pragma once

#include "Addon.h" 
#include <string>
#include "GeoStarDLGAddonBase.h"
#include <VCTRW.h>

//������ŵ���Ϣ��
class SymbolCache
{
	std::string m_VCTFile;
	gpkg::database_ptr m_DB;
	gpkg::symbols* m_pSymbols;
	gpkg::symbols_reference* m_pSymbolRef;
	//��¼�Ѿ��洢�����ű�ķ��ŵ�id��style��Ӧ��ϵ��
	std::map<std::string,long long> m_SymbolID;
	//�洢�ⲿ�ķ��ſ⡣
	std::map<std::string,std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> > m_CacheExtLib;

	std::string SymbolToString(GeoStar::Kernel::GsSymbol* pSym);
	std::string ToPointSymbol(VCTStyle& style);
	std::string ToLineSymbol(VCTStyle& style);
	std::string ToFillSymbol(VCTStyle& style);
	std::string ToTextSymbol(VCTStyle& style);
	
	std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> SymbolLib(const char* libName);

public:
	SymbolCache();
	void Attach(gpkg::database_ptr &db);
	//��VCT�ļ�
	void BindVCT(const char* vctFile);

	//����VCT��style��ѯ��¼�����ſ�ķ���id�����û���򷵻�0
	long long SymbolIDFromStyle(const char* style);
	//��һ��VCT��style�洢Ϊ���ţ������ط��ŵĴ洢id
	long long StoreStyleToSymbol(VCTStyle& style,VCT_GEOMETRY_TYPE eType);
	//�洢����ͷ��ŵĹ�ϵ
	void StoreSymbolRelation(const char* fcsname,long long fid,long long sid,const char* filter = NULL);

};


/// \brief ����VCT��ʽ
class ImportVCT:public GIS::AddonBase
{
	//���Ż��档
	SymbolCache m_SymbolCache;

	/// \brief ����һ���ļ�
	virtual bool ImportVCTFile(GeoStar::Utility::GsFile& file,gpkg::database_ptr& db,GIS::Progress * nProgress);
	/// \brief �����ļ��е�һ��������
	virtual bool ImportFeatureCode(VCTParser &parser,
									VCTFeatureCode& code,
									gpkg::database_ptr& db,
									GIS::Progress * nProgress);

public:
	ImportVCT(void);
	~ImportVCT(void);
	
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);

};

