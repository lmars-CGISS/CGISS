#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUnitDefinitionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUnitDefinitionType

#include "type_gml.CDefinitionType.h"


namespace gie
{

namespace gml
{	

class CUnitDefinitionType : public ::gie::gml::CDefinitionType
{
public:
	gie_EXPORT CUnitDefinitionType(xercesc::DOMNode* const& init);
	gie_EXPORT CUnitDefinitionType(CUnitDefinitionType const& init);
	void operator=(CUnitDefinitionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CUnitDefinitionType); }
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CUnitDefinitionType_altova_quantityType> quantityType;
	struct quantityType { typedef Iterator<gml::CStringOrRefType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CUnitDefinitionType_altova_quantityTypeReference> quantityTypeReference;
	struct quantityTypeReference { typedef Iterator<gml::CReferenceType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CUnitDefinitionType_altova_catalogSymbol> catalogSymbol;
	struct catalogSymbol { typedef Iterator<gml::CCodeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUnitDefinitionType
