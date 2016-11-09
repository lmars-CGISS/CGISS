#pragma once
#include <memory>
#include <bitset>
#include <vector>
#include <string>
#ifndef SQLITE_DLL 
#include <sqlite3.h>
#endif

//http://www.geopackage.org/
//http://www.geopackage.org/spec/#_ogc_geopackage_encoding_standard_with_corrigendum
struct sqlite3;
struct sqlite3_stmt;

/// \brief �����ռ�
namespace gpkg
{
	
	
#pragma region sqlite
	/// \brief �ֶ�����
	enum field_type
	{
		BOOLEAN,
		TINYINT,
		MEDIUMINT,
		INTEGER,
		INT=INTEGER,
		FLOAT,
		DOUBLE,
		REAL=DOUBLE,
		TEXT,
		BLOB,
		DATE,
		DATETIME,
		POINT,
		LINESTRING,
		MULTIPOLYGON,
	}; 
	/// \brief Geometry�ֶ�ͷ
	struct field
	{
		field();
		field(const field& r);
		field(const char* name ,field_type t);

		std::string name;
		field_type type;
		bool is_geometry();
	};
	 
	enum envelope_style
	{
		NoEnvelope=0,
		EnvelopeXY=1,
		EnvelopeXYZ=2,
		EnvelopeXYM=3,
		EnvelopeXYZM=4,
	};
	
	/// \brief Geometry�ֶ�ͷ
	struct geo_package_binary{
		unsigned char magic[2]; 
		unsigned char  version;           
		unsigned char  flags;             
		int srs_id;
		double envelope[8];      

		/// \brief �ֶ�ͷ�ĳ���
		int size();

		/// \brief ���magic�Ƿ���ȷ
		bool is_good_head();

		/// \brief WKB�ڴ�ͷƫ�Ƶ�ָ��
		unsigned char  *wkb_ptr();
		
		/// \brief �Ƿ��Ǳ�׼���ݸ�ʽflag��5λ
		bool is_standard();
		void is_standard(bool b);

		/// \brief �Ƿ��ǿ�geometryflag��4λ
		bool is_empty();
		void is_empty(bool b);

		/// \brief ���ݼ�¼�ľ��ε���ʽ��3,2,1��λ
		envelope_style envelope_type();
		void envelope_type(envelope_style  style);

		/// \brief �Ƿ��ǵ��ֽ���0λ
		bool is_little_endian();
		void is_little_endian(bool b);

	};


	/// \brief ���ݿ���
	struct database_handle
	{
		database_handle(const char* file);
		~database_handle();
		/// \brief �ر�
		void close();
		/// \brief �Ǵ��ڱ�
		bool exist_table(const char* name);
		
		/// \brief ִ��sql
		int execute(const char* sql);

		/// \brief �жϷ���ֵ�Ƿ��Ǵ���
		static bool is_error(int n);

		/// \brief �������
		static void report_error(sqlite3* db);

		sqlite3* m_db;
	};
	typedef std::shared_ptr<database_handle> database_handle_ptr;
	
	
	/// \brief sqlite
	struct sqlite_statment
	{
		/// \brief ����stmtָ��
		sqlite3_stmt * m_pStmt;   
		sqlite_statment(sqlite3* db,const char* sql);
		virtual ~sqlite_statment();
		bool prepare(sqlite3* db,const char* sql);
		bool bind(int i ,double v);
		bool bind(int i ,int v);
		bool bind(int i ,const char* v);
		bool bind(int i );
		bool bind(int i ,long long);
		bool bind(int i ,const unsigned char* v,int nLen);

		bool reset();
		int step();
		std::string string_value(int c);
		long long int64_value(int c);
		double double_value(int c);
		const unsigned char* blob_value(int c,int& n);
		long long last_rowid();
	};
	typedef std::shared_ptr<sqlite_statment> sqlite_statment_ptr;

	/// \brief ����Ԫ������ݱ�Ļ���
	class table
	{
	protected:
		/// \brief ���ݿ�ָ��
		std::weak_ptr<database_handle> m_ptrDB;
		
		/// \brief �������
		std::string m_name;
	public:

		/// \brief ��¼����
		long long count();
		
		/// \brief ���ݱ��Ƿ����
		bool exists();

		/// \brief �������
		const char* name();

	};
	
#pragma endregion

#pragma region ��ҪԪ��
	
	/// \brief Ԫ��gpkg_contents�ļ�¼
	struct content
	{
		std::string table_name;
		std::string data_type;
		std::string identifier;
		std::string description;
		time_t last_change;
		double min_x;
		double min_y;
		double max_x;
		double max_y;
		int srs_id;
	};
	/// \brief Ԫ��gpkg_contents
	class contents:public table
	{
		sqlite_statment_ptr m_ptrUpdateExtent;
	public:
		contents(std::shared_ptr<database_handle>& db);
		
		/// \brief ��ѯ�ض����͵ļ�¼
		std::vector<content> query(const char* data_type = NULL);
		
		/// \brief �������Ʋ�ѯ
		content query_identifier(const char* identifier);

		/// \brief ���һ���µļ�¼
		bool append(const content& c);

		/// \brief ɾ��һ����¼
		bool remove(const char* strTable);
		
		/// \brief ���¼�¼�ķ�Χ
		void update_extent(const content& c);


	};
	/// \brief ����ָ��
	typedef std::shared_ptr<contents> contents_ptr;
	/// \brief �ռ�ο���¼
	struct spatial_ref
	{
		std::string srs_name;
		int srs_id;
		std::string organization;
		int organization_coordsys_id;
		std::string definition;
		std::string description;
	};
	/// \brief Ԫ��gpkg_spatial_ref_sys
	class spatial_ref_sys:public table
	{
	public:
		spatial_ref_sys(std::shared_ptr<database_handle>& db);
		
		/// \brief ���ݿռ�ο�id��ѯһ���ռ�ο�
		spatial_ref query(int srs_id);

		/// \brief ����һ���ռ�ο������ô���ռ�ο���srs_id
		bool create(spatial_ref& ref);

	};
	
	/// \brief ����ָ��
	typedef std::shared_ptr<spatial_ref_sys> spatial_ref_sys_ptr;
#pragma endregion 

#pragma region ��ѡԪ��

	
	/// \brief Ԫ��gpkg_tile_matrix_set
	class tile_matrix_set:public table
	{
		
	};
	
	/// \brief ����ָ��
	typedef std::shared_ptr<tile_matrix_set> tile_matrix_set_ptr;
	
	/// \brief ���ζ����еļ�¼
	struct geometry_column
	{
		std::string table_name;
		std::string column_name;
		std::string geometry_type_name;
		int srs_id;
		bool z;
		bool m;
	};
	/// \brief Ԫ��gpkg_geometry_columns
	class geometry_columns:public table
	{
	public:
		geometry_columns(std::shared_ptr<database_handle>& db);
		
		/// \brief ���ݱ�����Ʋ�ѯһ�����μ�¼
		geometry_column query(const char* name);
		
		/// \brief ���һ���µ�geometry��¼
		bool append(geometry_column &col);

		/// \brief ɾ��һ����¼
		bool remove(const char* tablename);

	};
	
	/// \brief ����ָ��
	typedef std::shared_ptr<geometry_columns> geometry_columns_ptr;
	 

	/// \brief Ԫ��gpkg_tile_matrix
	class tile_matrix:public table
	{
	};
	/// \brief ����ָ��
	typedef std::shared_ptr<tile_matrix> tile_matrix_ptr;

	/// \brief Ԫ��gpkg_metadata
	class metadata:public table
	{
	};
	/// \brief ����ָ��
	typedef std::shared_ptr<metadata> metadata_ptr;

	/// \brief Ԫ��gpkg_metadata_reference
	class metadata_reference:public table
	{
	};
	
	/// \brief ����ָ��
	typedef std::shared_ptr<metadata_reference> metadata_reference_ptr;

	
	/// \brief ������������
	struct symbol
	{
		/// \brief ���ű�ʶ
		int id;
		/// \brief �������͡�
		std::string type;

		/// \brief ����Ȩ�������ķ��Žṹ����URI��
		/// ��OGC 05-077r4���ŵ�URIֵӦ���Ƿ���ģʽ�����ռ�http://schemas.opengeospatial.net/se�� 
		std::string sd_standard_uri;

		/// \brief ���ŵ�MIME  ����
		///			text/xml
		std::string mime_type;

		/// \brief ��������
		std::vector<unsigned char> data;
	};

	/// \brief ���ű���չ
	class symbols:public table
	{
	public:
		symbols(std::shared_ptr<database_handle>& db);
		
		/// \brief ����һ������
		bool add(symbol& data);

		/// \brief ɾ��һ������
		bool remove(const symbol& data);

		/// \brief ��ѯһ������
		bool query(symbol& data);

		/// \brief �滻һ����������
		bool replace(const symbol& data);

	};
	/// \brief ����ָ��
	typedef std::shared_ptr<symbols> symbols_ptr;


	/// \brief ��������
	struct symbol_reference
	{
		std::string table_name;
		long long	featureid;
		std::string filter;
		long long	symbolid;
	};

	/// \brief ��������
	class symbols_reference:public table
	{
		sqlite_statment_ptr m_ptrQuery;
	public:
		symbols_reference(std::shared_ptr<database_handle>& db);
		
		/// \brief ����һ������
		bool add(const symbol_reference& data);

		/// \brief ɾ��һ�����е����з�������
		bool remove(const std::string& table_name);

		/// \brief ɾ��һ������ĳ��feature�ķ�������
		bool remove(const std::string& table_name,long long feataureid);


		/// \brief ��ʼ��ѯһ���������ķ�������
		bool query(const char* table_name);

		/// \brief ��ʼ��ѯһ�����������ĳ��featureid�ķ���
		bool query(const char* table_name, long long featureid);
		
		/// \brief ����query֮���ȡ��һ�����õĲ�ѯ�����
		bool next(symbol_reference& data);


	};
	/// \brief ����ָ��
	typedef std::shared_ptr<symbols_reference> symbols_reference_ptr;

	
	/// \brief һ����չ��¼
	struct extension
	{
		std::string table_name;
		std::string column_name;
		std::string extension_name;
		std::string definition;
		std::string scope;
	};
	/// \brief Ԫ��gpkg_extensions
	class extensions:public table
	{
	public:
		extensions(std::shared_ptr<database_handle>& db);
		
		/// \brief ����һ����չ��¼
		bool add(const extension& ext);

		/// \brief ɾ��һ����չ��¼
		void remove(const extension& ext);

		/// \brief ��ѯһ����չ��¼
		bool query(extension& ext);

	};
	/// \brief ����ָ��
	typedef std::shared_ptr<extensions> extensions_ptr;

	/// \brief sqlite��id�����sqlite_sequence
	class sqlite_sequence:public table
	{
		sqlite_statment_ptr m_ptrReader;
	public:
		sqlite_sequence(std::shared_ptr<database_handle>& db);
		/// \brief ��ѯ��ĵ�ǰ�Զ�����id
		long long query(const char* name);
	};
	/// \brief ����ָ��
	typedef std::shared_ptr<sqlite_sequence> sqlite_sequence_ptr;

#pragma endregion 
	
	/// \brief �ռ���Ϣ���table����
	class spatial_table:public table
	{

	};
	
	/// \brief ������Ϣ
	struct feature
	{
		/// \brief ���õ����fid
		virtual void fid(long long id) = 0;
		/// \brief ��ȡ�����fid
		virtual long long fid() = 0;
		
		/// \brief geometry�����ݳ���
		virtual int geometry_length()= 0;
		/// \brief ��ȡgeometry������ͷָ��
		virtual geo_package_binary* geometry()= 0;
		/// \brief ����geometry
		virtual void geometry(geo_package_binary* geo,int nlen) = 0;

		/// \brief ��ȡĳ�еĵ��������ֶ�ֵ
		virtual long long int_value(int col)=0;
		/// \brief ��ȡĳ�еĵ��︡���ֶ�ֵ
		virtual double float_value(int col)=0;
		/// \brief ��ȡĳ�еĵ����ַ����ֶ�ֵ
		virtual const char* string_value(int col)=0;

		/// \brief ��ȡĳ�еĵ��������ֶ�ֵ
		virtual void value(int col,long long val)=0;
		/// \brief ��ȡĳ�еĵ��︡���ֶ�ֵ
		virtual void value(int col,double val)=0;
		/// \brief ��ȡĳ�еĵ����ַ����ֶ�ֵ
		virtual void value(int col,const char * val)=0;

	};
	/// \brief �����
	class feature_table:public spatial_table
	{
		/// \brief ������Ϣ
		content m_info;
		/// \brief ������Ϣ
		geometry_column m_geoinfo;
		 
		/// \brief ��ȡ���ݵĶ�ȡ
		sqlite_statment_ptr m_ptrReader;
		
		/// \brief д�����ݵ�statement
		sqlite_statment_ptr m_ptrWriter;
		
		/// \brief ɾ�����ݵ�statement
		sqlite_statment_ptr m_ptrDelete;
		
		/// \brief geometry�ֶε�����
		int m_nGeoColPos;

		/// \brief �ֶ�
		std::vector<field> m_fields;
		//��ȡ�ֶνṹ
		void read_table_field();
	public:
		feature_table(std::shared_ptr<database_handle>&  db,content& info,geometry_column& geo);
		
		/// \brief ����ԭ��Ϣ
		content&  content_infomation();
		/// \brief ����ԭ��Ϣ
		geometry_column&  geometry_infomation();
		  
		/// \brief �ֶ�
		std::vector<field>& fields();

		/// \brief �������Թ�������
		void filter(long long nOID);

		/// \brief �������Թ�������
		void filter(const char* str = NULL,bool bExact = false,const char* oidtable = NULL);

		/// \brief ���ü��κ����Թ�������
		void filter(double xmin,double ymin,double xmax,double ymax,const char* str,bool bExact = false,const char* oidtable = NULL);
		
		/// \brief ��ȡ��һ��feature
		bool next(feature* fea);

		/// \brief ����һ��feature
		bool save(feature* fea);

		/// \brief ����idɾ��һ������
		bool delete_feature(long long nFID);

		/// \brief �����ռ�����
		bool create_spatial_index(extensions* ext);

		/// \brief ɾ���ռ�����
		bool delete_spatial_index(extensions* ext);

		/// \brief ɾ����
		bool drop(extensions* ext);

	};
	/// \brief �����������ָ��
	typedef std::shared_ptr<feature_table> feature_table_ptr;
	/// \brief ��Ƭ��
	class tile_table:public spatial_table
	{
	};
	/// \brief ��Ƭ������ָ��
	typedef std::shared_ptr<tile_table> tile_table_ptr;

	/// \brief ���ݿ�
	class database
	{
		/// \brief sqlite��׼���б�
		sqlite_sequence_ptr m_ptrSequence;
		/// \brief ��չ��
		extensions_ptr m_ptrExtensions;
		/// \brief ���ݿ����
		database_handle_ptr  m_ptrDB;
		/// \brief ����Ԫ��
		contents_ptr m_ptrContents;
		/// \brief �ռ�ο�Ԫ��
		spatial_ref_sys_ptr m_ptrSR;

		/// \brief ����Ԫ��Ϣ��
		geometry_columns_ptr m_ptrGeo;
		
		/// \brief ���ű�
		symbols_ptr m_ptrSymbolData;

		/// \brief �������ñ���¼����ͷ��ŵĹ�ϵ��
		symbols_reference_ptr m_ptrSymRef;
	public:
		/// \brief sqlite�ľ��
		sqlite3* handle();
		
		/// \brief ���ݿ�ľ����
		database_handle_ptr  DB();

		/// \brief ���ű�
		symbols* symbol_table();
		/// \brief �������ñ���¼����ͷ��ŵĹ�ϵ��
		symbols_reference* symbol_reference_table();

		/// \brief ��ȡ����Ԫ��
		contents* contents_table();
		/// \brief ��ȡ�ռ�ο�Ԫ��
		spatial_ref_sys* spatial_ref_table();

		/// \brief ��ȡ������ϢԪ��
		geometry_columns* geometry_columns_table();

		/// \brief ��չ��
		extensions* extensions_table();

		/// \brief ��ȡ���б�ָ��
		sqlite_sequence* sequence_table();


	public:
		/// \brief �򿪻��ߴ����µ����ݿ�
		database(const char* strFile,bool bNew = true);
		~database();
		
		/// \brief �ر����ݿ�
		void close();

		/// \brief �Ƿ�ɹ���
		bool is_open();
		
		/// \brief �򿪵������
		feature_table_ptr open_feature_table(const char* strTable);

		/// \brief ����һ��������
		feature_table_ptr create_feature_table(content& c,const std::vector<field>& vecFields);


	};
	/// \brief ���ݿ�����ָ��
	typedef std::shared_ptr<database> database_ptr;


	/// \brief ����
	class transaction 
	{
		database_ptr m_database;
	public:
		transaction (const database_ptr& db);
		virtual ~transaction ();
		void abort();
		void commit();

	};

};