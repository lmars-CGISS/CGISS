#ifndef _IE_SIMPLE_STANDARD_META_DATA_H_
#define _IE_SIMPLE_STANDARD_META_DATA_H_
#pragma once
#include "stdafx.h"

class IE_SIMPLE_RASTER_EXT_CLASS ieSimpleStandardMetaData
{
private:
	std::string m_strContent;
public:
	ieSimpleStandardMetaData(){m_strContent = "";};
	 ~ieSimpleStandardMetaData(){m_strContent = "";};
	/*!
	* \brief ��ȡԪ��������
	* \returns const char* : 
	* \throws <exception class>
	* \remarks 
	* \see 
	*/
	const char* getXMLContent() const{return m_strContent.data();};
	/*!
	* \brief ����Ԫ��������
	* \param szContent : const char * 
	* \returns void : 
	* \throws <exception class>
	* \remarks 
	* \see 
	*/
	void setXMLContent(const char* szContent){
		if(szContent == NULL)
			m_strContent = "";
		else
			m_strContent = szContent;};
};
#endif