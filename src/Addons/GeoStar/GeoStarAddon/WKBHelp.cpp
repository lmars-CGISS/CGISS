#include "StdAfx.h"
#include "WKBHelp.h"

	//当前操作系统的字节序类型。
ByteOrderType ByteOrder::OSByteOrderType()
{
	int x = 0x1;
	return ((*(char *)&x) == 0x1)?eLittleEndian:eBigEndian;
}

WKBReader::WKBReader(void)
{
	m_OSOrder = ByteOrder::OSByteOrderType();
}


WKBReader::~WKBReader(void)
{
}

void WKBReader::Begin(const unsigned char* pBlob,int nSize)
{
	m_pStart =  pBlob;
	m_pEnd = pBlob + nSize;
	m_pCurrent = m_pStart;
	m_Order = (ByteOrderType)pBlob[0];
}
OGCGeometryType WKBReader::GeometryType(bool bSimple)
{
	OGCGeometryType eType = ((OGCGeometryType*)(m_pCurrent + 1))[0];
	if(m_OSOrder != m_Order)
		GeoStar::Utility::GsEndianConverter::SwapRefT(eType);
	if(bSimple && (eType & eOGCGeometryZ))
		eType = (OGCGeometryType)(eType - eOGCGeometryZ);
	return eType;
}
void WKBReader::Read(VCTPoint3D& pt,bool bZ)
{
	pt.x = ReadT<double>();
	pt.y = ReadT<double>();
	if(bZ) pt.z = ReadT<double>();
} 
bool WKBReader::Read(VCTPoint& pt)
{
	OGCGeometryType eType = GeometryType();
	m_pCurrent+=5;
	if(eType & eOGCPoint)
	{
		pt.FeatureType = VCT_POINT_DEFAULT;
		pt.vecPoint.push_back(VCTPoint3D());
		Read(pt.vecPoint.back(),(eType & eOGCGeometryZ)?true:false);
	}
	else
	{
		pt.FeatureType = VCT_POINT_GROUP;
		int n = ReadT<int>();
		pt.vecPoint.resize(n);
		for(int i =0;i<n;i++)
		{
			ReadT<char>();
			ReadT<int>();
			Read(pt.vecPoint[i],(eType & eOGCGeometryZ)?true:false);	
		}
	}
	return true;
}
void WKBReader::Read(VCTLineElement& line,VCT_LINE_GEOMETRY_TYPE eType,bool bHasZ)
{
	line.GeometryType = eType;
	switch(eType)
	{
		//1.0版本中的定义
	case VCT_LINE_SIMPLE://		=	1,		// 折线
	case VCT_LINE_DEFAULT:// = 11,				// 简单折线
		line.vecArcPoint.resize(ReadT<int>());
		break;
	case VCT_LINE_CIRCLEARC://	=	2,		// 三点圆弧
	case VCT_LINE_ARC:// = 12,					// 三点圆弧
		line.vecArcPoint.resize(2 * ReadT<int>() + 1);
		break;
	case VCT_LINE_CIRCLE://		=	3,		//三点圆
		line.vecArcPoint.resize(3);
		break;
	case VCT_LINE_ELLIPSE://	=	4,		//四点椭圆
	case VCT_LINE_SMOOTH://		=	5,		//光滑曲线
	case VCT_LINE_SPLINE://		=	6,		//样条曲线
	//2.0版本中的定义
	
	case VCT_LINE_ARC_CENTER:// = 13,			// 圆心弧	
	case VCT_LINE_ELLIPSE_ARC:// = 14,			// 椭圆弧	
	case VCT_LINE_SMOOTHLINE:// = 15,			// 三次样条曲线
	case VCT_LINE_BSPLINE:// = 16,				// B样条曲线
	case VCT_LINE_BEZIER:// = 17,				// Bezier曲线	
		break;
	}
	for(int i =0;i<line.vecArcPoint.size();i++)
	{
		Read(line.vecArcPoint[i],bHasZ);
	}
}
bool WKBReader::Read(VCTLine& line)
{
	line.FeatureType = VCT_LINE_DIRECT;
	OGCGeometryType eType = GeometryType();
	m_pCurrent+=5;
	bool bHasZ = (eType & eOGCGeometryZ)?true:false;
	if(bHasZ)
		eType = (OGCGeometryType)(eType - eOGCGeometryZ);
	switch(eType)
	{
	case eOGCLineString:
		
		line.vecLineData.push_back(VCTLineElement());
		Read(line.vecLineData.back(),VCT_LINE_DEFAULT,bHasZ);
		break;
	case eOGCMultiLineString:
		line.vecLineData.resize(ReadT<int>());
		for(int i =0;i<line.vecLineData.size();i++)
		{
			ReadT<char>(); //读取LineString的字节序
			ReadT<int>();//读取LineString的Geometry类型
			Read(line.vecLineData[i],VCT_LINE_DEFAULT,bHasZ); 
		}
		break;
	case eOGCArcString:
		line.vecLineData.push_back(VCTLineElement());
		Read(line.vecLineData.back(),VCT_LINE_ARC,bHasZ);
		break;
	case eOGCArc:
		break;
	case eOGCCircle:
		line.vecLineData.push_back(VCTLineElement());
		Read(line.vecLineData.back(),VCT_LINE_CIRCLE,bHasZ);
		break;
	}

	return !line.vecLineData.empty();
}
void WKBReader::Read(VCTPolygonElement& ele,int n,bool bHasZ)
{
	ele.GeoType = VCT_POLYGON_SIMPLE;
	ele.vecPoints.resize(n);
	for(int i =0;i<n;i++)
	{
		Read(ele.vecPoints[i],bHasZ);
	}
}
bool WKBReader::Read(VCTPolygon& polygon)
{
	polygon.FeatureType = VCT_POLYGON_DIRECT;
	OGCGeometryType eType = GeometryType();
	m_pCurrent+=5;
	bool bHasZ = (eType & eOGCGeometryZ)?true:false;
	if(bHasZ)
		eType = (OGCGeometryType)(eType - eOGCGeometryZ);
	switch(eType)
	{
	case eOGCPolygon:
		polygon.vecPolygonElement.resize(ReadT<int>());
		for(int i =0;i<polygon.vecPolygonElement.size();i++)
		{
			Read(polygon.vecPolygonElement[i],ReadT<int>(),bHasZ);
		}
		
		break;
	case eOGCMultiPolygon:
		{
			int n = ReadT<int>();
			for(int i = 0;i<n;i++)
			{
				int count = ReadT<int>();
				polygon.vecPolygonElement.reserve(polygon.vecPolygonElement.size() + count);
				for(int j =0;j< count;j++)
				{
					polygon.vecPolygonElement.push_back(VCTPolygonElement());
					ReadT<char>();//字节序
					ReadT<int>();//geometrytype
					Read(polygon.vecPolygonElement.back(),ReadT<int>(),bHasZ);
				}
			}
		}
		break;
	}

	return !polygon.vecPolygonElement.empty();
} 
WKBWriter::WKBWriter()
{
	m_nDim  =  2;
	m_eOrder = ByteOrder::OSByteOrderType();
	m_eOSOrder = ByteOrder::OSByteOrderType();
}
WKBWriter::WKBWriter(ByteOrderType eOrder,int nDim)
{
	m_nDim  =  nDim;
	m_eOrder = eOrder;
	m_eOSOrder = ByteOrder::OSByteOrderType();
}
WKBWriter::~WKBWriter()
{

}
void WKBWriter::Reset(ByteOrderType eOrder,int nDim)
{
	m_nDim  =  nDim;
	m_eOrder = eOrder; 
	m_Buffer.Allocate(0);
}
void WKBWriter::WriteByteOrder()
{
	char c = m_eOrder;
	m_Buffer.AppendT(c);
}
void WKBWriter::Write(void* val ,int nLen)
{
	m_Buffer.Append((unsigned char*)val,nLen);
}
void WKBWriter::Write(char val)
{
	Write(&val,1);
}
void WKBWriter::Write(short val)
{
	if(m_eOrder != m_eOSOrder)
		GeoStar::Utility::GsEndianConverter::SwapRef((unsigned short&)val);
	
	Write(&val,sizeof(val));
}
void WKBWriter::Write(int val)
{
	if(m_eOrder != m_eOSOrder)
		GeoStar::Utility::GsEndianConverter::SwapRef((unsigned int&)val);
	
	Write(&val,sizeof(val));

}
void WKBWriter::Write(__int64 val)
{
	if(m_eOrder != m_eOSOrder)
		GeoStar::Utility::GsEndianConverter::SwapRef((unsigned long long&)val);
	
	Write(&val,sizeof(val));
}
void WKBWriter::Write(float val)
{
	if(m_eOrder != m_eOSOrder)
		GeoStar::Utility::GsEndianConverter::SwapRef((unsigned int&)val);
	
	Write(&val,sizeof(val));
}
void WKBWriter::Write(double val)
{
	if(m_eOrder != m_eOSOrder)
		GeoStar::Utility::GsEndianConverter::SwapRef((unsigned long long&)val);
	
	Write(&val,sizeof(val));
}
void WKBWriter::Write(OGCGeometryType eType)
{
	if(m_nDim == 3)
		eType = (OGCGeometryType)(eType + OGCGeometryType::eOGCGeometryZ);
	Write((int)eType);
}
bool WKBWriter::Write(std::vector<VCTPoint3D>& vecArcPoint)
{
	std::vector<VCTPoint3D>::iterator it = vecArcPoint.begin();
	for(;it != vecArcPoint.end();it++)
	{
		Write(it->x);
		Write(it->y);
		if(m_nDim == 3)
			Write(it->z);
	}
	return true;
}
bool WKBWriter::Write(VCTPoint3D& pt)
{
	Write(pt.x);
	Write(pt.y);
	if(m_nDim == 3)
		Write(pt.z);
	return true;
}
bool WKBWriter::Write(VCTAnnotation& Ann)
{
	VCTPoint pt;
	
	std::vector<VCTAnnoPoint>::iterator it = Ann.vecAnnoPoint.begin();
	for(;it != Ann.vecAnnoPoint.end();it++)
	{
		pt.vecPoint.push_back(it->vctPoint3D);
	}
	if(pt.vecPoint.size() == 1)
		pt.FeatureType = VCT_POINT_DEFAULT;
	else
		pt.FeatureType = VCT_POINT_GROUP;

	return Write(pt);
}
bool WKBWriter::Write(VCTPoint& pt)
{
	if(pt.vecPoint.empty()) return false;
	WriteByteOrder();
	switch(pt.FeatureType)
	{
	case VCT_POINT_DEFAULT:// = 1,				// 独立点
		Write(eOGCPoint);
		Write(pt.vecPoint.front());
		break;
	case VCT_POINT_NODE:// = 2,					// 结点，结点包括纯结点和结点要素。规定纯结点的要素类型编码和层名为"Unknown"
	case VCT_POINT_DIRECTED:// = 3,				// 有向点
	case VCT_POINT_GROUP:// = 4,				// 点簇			仅在2.0版本中有
		Write(eOGCMultiPoint);
		//点数量
		Write((int)pt.vecPoint.size());
		for(std::vector<VCTPoint3D>::iterator it = pt.vecPoint.begin();
			it !=  pt.vecPoint.end();it++)
		{
			WriteByteOrder();
			Write(GeoStar::Kernel::GsOGCGeometryType::eOGCPoint);
			Write(*it);
		}
		break;
	}
	return true;
}

