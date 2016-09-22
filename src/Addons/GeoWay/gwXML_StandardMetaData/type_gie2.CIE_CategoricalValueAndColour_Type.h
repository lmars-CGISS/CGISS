#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_CategoricalValueAndColour_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_CategoricalValueAndColour_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_CategoricalValueAndColour_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_CategoricalValueAndColour_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_CategoricalValueAndColour_Type(CIE_CategoricalValueAndColour_Type const& init);
	void operator=(CIE_CategoricalValueAndColour_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_CategoricalValueAndColour_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_CategoricalValueAndColour_Type_altova_categoryName> categoryName;
	struct categoryName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gie2::CIE_ColourPalette_PropertyType, _altova_mi_gie2_altova_CIE_CategoricalValueAndColour_Type_altova_colourPalette> colourPalette;
	struct colourPalette { typedef Iterator<gie2::CIE_ColourPalette_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_CategoricalValueAndColour_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_CategoricalValueAndColour_Type_altova_value2> value2;
	struct value2 { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_CategoricalValueAndColour_Type
