#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicityRange_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicityRange_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gco
{	

class CMultiplicityRange_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMultiplicityRange_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiplicityRange_Type(CMultiplicityRange_Type const& init);
	void operator=(CMultiplicityRange_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CMultiplicityRange_Type); }
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gco_altova_CMultiplicityRange_Type_altova_lower> lower;
	struct lower { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CUnlimitedInteger_PropertyType, _altova_mi_gco_altova_CMultiplicityRange_Type_altova_upper> upper;
	struct upper { typedef Iterator<gco::CUnlimitedInteger_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicityRange_Type
