#pragma once
#include <string>
using namespace System;
using namespace System::Runtime::InteropServices;
class CNetHelp
{ 
public:
	/*static IUnknownPtr COMObject(Object^ obj)
	{
		 return (IUnknown*)Marshal::GetIUnknownForObject(obj).ToInt32();
	}*/
	static std::string MarshalString ( String ^ s) 
	{
		std::string  strOut;
		MarshalString (s,strOut);
		return strOut;
	}
	static CComBSTR MarshalWString ( String ^ s) 
	{
		CComBSTR  strOut;
		MarshalString (s,strOut);
		return strOut;
	}

	static void MarshalString ( String ^ s, std::string& os ) 
	{ 
	   const char* chars = 
		  (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	   os = chars;
	   Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
	static void MarshalString ( String ^ s, CComBSTR& os ) 
	{ 
	   wchar_t* chars = 
		  (wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	   os = chars;
	   Marshal::FreeHGlobal(IntPtr((void*)chars));
	}


};
