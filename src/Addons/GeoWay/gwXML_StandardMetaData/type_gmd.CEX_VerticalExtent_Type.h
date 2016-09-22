#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_VerticalExtent_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_VerticalExtent_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CEX_VerticalExtent_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CEX_VerticalExtent_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CEX_VerticalExtent_Type(CEX_VerticalExtent_Type const& init);
	void operator=(CEX_VerticalExtent_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CEX_VerticalExtent_Type); }
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmd_altova_CEX_VerticalExtent_Type_altova_minimumValue> minimumValue;
	struct minimumValue { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmd_altova_CEX_VerticalExtent_Type_altova_maximumValue> maximumValue;
	struct maximumValue { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gsr::CSC_CRS_PropertyType, _altova_mi_gmd_altova_CEX_VerticalExtent_Type_altova_verticalCRS> verticalCRS;
	struct verticalCRS { typedef Iterator<gsr::CSC_CRS_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_VerticalExtent_Type
