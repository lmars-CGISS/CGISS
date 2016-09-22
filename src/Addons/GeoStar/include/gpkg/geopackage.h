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

/// \brief 命名空间
namespace gpkg
{
	
	
#pragma region sqlite
	/// \brief 字段类型
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
	/// \brief Geometry字段头
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
	
	/// \brief Geometry字段头
	struct geo_package_binary{
		unsigned char magic[2]; 
		unsigned char  version;           
		unsigned char  flags;             
		int srs_id;
		double envelope[8];      

		/// \brief 字段头的长度
		int size();

		/// \brief 检测magic是否正确
		bool is_good_head();

		/// \brief WKB在此头偏移的指针
		unsigned char  *wkb_ptr();
		
		/// \brief 是否是标准数据格式flag第5位
		bool is_standard();
		void is_standard(bool b);

		/// \brief 是否是空geometryflag第4位
		bool is_empty();
		void is_empty(bool b);

		/// \brief 数据记录的矩形的形式。3,2,1三位
		envelope_style envelope_type();
		void envelope_type(envelope_style  style);

		/// \brief 是否是低字节序，0位
		bool is_little_endian();
		void is_little_endian(bool b);

	};


	/// \brief 数据库句柄
	struct database_handle
	{
		database_handle(const char* file);
		~database_handle();
		/// \brief 关闭
		void close();
		/// \brief 是存在表
		bool exist_table(const char* name);
		
		/// \brief 执行sql
		int execute(const char* sql);

		/// \brief 判断返回值是否是错误。
		static bool is_error(int n);

		/// \brief 报告错误
		static void report_error(sqlite3* db);

		sqlite3* m_db;
	};
	typedef std::shared_ptr<database_handle> database_handle_ptr;
	
	
	/// \brief sqlite
	struct sqlite_statment
	{
		/// \brief 创建stmt指针
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

	/// \brief 所有元表和数据表的基类
	class table
	{
	protected:
		/// \brief 数据库指针
		std::weak_ptr<database_handle> m_ptrDB;
		
		/// \brief 表的名称
		std::string m_name;
	public:

		/// \brief 记录总数
		long long count();
		
		/// \brief 数据表是否存在
		bool exists();

		/// \brief 表的名称
		const char* name();

	};
	
#pragma endregion

#pragma region 必要元表
	
	/// \brief 元表gpkg_contents的记录
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
	/// \brief 元表gpkg_contents
	class contents:public table
	{
		sqlite_statment_ptr m_ptrUpdateExtent;
	public:
		contents(std::shared_ptr<database_handle>& db);
		
		/// \brief 查询特定类型的记录
		std::vector<content> query(const char* data_type = NULL);
		
		/// \brief 根据名称查询
		content query_identifier(const char* identifier);

		/// \brief 添加一条新的记录
		bool append(const content& c);

		/// \brief 删除一条记录
		bool remove(const char* strTable);
		
		/// \brief 更新记录的范围
		void update_extent(const content& c);


	};
	/// \brief 智能指针
	typedef std::shared_ptr<contents> contents_ptr;
	/// \brief 空间参考记录
	struct spatial_ref
	{
		std::string srs_name;
		int srs_id;
		std::string organization;
		int organization_coordsys_id;
		std::string definition;
		std::string description;
	};
	/// \brief 元表gpkg_spatial_ref_sys
	class spatial_ref_sys:public table
	{
	public:
		spatial_ref_sys(std::shared_ptr<database_handle>& db);
		
		/// \brief 根据空间参考id查询一个空间参考
		spatial_ref query(int srs_id);

		/// \brief 创建一个空间参考，设置传入空间参考的srs_id
		bool create(spatial_ref& ref);

	};
	
	/// \brief 智能指针
	typedef std::shared_ptr<spatial_ref_sys> spatial_ref_sys_ptr;
#pragma endregion 

#pragma region 可选元表

	
	/// \brief 元表gpkg_tile_matrix_set
	class tile_matrix_set:public table
	{
		
	};
	
	/// \brief 智能指针
	typedef std::shared_ptr<tile_matrix_set> tile_matrix_set_ptr;
	
	/// \brief 几何对象列的记录
	struct geometry_column
	{
		std::string table_name;
		std::string column_name;
		std::string geometry_type_name;
		int srs_id;
		bool z;
		bool m;
	};
	/// \brief 元表gpkg_geometry_columns
	class geometry_columns:public table
	{
	public:
		geometry_columns(std::shared_ptr<database_handle>& db);
		
		/// \brief 根据表的名称查询一条几何记录
		geometry_column query(const char* name);
		
		/// \brief 添加一条新的geometry记录
		bool append(geometry_column &col);

		/// \brief 删除一条记录
		bool remove(const char* tablename);

	};
	
	/// \brief 智能指针
	typedef std::shared_ptr<geometry_columns> geometry_columns_ptr;

	/// \brief 元表gpkg_data_columns
	class data_columns:public table
	{
	};
	/// \brief 智能指针
	typedef std::shared_ptr<data_columns> data_columns_ptr;

	/// \brief 元表gpkg_data_columns_constraints
	class data_columns_constraints:public table
	{
	};
	/// \brief 智能指针
	typedef std::shared_ptr<data_columns_constraints> data_columns_constraints_ptr;

	/// \brief 元表gpkg_tile_matrix
	class tile_matrix:public table
	{
	};
	/// \brief 智能指针
	typedef std::shared_ptr<tile_matrix> tile_matrix_ptr;

	/// \brief 元表gpkg_metadata
	class metadata:public table
	{
	};
	/// \brief 智能指针
	typedef std::shared_ptr<metadata> metadata_ptr;

	/// \brief 元表gpkg_metadata_reference
	class metadata_reference:public table
	{
	};
	
	/// \brief 智能指针
	typedef std::shared_ptr<metadata_reference> metadata_reference_ptr;

	
	/// \brief 一条扩展记录
	struct extension
	{
		std::string table_name;
		std::string column_name;
		std::string extension_name;
		std::string definition;
		std::string scope;
	};
	/// \brief 元表gpkg_extensions
	class extensions:public table
	{
	public:
		extensions(std::shared_ptr<database_handle>& db);
		
		/// \brief 增加一条扩展记录
		bool add(const extension& ext);

		/// \brief 删除一条扩展记录
		void remove(const extension& ext);

		/// \brief 查询一条扩展记录
		bool query(extension& ext);

	};
	/// \brief 智能指针
	typedef std::shared_ptr<extensions> extensions_ptr;

	/// \brief sqlite的id分配表sqlite_sequence
	class sqlite_sequence:public table
	{
		sqlite_statment_ptr m_ptrReader;
	public:
		sqlite_sequence(std::shared_ptr<database_handle>& db);
		/// \brief 查询表的当前自动分配id
		long long query(const char* name);
	};
	/// \brief 智能指针
	typedef std::shared_ptr<sqlite_sequence> sqlite_sequence_ptr;

#pragma endregion 
	
	/// \brief 空间信息类的table基类
	class spatial_table:public table
	{

	};
	
	/// \brief 地物信息
	struct feature
	{
		/// \brief 设置地物的fid
		virtual void fid(long long id) = 0;
		/// \brief 获取地物的fid
		virtual long long fid() = 0;
		
		/// \brief geometry的数据长度
		virtual int geometry_length()= 0;
		/// \brief 获取geometry的数据头指针
		virtual geo_package_binary* geometry()= 0;
		/// \brief 设置geometry
		virtual void geometry(geo_package_binary* geo,int nlen) = 0;

		/// \brief 获取某列的地物整数字段值
		virtual long long int_value(int col)=0;
		/// \brief 获取某列的地物浮点字段值
		virtual double float_value(int col)=0;
		/// \brief 获取某列的地物字符串字段值
		virtual const char* string_value(int col)=0;

		/// \brief 获取某列的地物整数字段值
		virtual void value(int col,long long val)=0;
		/// \brief 获取某列的地物浮点字段值
		virtual void value(int col,double val)=0;
		/// \brief 获取某列的地物字符串字段值
		virtual void value(int col,const char * val)=0;

	};
	/// \brief 地物表
	class feature_table:public spatial_table
	{
		/// \brief 基本信息
		content m_info;
		/// \brief 几何信息
		geometry_column m_geoinfo;
		 
		/// \brief 读取数据的读取
		sqlite_statment_ptr m_ptrReader;
		
		/// \brief 写入数据的statement
		sqlite_statment_ptr m_ptrWriter;
		
		/// \brief 删除数据的statement
		sqlite_statment_ptr m_ptrDelete;
		
		/// \brief geometry字段的索引
		int m_nGeoColPos;

		/// \brief 字段
		std::vector<field> m_fields;
		//读取字段结构
		void read_table_field();
	public:
		feature_table(std::shared_ptr<database_handle>&  db,content& info,geometry_column& geo);
		
		/// \brief 基本原信息
		content&  content_infomation();
		/// \brief 基本原信息
		geometry_column&  geometry_infomation();
		  
		/// \brief 字段
		std::vector<field>& fields();

		/// \brief 设置属性过滤条件
		void filter(long long nOID);

		/// \brief 设置属性过滤条件
		void filter(const char* str = NULL,bool bExact = false,const char* oidtable = NULL);

		/// \brief 设置几何和属性过滤条件
		void filter(double xmin,double ymin,double xmax,double ymax,const char* str,bool bExact = false,const char* oidtable = NULL);
		
		/// \brief 获取下一个feature
		bool next(feature* fea);

		/// \brief 保存一个feature
		bool save(feature* fea);

		/// \brief 根据id删除一个地物
		bool delete_feature(long long nFID);

		/// \brief 创建空间索引
		bool create_spatial_index(extensions* ext);

		/// \brief 删除空间索引
		bool delete_spatial_index(extensions* ext);

		/// \brief 删除表
		bool drop(extensions* ext);

	};
	/// \brief 地物类表智能指针
	typedef std::shared_ptr<feature_table> feature_table_ptr;
	/// \brief 瓦片表
	class tile_table:public spatial_table
	{
	};
	/// \brief 瓦片表智能指针
	typedef std::shared_ptr<tile_table> tile_table_ptr;

	/// \brief 数据库
	class database
	{
		/// \brief sqlite标准序列表。
		sqlite_sequence_ptr m_ptrSequence;
		/// \brief 扩展表
		extensions_ptr m_ptrExtensions;
		/// \brief 数据库对象
		database_handle_ptr  m_ptrDB;
		/// \brief 内容元表
		contents_ptr m_ptrContents;
		/// \brief 空间参考元表
		spatial_ref_sys_ptr m_ptrSR;

		/// \brief 几何元信息表
		geometry_columns_ptr m_ptrGeo;
		
	public:
		/// \brief sqlite的句柄
		sqlite3* handle();
		
		/// \brief 数据库的句柄。
		database_handle_ptr  DB();

		/// \brief 获取内容元表
		contents* contents_table();
		/// \brief 获取空间参考元表
		spatial_ref_sys* spatial_ref_table();

		/// \brief 获取几何信息元表
		geometry_columns* geometry_columns_table();

		/// \brief 扩展表
		extensions* extensions_table();

		/// \brief 获取序列表指针
		sqlite_sequence* sequence_table();


	public:
		/// \brief 打开或者创建新的数据库
		database(const char* strFile,bool bNew = true);
		~database();
		
		/// \brief 关闭数据库
		void close();

		/// \brief 是否成功打开
		bool is_open();
		
		/// \brief 打开地物类表
		feature_table_ptr open_feature_table(const char* strTable);

		/// \brief 创建一个地物类
		feature_table_ptr create_feature_table(content& c,const std::vector<field>& vecFields);


	};
	/// \brief 数据库智能指针
	typedef std::shared_ptr<database> database_ptr;


	/// \brief 事务
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