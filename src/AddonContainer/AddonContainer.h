// AddonContainer.h

#pragma once
#include <vcclr.h>

using namespace System;
#include <map>
	
namespace GIS {
	
	public enum class ProgressLogLevel
	{
		eLog,
		eWarning,
		eError,
	};
	public interface class ProgressCallback
	{
	public:
		/// \brief ���ȱ仯
		virtual void OnProgress(long long nPos,long long nCount,String^ strTitile,String^ strContent);
		/// \brief ��־����
		virtual void OnLog(String^ strContent,ProgressLogLevel eLevel);
	};
	class ProgressProxy:public Progress
	{
		gcroot<ProgressCallback^> m_Progress;
	public:
		ProgressProxy(ProgressCallback^ progress);
		virtual ~ProgressProxy();

		/// \brief ���ȱ仯
		virtual void OnProgress(long long nPos,long long nCount,const char* strTitile,const char* strContent);
		/// \brief ��־����
		virtual void OnLog(const char* strContent,LogLevel eLevel);
	};

	public ref class AddonContext:public IDisposable
	{
		GIS::Addon* m_pAddon;
		DWORD m_Error;
		HMODULE  OpenModule(BSTR bstrName);
	internal:
		AddonContext(BSTR bstrDLL,BSTR bstrFun);
	public:
		virtual ~AddonContext();
		!AddonContext();
		property String^ Name
		{
			String^ get();
		}
		property String^ Description
		{
			String^ get();
		}
		property int Type
		{
			int get();
		}
		property bool IsValid
		{
			bool get();
		}
		property int ErrorCode
		{
			int get();
		}
		
		String^ Execute(String^ str,ProgressCallback^ progress);

	};

	public ref class AddonContainer:public IDisposable
	{
		std::map<CComBSTR,HMODULE>*  m_ModelCache;
	public:
		AddonContainer();
		virtual ~AddonContainer();
		!AddonContainer();
		static property System::String^  DllDirectory
		{
			System::String^ get();
			void set(System::String^ value);
		}
		
		///����һ�����ʵ��
		AddonContext^ CreateAddon(String^ strDLL,String^ funName);

		///����һ��dll�ĵ�����������
		static array<String^>^ ParserDllExport(String^ dllPath);

	};
	
}
