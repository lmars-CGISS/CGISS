#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Objective_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Objective_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Objective_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_Objective_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Objective_Type(CMI_Objective_Type const& init);
	void operator=(CMI_Objective_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Objective_Type); }
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CMI_Objective_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_Objective_Type_altova_priority> priority;
	struct priority { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmi::CMI_ObjectiveTypeCode_PropertyType, _altova_mi_gmi_altova_CMI_Objective_Type_altova_type> type;
	struct type { typedef Iterator<gmi::CMI_ObjectiveTypeCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_Objective_Type_altova_function> function;
	struct function { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CEX_Extent_PropertyType, _altova_mi_gmi_altova_CMI_Objective_Type_altova_extent> extent;
	struct extent { typedef Iterator<gmd::CEX_Extent_PropertyType> iterator; };
	MemberElement<gmi::CMI_PlatformPass_PropertyType, _altova_mi_gmi_altova_CMI_Objective_Type_altova_pass> pass;
	struct pass { typedef Iterator<gmi::CMI_PlatformPass_PropertyType> iterator; };
	MemberElement<gmi::CMI_Instrument_PropertyType, _altova_mi_gmi_altova_CMI_Objective_Type_altova_sensingInstrument> sensingInstrument;
	struct sensingInstrument { typedef Iterator<gmi::CMI_Instrument_PropertyType> iterator; };
	MemberElement<gmi::CMI_Event_PropertyType, _altova_mi_gmi_altova_CMI_Objective_Type_altova_objectiveOccurrence> objectiveOccurrence;
	struct objectiveOccurrence { typedef Iterator<gmi::CMI_Event_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Objective_Type
