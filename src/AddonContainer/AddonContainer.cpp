// ������ DLL �ļ���

#include "stdafx.h"

#include "AddonContainer.h"
#include "NetHelp.h"
#include <map>
#include "PEParser.h"
//������dll��ģ����
std::map<CComBSTR,HMODULE> g_Modules;
//��
CComAutoCriticalSection  g_Lock;

//��������ĺ���ָ��
typedef GIS::Addon* (__cdecl *ADDONPROC)(); 

namespace GIS {
	ProgressProxy::ProgressProxy(ProgressCallback^ progress)
	{
		m_Progress = progress;
	}
	ProgressProxy::~ProgressProxy()
	{
	}

		/// \brief ���ȱ仯
	void ProgressProxy::OnProgress(long long nPos,long long nCount,const char* strTitile,const char* strContent)
	{
		m_Progress->OnProgress(nPos,nCount,gcnew String(strTitile),gcnew String(strContent));
	}
	/// \brief ��־����
	void ProgressProxy::OnLog(const char* strContent,LogLevel eLevel)
	{
		
		m_Progress->OnLog(gcnew String(strContent),(ProgressLogLevel)eLevel);
	}
	
	HMODULE  AddonContext::OpenModule(BSTR bstrName)
	{
		m_Error = 0;
		//��������
		g_Lock.Lock();
		//Ѱ��dll���Ƿ��Ѿ���
		std::map<CComBSTR,HMODULE>::iterator it =  g_Modules.find(bstrName);
		HMODULE pModule = NULL;
		if(it != g_Modules.end())
		{
			pModule =  it->second;
			g_Lock.Unlock();
			return pModule;
		}
		pModule = LoadLibrary(bstrName);
		if(NULL ==  pModule)
		{
			m_Error = GetLastError();
			return NULL;
		}
		//��������
		g_Lock.Lock();
		g_Modules[bstrName] = pModule;
		g_Lock.Unlock();
		return pModule;
	}
	AddonContext::AddonContext(BSTR bstrDLL,BSTR bstrFun)
	{
		m_pAddon = NULL;
		//�Դ�д·����ΪKey
		CComBSTR bstr(bstrDLL);
		bstr.ToUpper();
		HMODULE  pModule = OpenModule(bstr);
		if(NULL == pModule)
			return;
		 
		//��ȡ��������ĺ���ָ��
		ADDONPROC ProcAdd =(ADDONPROC)GetProcAddress(pModule,CW2A(bstrFun));
		//Ҳ�п��ܲ����ڵġ�
		if(NULL == ProcAdd)
			return;
		//ִ�к�����ȡ�������ָ��
		m_pAddon = ProcAdd();
	}
	AddonContext::~AddonContext()
	{
		this->!AddonContext();
	}
	AddonContext::!AddonContext()
	{
		//���������������Destroy�����ͷš�
		if(NULL != m_pAddon)
			m_pAddon->Destroy();
		m_pAddon = NULL;
	}
	int AddonContext::ErrorCode::get()
	{
		return m_Error;
	}
	String^ AddonContext::Name::get()
	{
		if(NULL == m_pAddon)
			return nullptr;

		return gcnew String(m_pAddon->Name());
	}
	String^ AddonContext::Description::get()
	{
		if(NULL == m_pAddon)
			return nullptr;

		return gcnew String(m_pAddon->Name());
	}
	int AddonContext::Type::get()
	{
		return 0;
	}
	bool AddonContext::IsValid::get()
	{
		return NULL != m_pAddon;
	}
	String^ AddonContext::Execute(String^ str,ProgressCallback^ progress)
	{
		if(NULL == m_pAddon)
			return nullptr;
		ProgressProxy proxy(progress);
		std::string strInput = CNetHelp::MarshalString(str);
		const char* strOuput = m_pAddon->Execute(strInput.c_str(),&proxy);
		if(NULL == strOuput)
			return nullptr;
		return gcnew String(strOuput);
	}
	AddonContainer::AddonContainer()
	{
		m_ModelCache = new std::map<CComBSTR,HMODULE>();
	}
	AddonContainer::~AddonContainer()
	{
		this->!AddonContainer();
	}
	AddonContainer::!AddonContainer()
	{
		if(NULL != m_ModelCache)
		{
			delete m_ModelCache;
		}
			
		m_ModelCache = NULL;
	}
	
	
	System::String^ AddonContainer::DllDirectory::get()
	{
		TCHAR buff[4096];
		GetDllDirectory(4096,buff);
		return gcnew System::String(buff);
	}

	void AddonContainer::DllDirectory::set(System::String^  value)
	{
		CComBSTR str = CNetHelp::MarshalWString(value);
		SetDllDirectory(str );

	}
	///����һ�����ʵ��
	AddonContext^ AddonContainer::CreateAddon(String^ strDLL,String^ funName)
	{
		CComBSTR dll = CNetHelp::MarshalWString(strDLL);
		CComBSTR name = CNetHelp::MarshalWString(funName);
		return gcnew AddonContext(dll,name);
	}

	///����һ��dll�ĵ�����������
	array<String^>^ AddonContainer::ParserDllExport(String^ dllPath)
	{
		std::string dll = CNetHelp::MarshalString(dllPath);
		PEParser parser(dll.c_str());
		std::vector<std::string> vec;
		parser.EnumExport(vec);
		if(vec.empty())
			return nullptr;

		array<String^>^ arr = gcnew array<String^>(vec.size());
		for(int i =0;i<vec.size();i++)
		{
			arr[i] = gcnew String(vec[i].c_str());
		}
		return arr;
	}


}
