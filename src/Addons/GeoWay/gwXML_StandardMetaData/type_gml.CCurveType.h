#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCurveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCurveType

#include "type_gml.CAbstractCurveType.h"


namespace gie
{

namespace gml
{	

class CCurveType : public ::gie::gml::CAbstractCurveType
{
public:
	gie_EXPORT CCurveType(xercesc::DOMNode* const& init);
	gie_EXPORT CCurveType(CCurveType const& init);
	void operator=(CCurveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCurveType); }
	MemberElement<gml::CCurveSegmentArrayPropertyType, _altova_mi_gml_altova_CCurveType_altova_segments> segments;
	struct segments { typedef Iterator<gml::CCurveSegmentArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCurveType
