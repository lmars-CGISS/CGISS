#pragma once
#include "tinyxml2.h"
#include <string>

//解析key，value的参数。
class KVParameter
{
	tinyxml2::XMLDocument m_Doc;
	tinyxml2::XMLElement* NewElement(tinyxml2::XMLNode*  e,const char* strKey)
	{
		tinyxml2::XMLElement* pE = e->GetDocument()->NewElement(strKey);
		e->InsertEndChild(pE);
		return pE;
	}
	tinyxml2::XMLElement* Find(const char* strKey)
	{
		if(NULL == m_Doc.RootElement())
			return NULL;
		tinyxml2::XMLElement* pE = m_Doc.RootElement()->FirstChildElement("Parameter");
		while(NULL != pE)
		{
			//Key相等则返回
			const char* k = pE->Attribute("Key");
			if(NULL != k)
			{
				if(_stricmp(k,strKey)==0)
					return pE;
			}
			
			pE = pE->NextSiblingElement("Parameter");
		}
		return NULL;
	}
public:
	//从xml解析
	KVParameter(const char* strXML)
	{
		m_Doc.Parse(strXML);
	}
	//构造一个新的
	KVParameter()
	{
		//插入根节点。
		NewElement(&m_Doc,"GIS");

	}
	bool Error()
	{
		return m_Doc.Error() || m_Doc.RootElement() == NULL;
	}

	//设置值。
	template<class T>
	void SetValue(const char* strKey,T value)
	{
		tinyxml2::XMLElement* pEle =  Find(strKey);
		tinyxml2::XMLElement* pValue = NULL;
		if(pEle == NULL)
		{
			pEle = NewElement(m_Doc.RootElement(),"Parameter");
			pEle->SetAttribute("Key",strKey);
		}
		else
			pValue = pEle->FirstChildElement("Value");

		if(NULL == pValue)
			pValue = NewElement(pEle,"Value");
		pValue->SetText(value);
	}
	//获取值
	std::string Value(const char* strKey)
	{
		tinyxml2::XMLElement* pEle =  Find(strKey);
		if(NULL == pEle)
			return std::string();
		tinyxml2::XMLElement* pValue = pEle->FirstChildElement("Value");
		if(pValue == NULL)
			return std::string();
		const char* str =  pValue->GetText();
		if(NULL == str || strlen(str)==0)
			return std::string();
		return std::string(str);
		
	}
	//将KVP输出为字符串
	std::string ToString()
	{
		tinyxml2::XMLPrinter p;
		m_Doc.Accept(&p);
		return p.CStr();
	}
};
