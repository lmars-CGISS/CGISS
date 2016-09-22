#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Requirement_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Requirement_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Requirement_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_Requirement_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Requirement_Type(CMI_Requirement_Type const& init);
	void operator=(CMI_Requirement_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Requirement_Type); }
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmi_altova_CMI_Requirement_Type_altova_citation> citation;
	struct citation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CMI_Requirement_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmi_altova_CMI_Requirement_Type_altova_requestor> requestor;
	struct requestor { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmi_altova_CMI_Requirement_Type_altova_recipient> recipient;
	struct recipient { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	MemberElement<gmi::CMI_PriorityCode_PropertyType, _altova_mi_gmi_altova_CMI_Requirement_Type_altova_priority> priority;
	struct priority { typedef Iterator<gmi::CMI_PriorityCode_PropertyType> iterator; };
	MemberElement<gmi::CMI_RequestedDate_PropertyType, _altova_mi_gmi_altova_CMI_Requirement_Type_altova_requestedDate> requestedDate;
	struct requestedDate { typedef Iterator<gmi::CMI_RequestedDate_PropertyType> iterator; };
	MemberElement<gco::CDateTime_PropertyType, _altova_mi_gmi_altova_CMI_Requirement_Type_altova_expiryDate> expiryDate;
	struct expiryDate { typedef Iterator<gco::CDateTime_PropertyType> iterator; };
	MemberElement<gmi::CMI_Plan_PropertyType, _altova_mi_gmi_altova_CMI_Requirement_Type_altova_satisifiedPlan> satisifiedPlan;
	struct satisifiedPlan { typedef Iterator<gmi::CMI_Plan_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Requirement_Type
