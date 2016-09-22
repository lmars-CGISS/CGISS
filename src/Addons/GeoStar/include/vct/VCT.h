#pragma once
#include <vector>
#include <string>
/// \brief VCT���ݽṹ���塣
typedef __int64 VCTID;

//��Чֵ
//�� double ���� float����ȡ FLT_MINʱ������Ϊ��ֵ��Ч
//�� long����ȡֵLONG_MINʱ��           ����Ϊ��ֵ��Ч
union ColorRef
{
	unsigned long Quad;
	unsigned char RGBA[4];
};

//�����
struct VCTPoint3D
{
	double x,y,z;	 // ��ֵȡFLT_MIN������Ϊ����Чֵ
	VCTPoint3D()
	{
		memset(this,0,sizeof(VCTPoint3D));
	}
};


//��������
enum VCT_GEOMETRY_TYPE
{	      
      VCT_POINT = 0, 						// ��״Ҫ��
	  VCT_LINE = 1, 						// ��״Ҫ��
	  VCT_POLYGON = 2,						// ��״Ҫ��
	  VCT_SOLID = 3,						// ��Ҫ��			
	  VCT_ANNOTATION = 5,					// ע��
	  VCT_AGGREGATION = 6,					// �ۺϵ���
	  VCT_GEOMETRY_UNSURPORTED = 99			// ��֧��
} ;


//�����ֶ�����
enum VCT_FIELD_TYPE
{
		VCT_CHAR = 0,						// �ַ���
		VCT_VARCHAR = 1,					// �䳤�ַ��ͣ�ת�������ݿ��Memo ��Blob�ֶ�����		
		VCT_SMALLINT = 2,					// ������,2���ֽڴ洢	int2
		VCT_INTEGER = 3,					// ����,4���ֽڴ洢		int4
		VCT_FLOAT = 4,						// ��������,4���ֽڴ洢
		VCT_DOUBLE = 5,						// ��������,8���ֽڴ洢
		VCT_NUMERIC = 6,					// ��������,�г��ȺͿ��
		VCT_BOOL = 7,						// ��������	1���ֽڴ洢����Ӧ������ֵӦΪ"1"��"0"
		VCT_DATE = 8,						// ��������	4���ֽڴ洢����ʾ��ʽӦΪYYYY-MO-DD
		VCT_TIME = 9,						// ʱ������	4���ֽڴ洢����ʾ��ʽӦΪMI:SS.SSS
		VCT_DATETIME = 10,					// ����ʱ������	8���ֽڴ洢����ʾ��ʽӦΪYYYY-MO-DD HH:MI:SS.SSS	
		VCT_VARBIN = 11,					// �ַ��ͣ������ı�������ʽ������,����ʽ�ݲ����������������ֶ�ֵ��ת����
											// �������ֶ�(���ý������)��ȡ����ļ�ת��,���ֶ���������¼"Varbin",�ֶ�ֵ����¼����ļ�·����
											// ת�������ݿ��Memo ��Blob�ֶ�����
											
		VCT_INT1 = 12,
		VCT_INT8 = 13,
								
		VCT_FIELD_UNEXPECTED = 99
};

//�ļ�ͷ
struct VCTHead
{
	std::string strDataMark;				         // ��ʽ��־
	float  fVersion;						 // �汾
	char   chUnit;				             // ���굥λ,K��ʾ����,M��ʾ��,D��ʾ�Զ�Ϊ��λ�ľ�γ��,
											 //S��ʾ�Զȷ����ʾ�ľ�γ��(��ʱ�����ʽΪDDDMMSS.SSSS, DDDΪ��, MMΪ��, SS.SSSSΪ��)
	int    nDim; 						     // ����ά��
	int    nTopo;							 // ����		
	char   chCoordSysType;					 // ����ϵ���ͣ�G��ʾ��������ϵ��M��ʾ��ѧ����ϵ��
	std::string strProjection;			         // ͶӰ����	
	std::string strSpheroid;			             // �ο�������	
    std::string strParameters;			         // ͶӰ����	
	double dfMinX, dfMinY, dfMinZ, 	         // ��Χ
	       dfMaxX, dfMaxY, dfMaxZ;	
	long nScaleM;							 // ������
	std::string strDate;				             // ����
	char chSeparator;						 // �����ֶηָ�����
	
	std::string strHorizontalCRS;			     // ƽ������ο�ϵͳ	
											 // ����ŷ��ʯ�Ϳ�̽��֯��European Petroleum Survey Group��EPSG����
											 // �����ȫ��ͳһ������ο�ϵͳ����
	std::string strVerticalCRS;					 // �̻߳�׼�����ַ���
	std::string strTimeRS;						 // ʱ��ο�ϵͳ
	std::string  strComment;                      // ע��
	
	//����VCT��ʽ��By ��Ծ����20060612
	double	dMeridian;						//���������߾��ȣ��Զ�Ϊ��λ
	double	dTaren;							//ͼ���������ֵ�����������������
		

	//GB/T17798-2007��By ��Ծ����20070315
	std::string strVersion;						//�汾
	std::string strCSType;						//����ϵ���͡�C��ʾ�ѿ�����Cartesian������ϵ��D��ʾ�������ϵ��P��ʾͶӰ����ϵ��
	std::string strXAxis;						//X�����᷽��
	std::string strYAxis;						//Y�����᷽��
	std::string strXYUnit;						//ƽ�����굥λ
	std::string strZUnit;						//�߳����굥λ
	std::string strPM;							//��������
	double dOffsetX,dOffsetY,dOffsetZ;		//����ƫ����
	VCTHead()
	{
		strDataMark ="CNSDTF-VCT";
		fVersion =1.0 ;        
		strVersion = "GB/T17798-2007";
		chUnit = 'M';

		nDim = 2;            
		nTopo = 0;

		chCoordSysType = 'M';
	
		strProjection = "";
		strSpheroid = "";
		strParameters = "";

		dfMinX = dfMinX = dfMinZ = DBL_MAX;
		dfMaxX = dfMaxX = dfMaxZ = 0 - DBL_MAX;
		dfMinX = dfMinY = dfMinZ = DBL_MAX;
		dfMaxX = dfMaxY = dfMaxZ = 0 - DBL_MAX;
		dfMinX = dfMinZ = dfMinZ = DBL_MAX;
		dfMaxX = dfMaxZ = dfMaxZ = 0 - DBL_MAX;
		nScaleM = 0;
		strDate = "";
		chSeparator = ',';    
	
		strHorizontalCRS = "";
		strVerticalCRS = "";					
		strTimeRS = "";							
	
		strComment = "";

		dMeridian = 0.0f;
		dTaren = 0.0f;

		strCSType = "C";
		strXAxis = "E";
		strYAxis = "N";
		strXYUnit = "M";
		strZUnit = "M";
		strPM = "Greenwich";
		dOffsetX = dOffsetY = dOffsetZ = 0.0f;
	}
};


//Ҫ�����Ͳ���
struct VCTFeatureCode
{
    std::string strUserID;						// Ҫ�����ͱ���
	std::string strName;					        // Ҫ����������
    VCT_GEOMETRY_TYPE GeometryType;	        // ��������
	ColorRef   ulColor;					    // ȱʡ��ɫ
    std::string strAttributeTableName;			// ���Ա���
	std::string strUserItem;			// �û��,zjq,20070920
};


//�ֶ�����
struct  VCTField
{
	 std::string strFieldName;			   	    // �������
	 VCT_FIELD_TYPE FieldType;		    	// �ֶ�����
	 int  nWidth;							// ���
	 int  nPrecision;						// ����
	 VCTField()
	 {
		 nWidth = 0;
		 nPrecision = 0;
	 }
	 VCTField(const char* name,VCT_FIELD_TYPE t)
	 {
		 strFieldName = name;
		 FieldType = t;
		 nWidth = 0;
		 nPrecision = 0;
	 }
	 VCTField(const char* name,VCT_FIELD_TYPE t,int w,int p)
	 {
		 strFieldName = name;
		 FieldType = t;
		 nWidth = w;
		 nPrecision = p;
	 }

};

