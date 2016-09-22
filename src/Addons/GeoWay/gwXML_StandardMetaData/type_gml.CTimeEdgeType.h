#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeEdgeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeEdgeType

#include "type_gml.CAbstractTimeTopologyPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CTimeEdgeType : public ::gie::gml::CAbstractTimeTopologyPrimitiveType
{
public:
	gie_EXPORT CTimeEdgeType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeEdgeType(CTimeEdgeType const& init);
	void operator=(CTimeEdgeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeEdgeType); }
	MemberElement<gml::CTimeNodePropertyType, _altova_mi_gml_altova_CTimeEdgeType_altova_start> start;
	struct start { typedef Iterator<gml::CTimeNodePropertyType> iterator; };
	MemberElement<gml::CTimeNodePropertyType, _altova_mi_gml_altova_CTimeEdgeType_altova_end> end;
	struct end { typedef Iterator<gml::CTimeNodePropertyType> iterator; };
	MemberElement<gml::CTimePeriodPropertyType, _altova_mi_gml_altova_CTimeEdgeType_altova_extent> extent;
	struct extent { typedef Iterator<gml::CTimePeriodPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeEdgeType
