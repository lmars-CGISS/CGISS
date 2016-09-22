#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeInstantType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeInstantType

#include "type_gml.CAbstractTimeGeometricPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CTimeInstantType : public ::gie::gml::CAbstractTimeGeometricPrimitiveType
{
public:
	gie_EXPORT CTimeInstantType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeInstantType(CTimeInstantType const& init);
	void operator=(CTimeInstantType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeInstantType); }
	MemberElement<gml::CTimePositionType, _altova_mi_gml_altova_CTimeInstantType_altova_timePosition> timePosition;
	struct timePosition { typedef Iterator<gml::CTimePositionType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeInstantType
