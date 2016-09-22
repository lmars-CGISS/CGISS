#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedObservationAtDistanceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedObservationAtDistanceType

#include "type_gml.CDirectedObservationType.h"


namespace gie
{

namespace gml
{	

class CDirectedObservationAtDistanceType : public ::gie::gml::CDirectedObservationType
{
public:
	gie_EXPORT CDirectedObservationAtDistanceType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectedObservationAtDistanceType(CDirectedObservationAtDistanceType const& init);
	void operator=(CDirectedObservationAtDistanceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectedObservationAtDistanceType); }
	MemberElement<gml::CMeasureType, _altova_mi_gml_altova_CDirectedObservationAtDistanceType_altova_distance> distance;
	struct distance { typedef Iterator<gml::CMeasureType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedObservationAtDistanceType
