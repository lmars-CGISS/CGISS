#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_ResponsibleParty_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_ResponsibleParty_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CCI_ResponsibleParty_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCI_ResponsibleParty_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCI_ResponsibleParty_Type(CCI_ResponsibleParty_Type const& init);
	void operator=(CCI_ResponsibleParty_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CCI_ResponsibleParty_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_ResponsibleParty_Type_altova_individualName> individualName;
	struct individualName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_ResponsibleParty_Type_altova_organisationName> organisationName;
	struct organisationName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_ResponsibleParty_Type_altova_positionName> positionName;
	struct positionName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_Contact_PropertyType, _altova_mi_gmd_altova_CCI_ResponsibleParty_Type_altova_contactInfo> contactInfo;
	struct contactInfo { typedef Iterator<gmd::CCI_Contact_PropertyType> iterator; };
	MemberElement<gmd::CCI_RoleCode_PropertyType, _altova_mi_gmd_altova_CCI_ResponsibleParty_Type_altova_role> role;
	struct role { typedef Iterator<gmd::CCI_RoleCode_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_ResponsibleParty_Type
