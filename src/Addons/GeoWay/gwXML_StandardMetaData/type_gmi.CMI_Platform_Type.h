#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Platform_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Platform_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Platform_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_Platform_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Platform_Type(CMI_Platform_Type const& init);
	void operator=(CMI_Platform_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Platform_Type); }
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmi_altova_CMI_Platform_Type_altova_citation> citation;
	struct citation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CMI_Platform_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_Platform_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmi_altova_CMI_Platform_Type_altova_sponsor> sponsor;
	struct sponsor { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	MemberElement<gmi::CMI_Instrument_PropertyType, _altova_mi_gmi_altova_CMI_Platform_Type_altova_instrument> instrument;
	struct instrument { typedef Iterator<gmi::CMI_Instrument_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Platform_Type
