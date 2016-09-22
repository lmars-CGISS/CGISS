#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDefinitionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDefinitionType

#include "type_gml.CDefinitionBaseType.h"


namespace gie
{

namespace gml
{	

class CDefinitionType : public ::gie::gml::CDefinitionBaseType
{
public:
	gie_EXPORT CDefinitionType(xercesc::DOMNode* const& init);
	gie_EXPORT CDefinitionType(CDefinitionType const& init);
	void operator=(CDefinitionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDefinitionType); }
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CDefinitionType_altova_remarks> remarks;
	struct remarks { typedef Iterator<xs::CstringType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDefinitionType
