#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeOrNilReasonListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeOrNilReasonListType

#include "type_gml.CNameOrNilReasonListType.h"


namespace gie
{

namespace gml
{	

class CCodeOrNilReasonListType : public ::gie::gml::CNameOrNilReasonListType
{
public:
	gie_EXPORT CCodeOrNilReasonListType(xercesc::DOMNode* const& init);
	gie_EXPORT CCodeOrNilReasonListType(CCodeOrNilReasonListType const& init);
	void operator=(CCodeOrNilReasonListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCodeOrNilReasonListType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CCodeOrNilReasonListType_altova_codeSpace, 0, 0> codeSpace;	// codeSpace CanyURI
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeOrNilReasonListType
