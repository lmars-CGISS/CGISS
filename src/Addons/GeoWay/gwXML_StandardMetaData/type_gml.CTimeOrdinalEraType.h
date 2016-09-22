#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalEraType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalEraType

#include "type_gml.CDefinitionType.h"


namespace gie
{

namespace gml
{	

class CTimeOrdinalEraType : public ::gie::gml::CDefinitionType
{
public:
	gie_EXPORT CTimeOrdinalEraType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeOrdinalEraType(CTimeOrdinalEraType const& init);
	void operator=(CTimeOrdinalEraType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeOrdinalEraType); }
	MemberElement<gml::CRelatedTimeType, _altova_mi_gml_altova_CTimeOrdinalEraType_altova_relatedTime> relatedTime;
	struct relatedTime { typedef Iterator<gml::CRelatedTimeType> iterator; };
	MemberElement<gml::CTimeNodePropertyType, _altova_mi_gml_altova_CTimeOrdinalEraType_altova_start> start;
	struct start { typedef Iterator<gml::CTimeNodePropertyType> iterator; };
	MemberElement<gml::CTimeNodePropertyType, _altova_mi_gml_altova_CTimeOrdinalEraType_altova_end> end;
	struct end { typedef Iterator<gml::CTimeNodePropertyType> iterator; };
	MemberElement<gml::CTimePeriodPropertyType, _altova_mi_gml_altova_CTimeOrdinalEraType_altova_extent> extent;
	struct extent { typedef Iterator<gml::CTimePeriodPropertyType> iterator; };
	MemberElement<gml::CTimeOrdinalEraPropertyType, _altova_mi_gml_altova_CTimeOrdinalEraType_altova_member> member;
	struct member { typedef Iterator<gml::CTimeOrdinalEraPropertyType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CTimeOrdinalEraType_altova_group> group;
	struct group { typedef Iterator<gml::CReferenceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalEraType
