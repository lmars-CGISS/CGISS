#include "StdAfx.h"
#include "ImportVCT.h"
#include <iostream>
#include <io.h>
#include "time.h"
#pragma comment(lib,"LibVCT")

std::string ToUtf8(const char* str)
{
	return GeoStar::Utility::GsCW2A(GeoStar::Utility::GsCA2W(str).m_WStr,GeoStar::Utility::eCP_UTF8).m_Str;
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
	
	GeoStar::Utility::GsGrowByteBuffer m_Geo;
	GeoStar::Kernel::GsWKBOGCWriter m_Writer;
	GeoStar::Kernel::GsPointPtr m_ptrPoint;
	GeoStar::Kernel::GsMultiPointPtr m_ptrMultiPoint;
	GeoStar::Kernel::GsPathPtr m_ptrPath;
	GeoStar::Kernel::GsPolylinePtr m_ptrPolyline;
	GeoStar::Kernel::GsRingPtr m_ptrRing;
	GeoStar::Kernel::GsPolygonPtr m_ptrPolygon;
	GeoStar::Kernel::GsGeometryBlob m_GeometryBlob;
	GeoStar::Utility::GsGrowByteBuffer m_Coord;
	GeoStar::Utility::GsGrowByteBuffer m_Inter;
	int m_nDim; //坐标维度。 
public:
	GPKGWriteFeature(VCTParser*	pParser,VCTFeatureCode& code,int nDim):m_Writer(&m_Geo)
	{
		m_nDim = nDim;
		m_Code = code; 
		m_pParser = pParser;
	}
	//准备读取一个地物。
	void Prepare(fpos_t pos,fpos_t attpos)
	{
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
		m_Geo.Allocate(0);
		if(attpos >0)
			m_pParser->ParseObject(attpos,m_Att); 

	}

public:
	/// \brief 设置地物的fid
	virtual void fid(long long id)
	{
	}
	/// \brief 获取地物的fid
	virtual long long fid()
	{
		return 0;
	}
		
	/// \brief geometry的数据长度
	virtual int geometry_length()
	{
		return m_Geo.BufferSize();
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
	void MakePoint()
	{
		if(m_Point.vecPoint.size() == 1)
		{
			if(!m_ptrPoint)
				m_ptrPoint = new GeoStar::Kernel::GsPoint();
			VCTPoint3D& pt = m_Point.vecPoint.front();
			m_ptrPoint->Set(pt.x,pt.y,pt.z);
			m_ptrPoint->CoordinateDimension(m_nDim);
			m_Writer.Write(m_ptrPoint);
			return;
		}

		if(!m_ptrMultiPoint)
			m_ptrMultiPoint = new GeoStar::Kernel::GsMultiPoint();
		m_ptrMultiPoint->CoordinateDimension(3);
		m_ptrMultiPoint->Set((const GeoStar::Kernel::GsRawPoint3D*)(&m_Point.vecPoint[0]),m_Point.vecPoint.size());
		m_ptrMultiPoint->CoordinateDimension(m_nDim);
		m_Writer.Write(m_ptrPoint);
	}
	void MakeLine()
	{
		if(m_Line.vecLineData.size() == 1)
		{
			if(!m_ptrPath)
				m_ptrPath  = new GeoStar::Kernel::GsPath();
			m_Coord.Allocate(0);
			VCTLineElement &e = m_Line.vecLineData.front();
			m_Coord.AppendT(&e.vecArcPoint[0],e.vecArcPoint.size());

			int inter[]={1,2,1};
			
			m_ptrPath->GeometryBlobPtr()->CoordinateDimension(3);
			m_ptrPath->GeometryBlobPtr()->SetCoordinate(inter,3,m_Coord.PtrT<double>(),m_Coord.BufferSizeT<double>());
			m_ptrPath->GeometryBlobPtr()->CoordinateDimension(m_nDim);
			m_Writer.Write(m_ptrPath);	
			return;
		}
		m_Coord.Allocate(0);
		m_Inter.Allocate(0);

		std::vector<VCTLineElement>::iterator it = m_Line.vecLineData.begin();
		for(;it != m_Line.vecLineData.end();it++)
		{
			int inter[]={m_Coord.BufferSizeT<double>() + 1,2,1};
			m_Inter.AppendT(inter,3);

			m_Coord.AppendT(&it->vecArcPoint[0],it->vecArcPoint.size());
		}
		if(!m_ptrPolyline)
			m_ptrPolyline = new GeoStar::Kernel::GsPolyline();
		
		m_ptrPolyline->Clear();
		m_ptrPolyline->GeometryBlobPtr()->CoordinateDimension(3);
		m_ptrPolyline->GeometryBlobPtr()->SetCoordinate(m_Inter.PtrT<int>(),m_Inter.BufferSizeT<int>(),
			m_Coord.PtrT<double>(),m_Coord.BufferSizeT<double>());

		m_ptrPolyline->GeometryBlobPtr()->CoordinateDimension(m_nDim);
		m_Writer.Write(m_ptrPolyline);	
	}
	
	void MakePolygon()
	{
		if(m_Polygon.vecPolygonElement.size() == 1)
		{
			if(!m_ptrRing)
				m_ptrRing  = new GeoStar::Kernel::GsRing();
			m_Coord.Allocate(0);
			VCTPolygonElement &e = m_Polygon.vecPolygonElement.front();
			m_Coord.AppendT(&e.vecPoints[0],e.vecPoints.size());

			int inter[]={1,3,1};
			
			m_ptrRing->GeometryBlobPtr()->CoordinateDimension(3);
			m_ptrRing->GeometryBlobPtr()->SetCoordinate(inter,3,m_Coord.PtrT<double>(),m_Coord.BufferSizeT<double>());
			m_ptrRing->GeometryBlobPtr()->CoordinateDimension(m_nDim);
			m_Writer.Write(m_ptrRing);	
			return;
		}
		m_Coord.Allocate(0);
		m_Inter.Allocate(0);

		std::vector<VCTPolygonElement>::iterator it = m_Polygon.vecPolygonElement.begin();
		for(;it != m_Polygon.vecPolygonElement.end();it++)
		{
			int inter[]={m_Coord.BufferSizeT<double>() + 1,3,1};
			m_Inter.AppendT(inter,3);

			m_Coord.AppendT(&it->vecPoints[0],it->vecPoints.size());
		}
		if(!m_ptrPolygon)
			m_ptrPolygon = new GeoStar::Kernel::GsPolygon();
		
		m_ptrPolygon->Clear();
		m_ptrPolygon->GeometryBlobPtr()->Clear();
		m_ptrPolygon->GeometryBlobPtr()->CoordinateDimension(3);
		m_ptrPolygon->GeometryBlobPtr()->SetCoordinate(m_Inter.PtrT<int>(),m_Inter.BufferSizeT<int>(),
			m_Coord.PtrT<double>(),m_Coord.BufferSizeT<double>());

		m_ptrPolygon->CoordinateDimension(m_nDim);
		m_Writer.Write(m_ptrPolygon);	

	}
	void MakeAnn()
	{
	}

	///用于将Geometry构造成WKB
	void MakeGeometry()
	{
		switch(m_Code.GeometryType)
		{
		case VCT_POINT:  
			MakePoint();
			break;
		case VCT_LINE: 
			MakeLine();
			break;
		case VCT_POLYGON: 
			MakePolygon();
			break;
		case VCT_SOLID: 
			break;
		case VCT_ANNOTATION: 
			MakeAnn();
			break;
		}
	}
	void UnionExtent(double& xmin,double& ymin,double &xmax,double& ymax)
	{
		gpkg::geo_package_binary *head = m_Geo.PtrT<gpkg::geo_package_binary>();
		xmin = min(head->envelope[0],xmin);
		xmax = max(head->envelope[1],xmax);

		ymin = min(head->envelope[2],ymin);
		ymax = max(head->envelope[3],ymax);

	}

	/// \brief 获取geometry的数据头指针
	virtual gpkg::geo_package_binary* geometry()
	{
		if(m_Geo.BufferSize() ==0)
		{
			//缺省使用EnvelopeXY的模式
			m_Geo.Allocate( 8 + 4 * 8);
			m_Geo.SetBufferValue(0);
			gpkg::geo_package_binary *head = m_Geo.PtrT<gpkg::geo_package_binary>();
			head->magic[0] = 'G';
			head->magic[1] = 'P';
			head->is_little_endian(true);
			head->is_standard(true);
			head->envelope_type(gpkg::EnvelopeXY);
			ComputerExtent(head);

			m_Writer.Reset();
			MakeGeometry();
		}
		return m_Geo.PtrT<gpkg::geo_package_binary>();
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
bool ImportVCT::ImportOne(VCTParser &parser,VCTFeatureCode& code,gpkg::database_ptr& db,GIS::Progress * pProgress)
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
		int nPos = 0;
		if(itAtt != cacheAtt.end())
			nPos = itAtt->second;
		feature.Prepare(it->second,nPos);
		
		ptrFeaClass->save(&feature);
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
	
	return true;
}

/// \brief 执行插件
bool ImportVCT::ImportOne(GeoStar::Utility::GsFile& file,gpkg::database_ptr& db,GIS::Progress * pProgress)
{
	std::stringstream ss;
	
	ss<<"准备导入文件："<<file.FullPath();
	pProgress->OnLog(ss.str().c_str(),GIS::LogLevel::eInfo);
	
	VCTParser parser(file.FullPath().c_str());
	{
		VCTFileProgress progress(file.Size(),"解析VCT",file.Name().c_str(),pProgress);
		parser.Progress(&progress);
		parser.Parse();
		parser.Progress(NULL);

	}
	std::vector<VCTFeatureCode>::iterator it =  parser.FeatureCodes().begin();
	for(;it != parser.FeatureCodes().end();it++)
	{
		ImportOne(parser,*it,db,pProgress);
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

	GsVector<GeoStar::Utility::GsFile>::iterator it = vec.begin();
	for(;it != vec.end();it++)
	{
		ImportOne(*it,db,pProgress);
	}
	
	return NULL;
}

