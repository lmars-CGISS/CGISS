#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_MaintenanceInformation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_MaintenanceInformation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_MaintenanceInformation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_MaintenanceInformation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_MaintenanceInformation_Type(CMD_MaintenanceInformation_Type const& init);
	void operator=(CMD_MaintenanceInformation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_MaintenanceInformation_Type); }
	MemberElement<gmd::CMD_MaintenanceFrequencyCode_PropertyType, _altova_mi_gmd_altova_CMD_MaintenanceInformation_Type_altova_maintenanceAndUpdateFrequency> maintenanceAndUpdateFrequency;
	struct maintenanceAndUpdateFrequency { typedef Iterator<gmd::CMD_MaintenanceFrequencyCode_PropertyType> iterator; };
	MemberElement<gco::CDate_PropertyType, _altova_mi_gmd_altova_CMD_MaintenanceInformation_Type_altova_dateOfNextUpdate> dateOfNextUpdate;
	struct dateOfNextUpdate { typedef Iterator<gco::CDate_PropertyType> iterator; };
	MemberElement<gts::CTM_PeriodDuration_PropertyType, _altova_mi_gmd_altova_CMD_MaintenanceInformation_Type_altova_userDefinedMaintenanceFrequency> userDefinedMaintenanceFrequency;
	struct userDefinedMaintenanceFrequency { typedef Iterator<gts::CTM_PeriodDuration_PropertyType> iterator; };
	MemberElement<gmd::CMD_ScopeCode_PropertyType, _altova_mi_gmd_altova_CMD_MaintenanceInformation_Type_altova_updateScope> updateScope;
	struct updateScope { typedef Iterator<gmd::CMD_ScopeCode_PropertyType> iterator; };
	MemberElement<gmd::CMD_ScopeDescription_PropertyType, _altova_mi_gmd_altova_CMD_MaintenanceInformation_Type_altova_updateScopeDescription> updateScopeDescription;
	struct updateScopeDescription { typedef Iterator<gmd::CMD_ScopeDescription_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_MaintenanceInformation_Type_altova_maintenanceNote> maintenanceNote;
	struct maintenanceNote { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmd_altova_CMD_MaintenanceInformation_Type_altova_contact> contact;
	struct contact { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_MaintenanceInformation_Type
