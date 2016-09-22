#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Plan_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Plan_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Plan_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_Plan_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Plan_Type(CMI_Plan_Type const& init);
	void operator=(CMI_Plan_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Plan_Type); }
	MemberElement<gmi::CMI_GeometryTypeCode_PropertyType, _altova_mi_gmi_altova_CMI_Plan_Type_altova_type> type;
	struct type { typedef Iterator<gmi::CMI_GeometryTypeCode_PropertyType> iterator; };
	MemberElement<gmd::CMD_ProgressCode_PropertyType, _altova_mi_gmi_altova_CMI_Plan_Type_altova_status> status;
	struct status { typedef Iterator<gmd::CMD_ProgressCode_PropertyType> iterator; };
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmi_altova_CMI_Plan_Type_altova_citation> citation;
	struct citation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gmi::CMI_Requirement_PropertyType, _altova_mi_gmi_altova_CMI_Plan_Type_altova_satisfiedRequirement> satisfiedRequirement;
	struct satisfiedRequirement { typedef Iterator<gmi::CMI_Requirement_PropertyType> iterator; };
	MemberElement<gmi::CMI_Operation_PropertyType, _altova_mi_gmi_altova_CMI_Plan_Type_altova_operation> operation;
	struct operation { typedef Iterator<gmi::CMI_Operation_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Plan_Type
