#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_GCPCollection_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_GCPCollection_Type

#include "type_gmi.CAbstractMI_GeolocationInformation_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_GCPCollection_Type : public ::gie::gmi::CAbstractMI_GeolocationInformation_Type
{
public:
	gie_EXPORT CMI_GCPCollection_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_GCPCollection_Type(CMI_GCPCollection_Type const& init);
	void operator=(CMI_GCPCollection_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_GCPCollection_Type); }
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gmi_altova_CMI_GCPCollection_Type_altova_collectionIdentification> collectionIdentification;
	struct collectionIdentification { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_GCPCollection_Type_altova_collectionName> collectionName;
	struct collectionName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_ReferenceSystem_PropertyType, _altova_mi_gmi_altova_CMI_GCPCollection_Type_altova_coordinateReferenceSystem> coordinateReferenceSystem;
	struct coordinateReferenceSystem { typedef Iterator<gmd::CMD_ReferenceSystem_PropertyType> iterator; };
	MemberElement<gmi::CMI_GCP_PropertyType, _altova_mi_gmi_altova_CMI_GCPCollection_Type_altova_gcp> gcp;
	struct gcp { typedef Iterator<gmi::CMI_GCP_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_GCPCollection_Type
