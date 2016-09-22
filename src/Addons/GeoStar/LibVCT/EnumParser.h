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
		//ͨ���Բ�ͬ����ö�ٽ��й��캯��ģ���������ﵽ֧�ָ��ֲ�ͬö�ٵ�Ŀ�ġ�
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
		//�޷�ƥ�䵽�ַ������ַ���������ֵ������
		long nNumValue = LONG_MIN;
		std::istringstream iss(strValue);
		iss >> nNumValue;
		//�����ʱֵ������LONG_MIN����Ϊ�ַ����ɹ�������һ�����֡�
		if(nNumValue != LONG_MIN)
		{
			it = m_vecPair.begin();
			for(;it != m_vecPair.end();it++)
			{
				if(nNumValue == it->second)
					return it->second;
			}
		}
		//�˴��ڽ��������Լ��뿼��16���Ƶ������

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
//ö�ٽ������ǽ�C++��ö�ٴ��ַ���������ö��ֵ�����߽�ö��ֵ����Ϊ�ַ�����
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


//ö��ֱֵ�ӵ����ַ���
#define PUSH(X) Push(#X,X);
//�����ַ�����Ӧ��ö��ֵ��
#define PUSH2(K,V) Push(#K,V);

#define SINGLETONG(T) EnumType<T> EnumType<T>::m_Instance;
//��������ʼ
#define BEGIN_SPECIAL_CASE(T) EnumType<T>::EnumType(){

//����������
#define END_SPECIAL_CASE(T) };SINGLETONG(T);
