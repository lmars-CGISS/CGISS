#pragma once
#include <string>

namespace GIS
{
	/// \brief ��־����
	enum LogLevel
	{
		eInfo,
		eWarning,
		eError,
	};
	
	/// \brief ����
	class Progress
	{
	public:
		virtual ~Progress(){}
		/// \brief ���ȱ仯
		virtual void OnProgress(long long nPos,long long nCount,const char* strTitile,const char* strContent) = 0;
		/// \brief ��־����
		virtual void OnLog(const char* strContent,LogLevel eLevel) = 0;

	};
	/// \brief �������
	enum AddonType
	{
		eImport,
		eExport,
		eDataOperator,
	};

	/// \brief ����ת����������
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

		/// \brief �ݻٲ��
		virtual void Destroy() = 0;
		/// \brief �������
		virtual const char* Name() = 0;
		/// \brief �������
		virtual const char* Description() = 0;
		/// \brief �������
		virtual AddonType Type()  = 0;
		/// \brief ִ�в��
		virtual const char* Execute(const char* strParameter,Progress * nProgress) = 0;
	};
	 
	/// \brief ����ʵ�ֻ���
	/// \details �̳д����Լ��ٲ��ʵ�ֵĹ�����
	class AddonBase:public Addon
	{
	protected:
		std::string m_strName,m_strDescription;
		std::string m_strResult;
		AddonType m_eType;
	public:
		AddonBase(void){}
		virtual ~AddonBase(void){}
		/// \brief �ݻٲ��
		virtual void Destroy(){delete this;}

		/// \brief �������
		virtual const char* Name(){return m_strName.c_str();}
		/// \brief �������
		virtual const char* Description(){return m_strDescription.c_str();}
		/// \brief �������
		virtual AddonType Type(){return m_eType;} 
	};
}

