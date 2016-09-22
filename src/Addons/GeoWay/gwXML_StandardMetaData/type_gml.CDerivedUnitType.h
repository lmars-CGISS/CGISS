#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDerivedUnitType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDerivedUnitType

#include "type_gml.CUnitDefinitionType.h"


namespace gie
{

namespace gml
{	

class CDerivedUnitType : public ::gie::gml::CUnitDefinitionType
{
public:
	gie_EXPORT CDerivedUnitType(xercesc::DOMNode* const& init);
	gie_EXPORT CDerivedUnitType(CDerivedUnitType const& init);
	void operator=(CDerivedUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDerivedUnitType); }
	MemberElement<gml::CDerivationUnitTermType, _altova_mi_gml_altova_CDerivedUnitType_altova_derivationUnitTerm> derivationUnitTerm;
	struct derivationUnitTerm { typedef Iterator<gml::CDerivationUnitTermType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDerivedUnitType
