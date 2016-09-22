#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_NumericalGriddedData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_NumericalGriddedData_Type

#include "type_gie2.CIE_ThematicGriddedData_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_NumericalGriddedData_Type : public ::gie::gie2::CIE_ThematicGriddedData_Type
{
public:
	gie_EXPORT CIE_NumericalGriddedData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_NumericalGriddedData_Type(CIE_NumericalGriddedData_Type const& init);
	void operator=(CIE_NumericalGriddedData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_NumericalGriddedData_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_NumericalGriddedData_Type_altova_valueDescription> valueDescription;
	struct valueDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_NumericalGriddedData_Type
