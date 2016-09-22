#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeListType

#include "type_gml.CNameListType.h"


namespace gie
{

namespace gml
{	

class CCodeListType : public ::gie::gml::CNameListType
{
public:
	gie_EXPORT CCodeListType(xercesc::DOMNode* const& init);
	gie_EXPORT CCodeListType(CCodeListType const& init);
	void operator=(CCodeListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCodeListType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CCodeListType_altova_codeSpace, 0, 0> codeSpace;	// codeSpace CanyURI
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeListType
