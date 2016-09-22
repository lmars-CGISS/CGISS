#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Contact_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Contact_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CCI_Contact_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCI_Contact_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCI_Contact_Type(CCI_Contact_Type const& init);
	void operator=(CCI_Contact_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CCI_Contact_Type); }
	MemberElement<gmd::CCI_Telephone_PropertyType, _altova_mi_gmd_altova_CCI_Contact_Type_altova_phone> phone;
	struct phone { typedef Iterator<gmd::CCI_Telephone_PropertyType> iterator; };
	MemberElement<gmd::CCI_Address_PropertyType, _altova_mi_gmd_altova_CCI_Contact_Type_altova_address> address;
	struct address { typedef Iterator<gmd::CCI_Address_PropertyType> iterator; };
	MemberElement<gmd::CCI_OnlineResource_PropertyType, _altova_mi_gmd_altova_CCI_Contact_Type_altova_onlineResource> onlineResource;
	struct onlineResource { typedef Iterator<gmd::CCI_OnlineResource_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Contact_Type_altova_hoursOfService> hoursOfService;
	struct hoursOfService { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Contact_Type_altova_contactInstructions> contactInstructions;
	struct contactInstructions { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Contact_Type
