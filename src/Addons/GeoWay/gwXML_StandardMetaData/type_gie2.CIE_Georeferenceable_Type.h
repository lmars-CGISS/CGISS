#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Georeferenceable_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Georeferenceable_Type

#include "type_gmd.CMD_Georeferenceable_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_Georeferenceable_Type : public ::gie::gmd::CMD_Georeferenceable_Type
{
public:
	gie_EXPORT CIE_Georeferenceable_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_Georeferenceable_Type(CIE_Georeferenceable_Type const& init);
	void operator=(CIE_Georeferenceable_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_Georeferenceable_Type); }
	MemberElement<gcv::CSD_SensorModel_PropertyType, _altova_mi_gie2_altova_CIE_Georeferenceable_Type_altova_geolocationInfo> geolocationInfo;
	struct geolocationInfo { typedef Iterator<gcv::CSD_SensorModel_PropertyType> iterator; };
	MemberElement<gcv::CSD_SensorModel_PropertyType, _altova_mi_gie2_altova_CIE_Georeferenceable_Type_altova_geometricCorrection> geometricCorrection;
	struct geometricCorrection { typedef Iterator<gcv::CSD_SensorModel_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Georeferenceable_Type
