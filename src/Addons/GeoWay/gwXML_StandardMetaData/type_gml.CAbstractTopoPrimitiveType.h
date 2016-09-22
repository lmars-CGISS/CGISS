#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTopoPrimitiveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTopoPrimitiveType

#include "type_gml.CAbstractTopologyType.h"


namespace gie
{

namespace gml
{	

class CAbstractTopoPrimitiveType : public ::gie::gml::CAbstractTopologyType
{
public:
	gie_EXPORT CAbstractTopoPrimitiveType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractTopoPrimitiveType(CAbstractTopoPrimitiveType const& init);
	void operator=(CAbstractTopoPrimitiveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractTopoPrimitiveType); }
	MemberElement<gml::CIsolatedPropertyType, _altova_mi_gml_altova_CAbstractTopoPrimitiveType_altova_isolated> isolated;
	struct isolated { typedef Iterator<gml::CIsolatedPropertyType> iterator; };
	MemberElement<gml::CContainerPropertyType, _altova_mi_gml_altova_CAbstractTopoPrimitiveType_altova_container> container;
	struct container { typedef Iterator<gml::CContainerPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTopoPrimitiveType
