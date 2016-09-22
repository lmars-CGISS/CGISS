#pragma once
#include <string>

namespace GIS
{
	/// \brief 日志级别
	enum LogLevel
	{
		eInfo,
		eWarning,
		eError,
	};
	
	/// \brief 进度
	class Progress
	{
	public:
		virtual ~Progress(){}
		/// \brief 进度变化
		virtual void OnProgress(long long nPos,long long nCount,const char* strTitile,const char* strContent) = 0;
		/// \brief 日志内容
		virtual void OnLog(const char* strContent,LogLevel eLevel) = 0;

	};
	/// \brief 插件类型
	enum AddonType
	{
		eImport,
		eExport,
		eDataOperator,
	};

	/// \brief 数据转换或操作插件
	///\details 
	///	GIS::Addon* ImportShp();
	///
	///	GIS::Addon* ExportShp();
	///
	/// GIS::Addon* ProjectTransformVector();
	class Addon
	{
	public:
		virtual ~Addon(){}

		/// \brief 摧毁插件
		virtual void Destroy() = 0;
		/// \brief 插件名称
		virtual const char* Name() = 0;
		/// \brief 插件描述
		virtual const char* Description() = 0;
		/// \brief 插件类型
		virtual AddonType Type()  = 0;
		/// \brief 执行插件
		virtual const char* Execute(const char* strParameter,Progress * nProgress) = 0;
	};
	 
	/// \brief 创建实现基类
	/// \details 继承此类以减少插件实现的工作量
	class AddonBase:public Addon
	{
	protected:
		std::string m_strName,m_strDescription;
		std::string m_strResult;
		AddonType m_eType;
	public:
		AddonBase(void){}
		virtual ~AddonBase(void){}
		/// \brief 摧毁插件
		virtual void Destroy(){delete this;}

		/// \brief 插件名称
		virtual const char* Name(){return m_strName.c_str();}
		/// \brief 插件描述
		virtual const char* Description(){return m_strDescription.c_str();}
		/// \brief 插件类型
		virtual AddonType Type(){return m_eType;} 
	};
}

