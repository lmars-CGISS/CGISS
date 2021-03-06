#include "StdAfx.h"
#include "ExportVCT.h"
#include "WKBHelp.h"


std::string FromUtf8(const char* str)
{
	return GeoStar::Utility::GsCW2A(GeoStar::Utility::GsCA2W(str,GeoStar::Utility::eCP_UTF8).m_WStr).m_Str;
}
StyleCache::StyleCache()
{

}
void StyleCache::Attach(VCTWriter* w)
{
	m_nIndex = 0;
	m_Writer = w;
	m_StyleName.clear();
	m_FeaClassMetadata.clear();
}
//根据符号id查询style的名称
std::string StyleCache::StyleName(long long symID)
{
	std::map<long long,std::string>::iterator it = m_StyleName.find(symID);
	if(it != m_StyleName.end())
		return it->second;
	return std::string();
}
void StyleCache::AddFeatureClassMetadata(long long id)
{
	//如果元数据的id已经添加过则不需要添加了。
	std::vector<long long>::iterator it = m_FeaClassMetadata.begin();
	for(;it != m_FeaClassMetadata.end();it++)
	{
		if(*it == id)
			return;
	}

	m_FeaClassMetadata.push_back(id);
}
void StyleCache::Commit(gpkg::database_ptr& db)
{
	if(m_ptrSymLib)
	{
		GeoStar::Utility::GsFile f(m_Writer->Path());
		f.ChangeExtension("symx");
		m_ptrSymLib->Save(f.Path());
	}
	if(m_FeaClassMetadata.empty()) return;
	gpkg::metadata_table* table = db->metadata_table();
	gpkg::metadata meta;
	//构建以VCT文件名后面加xml后缀的路径作为元数据文件名
	std::string strMetaFile = m_Writer->Path();
	strMetaFile+=".xml";
	//这里只考虑写入第一个元数据。将来需要考虑融合多个元数据。
	for(int i =0;i < m_FeaClassMetadata.size();i++)
	{
		meta.id = m_FeaClassMetadata[i];
		
		//查询元数据
		if(table->query(meta))
		{
			if(!meta.data.empty())
			{
				//将元数据写入到文件中。
				std::ofstream f(strMetaFile.c_str());
				f<<meta.data;
				return;
			}
		}

	}
}
std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> StyleCache::SymbolLib()
{
	if(m_ptrSymLib) return m_ptrSymLib;
	m_ptrSymLib = std::make_shared<GeoStar::Kernel::GsSymbolLibrary>();
	GeoStar::Utility::GsFile f(m_Writer->Path());
	f.ChangeExtension("symx");
	m_ptrSymLib->Name(f.Name().c_str());
	return m_ptrSymLib;
}
void StyleCache::SaveStyle(GeoStar::Kernel::GsPointSymbol* pSym,const std::string& name)
{
	std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib();
	ptrLib->Symbols()->push_back(pSym);

	VCTStyle style;
	style.strID = name;
	style.vecPairs.push_back(VCTPairEx("LAYERNAME",FromUtf8(pSym->Name().c_str())));
	style.vecPairs.push_back(VCTPairEx("SYMBOLLIBPROTOCOL","GeoStarXMLSymbol"));
	style.vecPairs.push_back(VCTPairEx("SYMBOLLIBLOCATION",ptrLib->Name()));
	
	style.vecPairs.push_back(VCTPairEx("COLOR",GeoStar::Utility::GsStringHelp::ToString(pSym->Color().Argb)));
	style.vecPairs.push_back(VCTPairEx("POINTSIZE",GeoStar::Utility::GsStringHelp::ToString(pSym->Size())));
	style.vecPairs.push_back(VCTPairEx("SYMBOLID",GeoStar::Utility::GsStringHelp::ToString(pSym->Code())));
	
	m_Writer->Write(style);
}
void StyleCache::SaveStyle(GeoStar::Kernel::GsLineSymbol* pSym,const std::string& name)
{
	std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib();
	ptrLib->Symbols()->push_back(pSym);

	VCTStyle style;
	style.strID = name;
	style.vecPairs.push_back(VCTPairEx("LAYERNAME",FromUtf8(pSym->Name().c_str())));
	style.vecPairs.push_back(VCTPairEx("SYMBOLLIBPROTOCOL","GeoStarXMLSymbol"));
	style.vecPairs.push_back(VCTPairEx("SYMBOLLIBLOCATION",ptrLib->Name()));
	
	style.vecPairs.push_back(VCTPairEx("COLOR",GeoStar::Utility::GsStringHelp::ToString(pSym->Color().Argb)));
	style.vecPairs.push_back(VCTPairEx("LINEWIDTH",GeoStar::Utility::GsStringHelp::ToString(pSym->Width())));
	style.vecPairs.push_back(VCTPairEx("SYMBOLID",GeoStar::Utility::GsStringHelp::ToString(pSym->Code())));
	
	m_Writer->Write(style);
}
void StyleCache::SaveStyle(GeoStar::Kernel::GsFillSymbol* pSym,const std::string& name)
{
	std::shared_ptr<GeoStar::Kernel::GsSymbolLibrary> ptrLib = SymbolLib();
	ptrLib->Symbols()->push_back(pSym);

	VCTStyle style;
	style.strID = name;
	style.vecPairs.push_back(VCTPairEx("LAYERNAME",FromUtf8(pSym->Name().c_str())));
	style.vecPairs.push_back(VCTPairEx("SYMBOLLIBPROTOCOL","GeoStarXMLSymbol"));
	style.vecPairs.push_back(VCTPairEx("SYMBOLLIBLOCATION",ptrLib->Name()));
	
	style.vecPairs.push_back(VCTPairEx("COLOR",GeoStar::Utility::GsStringHelp::ToString(pSym->FillColor().Argb)));
	style.vecPairs.push_back(VCTPairEx("SYMBOLID",GeoStar::Utility::GsStringHelp::ToString(pSym->Code())));
		
	m_Writer->Write(style);
}
void StyleCache::SaveStyle(GeoStar::Kernel::GsTextSymbol* pSym,const std::string& name)
{
	VCTStyle style;
	style.strID = name;
	if(pSym->Name().empty())
		style.vecPairs.push_back(VCTPairEx("LAYERNAME",FromUtf8(pSym->Name().c_str())));
	
	style.vecPairs.push_back(VCTPairEx("COLOR",GeoStar::Utility::GsStringHelp::ToString(pSym->Color().Argb)));
	style.vecPairs.push_back(VCTPairEx("BACKCOLOR",GeoStar::Utility::GsStringHelp::ToString(pSym->BackgroundColor().Argb)));
	if(pSym->Code() >0)
		style.vecPairs.push_back(VCTPairEx("SYMBOLID",GeoStar::Utility::GsStringHelp::ToString(pSym->Code())));

	style.vecPairs.push_back(VCTPairEx("FONT",FromUtf8(pSym->Font().c_str())));
	style.vecPairs.push_back(VCTPairEx("ANNOHEIGHT",GeoStar::Utility::GsStringHelp::ToString(pSym->Height())));
	style.vecPairs.push_back(VCTPairEx("ANNOWIDTH",GeoStar::Utility::GsStringHelp::ToString(pSym->Width())));
	style.vecPairs.push_back(VCTPairEx("ANNOSPACE",GeoStar::Utility::GsStringHelp::ToString((pSym->VerticalExtra() + pSym->HorizonExtra())/2)));
	if(pSym->Bold())
		style.vecPairs.push_back(VCTPairEx("ANNOWEIGHT","700"));
	else
		style.vecPairs.push_back(VCTPairEx("ANNOWEIGHT","400"));
	switch(pSym->TextStyle())
	{
	case GeoStar::Kernel::eTextStyleLeftItalic:
		style.vecPairs.push_back(VCTPairEx("ANNOSTYLE","1"));
		break;
	case GeoStar::Kernel::eTextStyleRightItalic:
		style.vecPairs.push_back(VCTPairEx("ANNOSTYLE","2"));
		break;
	case GeoStar::Kernel::eTextStyleLeftShrug:
		style.vecPairs.push_back(VCTPairEx("ANNOSTYLE","3"));
		break;
	case GeoStar::Kernel::eTextStyleRightShrug:
		style.vecPairs.push_back(VCTPairEx("ANNOSTYLE","4"));
		break;
	default:
		style.vecPairs.push_back(VCTPairEx("ANNOSTYLE","0"));
		break;
	}
	if(pSym->UnderLine())
		style.vecPairs.push_back(VCTPairEx("ANNOUNDERLINE","1"));
	else
		style.vecPairs.push_back(VCTPairEx("ANNOUNDERLINE","0"));

	if(pSym->StrikeOut())
		style.vecPairs.push_back(VCTPairEx("ANNOSTRIKE","1"));
	else
		style.vecPairs.push_back(VCTPairEx("ANNOSTRIKE","0"));
	
	if(pSym->ShadowColor().A >0)
		style.vecPairs.push_back(VCTPairEx("ANNOSHADOW","1"));
	else
		style.vecPairs.push_back(VCTPairEx("ANNOSHADOW","0"));
	
	if(pSym->Hollow())
		style.vecPairs.push_back(VCTPairEx("ANNOHOLE","1"));
	else
		style.vecPairs.push_back(VCTPairEx("ANNOHOLE","0"));
	
	char align[3];
	memset(align,0,3);
	switch(pSym->HorizonAlign())
	{
	case GeoStar::Kernel::eStringAlignmentNear:
		align[0] = 'L';
		break;
	case GeoStar::Kernel::eStringAlignmentCenter:
		align[0] = 'C';
		break;
	case GeoStar::Kernel::eStringAlignmentFar:
		align[0] = 'R';
		break;
	}
	switch(pSym->VerticalAlign())
	{
	case GeoStar::Kernel::eStringAlignmentNear:
		align[1] = 'T';
		break;
	case GeoStar::Kernel::eStringAlignmentCenter:
		align[1] = 'C';
		break;
	case GeoStar::Kernel::eStringAlignmentFar:
		align[1] = 'B';
		break;
	}
	style.vecPairs.push_back(VCTPairEx("ANNOALIGNMENT",align));

	m_Writer->Write(style);

}


//存储一个符号为style，返回sytle的明恒
std::string StyleCache::SaveStyle(gpkg::symbol &sym)
{
	if(sym.data.empty())
		return std::string();

	//符号数据类型必须是xml
	if(stricmp(sym.mime_type.c_str(),"text/xml") !=0)
		return std::string();

	//如果标准必须是geostar的，其他的无法识别
	if(stricmp(sym.sd_standard_uri.c_str(),"GeoStar XML Symbol") !=0)
		return std::string();

	std::string strxml;
	const char* str = (const char*)&sym.data[0];
	strxml.insert(strxml.end(),str,str+sym.data.size());
	//从xml反序列化生成符号对象
	GeoStar::Kernel::GsSymbolPtr ptrSym  = GeoStar::Kernel::GsSymbolLibrary::ParserSymbol(strxml.c_str());
	if(!ptrSym )
		return std::string();
	
	//式样的名称。
	std::stringstream ss;
	ss<<"style_"<<m_nIndex++;
	
	switch(ptrSym->Type())
	{
	case GeoStar::Kernel::ePointSymbol:
		SaveStyle(GeoStar::Kernel::GsPointSymbolPtr(ptrSym),ss.str());
		break;
	case GeoStar::Kernel::eLineSymbol:
		SaveStyle(GeoStar::Kernel::GsLineSymbolPtr(ptrSym),ss.str());
		break;
	case GeoStar::Kernel::eFillSymbol:
		SaveStyle(GeoStar::Kernel::GsFillSymbolPtr(ptrSym),ss.str());
		break;
	case GeoStar::Kernel::eTextSymbol:
		SaveStyle(GeoStar::Kernel::GsTextSymbolPtr(ptrSym),ss.str());
		break;
	}

	//存储符号id和存储到vct中的style名称的关系。
	m_StyleName[sym.id] = ss.str();
	return ss.str();
}