typedef std::vector<VCTField> VCTFields;

//�������ݽṹ
struct VCTTableStructure
{
     std::string   strTableName;	               // ���Ա���
 	 int      nFieldnum;			       // ����헸���
	 bool	  bGeometry;				   // �Ƿ��м������ݹ���	
	 VCTFields vecFields;			       // �ֶ�����
};

//Ҫ�ص�ͷ��Ϣ
struct VCTObjectHeader
{
	VCTID   nObjID;					    	// Ŀ���ʶ��
	std::string strUserID;				    	// Ҫ�����ͱ���
	std::string strStyle;//strLayerName;         // ����,��2.0���Ѹ�Ϊͼ�α��ֱ���
	
	bool bValid;							//�����Ƿ���Ч
};

//��״Ҫ������
enum VCT_POINT_TYPE
{
		VCT_POINT_DEFAULT = 1,				// ������
		VCT_POINT_NODE = 2,					// ��㣬�����������ͽ��Ҫ�ء��涨������Ҫ�����ͱ���Ͳ���Ϊ"Unknown"
		VCT_POINT_DIRECTED = 3,				// �����
		VCT_POINT_GROUP = 4,				// ���			����2.0�汾����
};

//��״Ҫ��
struct VCTPoint
{
	VCTObjectHeader ObjHeader;		    	// Ҫ�ص�ͷ��Ϣ
	VCT_POINT_TYPE FeatureType;			    // ��������
	std::vector<VCTPoint3D> vecPoint;	        // ������,�����ʱ����������
	//���½���1.0�汾����
	int nLineNum;						    // �����ߵĸ���	
	std::vector<VCTID> vecLineOID;			    // �����ߵı�ʶ��	
};

// ��״Ҫ���������� ,������ֱ�����껹�Ǽ��
enum VCT_LINE_FEATURE_TYPE
{
	VCT_LINE_DIRECT = 1,	   	          // ֱ��������
	VCT_LINE_INDIRECT = 100	,	          // ���������

};

 
//   ��״Ҫ�ؼ�����״
enum   VCT_LINE_GEOMETRY_TYPE
{
	//1.0�汾�еĶ���
	VCT_LINE_SIMPLE		=	1,		// ����
	VCT_LINE_CIRCLEARC	=	2,		// ����Բ��
	VCT_LINE_CIRCLE		=	3,		//����Բ
	VCT_LINE_ELLIPSE	=	4,		//�ĵ���Բ
	VCT_LINE_SMOOTH		=	5,		//�⻬����
	VCT_LINE_SPLINE		=	6,		//��������
	//2.0�汾�еĶ���
	VCT_LINE_DEFAULT = 11,				// ������
	VCT_LINE_ARC = 12,					// ����Բ��
	VCT_LINE_ARC_CENTER = 13,			// Բ�Ļ�	
	VCT_LINE_ELLIPSE_ARC = 14,			// ��Բ��	
	VCT_LINE_SMOOTHLINE = 15,			// ������������
	VCT_LINE_BSPLINE = 16,				// B��������
	VCT_LINE_BEZIER = 17,				// Bezier����	
		
};

//�������ߵĽڵ�
struct VCTKnot
{
	double dfPara;							// ����ֵ
	int    nOrder;							// ����
	double dfWeight;						// Ȩֵ
};


struct VCTLineElement
{
  	VCT_LINE_GEOMETRY_TYPE  GeometryType;  // ������״
	std::vector<VCTPoint3D> vecArcPoint;        // ����ߵ�����(������,����Բ��),��������vecArcPoint.size()	
	double dfStartAngle;				   // ��ʼ��(Բ�Ļ�,��Բ��)
	double dfEndAngle;					   // ��ֹ��(Բ�Ļ�,��Բ��)
	union
	{
		double dfRatio;					  // ��Բ�̰����볤����ı���
	    double dfRadius;				  // �뾶(Բ�Ļ�)
	    int    nDegree;					  // �������ߵĽ���
    };
	std::vector<VCTKnot> vecKnot;               // �������ߵĽڵ�����,�ڵ��������vecKnot.size()
	
};


