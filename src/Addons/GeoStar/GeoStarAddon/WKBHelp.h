#pragma once
#include <VCTRW.h>

//����VCT��WKB��ת���Լ�WKB��VCT��ת��
enum ByteOrderType
{
	eBigEndian = 0,		//���ֽ���
	eLittleEndian = 1,	//���ֽ���
	eXDR = eBigEndian,
	eNDR = eLittleEndian,
};

/// \brief OGC�涨�ļ������͡�
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
	
	///��չ����
	eOGCArcString = 31,//����Բ����
	eOGCArc = 32,		//����Բ��
	eOGCCircle = 33,		//����Բ
	eOGCArcStringByBulge= 34,		//�ɿ��Ƶ��͹�ȱ�ʾ��Բ����
	eOGCArcByBulge= 35,		//�ɿ��Ƶ��͹�ȱ�ʾ��Բ��
	eOGCBSPLineCurve= 36,		//B��������
	eOGCBezier = 37,		//����������
	eOGCEnvelope = 41,		//����

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

	///��չ����
	eOGCArcStringZ = 1031,//����Բ����
	eOGCArcZ = 1032,		//����Բ��
	eOGCCircleZ = 1033,		//����Բ
	eOGCArcStringByBulgeZ= 1034,		//�ɿ��Ƶ��͹�ȱ�ʾ��Բ����
	eOGCArcByBulgeZ= 1035,		//�ɿ��Ƶ��͹�ȱ�ʾ��Բ��
	eOGCBSPLineCurveZ= 1036,		//B��������
	eOGCBezierZ = 1037,		//���������� 
	eOGCEnvelopeZ = 1041,		//����

};


//�ֽ������ࡣ
class ByteOrder
{
public:
	//��ǰ����ϵͳ���ֽ������͡�
	static ByteOrderType OSByteOrderType(); 
	
};

//���ڽ�WKB����ΪVCT�����ʽ��
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

//����VCT�����ʽд��WKB��ʽ��
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