ExportVCT::ExportVCT(void)
{
	m_strName = "导出VCT矢量数据格式";
	m_strDescription = "导出VCT矢量数据格式";
	
	m_eType = GIS::eExport;
}
ExportVCT::~ExportVCT(void)
{
}
VCT_GEOMETRY_TYPE GPKGToGeo(const char* strGeo)
{
	if(stricmp(strGeo,"POINT")==0)
		return VCT_POINT;
	if(stricmp(strGeo,"LINESTRING")==0)
		return VCT_LINE;
	if(stricmp(strGeo,"MULTIPOLYGON")==0)
		return VCT_POLYGON;

	return VCT_POINT;
}
class CReadFeature:public gpkg::feature
{
	VCT_GEOMETRY_TYPE m_gType;
	int m_nGeoIndex;

	VCTPoint m_Point;
	VCTLine  m_Line;
	VCTPolygon m_Polygon;
	VCTSolid m_Solid;
	VCTAnnotation  m_Ann;
	VCTAttributeRow m_Row;
	WKBReader m_Reader;
	VCTFeatureCode m_Code;
	VCTID& m_ID;
	bool m_bGeo;
public:
	CReadFeature(int nFieldCount,VCT_GEOMETRY_TYPE gType,int nGeoIndex,VCTFeatureCode &code,VCTID& ID):m_ID(ID)
	{
		m_bGeo = false;
		m_nGeoIndex = nGeoIndex;
		m_gType = gType;
		m_Row.vecstrFieldValues.resize(nFieldCount);

		m_Point.ObjHeader.strStyle = code.strName;
		m_Point.ObjHeader.strUserID = code.strName;

		m_Line.ObjHeader.strStyle = code.strName;
		m_Line.ObjHeader.strUserID = code.strName;

		m_Polygon.ObjHeader.strStyle = code.strName;
		m_Polygon.ObjHeader.strUserID = code.strName;

		m_Solid.ObjHeader.strStyle = code.strName;
		m_Solid.ObjHeader.strUserID = code.strName;

		m_Ann.ObjHeader.strStyle = code.strName;
		m_Ann.ObjHeader.strUserID = code.strName;

	}
public:
	void Reset()
	{
		m_bGeo = false; 
	}
	bool IsValid()
	{
		return m_bGeo;
	}
	/// \brief 设置地物的fid
	virtual void fid(long long id)
	{
		m_Row.nOID  = id;
	}
	/// \brief 获取地物的fid
	virtual long long fid()
	{
		return m_Row.nOID;
	}
		
