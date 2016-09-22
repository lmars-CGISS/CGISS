#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeType

#include "type_xs.CstringType.h"


namespace gie
{

namespace gml
{	

class CCodeType : public ::gie::xs::CstringType
{
public:
	gie_EXPORT CCodeType(xercesc::DOMNode* const& init);
	gie_EXPORT CCodeType(CCodeType const& init);
	void operator=(CCodeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCodeType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CCodeType_altova_codeSpace, 0, 0> codeSpace;	// codeSpace CanyURI
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeType
