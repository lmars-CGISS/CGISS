#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePositionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePositionType

#include "type_gml.CTimePositionUnionType.h"


namespace gie
{

namespace gml
{	

class CTimePositionType : public ::gie::gml::CTimePositionUnionType
{
public:
	gie_EXPORT CTimePositionType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimePositionType(CTimePositionType const& init);
	void operator=(CTimePositionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimePositionType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePositionType_altova_frame, 0, 0> frame;	// frame CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePositionType_altova_calendarEraName, 0, 0> calendarEraName;	// calendarEraName Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePositionType_altova_indeterminatePosition, 0, 4> indeterminatePosition;	// indeterminatePosition CTimeIndeterminateValueType
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePositionType
