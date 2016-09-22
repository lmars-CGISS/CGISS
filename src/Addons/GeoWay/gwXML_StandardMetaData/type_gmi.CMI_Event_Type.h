#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Event_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Event_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Event_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_Event_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Event_Type(CMI_Event_Type const& init);
	void operator=(CMI_Event_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Event_Type); }
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CMI_Event_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gmi::CMI_TriggerCode_PropertyType, _altova_mi_gmi_altova_CMI_Event_Type_altova_trigger> trigger;
	struct trigger { typedef Iterator<gmi::CMI_TriggerCode_PropertyType> iterator; };
	MemberElement<gmi::CMI_ContextCode_PropertyType, _altova_mi_gmi_altova_CMI_Event_Type_altova_context> context;
	struct context { typedef Iterator<gmi::CMI_ContextCode_PropertyType> iterator; };
	MemberElement<gmi::CMI_SequenceCode_PropertyType, _altova_mi_gmi_altova_CMI_Event_Type_altova_sequence> sequence;
	struct sequence { typedef Iterator<gmi::CMI_SequenceCode_PropertyType> iterator; };
	MemberElement<gco::CDateTime_PropertyType, _altova_mi_gmi_altova_CMI_Event_Type_altova_time> time;
	struct time { typedef Iterator<gco::CDateTime_PropertyType> iterator; };
	MemberElement<gmi::CMI_Objective_PropertyType, _altova_mi_gmi_altova_CMI_Event_Type_altova_expectedObjective> expectedObjective;
	struct expectedObjective { typedef Iterator<gmi::CMI_Objective_PropertyType> iterator; };
	MemberElement<gmi::CMI_Instrument_PropertyType, _altova_mi_gmi_altova_CMI_Event_Type_altova_relatedSensor> relatedSensor;
	struct relatedSensor { typedef Iterator<gmi::CMI_Instrument_PropertyType> iterator; };
	MemberElement<gmi::CMI_PlatformPass_PropertyType, _altova_mi_gmi_altova_CMI_Event_Type_altova_relatedPass> relatedPass;
	struct relatedPass { typedef Iterator<gmi::CMI_PlatformPass_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Event_Type
