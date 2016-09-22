#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_AcquisitionInformation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_AcquisitionInformation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_AcquisitionInformation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_AcquisitionInformation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_AcquisitionInformation_Type(CMI_AcquisitionInformation_Type const& init);
	void operator=(CMI_AcquisitionInformation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_AcquisitionInformation_Type); }
	MemberElement<gmi::CMI_Requirement_PropertyType, _altova_mi_gmi_altova_CMI_AcquisitionInformation_Type_altova_acquisitionRequirement> acquisitionRequirement;
	struct acquisitionRequirement { typedef Iterator<gmi::CMI_Requirement_PropertyType> iterator; };
	MemberElement<gmi::CMI_Objective_PropertyType, _altova_mi_gmi_altova_CMI_AcquisitionInformation_Type_altova_objective> objective;
	struct objective { typedef Iterator<gmi::CMI_Objective_PropertyType> iterator; };
	MemberElement<gmi::CMI_Instrument_PropertyType, _altova_mi_gmi_altova_CMI_AcquisitionInformation_Type_altova_instrument> instrument;
	struct instrument { typedef Iterator<gmi::CMI_Instrument_PropertyType> iterator; };
	MemberElement<gmi::CMI_Plan_PropertyType, _altova_mi_gmi_altova_CMI_AcquisitionInformation_Type_altova_acquisitionPlan> acquisitionPlan;
	struct acquisitionPlan { typedef Iterator<gmi::CMI_Plan_PropertyType> iterator; };
	MemberElement<gmi::CMI_Operation_PropertyType, _altova_mi_gmi_altova_CMI_AcquisitionInformation_Type_altova_operation> operation;
	struct operation { typedef Iterator<gmi::CMI_Operation_PropertyType> iterator; };
	MemberElement<gmi::CMI_Platform_PropertyType, _altova_mi_gmi_altova_CMI_AcquisitionInformation_Type_altova_platform> platform;
	struct platform { typedef Iterator<gmi::CMI_Platform_PropertyType> iterator; };
	MemberElement<gmi::CMI_EnvironmentalRecord_PropertyType, _altova_mi_gmi_altova_CMI_AcquisitionInformation_Type_altova_environmentalConditions> environmentalConditions;
	struct environmentalConditions { typedef Iterator<gmi::CMI_EnvironmentalRecord_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_AcquisitionInformation_Type