	/// \brief geometry的数据长度
	virtual int geometry_length()
	{
		return 0;
	}
	/// \brief 获取geometry的数据头指针
	virtual gpkg::geo_package_binary* geometry()
	{
		return NULL;
	}
	void GeometryBlobToVCT(GeoStar::Kernel::GsGeometryBlob* pBlob,std::vector<VCTPoint3D>& vec,int n = 0)
	{
		if(n <=0)
			vec.resize(pBlob->CoordinateLength() / pBlob->CoordinateDimension());
		else
			vec.resize(n);

		if(pBlob->CoordinateDimension() == 2)
		{	
			std::copy((GeoStar::Kernel::GsRawPoint*)pBlob->Coordinate(),
				(GeoStar::Kernel::GsRawPoint*)pBlob->Coordinate() + vec.size(),
				(GeoStar::Kernel::GsRawPoint3D*)(&vec[0]));
		}
		else
			memcpy(&vec[0],pBlob->Coordinate(),vec.size() * 24);

	}
	/// \brief 设置geometry
	virtual void geometry(gpkg::geo_package_binary* geo,int nlen)
	{
		if(NULL == geo) 
			return;

		unsigned char* wkb = geo->wkb_ptr();
		m_Reader.Begin(wkb,nlen - geo->size());
		OGCGeometryType eType = m_Reader.GeometryType(true);
		switch(eType)
		{
		case eOGCPoint:// 1 
		case eOGCMultiPoint:// 4 
			m_Point.vecPoint.clear();
			m_Reader.Read(m_Point);
			m_bGeo = true;
			break;
		case eOGCLineString:// 2 
		case eOGCMultiLineString:// 5 
			m_Line.vecLineData.clear();
			m_Reader.Read(m_Line);
			m_bGeo = true;
			break;
		case eOGCPolygon:// 3 
		case eOGCMultiPolygon:// 6 
			
			m_Polygon.vecPolygonElement.clear();
			m_Reader.Read(m_Polygon);
			m_bGeo = true;
			break;
		}
	}
	void BindStyle(const std::string &styleName)
	{
		switch(m_gType)
		{
		case VCT_POINT:
			m_Point.ObjHeader.strStyle = styleName;
			break;
		case VCT_LINE:
			m_Line.ObjHeader.strStyle = styleName;
			break;
		case VCT_POLYGON:
			m_Polygon.ObjHeader.strStyle = styleName;
			break;
		case VCT_ANNOTATION:
			m_Ann.ObjHeader.strStyle = styleName;
			break;
		}
	}
	void Write(VCTFeatureWriter &w)
	{
		m_Row.nOID = m_ID++;
		if(m_gType == VCT_POINT)
		{
			m_Point.ObjHeader.nObjID = m_Row.nOID;
			w.Write(m_Point);
		}
		else if(m_gType == VCT_LINE)
		{
			m_Line.ObjHeader.nObjID = m_Row.nOID;
			w.Write(m_Line);
		}
		else if(m_gType == VCT_POLYGON)
		{
			m_Polygon.ObjHeader.nObjID = m_Row.nOID;
			w.Write(m_Polygon);
		}
		else if(m_gType == VCT_ANNOTATION)
		{
			m_Ann.ObjHeader.nObjID = m_Row.nOID;
			m_Ann.strText = m_Row.vecstrFieldValues.front();
			
			//将普通点转换成注记点
			m_Ann.vecAnnoPoint.resize(m_Point.vecPoint.size());
			for(int i = 0;i<m_Point.vecPoint.size();i++)
			{
				m_Ann.vecAnnoPoint[i].vctPoint3D = m_Point.vecPoint[i];
			}
			w.Write(m_Ann);
			//删除第一个属性。
			m_Row.vecstrFieldValues.erase(m_Row.vecstrFieldValues.begin());
		}
		
		w.Write(m_Row);
	}