bool WKBWriter::Write(VCTLineElement& line)
{
	if(line.vecArcPoint.empty()) return false;

	WriteByteOrder();

	switch(line.GeometryType)
	{
		//1.0版本中的定义
	case VCT_LINE_SIMPLE://		=	1,		// 折线
	case VCT_LINE_DEFAULT:// = 11,				// 简单折线
		Write(eOGCLineString);
		Write((int)line.vecArcPoint.size());
		Write(line.vecArcPoint);
		break;
	case VCT_LINE_CIRCLEARC://	=	2,		// 三点圆弧
	case VCT_LINE_ARC:// = 12,					// 三点圆弧
		
		if(line.vecArcPoint.size() <3)
			line.vecArcPoint.resize(3);

		if(line.vecArcPoint.size() == 3)
		{
			Write(eOGCArc);
			Write(line.vecArcPoint);
		}
		else
		{
			Write(eOGCArcString);
			Write((int)(line.vecArcPoint.size() - 1) / 2 );
			Write(line.vecArcPoint);
		}
		break;
	case VCT_LINE_CIRCLE://		=	3,		//三点圆
		Write(eOGCCircle);
		if(line.vecArcPoint.size() != 3)
			line.vecArcPoint.resize(3);

		Write(line.vecArcPoint);
		break;
	case VCT_LINE_ELLIPSE://	=	4,		//四点椭圆
		return false;
		break;
	case VCT_LINE_SMOOTH://		=	5,		//光滑曲线
		return false;
		break;
	case VCT_LINE_SPLINE://		=	6,		//样条曲线
		return false;
	case VCT_LINE_ARC_CENTER:// = 13,			// 圆心弧	
	case VCT_LINE_ELLIPSE_ARC:// = 14,			// 椭圆弧	
	case VCT_LINE_SMOOTHLINE:// = 15,			// 三次样条曲线
	case VCT_LINE_BSPLINE:// = 16,				// B样条曲线
	case VCT_LINE_BEZIER:// = 17,				// Bezier曲线	
		return false;
		break;
	}
	return true;
}
 
