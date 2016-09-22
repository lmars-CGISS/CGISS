#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RangeElementDescription_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RangeElementDescription_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_RangeElementDescription_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_RangeElementDescription_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_RangeElementDescription_Type(CMI_RangeElementDescription_Type const& init);
	void operator=(CMI_RangeElementDescription_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_RangeElementDescription_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_RangeElementDescription_Type_altova_name> name;
	struct name { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_RangeElementDescription_Type_altova_definition> definition;
	struct definition { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CRecord_PropertyType, _altova_mi_gmi_altova_CMI_RangeElementDescription_Type_altova_rangeElement> rangeElement;
	struct rangeElement { typedef Iterator<gco::CRecord_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RangeElementDescription_Type