	/// \brief 获取某列的地物整数字段值
	virtual long long int_value(int col)
	{
		return 0;
	}
	/// \brief 获取某列的地物浮点字段值
	virtual double float_value(int col)
	{
		return 0;
	}
	/// \brief 获取某列的地物字符串字段值
	virtual const char* string_value(int col)
	{
		return NULL;
	}

	/// \brief 获取某列的地物整数字段值
	virtual void value(int col,long long val)
	{ 
		std::stringstream ss;
		ss<<val;
		value(col,ss.str().c_str());
	}
	/// \brief 获取某列的地物浮点字段值
	virtual void value(int col,double val)
	{
		std::stringstream ss;
		ss<<std::setprecision(10)<<val;
		value(col,ss.str().c_str());
	}
	/// \brief 获取某列的地物字符串字段值
	virtual void value(int col,const char * val)
	{
		if(col < m_nGeoIndex)
			col--;
		else
			col-=2;
		std::string strVal = FromUtf8(val);
		if(m_Row.vecstrFieldValues.size() <= col + 1)
			m_Row.vecstrFieldValues.resize(col + 1);

		if(val)
			m_Row.vecstrFieldValues[col] = strVal;
		else
			m_Row.vecstrFieldValues[col].clear();

	}

};
//根据空间参考
void PrepareHead(VCTHead& head,gpkg::content& content,gpkg::spatial_ref& ref)
{
	head.dfMinX = min(head.dfMinX, content.min_x);
	head.dfMaxX = max(head.dfMaxX, content.max_x);

	head.dfMinY = min(head.dfMinY, content.min_y);
	head.dfMaxY = max(head.dfMaxY, content.max_y);

	GeoStar::Kernel::GsSpatialReferencePtr ptrSR;
	if(!ref.definition.empty())
		ptrSR = new GeoStar::Kernel::GsSpatialReference(ref.definition.c_str());
	else if(ref.srs_id>0)
		ptrSR = new GeoStar::Kernel::GsSpatialReference(ref.srs_id);
	else
		ptrSR = new GeoStar::Kernel::GsSpatialReference(4326);
	if(ptrSR->Units() == GeoStar::Kernel::eMeter)
	{
		head.chCoordSysType = 'M';
		head.chUnit = 'M';
		head.strXYUnit = "M";
	}
	else if(ptrSR->Units() == GeoStar::Kernel::eDegree)
	{
		head.strXYUnit = "D";
		head.chUnit = 'D';
		head.chCoordSysType = 'D';
	}
	head.strProjection = FromUtf8(ptrSR->Projection().c_str());
	head.strSpheroid = FromUtf8(ptrSR->Ellipsoid().c_str());

	time_t t = time(NULL);
	tm  gm = *localtime(&t);

	std::stringstream ss;
	ss<<(gm.tm_year + 1900)<<std::setw(2)<<std::setfill('0')<<(gm.tm_mon + 1)<<gm.tm_mday;
	head.strDate = ss.str();
}

