#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeCurveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeCurveType

#include "type_gml.CAbstractCurveType.h"


namespace gie
{

namespace gml
{	

class CCompositeCurveType : public ::gie::gml::CAbstractCurveType
{
public:
	gie_EXPORT CCompositeCurveType(xercesc::DOMNode* const& init);
	gie_EXPORT CCompositeCurveType(CCompositeCurveType const& init);
	void operator=(CCompositeCurveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCompositeCurveType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CCompositeCurveType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CCurvePropertyType, _altova_mi_gml_altova_CCompositeCurveType_altova_curveMember> curveMember;
	struct curveMember { typedef Iterator<gml::CCurvePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeCurveType
