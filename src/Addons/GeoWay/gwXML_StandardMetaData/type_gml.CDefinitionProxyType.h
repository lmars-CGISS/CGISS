#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDefinitionProxyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDefinitionProxyType

#include "type_gml.CDefinitionType.h"


namespace gie
{

namespace gml
{	

class CDefinitionProxyType : public ::gie::gml::CDefinitionType
{
public:
	gie_EXPORT CDefinitionProxyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDefinitionProxyType(CDefinitionProxyType const& init);
	void operator=(CDefinitionProxyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDefinitionProxyType); }
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CDefinitionProxyType_altova_definitionRef> definitionRef;
	struct definitionRef { typedef Iterator<gml::CReferenceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDefinitionProxyType
