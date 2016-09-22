#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Instrument_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Instrument_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Instrument_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_Instrument_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Instrument_Type(CMI_Instrument_Type const& init);
	void operator=(CMI_Instrument_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Instrument_Type); }
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmi_altova_CMI_Instrument_Type_altova_citation> citation;
	struct citation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CMI_Instrument_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_Instrument_Type_altova_type> type;
	struct type { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_Instrument_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmi::CMI_Platform_PropertyType, _altova_mi_gmi_altova_CMI_Instrument_Type_altova_mountedOn> mountedOn;
	struct mountedOn { typedef Iterator<gmi::CMI_Platform_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Instrument_Type
