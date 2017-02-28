#pragma once
#include <VCTRW.h>

//用于VCT到WKB的转换以及WKB到VCT的转换
enum ByteOrderType
{
	eBigEndian = 0,		//高字节序
	eLittleEndian = 1,	//低字节序。
	eXDR = eBigEndian,
	eNDR = eLittleEndian,
};

/// \brief OGC规定的几何类型。
enum OGCGeometryType
{
	eOGCGeometry,// 0 
	eOGCPoint,// 1 
	eOGCLineString,// 2 
	eOGCPolygon,// 3 
	eOGCMultiPoint,// 4 
	eOGCMultiLineString,// 5 
	eOGCMultiPolygon,// 6 
	eOGCGeometryCollection,// 7 
	eOGCCircularString,// 8 
	eOGCCompoundCurve,// 9 
	eOGCCurvePolygon,// 10 
	eOGCMultiCurve,// 11 
	eOGCMultiSurface,// 12 
	eOGCCurve,// 13 
	eOGCSurface,// 14 
	eOGCPolyhedralSurface,// 15 
	eOGCTIN,// 16 
	
	///扩展类型
	eOGCArcString = 31,//三点圆弧串
	eOGCArc = 32,		//三点圆弧
	eOGCCircle = 33,		//三点圆
	eOGCArcStringByBulge= 34,		//由控制点和凸度表示的圆弧串
	eOGCArcByBulge= 35,		//由控制点和凸度表示的圆弧
	eOGCBSPLineCurve= 36,		//B样条曲线
	eOGCBezier = 37,		//贝塞尔曲线
	eOGCEnvelope = 41,		//矩形

	eOGCGeometryZ =1000 ,
	eOGCPointZ,//  1001 
	eOGCLineStringZ,//  1002 
	eOGCPolygonZ,//  1003 
	eOGCMultiPointZ,//  1004 
	eOGCMultiLineStringZ,//  1005 
	eOGCMultiPolygonZ,//  1006 
	eOGCGeometryCollectionZ,//  1007 
	eOGCCircularStringZ,//  1008 
	eOGCCompoundCurveZ,//  1009 
	eOGCCurvePolygonZ,//  1010 
	eOGCMultiCurveZ,//  1011 
	eOGCMultiSurfaceZ,//  1012 
	eOGCCurveZ,//  1013 
	eOGCSurfaceZ,//  1014 
	eOGCPolyhedralSurfaceZ,//  1015 
	eOGCTINZ,//  1016

	///扩展类型
	eOGCArcStringZ = 1031,//三点圆弧串
	eOGCArcZ = 1032,		//三点圆弧
	eOGCCircleZ = 1033,		//三点圆
	eOGCArcStringByBulgeZ= 1034,		//由控制点和凸度表示的圆弧串
	eOGCArcByBulgeZ= 1035,		//由控制点和凸度表示的圆弧
	eOGCBSPLineCurveZ= 1036,		//B样条曲线
	eOGCBezierZ = 1037,		//贝塞尔曲线 
	eOGCEnvelopeZ = 1041,		//矩形

};


//字节序辅助类。
class ByteOrder
{
public:
	//当前操作系统的字节序类型。
	static ByteOrderType OSByteOrderType(); 
	
};

//用于将WKB解析为VCT对象格式。
class WKBReader
{
	const unsigned char* m_pStart;
	const unsigned char* m_pEnd;
	const unsigned char* m_pCurrent;
	ByteOrderType m_Order;
	ByteOrderType m_OSOrder;
	void Read(VCTPoint3D& pt,bool bZ); 
	template<class T>
	T ReadT()
	{
		T val;
		int l = sizeof(T);
		memcpy(&val,m_pCurrent,l);
		if(l > 1 && m_OSOrder != m_Order) GeoStar::Utility::GsEndianConverter::SwapRefT(val);
		m_pCurrent+=l;
		return val;
	}
	void Read(VCTPolygonElement& ele,int n,bool bHasZ);
	void Read(VCTLineElement& line,VCT_LINE_GEOMETRY_TYPE eType,bool bHasZ);
public:
	WKBReader(void);
	~WKBReader(void);
	void Begin(const unsigned char* pBlob,int nSize);
	OGCGeometryType GeometryType(bool bSimple = false);
	
	bool Read(VCTPoint& pt);
	bool Read(VCTLine& line);
	bool Read(VCTPolygon& polygon); 
	
};

//用于VCT对象格式写成WKB格式。
class WKBWriter
{
	GeoStar::Utility::GsGrowByteBuffer m_Buffer;
	ByteOrderType m_eOrder;
	ByteOrderType m_eOSOrder;
	int				m_nDim;
	void WriteByteOrder();
	void Write(void* val ,int nLen);
	void Write(char val);
	void Write(short val);
	void Write(int val);
	void Write(__int64 val);
	void Write(float val);
	void Write(double val);
	void Write(OGCGeometryType eType);

	bool Write(VCTPoint3D& pt);
	bool Write(std::vector<VCTPoint3D>& vecArcPoint);
	void Write(int nLen,double* pCoord);
	bool Write(VCTLineElement& line);
	bool Write(VCTPolygonElement& ele);
	bool Write(GeoStar::Kernel::GsRing* pExt,GeoStar::Kernel::GsPolygon* pPolygon);
public:
	WKBWriter();
	WKBWriter(ByteOrderType eOrder,int nDim=2);
	~WKBWriter();
	void Reset(ByteOrderType eOrder,int nDim=2);
	bool Write(VCTPoint& pt);
	bool Write(VCTLine& line);
	bool Write(VCTPolygon& polygon);
	bool Write(VCTAnnotation& Ann);
	
	GeoStar::Utility::GsGrowByteBuffer* Buffer();

};

