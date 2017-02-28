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
//生成vct文件的元数据文件文件名。
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
//返回VCT文件的元数据，如果存在的话
std::string VCTContext::MetadataFile()
{
	
	//如果有meta文件
	std::string strMetaFile = MetaDataFile(m_VCTFile.c_str(),"meta");
	if(!strMetaFile.empty()) return strMetaFile;

	//如果有xml文件。
	strMetaFile = MetaDataFile(m_VCTFile.c_str(),"xml");
	if(!strMetaFile.empty()) return strMetaFile;

	//将来有其他扩展名的元数据也如此处理。
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
//存储元数据的引用
void VCTContext::StoreMetadataReference(const char* table_name)
{
	gpkg::metadata_reference_table* table = m_DB->metadata_reference_table();
	gpkg::metadata_reference ref;
	ref.reference_scope = "table";
	ref.table_name = table_name;
	ref.row_id_value = 0;
	ref.md_file_id = m_MetadataID;
	
	//父id为0
	ref.md_parent_id  = 0;
	
	//添加一条记录。
	table->add(ref);
}


//绑定VCT文件
void VCTContext::BindVCT(const char* vctFile)
{
	m_MetadataID = 0;
	//清空符号到符号id的缓存，因为对于每个VCT而言，其style名称在VCT文件内才是唯一的。
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
	//如果符号库的路径不是绝对路径
	if(!GeoStar::Utility::GsFileSystem::IsPathRooted(libName))
	{
		//vct文件所在的目录
		std::string strFolder = GeoStar::Utility::GsFile(m_VCTFile.c_str()).Parent().Path();
		//用vct所在的目录和符号库组成绝对路径。
		strSymLibFile = GeoStar::Utility::GsFileSystem::Combine(strFolder.c_str(),libName);
	}

	//如果符号库文件是不存在的则返回null
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

	//如果存在符号库，且符号id有效则从符号库LoadSymbol
	if(!strSymLib.empty() && nSymID > 0)
	{
		//获取外部符号库
		std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib(strSymLib.c_str());
		if(ptrLib)
		{
			//如果成功打开外部符号库则根据code获得符号。
			GeoStar::Kernel::GsPointSymbolPtr ptrSymFromLib = ptrLib->SymbolByCode(nSymID);
			if(ptrSymFromLib) //如果成功获取外部符号，则将vct中的相关信息同步到外部符号中并返回外部符号
			{
				ptrSymFromLib->Size(ptrSym->Size());
				ptrSymFromLib->Color(ptrSym->Color());
				ptrSymFromLib->Name(ptrSym->Name().c_str());
				return SymbolToString(ptrSymFromLib);
			}
		}
	}

	//到这里证明无法打开外部符号，或者没有引用外部符号，则直接使用简单符号替代。
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

	//如果存在符号库，且符号id有效则从符号库LoadSymbol
	if(!strSymLib.empty() && nSymID > 0)
	{
		//获取外部符号库
		std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib(strSymLib.c_str());
		if(ptrLib)
		{
			//如果成功打开外部符号库则根据code获得符号。
			GeoStar::Kernel::GsLineSymbolPtr ptrSymFromLib = ptrLib->SymbolByCode(nSymID);
			if(ptrSymFromLib) //如果成功获取外部符号，则将vct中的相关信息同步到外部符号中并返回外部符号
			{
				ptrSymFromLib->Width(ptrSym->Width());
				ptrSymFromLib->Color(ptrSym->Color());
				ptrSymFromLib->Name(ptrSym->Name().c_str());
				return SymbolToString(ptrSymFromLib);
			}
		}
	}

	//到这里证明无法打开外部符号，或者没有引用外部符号，则直接使用简单符号替代。
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

	//如果存在符号库，且符号id有效则从符号库LoadSymbol
	if(!strSymLib.empty() && nSymID > 0)
	{
		//获取外部符号库
		std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib(strSymLib.c_str());
		if(ptrLib)
		{
			//如果成功打开外部符号库则根据code获得符号。
			GeoStar::Kernel::GsFillSymbolPtr ptrSymFromLib = ptrLib->SymbolByCode(nSymID);
			if(ptrSymFromLib) //如果成功获取外部符号，则将vct中的相关信息同步到外部符号中并返回外部符号
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

	//到这里证明无法打开外部符号，或者没有引用外部符号，则直接使用简单符号替代。
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
			//注记线划的粗细程度，以 0～1000 的整数表示，如 400 代表正常体，700 代表粗 体字。
			int nWeight = atoi(it->strValue.c_str());
			ptrSym->Bold(nWeight>=700);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOSTYLE")==0)
		{ 
			GeoStar::Kernel::GsTextStyle style = GeoStar::Kernel::eTextStyleNormal;
			int nStyle = atoi(it->strValue.c_str());
			//注记形状，0 代表正体，1 代表左斜，2 代表右斜，3 代表左耸，4 代表右耸
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
			//注记是否有下划线，0 表示没有下划线，1 表示有下划线。 
			if(atoi(it->strValue.c_str()))
				ptrSym->UnderLine(true);
			else
				ptrSym->UnderLine(false);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOSTRIKE")==0)
		{
			//注记是否有删除线，0 代表没有删除线，1 代表有单删除线，2 代表有双删除线。 
			if(atoi(it->strValue.c_str()))
				ptrSym->StrikeOut(true);
			else
				ptrSym->StrikeOut(false);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOSHADOW")==0)
		{
			//注记是否有阴影，0 表示没有阴影，1 表示有阴影。 
			
			if(atoi(it->strValue.c_str()))
				ptrSym->ShadowColor(GeoStar::Kernel::GsColor::Black);
			else
				ptrSym->ShadowColor(GeoStar::Kernel::GsColor(0));
		}
		else if(stricmp(it->strKey.c_str(),"ANNOHOLE")==0)
		{
			//注记是否为空心，0 表示没有空心，1 表示有空心。 
			if(atoi(it->strValue.c_str()))
				ptrSym->Hollow(true);
			else
				ptrSym->Hollow(false);
		}
		else if(stricmp(it->strKey.c_str(),"ANNOALIGNMENT")==0)
		{
			//注记对齐方式
			//LB 代表左下，LC 代表左中，LT 代表左上，CT 代表中上，RT 代表右上，RC 代表右中，RB 代表右下，CB 代表中下， CC 代 表中中
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
				//注记是横排或竖排，0 表示横排，1 表示竖排。 
				//目前不支持
			}
			else if(stricmp(it->strKey.c_str(),"ANNOTRANSPARENT")==0)
			{
				//注记是透明，0 表示透明，1 表示透明
				//此功能不明确暂时不支持。
			}
	}
		 
	if(ptrSym->Name().empty())
		ptrSym->Name(style.strID.c_str());

	return SymbolToString(ptrSym);
}

//根据VCT的style查询记录到符号库的符号id。如果没有则返回0
long long VCTContext::SymbolIDFromStyle(const char* style)
{
	std::map<std::string,long long>::iterator it = m_SymbolID.find(style);
	if(it != m_SymbolID.end())
		return it->second;
	return 0;
}
//将一个VCT的style存储为符号，并返回符号的存储id
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
//存储地物和符号的关系
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
	
	//存储
	m_pSymbolRef->add(data);

}

ImportVCT::ImportVCT(void)
{
	m_strName = "导入VCT矢量数据格式";
	m_strDescription = "导入VCT矢量数据格式";
	
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
	//投影类型和椭球类型
	std::string strProj = head.strProjection;
	std::string strSpheroid = head.strSpheroid;
	GeoStar::Kernel::GsSpatialReferencePtr sr ;
	if(    stricmp(strProj.c_str(),"地理坐标系")==0 
		|| stricmp(strProj.c_str(),"WGS 1984")==0 )
		sr = new GeoStar::Kernel::GsSpatialReference(GeoStar::Kernel::eWGS84);
	else if(   stricmp(strProj.c_str(),"通用横轴墨卡托")==0 
			|| stricmp(strProj.c_str(),"Web墨卡托")==0 
			|| stricmp(strProj.c_str()," Web Mercator")==0 )
		sr = new GeoStar::Kernel::GsSpatialReference(GeoStar::Kernel::eWebMercator);
	else
		sr = new GeoStar::Kernel::GsSpatialReference(GeoStar::Kernel::eWGS84);
	return sr;
	/*
	<enumeration value="地理坐标系"/>
	<enumeration value="高斯-克吕格"/>
	<enumeration value="兰勃特正形割圆锥"/>
	<enumeration value="兰勃特正形切圆锥"/> 
	<enumeration value="兰勃特等积方位"/>
	<enumeration value="亚尔勃斯等积割圆锥"/>
	<enumeration value="亚尔勃斯等积切圆锥"/>
	<enumeration value="通用横轴墨卡托"/>
	<enumeration value="墨卡托正轴等角切圆柱"/>
	<enumeration value="墨卡托正轴等角割圆柱"/>
	<enumeration value="波斯托等距切方位"/>
	<enumeration value="彭纳等积伪圆锥"/>
	<enumeration value="等积正轴切圆柱"/>
	<enumeration value="等积正轴割圆柱"/>
	<enumeration value="等距正轴切圆锥"/>
	<enumeration value="等距正轴割圆锥"/>
	<enumeration value="等积斜轴切方位"/>
	*/
	return 0;
}
//从VCT的字段转换为gpkg的字段。
gpkg::field_type ToFieldType(VCT_FIELD_TYPE eType)
{
	switch(eType)
	{
	case VCT_CHAR:// = 0,						// 字符型
		return gpkg::TEXT;
	case VCT_VARCHAR:// = 1,					// 变长字符型，转换成数据库的Memo 或Blob字段类型		
		return gpkg::TEXT;
	case VCT_SMALLINT:// = 2,					// 短整型,2个字节存储	int2
		return gpkg::TINYINT;
	case VCT_INTEGER:// = 3,					// 整型,4个字节存储		int4
		return gpkg::MEDIUMINT;
	case VCT_FLOAT:// = 4,						// 浮点数型,4个字节存储
		return gpkg::FLOAT;
	case VCT_DOUBLE:// = 5,						// 浮点数型,8个字节存储
		return gpkg::DOUBLE;
	case VCT_NUMERIC:// = 6,					// 浮点数型,有长度和宽度
		return gpkg::DOUBLE;
	case VCT_BOOL:// = 7,						// 布尔类型	1个字节存储，相应的属性值应为"1"或"0"
		return gpkg::BOOLEAN;
	case VCT_DATE:// = 8,						// 日期类型	4个字节存储，显示格式应为YYYY-MO-DD
		return gpkg::DATE;
	case VCT_TIME:// = 9,						// 时间类型	4个字节存储，显示格式应为MI:SS.SSS
		return gpkg::DATETIME;
	case VCT_DATETIME:// = 10,					// 日期时间类型	8个字节存储，显示格式应为YYYY-MO-DD HH:MI:SS.SSS	
		return gpkg::DATETIME;
	case VCT_VARBIN:// = 11,					// 字符型，由于文本交换格式的限制,本格式暂不包含二进制类型字段值的转换。
												// 二进制字段(如多媒体数据)采取外挂文件转换,在字段描述处记录"Varbin",字段值处记录外挂文件路径。
												// 转换成数据库的Memo 或Blob字段类型
		return gpkg::BLOB;
											
	case VCT_INT1:// = 12,
		return gpkg::TINYINT;
	case VCT_INT8:// = 13,
		return gpkg::INTEGER;
	break;
	}
	return gpkg::TEXT;
}
//写入到GPKG中的
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

	int m_nDim; //坐标维度。 
	WKBWriter m_Writer;
public:
	GPKGWriteFeature(VCTParser*	pParser,VCTFeatureCode& code,int nDim)
	{
		m_nDim = nDim;
		m_Writer.Reset(ByteOrder::OSByteOrderType(),m_nDim);
		m_Code = code; 
		m_pParser = pParser;
	}
	//获取地物的式样。
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
	//准备读取一个地物。
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

		//对于注记地物需要将文本作为特殊的字段加入到第一个属性字段中
		if(m_Code.GeometryType == VCT_ANNOTATION)
			m_Att.vecstrFieldValues.insert(m_Att.vecstrFieldValues.begin(),m_Ann.strText);
		

	}
	long long m_FID;
	
public:
	/// \brief 设置地物的fid
	virtual void fid(long long id)
	{
		m_FID =  id;
	}
	/// \brief 获取地物的fid
	virtual long long fid()
	{
		return m_FID;
	}
		
	/// \brief geometry的数据长度
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
	/// \brief 计算几何对象的外接矩形。
	void ComputerExtent(gpkg::geo_package_binary *head)
	{
		double xmin = DBL_MAX;
		double ymin = DBL_MAX;
		double xmax = -DBL_MAX;
		double ymax = -DBL_MAX;

		switch(m_Code.GeometryType)
		{
		case VCT_POINT: //暂时没有考虑相对坐标
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
	 

	///用于将Geometry构造成WKB
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

	/// \brief 获取geometry的数据头指针
	virtual gpkg::geo_package_binary* geometry()
	{
		if(m_Writer.Buffer()->BufferSize() ==0)
		{
			//缺省使用EnvelopeXY的模式
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
	/// \brief 设置geometry
	virtual void geometry(gpkg::geo_package_binary* geo,int nlen)
	{
	}

	/// \brief 获取某列的地物整数字段值
	virtual long long int_value(int col)
	{
		col-=2;
		if(col>= m_Att.vecstrFieldValues.size())
			return 0;
		return _atoi64(m_Att.vecstrFieldValues[col].c_str());
	}
	/// \brief 获取某列的地物浮点字段值
	virtual double float_value(int col)
	{
		col-=2;
		if(col>= m_Att.vecstrFieldValues.size())
			return 0;
		return atof(m_Att.vecstrFieldValues[col].c_str());
	}
	/// \brief 获取某列的地物字符串字段值
	virtual const char* string_value(int col)
	{
		col-=2;
		if(col>= m_Att.vecstrFieldValues.size())
			return NULL;
		if(m_Att.vecstrFieldValues[col].empty())
			return NULL;

		//gpkg使用utf8存储字符串，这里需要转换为utf8后存储
		m_Att.vecstrFieldValues[col].swap(ToUtf8(m_Att.vecstrFieldValues[col].c_str()));
		return m_Att.vecstrFieldValues[col].c_str();
	} 

	/// \brief 获取某列的地物整数字段值
	virtual void value(int col,long long val)
	{
	}
	/// \brief 获取某列的地物浮点字段值
	virtual void value(int col,double val)
	{
	}
	/// \brief 获取某列的地物字符串字段值
	virtual void value(int col,const char * val)
	{
	}
};

/// \brief 导入文件中的一个地物类
bool ImportVCT::ImportFeatureCode(VCTParser &parser,
									VCTFeatureCode& code,
									gpkg::database_ptr& db,
									GIS::Progress * pProgress)
{
	std::stringstream ss;
	ss<<"准备导入地物类："<<code.strUserID;
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	VCTTableStructure* pStruct = parser.TableStructure(code.strUserID.c_str());
	if(NULL == pStruct)
	{
		pProgress->OnLog("无效的VCT文件",GIS::LogLevel::eError);
		return false;
	}
	double xmin = DBL_MAX,ymin = DBL_MAX,xmax = -DBL_MAX,ymax=-DBL_MAX;

	gpkg::content c;
	//首先打开这个地物类
	gpkg::feature_table_ptr ptrFeaClass = db->open_feature_table(ToUtf8(code.strUserID.c_str()).c_str());
	if(ptrFeaClass)
	{
		ptrFeaClass->delete_spatial_index(db->extensions_table());
		c = ptrFeaClass->content_infomation();
	}
	else //不存在则创建这个地物类。
	{
		GeoStar::Kernel::GsSpatialReferencePtr ptrSR = MakeSpatialReference(parser.Head());
		//空间参考
		int nEPSG = ptrSR->EPSG();
		gpkg::spatial_ref ref = db->spatial_ref_table()->query(nEPSG);
		//如果不能获得存在的空间参考则创建之。
		if(ref.srs_id != nEPSG)
		{
			ref.definition = ptrSR->ExportToWKT();
			ref.description = ptrSR->ExportToWKT();
			ref.organization = "EPSG";
			ref.organization_coordsys_id = nEPSG;
			ref.srs_id = nEPSG;
			ref.srs_name = ToUtf8(ptrSR->Name().c_str());
		
			//添加一个空间参考
			db->spatial_ref_table()->create(ref);
		}
		
		gpkg::geometry_column col;
		//基本表信息
		c.data_type = "features";
		c.identifier = ToUtf8(code.strUserID.c_str());
		c.table_name = ToUtf8(code.strUserID.c_str());//如果Userid存在非法的字符则将来需要替换，中文可能需要采用utf8.
		c.last_change = time(NULL);
		c.min_x = DBL_MAX;
		c.min_y = DBL_MAX;
		c.max_x = -DBL_MAX;
		c.max_y = -DBL_MAX;
		c.srs_id = ref.srs_id;

		//创建的字段。
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
		else if(code.GeometryType == VCT_ANNOTATION) //注记的几何类型当做点来处理。
		{
			col.geometry_type_name = "POINT";
			vecField.push_back(gpkg::field("geometry",gpkg::POINT));
			//为注记地物类增加注记文本字段。
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
	
		//添加几何和属性字段。
		db->geometry_columns_table()->append(col);
		db->contents_table()->append(c);

		ptrFeaClass = db->create_feature_table(c,vecField);

		//如果是注记地物类的话则需要在扩展表中添加记录，以标识这个是注记地物类
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
		pProgress->OnLog("创建或打开地物类失败",GIS::LogLevel::eError);
		return false;
	}
	GPKGWriteFeature feature(&parser,code,parser.Head().nDim);
	IDCache& cache = parser.GeometryIndex(code);
	IDCache& cacheAtt = parser.AttributeIndex(code);
	IDCache::iterator itAtt;
	IDCache::iterator it = cache.begin();

	std::string strTitle = "导入地物";
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
		//保存地物
		ptrFeaClass->save(&feature);
		//式样名称
		const char* style = feature.Style();
		//如果存在式样的话则
		if(style)
		{
			//根据Style获取对应的符号id
			long long nSymID = m_VCTContext.SymbolIDFromStyle(style);
			//如果符号id小于等于0则标示还没有存储这个符号。
			if(nSymID <= 0)
			{
				//查询style并将style存储为符号。
				KeyCache::iterator itStyle = parser.StyleIndex().find(style);
				if(itStyle != parser.StyleIndex().end()) //如果style能够查到的话
				{
					VCTStyle vStyle;
					if(parser.ParseObject(itStyle->second,vStyle))//如果成功解析到style则存储为符号
						nSymID = m_VCTContext.StoreStyleToSymbol(vStyle,code.GeometryType);
				}
			}
			//如果符号id有效则存储关系
			if(nSymID >0)
				m_VCTContext.StoreSymbolRelation(ptrFeaClass->name(),feature.fid(),nSymID);
		}
		//合并此地物的矩形范围
		feature.UnionExtent(c.min_x,c.min_y,c.max_x,c.max_y);
		if(clock() - t >100000) //100秒提交一次。
		{
			ptrTans->commit();
			ptrTans.reset(new  gpkg::transaction(db));
		}
	}
	//更新地物类的范围。
	db->contents_table()->update_extent(c);
	ptrTans->commit();

	ss.str("");
	ss<<"开始创建空间索引"<<code.strUserID;
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	ptrFeaClass->create_spatial_index(db->extensions_table());
	
	ss.str("");
	ss<<"创建空间索引完成";
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	//如果存在元数据的话
	std::string strMetaFile = m_VCTContext.MetadataFile();
	if(!strMetaFile.empty())
	{
		ss.str("");
		ss<<"创建元数据。";
		pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
		long long meta = m_VCTContext.MetaDataID();
		if(meta <=0)
			meta = m_VCTContext.StoreMetadata();
		if(meta >0)
			m_VCTContext.StoreMetadataReference(ptrFeaClass->name());
	}

	return true;
}

/// \brief 导入一个VCT文件的内容。
bool ImportVCT::ImportVCTFile(GeoStar::Utility::GsFile& file,gpkg::database_ptr& db,GIS::Progress * pProgress)
{
	std::stringstream ss;
	
	ss<<"准备导入文件："<<file.FullPath();
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	//绑定VCT文件的路径到符号缓存。
	m_VCTContext.BindVCT(file.Path());

	//解析整个VCT文件。
	VCTParser parser(file.Path());
	{
		VCTFileProgress progress(file.Size(),"解析VCT",file.Name().c_str(),pProgress);
		parser.Progress(&progress);
		parser.Parse();
		parser.Progress(NULL);
	}

	//顺序读取所有的FeatureCode
	std::vector<VCTFeatureCode>::iterator it =  parser.FeatureCodes().begin();
	for(;it != parser.FeatureCodes().end();it++)
	{
		//一个FeatureCode导出为一个地物类。
		ImportFeatureCode(parser,*it,db,pProgress);
	}

	return true;
}


/// \brief 执行插件
const char* ImportVCT::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	pProgress->OnLog("准备数据导入",GIS::LogLevel::eInfo);
	pProgress->OnLog("解析输入参数",GIS::LogLevel::eInfo);

	//输入参数
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		pProgress->OnLog("解析输入参数错误",GIS::LogLevel::eError);
		return NULL;
	}
	//输出的目录
	std::string strOuputFolder = kvp.Value("Output");
	if(strOuputFolder.empty())
	{
		pProgress->OnLog("没有设置输出路径",GIS::LogLevel::eError);
		return NULL;
	}

	//导入
	std::string strInputFile = kvp.Value("Path");
	if(strInputFile.empty())
	{
		pProgress->OnLog("没有设置输入路径",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "转换";
	strLog+=strInputFile;
	strLog+="到标准矢量数据";
	strLog+=strOuputFolder;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);

	bool bNew = GeoStar::Utility::GsFile(strOuputFolder.c_str()).Exists()?false:true;
	std::string strUtf8Path =	GeoStar::Utility::GsCW2A(GeoStar::Utility::GsCA2W(strOuputFolder.c_str()).m_WStr,
								GeoStar::Utility::eCP_UTF8).m_Str;
	//打开数据数据库。
	gpkg::database_ptr db(new gpkg::database(strUtf8Path.c_str(),bNew));
	pProgress->OnLog("打开输出数据集",GIS::LogLevel::eInfo);

	GeoStar::Utility::GsDir dir(strInputFile.c_str());
	GsVector<GeoStar::Utility::GsFile> vec =  dir.Files("*.vct");
	if(vec.empty())
	{
		pProgress->OnLog("没有可以转换的数据。",GIS::LogLevel::eError);
		return NULL;
	}


	std::stringstream ss;
	ss<<"准备转换"<<vec.size()<<"个VCT文件";
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	//准备好符号缓存，如果后面需要的话
	m_VCTContext.Attach(db);

	GsVector<GeoStar::Utility::GsFile>::iterator it = vec.begin();
	for(;it != vec.end();it++)
	{
		ImportVCTFile(*it,db,pProgress);
	}
	
	return NULL;
}

