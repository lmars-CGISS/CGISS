#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDerivationUnitTermType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDerivationUnitTermType

#include "type_gml.CUnitOfMeasureType.h"


namespace gie
{

namespace gml
{	

class CDerivationUnitTermType : public ::gie::gml::CUnitOfMeasureType
{
public:
	gie_EXPORT CDerivationUnitTermType(xercesc::DOMNode* const& init);
	gie_EXPORT CDerivationUnitTermType(CDerivationUnitTermType const& init);
	void operator=(CDerivationUnitTermType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDerivationUnitTermType); }

	MemberAttribute<__int64,_altova_mi_gml_altova_CDerivationUnitTermType_altova_exponent, 0, 0> exponent;	// exponent Cinteger
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDerivationUnitTermType
