#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCodeListValue_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCodeListValue_Type

#include "type_xs.CstringType.h"


namespace gie
{

namespace gie2
{	

class CCodeListValue_Type : public ::gie::xs::CstringType
{
public:
	gie_EXPORT CCodeListValue_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCodeListValue_Type(CCodeListValue_Type const& init);
	void operator=(CCodeListValue_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CCodeListValue_Type); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gie2_altova_CCodeListValue_Type_altova_codeList, 0, 0> codeList;	// codeList CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CCodeListValue_Type_altova_codeListValue, 0, 0> codeListValue;	// codeListValue CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CCodeListValue_Type_altova_codeSpace, 0, 0> codeSpace;	// codeSpace CanyURI
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCodeListValue_Type
