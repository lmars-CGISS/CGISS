#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARDopplerCentroidParameter_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARDopplerCentroidParameter_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_SARDopplerCentroidParameter_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_SARDopplerCentroidParameter_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_SARDopplerCentroidParameter_Type(CIE_SARDopplerCentroidParameter_Type const& init);
	void operator=(CIE_SARDopplerCentroidParameter_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_SARDopplerCentroidParameter_Type); }
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARDopplerCentroidParameter_Type_altova_polynomial_coefficient_0> polynomial_coefficient_0;
	struct polynomial_coefficient_0 { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARDopplerCentroidParameter_Type_altova_polynomial_coefficient_1> polynomial_coefficient_1;
	struct polynomial_coefficient_1 { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARDopplerCentroidParameter_Type_altova_polynomial_coefficient_3> polynomial_coefficient_3;
	struct polynomial_coefficient_3 { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARDopplerCentroidParameter_Type_altova_reference_point> reference_point;
	struct reference_point { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CDateTime_PropertyType, _altova_mi_gie2_altova_CIE_SARDopplerCentroidParameter_Type_altova_time> time;
	struct time { typedef Iterator<gco::CDateTime_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARDopplerCentroidParameter_Type
