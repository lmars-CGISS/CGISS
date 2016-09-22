#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRingType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRingType

#include "type_gml.CAbstractRingType.h"


namespace gie
{

namespace gml
{	

class CRingType : public ::gie::gml::CAbstractRingType
{
public:
	gie_EXPORT CRingType(xercesc::DOMNode* const& init);
	gie_EXPORT CRingType(CRingType const& init);
	void operator=(CRingType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CRingType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CRingType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CCurvePropertyType, _altova_mi_gml_altova_CRingType_altova_curveMember> curveMember;
	struct curveMember { typedef Iterator<gml::CCurvePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRingType
