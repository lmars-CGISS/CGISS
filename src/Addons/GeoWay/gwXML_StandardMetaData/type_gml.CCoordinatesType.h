#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoordinatesType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoordinatesType

#include "type_xs.CstringType.h"


namespace gie
{

namespace gml
{	

class CCoordinatesType : public ::gie::xs::CstringType
{
public:
	gie_EXPORT CCoordinatesType(xercesc::DOMNode* const& init);
	gie_EXPORT CCoordinatesType(CCoordinatesType const& init);
	void operator=(CCoordinatesType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCoordinatesType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CCoordinatesType_altova_decimal, 0, 0> decimal;	// decimal Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CCoordinatesType_altova_cs, 0, 0> cs;	// cs Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CCoordinatesType_altova_ts, 0, 0> ts;	// ts Cstring
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoordinatesType
