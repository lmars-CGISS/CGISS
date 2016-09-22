#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractMD_Identification_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractMD_Identification_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CAbstractMD_Identification_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CAbstractMD_Identification_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractMD_Identification_Type(CAbstractMD_Identification_Type const& init);
	void operator=(CAbstractMD_Identification_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CAbstractMD_Identification_Type); }
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_citation> citation;
	struct citation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_abstract> abstract;
	struct abstract { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_purpose> purpose;
	struct purpose { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_credit> credit;
	struct credit { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_ProgressCode_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_status> status;
	struct status { typedef Iterator<gmd::CMD_ProgressCode_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_pointOfContact> pointOfContact;
	struct pointOfContact { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	MemberElement<gmd::CMD_MaintenanceInformation_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_resourceMaintenance> resourceMaintenance;
	struct resourceMaintenance { typedef Iterator<gmd::CMD_MaintenanceInformation_PropertyType> iterator; };
	MemberElement<gmd::CMD_BrowseGraphic_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_graphicOverview> graphicOverview;
	struct graphicOverview { typedef Iterator<gmd::CMD_BrowseGraphic_PropertyType> iterator; };
	MemberElement<gmd::CMD_Format_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_resourceFormat> resourceFormat;
	struct resourceFormat { typedef Iterator<gmd::CMD_Format_PropertyType> iterator; };
	MemberElement<gmd::CMD_Keywords_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_descriptiveKeywords> descriptiveKeywords;
	struct descriptiveKeywords { typedef Iterator<gmd::CMD_Keywords_PropertyType> iterator; };
	MemberElement<gmd::CMD_Usage_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_resourceSpecificUsage> resourceSpecificUsage;
	struct resourceSpecificUsage { typedef Iterator<gmd::CMD_Usage_PropertyType> iterator; };
	MemberElement<gmd::CMD_Constraints_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_resourceConstraints> resourceConstraints;
	struct resourceConstraints { typedef Iterator<gmd::CMD_Constraints_PropertyType> iterator; };
	MemberElement<gmd::CMD_AggregateInformation_PropertyType, _altova_mi_gmd_altova_CAbstractMD_Identification_Type_altova_aggregationInfo> aggregationInfo;
	struct aggregationInfo { typedef Iterator<gmd::CMD_AggregateInformation_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractMD_Identification_Type
