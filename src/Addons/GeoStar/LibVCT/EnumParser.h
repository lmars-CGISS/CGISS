#pragma once
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>

template<typename ENUM>
class EnumType
{
	std::vector<std::pair<std::string,ENUM> > m_vecPair;
	void Push(std::string str,ENUM value)
	{
		m_vecPair.push_back(std::pair<std::string,ENUM>(str,value));
	}
	static EnumType<ENUM> m_Instance;
public:
	EnumType()
	{
		//通过对不同类型枚举进行构造函数模版特例来达到支持各种不同枚举的目的。
	}
	static EnumType<ENUM>* Instance()
	{
		return &m_Instance;
	}
	ENUM FromString(const char* strValue,ENUM eDefault)
	{
		if(m_vecPair.empty())
			return eDefault;
		std::vector<std::pair<std::string,ENUM> >::iterator it = m_vecPair.begin();
		for(;it != m_vecPair.end();it++)
		{
			if(_strcmpi(it->first.c_str(),strValue)==0)
				return it->second;
		}
		//无法匹配到字符串则将字符串当做数值来处理
		long nNumValue = LONG_MIN;
		std::istringstream iss(strValue);
		iss >> nNumValue;
		//如果此时值不等于LONG_MIN则认为字符串成功解析成一个数字。
		if(nNumValue != LONG_MIN)
		{
			it = m_vecPair.begin();
			for(;it != m_vecPair.end();it++)
			{
				if(nNumValue == it->second)
					return it->second;
			}
		}
		//此处在将来还可以加入考虑16进制的情况。

		return eDefault;
	}
	std::string ToString(ENUM eValue,const char* strDefault)
	{
		std::string strRet = (NULL == strDefault)?"":strDefault;
		std::vector<std::pair<std::string,ENUM> >::iterator it = m_vecPair.begin();
		for(;it != m_vecPair.end();it++)
		{
			if(it->second == eValue)
				return it->first;
		}

		return strRet;
	}

};
//枚举解析器是将C++的枚举从字符串解析成枚举值，或者将枚举值解析为字符串。
class CEnumParser
{
public: 
	 template<typename ENUM>
	 static ENUM ParserFromString(const std::string& strValue,ENUM eDefault)
	{
		return ParserFromString(strValue.c_str(),eDefault);
	};
	 template<typename ENUM>
	static ENUM ParserFromString(const char* strValue,ENUM eDefault)
	{
		return EnumType<ENUM>::Instance()->FromString(strValue,eDefault);
	}	
	template<typename ENUM>
	static std::string ToString(ENUM eValue,const char* strDefault)
	{
		return EnumType<ENUM>::Instance()->ToString(eValue,strDefault);
	}
	template<typename ENUM>
	static std::string ToString(ENUM eValue,const std::string& strDefault)
	{
		return EnumType<ENUM>::Instance()->ToString(eValue,strDefault.c_str());
	}
};


//枚举值直接当做字符串
#define PUSH(X) Push(#X,X);
//其他字符串对应的枚举值。
#define PUSH2(K,V) Push(#K,V);

#define SINGLETONG(T) EnumType<T> EnumType<T>::m_Instance;
//特例化开始
#define BEGIN_SPECIAL_CASE(T) EnumType<T>::EnumType(){

//特例化结束
#define END_SPECIAL_CASE(T) };SINGLETONG(T);
