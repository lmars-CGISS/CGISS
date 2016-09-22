#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedObservationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedObservationType

#include "type_gml.CObservationType.h"


namespace gie
{

namespace gml
{	

class CDirectedObservationType : public ::gie::gml::CObservationType
{
public:
	gie_EXPORT CDirectedObservationType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectedObservationType(CDirectedObservationType const& init);
	void operator=(CDirectedObservationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectedObservationType); }
	MemberElement<gml::CDirectionPropertyType, _altova_mi_gml_altova_CDirectedObservationType_altova_direction> direction;
	struct direction { typedef Iterator<gml::CDirectionPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedObservationType
