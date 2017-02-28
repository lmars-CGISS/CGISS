#include "StdAfx.h"
#include "ImportVCT.h"
#include <iostream>
#include <io.h>
#include "time.h"
#include "WKBHelp.h"

#pragma comment(lib,"LibVCT")

std::string ToUtf8(const char* str)
{
	return GeoStar::Utility::GsCW2A(GeoStar::Utility::GsCA2W(str).m_WStr,GeoStar::Utility::eCP_UTF8).m_Str;
}
VCTContext::VCTContext()
{
	m_pSymbols = NULL;
	m_pSymbolRef = NULL;
}
//����vct�ļ���Ԫ�����ļ��ļ�����
std::string MetaDataFile(const char* vctFile,const char* ext)
{
	GeoStar::Utility::GsFile file(vctFile);
	file.ChangeExtension(ext);
	if(file.Exists()) return file.Path();
	
	std::string strFile = vctFile;
	strFile+=".";
	strFile+=ext;
	if(GeoStar::Utility::GsFileSystem::Exists(strFile.c_str()))
		return strFile;
	return std::string();
}
//����VCT�ļ���Ԫ���ݣ�������ڵĻ�
std::string VCTContext::MetadataFile()
{
	
	//�����meta�ļ�
	std::string strMetaFile = MetaDataFile(m_VCTFile.c_str(),"meta");
	if(!strMetaFile.empty()) return strMetaFile;

	//�����xml�ļ���
	strMetaFile = MetaDataFile(m_VCTFile.c_str(),"xml");
	if(!strMetaFile.empty()) return strMetaFile;

	//������������չ����Ԫ����Ҳ��˴���
	return std::string();
}
long long VCTContext::MetaDataID()
{
	return m_MetadataID;
}
long long VCTContext::StoreMetadata()
{
	gpkg::metadata_table* table = m_DB->metadata_table();
	gpkg::metadata meta;
	meta.md_scope = "dataset";
	meta.md_standard_uri = "GeoStarXMLMetadata";
	meta.mime_type = "text/xml";
	std::ifstream f(MetadataFile().c_str());
	
	meta.data = std::string((std::istreambuf_iterator<char>(f)),  
                 std::istreambuf_iterator<char>()); 

	
	table->add(meta);

	m_MetadataID =  meta.id;
	return m_MetadataID;
}
//�洢Ԫ���ݵ�����
void VCTContext::StoreMetadataReference(const char* table_name)
{
	gpkg::metadata_reference_table* table = m_DB->metadata_reference_table();
	gpkg::metadata_reference ref;
	ref.reference_scope = "table";
	ref.table_name = table_name;
	ref.row_id_value = 0;
	ref.md_file_id = m_MetadataID;
	
	//��idΪ0
	ref.md_parent_id  = 0;
	
	//���һ����¼��
	table->add(ref);
}


//��VCT�ļ�
void VCTContext::BindVCT(const char* vctFile)
{
	m_MetadataID = 0;
	//��շ��ŵ�����id�Ļ��棬��Ϊ����ÿ��VCT���ԣ���style������VCT�ļ��ڲ���Ψһ�ġ�
	m_SymbolID.clear();
	m_CacheExtLib.clear();

	m_VCTFile = vctFile;
}
void VCTContext::Attach(gpkg::database_ptr &db)
{
	m_pSymbols = NULL;
	m_pSymbolRef = NULL;
	m_DB = db;
}
std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> VCTContext::SymbolLib(const char* libName)
{
	std::map<std::string,std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> >::iterator it = m_CacheExtLib.find(libName);
	if(it != m_CacheExtLib.end())
		return it->second;
	std::string strSymLibFile = libName;
	//������ſ��·�����Ǿ���·��
	if(!GeoStar::Utility::GsFileSystem::IsPathRooted(libName))
	{
		//vct�ļ����ڵ�Ŀ¼
		std::string strFolder = GeoStar::Utility::GsFile(m_VCTFile.c_str()).Parent().Path();
		//��vct���ڵ�Ŀ¼�ͷ��ſ���ɾ���·����
		strSymLibFile = GeoStar::Utility::GsFileSystem::Combine(strFolder.c_str(),libName);
	}

	//������ſ��ļ��ǲ����ڵ��򷵻�null
	if(!GeoStar::Utility::GsFileSystem::Exists(strSymLibFile.c_str()))
		return NULL;

	std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrSym(new GeoStar::Kernel::GsSymbolLibrary(strSymLibFile.c_str()));

	m_CacheExtLib[libName] = ptrSym;
	return ptrSym;
}
std::string VCTContext::SymbolToString(GeoStar::Kernel::GsSymbol* pSym)
{
	return GeoStar::Kernel::GsSymbolLibrary::ToString(pSym,GeoStar::Kernel::eGenernalFormat);
}
std::string VCTContext::ToPointSymbol(VCTStyle& style)
{
	GeoStar::Kernel::GsPointSymbolPtr ptrSym = new GeoStar::Kernel::GsSimplePointSymbol();
	if(ptrSym->Name().empty())
		ptrSym->Name(style.strID.c_str());
	std::string strSymLib;
	int nSymID = -1;
	std::vector<VCTPairEx>::iterator it =	style.vecPairs.begin();
	for(;it != style.vecPairs.end();it++)
	{
		if(stricmp(it->strKey.c_str(),"LAYERNAME")==0)
			ptrSym->Name(ToUtf8(it->strValue.c_str()).c_str());
		else if(stricmp(it->strKey.c_str(),"COLOR")==0)
			ptrSym->Color(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		else if(stricmp(it->strKey.c_str(),"FORECOLOR")==0)
			ptrSym->Color(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		else if(stricmp(it->strKey.c_str(),"POINTSIZE")==0)
			ptrSym->Size(atof(it->strValue.c_str()));
		else if(stricmp(it->strKey.c_str(),"SYMBOLLIBLOCATION")==0)
			strSymLib = it->strValue;
		else if(stricmp(it->strKey.c_str(),"SYMBOLID")==0)
			nSymID = atoi(it->strValue.c_str());
	}

	//������ڷ��ſ⣬�ҷ���id��Ч��ӷ��ſ�LoadSymbol
	if(!strSymLib.empty() && nSymID > 0)
	{
		//��ȡ�ⲿ���ſ�
		std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib(strSymLib.c_str());
		if(ptrLib)
		{
			//����ɹ����ⲿ���ſ������code��÷��š�
			GeoStar::Kernel::GsPointSymbolPtr ptrSymFromLib = ptrLib->SymbolByCode(nSymID);
			if(ptrSymFromLib) //����ɹ���ȡ�ⲿ���ţ���vct�е������Ϣͬ�����ⲿ�����в������ⲿ����
			{
				ptrSymFromLib->Size(ptrSym->Size());
				ptrSymFromLib->Color(ptrSym->Color());
				ptrSymFromLib->Name(ptrSym->Name().c_str());
				return SymbolToString(ptrSymFromLib);
			}
		}
	}

	//������֤���޷����ⲿ���ţ�����û�������ⲿ���ţ���ֱ��ʹ�ü򵥷��������
	return SymbolToString(ptrSym);
}
std::string VCTContext::ToLineSymbol(VCTStyle& style)
{
	GeoStar::Kernel::GsLineSymbolPtr ptrSym = new GeoStar::Kernel::GsSimpleLineSymbol();

	if(ptrSym->Name().empty())
		ptrSym->Name(style.strID.c_str());

	std::string strSymLib;
	int nSymID = -1;
	std::vector<VCTPairEx>::iterator it =	style.vecPairs.begin();
	for(;it != style.vecPairs.end();it++)
	{
		if(stricmp(it->strKey.c_str(),"LAYERNAME")==0)
			ptrSym->Name(ToUtf8(it->strValue.c_str()).c_str());
		else if(stricmp(it->strKey.c_str(),"COLOR")==0)
			ptrSym->Color(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		else if(stricmp(it->strKey.c_str(),"FORECOLOR")==0)
			ptrSym->Color(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		else if(stricmp(it->strKey.c_str(),"LINEWIDTH")==0)
			ptrSym->Width(atof(it->strValue.c_str()));
		else if(stricmp(it->strKey.c_str(),"SYMBOLLIBLOCATION")==0)
			strSymLib = it->strValue;
		else if(stricmp(it->strKey.c_str(),"SYMBOLID")==0)
			nSymID = atoi(it->strValue.c_str());
	}

	//������ڷ��ſ⣬�ҷ���id��Ч��ӷ��ſ�LoadSymbol
	if(!strSymLib.empty() && nSymID > 0)
	{
		//��ȡ�ⲿ���ſ�
		std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib(strSymLib.c_str());
		if(ptrLib)
		{
			//����ɹ����ⲿ���ſ������code��÷��š�
			GeoStar::Kernel::GsLineSymbolPtr ptrSymFromLib = ptrLib->SymbolByCode(nSymID);
			if(ptrSymFromLib) //����ɹ���ȡ�ⲿ���ţ���vct�е������Ϣͬ�����ⲿ�����в������ⲿ����
			{
				ptrSymFromLib->Width(ptrSym->Width());
				ptrSymFromLib->Color(ptrSym->Color());
				ptrSymFromLib->Name(ptrSym->Name().c_str());
				return SymbolToString(ptrSymFromLib);
			}
		}
	}

	//������֤���޷����ⲿ���ţ�����û�������ⲿ���ţ���ֱ��ʹ�ü򵥷��������
	return SymbolToString(ptrSym);
}
std::string VCTContext::ToFillSymbol(VCTStyle& style)
{
	GeoStar::Kernel::GsFillSymbolPtr ptrSym = new GeoStar::Kernel::GsSimpleFillSymbol();

	if(ptrSym->Name().empty())
		ptrSym->Name(style.strID.c_str());
	
	std::string strSymLib;
	int nSymID = -1;
	bool bOutWidth = false;
	bool bOutColor = false;
	std::vector<VCTPairEx>::iterator it =	style.vecPairs.begin();
	for(;it != style.vecPairs.end();it++)
	{
		if(stricmp(it->strKey.c_str(),"LAYERNAME")==0)
			ptrSym->Name(ToUtf8(it->strValue.c_str()).c_str());
		else if(stricmp(it->strKey.c_str(),"COLOR")==0)
			ptrSym->FillColor(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		else if(stricmp(it->strKey.c_str(),"LINEWIDTH")==0)
		{
			bOutWidth = true;
			ptrSym->Outline()->Width(atof(it->strValue.c_str()));
		}
		else if(stricmp(it->strKey.c_str(),"FORECOLOR")==0)
		{
			bOutColor = true;
			ptrSym->Outline()->Color(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		}
		else if(stricmp(it->strKey.c_str(),"SYMBOLLIBLOCATION")==0)
			strSymLib = it->strValue;
		else if(stricmp(it->strKey.c_str(),"SYMBOLID")==0)
			nSymID = atoi(it->strValue.c_str());
	}

	//������ڷ��ſ⣬�ҷ���id��Ч��ӷ��ſ�LoadSymbol
	if(!strSymLib.empty() && nSymID > 0)
	{
		//��ȡ�ⲿ���ſ�
		std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib(strSymLib.c_str());
		if(ptrLib)
		{
			//����ɹ����ⲿ���ſ������code��÷��š�
			GeoStar::Kernel::GsFillSymbolPtr ptrSymFromLib = ptrLib->SymbolByCode(nSymID);
			if(ptrSymFromLib) //����ɹ���ȡ�ⲿ���ţ���vct�е������Ϣͬ�����ⲿ�����в������ⲿ����
			{
				if(bOutColor && ptrSymFromLib->Outline())
					ptrSymFromLib->Outline()->Color(ptrSym->Outline()->Color());
				if(bOutWidth && ptrSymFromLib->Outline())
					ptrSymFromLib->Outline()->Width(ptrSym->Outline()->Width());
				
				ptrSymFromLib->FillColor(ptrSym->FillColor());
				ptrSymFromLib->Name(ptrSym->Name().c_str());
				return SymbolToString(ptrSymFromLib);
			}
		}
	}

	//������֤���޷����ⲿ���ţ�����û�������ⲿ���ţ���ֱ��ʹ�ü򵥷��������
	return SymbolToString(ptrSym);
}
std::string VCTContext::ToTextSymbol(VCTStyle& style)
{
	GeoStar::Kernel::GsTextSymbolPtr ptrSym = new GeoStar::Kernel::GsTextSymbol();
	std::vector<VCTPairEx>::iterator it =	style.vecPairs.begin();
	for(;it != style.vecPairs.end();it++)
	{
		if(stricmp(it->strKey.c_str(),"LAYERNAME")==0)
			ptrSym->Name(it->strValue.c_str());
		else if(stricmp(it->strKey.c_str(),"COLOR")==0)
			ptrSym->Color(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		else if(stricmp(it->strKey.c_str(),"FORECOLOR")==0)
			ptrSym->Color(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		else if(stricmp(it->strKey.c_str(),"BACKCOLOR")==0)
			ptrSym->BackgroundColor(GeoStar::Kernel::GsColor::FromCOLORREF(atoi(it->strValue.c_str())));
		else if(stricmp(it->strKey.c_str(),"SYMBOLID")==0)
			ptrSym->Code(atoi(it->strValue.c_str()));
		else if(stricmp(it->strKey.c_str(),"FONT")==0)
			ptrSym->Font(it->strValue.c_str());
		else if(stricmp(it->strKey.c_str(),"ANNOHEIGHT")==0)
			ptrSym->Height(atoi(it->strValue.c_str()));
		else if(stricmp(it->strKey.c_str(),"ANNOWIDTH")==0)
			ptrSym->Width(atoi(it->strValue.c_str()));
		else if(stricmp(it->strKey.c_str(),"ANNOSPACE")==0)
		{
			ptrSym->VerticalExtra(atoi(it->strValue.c_str()));
			ptrSym->HorizonExtra(atoi(it->strValue.c_str()));
		}
		else if(stricmp(it->strKey.c_str(),"ANNOWEIGHT")==0)
		{ 
			//ע���߻��Ĵ�ϸ�̶ȣ��� 0��1000 ��������ʾ���� 400 ���������壬700 ����� ���֡�
			int nWeight = atoi(it->strValue.c_str());
			ptrSym->Bold(nWeight>=700);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOSTYLE")==0)
		{ 
			GeoStar::Kernel::GsTextStyle style = GeoStar::Kernel::eTextStyleNormal;
			int nStyle = atoi(it->strValue.c_str());
			//ע����״��0 �������壬1 ������б��2 ������б��3 �������ʣ�4 ��������
			switch(nStyle)
			{
			case 1:
				style = GeoStar::Kernel::eTextStyleLeftItalic;
				break;
			case 2:
				style = GeoStar::Kernel::eTextStyleRightItalic;
				break;
			case 3:
				style = GeoStar::Kernel::eTextStyleLeftShrug;
				break;
			case 4:
				style = GeoStar::Kernel::eTextStyleRightShrug;
				break;
			default:
				break;
			}
			ptrSym->TextStyle(style);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOUNDERLINE")==0)
		{
			//ע���Ƿ����»��ߣ�0 ��ʾû���»��ߣ�1 ��ʾ���»��ߡ� 
			if(atoi(it->strValue.c_str()))
				ptrSym->UnderLine(true);
			else
				ptrSym->UnderLine(false);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOSTRIKE")==0)
		{
			//ע���Ƿ���ɾ���ߣ�0 ����û��ɾ���ߣ�1 �����е�ɾ���ߣ�2 ������˫ɾ���ߡ� 
			if(atoi(it->strValue.c_str()))
				ptrSym->StrikeOut(true);
			else
				ptrSym->StrikeOut(false);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOSHADOW")==0)
		{
			//ע���Ƿ�����Ӱ��0 ��ʾû����Ӱ��1 ��ʾ����Ӱ�� 
			
			if(atoi(it->strValue.c_str()))
				ptrSym->ShadowColor(GeoStar::Kernel::GsColor::Black);
			else
				ptrSym->ShadowColor(GeoStar::Kernel::GsColor(0));
		}
		else if(stricmp(it->strKey.c_str(),"ANNOHOLE")==0)
		{
			//ע���Ƿ�Ϊ���ģ�0 ��ʾû�п��ģ�1 ��ʾ�п��ġ� 
			if(atoi(it->strValue.c_str()))
				ptrSym->Hollow(true);
			else
				ptrSym->Hollow(false);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOALIGNMENT")==0)
		{
			//ע�Ƕ��뷽ʽ
			//LB �������£�LC �������У�LT �������ϣ�CT �������ϣ�RT �������ϣ�RC �������У�RB �������£�CB �������£� CC �� ������
			//    -------------
			//    |LT |CT |RT |
			//    ------------
			//	  |LC |CC |RC |
			//    -------------
			//    |LB |CB |RB |
			//    -------------
			if(it->strValue.empty())
				it->strValue = "CC";
			if(it->strValue.size() == 1)
				it->strValue.push_back(it->strValue.back());
			switch(it->strValue.front())
			{
				case 'L':
				case 'l':
					ptrSym->HorizonAlign(GeoStar::Kernel::eStringAlignmentNear);
					break;
				case 'C':
				case 'c':
					ptrSym->HorizonAlign(GeoStar::Kernel::eStringAlignmentCenter);
					break;
				case 'R':
				case 'r':
					ptrSym->HorizonAlign(GeoStar::Kernel::eStringAlignmentFar);
					break;
				default:
					ptrSym->HorizonAlign(GeoStar::Kernel::eStringAlignmentNear);
					break;
			}

			switch(it->strValue.back())
			{
				case 'T':
				case 't':
					ptrSym->VerticalAlign(GeoStar::Kernel::eStringAlignmentNear);
					break;
				case 'C':
				case 'c':
					ptrSym->VerticalAlign(GeoStar::Kernel::eStringAlignmentCenter);
					break;
				case 'B':
				case 'b':
					ptrSym->VerticalAlign(GeoStar::Kernel::eStringAlignmentFar);
					break;
				default:
					ptrSym->VerticalAlign(GeoStar::Kernel::eStringAlignmentNear);
					break;
				}
			}
			else if(stricmp(it->strKey.c_str(),"ANNOHORIZONTAL")==0)
			{
				//ע���Ǻ��Ż����ţ�0 ��ʾ���ţ�1 ��ʾ���š� 
				//Ŀǰ��֧��
			}
			else if(stricmp(it->strKey.c_str(),"ANNOTRANSPARENT")==0)
			{
				//ע����͸����0 ��ʾ͸����1 ��ʾ͸��
				//�˹��ܲ���ȷ��ʱ��֧�֡�
			}
	}
		 
	if(ptrSym->Name().empty())
		ptrSym->Name(style.strID.c_str());

	return SymbolToString(ptrSym);
}

//����VCT��style��ѯ��¼�����ſ�ķ���id�����û���򷵻�0
long long VCTContext::SymbolIDFromStyle(const char* style)
{
	std::map<std::string,long long>::iterator it = m_SymbolID.find(style);
	if(it != m_SymbolID.end())
		return it->second;
	return 0;
}
//��һ��VCT��style�洢Ϊ���ţ������ط��ŵĴ洢id
long long VCTContext::StoreStyleToSymbol(VCTStyle& style,VCT_GEOMETRY_TYPE eType)
{
	std::string strSymbolXML;
	if(eType == VCT_POINT)
		strSymbolXML = ToPointSymbol(style);
	else if(eType == VCT_LINE)
		strSymbolXML = ToLineSymbol(style);
	else if(eType == VCT_POLYGON)
		strSymbolXML = ToFillSymbol(style);
	else if(eType == VCT_ANNOTATION)
		strSymbolXML = ToTextSymbol(style);
	if(strSymbolXML.empty())
		return 0;
	if(!m_pSymbols)
		m_pSymbols = m_DB->symbol_table();
	gpkg::symbol sym;
	sym.name = style.strID;
	switch(eType)
	{
	case VCT_POINT:
		sym.type= "Point";
		break;
	case VCT_LINE:
		sym.type= "Line";
		break;
	case VCT_POLYGON:
		sym.type= "Polygon";
		break;
	case VCT_ANNOTATION:
		sym.type= "Text";
		break;
	}
	const char* data = strSymbolXML.data();
	sym.data.insert(sym.data.end(),(const unsigned char*)data,(const unsigned char*)(data + strSymbolXML.length()));
	sym.mime_type = "text/xml";
	sym.sd_standard_uri  = "GeoStar XML Symbol";
	
	if(!m_pSymbols->add(sym))
		return 0;

	m_SymbolID[style.strID] = sym.id;
	return sym.id;
}
//�洢����ͷ��ŵĹ�ϵ
void VCTContext::StoreSymbolRelation(const char* fcsname,long long fid,long long sid,const char* filter)
{
	if(!m_pSymbolRef)
		m_pSymbolRef = m_DB->symbol_reference_table();
	gpkg::symbol_reference data;
	data.reference_scope = "featureClass";
	data.row_id = fid;
	if(filter)
		data.filter = filter;
	if(fcsname)
		data.table_name = fcsname;
	data.symbol_id = sid;
	
	//�洢
	m_pSymbolRef->add(data);

}

ImportVCT::ImportVCT(void)
{
	m_strName = "����VCTʸ�����ݸ�ʽ";
	m_strDescription = "����VCTʸ�����ݸ�ʽ";
	
	m_eType = GIS::eImport;
}


ImportVCT::~ImportVCT(void)
{
}
class VCTFileProgress:public VCTProgress
{
	GIS::Progress * m_pProgress;
	std::string m_strTitle;
	std::string m_strContent;
	long long		m_Length;
public:
	VCTFileProgress(long long nLen,const char* title,const char* content,GIS::Progress * pProgress)
	{
		m_pProgress = pProgress;
		m_strTitle = title;
		m_strContent = content;
		m_Length = nLen;
	}
	virtual void OnProgress(fpos_t pos)
	{
		m_pProgress->OnProgress(pos,m_Length,m_strTitle.c_str(),m_strContent.c_str());
	}
	~VCTFileProgress()
	{
		m_pProgress->OnProgress(m_Length,m_Length,m_strTitle.c_str(),m_strContent.c_str());
	}


};
GeoStar::Kernel::GsSpatialReferencePtr MakeSpatialReference(VCTHead& head)
{
	//ͶӰ���ͺ���������
	std::string strProj = head.strProjection;
	std::string strSpheroid = head.strSpheroid;
	GeoStar::Kernel::GsSpatialReferencePtr sr ;
	if(    stricmp(strProj.c_str(),"��������ϵ")==0 
		|| stricmp(strProj.c_str(),"WGS 1984")==0 )
		sr = new GeoStar::Kernel::GsSpatialReference(GeoStar::Kernel::eWGS84);
	else if(   stricmp(strProj.c_str(),"ͨ�ú���ī����")==0 
			|| stricmp(strProj.c_str(),"Webī����")==0 
			|| stricmp(strProj.c_str()," Web Mercator")==0 )
		sr = new GeoStar::Kernel::GsSpatialReference(GeoStar::Kernel::eWebMercator);
	else
		sr = new GeoStar::Kernel::GsSpatialReference(GeoStar::Kernel::eWGS84);
	return sr;
	/*
	<enumeration value="��������ϵ"/>
	<enumeration value="��˹-������"/>
	<enumeration value="���������θ�Բ׶"/>
	<enumeration value="������������Բ׶"/> 
	<enumeration value="�����صȻ���λ"/>
	<enumeration value="�Ƕ���˹�Ȼ���Բ׶"/>
	<enumeration value="�Ƕ���˹�Ȼ���Բ׶"/>
	<enumeration value="ͨ�ú���ī����"/>
	<enumeration value="ī��������Ƚ���Բ��"/>
	<enumeration value="ī��������ȽǸ�Բ��"/>
	<enumeration value="��˹�еȾ��з�λ"/>
	<enumeration value="���ɵȻ�αԲ׶"/>
	<enumeration value="�Ȼ�������Բ��"/>
	<enumeration value="�Ȼ������Բ��"/>
	<enumeration value="�Ⱦ�������Բ׶"/>
	<enumeration value="�Ⱦ������Բ׶"/>
	<enumeration value="�Ȼ�б���з�λ"/>
	*/
	return 0;
}
//��VCT���ֶ�ת��Ϊgpkg���ֶΡ�
gpkg::field_type ToFieldType(VCT_FIELD_TYPE eType)
{
	switch(eType)
	{
	case VCT_CHAR:// = 0,						// �ַ���
		return gpkg::TEXT;
	case VCT_VARCHAR:// = 1,					// �䳤�ַ��ͣ�ת�������ݿ��Memo ��Blob�ֶ�����		
		return gpkg::TEXT;
	case VCT_SMALLINT:// = 2,					// ������,2���ֽڴ洢	int2
		return gpkg::TINYINT;
	case VCT_INTEGER:// = 3,					// ����,4���ֽڴ洢		int4
		return gpkg::MEDIUMINT;
	case VCT_FLOAT:// = 4,						// ��������,4���ֽڴ洢
		return gpkg::FLOAT;
	case VCT_DOUBLE:// = 5,						// ��������,8���ֽڴ洢
		return gpkg::DOUBLE;
	case VCT_NUMERIC:// = 6,					// ��������,�г��ȺͿ��
		return gpkg::DOUBLE;
	case VCT_BOOL:// = 7,						// ��������	1���ֽڴ洢����Ӧ������ֵӦΪ"1"��"0"
		return gpkg::BOOLEAN;
	case VCT_DATE:// = 8,						// ��������	4���ֽڴ洢����ʾ��ʽӦΪYYYY-MO-DD
		return gpkg::DATE;
	case VCT_TIME:// = 9,						// ʱ������	4���ֽڴ洢����ʾ��ʽӦΪMI:SS.SSS
		return gpkg::DATETIME;
	case VCT_DATETIME:// = 10,					// ����ʱ������	8���ֽڴ洢����ʾ��ʽӦΪYYYY-MO-DD HH:MI:SS.SSS	
		return gpkg::DATETIME;
	case VCT_VARBIN:// = 11,					// �ַ��ͣ������ı�������ʽ������,����ʽ�ݲ����������������ֶ�ֵ��ת����
												// �������ֶ�(���ý������)��ȡ����ļ�ת��,���ֶ���������¼"Varbin",�ֶ�ֵ����¼����ļ�·����
												// ת�������ݿ��Memo ��Blob�ֶ�����
		return gpkg::BLOB;
											
	case VCT_INT1:// = 12,
		return gpkg::TINYINT;
	case VCT_INT8:// = 13,
		return gpkg::INTEGER;
	break;
	}
	return gpkg::TEXT;
}
//д�뵽GPKG�е�
class GPKGWriteFeature:public gpkg::feature
{ 
	VCTPoint m_Point;
	VCTLine  m_Line;
	VCTPolygon m_Polygon;
	VCTSolid m_Solid;
	VCTAnnotation  m_Ann;

	VCTAttributeRow m_Att;
	VCTParser*	m_pParser;
	VCTFeatureCode  m_Code;

	int m_nDim; //����ά�ȡ� 
	WKBWriter m_Writer;
public:
	GPKGWriteFeature(VCTParser*	pParser,VCTFeatureCode& code,int nDim)
	{
		m_nDim = nDim;
		m_Writer.Reset(ByteOrder::OSByteOrderType(),m_nDim);
		m_Code = code; 
		m_pParser = pParser;
	}
	//��ȡ�����ʽ����
	const char* Style()
	{
		switch(m_Code.GeometryType)
		{
		case VCT_POINT:
			return m_Point.ObjHeader.strStyle.c_str();
		case VCT_LINE:
			return m_Line.ObjHeader.strStyle.c_str();
		case VCT_POLYGON:
			return m_Polygon.ObjHeader.strStyle.c_str();
		case VCT_SOLID:
			return m_Solid.ObjHeader.strStyle.c_str();
		case VCT_ANNOTATION:
			return m_Ann.ObjHeader.strStyle.c_str();
		}
		return NULL;
	}
	//׼����ȡһ�����
	void Prepare(fpos_t pos,fpos_t attpos)
	{
		m_FID = 0; 
		switch(m_Code.GeometryType)
		{
		case VCT_POINT:
			m_pParser->ParseObject(pos,m_Point);
			break;
		case VCT_LINE:
			m_pParser->ParseObject(pos,m_Line);
			break;
		case VCT_POLYGON:
			m_pParser->ParseObject(pos,m_Polygon);
			break;
		case VCT_SOLID:
			m_pParser->ParseObject(pos,m_Solid);
			break;
		case VCT_ANNOTATION: 
			m_pParser->ParseObject(pos,m_Ann);
			break;
		break;
		} 
		
		m_Writer.Reset(ByteOrder::OSByteOrderType(),m_nDim);
		if(attpos >0)
			m_pParser->ParseObject(attpos,m_Att); 

		//����ע�ǵ�����Ҫ���ı���Ϊ������ֶμ��뵽��һ�������ֶ���
		if(m_Code.GeometryType == VCT_ANNOTATION)
			m_Att.vecstrFieldValues.insert(m_Att.vecstrFieldValues.begin(),m_Ann.strText);
		

	}
	long long m_FID;
	
public:
	/// \brief ���õ����fid
	virtual void fid(long long id)
	{
		m_FID =  id;
	}
	/// \brief ��ȡ�����fid
	virtual long long fid()
	{
		return m_FID;
	}
		
	/// \brief geometry�����ݳ���
	virtual int geometry_length()
	{
		return m_Writer.Buffer()->BufferSize();
	}
	void ComputerExtent(std::vector<VCTPoint3D>& vec,double& xmin,double& ymin,double& xmax,double &ymax)
	{
		std::vector<VCTPoint3D>::iterator it = vec.begin();
		for(;it != vec.end();it++)
		{
			xmin = min(xmin,it->x);
			ymin = min(ymin,it->y);
			xmax = max(xmax,it->x);
			ymax = max(ymax,it->y);
		}
	}
	/// \brief ���㼸�ζ������Ӿ��Ρ�
	void ComputerExtent(gpkg::geo_package_binary *head)
	{
		double xmin = DBL_MAX;
		double ymin = DBL_MAX;
		double xmax = -DBL_MAX;
		double ymax = -DBL_MAX;

		switch(m_Code.GeometryType)
		{
		case VCT_POINT: //��ʱû�п����������
			ComputerExtent(m_Point.vecPoint,xmin,ymin,xmax,ymax);
			break;
		case VCT_LINE: 
			{
				std::vector<VCTLineElement>::iterator it = m_Line.vecLineData.begin();
				for(;it != m_Line.vecLineData.end();it++)
				{
					ComputerExtent(it->vecArcPoint,xmin,ymin,xmax,ymax);
				}
			}
			
			break;
		case VCT_POLYGON: 
			{
				std::vector<VCTPolygonElement>::iterator it = m_Polygon.vecPolygonElement.begin();
				for(;it != m_Polygon.vecPolygonElement.end();it++)
				{
					ComputerExtent(it->vecPoints,xmin,ymin,xmax,ymax);
				}
			}
			break;
		case VCT_SOLID: 
			break;
		case VCT_ANNOTATION: 
			std::vector<VCTAnnoPoint>::iterator it = m_Ann.vecAnnoPoint.begin();
			for(;it != m_Ann.vecAnnoPoint.end();it++)
			{
				xmin = min(xmin,it->vctPoint3D.x);
				ymin = min(ymin,it->vctPoint3D.y);
				xmax = max(xmax,it->vctPoint3D.x);
				ymax = max(ymax,it->vctPoint3D.x);
			}
			
			break;
		break;
		}
		head->envelope[0] = xmin;
		head->envelope[1] = xmax;

		head->envelope[2] = ymin;
		head->envelope[3] = ymax;

	}
	 

	///���ڽ�Geometry�����WKB
	void MakeGeometry()
	{
		switch(m_Code.GeometryType)
		{
		case VCT_POINT:  
			m_Writer.Write(m_Point);
			break;
		case VCT_LINE: 
			m_Writer.Write(m_Line);
			break;
		case VCT_POLYGON: 
			m_Writer.Write(m_Polygon);
			break;
		case VCT_SOLID: 
			break;
		case VCT_ANNOTATION: 
			m_Writer.Write(m_Ann);
			break;
		}
	}
	void UnionExtent(double& xmin,double& ymin,double &xmax,double& ymax)
	{
		
		gpkg::geo_package_binary *head = m_Writer.Buffer()->PtrT<gpkg::geo_package_binary>();
		xmin = min(head->envelope[0],xmin);
		xmax = max(head->envelope[1],xmax);

		ymin = min(head->envelope[2],ymin);
		ymax = max(head->envelope[3],ymax);

	}

	/// \brief ��ȡgeometry������ͷָ��
	virtual gpkg::geo_package_binary* geometry()
	{
		if(m_Writer.Buffer()->BufferSize() ==0)
		{
			//ȱʡʹ��EnvelopeXY��ģʽ
			m_Writer.Buffer()->Allocate( 8 + 4 * 8);
			m_Writer.Buffer()->SetBufferValue(0);
			gpkg::geo_package_binary *head = m_Writer.Buffer()->PtrT<gpkg::geo_package_binary>();
			head->magic[0] = 'G';
			head->magic[1] = 'P';
			head->is_little_endian(true);
			head->is_standard(true);
			head->envelope_type(gpkg::EnvelopeXY);
			ComputerExtent(head);
			MakeGeometry();
		}
		return m_Writer.Buffer()->PtrT<gpkg::geo_package_binary>();
	}
	/// \brief ����geometry
	virtual void geometry(gpkg::geo_package_binary* geo,int nlen)
	{
	}

	/// \brief ��ȡĳ�еĵ��������ֶ�ֵ
	virtual long long int_value(int col)
	{
		col-=2;
		if(col>= m_Att.vecstrFieldValues.size())
			return 0;
		return _atoi64(m_Att.vecstrFieldValues[col].c_str());
	}
	/// \brief ��ȡĳ�еĵ��︡���ֶ�ֵ
	virtual double float_value(int col)
	{
		col-=2;
		if(col>= m_Att.vecstrFieldValues.size())
			return 0;
		return atof(m_Att.vecstrFieldValues[col].c_str());
	}
	/// \brief ��ȡĳ�еĵ����ַ����ֶ�ֵ
	virtual const char* string_value(int col)
	{
		col-=2;
		if(col>= m_Att.vecstrFieldValues.size())
			return NULL;
		if(m_Att.vecstrFieldValues[col].empty())
			return NULL;

		//gpkgʹ��utf8�洢�ַ�����������Ҫת��Ϊutf8��洢
		m_Att.vecstrFieldValues[col].swap(ToUtf8(m_Att.vecstrFieldValues[col].c_str()));
		return m_Att.vecstrFieldValues[col].c_str();
	} 

	/// \brief ��ȡĳ�еĵ��������ֶ�ֵ
	virtual void value(int col,long long val)
	{
	}
	/// \brief ��ȡĳ�еĵ��︡���ֶ�ֵ
	virtual void value(int col,double val)
	{
	}
	/// \brief ��ȡĳ�еĵ����ַ����ֶ�ֵ
	virtual void value(int col,const char * val)
	{
	}
};

/// \brief �����ļ��е�һ��������
bool ImportVCT::ImportFeatureCode(VCTParser &parser,
									VCTFeatureCode& code,
									gpkg::database_ptr& db,
									GIS::Progress * pProgress)
{
	std::stringstream ss;
	ss<<"׼����������ࣺ"<<code.strUserID;
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	VCTTableStructure* pStruct = parser.TableStructure(code.strUserID.c_str());
	if(NULL == pStruct)
	{
		pProgress->OnLog("��Ч��VCT�ļ�",GIS::LogLevel::eError);
		return false;
	}
	double xmin = DBL_MAX,ymin = DBL_MAX,xmax = -DBL_MAX,ymax=-DBL_MAX;

	gpkg::content c;
	//���ȴ����������
	gpkg::feature_table_ptr ptrFeaClass = db->open_feature_table(ToUtf8(code.strUserID.c_str()).c_str());
	if(ptrFeaClass)
	{
		ptrFeaClass->delete_spatial_index(db->extensions_table());
		c = ptrFeaClass->content_infomation();
	}
	else //�������򴴽���������ࡣ
	{
		GeoStar::Kernel::GsSpatialReferencePtr ptrSR = MakeSpatialReference(parser.Head());
		//�ռ�ο�
		int nEPSG = ptrSR->EPSG();
		gpkg::spatial_ref ref = db->spatial_ref_table()->query(nEPSG);
		//������ܻ�ô��ڵĿռ�ο��򴴽�֮��
		if(ref.srs_id != nEPSG)
		{
			ref.definition = ptrSR->ExportToWKT();
			ref.description = ptrSR->ExportToWKT();
			ref.organization = "EPSG";
			ref.organization_coordsys_id = nEPSG;
			ref.srs_id = nEPSG;
			ref.srs_name = ToUtf8(ptrSR->Name().c_str());
		
			//���һ���ռ�ο�
			db->spatial_ref_table()->create(ref);
		}
		
		gpkg::geometry_column col;
		//��������Ϣ
		c.data_type = "features";
		c.identifier = ToUtf8(code.strUserID.c_str());
		c.table_name = ToUtf8(code.strUserID.c_str());//���Userid���ڷǷ����ַ�������Ҫ�滻�����Ŀ�����Ҫ����utf8.
		c.last_change = time(NULL);
		c.min_x = DBL_MAX;
		c.min_y = DBL_MAX;
		c.max_x = -DBL_MAX;
		c.max_y = -DBL_MAX;
		c.srs_id = ref.srs_id;

		//�������ֶΡ�
		std::vector<gpkg::field> vecField; 
		vecField.push_back(gpkg::field("fid",gpkg::INTEGER));
		if(code.GeometryType == VCT_POINT)
		{
			vecField.push_back(gpkg::field("geometry",gpkg::POINT));
			col.geometry_type_name = "POINT";
		}
		else if(code.GeometryType == VCT_LINE)
		{
			vecField.push_back(gpkg::field("geometry",gpkg::LINESTRING));
			col.geometry_type_name = "LINESTRING";
		}
		else if(code.GeometryType == VCT_POLYGON)
		{
			vecField.push_back(gpkg::field("geometry",gpkg::MULTIPOLYGON));
			col.geometry_type_name = "MULTIPOLYGON";
		}
		else if(code.GeometryType == VCT_ANNOTATION) //ע�ǵļ������͵�����������
		{
			col.geometry_type_name = "POINT";
			vecField.push_back(gpkg::field("geometry",gpkg::POINT));
			//Ϊע�ǵ���������ע���ı��ֶΡ�
			vecField.push_back(gpkg::field("annotaionValue",gpkg::TEXT));
		}

		VCTFields::iterator it = pStruct->vecFields.begin();
		for(;it != pStruct->vecFields.end();it++)
		{
			vecField.push_back(gpkg::field(it->strFieldName.c_str(),ToFieldType(it->FieldType)));
		}
		 
		col.srs_id = ref.srs_id;
		col.column_name = "geometry"; 
		col.m = false;
		col.z = false;
		col.table_name = c.table_name.c_str();
	
		//��Ӽ��κ������ֶΡ�
		db->geometry_columns_table()->append(col);
		db->contents_table()->append(c);

		ptrFeaClass = db->create_feature_table(c,vecField);

		//�����ע�ǵ�����Ļ�����Ҫ����չ������Ӽ�¼���Ա�ʶ�����ע�ǵ�����
		if(code.GeometryType == VCT_ANNOTATION)
		{
			gpkg::extension ext;
			ext.column_name = col.column_name;
			ext.table_name = c.table_name;
			ext.extension_name = "gpkgc_annotation";
			ext.scope = "read-write";
			ext.definition = "GeoStar";
			db->extensions_table()->add(ext);
		}
	}

	if(!ptrFeaClass)
	{
		pProgress->OnLog("������򿪵�����ʧ��",GIS::LogLevel::eError);
		return false;
	}
	GPKGWriteFeature feature(&parser,code,parser.Head().nDim);
	IDCache& cache = parser.GeometryIndex(code);
	IDCache& cacheAtt = parser.AttributeIndex(code);
	IDCache::iterator itAtt;
	IDCache::iterator it = cache.begin();

	std::string strTitle = "�������";
	std::string strContent = code.strUserID;
	long long nPos = 0;
	long long nMax = cache.size();
	std::auto_ptr<gpkg::transaction> ptrTans(new  gpkg::transaction(db));
	clock_t t = clock();
	 
	for(;it != cache.end();it++)
	{
		pProgress->OnProgress(nPos,nMax,strTitle.c_str(),strContent.c_str());
		nPos++;

		itAtt = cacheAtt.find(it->first);
		fpos_t nAttPos = 0;
		if(itAtt != cacheAtt.end())
			nAttPos = itAtt->second;
		feature.Prepare(it->second,nAttPos);
		//�������
		ptrFeaClass->save(&feature);
		//ʽ������
		const char* style = feature.Style();
		//�������ʽ���Ļ���
		if(style)
		{
			//����Style��ȡ��Ӧ�ķ���id
			long long nSymID = m_VCTContext.SymbolIDFromStyle(style);
			//�������idС�ڵ���0���ʾ��û�д洢������š�
			if(nSymID <= 0)
			{
				//��ѯstyle����style�洢Ϊ���š�
				KeyCache::iterator itStyle = parser.StyleIndex().find(style);
				if(itStyle != parser.StyleIndex().end()) //���style�ܹ��鵽�Ļ�
				{
					VCTStyle vStyle;
					if(parser.ParseObject(itStyle->second,vStyle))//����ɹ�������style��洢Ϊ����
						nSymID = m_VCTContext.StoreStyleToSymbol(vStyle,code.GeometryType);
				}
			}
			//�������id��Ч��洢��ϵ
			if(nSymID >0)
				m_VCTContext.StoreSymbolRelation(ptrFeaClass->name(),feature.fid(),nSymID);
		}
		//�ϲ��˵���ľ��η�Χ
		feature.UnionExtent(c.min_x,c.min_y,c.max_x,c.max_y);
		if(clock() - t >100000) //100���ύһ�Ρ�
		{
			ptrTans->commit();
			ptrTans.reset(new  gpkg::transaction(db));
		}
	}
	//���µ�����ķ�Χ��
	db->contents_table()->update_extent(c);
	ptrTans->commit();

	ss.str("");
	ss<<"��ʼ�����ռ�����"<<code.strUserID;
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	ptrFeaClass->create_spatial_index(db->extensions_table());
	
	ss.str("");
	ss<<"�����ռ��������";
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	//�������Ԫ���ݵĻ�
	std::string strMetaFile = m_VCTContext.MetadataFile();
	if(!strMetaFile.empty())
	{
		ss.str("");
		ss<<"����Ԫ���ݡ�";
		pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
		long long meta = m_VCTContext.MetaDataID();
		if(meta <=0)
			meta = m_VCTContext.StoreMetadata();
		if(meta >0)
			m_VCTContext.StoreMetadataReference(ptrFeaClass->name());
	}

	return true;
}

/// \brief ����һ��VCT�ļ������ݡ�
bool ImportVCT::ImportVCTFile(GeoStar::Utility::GsFile& file,gpkg::database_ptr& db,GIS::Progress * pProgress)
{
	std::stringstream ss;
	
	ss<<"׼�������ļ���"<<file.FullPath();
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	//��VCT�ļ���·�������Ż��档
	m_VCTContext.BindVCT(file.Path());

	//��������VCT�ļ���
	VCTParser parser(file.Path());
	{
		VCTFileProgress progress(file.Size(),"����VCT",file.Name().c_str(),pProgress);
		parser.Progress(&progress);
		parser.Parse();
		parser.Progress(NULL);
	}

	//˳���ȡ���е�FeatureCode
	std::vector<VCTFeatureCode>::iterator it =  parser.FeatureCodes().begin();
	for(;it != parser.FeatureCodes().end();it++)
	{
		//һ��FeatureCode����Ϊһ�������ࡣ
		ImportFeatureCode(parser,*it,db,pProgress);
	}

	return true;
}


/// \brief ִ�в��
const char* ImportVCT::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	pProgress->OnLog("׼�����ݵ���",GIS::LogLevel::eInfo);
	pProgress->OnLog("�����������",GIS::LogLevel::eInfo);

	//�������
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		pProgress->OnLog("���������������",GIS::LogLevel::eError);
		return NULL;
	}
	//�����Ŀ¼
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("û���������·��",GIS::LogLevel::eError);
		return NULL;
	}

	//����
	std::string strInputFile = kvp.Value("Path");
	if(strInputFile.empty())
	{
		pProgress->OnLog("û����������·��",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "ת��";
	strLog+=strInputFile;
	strLog+="����׼ʸ������";
	strLog+=strOuputFolder;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

	bool bNew = GeoStar::Utility::GsFile(strOuputFolder.c_str()).Exists()?false:true;
	std::string strUtf8Path =	GeoStar::Utility::GsCW2A(GeoStar::Utility::GsCA2W(strOuputFolder.c_str()).m_WStr,
								GeoStar::Utility::eCP_UTF8).m_Str;
	//���������ݿ⡣
	gpkg::database_ptr db(new gpkg::database(strUtf8Path.c_str(),bNew));
	pProgress->OnLog("��������ݼ�",GIS::LogLevel::eInfo);

	GeoStar::Utility::GsDir dir(strInputFile.c_str());
	GsVector<GeoStar::Utility::GsFile> vec =  dir.Files("*.vct");
	if(vec.empty())
	{
		pProgress->OnLog("û�п���ת�������ݡ�",GIS::LogLevel::eError);
		return NULL;
	}


	std::stringstream ss;
	ss<<"׼��ת��"<<vec.size()<<"��VCT�ļ�";
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	//׼���÷��Ż��棬���������Ҫ�Ļ�
	m_VCTContext.Attach(db);

	GsVector<GeoStar::Utility::GsFile>::iterator it = vec.begin();
	for(;it != vec.end();it++)
	{
		ImportVCTFile(*it,db,pProgress);
	}
	
	return NULL;
}