OGCGeometryType LineGeometryType(std::vector<VCTLineElement>& vecLineData)
{
	std::vector<VCTLineElement>::iterator it = vecLineData.begin();
	for(;it != vecLineData.end();it++)
	{
		if(it->GeometryType != VCT_LINE_SIMPLE &&
			it->GeometryType != VCT_LINE_DEFAULT)
			return OGCGeometryType::eOGCGeometryCollection;
	}
	return OGCGeometryType::eOGCMultiLineString;
}
bool WKBWriter::Write(VCTLine& line)
{
	//直接线。
	if(VCT_LINE_DIRECT == line.FeatureType)
	{
		if(line.vecLineData.empty()) return false;
		if(line.vecLineData.size() == 1)
			return Write(line.vecLineData.front());
		OGCGeometryType eType = LineGeometryType(line.vecLineData);
		WriteByteOrder();
		Write(eType);
		Write((int)line.vecLineData.size());
		std::vector<VCTLineElement>::iterator it = line.vecLineData.begin();
		for(;it != line.vecLineData.end();it++)
		{
			Write(*it);
		}
	}
	return true;
}
bool WKBWriter::Write(VCTPolygonElement& ele)
{
	switch(ele.GeoType)
	{
		case VCT_POLYGON_SIMPLE:// = 11,                // 简单多边形
			WriteByteOrder();
			Write(eOGCPolygon);
			Write(int(1));
			Write((int)ele.vecPoints.size());
			Write(ele.vecPoints);
			break;
		case VCT_POLYGON_3POINTCIRCLE:// = 12,	        // 三点圆		
		case VCT_POLYGON_CIRCLE:// = 13,	            // 圆心圆		
		case VCT_POLYGON_ELLIPSE:// = 14,		        // 椭圆		
			break;
		break;

	}
	return true;
}
GeoStar::Kernel::GsPolygonPtr ToPolygon(VCTPolygon& polygon,int nDim)
{
	//这里就证明是多边形，需要考虑是Polygon还是MultiPolygon
	GeoStar::Kernel::GsPolygonPtr ptrPolygon = new GeoStar::Kernel::GsPolygon();
	ptrPolygon->CoordinateDimension(nDim);

	std::vector<VCTPolygonElement>::iterator it =  polygon.vecPolygonElement.begin();
	for(;it != polygon.vecPolygonElement.end();it++)
	{
		GeoStar::Kernel::GsRingPtr ptrRing = new GeoStar::Kernel::GsRing();
		ptrRing->CoordinateDimension(nDim);
		std::vector<VCTPoint3D>::iterator itp = it->vecPoints.begin();
		if(nDim == 2)
		{
			for(;itp != it->vecPoints.end();itp++)
			{
				ptrRing->Add(GeoStar::Kernel::GsRawPoint(itp->x,itp->y));
			}
		}
		else
		{
			for(;itp != it->vecPoints.end();itp++)
			{
				ptrRing->Add(GeoStar::Kernel::GsRawPoint3D(itp->x,itp->y,itp->z));
			}
		}
		ptrPolygon->Add(ptrRing);
	}
	return ptrPolygon;
}
bool WKBWriter::Write(VCTPolygon& polygon)
{
	//直接线。
	if(VCT_POLYGON_DIRECT == polygon.FeatureType)
	{
		if(polygon.vecPolygonElement.empty()) return false; 
		
		//对于一个边的普通多边形。
		if(polygon.vecPolygonElement.size() == 1) 
		{
			if(polygon.vecPolygonElement.front().GeoType == VCT_POLYGON_SIMPLE)
			{
				WriteByteOrder();
				Write(eOGCPolygon);
				Write(int(1));
				Write((int)polygon.vecPolygonElement.front().vecPoints.size());
				Write(polygon.vecPolygonElement.front().vecPoints);
				return true;
			}

			return Write(polygon.vecPolygonElement.front());
		}
		OGCGeometryType eType = eOGCMultiPolygon;
		//只要中间有一个元素不是简单线则认为是GeometryCollection
		std::vector<VCTPolygonElement>::iterator it = polygon.vecPolygonElement.begin();
		for(;it != polygon.vecPolygonElement.end();it++)
		{
			if(it->GeoType != VCT_POLYGON_SIMPLE)
			{
				eType = eOGCGeometryCollection;
				break;
			}
		}
		//如果是集合
		if(eType == eOGCGeometryCollection)
		{
			WriteByteOrder();
			Write(eType);
			Write(int(polygon.vecPolygonElement.size()));
			it = polygon.vecPolygonElement.begin();
			for(;it != polygon.vecPolygonElement.end();it++)
			{
				 Write(*it);
			}
			return true;
		}
		//转化为GeoStar的polygon用于分隔出单外圈的多边形。
		GeoStar::Kernel::GsPolygonPtr ptrPolygon = ToPolygon(polygon,m_nDim);
		ptrPolygon->Simplify();
		//外圈。
		GeoStar::Kernel::GsGeometryCollectionPtr ptrExt =  ptrPolygon->ExteriorRings();
		if(ptrExt->Count() >1)
		{
			WriteByteOrder();
			Write(eOGCMultiPolygon);
			Write(int(ptrExt->Count())); 
		}
		for(int i =0;i<ptrExt->Count();i++)
		{
			Write(GeoStar::Kernel::GsRingPtr(ptrExt->Geometry(i)),ptrPolygon);
		}
	}
	return false;
}
void WKBWriter::Write(int nLen,double* pCoord)
{
	for(int i =0;i<nLen;i+=m_nDim)
	{
		Write(pCoord[i]);
		Write(pCoord[i+1]);
		if(m_nDim == 3)
			Write(pCoord[i+2]);
	}
}
bool WKBWriter::Write(GeoStar::Kernel::GsRing* pExt,GeoStar::Kernel::GsPolygon* pPolygon)
{
	WriteByteOrder();
	Write(eOGCPolygon);
	
	GeoStar::Kernel::GsGeometryCollectionPtr ptrInter =  pPolygon->InteriorRings(pExt);

	//写入Polygon的数量
	Write(int(ptrInter->Count() + 1));
	Write(pExt->GeometryBlobPtr()->CoordinateLength(),pExt->GeometryBlobPtr()->Coordinate());

	for(int i =0;i<ptrInter->Count();i++)
	{
		GeoStar::Kernel::GsGeometryPtr ptrRing = ptrInter->Geometry(i);
		Write(ptrRing->GeometryBlobPtr()->CoordinateLength(),ptrRing->GeometryBlobPtr()->Coordinate());
	}
	return true;
}
GeoStar::Utility::GsGrowByteBuffer* WKBWriter::Buffer()
{
	return &m_Buffer;
}
