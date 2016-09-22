#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DataIdentification_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DataIdentification_Type

#include "type_gmd.CAbstractMD_Identification_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_DataIdentification_Type : public ::gie::gmd::CAbstractMD_Identification_Type
{
public:
	gie_EXPORT CMD_DataIdentification_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_DataIdentification_Type(CMD_DataIdentification_Type const& init);
	void operator=(CMD_DataIdentification_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_DataIdentification_Type); }
	MemberElement<gmd::CMD_SpatialRepresentationTypeCode_PropertyType, _altova_mi_gmd_altova_CMD_DataIdentification_Type_altova_spatialRepresentationType> spatialRepresentationType;
	struct spatialRepresentationType { typedef Iterator<gmd::CMD_SpatialRepresentationTypeCode_PropertyType> iterator; };
	MemberElement<gmd::CMD_Resolution_PropertyType, _altova_mi_gmd_altova_CMD_DataIdentification_Type_altova_spatialResolution> spatialResolution;
	struct spatialResolution { typedef Iterator<gmd::CMD_Resolution_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_DataIdentification_Type_altova_language> language;
	struct language { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_CharacterSetCode_PropertyType, _altova_mi_gmd_altova_CMD_DataIdentification_Type_altova_characterSet> characterSet;
	struct characterSet { typedef Iterator<gmd::CMD_CharacterSetCode_PropertyType> iterator; };
	MemberElement<gmd::CMD_TopicCategoryCode_PropertyType, _altova_mi_gmd_altova_CMD_DataIdentification_Type_altova_topicCategory> topicCategory;
	struct topicCategory { typedef Iterator<gmd::CMD_TopicCategoryCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_DataIdentification_Type_altova_environmentDescription> environmentDescription;
	struct environmentDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CEX_Extent_PropertyType, _altova_mi_gmd_altova_CMD_DataIdentification_Type_altova_extent> extent;
	struct extent { typedef Iterator<gmd::CEX_Extent_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_DataIdentification_Type_altova_supplementalInformation> supplementalInformation;
	struct supplementalInformation { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DataIdentification_Type
