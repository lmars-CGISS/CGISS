#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_ProcessStep_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_ProcessStep_Type

#include "type_gmd.CLI_ProcessStep_Type.h"


namespace gie
{

namespace gmi
{	

class CLE_ProcessStep_Type : public ::gie::gmd::CLI_ProcessStep_Type
{
public:
	gie_EXPORT CLE_ProcessStep_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLE_ProcessStep_Type(CLE_ProcessStep_Type const& init);
	void operator=(CLE_ProcessStep_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CLE_ProcessStep_Type); }
	MemberElement<gmi::CLE_Source_PropertyType, _altova_mi_gmi_altova_CLE_ProcessStep_Type_altova_output> output;
	struct output { typedef Iterator<gmi::CLE_Source_PropertyType> iterator; };
	MemberElement<gmi::CLE_ProcessStepReport_PropertyType, _altova_mi_gmi_altova_CLE_ProcessStep_Type_altova_report> report;
	struct report { typedef Iterator<gmi::CLE_ProcessStepReport_PropertyType> iterator; };
	MemberElement<gmi::CLE_Processing_PropertyType, _altova_mi_gmi_altova_CLE_ProcessStep_Type_altova_processingInformation> processingInformation;
	struct processingInformation { typedef Iterator<gmi::CLE_Processing_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_ProcessStep_Type