//��״Ҫ��
struct VCTLine
{
	VCTObjectHeader  ObjHeader;	           // Ҫ�ص�ͷ��Ϣ
    VCT_LINE_FEATURE_TYPE  FeatureType;    // ��������,

	// ֱ������ϵ�õ���                     
	std::vector<VCTLineElement>   vecLineData;  // �洢����������ݣ��߶εĸ������Ծ���vecLineData.size()

	// �������ϵ�õ���
	std::vector<VCTID> vecArcID;				   // ��������е���Ŀ��ı�ʶ��(�������),
	                                       // �߶εĸ������Ծ���vecArcID.size()
    //���½���1.0�汾��
	VCTID nFNode;						//��ڵ�	
	VCTID nTNode;						//�սڵ�	
	VCTID nLPolygon;						//������	
	VCTID nRPolygon;						//�Ҷ����	
};

// �����������
enum  VCT_POLYGON_FEATURE_TYPE
{
	VCT_POLYGON_DIRECT = 1,             // ֱ������
	VCT_POLYGON_INDIRECT = 100,           // �������

};


//  �����Ĺ�������
enum VCT_POLYGON_INDIRECT_TYPE
{
   VCT_POLYGON_INDIRECT_SUB_LINE = 21,       // �������߶��󹹳ɵ���

   VCT_POLYGON_INDIRECT_SUB_POLYGON = 22,    // ����������󹹳ɵ���

};


// ֱ����ļ�������
enum VCT_POLYGON_GEOMETRY_TYPE
{
	VCT_POLYGON_SIMPLE = 11,                // �򵥶����
	VCT_POLYGON_3POINTCIRCLE = 12,	        // ����Բ		
	VCT_POLYGON_CIRCLE = 13,	            // Բ��Բ		
	VCT_POLYGON_ELLIPSE = 14,		        // ��Բ			
 	
};


//  ֱ�������¸��ּ���ͼ�ε����ݳ�Ա
struct VCTPolygonElement
 {
	VCT_POLYGON_GEOMETRY_TYPE  GeoType;    // ��ļ�����״                       
	std::vector<VCTPoint3D>  vecPoints;         // ��Ȧ�����괮,��Ȧ�ĵ�������vecPoints.size()
	union
	{
		double	dfRadius;				   // Բ��Բ �뾶	
	    double	dfRatio;				   // ��Բ �̰��᳤���볤����ı���
	};
};


//  �����Ľṹ
struct VCTPolygonIndirect
{ 
	VCT_POLYGON_INDIRECT_TYPE IndirectType; // �����Ĺ�������
	std::vector<VCTID> vecnSubOID;               // �Ӷ����ʶ�ţ��Ӷ������������vecnSubOID.size()
};


//  ��״Ҫ��
struct VCTPolygon
{   
	// ֱ�Ӽ�Ӷ�Ҫ�õ�������
	VCTObjectHeader ObjHeader;				// Ҫ�ص�ͷ��Ϣ
	VCT_POLYGON_FEATURE_TYPE FeatureType;	// ��������: �Ǽ�����껹��ֱ������
	VCTPoint3D LabPoint;					// ��ʶ������
    
	// ֱ�������õ��Ķ���
	std::vector<VCTPolygonElement> vecPolygonElement; // �����Ԫ��,Ȧ������vecPolygonElement.size()
	
	// ��������õ��Ķ���
	VCTPolygonIndirect  PolygonIndrect;  
};

//��Ҫ������	����2.0�汾����
enum  VCT_SOLID_TYPE
{
	VCT_SOLID_DIRECT = 1 ,                // ֱ������
	VCT_SOLID_INDIRECT = 100,	              // �������(��Ŀ�깹��)
};


// ֱ����������Ҫ�صļ�����״��ʶ
enum VCT_SOLID_GEOMETRY_TYPE
{
	VCT_SOLID_FOUR_POLGON = 11,            // ������
	VCT_SOLID_CUBOID = 12,                 // ������
	VCT_SOLID_ROTATE = 13,                 // ��ת��
    
};

// ֱ������ϵ��һ����Ԫ�صĽṹ
struct VCTSolidElement
{
   	VCT_SOLID_GEOMETRY_TYPE   GeoType;     // ����ͼ������ 
	std::vector< VCTPoint3D > vecPoints;        // ������, ����,������\������ĵ�������vecPoints.size()
	VCTPolygonElement PolygonElement;      // ��״����
};


//��Ҫ�� ����2.0�汾����
struct VCTSolid
{
	VCTObjectHeader ObjHeader;			  // Ҫ�ص�ͷ��Ϣ
	VCT_SOLID_TYPE   FeatureType;		  // ��������
    VCTPoint3D LabPoibt;                  // ��ʶ��	
    
	//  ֱ�������õ��Ķ���
	std::vector<VCTSolidElement> vecSolidElement; // ֱ����������ĸ�������vecSolidElement.size()

	//  ��������õ��Ķ���
	int nSubType;
	std::vector<VCTID> vecSubOid;        		    // ��Ŀ��ı�ʶ�� ,�����������Ŀ������vecSubOid.size()    
};



//����Ŀ��Ҫ��	����2.0�汾����
struct VCTAggregation
{
	VCTObjectHeader ObjHeader;			  // Ҫ�ص�ͷ��Ϣ
	
    std::vector<VCTID> vecSubOid;             // ��Ŀ��ı�ʶ��,��Ŀ����������vecSubOid.size()
};

//ע��Ҫ������ 
enum VCT_ANNO_TYPE
{
	VCT_ANNO_SINGLE = 1,			    // ����ע��
	VCT_ANNO_MULTIPLE = 2,		        // ���ע��
};

// ע�ǵ�ṹ
struct VCTAnnoPoint
{
	VCTPoint3D vctPoint3D;             // �����
	float      fShiftDegree;           // ��ת��
	VCTAnnoPoint()
	{
		fShiftDegree = 0;
	}
};

//ע��Ҫ��
struct VCTAnnotation
{
    VCTObjectHeader ObjHeader;  	   // Ҫ�ص�ͷ��Ϣ
	VCT_ANNO_TYPE   FeatureType;	   // ��������
	std::string     strText;                // ע������
	
	std::vector<VCTAnnoPoint> vecAnnoPoint; // ע�������

	//������1.0�汾���У���2.0�汾��û�У�������ʽ�б�ʾ��
	std::string  strFontName;						//����
	ColorRef ulColor;							//��ɫ
	//���� 
	int  nWeight;							//����,0��1000������,��ʾ�����߻��Ĵ�ϸ�̶ȡ���400����������,700���������
	int  nType;								//��״,0��������,1������б,2������б,3��������,4��������
	bool bUnderline;						//�»���,1�������»���,0����û���»���
	//��С
	bool bSizeNumber;						//�Ƿ����ֺű�ʾ�ֵĴ�С
	double dfSizeNumber;					//�ֺ�
	double dfTextWidth;						//�ֿ�,ʵ�����곤�ȵ�λ
	double dfTextHeight;					//�ָ�,ʵ�����곤�ȵ�λ
	//���
	double dfSpace;							//���,ʵ�����곤�ȵ�λ
	//��������2.0�汾��ʽ�������ӵ�
	bool   bHorizon;						//���Ż�����,1�������,0��������(���Ե���ע��)
	int  nDeleteline;						//ɾ����,0����û��ɾ����,1�����е�ɾ����,	2������˫ɾ����
	bool bShadow;							//��Ӱ,1��������Ӱ,0����û����Ӱ
	bool bHole;								//����,1�����п���,0����û�п���
	std::string strAlign;						//���뷽ʽ,LB��������,LC��������,LT��������,CT��������,RT��������,
											//RC��������,RB��������,CB��������, CC��������(���Ե���ע��)
	//��ʼ��
	VCTAnnotation()
	{
		FeatureType = VCT_ANNO_SINGLE;
		strText = "";
		vecAnnoPoint.clear();
		strFontName = "";
		ulColor.Quad = 0;
		nWeight = 400;
		nType = 0;
		bHole = 0;
		bHorizon = 1;
		bShadow = 0;
		bSizeNumber = 0;
		dfSizeNumber = 0;
		bUnderline = 0;
		dfTextWidth = 0;
		dfTextHeight = 0;
		dfSpace = 0;
		nDeleteline = 0;
		strAlign = "LB";
	}
};


