#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiCurveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiCurveType

#include "type_gml.CAbstractGeometricAggregateType.h"


namespace gie
{

namespace gml
{	

class CMultiCurveType : public ::gie::gml::CAbstractGeometricAggregateType
{
public:
	gie_EXPORT CMultiCurveType(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiCurveType(CMultiCurveType const& init);
	void operator=(CMultiCurveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMultiCurveType); }
	MemberElement<gml::CCurvePropertyType, _altova_mi_gml_altova_CMultiCurveType_altova_curveMember> curveMember;
	struct curveMember { typedef Iterator<gml::CCurvePropertyType> iterator; };
	MemberElement<gml::CCurveArrayPropertyType, _altova_mi_gml_altova_CMultiCurveType_altova_curveMembers> curveMembers;
	struct curveMembers { typedef Iterator<gml::CCurveArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiCurveType
