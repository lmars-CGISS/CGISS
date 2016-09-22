#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Metadata_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Metadata_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_Metadata_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_Metadata_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_Metadata_Type(CMD_Metadata_Type const& init);
	void operator=(CMD_Metadata_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_Metadata_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_fileIdentifier> fileIdentifier;
	struct fileIdentifier { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_language> language;
	struct language { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_CharacterSetCode_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_characterSet> characterSet;
	struct characterSet { typedef Iterator<gmd::CMD_CharacterSetCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_parentIdentifier> parentIdentifier;
	struct parentIdentifier { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_ScopeCode_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_hierarchyLevel> hierarchyLevel;
	struct hierarchyLevel { typedef Iterator<gmd::CMD_ScopeCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_hierarchyLevelName> hierarchyLevelName;
	struct hierarchyLevelName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_contact> contact;
	struct contact { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	MemberElement<gco::CDate_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_dateStamp> dateStamp;
	struct dateStamp { typedef Iterator<gco::CDate_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_metadataStandardName> metadataStandardName;
	struct metadataStandardName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_metadataStandardVersion> metadataStandardVersion;
	struct metadataStandardVersion { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_dataSetURI> dataSetURI;
	struct dataSetURI { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CPT_Locale_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_locale> locale;
	struct locale { typedef Iterator<gmd::CPT_Locale_PropertyType> iterator; };
	MemberElement<gmd::CMD_SpatialRepresentation_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_spatialRepresentationInfo> spatialRepresentationInfo;
	struct spatialRepresentationInfo { typedef Iterator<gmd::CMD_SpatialRepresentation_PropertyType> iterator; };
	MemberElement<gmd::CMD_ReferenceSystem_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_referenceSystemInfo> referenceSystemInfo;
	struct referenceSystemInfo { typedef Iterator<gmd::CMD_ReferenceSystem_PropertyType> iterator; };
	MemberElement<gmd::CMD_MetadataExtensionInformation_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_metadataExtensionInfo> metadataExtensionInfo;
	struct metadataExtensionInfo { typedef Iterator<gmd::CMD_MetadataExtensionInformation_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identification_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_identificationInfo> identificationInfo;
	struct identificationInfo { typedef Iterator<gmd::CMD_Identification_PropertyType> iterator; };
	MemberElement<gmd::CMD_ContentInformation_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_contentInfo> contentInfo;
	struct contentInfo { typedef Iterator<gmd::CMD_ContentInformation_PropertyType> iterator; };
	MemberElement<gmd::CMD_Distribution_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_distributionInfo> distributionInfo;
	struct distributionInfo { typedef Iterator<gmd::CMD_Distribution_PropertyType> iterator; };
	MemberElement<gmd::CDQ_DataQuality_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_dataQualityInfo> dataQualityInfo;
	struct dataQualityInfo { typedef Iterator<gmd::CDQ_DataQuality_PropertyType> iterator; };
	MemberElement<gmd::CMD_PortrayalCatalogueReference_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_portrayalCatalogueInfo> portrayalCatalogueInfo;
	struct portrayalCatalogueInfo { typedef Iterator<gmd::CMD_PortrayalCatalogueReference_PropertyType> iterator; };
	MemberElement<gmd::CMD_Constraints_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_metadataConstraints> metadataConstraints;
	struct metadataConstraints { typedef Iterator<gmd::CMD_Constraints_PropertyType> iterator; };
	MemberElement<gmd::CMD_ApplicationSchemaInformation_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_applicationSchemaInfo> applicationSchemaInfo;
	struct applicationSchemaInfo { typedef Iterator<gmd::CMD_ApplicationSchemaInformation_PropertyType> iterator; };
	MemberElement<gmd::CMD_MaintenanceInformation_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_metadataMaintenance> metadataMaintenance;
	struct metadataMaintenance { typedef Iterator<gmd::CMD_MaintenanceInformation_PropertyType> iterator; };
	MemberElement<gmd::CDS_Aggregate_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_series> series;
	struct series { typedef Iterator<gmd::CDS_Aggregate_PropertyType> iterator; };
	MemberElement<gmd::CDS_DataSet_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_describes> describes;
	struct describes { typedef Iterator<gmd::CDS_DataSet_PropertyType> iterator; };
	MemberElement<gco::CObjectReference_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_propertyType> propertyType;
	struct propertyType { typedef Iterator<gco::CObjectReference_PropertyType> iterator; };
	MemberElement<gco::CObjectReference_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_featureType> featureType;
	struct featureType { typedef Iterator<gco::CObjectReference_PropertyType> iterator; };
	MemberElement<gco::CObjectReference_PropertyType, _altova_mi_gmd_altova_CMD_Metadata_Type_altova_featureAttribute> featureAttribute;
	struct featureAttribute { typedef Iterator<gco::CObjectReference_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Metadata_Type
