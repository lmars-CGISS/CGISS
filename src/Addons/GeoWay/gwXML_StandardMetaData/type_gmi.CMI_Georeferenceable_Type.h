#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Georeferenceable_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Georeferenceable_Type

#include "type_gmd.CMD_Georeferenceable_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Georeferenceable_Type : public ::gie::gmd::CMD_Georeferenceable_Type
{
public:
	gie_EXPORT CMI_Georeferenceable_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Georeferenceable_Type(CMI_Georeferenceable_Type const& init);
	void operator=(CMI_Georeferenceable_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Georeferenceable_Type); }
	MemberElement<gmi::CMI_GeolocationInformation_PropertyType, _altova_mi_gmi_altova_CMI_Georeferenceable_Type_altova_geolocationInformation> geolocationInformation;
	struct geolocationInformation { typedef Iterator<gmi::CMI_GeolocationInformation_PropertyType> iterator; };
	MemberElement<gmi::CMI_Platform_PropertyType, _altova_mi_gmi_altova_CMI_Georeferenceable_Type_altova_platformParameters> platformParameters;
	struct platformParameters { typedef Iterator<gmi::CMI_Platform_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Georeferenceable_Type
