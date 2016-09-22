#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_MetadataExtensionInformation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_MetadataExtensionInformation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_MetadataExtensionInformation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_MetadataExtensionInformation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_MetadataExtensionInformation_Type(CMD_MetadataExtensionInformation_Type const& init);
	void operator=(CMD_MetadataExtensionInformation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_MetadataExtensionInformation_Type); }
	MemberElement<gmd::CCI_OnlineResource_PropertyType, _altova_mi_gmd_altova_CMD_MetadataExtensionInformation_Type_altova_extensionOnLineResource> extensionOnLineResource;
	struct extensionOnLineResource { typedef Iterator<gmd::CCI_OnlineResource_PropertyType> iterator; };
	MemberElement<gmd::CMD_ExtendedElementInformation_PropertyType, _altova_mi_gmd_altova_CMD_MetadataExtensionInformation_Type_altova_extendedElementInformation> extendedElementInformation;
	struct extendedElementInformation { typedef Iterator<gmd::CMD_ExtendedElementInformation_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_MetadataExtensionInformation_Type
