#pragma once
#include "preconfig.h" 
#include <fstream>
#include<string>
#include <sstream>
#include "locker.h"
#include "stringhelp.h"
UTILITY_NS  
/// \brief 日志的级别	
enum LOG_LEVEL
{
  eLOGALL = -99999,
  eLOGNONE=99999,
  eLOGTRACE= -100,
  eLOGDEBUG= 0,
  eLOGINFO=100,
  eLOGWARN=200,
  eLOGERROR=300,
  eLOGFATAL=400,
};

/// \brief 自定义的输出管道
class GS_API GsCustomLogOutput
{
public:
	virtual bool OnLog(const char* log) = 0;
};

/// \brief 将日志输出到文件
class GS_API GsFileCustomLogOutput:public GsCustomLogOutput
{
	std::ofstream m_file;
public:
	virtual bool OnLog(const char* log);
	GsFileCustomLogOutput(const char* strFileName,bool bAppend = false);
};

/// \brief 创建日志
class GS_API GsLogger
{  
	GsSafeObject<GsString> m_strLasterError;
	void* m_pLog;
	void* m_pHook;

	volatile LOG_LEVEL m_nLevel; 
	/// \brief 日志流操作
	class GS_API GsLogStream
	{
		GsLogger& m_Log;
		std::stringstream m_ss;
		bool m_bEnable;
		LOG_LEVEL m_nLevel;
	public:
		GsLogStream(const GsLogStream &rhs);
		GsLogStream(GsLogger& log,LOG_LEVEL l,bool bEnable);
		virtual ~GsLogStream();
		template <typename T>
		inline GsLogStream& operator << (
			const T& item
		)
		{
			if(m_bEnable)
				m_ss<<item;
			return *this;
		}
	};

	  
public:
	/// \brief 构造函数
	GsLogger();
	GsLogger(const char* strLogName);

	/// \brief 判断当前程序是否运行在调试状态
	///\details 仅仅对于windows平台下Visual Studio中调试状态有效，其他情况下一律返回false。
	static bool IsDebuging();

	/// \brief 最后报告的错误
	GsString LastError();
	/// \brief 获得日志级别，设置日志级别
	LOG_LEVEL LogLevel( LOG_LEVEL l);
	LOG_LEVEL LogLevel();
	/// \brief 自定义输出
	GsCustomLogOutput* CustomOutput(GsCustomLogOutput* pOutput);
	GsCustomLogOutput* CustomOutput();
	/// \brief 获取日志名
	std::string Name() const;
	/// \brief 虚析构函数
	virtual ~GsLogger(); 
	/// \brief 日志操作后输出流是否刷新
	///\return 返回true表示刷新，否则，不刷新
	bool auto_flush();
	/// \brief 报告一段日志
	void Log(LOG_LEVEL l,const char* log);	
	/// \brief 缺省的日志对象
	static GsLogger& Default();	
	/// \brief 输出日志
	GsLogStream operator << (const LOG_LEVEL& l) const; 
};
/// \brief 全局日志对象各级别宏定义
#define GSLOG				UTILITY_NAME::GsLogger::Default()

#define GSLOG_ERROR			UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGERROR
#define GS_E				UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGERROR

#define GSLOG_TRACE			UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGTRACE
#define GS_T				UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGTRACE

#define GSLOG_DEBUG			UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGDEBUG
#define GS_D				UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGDEBUG

#define GSLOG_INFO			UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGINFO
#define GS_I				UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGINFO

#define GSLOG_WARN			UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGWARN
#define GS_W				UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGWARN

#define GSLOG_FATAL			UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGFATAL
#define GS_F				UTILITY_NAME::GsLogger::Default()<<UTILITY_NAME::eLOGFATAL
UTILITY_ENDNS
