#include "geopackage.h"  
#include <iostream>
#include <sstream>

#ifndef WIN32
#define stricmp strcasecmp
#define _stricmp strcasecmp
#endif
/// \brief 命名空间
namespace gpkg
{   

#pragma region field
	const char* field_name[]={"BOOLEAN","TINYINT","MEDIUMINT","INTEGER","INT","FLOAT","REAL","DOUBLE","TEXT","BLOB","DATE","DATETIME","POINT","LINESTRING","MULTIPOLYGON",NULL};
	field_type  filed_type_index[]={BOOLEAN , TINYINT , MEDIUMINT , INTEGER , INT, FLOAT , REAL , DOUBLE , TEXT , BLOB , DATE , DATETIME,POINT,LINESTRING,MULTIPOLYGON };
	const char* field_type_name(field_type t)
	{
		for(int i =0;i<sizeof(filed_type_index) / sizeof(field_type);i++)
		{
			if(filed_type_index[i] ==t)
				return field_name[i];
		}
		return NULL;
	}
	
	field_type parser_field_type(const char* str)
	{
		if(NULL == str || strlen(str)==0)
			return TEXT;
		int i =0;
		while(field_name[i] != NULL)
		{
			if(stricmp(field_name[i],str)==0)
				return filed_type_index[i];
			i++;
		}
		return TEXT;
	}
	field::field()
	{
		type  = TEXT;
	}
	field::field(const field& r)
	{
		name = r.name;
		type = r.type;
	}
	field::field(const char* strname,field_type t)
	{
		name = strname;
		type = t;
	}
	bool field::is_geometry()
	{
		return type == POINT || type == LINESTRING || type == MULTIPOLYGON;
	}
#pragma endregion
#pragma region geo_package_binary
	/// \brief 检测magic是否正确
	bool geo_package_binary::is_good_head()
	{
		return magic[0] == 'G' && magic[1] == 'P';
	}
	/// \brief 字段头的长度
	int geo_package_binary::size()
	{
		switch(envelope_type())
		{
		case NoEnvelope:
			return 8;
		case EnvelopeXY:
			return 8 + 4 * 8;
		case EnvelopeXYZ:
		case EnvelopeXYM:
			return 8 + 6 * 8;
		case EnvelopeXYZM:
			return 8 + 8 * 8;
		}
		return 8;
	}
	/// \brief WKB在此头偏移的指针
	unsigned char  *geo_package_binary::wkb_ptr()
	{
		switch(envelope_type())
		{
		case NoEnvelope:
			return (unsigned char  *)envelope;
		case EnvelopeXY:
			return (unsigned char  *)(envelope + 4);
		case EnvelopeXYZ:
		case EnvelopeXYM:
			return (unsigned char  *)(envelope + 6);
		case EnvelopeXYZM:
			return (unsigned char  *)(envelope + 8);
		}
		return (unsigned char  *)envelope;
	}
		
	/// \brief 是否是标准数据格式flag第5位
	bool geo_package_binary::is_standard()
	{
		std::bitset<8>* pBit = (std::bitset<8>*)&flags;
		return !pBit->test(5);
	}
	void geo_package_binary::is_standard(bool b)
	{
		std::bitset<8>* pBit = (std::bitset<8>*)&flags;
		pBit->set(5,b);
	}
		
	/// \brief 是否是空geometryflag第4位
	bool geo_package_binary::is_empty()
	{
		std::bitset<8>* pBit = (std::bitset<8>*)&flags;
		return pBit->test(4);
	}
	void geo_package_binary::is_empty(bool  b)
	{
		std::bitset<8>* pBit = (std::bitset<8>*)&flags;
		pBit->set(4,b);
	}

	/// \brief 数据记录的矩形的形式。3,2,1三位
	envelope_style geo_package_binary::envelope_type()
	{
		 return (envelope_style)((flags & (0x07 << 1)) >> 1);
	}
	void geo_package_binary::envelope_type(envelope_style style)
	{
		int f = (style<<1);
		flags|=f;
	}

	/// \brief 是否是高字节序，0位
	bool geo_package_binary::is_little_endian()
	{
		std::bitset<8>* pBit = (std::bitset<8>*)&flags;
		return pBit->test(0);
	}
	void geo_package_binary::is_little_endian(bool b)
	{
		std::bitset<8>* pBit = (std::bitset<8>*)&flags;
		pBit->set(0,b);
	}

	
#pragma endregion
#pragma region sqlite_statment
	sqlite_statment::sqlite_statment(sqlite3* db,const char* sql)
	{
		int n = sqlite3_prepare_v2(db,sql,strlen(sql),&m_pStmt,0);
		if(database_handle::is_error(n))
			database_handle::report_error(db);
		//std::cout<<n<<std::endl;

	}
	bool sqlite_statment::reset()
	{
		if(!m_pStmt)
			return false;
		return database_handle::is_error(sqlite3_reset(m_pStmt));
	}
	bool sqlite_statment::bind(int i ,const unsigned char* v,int nLen)
	{
		if(nLen <=0)
			return bind(i);
		return sqlite3_bind_blob(m_pStmt,i,v,nLen,NULL) == SQLITE_OK;
	}
	bool sqlite_statment::bind(int i ,double v)
	{
		return sqlite3_bind_double(m_pStmt,i,v) == SQLITE_OK;
	}
	bool sqlite_statment::bind(int i ,long long v)
	{
		return sqlite3_bind_int64(m_pStmt,i,v) == SQLITE_OK;
	}
	bool sqlite_statment::bind(int i ,int v)
	{
		return sqlite3_bind_int(m_pStmt,i,v) == SQLITE_OK;
	}
	bool sqlite_statment::bind(int i )
	{
		return sqlite3_bind_null(m_pStmt,i) == SQLITE_OK;
	}
	bool sqlite_statment::bind(int i ,const char* v)
	{
		if(v == NULL || strlen(v) ==0)
			return bind(i);

		return sqlite3_bind_text(m_pStmt,i,v,strlen(v),NULL) == SQLITE_OK;
	}

	bool sqlite_statment::prepare(sqlite3* db,const char* sql)
	{
		if(NULL != m_pStmt)
			sqlite3_finalize(m_pStmt);
		m_pStmt = NULL;
		return sqlite3_prepare_v2(db,sql,strlen(sql),&m_pStmt,0) == SQLITE_OK;
	}
	sqlite_statment::~sqlite_statment()
	{
		if(NULL != m_pStmt)
			sqlite3_finalize(m_pStmt);
		m_pStmt = NULL;
	}
	long long sqlite_statment::last_rowid()
	{
		if(m_pStmt == NULL)
			return 0;
		return sqlite3_last_insert_rowid(sqlite3_db_handle(m_pStmt));
	}
	int sqlite_statment::step()
	{
		int i = sqlite3_step(m_pStmt);
		if(database_handle::is_error(i))
			database_handle::report_error(sqlite3_db_handle(m_pStmt));
		return i;
	}
	std::string sqlite_statment::string_value(int c)
	{
		const unsigned char* str = sqlite3_column_text(m_pStmt,c);
		if(NULL == str)
			return std::string();
		return std::string((const char*)str);
	}
	long long sqlite_statment::int64_value(int c)
	{
		return sqlite3_column_int64(m_pStmt,c);
	}
	const unsigned char* sqlite_statment::blob_value(int c,int& n)
	{
		n = sqlite3_column_bytes(m_pStmt,c);
		return (const unsigned char*)sqlite3_column_blob(m_pStmt,c);
	}
	double sqlite_statment::double_value(int c)
	{
		return sqlite3_column_double(m_pStmt,c);
	}
	 
#pragma endregion
#pragma region database_handle
	   


	static void GeoPackageSTMinX(sqlite3_context* pContext,int argc, sqlite3_value** argv)
	{
		if( sqlite3_value_type (argv[0]) != SQLITE_BLOB )
			return;
		geo_package_binary* pHead = (geo_package_binary*)sqlite3_value_blob(argv[0]);
		sqlite3_result_double( pContext, pHead->envelope[0]);

	}
	static void GeoPackageSTMinY(sqlite3_context* pContext,int argc, sqlite3_value** argv)
	{
		if( sqlite3_value_type (argv[0]) != SQLITE_BLOB )
			return;
		geo_package_binary* pHead = (geo_package_binary*)sqlite3_value_blob(argv[0]);
		sqlite3_result_double( pContext, pHead->envelope[2]);
 
	}
	static void GeoPackageSTMaxX(sqlite3_context* pContext,int argc, sqlite3_value** argv)
	{
		if( sqlite3_value_type (argv[0]) != SQLITE_BLOB )
			return;
		geo_package_binary* pHead = (geo_package_binary*)sqlite3_value_blob(argv[0]);
		sqlite3_result_double( pContext, pHead->envelope[1]);
 		 
	}
	static void GeoPackageSTMaxY(sqlite3_context* pContext,int argc, sqlite3_value** argv)
	{
		if( sqlite3_value_type (argv[0]) != SQLITE_BLOB )
			return;
		geo_package_binary* pHead = (geo_package_binary*)sqlite3_value_blob(argv[0]);
		sqlite3_result_double( pContext, pHead->envelope[3]);
 		 
	}
	static void GeoPackageSTIsEmpty(sqlite3_context* pContext,int argc, sqlite3_value** argv)
	{
		if( sqlite3_value_type (argv[0]) != SQLITE_BLOB )
			return;
		geo_package_binary* pHead = (geo_package_binary*)sqlite3_value_blob(argv[0]);
		sqlite3_result_int( pContext, pHead->is_empty()?1:0);
	}
	static void GeoPackageSTGeometryType(sqlite3_context* pContext,int argc, sqlite3_value** argv)
	{
		 
	}
	static void GeoPackageGPKGIsAssignable(sqlite3_context* pContext,int argc, sqlite3_value** argv)
	{
		 
	}
	static void GeoPackageSTSRID(sqlite3_context* pContext,int argc, sqlite3_value** argv)
	{
		 
	}
	//创建sqlite3的扩展函数
	void create_function(sqlite3* hDB)
	{
		
		/* Used by RTree Spatial Index Extension */
		if(database_handle::is_error(sqlite3_create_function(hDB, "ST_MinX", 1, SQLITE_ANY, NULL,GeoPackageSTMinX, NULL, NULL)))
			database_handle::report_error(hDB);

		if(database_handle::is_error(sqlite3_create_function(hDB, "ST_MinY", 1, SQLITE_ANY, NULL,GeoPackageSTMinY, NULL, NULL)))
			database_handle::report_error(hDB);
		if(database_handle::is_error(sqlite3_create_function(hDB, "ST_MaxX", 1, SQLITE_ANY, NULL,GeoPackageSTMaxX, NULL, NULL)))
			database_handle::report_error(hDB);
		if(database_handle::is_error(sqlite3_create_function(hDB, "ST_MaxY", 1, SQLITE_ANY, NULL,GeoPackageSTMaxY, NULL, NULL)))
			database_handle::report_error(hDB);
		if(database_handle::is_error(sqlite3_create_function(hDB, "ST_IsEmpty", 1, SQLITE_ANY, NULL,GeoPackageSTIsEmpty, NULL, NULL)))
			database_handle::report_error(hDB);
		/* Used by Geometry Type Triggers Extension */
		if(database_handle::is_error(sqlite3_create_function(hDB, "ST_GeometryType", 1, SQLITE_ANY, NULL,GeoPackageSTGeometryType, NULL, NULL)))
			database_handle::report_error(hDB);
		if(database_handle::is_error(sqlite3_create_function(hDB, "GPKG_IsAssignable", 2, SQLITE_ANY, NULL,GeoPackageGPKGIsAssignable, NULL, NULL)))
			database_handle::report_error(hDB);

		/* Used by Geometry SRS ID Triggers Extension */
		if(database_handle::is_error(sqlite3_create_function(hDB, "ST_SRID", 1, SQLITE_ANY, NULL,GeoPackageSTSRID, NULL, NULL)))
			database_handle::report_error(hDB);
	}

	database_handle::database_handle(const char* file)
	{
		sqlite3_open(file,&m_db);
		create_function(m_db);
	}
	database_handle::~database_handle()
	{
		close();
	}
	void database_handle::close()
	{
		if(NULL != m_db)
			sqlite3_close(m_db);
		m_db = NULL;
	}
	//执行sql
	int database_handle::execute(const char* sql)
	{
		int n = sqlite3_exec(m_db,sql,NULL,NULL,NULL);
		if(is_error(n))
			database_handle::report_error(m_db);
		return n;
	}
	
	/// \brief 判断返回值是否是错误。
	bool database_handle::is_error(int n)
	{
		switch(n)
		{
		case SQLITE_OK:
		case SQLITE_ROW:
		case SQLITE_DONE:
			return false;
		}
		return true;
	}

	void database_handle::report_error(sqlite3* db)
	{
		std::cout<<"Sqlite Error "<<sqlite3_errmsg(db)<<std::endl;
	}

	
	//是存在表
	bool database_handle::exist_table(const char* name)
	{ 
		sqlite_statment stmt(m_db,"select * from sqlite_master where type ='table' and tbl_name=?;");
		stmt.bind(1,name);
		return stmt.step() == SQLITE_ROW;
	}
#pragma endregion
#pragma region table
	/// \brief 记录总数
	long long table::count()
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return 0;

		std::stringstream ss;
		ss<<"select count(*) from "<<m_name;
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str()); 
		if(stmt.step() != SQLITE_ROW)
			return 0;
		return stmt.int64_value(0);
	}
	/// \brief 数据表是否存在
	bool table::exists()
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return false;
		return ptrDB->exist_table(m_name.c_str());
	}
	/// \brief 表的名称
	const char* table::name()
	{
		return m_name.c_str();
	}

#pragma endregion
#pragma region extensions
	extensions::extensions(std::shared_ptr<database_handle>& db)
	{
		m_name = "gpkg_extensions";
		m_ptrDB = db;
		if(exists())
			return;
		
		//没有则创建元表。
		//http://www.geopackage.org/spec/#gpkg_extensions_sql
		std::string sql = "CREATE TABLE gpkg_extensions (\
									table_name TEXT,\
									column_name TEXT,\
									extension_name TEXT NOT NULL,\
									definition TEXT NOT NULL,\
									scope TEXT NOT NULL,\
									CONSTRAINT ge_tce UNIQUE (table_name, column_name, extension_name));";
		db->execute(sql.c_str());
		
	}
	/// \brief 增加一条扩展记录
	bool extensions::add(const extension& ext)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return false;

		std::stringstream ss;
		ss <<"insert or replace into gpkg_extensions(table_name,column_name,extension_name,definition,scope)\
			 values(?,?,?,?,?)";
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
		stmt.bind(1,ext.table_name.c_str());
		stmt.bind(2,ext.column_name.c_str());
		stmt.bind(3,ext.extension_name.c_str());
		stmt.bind(4,ext.definition.c_str());
		stmt.bind(5,ext.scope.c_str());
		return database_handle::is_error(stmt.step());
	}

	/// \brief 删除一条扩展记录
	void extensions::remove(const extension& ext)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return ;

		std::stringstream ss;
		ss <<"delete from  gpkg_extensions where  table_name =? and  column_name = ? and extension_name =?";
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
		stmt.bind(1,ext.table_name.c_str());
		stmt.bind(2,ext.column_name.c_str());
		stmt.bind(3,ext.extension_name.c_str());
		stmt.step();
	}
	/// \brief 查询一条扩展记录
	bool extensions::query(extension& ext)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return  false;

		std::stringstream ss;
		ss <<"select definition,scope from  gpkg_extensions where  table_name =? and  column_name = ? and extension_name =?";
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
		stmt.bind(1,ext.table_name.c_str());
		stmt.bind(2,ext.column_name.c_str());
		stmt.bind(3,ext.extension_name.c_str());
		if(SQLITE_ROW != stmt.step())
			return false;
		ext.definition = stmt.string_value(0);
		ext.scope = stmt.string_value(1);
		return true;
	}

	
#pragma endregion
#pragma region contents
	sqlite_sequence::sqlite_sequence(std::shared_ptr<database_handle>& db)
	{
		m_name = "sqlite_sequence";
		m_ptrDB = db;
	}
	 
	/// \brief 查询表的当前自动分配id
	long long sqlite_sequence::query(const char* nam)
	{
		
		if(!m_ptrReader)
		{
			
			database_handle_ptr ptrDB = m_ptrDB.lock();
			if(!ptrDB.get())
				return  0;
			std::stringstream ss;
			ss<<"select seq from "<<name()<<" where name=?";
			m_ptrReader.reset(new sqlite_statment(ptrDB->m_db,ss.str().c_str()));
		}
		else
			m_ptrReader->reset();
		m_ptrReader->bind(1,nam);

		if(SQLITE_ROW != m_ptrReader->step())
			return 0;
		long long n =  m_ptrReader->int64_value(0);

		//将游标使用完。否则可能会锁定记录。造成数据表无法被删除。
		while(SQLITE_ROW == m_ptrReader->step())
		{

		}
		return n;
	}
	
#pragma endregion
#pragma region contents
	contents::contents(std::shared_ptr<database_handle>& db)
	{ 
		m_name = "gpkg_contents";
		m_ptrDB = db;
		if(exists())
			return;
		
		//没有则创建元表。
		//http://www.geopackage.org/spec/#_contents
		std::string sql = "CREATE TABLE gpkg_contents \
							(table_name  TEXT     NOT NULL PRIMARY KEY,\
							data_type   TEXT     NOT NULL,\
							identifier  TEXT     UNIQUE,\
							description TEXT     DEFAULT '',\
							last_change DATETIME NOT NULL DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ','now')),\
							min_x       DOUBLE,\
							min_y       DOUBLE,\
							max_x       DOUBLE,\
							max_y       DOUBLE,\
							srs_id      INTEGER,\
							CONSTRAINT fk_gc_r_srs_id FOREIGN KEY (srs_id) REFERENCES gpkg_spatial_ref_sys(srs_id))";
		db->execute(sql.c_str());
		
	}
	/// \brief 更新记录的范围
	void contents::update_extent(const content& c)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return ;
		if(!m_ptrUpdateExtent.get())
		{
			std::stringstream ss;
			ss<<"update "<<name()<<" set min_x=min(min_x,?) ,min_y=min(min_y,?) ,\
								   max_x=max(max_x,?) ,max_y=max(max_y,?) where table_name=?";
			m_ptrUpdateExtent.reset(new sqlite_statment(ptrDB->m_db,ss.str().c_str()));
		}
		else
			m_ptrUpdateExtent->reset();

		m_ptrUpdateExtent->bind(1,c.min_x);
		m_ptrUpdateExtent->bind(2,c.min_y);
		m_ptrUpdateExtent->bind(3,c.max_x);
		m_ptrUpdateExtent->bind(4,c.max_y);
		m_ptrUpdateExtent->bind(5,c.table_name.c_str());
		m_ptrUpdateExtent->step();
		

	}
	/// \brief 删除一条记录
	bool contents::remove(const char* strTable)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return false;
		
		std::stringstream ss;
		ss <<"delete from  gpkg_contents where table_name=?";
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
		stmt.bind(1,strTable);
		return !database_handle::is_error(stmt.step());

	}


	/// \brief 添加一条新的记录
	bool contents::append(const content& c)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return false;

		std::stringstream ss;
		ss <<"insert into gpkg_contents(table_name,data_type,identifier,description,min_x,min_y,max_x,max_y,srs_id)\
			 values(?,?,?,?,?,?,?,?,?)";
		
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
		int i =1;
		stmt.bind(i++,c.table_name.c_str());
		stmt.bind(i++,c.data_type.c_str());
		stmt.bind(i++,c.identifier.c_str());
		stmt.bind(i++,c.description.c_str());
		stmt.bind(i++,c.min_x);
		stmt.bind(i++,c.min_y);
		stmt.bind(i++,c.max_x);
		stmt.bind(i++,c.max_y);
		stmt.bind(i++,c.srs_id);
		 
		return stmt.step() == SQLITE_OK;
	}


	/// \brief 根据名称查询
	content contents::query_identifier(const char* identifier)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return content();

		std::stringstream ss;
		ss <<"select table_name,data_type,identifier,description,last_change,min_x,min_y,max_x,max_y,srs_id from gpkg_contents";
		ss <<" where identifier=?";
		
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
		stmt.bind(1,identifier);
		 
		if(stmt.step() != SQLITE_ROW)
			return content();
		
		content c;
		int i =0;
		c.table_name = stmt.string_value(i++);
		c.data_type = stmt.string_value(i++);
		c.identifier = stmt.string_value(i++);
		c.description = stmt.string_value(i++);
		c.last_change = stmt.int64_value(i++);
		c.min_x = stmt.double_value(i++);
		c.min_y = stmt.double_value(i++);
		c.max_x = stmt.double_value(i++);
		c.max_y = stmt.double_value(i++);
		c.srs_id = stmt.int64_value(i++);
		return c;
	}
	/// \brief 查询特定类型的记录
	std::vector<content> contents::query(const char* data_type)
	{
		std::stringstream ss;
		ss <<"select table_name,data_type,identifier,description,last_change,min_x,min_y,max_x,max_y,srs_id from gpkg_contents";
		if(strlen(data_type)>0)
			ss <<" where data_type=?";
		
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return std::vector<content>();

		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());

		stmt.bind(1,data_type);
		
		std::vector<content>  vecRet;
		while(stmt.step() == SQLITE_ROW)
		{
			content c;
			int i =0;
			c.table_name = stmt.string_value(i++);
			c.data_type = stmt.string_value(i++);
			c.identifier = stmt.string_value(i++);
			c.description = stmt.string_value(i++);
			c.last_change = stmt.int64_value(i++);
			c.min_x = stmt.double_value(i++);
			c.min_y = stmt.double_value(i++);
			c.max_x = stmt.double_value(i++);
			c.max_y = stmt.double_value(i++);
			c.srs_id = stmt.int64_value(i++);
			vecRet.push_back(c);
		}
		return vecRet;

	}
#pragma endregion
#pragma region spatial_ref_sys
	spatial_ref_sys::spatial_ref_sys(std::shared_ptr<database_handle>& db)
	{
		m_name = "gpkg_spatial_ref_sys";
		m_ptrDB = db;
		if(!db->exist_table("gpkg_spatial_ref_sys"))
		{
			//没有则创建元表。
			//http://www.geopackage.org/spec/#spatial_ref_sys
			std::string sql = "CREATE TABLE gpkg_spatial_ref_sys(srs_name                 TEXT    NOT NULL,\
								srs_id                   INTEGER NOT NULL PRIMARY KEY,\
								organization             TEXT    NOT NULL,\
								organization_coordsys_id INTEGER NOT NULL,\
								definition               TEXT    NOT NULL,\
								description              TEXT)";
			db->execute(sql.c_str());
		}
	}
	/// \brief 创建一个空间参考，设置传入空间参考的srs_id
	bool spatial_ref_sys::create(spatial_ref& ref)
	{
		//获取数据库句柄，无法获得则退出
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return false;

		//组件查询的sql
		std::stringstream ss;
		ss <<"insert into  gpkg_spatial_ref_sys(srs_name,srs_id,organization,organization_coordsys_id,definition,description)\
			 values(?,?,?,?,?,?)";
 
		//准备statement
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
		//绑定id
		int i =1;
		stmt.bind(i++,ref.srs_name.c_str());
		stmt.bind(i++,ref.srs_id);
		stmt.bind(i++,ref.organization.c_str());
		stmt.bind(i++,ref.organization_coordsys_id);
		stmt.bind(i++,ref.definition.c_str());
		stmt.bind(i++,ref.description.c_str());
		  
		return  stmt.step() == SQLITE_OK;

	}

	/// \brief 根据空间参考id查询一个空间参考
	spatial_ref spatial_ref_sys::query(int srs_id)
	{
		//获取数据库句柄，无法获得则退出
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return spatial_ref();

		//组件查询的sql
		std::stringstream ss;
		ss <<"select srs_name,srs_id,organization,organization_coordsys_id,definition,description from gpkg_spatial_ref_sys where srs_id=?";

		//准备statement
		sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
		//绑定id
		stmt.bind(1,srs_id);
		
		if(stmt.step() != SQLITE_ROW)
			return spatial_ref();

		spatial_ref ref;
		int i =0;
		ref.srs_name  = stmt.string_value(i++);
		ref.srs_id = stmt.int64_value(i++);
		ref.organization = stmt.string_value(i++);
		ref.organization_coordsys_id = stmt.int64_value(i++);
		ref.definition = stmt.string_value(i++);
		ref.description = stmt.string_value(i++);
		return ref;
	}
#pragma endregion
#pragma region geometry_columns
geometry_columns::geometry_columns(std::shared_ptr<database_handle>& db)
{
	m_ptrDB = db;
	if(!db->exist_table("gpkg_geometry_columns"))
	{
		//没有则创建元表。
		//http://www.geopackage.org/spec/#_geometry_columns
		std::string sql = "CREATE TABLE gpkg_geometry_columns ( \
							table_name TEXT NOT NULL, \
							column_name TEXT NOT NULL, \
							geometry_type_name TEXT NOT NULL, \
							srs_id INTEGER NOT NULL, \
							z TINYINT NOT NULL, \
							m TINYINT NOT NULL, \
							CONSTRAINT pk_geom_cols PRIMARY KEY (table_name, column_name), \
							CONSTRAINT uk_gc_table_name UNIQUE (table_name), \
							CONSTRAINT fk_gc_tn FOREIGN KEY (table_name) REFERENCES gpkg_contents(table_name), \
							CONSTRAINT fk_gc_srs FOREIGN KEY (srs_id) REFERENCES gpkg_spatial_ref_sys (srs_id))";
		db->execute(sql.c_str());
	}
}
/// \brief 删除一条记录
bool geometry_columns::remove(const char* tablename)
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return false;

	//组件查询的sql
	std::stringstream ss;
	ss <<"delete from gpkg_geometry_columns where table_name=?";

	//准备statement
	sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
	stmt.bind(1,tablename);
		
	return !database_handle::is_error(stmt.step());
}


/// \brief 添加一条新的geometry记录
bool geometry_columns::append(geometry_column &col)
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return false;

	//组件查询的sql
	std::stringstream ss;
	ss <<"insert into gpkg_geometry_columns( table_name,column_name,geometry_type_name,srs_id,z,m)\
		 values(?,?,?,?,?,?)";

	//准备statement
	sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
	int i =1;
	stmt.bind(i++,col.table_name.c_str());
	stmt.bind(i++,col.column_name.c_str());
	stmt.bind(i++,col.geometry_type_name.c_str());
	stmt.bind(i++,col.srs_id);
	stmt.bind(i++,col.z);
	stmt.bind(i++,col.m);
		
	return !database_handle::is_error(stmt.step());
}
geometry_column geometry_columns::query(const char* name)
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return geometry_column();

	//组件查询的sql
	std::stringstream ss;
	ss <<"select table_name,column_name,geometry_type_name,srs_id,z,m from gpkg_geometry_columns where table_name=?";

	//准备statement
	sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());
	stmt.bind(1,name);
		
	if(stmt.step() != SQLITE_ROW)
		return geometry_column();

	geometry_column ref;
	int i =0;
	ref.table_name  = stmt.string_value(i++);
	ref.column_name = stmt.string_value(i++);
	ref.geometry_type_name = stmt.string_value(i++);
	ref.srs_id = stmt.int64_value(i++);
	ref.z = stmt.int64_value(i++);
	ref.m = stmt.int64_value(i++);
	return ref;
}
#pragma endregion
#pragma region feature_table
feature_table::feature_table(std::shared_ptr<database_handle>&  db,content& info,geometry_column& geo)
{
	m_name = info.table_name;
	m_nGeoColPos = -1;
	m_ptrDB = db;
	m_info = info;
	m_geoinfo = geo;
	read_table_field();
}
/// \brief 基本原信息
content&  feature_table::content_infomation()
{
	return m_info;
}

/// \brief 字段
std::vector<field>& feature_table::fields()
{
	return m_fields;
}
/// \brief 基本原信息
geometry_column& feature_table::geometry_infomation()
{
	return m_geoinfo;
}
//读取字段结构
void feature_table::read_table_field()
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return ;
	m_nGeoColPos = -1;
	m_fields.clear();
	std::stringstream ss;
	ss<<"select * from "<<name();
	sqlite_statment stmt(ptrDB->m_db,ss.str().c_str());

	for(int i =0;i<sqlite3_column_count(stmt.m_pStmt);i++)
	{
		const char* str = sqlite3_column_decltype(stmt.m_pStmt,i);
		field f;
		f.name = sqlite3_column_name(stmt.m_pStmt,i);
		f.type = parser_field_type(str);
		m_fields.push_back(f);
		if(stricmp(f.name.c_str(),m_geoinfo.column_name.c_str())==0)
			m_nGeoColPos = i;
	}
}
/// \brief 设置属性过滤条件
void feature_table::filter(long long nOID)
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return ;
	//组件查询的sql
	std::stringstream ss;
	ss <<"select * from " << m_info.table_name<<" where "<<m_fields.front().name<<"=?";
	m_ptrReader.reset(new sqlite_statment(ptrDB->m_db,ss .str().c_str())); 
	m_ptrReader->bind(1,nOID); 

}
/// \brief 设置属性过滤条件
void feature_table::filter(const char* str,bool bExact ,const char* oidtable)
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return ;
	//组件查询的sql
	std::stringstream ss;
	ss <<"select ";

	//精确查询的话则只使用这两个字段。
	if(bExact)
		ss<<"d."<<m_fields.front().name<<",d."<<m_geoinfo.column_name;
	else
		ss<<"d.*";

	ss<<" from " << name()<<" d";
	if(oidtable)
		ss<<","<<oidtable<<" o";
	
	bool bWhere = false;
	if(NULL != str && strlen(str) >0)
	{
		ss<<" where " << str;
		bWhere = true;
	}
	
	if(oidtable)
		ss<<(bWhere?" and ":" where ")<<m_fields.front().name<<"=o.oid";

	m_ptrReader.reset(new sqlite_statment(ptrDB->m_db,ss .str().c_str()));  
}

/// \brief 设置几何和属性过滤条件
void feature_table::filter(double xmin,double ymin,double xmax,double ymax,const char* str,bool bExact,const char* oidtable)
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return ;
	//索引表名称
	std::string strIndexTable = "rtree_";
	strIndexTable+=m_info.identifier;
	strIndexTable+="_";
	strIndexTable+=m_geoinfo.column_name;
	bool bExistIndex = ptrDB->exist_table(strIndexTable.c_str());

	//组件查询的sql
	std::stringstream ss;
	ss<<"select ";
	if(bExact)
		ss<<"d."<<m_fields.front().name<<","<<"d."<<m_geoinfo.column_name;
	else
		ss<<"d.*";
	
	ss <<" from " << m_info.table_name <<" d";
	if( oidtable)
		ss<<","<<oidtable <<" o ";

	if( bExistIndex)
		ss<<","<<strIndexTable <<" i ";

	bool bWhere = false;
	if(bExistIndex)
	{
		ss<<" where " ;
		bWhere = true;
		if(NULL != str && strlen(str) >0)
			ss<<str <<" and ";
		ss<<" i.id=d.fid and i.maxX>=? AND i.minX<=? AND i.maxY>=?  AND i.minY<=?" ;
	
	}else 	if(NULL != str && strlen(str) >0)
	{
		ss<<" where "<< str;
		bWhere = true;
	}
	if( oidtable)
		ss<<(bWhere? " and ":" where ")<<"d."<<m_fields.front().name<<"=o.oid";;

	m_ptrReader.reset(new sqlite_statment(ptrDB->m_db,ss .str().c_str()));
	if(bExistIndex)
	{
		m_ptrReader->bind(1,xmin);
		m_ptrReader->bind(2,xmax);
		m_ptrReader->bind(3,ymin);
		m_ptrReader->bind(4,ymax);
	} 
}
void CreateSpatialIndex(database_handle* db,const char* table,const char* geom,const char* fid)
{
	std::stringstream ss;
	std::string index;
	ss<<"rtree_"<<table<<"_"<< geom;
	index = ss.str();
	
	ss.str("");
	//创建空间索引表
	ss<<"CREATE VIRTUAL TABLE "<<index<<" USING rtree(id, minx, maxx, miny, maxy)";
	//创建空间索引表。
	db->execute(ss.str().c_str());

	
	//创建空间索引的触发器1
	ss.str("");
	ss<<"CREATE TRIGGER "<<index<<"_update1  AFTER UPDATE OF "<<geom <<" ON "<<table<<" WHEN OLD."<<fid
		<<" = NEW."<<fid<<" AND (NEW."<<geom<<" NOTNULL AND NOT ST_IsEmpty(NEW."<<geom
		<<")) BEGIN INSERT OR REPLACE INTO "<<index<<" VALUES (NEW."<<fid<<",ST_MinX(NEW."<<geom
		<<"), ST_MaxX(NEW."<<geom<<"),ST_MinY(NEW."<<geom<<"), ST_MaxY(NEW."<<geom<<")); END";
	db->execute(ss.str().c_str());

	//创建空间索引的触发器2
	ss.str("");
	ss<<"CREATE TRIGGER "<<index<<"_update2 AFTER UPDATE OF "<<geom
		<<" ON "<<table<<" WHEN OLD."<<fid<<" = NEW."<<fid<<" AND (NEW."<<geom<<" ISNULL OR ST_IsEmpty(NEW."<<geom
		<<")) BEGIN DELETE FROM "<<index<<" WHERE id = OLD."<<fid<<"; END";
	db->execute(ss.str().c_str());

	//创建空间索引的触发器3
	ss.str("");
	ss<<"CREATE TRIGGER "<<index<<"_update3 AFTER UPDATE OF "<<geom<<" ON "<<table<<" WHEN OLD."<<fid<<" != NEW."
		<<fid<<" AND (NEW."<<geom<<" NOTNULL AND NOT ST_IsEmpty(NEW."<<geom<<")) BEGIN DELETE FROM  "
		<<index<<" WHERE id = OLD."<<fid<<"; INSERT OR REPLACE INTO "<<index<<" VALUES (NEW."<<fid<<",ST_MinX(NEW."
		<<geom<<"), ST_MaxX(NEW."<<geom<<"),ST_MinY(NEW."<<geom<<"), ST_MaxY(NEW."<<geom<<")); END";
	db->execute(ss.str().c_str());

	//创建空间索引的触发器4
	ss.str("");
	ss<<"CREATE TRIGGER "<<index<<"_update4 AFTER UPDATE ON "<<table<<" WHEN OLD."<<fid<<" != NEW."
		<<fid<<" AND (NEW."<<geom<<" ISNULL OR ST_IsEmpty(NEW."<<geom<<")) BEGIN DELETE FROM "
		<<index<<" WHERE id IN (OLD."<<fid<<", NEW."<<fid<<"); END";
	db->execute(ss.str().c_str());


	//创建空间索引的触发器5,删除
	ss.str("");
	ss<<"CREATE TRIGGER "<<index<<"_delete AFTER DELETE ON "<<table<<" WHEN old."<<geom<<" NOT NULL BEGIN DELETE FROM "
		<<index<<" WHERE id = OLD."<<fid<<"; END";
	db->execute(ss.str().c_str());

	//创建空间索引的触发器6,insert
	ss.str("");
	ss<<"CREATE TRIGGER "<<index<<"_insert AFTER INSERT ON "<<table<<" WHEN (new."<<geom<<" NOT NULL AND NOT ST_IsEmpty(NEW."
		<<geom<<")) BEGIN INSERT OR REPLACE INTO "<<index<<" VALUES (NEW."<<fid<<",ST_MinX(NEW."<<geom<<"), ST_MaxX(NEW."
		<<geom<<"),ST_MinY(NEW."<<geom<<"), ST_MaxY(NEW."<<geom<<")); END";
	db->execute(ss.str().c_str());


	//插入空间索引数据
	ss.str("");
	ss<<"insert into "<<index<<" select "<<fid<<",ST_MinX("<<geom<<"),ST_MaxX("<<geom<<"),ST_MinY("<<geom
		<<"),ST_MaxY("<<geom<<") from "<<table;
	db->execute(ss.str().c_str());
}
/// \brief 创建空间索引
bool feature_table::create_spatial_index(extensions* ext)
{
		//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return false;

	extension extent;
	extent.table_name = name();
	extent.extension_name = "gpkg_rtree_index";
	extent.definition ="GeoPackage 1.0 Specification Annex L";
	extent.scope ="write-only"; 
	

	std::string fid="oid";
	/// \brief 字段
	std::vector<field>::iterator it = m_fields.begin();
	for(;it != m_fields.end();it++)
	{
		//特殊识别主键字段。
		if(stricmp(it->name.c_str(),"OID")==0 ||
			stricmp(it->name.c_str(),"fid")==0 )
		{
			fid = it->name;
		}
		if(!it->is_geometry())
			continue;
		extent.column_name = it->name;
		ext->add(extent);
		
		CreateSpatialIndex(ptrDB.get(),name(),it->name.c_str(),fid.c_str());
		
	}
	 
	return true;
}
/// \brief 删除表
bool feature_table::drop(extensions* ext)
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return false;
	m_ptrReader = NULL;
	m_ptrWriter = NULL;
	m_ptrDelete = NULL;

	//删除空间索引表
	std::stringstream ss;
	ss<<"drop table "<<name();
	ptrDB->execute(ss.str().c_str());

	delete_spatial_index(ext);
	
	return true;
}
/// \brief 删除空间索引
bool feature_table::delete_spatial_index(extensions* ext)
{
	//获取数据库句柄，无法获得则退出
	database_handle_ptr ptrDB = m_ptrDB.lock();
	if(!ptrDB.get())
		return false;
	
	extension extent;
	extent.table_name = name();
	extent.extension_name = "gpkg_rtree_index"; 
	
	/// \brief 字段
	std::vector<field>::iterator it = m_fields.begin();
	for(;it != m_fields.end();it++)
	{
		if(!it->is_geometry())
			continue;
		extent.column_name = it->name;
		//删除空间索引的记录
		ext->remove(extent);
		
		//删除空间索引表
		std::stringstream ss;
		ss<<"drop table if exists rtree_"<<name()<<"_"<< it->name;
		ptrDB->execute(ss.str().c_str());
		
		ss.str("");
		ss<<"drop trigger if  exists rtree_"<<name()<<"_"<< it->name<<"_update1";
		ptrDB->execute(ss.str().c_str());

		ss.str("");
		ss<<"drop trigger if  exists rtree_"<<name()<<"_"<< it->name<<"_update2";
		ptrDB->execute(ss.str().c_str());

		ss.str("");
		ss<<"drop trigger if  exists rtree_"<<name()<<"_"<< it->name<<"_update3";
		ptrDB->execute(ss.str().c_str());


		ss.str("");
		ss<<"drop trigger if  exists rtree_"<<name()<<"_"<< it->name<<"_update4";
		ptrDB->execute(ss.str().c_str());


		ss.str("");
		ss<<"drop trigger if  exists rtree_"<<name()<<"_"<< it->name<<"_insert";
		ptrDB->execute(ss.str().c_str());

		ss.str("");
		ss<<"drop trigger if  exists rtree_"<<name()<<"_"<< it->name<<"_delete";
		ptrDB->execute(ss.str().c_str());

	}
	return true;
}


/// \brief 根据id删除一个地物
bool feature_table::delete_feature(long long nFID)
{
	if(!m_ptrDelete)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return false;
		//组件查询的sql
		std::stringstream ss;
		ss<<"delete from "<<name()<<" where "; 

		for(int i =0;i<m_fields.size();i++)
		{
			field &f = m_fields[i];
			if(stricmp(f.name.c_str(),"OID")==0 ||
				stricmp(f.name.c_str(),"fid")==0 )
			{
				ss<<f.name;
				break;
			}
		}
		ss<<"=?";
		m_ptrDelete.reset(new sqlite_statment(ptrDB->m_db,ss .str().c_str()));
	}
	else
		m_ptrDelete->reset();

	m_ptrDelete->bind(1,nFID);
	return !database_handle::is_error(m_ptrDelete->step());
}


/// \brief 保存一个feature
bool feature_table::save(feature* fea)
{
	if(!m_ptrWriter)
	{
		database_handle_ptr ptrDB = m_ptrDB.lock();
		if(!ptrDB.get())
			return false;
		//组件查询的sql
		std::stringstream ss;
		ss<<"insert or replace into "<<m_info.table_name<<" values("; 

		for(int i =0;i<m_fields.size();i++)
		{
			if(i >0)
				ss<<",";
			ss<<"?";
		}
		ss<<")";
		m_ptrWriter.reset(new sqlite_statment(ptrDB->m_db,ss .str().c_str()));
	}
	else
		m_ptrWriter->reset();
	long long fid = 0;
	for(int i =0;i<m_fields.size();i++)
	{
		field &f = m_fields[i];
		switch(f.type)
		{
		case BOOLEAN:
			case TINYINT:
			case MEDIUMINT:
				m_ptrWriter->bind(i+1,fea->int_value(i));
				break;
			case INTEGER:
				//特殊识别主键字段。
				if(stricmp(f.name.c_str(),"OID")==0 ||
					stricmp(f.name.c_str(),"fid")==0 )
				{
					fid = fea->fid();
					if(fid <=0)
						m_ptrWriter->bind(i+1);
					else
						m_ptrWriter->bind(i+1,fid);
				}
				else
					m_ptrWriter->bind(i+1,fea->int_value(i));
				break;
			case FLOAT:
			case DOUBLE:
				m_ptrWriter->bind(i+1,fea->float_value(i));
				break;
			case TEXT:
				m_ptrWriter->bind(i+1,fea->string_value(i));
				break;
			case BLOB:
			case DATE:
			case DATETIME:
				break;
			case POINT:
			case LINESTRING:
			case MULTIPOLYGON:
				geo_package_binary* pGeo =fea->geometry();
				m_ptrWriter->bind(i+1,(unsigned char*)pGeo,fea->geometry_length());
				break;
		}
	}
	if(database_handle::is_error(m_ptrWriter->step()))
		return false;
	if(fid <=0)
		fea->fid(m_ptrWriter->last_rowid());
	return true;
}

/// \brief 获取下一个feature
bool feature_table::next(feature* fea)
{
	if(!m_ptrReader.get())
		return false;
	if(m_ptrReader->step() != SQLITE_ROW)
		return false;
	fea->fid(m_ptrReader->int64_value(0)); 
	for(int i =1;i<sqlite3_column_count(m_ptrReader->m_pStmt);i++)
	{
		//如果是geometry字段则特殊处理。
		if(i == m_nGeoColPos)
		{
			int n;
			const unsigned char* geo = m_ptrReader->blob_value(i,n);
			geo_package_binary* phead = (geo_package_binary*)geo;
			fea->geometry(phead,n);
		}
		else
		{
			switch(m_fields[i].type)
			{
				case BOOLEAN:
				case TINYINT:
				case MEDIUMINT:
				case INTEGER:
					fea->value(i,m_ptrReader->int64_value(i));
					break;
				//case INT:
				case FLOAT:
				case DOUBLE:
					fea->value(i,(float)m_ptrReader->double_value(i));
					break;
				//case REAL:
				case TEXT:
				case BLOB:
				case DATE:
				case DATETIME:
					fea->value(i,m_ptrReader->string_value(i).c_str());
					break;
			}
		}
	}
	return true;
}
 

#pragma endregion
#pragma region database
/// \brief 打开或者创建新的数据库
database::database(const char* strFile,bool bNew)
{
	m_ptrDB.reset(new database_handle(strFile));
	//如果新建文件这写入application_id
	if(bNew)
		m_ptrDB->execute("PRAGMA application_id=1196437808");
	
}

database::~database()
{
	m_ptrDB->close();
} 
			
/// \brief 是否成功打开
bool database::is_open()
{
	return m_ptrDB != NULL;
}	
/// \brief 关闭数据库
void database::close()
{
	if(m_ptrDB.get())
		m_ptrDB->close();

}
/// \brief sqlite的句柄
sqlite3* database::handle()
{
	return m_ptrDB->m_db;
}
		
/// \brief 数据库的句柄。
database_handle_ptr  database::DB()
{
	return m_ptrDB;
}

//获取内容元表
contents* database::contents_table()
{
	spatial_ref_table();
	if(m_ptrContents.get())
		return m_ptrContents.get();

	m_ptrContents.reset(new contents(m_ptrDB));
	return m_ptrContents.get();
}
/// \brief 获取几何信息元表
geometry_columns* database::geometry_columns_table()
{
	if(m_ptrGeo.get())
		return m_ptrGeo.get();

	m_ptrGeo.reset(new geometry_columns(m_ptrDB));
	return m_ptrGeo.get();
}
/// \brief 获取序列表指针
sqlite_sequence* database::sequence_table()
{
	if(m_ptrSequence.get())
		return m_ptrSequence.get();

	m_ptrSequence.reset(new sqlite_sequence(m_ptrDB));
	return m_ptrSequence.get();
}

/// \brief 扩展表
extensions* database::extensions_table()
{
	if(m_ptrExtensions.get())
		return m_ptrExtensions.get();

	m_ptrExtensions.reset(new extensions(m_ptrDB));
	return m_ptrExtensions.get();
}

//获取空间元表
spatial_ref_sys* database::spatial_ref_table()
{
	if(m_ptrSR.get())
		return m_ptrSR.get();

	m_ptrSR.reset(new spatial_ref_sys(m_ptrDB));
	return m_ptrSR.get();
}
/// \brief 打开地物类表
feature_table_ptr database::open_feature_table(const char* strName)
{ 
	content c = contents_table()->query_identifier(strName);
	if(c.identifier.empty())
		return 0;

	/// \brief 获取几何信息元表
	//满足linux下编译语法
	gpkg::geometry_column geocol = geometry_columns_table()->query(c.table_name.c_str());
	return feature_table_ptr(new feature_table(m_ptrDB,c,geocol));
}

/// \brief 创建一个地物类
feature_table_ptr database::create_feature_table(content& c,const std::vector<field>& vecFields)
{
	std::stringstream ss;
	ss<<"create table "<<c.table_name<<"(";
	std::vector<field>::const_iterator it = vecFields.begin();
	for(;it != vecFields.end();it++)
	{
		if(it != vecFields.begin())
			ss<<",";
		ss<<it->name<<" "<<field_type_name(it->type);
		
		if(it->type != INTEGER)
			continue;

		//特殊识别主键字段。
		if(stricmp(it->name.c_str(),"OID")==0 ||
			stricmp(it->name.c_str(),"fid")==0 )
		{
			ss<<"  PRIMARY KEY AUTOINCREMENT ";
		}
	}
	ss<<")";
	if(database_handle::is_error(m_ptrDB->execute(ss.str().c_str())))
		return 0;

	/// \brief 获取几何信息元表
	//满足linux下编译语法
	gpkg::geometry_column geocol = geometry_columns_table()->query(c.table_name.c_str());
	return feature_table_ptr(new feature_table(m_ptrDB,c,geocol));
}

#pragma endregion
#pragma region transaction
transaction::transaction (const database_ptr& db):m_database(db)
{
	sqlite3_exec(m_database->handle(),"begin",NULL,NULL,NULL);
}
transaction::~transaction ()
{
	commit();
}
void transaction::abort()
{
	if(!m_database)
		return;
	sqlite3_exec(m_database->handle(),"abort",NULL,NULL,NULL);
	m_database = NULL;

}
void transaction::commit()
{
	if(!m_database)
		return;
	sqlite3_exec(m_database->handle(),"commit",NULL,NULL,NULL);

}


#pragma endregion 
}