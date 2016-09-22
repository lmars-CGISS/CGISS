#pragma once
#include "VCT.h" 
#include <google/dense_hash_map> 
#include <fstream>
#include <map>
/// \brief ���Ȼص�
struct VCTProgress
{
	virtual void OnProgress(fpos_t pos) = 0;
};

enum VCT_FILE_FORMAT
{
	VCT_1999=			1,    //���ұ�׼��ʽ1999
	VCT_LAND=			2,    //������Դ����׼1.0
	VCT_GD	=			3,    //�㶫ʡ��������׼1.1
	VCT_LANDUSE=		4,   //������Դ����׼2.0 �������ñ�׼
	VCT_CADASTRAL=      5,    //������Դ����׼2.0 ����ؼ���׼
	VCT_2007=			11,   //���ұ�׼��ʽ2007
};
typedef google::dense_hash_map<VCTID,fpos_t> IDCache;
typedef google::dense_hash_map<std::string,fpos_t> KeyCache;

/// \brief VCT��ʽ��������VCT��ʽ����Ϊ�ڴ����
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
	
	/// \brief ��������
	std::map<std::string,std::string>					m_ConstantMap;

	/// \brief VCT�ļ���ʽ��׼
	VCT_FILE_FORMAT		m_Format;
	std::string			m_Separator;
	std::vector<char>	m_LineCache; 
	const char*			m_Line; 
	std::fstream::pos_type m_Pos;  
	VCTProgress*		m_pProgress;
	
	//��ȡһ��
	const char* ReadLine();
	//��ȡ���ڵĽ�β
	bool ReadToEndSection();
	//��ȡ�������β��
	bool ReadToEndObject();
	//��ȡ�ǿ���
	bool ReadToNoneEmpty();

	//��ǰ��
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

	
	/// \brief ��������
	void ParseRepresentation();
	bool ParseRepresentation(VCTStyle& style);

	/// \brief ��������
	void ParseConstant();
	bool ParseConstant(VCTConstant& constpair);

	/// \brief ������
	void ParseRelationTable();
	bool ParseRelationTable(VCTRelationTable &tab);
	 
	/// \brief �����䳤�ַ���
	void ParseVarchar(); 
	bool ParseVarchar(VCTVarchar& val); 

	/// \brief �����ڵ�����
	void ParseNodeTopology(); 
	bool ParseNodeTopology(VCTNodeTopo& val); 
	/// \brief ����������
	void ParseEdgeTopology(); 
	bool ParseEdgeTopology(VCTEdgeTopo& val); 
	
	/// \brief �����ۺϵ���
	void ParseAggregation();
	bool ParseAggregation(VCTAggregation& coll);

public:
	VCTParser(const char* vct);
	~VCTParser(void);
	
	VCTProgress* Progress();
	void  Progress(VCTProgress* progress);
	/// \brief ���ļ�λ�ö�ȡһ������
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

	/// \brief �ļ�����
	VCT_FILE_FORMAT FileFormat();
	/// \brief �ļ�ͷ
	VCTHead& Head();
	
	/// \brief ����Feature����Feature��������
	IDCache& GeometryIndex(VCTFeatureCode& code);
	IDCache& AttributeIndex(VCTFeatureCode& code);
	IDCache& NodeTopoIndex(VCTFeatureCode& code);
	IDCache& EdgeTopoIndex(VCTFeatureCode& code);

	
	/// \brief �䳤�ַ�������
	IDCache& VarcharIndex();

	/// \brief ��������
	std::map<std::string,std::string>& ConstantMap();
	/// \brief ��ϵ��
	KeyCache& RelationTableIndex();

	/// \brief ʽ������
	KeyCache & StyleIndex();

	std::vector<VCTFeatureCode>&  FeatureCodes();
	std::vector<VCTTableStructure>&  TableStructures();

	/// \brief ��ȡ�����ƶ�Ӧ�ı�ṹ
	VCTTableStructure* TableStructure(const char* tabname);
	 
	/// \brief ����
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
//���ڴ洢����ʱ�ļ���
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

	/// \brief ���ļ�λ�ö�ȡһ������
	void Write(VCTPoint& obj);
	void Write(VCTLine& obj);
	void Write(VCTPolygon& obj);
	void Write(VCTSolid& obj);
	void Write(VCTAnnotation& obj);
	void Write(VCTAttributeRow& obj);
	void Write(VCTAggregation& obj);
	
};

/// \brief VCTд�롣��֧��VCT2007�汾�ĸ�ʽд�롣
class VCTWriter
{
	std::vector<char>										m_LineCache; 
	std::string												m_strVCTFile;
	VCTHead													m_Head;
	std::vector<std::pair<VCTFeatureCode,VCTTableStructure>> m_FeatureCodes;
	std::map<std::string,VCTTempFilePtr >					m_StreamWrite;
	std::map<std::string,std::string>						m_ConstantMap; //������

	//����ͷ
	void SaveHead(std::ofstream& fs);
	void CopyFile(std::ofstream& fs,VCTTempFilePtr &ptrFile);
public:
	VCTWriter(const char* strVCT);
	VCTFeatureWriter BeginFeature(VCTFeatureCode& code,VCTTableStructure tab);
	void Write(VCTStyle& style);
	void Write(VCTRelationTable& tab);
	void Write(const char* key,const char* value);
	
	/// \brief д��䳤�ַ�����
	void Write(VCTID id,const char* value);

	/// \brief �ļ�ͷ��
	VCTHead& Head();
	
	/// \brief ������������д��֮����ô˺����ύ���ݵ������ļ���
	void Finish();
};
