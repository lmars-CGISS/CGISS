#pragma once
#include "VCT.h" 
#include <google/dense_hash_map> 
#include <fstream>
#include <map>
/// \brief 进度回调
struct VCTProgress
{
	virtual void OnProgress(fpos_t pos) = 0;
};

enum VCT_FILE_FORMAT
{
	VCT_1999=			1,    //国家标准格式1999
	VCT_LAND=			2,    //国土资源部标准1.0
	VCT_GD	=			3,    //广东省国土厅标准1.1
	VCT_LANDUSE=		4,   //国土资源部标准2.0 土地利用标准
	VCT_CADASTRAL=      5,    //国土资源部标准2.0 城镇地籍标准
	VCT_2007=			11,   //国家标准格式2007
};
typedef google::dense_hash_map<VCTID,fpos_t> IDCache;
typedef google::dense_hash_map<std::string,fpos_t> KeyCache;

/// \brief VCT格式解析，将VCT格式解析为内存对象。
class VCTParser
{
	std::string m_strVCTFile;
	std::ifstream m_fs;
	
	VCTHead m_Head;
	std::vector<VCTFeatureCode> m_FeatureCodes;
	std::vector<VCTTableStructure> m_TableStructures;
	google::dense_hash_map<VCT_GEOMETRY_TYPE,
		 google::dense_hash_map<std::string,IDCache> > m_GeometryIndex;
	
	google::dense_hash_map<std::string,IDCache>        m_AttributeIndex;
	KeyCache											m_StyleIndex;
	KeyCache											m_RelationTableIndex; 
	IDCache											   m_VarCharIndex;
	IDCache											   m_NodeTopoIndex;
	IDCache											   m_EdgeTopoIndex;
	
	/// \brief 常量缓存
	std::map<std::string,std::string>					m_ConstantMap;

	/// \brief VCT文件格式标准
	VCT_FILE_FORMAT		m_Format;
	std::string			m_Separator;
	std::vector<char>	m_LineCache; 
	const char*			m_Line; 
	std::fstream::pos_type m_Pos;  
	VCTProgress*		m_pProgress;
	
	//读取一行
	const char* ReadLine();
	//读取到节的结尾
	bool ReadToEndSection();
	//读取到对象结尾。
	bool ReadToEndObject();
	//读取非空行
	bool ReadToNoneEmpty();

	//当前行
	const char* CurrentLine();

	void Cache(VCT_GEOMETRY_TYPE gType, const std::string& code, VCTID id,fpos_t pos);
	
	void Cache(VCTPoint &geo,fpos_t pos);
	void Cache(VCTLine &geo,fpos_t pos);
	void Cache(VCTPolygon &geo,fpos_t pos);
	void Cache(VCTSolid &geo,fpos_t pos);
	void Cache(VCTAnnotation &geo,fpos_t pos); 
	void Cache(VCTNodeTopo &geo,fpos_t pos);
	void Cache(VCTEdgeTopo &geo,fpos_t pos);
	void Cache(VCTAggregation &geo,fpos_t pos);
	bool Cache(const char* tab,VCTAttributeRow &row,fpos_t pos);


	void Cache(VCTStyle &style,fpos_t pos);
	void Cache(VCTVarchar &val,fpos_t pos);

	void ParseHead(const char* strLine);
	void ParseFeatureCode(const char* strLine);
	void ParseTableStructure();
	void ParsePoint();
	bool ParsePoint(VCTPoint3D& pt);
	bool ParsePoint(VCTPoint& pt);
	bool ParsePoint(std::vector<VCTPoint3D>& pt,int nCount=0);

	bool ParseObjectHead(VCTObjectHeader& head);
	void ParseAttribute();
	bool ParseAttribute(VCTAttributeRow& row,int nFieldCount);

	void ParseLine();
	bool ParseLine(VCTLine& ln); 

	void ParsePolygon();
	bool ParsePolygon(VCTPolygon& area); 
	bool ParsePolygon(std::vector<VCTPolygonElement>& vecEle); 

	bool ParseRef(std::vector<VCTID>& vecSubOid);

	void ParseSolid();
	bool ParseSolid(VCTSolid& geo); 

	void ParseAnnotation();
	bool ParseAnnotation(VCTAnnotation& geo); 

	
	/// \brief 解析常量
	void ParseRepresentation();
	bool ParseRepresentation(VCTStyle& style);

	/// \brief 解析常量
	void ParseConstant();
	bool ParseConstant(VCTConstant& constpair);

	/// \brief 关联表
	void ParseRelationTable();
	bool ParseRelationTable(VCTRelationTable &tab);
	 
	/// \brief 解析变长字符串
	void ParseVarchar(); 
	bool ParseVarchar(VCTVarchar& val); 

	/// \brief 解析节点拓扑
	void ParseNodeTopology(); 
	bool ParseNodeTopology(VCTNodeTopo& val); 
	/// \brief 解析边拓扑
	void ParseEdgeTopology(); 
	bool ParseEdgeTopology(VCTEdgeTopo& val); 
	
	/// \brief 解析聚合地物
	void ParseAggregation();
	bool ParseAggregation(VCTAggregation& coll);

public:
	VCTParser(const char* vct);
	~VCTParser(void);
	
	VCTProgress* Progress();
	void  Progress(VCTProgress* progress);
	/// \brief 从文件位置读取一个对象
	bool ParseObject(fpos_t pos,VCTPoint& obj);
	bool ParseObject(fpos_t pos,VCTLine& obj);
	bool ParseObject(fpos_t pos,VCTPolygon& obj);
	bool ParseObject(fpos_t pos,VCTSolid& obj);
	bool ParseObject(fpos_t pos,VCTAnnotation& obj);
	bool ParseObject(fpos_t pos,VCTAttributeRow& obj);
	bool ParseObject(fpos_t pos,VCTVarchar& obj);
	bool ParseObject(fpos_t pos,VCTConstant& obj);
	bool ParseObject(fpos_t pos,VCTRelationTable& obj);
	bool ParseObject(fpos_t pos,VCTAggregation& obj);
	bool ParseObject(fpos_t pos,VCTEdgeTopo& obj);
	bool ParseObject(fpos_t pos,VCTNodeTopo& obj); 

	/// \brief 文件类型
	VCT_FILE_FORMAT FileFormat();
	/// \brief 文件头
	VCTHead& Head();
	
	/// \brief 根据Feature表获得Feature的索引。
	IDCache& GeometryIndex(VCTFeatureCode& code);
	IDCache& AttributeIndex(VCTFeatureCode& code);
	IDCache& NodeTopoIndex(VCTFeatureCode& code);
	IDCache& EdgeTopoIndex(VCTFeatureCode& code);

	
	/// \brief 变长字符串缓存
	IDCache& VarcharIndex();

	/// \brief 常量缓存
	std::map<std::string,std::string>& ConstantMap();
	/// \brief 关系表
	KeyCache& RelationTableIndex();

	/// \brief 式样索引
	KeyCache & StyleIndex();

	std::vector<VCTFeatureCode>&  FeatureCodes();
	std::vector<VCTTableStructure>&  TableStructures();

	/// \brief 获取表名称对应的表结构
	VCTTableStructure* TableStructure(const char* tabname);
	 
	/// \brief 解析
	bool Parse();
};

enum VCTTempFileType
{
	ePointFile,
	eLineFile,
	ePolygonFile,
	eSolidFile,
	eAnnotationFile,
	eAggregationFile,
	eAttributeFile,
	eStyleFile,
	eRelationTableFile,
	eVarcharFile,
};
//用于存储的临时文件。
struct VCTTempFile
{
	std::string File;
	VCTTempFileType Type;
	std::ofstream FS;
};
typedef std::shared_ptr<VCTTempFile> VCTTempFilePtr;
class VCTFeatureWriter
{
	VCTTempFilePtr m_GeoTempFile;
	VCTTempFilePtr m_AttTempFile;
	VCTFeatureCode m_Code;
	VCTHead			m_Head;
	void Write(const VCTObjectHeader& vctObjectHeader);
	void Write(const std::vector<VCTPoint3D>& pts);
	void Write(const VCTPoint3D &pt);
	void Write(const std::vector<VCTID>& pts);
 
	void EndObject();
public:
	VCTFeatureWriter(VCTFeatureCode &code,VCTTempFilePtr ptrGeo,
		VCTTempFilePtr ptrAtt,VCTHead &head);
	VCTFeatureWriter(const VCTFeatureWriter& rhs);
	VCTFeatureWriter& operator =(const VCTFeatureWriter& rhs);

	/// \brief 从文件位置读取一个对象
	void Write(VCTPoint& obj);
	void Write(VCTLine& obj);
	void Write(VCTPolygon& obj);
	void Write(VCTSolid& obj);
	void Write(VCTAnnotation& obj);
	void Write(VCTAttributeRow& obj);
	void Write(VCTAggregation& obj);
	
};

/// \brief VCT写入。仅支持VCT2007版本的格式写入。
class VCTWriter
{
	std::vector<char>										m_LineCache; 
	std::string												m_strVCTFile;
	VCTHead													m_Head;
	std::vector<std::pair<VCTFeatureCode,VCTTableStructure>> m_FeatureCodes;
	std::map<std::string,VCTTempFilePtr >					m_StreamWrite;
	std::map<std::string,std::string>						m_ConstantMap; //常量。

	//保存头
	void SaveHead(std::ofstream& fs);
	void CopyFile(std::ofstream& fs,VCTTempFilePtr &ptrFile);
public:
	VCTWriter(const char* strVCT);
	VCTFeatureWriter BeginFeature(VCTFeatureCode& code,VCTTableStructure tab);
	void Write(VCTStyle& style);
	void Write(VCTRelationTable& tab);
	void Write(const char* key,const char* value);
	
	/// \brief 写入变长字符串。
	void Write(VCTID id,const char* value);

	/// \brief 文件头。
	VCTHead& Head();
	
	/// \brief 结束所有数据写入之后调用此函数提交数据到最终文件。
	void Finish();
};
