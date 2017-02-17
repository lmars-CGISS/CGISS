#pragma once
#include "Addon.h" 
#include <string>
#include "GeoStarDLGAddonBase.h"
#include <VCTRW.h>

//����洢��vect�е�ʽ����
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
	//���ݷ���id��ѯstyle������
	std::string StyleName(long long symID);
	//�洢һ������Ϊstyle������sytle������
	std::string SaveStyle(gpkg::symbol &sym);


};

class ExportVCT:public GIS::AddonBase
{
	StyleCache m_StyleCache;
	//�����VCT�ļ��С�
	void WriteTo(VCTWriter& w,gpkg::content& content,gpkg::database_ptr db,GIS::Progress * nProgress,VCTID& id);

public:
	ExportVCT(void);
	virtual ~ExportVCT(void);
	/// \brief ִ�в��
	virtual const char* Execute(const char* strParameter,GIS::Progress * nProgress);
};

