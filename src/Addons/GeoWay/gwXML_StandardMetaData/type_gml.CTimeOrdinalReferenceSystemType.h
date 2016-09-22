#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalReferenceSystemType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalReferenceSystemType

#include "type_gml.CTimeReferenceSystemType.h"


namespace gie
{

namespace gml
{	

class CTimeOrdinalReferenceSystemType : public ::gie::gml::CTimeReferenceSystemType
{
public:
	gie_EXPORT CTimeOrdinalReferenceSystemType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeOrdinalReferenceSystemType(CTimeOrdinalReferenceSystemType const& init);
	void operator=(CTimeOrdinalReferenceSystemType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeOrdinalReferenceSystemType); }
	MemberElement<gml::CTimeOrdinalEraPropertyType, _altova_mi_gml_altova_CTimeOrdinalReferenceSystemType_altova_component> component;
	struct component { typedef Iterator<gml::CTimeOrdinalEraPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalReferenceSystemType
