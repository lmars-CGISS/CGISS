#pragma once
#include <vector>
#include <string>
/// \brief VCT数据结构定义。
typedef __int64 VCTID;

//无效值
//当 double 或者 float类型取 FLT_MIN时，则认为其值无效
//当 long类型取值LONG_MIN时，           则认为其值无效
union ColorRef
{
	unsigned long Quad;
	unsigned char RGBA[4];
};

//坐标点
struct VCTPoint3D
{
	double x,y,z;	 // 当值取FLT_MIN，则认为是无效值
	VCTPoint3D()
	{
		memset(this,0,sizeof(VCTPoint3D));
	}
};


//几何类型
enum VCT_GEOMETRY_TYPE
{	      
      VCT_POINT = 0, 						// 点状要素
	  VCT_LINE = 1, 						// 线状要素
	  VCT_POLYGON = 2,						// 面状要素
	  VCT_SOLID = 3,						// 体要素			
	  VCT_ANNOTATION = 5,					// 注记
	  VCT_AGGREGATION = 6,					// 聚合地物
	  VCT_GEOMETRY_UNSURPORTED = 99			// 不支持
} ;


//属性字段类型
enum VCT_FIELD_TYPE
{
		VCT_CHAR = 0,						// 字符型
		VCT_VARCHAR = 1,					// 变长字符型，转换成数据库的Memo 或Blob字段类型		
		VCT_SMALLINT = 2,					// 短整型,2个字节存储	int2
		VCT_INTEGER = 3,					// 整型,4个字节存储		int4
		VCT_FLOAT = 4,						// 浮点数型,4个字节存储
		VCT_DOUBLE = 5,						// 浮点数型,8个字节存储
		VCT_NUMERIC = 6,					// 浮点数型,有长度和宽度
		VCT_BOOL = 7,						// 布尔类型	1个字节存储，相应的属性值应为"1"或"0"
		VCT_DATE = 8,						// 日期类型	4个字节存储，显示格式应为YYYY-MO-DD
		VCT_TIME = 9,						// 时间类型	4个字节存储，显示格式应为MI:SS.SSS
		VCT_DATETIME = 10,					// 日期时间类型	8个字节存储，显示格式应为YYYY-MO-DD HH:MI:SS.SSS	
		VCT_VARBIN = 11,					// 字符型，由于文本交换格式的限制,本格式暂不包含二进制类型字段值的转换。
											// 二进制字段(如多媒体数据)采取外挂文件转换,在字段描述处记录"Varbin",字段值处记录外挂文件路径。
											// 转换成数据库的Memo 或Blob字段类型
											
		VCT_INT1 = 12,
		VCT_INT8 = 13,
								
		VCT_FIELD_UNEXPECTED = 99
};

//文件头
struct VCTHead
{
	std::string strDataMark;				         // 格式标志
	float  fVersion;						 // 版本
	char   chUnit;				             // 坐标单位,K表示公里,M表示米,D表示以度为单位的经纬度,
											 //S表示以度分秒表示的经纬度(此时坐标格式为DDDMMSS.SSSS, DDD为度, MM为分, SS.SSSS为秒)
	int    nDim; 						     // 坐标维数
	int    nTopo;							 // 拓扑		
	char   chCoordSysType;					 // 坐标系类型，G表示测量坐标系、M表示数学坐标系。
	std::string strProjection;			         // 投影类型	
	std::string strSpheroid;			             // 参考椭球体	
    std::string strParameters;			         // 投影参数	
	double dfMinX, dfMinY, dfMinZ, 	         // 范围
	       dfMaxX, dfMaxY, dfMaxZ;	
	long nScaleM;							 // 比例尺
	std::string strDate;				             // 日期
	char chSeparator;						 // 属性字段分隔符号
	
	std::string strHorizontalCRS;			     // 平面坐标参考系统	
											 // 引用欧洲石油勘探组织（European Petroleum Survey Group（EPSG））
											 // 定义的全球统一的坐标参考系统名称
	std::string strVerticalCRS;					 // 高程基准描述字符串
	std::string strTimeRS;						 // 时间参考系统
	std::string  strComment;                      // 注释
	
	//国土VCT格式，By 邓跃进，20060612
	double	dMeridian;						//中央子午线经度，以度为单位
	double	dTaren;							//图幅理论面积值，或行政区控制面积
		

