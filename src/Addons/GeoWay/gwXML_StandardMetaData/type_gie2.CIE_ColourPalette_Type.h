#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ColourPalette_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ColourPalette_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_ColourPalette_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_ColourPalette_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_ColourPalette_Type(CIE_ColourPalette_Type const& init);
	void operator=(CIE_ColourPalette_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_ColourPalette_Type); }
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_ColourPalette_Type_altova_red> red;
	struct red { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_ColourPalette_Type_altova_green> green;
	struct green { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_ColourPalette_Type_altova_blue> blue;
	struct blue { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ColourPalette_Type
