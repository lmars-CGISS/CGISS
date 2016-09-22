#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIdentifiedObjectType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIdentifiedObjectType

#include "type_gml.CDefinitionType.h"


namespace gie
{

namespace gml
{	

class CIdentifiedObjectType : public ::gie::gml::CDefinitionType
{
public:
	gie_EXPORT CIdentifiedObjectType(xercesc::DOMNode* const& init);
	gie_EXPORT CIdentifiedObjectType(CIdentifiedObjectType const& init);
	void operator=(CIdentifiedObjectType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CIdentifiedObjectType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIdentifiedObjectType
