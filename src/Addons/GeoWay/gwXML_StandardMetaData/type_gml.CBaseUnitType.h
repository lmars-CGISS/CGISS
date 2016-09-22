#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBaseUnitType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBaseUnitType

#include "type_gml.CUnitDefinitionType.h"


namespace gie
{

namespace gml
{	

class CBaseUnitType : public ::gie::gml::CUnitDefinitionType
{
public:
	gie_EXPORT CBaseUnitType(xercesc::DOMNode* const& init);
	gie_EXPORT CBaseUnitType(CBaseUnitType const& init);
	void operator=(CBaseUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CBaseUnitType); }
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CBaseUnitType_altova_unitsSystem> unitsSystem;
	struct unitsSystem { typedef Iterator<gml::CReferenceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBaseUnitType
