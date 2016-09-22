#pragma once
#include "preconfig.h" 
#include <string>
#include <sstream>
#include "vectorhelp.h"

UTILITY_NS 
typedef std::string GsString;
typedef std::wstring GsWString;
/// \brief 编码id
enum GsCodePageID
{
	eCP_ACP = 0,
	eCP_GBK=936,
	eCP_UTF16 = 1200,
	eCP_UTF7 = 65000,
	eCP_UTF8 = 65001,
	eCP_GB2312=20936,
	eCP_GB18030=54936,
	
};
/// \brief 宽字符串转窄字符
class GS_API GsCW2A
{ 
	
public:
	GsString m_Str;
	GsCW2A(const wchar_t* str);
	GsCW2A(const wchar_t* str,GsCodePageID eCodePage);
	GsCW2A(const wchar_t* str,const char* codepage);
	GsCW2A(const GsWString& str);
	GsCW2A(const GsWString& str,GsCodePageID eCodePage);
	GsCW2A(const GsWString& str,const char* codepage);

	~GsCW2A() throw();
	operator const char*() const;
	operator GsString() const;
private:
	bool Init(const wchar_t* str,const char* codepage);  

private:
	GsCW2A(const GsCW2A&);
	GsCW2A& operator=(const GsCW2A&);
};

/// \brief 窄字符串转宽字符
class GS_API GsCA2W
{ 
public:
	GsWString m_WStr;
	GsCA2W(const char* str);
	GsCA2W(const char* str,GsCodePageID eCodePage);
	GsCA2W(const char* str,const char* codepage);
	GsCA2W(const GsString& str);
	GsCA2W(const GsString& str,GsCodePageID eCodePage);
	GsCA2W(const GsString& str,const char* codepage);

	~GsCA2W() throw();
	operator const wchar_t*() const;
	operator GsWString() const;
private:
	bool Init(const char* str,const char* codepage);  

private:
	GsCA2W(const GsCA2W&);
	GsCA2W& operator=(const GsCA2W&);
};


/// \brief 实现字符串编码相关的功能
class GS_API GsEncoding
{
public:
	GsEncoding();
	/// \brief 判断字符串是否是utf8字符串。
	///\param  str 要判断的字符串
	///\return 返回输入字符串是否是utf8字符串
	static bool IsUtf8(const char* str);

	/// \brief 将本地字符串转换为utf8字符串
	///\return 返回转换为utf8编码的字符串
	static GsString ToUtf8(const char* str);

	/// \brief 将本地Unicode字符串转换为utf8字符串
	///\return 返回转换为utf8编码的字符串
	static GsString ToUtf8(const wchar_t* str);

	/// \brief 将本地Unicode字符串转换为MBCS的本地窄字符串
	///\return 返回转换为utf8编码的字符串
	static GsString ToLocal(const wchar_t* str);

	/// \brief 将utf8的窄字符串转换Unicode宽字符串
	///\return 返回Unicode编码的字符串
	static GsWString Utf8ToUnicode(const char* str);
	
	/// \brief 将MBCS本地的窄字符串转换Unicode宽字符串
	///\return 返回Unicode编码的字符串
	static GsWString LocalToUnicode(const char* str);

	/// \brief 将Utf8的字符串转换为本地字符串
	///\return 返回转换为本地编码的字符串。
	static GsString ToLocal(const char* str);
};

/// \brief 将字符串转换为utf8字符串
class GS_API GsUtf8
{
	const char* m_Ori;
	GsString m_Utf;
public:
	 GsUtf8(const char* ori);
	explicit GsUtf8(const GsString& ori);
	operator const char*();
	operator GsString();
	GsString Str();
};

/// \brief 将字符串转换为本地字符串
class GS_API GsLocal
{
	const char* m_Ori;
	GsString m_Utf;
public:
	GsLocal(const char* ori);
	GsLocal(const GsString& ori);
	operator const char*();
	operator GsString();
	GsString Str();
};


/// \brief 将生成utf8的字符串。
/// \code{.cpp}
/// std::string str = UTF8("12汉字abc");
/// Fun(UTF8("12汉字abc"));
/// void Fun(const char* str)
/// {....}
/// \endcode
#define UTF8(A) ((A==NULL)?NULL:(GsEncoding::IsUtf8(A)?A:GsEncoding::ToUtf8(A).c_str()))

/// \brief 将任意数据转化为字符串
/// \details 
/// GsString str =  GsStringStream() <<"Number_"<<i;
class GS_API GsStringStream
{
	std::stringstream m_ss;
	GsString m_str;
public:
	GsStringStream();
	virtual ~GsStringStream();
	GsString Str();
	const char* CStr();
	operator GsString ();
	operator const char* ();
	template <typename T>
	GsStringStream& operator << (const T& item)
	{
		m_ss<<item;
		return *this;
	}
};

/// \brief 提供字符串相关的一些功能函数。
class GS_API GsStringHelp
{
public:
	
	/// \brief 转换为字符串对象
	static GsString ToString(const char* str);
	/// \brief 转换为字符串对象
	static GsString ToString(char v);
	/// \brief 转换为字符串对象
	static GsString ToString(unsigned char v);
	/// \brief 转换为字符串对象
	static GsString ToString(short v);
	/// \brief 转换为字符串对象
	static GsString ToString(unsigned short v);
	/// \brief 转换为字符串对象
	static GsString ToString(int v);
	/// \brief 转换为字符串对象
	static GsString ToString(unsigned int v);
	/// \brief 转换为字符串对象
	static GsString ToString(long long v);
	/// \brief 转换为字符串对象
	static GsString ToString(unsigned long long v);
	/// \brief 转换为字符串对象
	static GsString ToString(float v);
	/// \brief 转换为字符串对象
	static GsString ToString(double v);
	/// \brief 转换为字符串对象
	static GsString ToString(bool v);
	/// \brief 转换为字符串对象
	static GsString ToString(const unsigned char* blob,int nLen);

	/// \brief 格式化字符串
	static GsString Format(int nMaxLen,const char* format,...);


	/// \brief 字符串是否为空或者无效字符串
	static bool IsNullOrEmpty(const char* str);
	
		/// \brief 将字符串分割为若干子串
	static GsVector<GsString> Split(const char* str,const char* strSep);

	/// \brief 将字符串分割为若干子串
	static GsVector<GsString> Split(const char* str,char sp);

	
	/// \brief 将字符串中的制定字符串替换为新的部分
	static GsString Replace(const char* str,const char* src,const char* dst);



	/// \brief 剔除字符串前面的空白字符
	static GsString Trim(const char* str);

	/// \brief 剔除字符串前面空白字符
	static GsString TrimLeft(const char* str);

	/// \brief 剔除字符串尾部的空白字符
	static GsString TrimRight(const char* str);

	/// \brief 字符串是否以某个之串开头。
	static bool StartWith(const char* str,const char* strHead,bool bIgnoringCase = true);


	
	/// \brief 通配符匹配字符串
	/// \details 通过 *a  来匹配   aaaa或者bbba或者ccca等，*代表1到N个字符，？代表1个字符
	///\param  pattern 通配符匹配模式如（*?abc)
	///\param str 要匹配的字符串
	static bool IsMatch(const char* pattern,const char* str);

	

};
UTILITY_ENDNS