//输出到VCT文件中。
void ExportVCT::WriteTo(VCTWriter& w,gpkg::content& content,gpkg::database_ptr db,GIS::Progress * pProgress,VCTID& id)
{
	//打开地物表。
	gpkg::feature_table_ptr ptrFeaClass = db->open_feature_table(content.table_name.c_str());
	if(!ptrFeaClass)
	{
		std::stringstream ss;
		ss<<"地物类表"<<content.table_name<<"打开失败";
		pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eError);
		return ;
	}
	//准备好VCT的头。
	PrepareHead(w.Head(),content,db->spatial_ref_table()->query(content.srs_id));

	//获得几何类型。
	gpkg::geometry_column geo =  db->geometry_columns_table()->query(content.table_name.c_str());
	VCTFeatureCode code;
	code.GeometryType = GPKGToGeo(geo.geometry_type_name.c_str());
	//如果几何类型为点的话则考虑几何类型是否为注记类型。
	if(code.GeometryType == VCT_POINT)
	{
		//如果存在注记的扩展则一定是注记地物类。
		gpkg::extension ext;
		ext.table_name = content.table_name;
		ext.column_name = geo.column_name;
		ext.extension_name = "gpkgc_annotation";
		if(db->extensions_table()->query(ext))
			code.GeometryType = VCT_ANNOTATION;
	}
	code.strName = FromUtf8(content.identifier.c_str());
	code.strUserID = FromUtf8(code.strName.c_str());
	code.strAttributeTableName = FromUtf8(code.strName.c_str());
	//表结构
	VCTTableStructure tab;
	tab.strTableName = code.strUserID;
	

	//获取字段结构。
	std::vector<gpkg::field> vecField = ptrFeaClass->fields();
	std::vector<gpkg::field>::iterator it = vecField.begin();
	//几何字段的索引
	int nGeoFieldIndex  = -1;
	for(;it != vecField.end();it++)
	{
		if(it == vecField.begin()) //跳开首字段，因为这个是FID
			continue;
		//对于注记地物类跳开annotaionValue字段
		if(code.GeometryType == VCT_ANNOTATION &&  stricmp(it->name.c_str(),"annotaionValue")==0)
			continue;
		//翻译所有的字段。
		switch(it->type)
		{
		case gpkg::BOOLEAN:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_BOOL));
			break;
		case gpkg::TINYINT:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_SMALLINT));
			break;
		case gpkg::MEDIUMINT:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_INTEGER));
			break;
		case gpkg::INTEGER: 
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_INTEGER));
			break;
		case gpkg::FLOAT:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_FLOAT,10,8));
			break;
		case gpkg::DOUBLE: 
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_FLOAT,38,10));
			break;
		case gpkg::TEXT:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_CHAR,1024,0));
			break;
		case gpkg::BLOB:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_VARBIN));
			break;
		case gpkg::DATE:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_DATE));
			break;
		case gpkg::DATETIME:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_DATETIME));
			break;

		case gpkg::POINT:
		case gpkg::LINESTRING:
		case gpkg::MULTIPOLYGON:
			nGeoFieldIndex = (it - vecField.begin());
			continue;
			break;
		default:
			tab.vecFields.push_back(VCTField(FromUtf8(it->name.c_str()).c_str(),VCT_CHAR,1024,0));
			break;

		}
	}

	//开始写入一个地物类。
	VCTFeatureWriter writer = w.BeginFeature(code,tab);

	//地物类的总数
	long nMax = ptrFeaClass->count();
	//设置空过滤条件。
	ptrFeaClass->filter();
	int nFieldCount = tab.vecFields.size();
	if(code.GeometryType == VCT_ANNOTATION)
		nFieldCount++;

	CReadFeature fea(nFieldCount,code.GeometryType,nGeoFieldIndex,code,id);
	int nPos  = 0;
	std::string strTitle = "转换地物";
	std::string strContent = code.strName;
	gpkg::symbol_reference_table* pSymRef = db->symbol_reference_table();
	gpkg::symbol_reference symRef;
	gpkg::symbol_table* pSyms = db->symbol_table();
	gpkg::symbol sym;
	fea.Reset();
	while(ptrFeaClass->next(&fea))
	{
		if(!fea.IsValid())
		{
			fea.Reset();
			continue;
		}
		//查询地物关联的符号。
		if(pSymRef->query(content.table_name.c_str(),fea.fid()))
		{
			//获取所有的符号关联。
			while(pSymRef->next(symRef))
			{
				//获取符号id对应存储到vct中的式样名称
				std::string strName = m_StyleCache.StyleName(symRef.symbol_id);
				if(strName.empty()) //如果名称为空则标示没有存储到vct中。
				{
					sym.id = symRef.symbol_id;
					if(pSyms->query(sym)) //根据符号id从数据库中查询符号数据
						strName = m_StyleCache.SaveStyle(sym); //存储符号数据并获取style的名称
				}
				if(!strName.empty())
					fea.BindStyle(strName);
			}
		}

		//写入到vct中
		fea.Write(writer);
		
		nPos++;
		pProgress->OnProgress(nPos,nMax,strTitle.c_str(),strContent.c_str());
		fea.Reset();
	}

	//查询地物类的元数据
	gpkg::metadata_reference_table* pRefTable = db->metadata_reference_table();
	std::string strScope = "table";
	pRefTable->query(strScope,content.table_name);
	gpkg::metadata_reference ref;
	//如果查询到地物类的元数据则加入到cache中，当commit的时候会生成元数据文件。
	if(pRefTable->next(ref))
		m_StyleCache.AddFeatureClassMetadata(ref.md_file_id);

}
/// \brief 执行插件
const char* ExportVCT::Execute(const char* strParameter,GIS::Progress * pProgress)
{
	pProgress->OnLog("准备数据导出",GIS::LogLevel::eInfo);
	pProgress->OnLog("解析输入参数",GIS::LogLevel::eInfo);

	//输入参数
	KVParameter kvp(strParameter);
	if(kvp.Error())
	{
		pProgress->OnLog("解析输入参数错误",GIS::LogLevel::eError);
		return NULL;
	}
	//输入的geopackage文件。
	std::string strInput = kvp.Value("Input");
	if(strInput.empty())
	{
		pProgress->OnLog("没有设置输入路径。",GIS::LogLevel::eError);
		return NULL;
	}

	//输出VCT文件。
	std::string strOutFile = kvp.Value("Path");
	if(strOutFile.empty())
	{
		pProgress->OnLog("没有设置输出文件",GIS::LogLevel::eError);
		return NULL;
	}

	std::string strLog = "转换标准格式矢量数据为VCT矢量数据从";
	strLog+=strInput;
	strLog+="到";
	strLog+=strOutFile;
	pProgress->OnLog(strLog.c_str(),GIS::LogLevel::eInfo);
	 
	GeoStar::Utility::GsFile file(GeoStar::Utility::GsUtf8(strInput.c_str()));
	if(!file.Exists())
	{
		pProgress->OnLog("输入路径不存在。",GIS::LogLevel::eError);
		return NULL;
	}
	
	
	//如果是以VCT为扩展名的文件则标识输出到到单个VCT文件中。
	bool bSingleVCT = GeoStar::Utility::GsStringHelp::EndWith( strOutFile.c_str(),".vct",true);

	//打开数据数据库。
	gpkg::database_ptr db(new gpkg::database(file.FullPath().c_str(),false));
	pProgress->OnLog("打开输出数据集",GIS::LogLevel::eInfo);
	
	//枚举所有的feature
	std::vector<gpkg::content> vecContent = db->contents_table()->query("features");
	std::vector<gpkg::content>::iterator it = vecContent.begin();
	VCTID id = 1;
	if(bSingleVCT)
	{
		VCTWriter w(strOutFile.c_str());
		m_StyleCache.Attach(&w);
		for(;it != vecContent.end();it++)
		{
			WriteTo(w,*it,db,pProgress,id);
		}
		m_StyleCache.Commit(db);
		//结束绘制。
		pProgress->OnLog("提交数据。",GIS::LogLevel::eInfo);
		w.Finish();
	}
	else //如果非单个文件的话则每个地物类输出一个文件。
	{ 
		for(;it != vecContent.end();it++)
		{ 
			string strFileName = it->table_name.c_str();
			strFileName+=".vct";
			strFileName = GeoStar::Utility::GsFileSystem::Combine(GeoStar::Utility::GsUtf8( strOutFile.c_str()),strFileName.c_str());

			VCTWriter w(strFileName.c_str());
			m_StyleCache.Attach(&w);
			WriteTo(w,*it,db,pProgress,id);
			pProgress->OnLog("提交数据。",GIS::LogLevel::eInfo);
			m_StyleCache.Commit(db);
			w.Finish();
		}
	}

	return NULL;
}