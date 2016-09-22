#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicity_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicity_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gco
{	

class CMultiplicity_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMultiplicity_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiplicity_Type(CMultiplicity_Type const& init);
	void operator=(CMultiplicity_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CMultiplicity_Type); }
	MemberElement<gco::CMultiplicityRange_PropertyType, _altova_mi_gco_altova_CMultiplicity_Type_altova_range> range;
	struct range { typedef Iterator<gco::CMultiplicityRange_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicity_Type
