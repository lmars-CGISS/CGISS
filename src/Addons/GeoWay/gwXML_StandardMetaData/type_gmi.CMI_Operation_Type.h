#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Operation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Operation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Operation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_Operation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Operation_Type(CMI_Operation_Type const& init);
	void operator=(CMI_Operation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Operation_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_citation> citation;
	struct citation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gmd::CMD_ProgressCode_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_status> status;
	struct status { typedef Iterator<gmd::CMD_ProgressCode_PropertyType> iterator; };
	MemberElement<gmi::CMI_OperationTypeCode_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_type> type;
	struct type { typedef Iterator<gmi::CMI_OperationTypeCode_PropertyType> iterator; };
	MemberElement<gmi::CMI_Objective_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_objective> objective;
	struct objective { typedef Iterator<gmi::CMI_Objective_PropertyType> iterator; };
	MemberElement<gmi::CMI_Plan_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_plan> plan;
	struct plan { typedef Iterator<gmi::CMI_Plan_PropertyType> iterator; };
	MemberElement<gmi::CMI_Operation_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_childOperation> childOperation;
	struct childOperation { typedef Iterator<gmi::CMI_Operation_PropertyType> iterator; };
	MemberElement<gmi::CMI_Event_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_significantEvent> significantEvent;
	struct significantEvent { typedef Iterator<gmi::CMI_Event_PropertyType> iterator; };
	MemberElement<gmi::CMI_Platform_PropertyType, _altova_mi_gmi_altova_CMI_Operation_Type_altova_platform> platform;
	struct platform { typedef Iterator<gmi::CMI_Platform_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Operation_Type