	//GB/T17798-2007，By 邓跃进，20070315
	std::string strVersion;						//版本
	std::string strCSType;						//坐标系类型。C表示笛卡儿（Cartesian）坐标系、D表示大地坐标系，P表示投影坐标系。
	std::string strXAxis;						//X坐标轴方向。
	std::string strYAxis;						//Y坐标轴方向。
	std::string strXYUnit;						//平面坐标单位
	std::string strZUnit;						//高程坐标单位
	std::string strPM;							//首子午线
	double dOffsetX,dOffsetY,dOffsetZ;		//坐标偏移量
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


//要素类型参数
struct VCTFeatureCode
{
    std::string strUserID;						// 要素类型编码
	std::string strName;					        // 要素类型名称
    VCT_GEOMETRY_TYPE GeometryType;	        // 几何类型
	ColorRef   ulColor;					    // 缺省颜色
    std::string strAttributeTableName;			// 属性表名
	std::string strUserItem;			// 用户項,zjq,20070920
};


//字段描述
struct  VCTField
{
	 std::string strFieldName;			   	    // 属性項名
	 VCT_FIELD_TYPE FieldType;		    	// 字段类型
	 int  nWidth;							// 宽度
	 int  nPrecision;						// 精度
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

//属性数据结构
struct VCTTableStructure
{
     std::string   strTableName;	               // 属性表名
 	 int      nFieldnum;			       // 属性項个数
	 bool	  bGeometry;				   // 是否有几何数据关联	
	 VCTFields vecFields;			       // 字段描述
};

//要素的头信息
struct VCTObjectHeader
{
	VCTID   nObjID;					    	// 目标标识号
	std::string strUserID;				    	// 要素类型编码
	std::string strStyle;//strLayerName;         // 层名,在2.0中已改为图形表现编码
	
	bool bValid;							//对象是否有效
};

//点状要素类型
enum VCT_POINT_TYPE
{
		VCT_POINT_DEFAULT = 1,				// 独立点
		VCT_POINT_NODE = 2,					// 结点，结点包括纯结点和结点要素。规定纯结点的要素类型编码和层名为"Unknown"
		VCT_POINT_DIRECTED = 3,				// 有向点
		VCT_POINT_GROUP = 4,				// 点簇			仅在2.0版本中有
};

//点状要素
struct VCTPoint
{
	VCTObjectHeader ObjHeader;		    	// 要素的头信息
	VCT_POINT_TYPE FeatureType;			    // 特征类型
	std::vector<VCTPoint3D> vecPoint;	        // 点坐标,有向点时有两对坐标
	//以下仅在1.0版本中有
	int nLineNum;						    // 关联线的个数	
	std::vector<VCTID> vecLineOID;			    // 关联线的标识码	
};

// 线状要素特征类型 ,表明是直接坐标还是间接
enum VCT_LINE_FEATURE_TYPE
{
	VCT_LINE_DIRECT = 1,	   	          // 直接坐标线
	VCT_LINE_INDIRECT = 100	,	          // 间接坐标线

};

 
//   线状要素几何形状
enum   VCT_LINE_GEOMETRY_TYPE
{
	//1.0版本中的定义
	VCT_LINE_SIMPLE		=	1,		// 折线
	VCT_LINE_CIRCLEARC	=	2,		// 三点圆弧
	VCT_LINE_CIRCLE		=	3,		//三点圆
	VCT_LINE_ELLIPSE	=	4,		//四点椭圆
	VCT_LINE_SMOOTH		=	5,		//光滑曲线
	VCT_LINE_SPLINE		=	6,		//样条曲线
	//2.0版本中的定义
	VCT_LINE_DEFAULT = 11,				// 简单折线
	VCT_LINE_ARC = 12,					// 三点圆弧
	VCT_LINE_ARC_CENTER = 13,			// 圆心弧	
	VCT_LINE_ELLIPSE_ARC = 14,			// 椭圆弧	
	VCT_LINE_SMOOTHLINE = 15,			// 三次样条曲线
	VCT_LINE_BSPLINE = 16,				// B样条曲线
	VCT_LINE_BEZIER = 17,				// Bezier曲线	
		
};

//样条曲线的节点
struct VCTKnot
{
	double dfPara;							// 参数值
	int    nOrder;							// 阶数
	double dfWeight;						// 权值
};


struct VCTLineElement
{
  	VCT_LINE_GEOMETRY_TYPE  GeometryType;  // 几何形状
	std::vector<VCTPoint3D> vecArcPoint;        // 组成线的坐标(简单折线,三点圆弧),点数就是vecArcPoint.size()	
	double dfStartAngle;				   // 起始角(圆心弧,椭圆弧)
	double dfEndAngle;					   // 终止角(圆心弧,椭圆弧)
	union
	{
		double dfRatio;					  // 椭圆短半轴与长半轴的比率
	    double dfRadius;				  // 半径(圆心弧)
	    int    nDegree;					  // 样条曲线的阶数
    };
	std::vector<VCTKnot> vecKnot;               // 样条曲线的节点数组,节点个数就是vecKnot.size()
	
};


//线状要素
struct VCTLine
{
	VCTObjectHeader  ObjHeader;	           // 要素的头信息
    VCT_LINE_FEATURE_TYPE  FeatureType;    // 特征类型,

	// 直接坐标系用到的                     
	std::vector<VCTLineElement>   vecLineData;  // 存储具体的线数据，线段的个数可以就是vecLineData.size()

	// 间接坐标系用到的
	std::vector<VCTID> vecArcID;				   // 间接坐标中的线目标的标识号(间接坐标),
	                                       // 线段的个数可以就是vecArcID.size()
    //以下仅在1.0版本中
	VCTID nFNode;						//起节点	
	VCTID nTNode;						//终节点	
	VCTID nLPolygon;						//左多边形	
	VCTID nRPolygon;						//右多边形	
};

// 面的特征类型
enum  VCT_POLYGON_FEATURE_TYPE
{
	VCT_POLYGON_DIRECT = 1,             // 直接坐标
	VCT_POLYGON_INDIRECT = 100,           // 间接坐标

};


//  间接面的构成类型
enum VCT_POLYGON_INDIRECT_TYPE
{
   VCT_POLYGON_INDIRECT_SUB_LINE = 21,       // 引用子线对象构成的面

   VCT_POLYGON_INDIRECT_SUB_POLYGON = 22,    // 引用子面对象构成的面

};


// 直接面的几何特征
enum VCT_POLYGON_GEOMETRY_TYPE
{
	VCT_POLYGON_SIMPLE = 11,                // 简单多边形
	VCT_POLYGON_3POINTCIRCLE = 12,	        // 三点圆		
	VCT_POLYGON_CIRCLE = 13,	            // 圆心圆		
	VCT_POLYGON_ELLIPSE = 14,		        // 椭圆			
 	
};


//  直接坐标下各种几何图形的数据成员
struct VCTPolygonElement
 {
	VCT_POLYGON_GEOMETRY_TYPE  GeoType;    // 面的几何形状                       
	std::vector<VCTPoint3D>  vecPoints;         // 本圈的坐标串,本圈的点数就是vecPoints.size()
	union
	{
		double	dfRadius;				   // 圆心圆 半径	
	    double	dfRatio;				   // 椭圆 短半轴长度与长半轴的比率
	};
};


//  间接面的结构
struct VCTPolygonIndirect
{ 
	VCT_POLYGON_INDIRECT_TYPE IndirectType; // 间接面的构成类型
	std::vector<VCTID> vecnSubOID;               // 子对象标识号，子对象的项数就是vecnSubOID.size()
};


//  面状要素
struct VCTPolygon
{   
	// 直接间接都要用到的数据
	VCTObjectHeader ObjHeader;				// 要素的头信息
	VCT_POLYGON_FEATURE_TYPE FeatureType;	// 特征类型: 是间接坐标还是直接坐标
	VCTPoint3D LabPoint;					// 标识点坐标
    
	// 直接坐标用到的东西
	std::vector<VCTPolygonElement> vecPolygonElement; // 本面的元素,圈数就是vecPolygonElement.size()
	
	// 间接坐标用到的东西
	VCTPolygonIndirect  PolygonIndrect;  
};

//体要素类型	仅在2.0版本中有
enum  VCT_SOLID_TYPE
{
	VCT_SOLID_DIRECT = 1 ,                // 直接坐标
	VCT_SOLID_INDIRECT = 100,	              // 间接坐标(面目标构成)
};


// 直接坐标下体要素的几何形状标识
enum VCT_SOLID_GEOMETRY_TYPE
{
	VCT_SOLID_FOUR_POLGON = 11,            // 四面体
	VCT_SOLID_CUBOID = 12,                 // 长方体
	VCT_SOLID_ROTATE = 13,                 // 旋转体
    
};

// 直接坐标系下一个体元素的结构
struct VCTSolidElement
{
   	VCT_SOLID_GEOMETRY_TYPE   GeoType;     // 几何图形类型 
	std::vector< VCTPoint3D > vecPoints;        // 点坐标, 公用,四面体\长方体的点数就是vecPoints.size()
	VCTPolygonElement PolygonElement;      // 旋状体用
};


//体要素 仅在2.0版本中有
struct VCTSolid
{
	VCTObjectHeader ObjHeader;			  // 要素的头信息
	VCT_SOLID_TYPE   FeatureType;		  // 特征类型
    VCTPoint3D LabPoibt;                  // 标识点	
    
	//  直接坐标用到的东西
	std::vector<VCTSolidElement> vecSolidElement; // 直接坐标中体的个数就是vecSolidElement.size()

	//  间接坐标用到的东西
	int nSubType;
	std::vector<VCTID> vecSubOid;        		    // 子目标的标识号 ,间接坐标中子目标的項数vecSubOid.size()    
};



//集合目标要素	仅在2.0版本中有
struct VCTAggregation
{
	VCTObjectHeader ObjHeader;			  // 要素的头信息
	
    std::vector<VCTID> vecSubOid;             // 子目标的标识号,子目标的項数就是vecSubOid.size()
};

//注记要素类型 
enum VCT_ANNO_TYPE
{
	VCT_ANNO_SINGLE = 1,			    // 单点注记
	VCT_ANNO_MULTIPLE = 2,		        // 多点注记
};

// 注记点结构
struct VCTAnnoPoint
{
	VCTPoint3D vctPoint3D;             // 坐标点
	float      fShiftDegree;           // 旋转度
	VCTAnnoPoint()
	{
		fShiftDegree = 0;
	}
};

//注记要素
struct VCTAnnotation
{
    VCTObjectHeader ObjHeader;  	   // 要素的头信息
	VCT_ANNO_TYPE   FeatureType;	   // 特征类型
	std::string     strText;                // 注记内容
	
	std::vector<VCTAnnoPoint> vecAnnoPoint; // 注记坐标点

	//以下在1.0版本中有，在2.0版本中没有（放在样式中表示）
	std::string  strFontName;						//字体
	ColorRef ulColor;							//颜色
	//字型 
	int  nWeight;							//磅数,0～1000的整数,表示字型线划的粗细程度。如400代表正常体,700代表粗体字
	int  nType;								//形状,0代表正体,1代表左斜,2代表右斜,3代表左耸,4代表右耸
	bool bUnderline;						//下划线,1代表有下划线,0代表没有下划线
	//大小
	bool bSizeNumber;						//是否用字号表示字的大小
	double dfSizeNumber;					//字号
	double dfTextWidth;						//字宽,实际坐标长度单位
	double dfTextHeight;					//字高,实际坐标长度单位
	//间隔
	double dfSpace;							//间隔,实际坐标长度单位
	//以下是在2.0版本样式中新增加的
	bool   bHorizon;						//横排或竖排,1代表横排,0代表竖排(仅对单点注记)
	int  nDeleteline;						//删除线,0代表没有删除线,1代表有单删除线,	2代表有双删除线
	bool bShadow;							//阴影,1代表有阴影,0代表没有阴影
	bool bHole;								//空心,1代表有空心,0代表没有空心
	std::string strAlign;						//对齐方式,LB代表左下,LC代表左中,LT代表左上,CT代表中上,RT代表右上,
											//RC代表右中,RB代表右下,CB代表中下, CC代表中中(仅对单点注记)
	//初始化
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


//点拓扑	仅在2.0版本中有	
struct VCTNodeTopo
{
	long nObjID;					        // 节点对象的标识号
    std::vector<VCTID> vecSubOid;		        	// 关联线目标的标识号,关联线目标的項数就是vecSubOid.size()
	bool bValid;
};


//线拓扑	仅在2.0版本中有
struct VCTEdgeTopo
{
	VCTID nObjID;							 // 目标标识号
	VCTID nFNodeID;						     // 头节点	
	VCTID nTNodeID;							 // 尾节点	
	VCTID nLPolygonID;						 // 左多边形	
	VCTID nRPolygonID;						 // 右多边形
	
	bool bValid;
};


// 属性表中的一行数据
struct VCTAttributeRow
{
	VCTID              nOID;                   // 对象标识号，位于每一行的开始位置
	std::vector<std::string>    vecstrFieldValues;      // 属性页，即几何对象的字段值
};

struct VCTAttributeTable
{
	std::string                  strTableName;   // 属性表名
	std::vector<VCTAttributeRow> vecRows;		// 属性表的的数据
};	


struct VCTVarchar
{
	VCTID nObjID;
	std::string strText;
};

//样式	仅在2.0版本中有
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


//错误
enum VCT_ERROR_ID
{
	VCT_ERROR_OPENFILE			=	0x00,			// 打开文件失败
	VCT_ERROR_CREATEFILE		=	0x01,			// 创建文件失败
	VCT_ERROR_CREATETEMPFILE	=	0x02,			// 创建临时文件失败
	VCT_ERROR_DATA				=	0x03,			// 数据错误
	VCT_ERROR_EXCEPTION			=	0x20,			// 异常
};