//������	����2.0�汾����	
struct VCTNodeTopo
{
	long nObjID;					        // �ڵ����ı�ʶ��
    std::vector<VCTID> vecSubOid;		        	// ������Ŀ��ı�ʶ��,������Ŀ����������vecSubOid.size()
	bool bValid;
};


//������	����2.0�汾����
struct VCTEdgeTopo
{
	VCTID nObjID;							 // Ŀ���ʶ��
	VCTID nFNodeID;						     // ͷ�ڵ�	
	VCTID nTNodeID;							 // β�ڵ�	
	VCTID nLPolygonID;						 // ������	
	VCTID nRPolygonID;						 // �Ҷ����
	
	bool bValid;
};


// ���Ա��е�һ������
struct VCTAttributeRow
{
	VCTID              nOID;                   // �����ʶ�ţ�λ��ÿһ�еĿ�ʼλ��
	std::vector<std::string>    vecstrFieldValues;      // ����ҳ�������ζ�����ֶ�ֵ
};

struct VCTAttributeTable
{
	std::string                  strTableName;   // ���Ա���
	std::vector<VCTAttributeRow> vecRows;		// ���Ա�ĵ�����
};	


struct VCTVarchar
{
	VCTID nObjID;
	std::string strText;
};

//��ʽ	����2.0�汾����
struct VCTDefaultStyle
{
	int lColor;
	int lForeColor;
	int lBackColor;
	int	 nSymbolID;
	double dPointSize;
	double dLineWidth;
	VCTID  nLineStyleID;
	VCTID nPatternID;
	std::string strFont;
	double dAnnoHeight;
	double dAnnoWidth;
	double dAnnoSpace;
	int nAnnoWeight;
	int nAnnoStyle;
	int bAnnoUnderline;
	int bAnnoStrike;
	int bAnnoShadow;
	int bAnnoHole;
	std::string strAnnoAlignment;
	int bAnnoHorizontal;
	int bAnnoTransparent;
	VCTDefaultStyle()
	{
		lColor = 0;
		lForeColor = 0;
		lBackColor = 0;
		nSymbolID = 0;
		dPointSize = 0;
		dLineWidth = 0;
		nLineStyleID = 0;
		nPatternID = 0;
		dAnnoHeight = 0;
		dAnnoWidth = 0;
		dAnnoSpace = 0;
		nAnnoWeight = 0;
		nAnnoStyle = 0;
		bAnnoUnderline = 0;
		bAnnoStrike = 0;
		bAnnoShadow = 0;
		bAnnoHole = 0;
		bAnnoHorizontal = 0;
		bAnnoTransparent = 0;
	};
};

struct VCTConstant
{
	std::string strKey;
	std::string strValue;
};

typedef std::vector<VCTConstant> VCTConstantVector;

struct VCTPairEx
{
	std::string strKey;
	std::string strValue;
	std::vector<std::string> strVecAlias;
};
struct VCTRelationTable
{
	std::string strTableID;
	std::vector<VCTPairEx>	vecRelationPairs;
};

struct VCTStyle
{
	std::string strID;
	std::vector<VCTPairEx>	vecPairs;
};


//����
enum VCT_ERROR_ID
{
	VCT_ERROR_OPENFILE			=	0x00,			// ���ļ�ʧ��
	VCT_ERROR_CREATEFILE		=	0x01,			// �����ļ�ʧ��
	VCT_ERROR_CREATETEMPFILE	=	0x02,			// ������ʱ�ļ�ʧ��
	VCT_ERROR_DATA				=	0x03,			// ���ݴ���
	VCT_ERROR_EXCEPTION			=	0x20,			// �쳣
};

